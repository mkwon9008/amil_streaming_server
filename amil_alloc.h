
/*	amil_alloc.h
*	This file is define macros and preprocessing functionality.
*	<RULE>
*	1. Function is created as concise as possible.
*	2. If you must write a custom function before amil + underbar.
*	3. Function names are separated by a custom type + content + relevant work.
	   If needed, it may be written the use of the method object between custom type and content.
*	4. The macro statement is written in capital letters.
*/	

#ifndef AMIL_ALLOC_HEADER_INCLUDE
#define AMIL_ALLOC_HEADER_INCLUDE

#include <amil_config.h>
#include <amil_core.h>

void *amil_alloc(size_t size, amil_log_t *log);
void *amil_calloc(size_t size, amil_log_t *log);

#define amil_free	free

#if (AMIL_HAVE_POSIX_MEMALIGN || AMIL_HAVE_MEMALIGN)

void *amil_memalign(size_t alignment, size_t size, amil_log_t *log);

#else

#define amil_memalign(alignment, size, log) amil_alloc(size, log)

#endif

extern amil_uint_t amil_pagesize;
extern amil_uint_t amil_pagesize_shift;
extern amil_uint_t amil_cacheline_size;

#endif 
/* script end*/