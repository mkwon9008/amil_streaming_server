

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


void *amil_palloc(amil_pool_t *pool, size_t size)
{
#if !(AMIL_DEBUG_PALLOC)
	if(size <= pool -> max){
		return amil_palloc_small(pool, size, 1);
	}
#endif
	return amil_palloc_large(pool, size);
}

void *amil_pnalloc(amil_pool_t *pool, size_t size)
{
#if !(AMIL_DEBUG_PALLOC)
	if(size <= pool -> max){
		return amil_palloc_small(pool, size, 0);
	}
#endif
	return amil_palloc_large(pool, size);	
}

amil_pool_t * amil_create_pool(size_t size, aiml_log_t *log)
{
	amil_pool_t *p;

	p = amil_memalign(AMIL_POOL_ALIGNMENT, size, log);
	if(p == NULL)
	{
		return NULL;
	}

	p -> d.last =(u_char *)p + sizeof(amil_pool_t);
	p -> d.end = (u_char *)p + size;
	p -> d.next = NULL;
	p -> d.failed = 0;

	size = size - sizeof(amil_pool_t);
	p -> max = (size < AMIL_MAX_ALLOC_FROM_POOL) ? size : AMIL_MAX_ALLOC_FROM_POOL;

	p -> current = p;
	p -> chain = NULL;
	p -> large = NULL;
	p -> cleanup = NULL;
	p -> log = log;

	return p;
}


/*amil_pnalloc is twice.*/
/*void *amil_pnalloc(amil_pool_t *pool, size_t size)
{
	u_char *m;
	amil_pool_t *p;

	if(size <= pool -> max)
	{
		p = pool->current;


		do 
		{
			m = amil_align_ptr(p->d.last, AMIL_ALIGNMENT);

			if((size_t) (p->d.end - m) >= size)
			{
				p->d.last = m + size;

				return m;
			}

			p = p->d.next;

		} while (p);

		return amil_palloc_large(pool, size);
	}
	return amil_palloc_large(pool, size);
}*/


void amil_destroy_pool(amil_pool_t *pool)
{
	amil_pool_t *p, *n;
	amil_pool_large_t *l;
	amil_pool_cleanup_t *c;

	for(c = pool -> cleanup; c ; c = c -> next)
	{
		if(c -> handler)
		{
			amil_log_debug1(AMIL_LOG_DEBUG_ALLOC, pool -> log, 0, "run cleanup : %p", c);
			c -> handler (c -> data);
		}
	}

#if(AMIL_DEBUG)

	for(l = pool -> large; l; l = l -> next)
	{
		amil_log_debug1(AMIL_LOG_DEBUG_ALLOC, pool -> log, 0, "free : %p", l -> alloc);
	}

	for(p = pool, n = pool -> d.next; /*void*/ ; p = n, n = n -> d.next)
	{
		amil_log_debug2(AMIL_LOG_DEBUG_ALLOC, pool -> log, 0, "free : %p, unused : %uz", p, p -> d.end - p -> d.last);
		if(n == NULL)
		{
			break;
		}
	}

#endif

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

		if(n == NULL)
		{
			break;
		}
	}
}


amil_pool_cleanup_t * amil_pool_cleanup_add(amil_pool_t *p, size_t size)
{
	amil_pool_cleanup_t *c;

	c = amil_palloc(p, sizeof(amil_pool_cleanup_t));

	if(c == NULL)
	{
		return NULL;
	}

	if(size) 
	{
		c -> data = amil_palloc(p, size);
		if(c -> data == NULL)
		{
			return NULL;
		}
	}
	else
	{
		c -> data = NULL;
	}

	c -> handler = NULL;
	c -> next = p -> cleanup;
	p -> cleanup = c;

	amil_log_debug1(AMIL_LOG_DEBUG_ALLOC, p -> log, 0, "add cleanup : %p", c);

	return c;
}

void amil_pool_run_cleanup_file(amil_pool_t *p, amil_fd_t fd)
{
	amil_pool_cleanup_t				*c;
	amil_pool_run_cleanup_file_t 	*cf;

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

void amil_pool_cleanup_file(void *data)
{
	amil_pool_cleanup_file_t *c = data;

	amil_log_debug1(AMIL_LOG_DEBUG_ALLOC, c -> log, 0, "file cleanup : fd: %d", c -> fd);
	if(amil_close_file (c -> fd) == AMIL_FILE_ERROR)
	{
		amil_log_error(AMIL_LOG_ALERT, c -> log, amil_errno, amil_close_file_n " \"%s\" failed", c -> name);
	}
}

/*end script.*/