
/*	amil_alloc.c
*	This file has allocation memory functionality.
*	<RULE>
*	1. Function is created as concise as possible.
*	2. If you must write a custom function before amil + underbar.
*	3. Function names are separated by a custom type + content + relevant work.
	   If needed, it may be written the use of the method object between custom type and content.
*	4. The macro statement is written in capital letters.
*/	

#include <amil_config.h>
#include <amil_core.h>

amil_uint_t amil_pagesize;
amil_uint_t amil_pagesize_shift;
amil_uint_t amil_cacheline_size;

/*	amil_alloc function is allocation memory to varriable or some arguments.
*/
void *amil_alloc(size_t size, amil_log_t *log)
{
	void *p;

	p = malloc(size);
	//check Null pointer exception. (memory allocated failed)
	if(p == NULL)
	{
		amil_log_error(AMIL_LOG_EMERG, log, amil_errno, "malloc(%uz) failed", size);
	}

	//write debug log.
	amil_log_debug2(AMIL_LOG_DEBUG_ALLOC, log, 0, "malloc : %p:%uz", p, size);

	return p;
}

/*	amil_calloc function is allocation memory to count of varriable or some arguments.
*/
void *amil_calloc(size_t size, amil_log_t *log)
{
	void *p;

	p = amil_alloc(size, log);

	if(p)
	{
		amil_memzero(p, size);
	}

	return p;
}

#if(AMIL_HAVE_POSIX_MEMALIGN)

/*	amil_memalign(AMIL_HAVE_POSIX_MEMALIGN)
*	posix_memalign = defined by <stdlib.h>
*/
void *amil_memalign(size_t alignment, size_t size, amil_log_t *log)
{
	void *p;
	int err;

	err = posix_memalign(&p, alignment, size);

	if(err)
	{
		amil_log_error(AMIL_LOG_EMERG, log, err, "posix_memalign(%uz, %uz) failed", alignment, size);
		p = NULL;
	}

	amil_log_debug3(AMIL_LOG_DEBUG_ALLOC, log, 0, "posix_memalign : %p:%uz @%uz", p, size, alignment);
	return p;
}


#elif (AMIL_HAVE_MEMALIGN)
/*	amil_memalign(AMIL_HAVE_MEMALIGN)
*	memalign = defined by <stdio.h> :: memalign(size_t size, size_t boundary)
*/
void *amil_memalign(size_t alignment, size_t size, amil_log_t *log)
{
	void *p;

	p = memalign(alignment, size);

	if(p == NULL)
	{
		amil_log_error(AMIL_LOG_EMERG, log, amil_errno, "memalign(%uz, %uz) failed", alignment, size);
	}

	amil_log_debug3(AMIL_LOG_DEBUG_ALLOC, log, 0, "memalign : %p:%uz @%uz", p, size, alignment);

	return p;
}

#endif

/* script end */