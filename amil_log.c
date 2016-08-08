
/*	amil_log.c
*	This file is written a function to process the error.
*	<RULE>
*	1. Function is created as concise as possible.
*	2. If you must write a custom function before amil + underbar.
*	3. Function names are separated by a custom type + content + relevant work.
	   If needed, it may be written the use of the method object between custom type and content.
*	4. The macro statement is written in capital letters.
*/	

#include <amil_config.h>
#include <amil_core.h>

//Static function preprocessing.
static char *amil_error_log(amil_conf_t *cf, amil_command_t *cmd, void *conf);
static char *amil_log_set_levels(amil_conf_t *cf, amil_log_t *log);
static void amil_log_insert(amil_log_t *log, amil_log_t *new_log);

//if amil is debug mode.
#if (AMIL_DEBUG)
//Static function preprocessing.
static void amil_log_memory_writer(amil_log_t *log, amil_uint_t level, u_char *buf, size_t len);
static void amil_log_memory_cleanup(void *data);


 /*struct here*/


#if (AMIL_HAVE_VARIADIC_MACROS)
void amil_log_error_core(amil_uint_t level, amil_log_t *log, amil_err_t err, const char *fmt, ...)

#else
void amil_log_error_core(amil_uint_t level, amil_log_t *log, amil_err_t err, const char *fmt, va_list args)
//end debug mode.
#endif


#if !(AMIL_HAVE_VARIADIC_MACROS)
/*	amil_log_error function is checking log level. and trasport that data to amil_log_error_core.
*	amil_cdecl = defined by amil_config.h
*	amil_uint_t = defined by amil_config.h
*	amil_log_t = defined by amil_log.h
*	amil_err_t = defined by amil_log.h
*/
void amil_cdecl amil_log_error(amil_uint_t level, amil_log_t *log, amil_err_t err, const char *fmt, ...)
{
	va_list args;
	if(log -> log_level >= level)
	{
		va_start(args, fmt);
		amil_log_error_core(level, log, err, fmt, args);
		va_end(args);
	}
}

/* 	amil_log_debug_core function is transport error data to amil_log_error_core
*	amil_cdecl = defined by amil_config.h
*	amil_log_t = defined by amil_log.h
*	amil_err_t = defined by amil_log.h
*/
void amil_cdecl amil_log_debug_core(amil_log_t *log, amil_err_t err, const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	amil_log_error_core(AMIL_LOG_DEBUG, log, err,fmt, args);
	va_end(args);
}
//Macro end !(AMIL_HAVE_VARIADIC_MACROS)
#endif

/*	amil_log_abort function is get from amil_vsnprintf. and return data to amil_log_error function.
*
*/
void amil_cdecl amil_log_abort (amil_err_t err, const char *fmt, ...)
{
	u_char *p;
	u_char errstr[AMIL_MAX_CONF_ERRSTR];
	va_list args;

	va_start(args, fmt);
	p = amil_vsnprintf(errstr, sizeof(errstr) - 1, fmt, args);

	amil_log_error(AMIL_LOG_ALERT, amil_cycle -> log, err, "%*s", p - errstr, errstr);
}

