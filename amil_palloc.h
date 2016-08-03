

#ifndef AMIL_PALLOC_HAEDER_INCLUDE
#define AMIL_PALLOC_HAEDER_INCLUDE

#include <amil_config.h>
#include <amil_core.h>



struct amil_pool_s
{
	amil_pool_data_t 		d;
	size_t 					max;
	amil_pool_t 			*current;
	amil_chain_large_t 		*large;
	amil_pool_cleanup_t 	*cleanup;
	amil_log_t 				*log;
};

typedef struct
{
	amil_fd_t 	fd;
	amil_log_t 	*log;
	u_char 		*name;
}amil_pool_cleanup_file_t;



/*end script.*/