
/*	amil_list.h
*	This file are definition macro and struct and Preprocessing about list functionality.
*	<RULE>
*	1. Function is created as concise as possible.
*	2. If you must write a custom function before amil + underbar.
*	3. Function names are separated by a custom type + content + relevant work.
	   If needed, it may be written the use of the method object between custom type and content.
*	4. The macro statement is written in capital letters.
*/	

#ifndef AMIL_LIST_HEADER_INCLUDE
#define AMIL_LIST_HEADER_INCLUDE

#include <amil_config.h>
#include <amil_core.h>

typedef struct amil_list_part_s 	amil_list_part_t;

struct amil_list_part_s
{
	void 				*elts;
	amil_uint_t 		nelts;
	amil_list_part_t 	*next;
};


typedef struct 
{
	amil_list_part_t 	*last;
	amil_list_part_t 	part;
	size_t 				size;
	amil_uint_t 		nalloc;
	amil_pool_t 		*pool;
} amil_list_t;

amil_list_t *amil_list_create(amil_pool_t *pool, amil_uint_t n, size_t size);

static amil_inline amil_int_t amil_list_init(amil_lsit_t *list, amil_pool_t *pool, amil_uint n, size_t size)
{
	list -> part.elts = amil_palloc (pool, n * size);
	if(list -> part.elts == NULL ) 
	{
		return AMIL_ERROR;
	}

	list -> part.nelts = 0; 
	list -> part.next = NULL;
	list -> last = &list -> part; 
	list -> size = size;
	list -> nalloc = n;
	list -> pool = pool;

	return AMIL_OK;
}

void *amil_list_push(amil_list_t *list);

#endif
/*end script*/