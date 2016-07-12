/*created by mkwon
* 	
*/

#ifndef AMIL_THREAD_HEATHER_INCLUDED
#define AMIL_THREAD_HEATHER_INCLUDED

#include <pthread.h> //std
#include <amil_config.h>
#include <amil_core.h>


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