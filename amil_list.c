

/*	amil_list.c
*	This file is the file to create a function for the list.
*	<RULE>
*	1. Function is created as concise as possible.
*	2. If you must write a custom function before amil + underbar.
*	3. Function names are separated by a custom type + content + relevant work.
	   If needed, it may be written the use of the method object between custom type and content.
*	4. The macro statement is written in capital letters.
*/	

#include <amil_core.h>
#include <amil_config.h>

/*	amil_list_create are creating a list functionality.
*	amil_list_t = defined by amil_list.h
*	amil_pool_t = type defined by amil_core.h
*	amil_uint_t = type defined by amil_config.h
*	size_t = defined by <sys/types.h>
*	amil_palloc = function defined by amil_palloc.c
*	amil_palloc = function prototype declaration from amil_palloc.h 
*	amil_list_init = function defined by amil_list.h
*/
amil_list_t *amil_list_create(amil_pool_t *pool, amil_uint_t n, size_t size)
{
	//declaration new list.
	amil_list_t 	*list;

	//create new list.
	list = amil_palloc(pool, sizeof(amil_list_t));

	//check exception.
	if(list == NULL)
	{
		return NULL;
	}

	//check exception.
	if(amil_list_init(list, pool, n, size) != AMIL_OK)
	{
		return NULL;
	}

	return list;
}


/*	amil_list_push is create last elements. then push the list.
*	amil_list_t = defined by amil_list.h
*	amil_list_part_t = defined by amil_list.h
*	amil_palloc = function defined by amil_palloc.c
*	amil_palloc = function prototype declaration from amil_palloc.h 
*/
void *amil_list_push(amil_list_t *l)
{
	void 				*elt;
	amil_list_part_t 	*last;

	last = l -> last;

	//check exception.
	if(last -> nelts == l -> nalloc)
	{
		//creat last.
		last = amil_palloc (l -> pool, sizeof(amil_list_part_t));
		//check exception.
		if(last  == NULL)
		{
			return NULL;
		}

		//Allocated memory at last -> elts.
		last -> elts = amil_palloc(l -> pool, l -> nalloc * l -> size);
		//check exception.
		if (last -> elts == NULL )
		{
			return NULL;
		}

		last -> nelts = 0;
		last -> next = NULL;

		l -> last -> next = last;
		l -> last = last;
	}

	elt = (char *) last -> elts + l -> size * last -> nelts;
	last -> nelts++;

	return elt;
}

/*script end*/