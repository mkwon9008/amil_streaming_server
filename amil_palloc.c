

/*	amil_palloc.c
*	This file are definition memory allocation functionality.
*	<RULE>
*	1. Function is created as concise as possible.
*	2. If you must write a custom function before amil + underbar.
*	3. Function names are separated by a custom type + content + relevant work.
	   If needed, it may be written the use of the method object between custom type and content.
*	4. The macro statement is written in capital letters.
*/	


#include <amil_config.h>
#include <amil_core.h>

static aiml_inline void *amil_palloc_small(amil_pool_t *pool, size_t size, amil_uint_t align);
static void *amil_palloc_block(amil_pool_t *pool, size_t size);
static void *amil_palloc_large(amil_pool_t *pool, size_t size);

/*	amil_palloc function is check the max size of pool and size.
*	amil_pool_t = defined by amil_core.h
*	size_t = defined by <sys/types.h>
*/
void *amil_palloc(amil_pool_t *pool, size_t size)
{
#if !(AMIL_DEBUG_PALLOC)
	//check size.
	if(size <= pool -> max){
		return amil_palloc_small(pool, size, 1);
	}
#endif
	return amil_palloc_large(pool, size);
}

/*	amil_pnalloc function is check the max size of amil_pool_t and size.
*	amil_pool_t = defined by amil_core.h
*	size_t = defined by <sys/types.h>
*/
void *amil_pnalloc(amil_pool_t *pool, size_t size)
{
#if !(AMIL_DEBUG_PALLOC)

	//check size
	if(size <= pool -> max){
		return amil_palloc_small(pool, size, 0);
	}
#endif
	return amil_palloc_large(pool, size);	
}

/*	amil_create_pool function has create new pool functionality.
*/
amil_pool_t * amil_create_pool(size_t size, aiml_log_t *log)
{
	amil_pool_t *p;

	p = amil_memalign(AMIL_POOL_ALIGNMENT, size, log); //defined by amil_alloc.c
	//check Null pointer exception.
	if(p == NULL)
	{
		return NULL;
	}

	p -> d.last =(u_char *)p + sizeof(amil_pool_t);
	p -> d.end = (u_char *)p + size;
	p -> d.next = NULL;
	p -> d.failed = 0;

	size = size - sizeof(amil_pool_t);
	/*	The question mark operator syntax.
	if(size < AMIL_MAXALLOC_FROM_POOL)
	{
		max = size;
	}
	else
	{
		max = AMIL_MAX_ALLOC_FROM_POOL;
	}
	*/
	p -> max = (size < AMIL_MAX_ALLOC_FROM_POOL) ? size : AMIL_MAX_ALLOC_FROM_POOL;

	//set pool.
	p -> current = p;
	p -> chain = NULL;
	p -> large = NULL;
	p -> cleanup = NULL;
	p -> log = log;

	return p;
}

/*	amil_destroy_pool function has delete pool functinality.
*/	

void amil_destroy_pool(amil_pool_t *pool)
{
	amil_pool_t *p, *n;
	amil_pool_large_t *l;
	amil_pool_cleanup_t *c;

	//loop cleanup data.
	for(c = pool -> cleanup; c ; c = c -> next)
	{
		if(c -> handler)
		{
			amil_log_debug1(AMIL_LOG_DEBUG_ALLOC, pool -> log, 0, "run cleanup : %p", c);
			c -> handler (c -> data);
		}
	}

#if(AMIL_DEBUG)
	//loop memory free.
	for(l = pool -> large; l; l = l -> next)
	{
		amil_log_debug1(AMIL_LOG_DEBUG_ALLOC, pool -> log, 0, "free : %p", l -> alloc);
	}

	for(p = pool, n = pool -> d.next; /*void*/ ; p = n, n = n -> d.next)
	{
		amil_log_debug2(AMIL_LOG_DEBUG_ALLOC, pool -> log, 0, "free : %p, unused : %uz", p, p -> d.end - p -> d.last);
		//check Null pointer exception.
		if(n == NULL)
		{
			break;
		}
	}

#endif

	//loop memory free.
	for(l = pool -> large; l ; l = l -> next)	
	{
		if(l -> alloc)
		{
			amil_free(l -> alloc);
		}
	}

	for(p = pool, n = pool -> d.next; /*void*/ ; p = n, n = n -> d.next)
	{
		amil_free(p);
		//check Null pointer exception.
		if(n == NULL)
		{
			break;
		}
	}
}

