

/*	amil_conf_file.c
*	This file is defined configure file function.
*	<RULE>
*	1. Function is created as concise as possible.
*	2. If you must write a custom function before amil + underbar.
*	3. Function names are separated by a custom type + content + relevant work.
	   If needed, it may be written the use of the method object between custom type and content.
*	4. The macro statement is written in capital letters.
*/	

#include <amil_core.h>
#include <amil_config.h>

#define AMIL_CONF_BUFFER 4096

//Preprocessing function.
static amil_int_t amil_conf_handler(amil_conf_t *cf, amil_int_t last);
static amil_int_t amil_conf_read_token(amil_conf_t *cf);
static void amil_conf_flush_files(amil_cycle_t *cycle);

/*	amil_conf_full_name function is check for conf_prefix and return result of amil_get_full_name.
*	amil_int_t = defined by amil_config.h
*	amil_cycle_t = defined by amil_core.h
*	amil_str_t = type defined by amil_string.h
*	amil_uint_t type defined by amil_config.h
*	return varriable type is amil_int_t. The result of amil_get_full_name function.
*/
amil_int_t amil_conf_full_name(amil_cycle_t *cycle, amil_str_t *name, amil_uint_t conf_prefix)
{
	//decleared new varriable *prefix of amil_str_t type.
	amil_str_t 	*prefix;

	/*	
	* The question mark(?) is as following as..
	*if(conf_prefix)
	*{
	*	prefix = &cycle -> conf_prefix;
	*}
	*else
	*{
	*	prefix = &cycle -> prefix;
	*}
	*/
	prefix = conf_prefix ? &cycle -> conf_prefix : &cycle -> prefix;
	return amil_get_full_name(cycle->pool, prefix, name);
}

/*	amil_conf_open_file function is used to read files from other file within amil.
*	amil_open_file_t = defined by amil_core.h
*	amil_cycle_t = defined by amil_core.h
*	amil_str_t = type defined by amil_string.h
*	amil_list_part_t = type defined by amil_list.h
*	amil_uint_t = type defined by amil_config.h
*	amil_str_null = function defined by amil_string.h
*	amil_conf_full_name = function defined by amil_conf_file.c
*	amil_strcmp = type defined by amil_string.c
*	amil_list_push = function defined by amil_array.c
*	return varriable type is amil_open_file_t (file)
*/
amil_open_file_t *amil_conf_open_file(amil_cycle_t *cycle, amil_str_t *name)
{
	//Decleared varriables.
	amil_str_t			full;
	amil_uint_t			i;
	amil_list_part_t	*part;
	amil_open_file_t 	*file;

//Preprocessing in amil_conf_open_file macro.
#if(AMIL_SUPPRESS_WARN)
	amil_str_null(&full);
#endif
	//statement start.
	if(name -> len) {
		full = *name;
		//check exception.
		if(amil_conf_full_name(&cycle, &full, 0) != AMIL_OK)
		{
			return NULL;
		}

		part = &cycle -> open_files.part;
		file = part -> elts;

		// read file until end of file.
		for(i=0; /*void*/ ;i++)
		{
			if(i >= part -> nelts) 
			{
				if(part->next == NULL)
				{
					break;
				}
				part = part -> next;
				file = part -> elts;
				i = 0;
			}
			if(full.len != file[i].name.len)
			{
				continue;
			}
			if(amil_strcmp(full.data, file[i].name.data) == 0)
			{
				return &file[i];
			}
		}
	}

	file = amil_list_push(&cycle -> open_files);
	//check exeption.
	if (file == NULL)
	{
		return NULL;
	}

	if(name -> len)
	{
		file -> fd = AMIL_INVALID_FILE;
		file -> name = full;
	}
	else 
	{
		file -> fd = amil_stderr;
		file -> name = *name;
	}

	file -> flush = NULL;
	file -> data = NULL;

	return file;
}