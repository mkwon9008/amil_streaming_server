
/*	amil_log.h
*	This file are definition macro and struct and Preprocessing about list functionality.
*	<RULE>
*	1. Function is created as concise as possible.
*	2. If you must write a custom function before amil + underbar.
*	3. Function names are separated by a custom type + content + relevant work.
	   If needed, it may be written the use of the method object between custom type and content.
*	4. The macro statement is written in capital letters.
*/	

#ifndef AMIL_LOG_HEADER_INCLUDE
#define AMIL_LOG_HEADER_INCLUDE

#define AMIL_LOG_STDERR 0
#define AMIL_LOG_EMERG 1
#define AMIL_LOG_ALERT 2
#define AMIL_LOG_CRIT 3
#define AMIL_LOG_ERR 4
#define AMIL_LOG_WARN 5
#define AMIL_LOG_NOTICE 6
#define AMIL_LOG_INFO 7
#define AMIL_LOG_DEBUG 8


#define amil_log_debug1(level, log, err, fmt, arg1) amil_log_debug(level, log, err, fmt, arg1)
#define amil_log_debug2(level, log, err, fmt, arg1, arg2) amil_log_debug(level, log, err, fmt, arg1, arg2)
#define amil_log_debug3(level, log, err, fmt, arg1, arg2, arg3) amil_log_debug(level, log, err, fmt, arg1, arg2, arg3)
#define amil_log_debug4(level, log, err, fmt, arg1, arg2, arg3, arg4) amil_log_debug(level, log, err, fmt, arg1, arg2, arg3, arg4)
#define amil_log_debug5(level, log, err, fmt, arg1, arg2, arg3, arg4, arg5) amil_log_debug(level, log, err, fmt, arg1, arg2, arg3, arg4, arg5)
#define amil_log_debug6(level, log, err, fmt, arg1, arg2, arg3, arg4, arg5, arg6) amil_log_debug(level, log, err, fmt, arg1, arg2, arg3, arg4, arg5, arg6)
#define amil_log_debug7(level, log, err, fmt, arg1, arg2, arg3, arg4, arg5, arg6, arg7) amil_log_debug(level, log, err, fmt, arg1, arg2, arg3, arg4, arg5, arg6, arg7)
#define amil_log_debug8(level, log, err, fmt, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) amil_log_debug(level, log, err, fmt, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)

#endif

#else

#define amil_log_debug0(level, log, err, fmt)
#define amil_log_debug1(level, log, err, fmt, arg1)
#define amil_log_debug2(level, log, err, fmt, arg1, arg2)
#define amil_log_debug3(level, log, err, fmt, arg1, arg2, arg3)
#define amil_log_debug4(level, log, err, fmt, arg1, arg2, arg3, arg4)
#define amil_log_debug5(level, log, err, fmt, arg1, arg2, arg3, arg4, arg5)
#define amil_log_debug6(level, log, err, fmt, arg1, arg2, arg3, arg4, arg5, arg6)
#define amil_log_debug7(level, log, err, fmt, arg1, arg2, arg3, arg4, arg5, arg6, arg7)

#endif

/* Preprocessing HERE */

static amil_inline void amil_write_stderr(char *text)
{
	(void) amil_write_fd(amil_stderr, text, amil_strlen(text));
}

static amil_inline void amil_write_stdout(char *text)
{
	(void) amil_write_fd(amil_stdout, text, amil_strlen(text));
}

extern amil_module_t amil_errlog_module;
extern amil_uint_t amil_use_stderr;

#endif