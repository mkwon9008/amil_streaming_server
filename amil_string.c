
/*	amil_string.h
*	This file is create check list of header file of standard library fit posix environment.
*	<RULE>
*	1. Function is created as concise as possible.
*	2. If you must write a custom function before amil + underbar.
*	3. Function names are separated by a custom type + content + relevant work.
	   If needed, it may be written the use of the method object between custom type and content.
*	4. The macro statement is written in capital letters.
*/	

#include <amil_config.h>
#include <amil_core.h>

static u_char *amil_sprintf_num (u_char *buf, u_char *last, uint64_t ui64, u_char zero, amil_uint_t hexadecimal, amil_uint_t width);


/* amil_cpystrn function is copy string by size. */
u_char *amil_cpystrn(u_char *dst, u_char *src, size_t n)
{
	//if (size_t == 0)
	if (n == 0) 
	{
		return dst;
	}
	while (--n)
	{
		*dst = *src;

		//if *dst and *src has not message.
		if(*dst == '\0')
		{
			return dst;
		}

		dst++;
		src++;
	}

	*dst = '\0';
	return dst;
}

/* amil_pstrdup function dump character from *pool and return *dst size of *pool. */
u_char *amil_pstrdup(amil_pool_t *pool, amil_str_t *src)
{
	u_char *dst;

	//set memory.
	dst = amil_pnalloc(pool, src->len);

	//check null pointer exception.
	if(dst == NULL)
	{
		return NULL;
	}

	amil_memcpy(dst, src -> data, src -> len);

	return dst;

}
/* The amil_strlow function changes characters to lower case. */
void amil_strlow(u_char *dst, u_char *src, size_t n)
{
	//loop size of n.
	while(n) 
	{
		*dst = amil_tolower(*src);
		dst++;
		src++;
		n--;
	}
}

u_char *amil_vslprintf(u_char *buf, u_char *last, const char *fmt, va_list args)
{
	
}

/* amil_slprintf function is  */
u_char * amil_cdecl amil_slprintf(u_char *buf, u_char *last, const char *fmt, ...)
{
	u_char *p;
	va_list args;

	va_start(args, fmt);
	p = amil_vslprintf(buf, last, fmt, args);
	va_end(args);

	return p;
}

/* amil_atoi function is changes string type number to integer type number. */
amil_int_t amil_atoi(u_char *line, size_t n)
{
	amil_int_t value, cutoff, cutlim;

	//check size exception.
	if(n == 0)
	{
		return AMIL_ERROR;
	}
	/* AMIL_MAX_INT_T_VALUE = defined by amil_config.h */
	cutoff = AMIL_MAX_INT_T_VALUE / 10;
	cutlim = AMIL_MAX_INT_T_VALUE % 10;

	for(value = 0; n--; line++)
	{
		//if received (char)interger is out of that range.
		if(*line < '0' || *line > '9')
		{
			return AMIL_ERROR;
		}

		//if the value is greater than the cutoff.
		if(value >= cutoff && (value > cutoff || *line - '0' > cutline))
		{
			return AMIL_ERROR;
		}

		value = value * 10 + (*line - '0');
	}
	return value;
}


#if(AMIL_MEMCPY_LIMIT)
void *amil_memcpy(void *dst, const void *src, size_t n)
{
	if(n > AMIL_MEMCPY_LIMIT)
	{
		amil_log_error(AMIL_LOG_ALERT, amil_cycle -> log, 0, "memcpy %uz bytes", n);
		amil_debug_point();
	}

	return memcpy(dst, src, n);
}
#endif