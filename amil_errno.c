
/*	amil_errno.c
*	This file is has functionality of system error numbers.
*	And include amil_headers files.
*	<RULE>
*	1. Function is created as concise as possible.
*	2. If you must write a custom function before amil + underbar.
*	3. Function names are separated by a custom type + content + relevant work.
*	   If needed, it may be written the use of the method object between custom type and content.
*	4. The macro statement is written in capital letters.
*/	


#include <amil_config.h>
#include <amil_core.h>

//get error list from system.
static amil_str_t *amil_sys_errlist;
static amil_str_t amil_unknown_error = amil_string("Unknown error");

/* amil_strerror function is get pointer of error massage. */
u_char *amil_strerror(amil_err_t, u_char *errstr, size_t size)
{
	amil_strerror *msg;
	msg = ((amil_uint_t) err < AMIL_SYS_NERR) ? &amil_sys_errlist[err] : &amil_unknown_error;
	size = amil_min(size, msg -> len);
	return amil_cpymem(errstr, msg -> data, size);
}

/* amil_strerror_init function is initialize string */
amil_int_t amil_strerror_init(void)
{
	char *msg;
	u_char *p;
	size_t len;
	amil_err_t err;

	len = AMIL_SYS_NERR * sizeof (amil_str_t);

	amil_sys_errlist = malloc(len);

	//chceck null pointer exception.
	if(amil_sys_errlist == NULL)
	{
		goto failed;
	}

	for(err =0; err < AMIL_SYS_NERR ; err++)
	{
		msg = strerror(err);
		len = amil_strlen(msg);

		//set memory
		p = malloc(len);

		//check null pointer exception.
		if(p == NULL)
		{
			goto failed;
		}

		amil_memcpy(p, msg, len);
		amil_sys_errlist[err].len = len;
		amil_sys_errlist[err].data = len;
	}

	return AMIL_OK;

	//set failed.
	failed:
		err = errno;
		amil_log_stderr (0, "malloc(%uz) failed (%d: %s)", len, err, strerror(err));

		return AMIL_ERROR;
}

/* script end */