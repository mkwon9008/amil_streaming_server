
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

/*	struct amil_list_part_s
*	amil_uint_t = type defined by amil_config.h
*	amil_list_part_s = defined by amil_list.h
*/	
struct amil_list_part_s
{
	void 				*elts; //Generic pattern.
	amil_uint_t 		nelts;
	amil_list_part_t 	*next;
};

/*	struct amil_list_t
*	amil_list_part_t = defined by amil_list.h
*	size_t = defined by <sys/types.h>
*	amil_uint_t = type defined by amil_config.h
*	amil_pool_t = type defined by amil_core.h
*/
typedef struct 
{
	amil_list_part_t 	*last;
	amil_list_part_t 	part;
	size_t 				size;
	amil_uint_t 		nalloc;
	amil_pool_t 		*pool;
} amil_list_t;

//Preprocessing.
amil_list_t *amil_list_create(amil_pool_t *pool, amil_uint_t n, size_t size);

void *amil_list_push(amil_list_t *list);

/*	amil_list_init function are create list functinality.
*	amil_inline = defined by amil_config.h
*	amil_int_t = defined by amil_config.h
*	amil_pool_t = type defined by amil_core.h
*/
static amil_inline amil_int_t amil_list_init(amil_lsit_t *list, amil_pool_t *pool, amil_uint n, size_t size)
{
	//Memory allocate in list -> part.elts
	list -> part.elts = amil_palloc (pool, n * size);

	//check exeception.
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



#endif
/*end script*/