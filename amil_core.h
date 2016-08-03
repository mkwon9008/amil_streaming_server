/*created by mkwon*/

#ifndef AMIL_CORE_HEATHER_INCLUDED
#define AMIL_CORE_HEATHER_INCLUDED

#include <amil_config.h> 

typedef struct amil_conf_s			amil_conf_t;
typedef struct amil_cycle_s			amil_cycle_t;
typedef struct amil_log_s			amil_log_t;
typedef struct amil_pool_s			amil_pool_t;
typedef struct amil_open_file_s		amil_open_file_t;
typedef struct amil_connection_s	amil_connection_t;
typedef struct amli_file_s			amli_file_t;
typedef struct amil_event_s			amil_event_t;
typedef struct amil_command_s		amil_command_t;

#if(AMIL_THREADS)
typedef struct amil_thread_task_s amil_thread_task_t;
// input struct & include header.

#endif

typedef void (*amil_event_handler_pt)(amil_event_t *ev);
typedef void (*amil_connection_handler_pt)(amil_connection_t *c);

#define AMIL_OK		 0
#define AMIL_ERROR	-1
#define AMIL_ABORT	-2
#define AMIL_DONE	-3

//include start.

#include <amil_conf_file.h>
#include <amil_thread.h>
#include <amil_string.h>
#include <amil_log.h>
#include <amil_list.h>
#include <amil_palloc.h>


