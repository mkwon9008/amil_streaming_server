


#include <amil_config.h>
#include <amil_core.h>

static amil_int_t amil_test_full_name(amil_str_t *name);

static amil_atomic_t temp_number = 0;
amil_atomic_t *amil_temp_number = &temp_number;
amil_atomic_int_t amil_random_number = 123456;

amil_int_t amil_get_full_name(amil_pool_t *pool, amil_str_t *prefix, amil_str_t *name)
{
	size_t len;
	u_char *p, *n;
	amil_int_t rc;

	rc = amil_test_full_name(name);

	if(rc == AMIL_OK)
	{
		return rc;
	}

	len = prefix -> len;

#if (AMIL_WIN32)

	if(rc == 2)
	{
		len = rc;
	}

#endif

	n = amil_pnalloc(pool, len + name -> len + 1);

	if(n == NULL) 
	{
		return AMIL_ERROR;
	}

	p = amil_cpymem(n, prefix -> data, len);
	amil_cpystrn(p, name -> data, name -> len + 1);

	name -> len += len;
	name -> data = n;

	return AMIL_OK;

}

static amil_int_t amil_test_full_name(amil_str_t *name)
{
#if (AMIL_WIN32)	
	u_char c0, c1;

	c0 = name -> data[0];

	if(name -> len < 2)
	{
		if(c0 == '/')
		{
			return 2;
		}
		return AMIL_DECLINED;
	}

	c1 = name -> data[1];
	
	if(c1 == ':')
	{
		c0 |= 0x20;

		if((c0 >= 'a' && c0 <= 'z'))
		{
			return AMIL_OK;
		}

		return AMIL_DECLINED;
	}

	if(c1 == '/')
	{
		return AMIL_OK;
	}

	if(c0 == '/')
	{
		return 2;
	}

	return AMIL_DECLINED;


#else

	if(name -> data[0] == '/')
	{
		return AMIL_OK;
	}

	return AMIL_DECLINED;
#endif	
}

ssize_t amil_write_chain_to_temp_file(amil_temp_file_t *tf, amil_chain_t *chain)
{
	amil_int_t rc;

	if(tf -> file.fd == AMIL_INVALID_FILE)
	{
		rc = amil_create_temp_file (&tf -> file, tf -> path, tf -> pool, tf -> persistent, tf -> clean, tf -> access);

		if(rc != AMIL_OK)
		{
			return rc;
		}

		if(tf -> log_level)
		{
			amil_log_error(tf -> log_level, tf -> file.log, 0, "%s %V", tf -> warn, &tf -> file.name);
		}
	}

#if (AMIL_THREADS && AMIL_HAVE_PWRITEV)	
	if(tf -> thread_write)
	{
		return amil_thread_write_chain_to_file(&tf -> file, chain, tf -> offset, tf -> pool);
	}
#endif	

	return amil_write_chain_to_file(&tf -> file, chain, &tf -> offset, tf -> pool);

}


amil_int_t amil_create_temp_file(amil_file_t *file, amil_path_t *path, amil_pool_t *pool, amil_uint_t persistent, amil_uint_t clean, amil_uint_t access)
{
	uint32_t n;
	amil_err_t err;
	amil_pool_cleanup_t *cln;
	amil_pool_cleanup_file_t *clnf;

	file -> name.len = path -> name.len + 1 + path -> len + 10;

	file -> name.data = amil_pnalloc(pool, file -> name.len + 1);
	if(file -> name.data == NULL)
	{
		return AMIL_ERROR;
	}

#if 0
	for(i = 0; i < file -> name.len; i++)
	{
		file -> name.data[i] = 'X';
	}
#endif

	amil_memcpy(file -> name.data, path -> name.data, path -> name.len);

	n = (uint32_t) amil_next_temp_number(0);

	cln = amil_pool_cleanup_add(pool, sizeof(amil_pool_cleanup_file_t));
	if(cln == NULL)
	{
		return AMIL_ERROR;
	}

	for(/*void*/;/*void*/;/*void*/)
	{
		(void) amil_sprintf(file -> name.data + path -> name.len + 1 + path -> len, "%010uD%z", n);
		amil_create_hashed_filename(path, file -> name.data, file -> name.len);
		amil_log_debug1 (AMIL_LOG_DEBUG_CORE, file -> log, 0, "hashed path : %s", file -> name.data);
		file -> fd = amil_open_tempfile(file -> name.data, persistent, access);

		amil_log_debug1 (AMIL_LOG_DEBUG_CORE, file -> log, 0, "temp fd: : %d", file -> fd);

		if(file -> fd != AMIL_INVALID_FILE)
		{
			cln -> handler = clean ? amil_pool_delete_file : amil_pool_cleanup_file;

			clnf = cln -> data;

			clnf -> fd = file -> fd;
			clnf -> name = file -> name.data;
			clnf -> log = pool -> log;

			return AMIL_OK;
		}

		err = amil_errno;

		if(err == AMIL_EEXIST_FILE)
		{
			n = (uint32_t) amil_next_temp_number(1);
			continue;
		}

		if((path -> level[0] == 0) || (err != AMIL_ENOPATH))
		{
			amil_log_error(AMIL_LOG_CRIT, file -> log, err, amil_open_tempfile_n "\"%s\" failed", file -> name.data);
			return AMIL_ERROR;
		}

		if(amil_create_path(file, path) == AMIL_ERROR)
		{
			return AMIL_ERROR;
		}
	}
}
