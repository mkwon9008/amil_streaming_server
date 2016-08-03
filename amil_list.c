

#include <amil_core.h>
#include <amil_config.h>

amil_list_t *amil_list_create(amil_pool_t *pool, amil_uint_t n, size_t size)
{
	amil_list_t 	*list;

	list = amil_palloc(pool, sizeof(amil_list_t));
	if(list == NULL)
	{
		return NULL;
	}

	if(amil_list_init(list, pool, n, size) != AMIL_OK)
	{
		return NULL;
	}

	return list;
}

void *amil_list_push(amil_list_t *l)
{
	void 				*elt;
	amil_list_part_t 	*last;

	last = l -> last;

	if(last -> nelts == l -> nalloc)
	{
		last = amil_palloc (l -> pool, sizeof(amil_list_part_t));
		if(last  == NULL)
		{
			return NULL;
		}

		last -> elts = amil_palloc(l -> pool, l -> nalloc * l -> size);
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