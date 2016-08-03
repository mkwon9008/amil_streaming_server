


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

