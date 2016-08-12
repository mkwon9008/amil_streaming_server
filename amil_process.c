
/*	amil_process.c
*	This file is create check list of header file of standard library fit posix environment.
*	<RULE>
*	1. Function is created as concise as possible.
*	2. If you must write a custom function before amil + underbar.
*	3. Function names are separated by a custom type + content + relevant work.
	   If needed, it may be written the use of the method object between custom type and content.
*	4. The macro statement is written in capital letters.
*/	

#include <amil_config.h>
#include <amil_core.h>
//#include <amil_channel.h>
//#include <amil_event.h>

typedef struct 
{
	int signo;
	char *signame;
	char *name;
	void (*handler)(int signo);
} amil_signal_t;

int 	amil_argc;
char 	**amil_argv;
char 	**amil_os_argv;

static void amil_execute_proc(amil_cycle_t *cycle, void *data);
static void amil_experience_proc(amil_uint_t *argc, void *data);