/*	amil_pool_cleanup_add function has create amil_pool_cleanup_t functionality. 
*/
amil_pool_cleanup_t * amil_pool_cleanup_add(amil_pool_t *p, size_t size)
{
	amil_pool_cleanup_t *c;

	c = amil_palloc(p, sizeof(amil_pool_cleanup_t));

	//check null pointer exception.
	if(c == NULL)
	{
		return NULL;
	}
	//memory allocation.
	if(size) 
	{
		c -> data = amil_palloc(p, size);
		//check null pointer exception.
		if(c -> data == NULL)
		{
			return NULL;
		}
	}
	//set c -> data = null;
	else
	{
		c -> data = NULL;
	}

	//set elements.
	c -> handler = NULL;
	c -> next = p -> cleanup;
	p -> cleanup = c;

	amil_log_debug1(AMIL_LOG_DEBUG_ALLOC, p -> log, 0, "add cleanup : %p", c);

	return c;
}
/*	amil_pool_run_cleanup_file function has run the cleanup files functionality.
*/
void amil_pool_run_cleanup_file(amil_pool_t *p, amil_fd_t fd)
{
	amil_pool_cleanup_t				*c;
	amil_pool_run_cleanup_file_t 	*cf;

	//loop set c, c -> next
	for(c = p-> cleanup; c; c = c -> next)
	{
		if(c -> handler == amil_pool_run_cleanup_file)
		{
			cf = c -> data;

			if(cf -> fd == fd)
			{
				c -> handler(cf); 
				c -> handler = NULL;
				return;
			}
		}
	}
}
/*	amil_pool_cleanup_file function has copy *data to amil_pool_cleanup_file_t and cleanup and close.
*/
void amil_pool_cleanup_file(void *data)
{
	amil_pool_cleanup_file_t *c = data;

	amil_log_debug1(AMIL_LOG_DEBUG_ALLOC, c -> log, 0, "file cleanup : fd: %d", c -> fd);
	//check file error exception.
	if(amil_close_file (c -> fd) == AMIL_FILE_ERROR)
	{
		amil_log_error(AMIL_LOG_ALERT, c -> log, amil_errno, amil_close_file_n " \"%s\" failed", c -> name);
	}
}


/*	amil_palloc_small function has set allocation amil_palloc_block.
*	amil_align_ptr = defined by amil_config.h
*/
static amil_inline void * amil_palloc_small(amil_pool_t *pool, size_t size, amil_uint_t align)
{
	u_char *m;
	amil_pool_t *p;

	p = pool -> current;

	do
	{
		m = p -> d.last;

		if(align)
		{
			m = amil_align_ptr(m, AMIL_ALIGNMENT);
		}

		if((size_t) (p -> d.end - m) >= size)
		{
			p -> d.last = m + size;
			return m;
		}

		p = p -> d.next;
	} while (p);

	return amil_palloc_block(pool, size)
}

/*	amil_palloc_large function has 
*
*/
static void *amil_palloc_large (amil_pool_t *pool, size_t size)
{
	void *p;
	amil_uint_t n;
	amil_pool_large_t *large;

	p = amil_alloc(size, pool -> log); //defined by amil_alloc.c
	//check null pointer exception.
	if(p == NULL)
	{
		return NULL;
	}

	n = 0;

	//loop 
	for (large = pool -> large; large ; large = large -> next)
	{
		if(large -> alloc == NULL)
		{
			large -> alloc = p;
			return p;
		}

		if(n++ > 3)
		{
			break;
		}
	}

	large = amil_palloc_small(pool, sizeof(amil_pool_large_t), 1);
	//check null pointer exception.
	if(large == NULL)
	{
		amil_free(p);
		return NULL;
	}

	large -> alloc = p;
	large -> next = pool -> large;
	pool -> large = large;

	return p;
}
/*	amil_palloc_block function has set allocation memory functionality.
*/
static void *amil_palloc_block(amil_pool_t *pool, size_t size)
{
	u_char *m;
	size_t psize;
	amil_pool_t *p, *new;

	psize = (size_t) (pool -> d.end - (u_char *) pool);

	m = amil_memalign(AMIL_POOL_ALIGNMENT, psize, pool -> log); //defined by amil_alloc.c

	//check null pointer exception.
	if(m == NULL)
	{
		return NULL;
	}

	//set new.
	new = (amil_pool_t *) m;

	new -> d.end = m + psize;
	new -> d.next = NULL;
	new -> d.failed = 0;

	m += sizeof(amil_pool_data_t);
	m = amil_align_ptr(m, AMIL_ALIGNMENT);
	new -> d.last = m + size;

	for(p = pool -> current; p -> d.next; p = p -> d.next)
	{
		if(p -> d.failed ++ > 4)
		{
			pool -> current = p -> d.next;
		}
	}

	p -> d.next = new;

	return m;
}
