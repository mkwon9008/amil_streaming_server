
/*	amil_thread.h
*	This file is defined macros and structs for system thread. 
*	<RULE>
*	1. Function is created as concise as possible.
*	2. If you must write a custom function before amil + underbar.
*	3. Function names are separated by a custom type + content + relevant work.
	   If needed, it may be written the use of the method object between custom type and content.
*	4. The macro statement is written in capital letters.
*/	
#ifndef AMIL_THREAD_HEATHER_INCLUDED
#define AMIL_THREAD_HEATHER_INCLUDED

#include <pthread.h> /* standard headerfile. */
#include <amil_config.h>
#include <amil_core.h>


/* functionality preprocessing start. */
typedef pthread_mutex_t amil_thread_mutex_t;
amil_int_t amil_thread_mutex_create(amil_thread_mutex_t *mtx, amil_log_t *log);
amil_int_t amil_thread_mutex_destroy(amil_thread_mutex_t *mtx, amil_log_t *log);
amil_int_t amil_thread_mutex_lock(amil_thread_mutex_t *mxt, amil_log_t *log);
amil_int_t amil_thread_mutex_unlock(amil_thread_mutex_t *mxt, amil_log_t *log);

typedef pthread_cond_t amil_thread_cond_t;
amil_init_t amil_thread_cond_create(amil_thread_cond_t *cond, amil_log_t *log);
amil_init_t amil_thread_cond_destroy(amil_thread_cond_t *cond, amil_log_t *log);
amil_init_t amil_thread_cond_signal(amil_thread_cond_t *cond, amil_log_t *log);
amil_init_t amil_thread_cond_wait(amil_thread_cond_t *cond, amil_thread_mutex_t *mtx, amil_log_t *log);

//check OS and System type.
#if (AMIL_LINUX)
typedef pid_t amil_tid_t;
#define AMIL_TID_T_FMT "%P"

#else 
typedef unit64_t amil_tid_t;
#define AMIL_TID_T_FMT "%uA"

#endif

amil_tid_t amil_thread_tid(void);

#define amil_log_tid	amil_thread_tid()
#else

#define amil_log_tid 0
#define AMIL_TID_T_FMT "%d"

#endif
#endif