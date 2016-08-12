
/*	amil_palloc.h
*	This file are definition struct for allocation functionality.
*	<RULE>
*	1. Function is created as concise as possible.
*	2. If you must write a custom function before amil + underbar.
*	3. Function names are separated by a custom type + content + relevant work.
	   If needed, it may be written the use of the method object between custom type and content.
*	4. The macro statement is written in capital letters.
*/	

#ifndef AMIL_PALLOC_HAEDER_INCLUDE
#define AMIL_PALLOC_HAEDER_INCLUDE

#include <amil_config.h>
#include <amil_core.h>


#define AMIL_MAX_ALLOC_FROM_POOL (amil_pagesize - 1)

typedef struct 
{
	u_char *last;
	u_char *end;
	amil_pool_t *next;
	amil_uint_t failed;
} amil_pool_data_t;


/*	struct amil_pool_s 
*	amil_pool_data_t = defined by aiml_palloc.h
*	amil_pool_t = defined by amil_core.h
*	amil_chain_large_t = defined by 
*/
struct amil_pool_s
{
	amil_pool_data_t 		d;
	size_t 					max;
	amil_pool_t 			*current;
	amil_chain_t 			*chain;
	amil_pool_large_t		*large;
	amil_pool_cleanup_t 	*cleanup;
	amil_log_t 				*log;
};

/* struct amil_pool_cleanup_file_t */
typedef struct
{
	amil_fd_t 	fd;
	amil_log_t 	*log;
	u_char 		*name;
}amil_pool_cleanup_file_t;

/* function preprocessing start. */
void *amil_palloc(amil_pool_t *pool, size_t size);
void *amil_pnalloc(amil_pool_t *pool, size_t size);

typedef struct amil_pool_cleanup_s amil_pool_cleanup_t;


/*end script.*/