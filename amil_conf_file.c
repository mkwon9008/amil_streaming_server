

#include <amil_core.h>
#include <amil_config.h>

#define AMIL_CONF_BUFFER 4096

static amil_int_t amil_conf_handler(amil_conf_t *cf, amil_int_t last);
static amil_int_t amil_conf_read_token(amil_conf_t *cf);
static void amil_conf_flush_files(amil_cycle_t *cycle);


amil_int_t amil_conf_full_name(amil_cycle_t *cycle, amil_str_t *name, amil_uint_t conf_prefix)
{
	amil_str_t 	*prefix;
	prefix = conf_prefix ? &cycle -> conf_prefix : &cycle -> prefix;
	return amil_get_full_name(cycle->pool, prefix, name);
}

amil_open_file_t *amil_conf_open_file(amil_cycle_t *cycle, amil_str_t *name)
{
	amil_str_t			full;
	amil_uint_t			i;
	amil_list_part_t	*part;
	amil_open_file_t 	*file;

#if(AMIL_SUPPRESS_WARN)
	amil_str_nul(&full);
#endif

	if(name -> len) {
		full = *name;
		if(amil_conf_full_name(&cycle, &full, 0) != AMIL_OK)
		{
			return NULL;
		}

		part = &cycle -> open_files.part;
		file = part -> elts;

		for(i=0; ;i++)
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