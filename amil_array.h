/*	amil_array.h
*	This file is definition macro and Preprocessing of Array functions
*	<RULE>
*	1. Function is created as concise as possible.
*	2. If you must write a custom function before amil + underbar.
*	3. Function names are separated by a custom type + content + relevant work.
	   If needed, it may be written the use of the method object between custom type and content.
*	4. The macro statement is written in capital letters.
*/	

#ifndef AMIL_ARRAY_HEADER_INCLUDE
#define AMIL_ARRAY_HEADER_INCLUDE

#include <amil_config.h>
#include <amil_core.h>

/*	defined amil_array_t
*	void *elts = Generic pattern	
*	amil_uint_t = defined at amil_config.h
*	amil_pool_t = defined at amil_core.h
*/
typedef struct {
	void        *elts;
	amil_uint_t   nelts;
	size_t       size;
	amil_uint_t   nalloc;
	amil_pool_t  *pool;
 } amil_array_t;
 
//Preprocessing functions statement.
amil_array_t *amil_array_create(amil_pool_t *p, amil_uint_t n, size_t size);
void amil_array_destroy(amil_array_t *a);
void *amil_array_push(amil_array_t *a);
void *amil_array_push_n(amil_array_t *a, amil_uint_t n);
 
/*	amil_array_init is receiving data from standard array.h
*	And set data to amil_array_t structure.
*	amil_palloc = function defined by amil_palloc.c
*	amil_palloc = function prototype declaration from amil_palloc.h 
*	amil_array_t = type defined by amil_array.h
*	amil_pool_t = type defined by amil_core.h
*	amil_uint_t = type defined by amil_core.h
*/
static amil_inline amil_int_t amil_array_init(amil_array_t *array, amil_pool_t *pool, amil_uint_t n, size_t size)
{
 
	array->nelts = 0;
	array->size = size;
	array->nalloc = n;
	array->pool = pool;
 
	array->elts = amil_palloc(pool, n * size);
	if (array->elts == NULL) {
		return AMIL_ERROR;
	}
 
	return AMIL_OK;
}
 
 
#endif
/*script end*/
