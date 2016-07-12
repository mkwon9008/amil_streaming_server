/*created by mkwon*/

#ifndef AMIL_CORE_HEATHER_INCLUDED
#define AMIL_CORE_HEATHER_INCLUDED

#include <amil_config.h> //header needed.

typedef struct amil_conf_s			amil_conf_t;
typedef struct amil_open_file_s		amil_open_file_t;
typedef struct amil_connection_s	amil_connection_t;
typedef struct amli_file_s			amli_file_t;
typedef struct amil_event_s			amil_event_t;

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

#include <amil_thread.h>

