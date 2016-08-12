
/*	amil_file.c
*	This file is relation with file I/O functionality.
*	<RULE>
*	1. Function is created as concise as possible.
*	2. If you must write a custom function before amil + underbar.
*	3. Function names are separated by a custom type + content + relevant work.
	   If needed, it may be written the use of the method object between custom type and content.
*	4. The macro statement is written in capital letters.
*/	

#include <amil_config.h>
#include <amil_core.h>


/*	static preprocessing.
*	amil_int_t = 
*	amil_atomic_t = defined by amil_atomic.h
*	amil_atomic_int_t = defined by amil_atomic.h
*/
static amil_int_t amil_test_full_name(amil_str_t *name);
static amil_atomic_t temp_number = 0;
amil_atomic_t *amil_temp_number = &temp_number;
amil_atomic_int_t amil_random_number = 123456;


/*	amil_get_full_name function is get and check full name from data.
*	amil_pool_t = type defined by amil_core.h
*	amil_str_t = type defined by amil_string.h
*	amil_test_full_name = function defined by amil_file.c
*	amil_test_full_name = function prototype defined amil_file.h
*	amil_pnalloc = function defined amil_palloc.c
*	amil_pnalloc = function prototype declaration amil_palloc.h
*	amil_cpymem = defined amil_string.h
*	amil_cpystrn = function defined amil_string.c
* 	return varriable type is amil_int_t. And amil_signal (AMIL_OK)
*/
amil_int_t amil_get_full_name(amil_pool_t *pool, amil_str_t *prefix, amil_str_t *name)
{
	size_t len;
	u_char *p, *n;
	amil_int_t rc;

	rc = amil_test_full_name(name);

	//check exception.
	if(rc == AMIL_OK)
	{
		return rc;
	}

	len = prefix -> len;

//Operating System type.
#if (AMIL_WIN32)

	if(rc == 2)
	{
		len = rc;
	}

#endif

	n = amil_pnalloc(pool, len + name -> len + 1);
	
	//check exception.
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


/*	amil_test_full_name is for test with full name from data.
*	amil_int_t = defined by 
*/
static amil_int_t amil_test_full_name(amil_str_t *name)
{
//Operating System type.
#if (AMIL_WIN32)	
	u_char c0, c1;

	c0 = name -> data[0];

	//if(len < 2 ) then return AMIL_DECLINED.
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

/*	amil_write_chain_to_temp_file is write chain to temp files.
*	ssize_t = (signed int) defined by <sys/types.h>
*	amil_temp_file_t = defined by amil_file.h
*	amil_chain_t = defined by amil_core.h
*	amil_log_error = function defined by amil_log.c
*	amil_log_error = 
* 	amil_create_temp_file = function defined by amil_file.c
*	amil_create_temp_file = function prototype declaration from amil_file.h
*	amil_write_chain_to_file = function defined by amil_file.c
*	amil_write_chain_to_file = function prototype declaration from amil_file.h
*	amil_thread_write_chain_to_file = 
*	amil_thread_write_chain_to_file = 
*/
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

/*	amil_create_temp_file is create a temp file functionality
*	amil_int_t = defined by amil_config.h
* 	amil_file_t = defined by amil_file.h
*	amil_path_t = defined by amil_file.h
*	amil_pool_t = defined by amil_core.h
*	amil_uint_t = defined by amil_config.h
*/
amil_int_t amil_create_temp_file(amil_file_t *file, amil_path_t *path, amil_pool_t *pool, amil_uint_t persistent, amil_uint_t clean, amil_uint_t access)
{
/*
*	uint32_t = defined by <sys/types.h>
*	amil_err_t = 
*	amil_pool_cleanup_t = defined amil_palloc.h
*	amil_pool_cleanup_file_t = defined amil_palloc.h
*/
	uint32_t n;
	amil_err_t err;
	amil_pool_cleanup_t *cln;
	amil_pool_cleanup_file_t *clnf;

	file -> name.len = path -> name.len + 1 + path -> len + 10;
	
	file -> name.data = amil_pnalloc(pool, file -> name.len + 1);
	//check exception.
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


ssize_t amil_thread_write_chain_to_file(amil_file_t *file, amil_chain_t *cl, off_t offset, amil_pool_t *pool)
{

}
amil_write_chain_to_file(amil_file_t *file, amil_chain_t *cl, off_t offset, amil_pool_t *pool)
{

}
