

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



/*amil_pnalloc is twice.*/
void *amil_pnalloc(amil_pool_t *pool, size_t size)
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