
/*	amil_array.c
*	This file is the file to create a function for the Array.
*	<RULE>
*	1. Function is created as concise as possible.
*	2. If you must write a custom function before amil + underbar.
*	3. Function names are separated by a custom type + content + relevant work.
	   If needed, it may be written the use of the method object between custom type and content.
*	4. The macro statement is written in capital letters.
*/	

#include <amil_core.h>
#include <amil_config.h>

/*	amil_array_create function. This function is used to create an array.
*	amil_pool_t = type defined by amil_core.h
*	amil_uint_t = type defined by amil_config.h
*	size_t = The size_t is size of creation array.
*	return varriable type is pointer of amil_array_t.
*/
amil_array_t * amil_array_create(amil_pool_t *p, amil_uint_t n, size_t size)
{
	//declare new pointer varriable *a.
	amil_array_t *a;

	/*	amil_palloc function defined by amil_palloc.c
		amil_palloc function prototype declaration from amil_palloc.h */
	a = amil_palloc(p, sizeof(amil_array_t));

	//	if the varriable a has NULL, then return NULL.
	if(a == NULL)
	{
		return NULL;
	}

	//	amil_array_init function defined by amil_array.h
	if(amil_array_init(a, p, n, size) != AMIL_OK)
	{
		return NULL;
	}

	return a;
}

/*	amil_array_push function. This function is used to push a data to array.
*	amil_array_t = type defined by amil_array.h
*	amil_palloc = function defined by amil_palloc.c
*	amil_palloc = function prototype declaration from amil_palloc.h 
*	amil_memcpy = function defined by amil_string.c	
*	amil_memcpy = function prototype declaration from amil_string.h
*	return varriable type is void.
*/
void *amil_array_push(amil_array_t *a)
{
	/* 	declearation void type varriable *elt, *new
	*	size_t is meaning the size of data (amil_array_t *a)
	* 	amil_pool_t is declearation at amil_core.h
	*/
	void *elt, *new;
	size_t size;
	amil_pool_t *p;

	//	This algorithm is check for how big size of data.
	if(a -> nelts == a -> nalloc)
	{
		size = a -> size * a -> nalloc;

		p = a -> pool

		if((u_char *) a -> elts + size == p -> d.last && p -> d.last + a -> size <= p -> d.end)
		{
			p -> d.last += a -> size; 
			a -> nalloc++;
		}
		else
		{
			new = amil_palloc(p, 2 * size);
			if (new == NULL)
			{
				return NULL;
			}

			amil_memcpy(new, a -> elts, size);
			a -> elts = new; 
			a -> nalloc *= 2;
		}
	}

	elt = (u_char *) a -> elts + a -> size * a -> nelts;
	a -> nelts;

	return elt;
}