/* amil_log_set_log function is create log syntaxs on log.txt
*	amil_log_t = defined by amil_log.h
*	amil_str_t
*
*/
char *amil_log_set_log(amil_conf_t *cf, amil_log_t **head)
{
	amil_log_t 			*new_log;
	amil_str_t			*value, name;
	amil_syslog_peer_t 	*peer;

	if(*head != NULL && (*head) -> log_level == 0)
	{
		new_log = *head;
	}
	else
	{
		new_log = amil_pcalloc(cf -> pool, sizeof(amil_log_t));
		if(new_log == NULL)
		{
			return AMIL_CONF_ERROR;
		}

		if(*head == NULL)
		{
			*head = new_log;
		}
	}

	value = cf -> args ->elts; 

	if(amil_strcmp (value[1].data, "strerr") == 0
	{
		amil_str_null(&name);
		cf -> cycle -> log_use_stderr = 1;

		new_log -> file = amil_conf_open_file(cf ->cycle, &name);
		if(new_log->file == NULL) 
		{
			return AMIL_CONF_ERROR;
		}
		else if (amil_strncmp(value[1],data, "memory:", 7) == 0)
		{
#if (AMIL_DEBUG)
			size_t 					size, needed;
			amil_pool_cleanup_t 	*cln;
			amil_log_memory_buf_t 	*buf;

			value[1].len -= 7;
			value[1].data += 7;

			needed = sizeof("MEMLOG : " AMIL_LINEFEED) + cf -> conf_file -> file.name.len + AMIL_SIZE_T_LEN + AMIL_INT_T_LEN + AMIL_MAX_ERROR_STR;
			size = amil_parse_size(&value[1]);
			if(size == (size_t) AMIL_ERROR || size < needed)
			{
				amil_conf_log_error(AMIL_LOG_EMERG, cf, 0, "invalid buffer size \" %V\"", &value[1]);
				return AMIL_CONF_ERROR;
			}

			buf = amil_pcalloc(cf->pool, sizeof(amil_log_memory_buf_t));
			if(buf == NULL)
			{
				return AMIL_CONF_ERROR;
			}
			buf -> start = amil_pnalloc(cf->pool, size);
			if(buf -> start == NULL)
			{
				return AMIL_CONF_ERROR;
			}

			buf -> end = buf -> start + size;
			buf -> pos = amil_slprintf(buf->start, buf->end, "MEMLOG %uz %V:%ui%N", size, &cf -> conf_file -> file.name, cf -> conf_file -> line);
			amil_memset(buf -> pos, ' ', buf -> end - buf -> pos);

			cln = amil_pool_cleanup_add(cf -> pool, 0);

			if(cln == NULL)
			{
				return AMIL_CONF_ERROR;
			}

			cln -> data = new_log;
			cln -> handler = amil_log_memory_cleanup;

			new_log -> writer = amil_log_memory_writer;
			new_log -> wdata = buf;

#else
			amil_conf_log_error(AMIL_LOG_EMERG, cf, 0, "amil was built without debug support");
			return AMIL_CONF_ERROR;
#endif				
		}
		else if (amil_strncmp(value[1].data, "syslog", 7) == 0)
		{
			peer = amil_pcalloc(cf -> pool, sizeof(amil_syslog_peer_t));
			if(peer == NULL)
			{
				return AMIL_CONF_ERROR;
			}

			if(amil_syslog_process_conf(cf, peer) != AMIL_CONF_OK)
			{
				return AMIL_CONF_ERROR
			}

			new_log -> writer = amil_syslog_writer;
			new_log -> wdata = peer;
		}
		else
		{
			new_log -> file = amil_conf_open_file(cf -> cycle, &value[1]);
			if(new_log -> file == NULL)
			{
				return AMIL_CONF_ERROR;
			}
		}
		if (amil_log_set_levels(cf, new_log) != AMIL_CONF_OK)
		{
			return AMIL_CONF_ERROR;
		}

		if(*head != new_log)
		{
			amil_log_insert(*head, new_log);
		}
		return AMIL_CONF_OK;
	}

static void amil_log_insert(amil_log_t *log, amil_log_t *new_log)
{
	amil_log_t tmp;

	if(new_log -> log_level > log -> log_level)
	{
		tmp = *log;
		*log = *new_log;
		*new_log = tmp;

		log -> next = new_log;
		return;
	}

	while (log -> next)
	{
		if(new_log -> log_level > log -> next -> log_level)
		{
			new_log -> next = log -> next;
			log -> next = new_log;
			return;
		}

		log = log -> next;
	}

	log -> next = new_log;
}


#if (AMIL_DEBUG)
static void amil_log_memory_writer(amil_log_t *log, amil_uint_t level, u_char *buf)
{
	u_char		*p;
	size_t 		avail, written;
	amil_log_memory_buf_t *mem;

	mem = log -> wdata;

	if(mem == NULL)
	{
		return;
	}

	written = amil_atomic_fetch_add (&mem -> written, len);
	p = mem -> pos + written % (mem -> end - mem -> pos);
	avail = mem -> end - p;

	if(avail >= len)
	{
		amil_memcpy(p, buf, len);
	}
	else
	{
		amil_memcpy(p, buf, avail);
		amil_memcpy(mem -> pos, buf + avail, len - avail);
	}
}

static void amil_log_memory_cleanup(void *data)
{
	amil_log_t *log = data;
	amil_log_debug0(AMIL_LOG_DEBUG_CORE, log, 0, "destroy memory log buffer");
	log -> wdata = NULL;
}
#endif
/*script end*/