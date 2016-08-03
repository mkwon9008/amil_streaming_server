

#include <amil_config.h>
#include <amil_core.h>

static u_char *amil_sprintf_num (u_char *buf, u_char *last, uint64_t ui64, u_char zero, amil_uint_t hexadecimal, amil_uint_t width);


u_char *amil_cpystrn(u_char *dst, u_char *src, size_t n)
{
	if (n == 0) 
	{
		return dst;
	}
	while (--n)
	{
		*dst = *src;

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

u_char *amil_pstrdup(amil_pool_t *pool, amil_str_t *src)
{
	u_char *dst;

	dst = amil_pnalloc(pool, src->len);
	if(dst == NULL)
	{
		return NULL;
	}


}

void amil_strlow(u_char *dst, u_char *src, size_t n)
{
	while(n) 
	{
		*dst = amil_tolower(*src);
		dst++;
		src++;
		n--;
	}
}

u_char * amil_cdecl amil_slprintf(u_char *buf, u_char *last, const char *fmt, ...)
{
	u_char *p;
	va_list args;

	va_start(args, fmt);
	p = amil_vslprintf(buf, last, fmt, args);
	va_end(args);

	return p;
}

amil_int_t amil_atoi(u_char *line, size_t n)
{
	amil_int_t value, cutoff, cutlim;

	if(n == 0)
	{
		return AMIL_ERROR;
	}

	cutoff = AMIL_MAX_INT_T_VALUE / 10;
	cutlim = AMIL_MAX_INT_T_VALUE % 10;

	for(value = 0; n--; line++)
	{
		if(*line < '0' || *line > '9')
		{
			return AMIL_ERROR;
		}

		if(value >= cutoff && (value > cutoff || *line - '0' > cutline))
		{
			return AMIL_ERROR;
		}

		value = value * 10 + (*line - '0');
	}
	return value;
}


void *amil_memcpy(void *dst, const void *src, size_t n)
{
	if(n > AMIL_MEMCPY_LIMIT)
	{
		amil_log_error(AMIL_LOG_ALERT, amil_cycle -> log, 0, "memcpy %uz bytes", n);

	}
}