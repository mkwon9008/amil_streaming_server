
/*	amil_core.h
*	This file is definition macro and Preprocessing. 
*	And include amil_headers files.
*	<RULE>
*	1. Function is created as concise as possible.
*	2. If you must write a custom function before amil + underbar.
*	3. Function names are separated by a custom type + content + relevant work.
*	   If needed, it may be written the use of the method object between custom type and content.
*	4. The macro statement is written in capital letters.
*/	

#ifndef AMIL_CORE_HEATHER_INCLUDED
#define AMIL_CORE_HEATHER_INCLUDED

#include <amil_config.h> 

typedef struct amil_conf_s			amil_conf_t;
typedef struct amil_module_s 		amil_module_t;
typedef struct amil_chain_s			amil_chain_t;
typedef struct amil_cycle_s			amil_cycle_t;
typedef struct amil_log_s			amil_log_t;
typedef struct amil_pool_s			amil_pool_t;
typedef struct amil_open_file_s		amil_open_file_t;
typedef struct amil_connection_s	amil_connection_t;
typedef struct amli_file_s			amli_file_t;
typedef struct amil_event_s			amil_event_t;
typedef struct amil_event_aio_s 	amil_event_aio_t;
typedef struct amil_command_s		amil_command_t;

#if(AMIL_THREADS)
typedef struct amil_thread_task_s amil_thread_task_t;
// input struct & include header.

#endif

typedef void (*amil_event_handler_pt)(amil_event_t *ev);
typedef void (*amil_connection_handler_pt)(amil_connection_t *c);

#define AMIL_OK		 0
#define AMIL_ERROR	-1
#define AMIL_AGAIN  -2
#define AMIL_BUSY 	-3
#define AMIL_DONE	-4
#define AMIL_DECLINED -5
#define AMIL_ABORT	-6


//amil_headers include start.

#include <amil_alloc.h>
#include <amil_array.h>
#include <amil_atomic.h>
#include <amil_file.h>
#include <amil_syslog.h>
#include <amil_conf_file.h>
#include <amil_thread.h>
#include <amil_string.h>
#include <amil_log.h>
#include <amil_list.h>
#include <amil_palloc.h>


void amil_cpuinfo(void);

#if (AMIL_HAVE_OPENAT)
#define AMIL_DISABLE_SYMLINKS_OFF 0
#define AMIL_DISABLE_SYMLINKS_ON 1
#define AMIL_DISABLE_SYMLINKS_NOTOWNER 2
#endif

#endif

/*script end*/

