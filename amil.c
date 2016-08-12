

/*	amil.c
*	This file is has main function in this project.
*	<RULE>
*	1. Function is created as concise as possible.
*	2. If you must write a custom function before amil + underbar.
*	3. Function names are separated by a custom type + content + relevant work.
	   If needed, it may be written the use of the method object between custom type and content.
*	4. The macro statement is written in capital letters.
*/	

#include <amil_config.h>
#include <amil_core.h>
#include <amil.h>

/* functionality preprocessing start. */
static amil_int_t amil_add_inherited_sockets(amil_cycle_t *cycle);
static amil_int_t amil_get_options(int argc, char *const *argv);
static amil_int_t amil_process_option(amil_cycle_t *cycle);
static amil_int_t amil_save_argv(amil_cycle_t *cycle, int argc, char *const *argv);

static void *amil_core_module_create_conf(amil_cycle_t *cycle);
static char *amil_core_module_init_conf(amil_cycle_t *cycle, void *conf);
static char *amil_set_user(amil_conf_t *cf, amil_command_t *cmd, void *conf);
static char *amil_set_env(amil_conf_t *cf, amil_command_t *cmd, void *conf);
static char *amil_set_priority(amil_conf_t *cf, amil_command_t *cmd, void *conf);
static char *amil_set_cpu_affinity(amil_conf_t *cf, amil_command_t *cmd, void *conf);
static char *amil_set_worker_processes(amil_conf_t *cf, amil_command_t *cmd, void *conf;)

/* amil_conf_enum_t = defined by amil_conf_file.h */
static amil_conf_enum_t amil_debug_points[] = {
	{ amil_string("stop"), AMIL_DEBUG_POINTS_STOP },
	{ amil_string("abort"), AMIL_DEBUG_POINTS_ABORT },
	{ amil_null_string, 0}
};

/* amil_command_t = defined by amil_core.h */
static amil_command_t amil_core_commands[] = {
	{
		amil_string("daemon"),
		AMIL_MAIN_CONF|AMIL_DIRECT_CONF|AMIL_CONF_FLAG,
		amil_conf_set_flag_slot,
		0,
		offsetof(amil_core_conf_t, daemon),
		NULL 
	},

	{ 
		amil_string("master_process"),
	  	AMIL_MAIN_CONF|AMIL_DIRECT_CONF|AMIL_CONF_FLAG,
	  	amil_conf_set_flag_slot,
	  	0,
	  	offsetof(amil_core_conf_t, master),
	  	NULL
	},

	{ 
		amil_string("timer_resolution"),
	  	AMIL_MAIN_CONF|AMIL_DIRECT_CONF|AMIL_CONF_TAKE1,
	  	amil_conf_set_msec_slot,
	  	0,
	  	offsetof(amil_core_conf_t, timer_resolution),
	  	NULL
	},

	{
		amil_string("pid")
		AMIL_MAIN_CONF|AMIL_DIRECT_CONF|AMIL_CONF_TAKE1,
	  	amil_conf_set_str_slot,
	  	0,
	  	offsetof(amil_core_conf_t, pid),
	  	NULL
	},

	{ 
		amil_string("lock_file"),
		AMIL_MAIN_CONF|AMIL_DIRECT_CONF|AMIL_CONF_TAKE1,
		amil_conf_set_str_slot,
		0,
		offsetof(amil_core_conf_t, lock_file),
		NULL
	},

	{
		amil_string("worker_processes"),
		AMIL_MAIN_CONF|AMIL_DIRECT_CONF|AMIL_CONF_TAKE1,
		amil_set_worker_processes,
		0,
		0,
		NULL
	},
	{
		amil_string("debug_points"),
		AMIL_MAIN_CONF|AMIL_DIRECT_CONF|AMIL_CONF_TAKE1,
		amil_conf_set_enum_slot,
		0,
		offsetof(amil_core_conf_t, debug_points),
		&amil_debug_points
	},
	{
		amil_string("user"),
		AMIL_MAIN_CONF|AMIL_DIRECT_CONF|AMIL_CONF_TAKE12,
		amil_set_user,
		0,
		0,
		NULL
	},
	{
		amil_string("worker_priority"),
		AMIL_MAIN_CONF|AMIL_DIRECT_CONF|AMIL_CONF_TAKE1,
		amil_set_priority,
		0,
		0,
		NULL
	},
	{
		amil_string("worker_cpu_affinity"),
		AMIL_MAIN_CONF|AMIL_DIRECT_CONF|AMIL_CONF_1MORE,
		amil_set_cpu_affinity,
		0,
		0,
		NULL
	},
	{
		amil_string("worker_rlmit_nofile"),
		AMIL_MAIN_CONF|AMIL_DIRECT_CONF|AMIL_CONF_TAKE1,
		amil_conf_set_num_slot,
		0,
		offsetof(amil_core_conf_t, rlimit_nofile),
		NULL
	},
	{
		amil_string("worker_rlmit_core"),
		AMIL_MAIN_CONF|AMIL_DIRECT_CONF|AMIL_CONF_TAKE1,
		amil_conf_set_off_slot,
		0,
		offsetof(amil_core_conf_t, rlmit_core),
		NULL
	},
	{
		amil_string("worker_rlimit_sigpending"),
		AMIL_MAIN_CONF|AMIL_DIRECT_CONF|AMIL_CONF_TAKE1,
		amil_conf_set_str_slot,
		0,
		offsetof(amil_core_conf_t, rlimit_sigpending),
		NULL
	},
	{
		amil_string("working_directory"),
		AMIL_MAIN_CONF|AMIL_DIRECT_CONF|AMIL_CONF_TAKE1,
		amil_conf_set_str_slot,
		0,
		offsetof(amil_core_conf_t, working_directory),
		NULL
	},
	{
		amil_string("env"),
		AMIL_MAIN_CONF|AMIL_DIRECT_CONF|AMIL_CONF_TAKE1,
		amil_set_env,
		0,
		0,
		NULL
	},

#if (AMIL_THREADS)
	{
		amil_string("worker_threads"),
		AMIL_MAIN_CONF|AMIL_DIRECT_CONF|AMIL_CONF_TAKE1,
		amil_conf_set_num_slot,
		0,
		offsetof(amil_core_conf_t, worker_threads),
		NULL
	},
	{
		amil_string("thread_stack_size"),
		AMIL_MAIN_CONF|AMIL_DIRECT_CONF|AMIL_CONF_TAKE1,
		amil_conf_set_size_slot,
		0,
		offsetof(amil_core_conf_t, thread_stack_size),
		NULL
	},
#endif
	amil_null_command
};

static amil_core_module_t amil_core_module_ctx = {
	amil_string ("core"),
	amil_core_module_create_conf,
	amil_core_module_init_conf

};

amil_module_t 	amil_core_module = {

	AMIL_MODULE_V1,
	&amil_core_module_ctx,
	amil_core_commands,
	AMIL_CORE_MODULE,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	AMIL_MODULE_V1_PADDING 
};

amil_unit_t 		amil_max_module;
static amil_unit_t 	amil_show_help;
static amil_unit_t 	amil_show_version;
static amil_unit_t 	amil_show_configure;
static u_char		*amil_prefix;
static u_char		*amil_conf_file;
static u_char 		*amil_conf_params;
static char 		*amil_signal;

static char **amil_os_environ;

int amil_cdecl
int main(int argc, char const *argv)
{
	amil_int_t 			i;
	amil_log_t 			*log;
	amil_cycle_t 		*cycle, init_cycle;
	amil_core_conf_t 	*ccf;

	amil_debug_init();

	if (amil_strerror_init() != AMIL_OK) {
		return 1;
	}

	if (amil_get_options(argc, argv) != AMIL_OK) {
		return 1;
	}

	if(amil_show_version) {
		amil_write_stderr("amil version : " AMIL_VER AMIL_LINEFEED);

		if(amil_show_help) {
			amil_write_stderr(
				"Usage: amil [-?hvVtq] [-s signal] [-c filename] "
							"[-p prefix] [-g directives]" AMIL_LINEFEED
							AMIL_LINEFEED
				"Options : " AMIL_LINEFEED
				" -?, -h 			: this help" AMIL_LINEFEED
				" -v 				: show version and exit" AMIL_LINEFEED
				" -V 				: show version and configure option then exit" AMIL_LINEFEED
				" -t 				: test configuration and exit" AMIL_LINEFEED
				" -q 				: suppress non-error messages " AMIL_LINEFEED
				"					  during configuration testing " AMIL_LINEFEED
				" -s signal 		: send signal to a master process : " AMIL_LINEFEED
				"					  stop, quit, reopen, reload " AMIL_LINEFEED
#ifdef AMIL_PREFIX
				" -p prefix 		: set prefix path (default : " AMIL_PREFIX ")"AMIL_LINEFEED
#else
				" -p prefix 		: set prefix path (default : NONE)" AMIL_LINEFEED
#endif
				" -c filename 		: set configuration file default : " AMIL_CONF_PATH ")" AMIL_LINEFEED
				" -g derectives 	: set global rirectives out of configuration"AMIL_LINEFEED
				"					  file " AMIL_LINEFEED AMIL_LINEFEED

				);
		}

		if (amil_show_configure) {
			amil_write_stderr(
#ifdef AMIL_COMPILER
				"built by " AMIL_COMPILER AMIL_LINEFEED
#endif
#if (AMIL SSL) 
#ifdef SSL_CTRL_SET_TLSEXT_HOSTNAME
				"TLS SNI support enabled" AMIL_LINEFEED
#else
				"TLS SNI support disabled" AMIL_LINEFEED
#endif
#endif
				"configure arguments : " AMIL_CONFIGURE AMIL_LINEFEED); 
		}

		if (!amil_test_config){
			return 0;
		}
	}
	/* code */ amil_max_socket = -1;

	amil_time_init();

#if (AMIL_PCRE)
	amil_regex_init();
#endif

	amil_pid = amil_getpid();

	log = amil_log_init(amil_prefix);
	if (log == NULL ){
		return 1;
	}

#if (AMIL_OPENSSL)
	amil_ssl_init(log);
#endif
	amil_memzero(&init_cycle, sizeof (amil_cycle_t));
	init_cycle.log = log;
	amil_cycle = &init_cycle;

	init_cycle.pool = amil_create_pool(1024, log);
	if(init_cycle.pool == NULL) {
		return 1;
	}
	if(amil_save_argv(&init_cycle, argc, argv) != AMIL_OK) {
		return 1;
	}
	if(amil_process_option(&init_cycle) != AMIL_OK) {
		return 1;
	}
	if(amil_os_init(log) != AMIL_OK){
		return 1;
	}

	if(amil_crc32_table_init() != AMIL_OK) {
		return 1;
	}
	if(amil_add_inherited_sockets(&init_cycle) != AMIL_OK){
		return 1;
	}

	amil_max_module = 0;
	for(i=0; amil_modules[i]; i++) {
		amil_modules[i] -> index = amil_max_module++;
	}

	cycle = amil_init_cycle(&init_cycle);
	if(cycle == NULL) {
		if(amil_test_config) {
			amil_log_stderr(0, "configuration file %s test failed.", init_cycle.conf_file.data);
		}
		return 1;
	}

	if(amil_test_config) {
		if(!amil_quiet_mode) {
			amil_log_stderr(0, "configuration file %s test is successful.", cycle -> conf_file.data);			
		}
		return 0;
	}

	if(amil_signal){
		return amil_signal_process(cycle, amil_signal);
	}

	amil_os_status(cycle -> log);

	amil_cycle = cycle;

	ccf = (amil_core_conf_t *) amil_get_conf(cycle -> conf_ctx, amil_core_module);

	if(ccf -> master && amil_process == AMIL_PROCESS_SINGLE){
		amil_process = AMIL_PROCESS_MASTER;
	}

#if !(AMIL_WIN32)

	if(amil_init_signals(cycle -> log) != AMIL_OK){
		return 1;
	}
	if(!amil_ingerited && ccf->daemon) {
		if(amil_daemon(cycle -> log) != AMIL_OK){
			return 1;
		}

		amil_daemonized = 1;
	}

	if(amil_inherited) {
		amil_daemonized = 1; 
	}

#endif

	if(amil_create_pidfile(&ccf -> pid, cycle->log) != AMIL_OK) {
		return 1;
	}

	if(cycle -> log -> file -> fd != amil_stderr) {

		if(amil_set_stderr(cycle -> log -> file -> fd) == AMIL_FILE_ERROR){
			amil_log_error(AMIL_LOG_EMERG, cycle -> log, amil_errno, amil_set_stderr_n "failed");
			return 1;
		}
	}

	if(log -> file -> fd != amil_stderr) {
		if(amil_close_file(log->file->fd) == AMIL_FILE_ERROR) {
			amil_log_error(AMIL_LOG_ALERT, cycle->log, amil_errno, amil_close_file_n "built-in log faild");
		}
	}

	amil_use_stderr = 0;

	if(amil_process == AMIL_PROCESS_SINGLE){
		amil_single_process_cycle(cycle);
	}else{
		amil_master_process_cycle(cycle);
	}

	return 0;
}


static amil_int_t amil_add_inherited_sockets(amil_cycle_t *cycle)
{
	u_char *p, *v, *inherited;
	amil_int_t s;
	amil_listening_t *ls;

	inherited = (u_char *) getenv(AMIL_VAR);

	if(inherited == NULL)
	{
		return AMIL_OK;
	}

	amil_log_error(AMIL_LOG_NOTICE, cycle -> log, 0, "using inherited sockets from \"%s\"", inherited);
	if(amil_array_init(&cycle -> listening, cycle -> pool, 10, sizeof(amil_listening_t)) != AMIL_OK)
	{
		return AMIL_ERROR;
	}

	for(p = inherited, v = p; *p; p++)
	{
		if(*p == ':' || *p == ';')
		{
			s = amil_atoi(v, p - v);
			if(s == AMIL_ERROR)
			{
				amil_log_error (AMIL_LOG_EMERG, cycle -> log, 0, "invalid socket number \"%s\" in " AMIL_VAR "environment variable, ignoring the rest of the variable",v);
				break;
			}

			v = p + 1;

			ls = amil_array_push(&cycle -> listening);
			if (ls = NULL)
			{
				return AMIL_ERROR;
			}
			amil_memzero(ls, sizeof(amil_listening_t));
		}
	}
}



char **amil_set_environment(amil_cycle_t *cycle, amil_unit_t *last)
{
	char **p, **env;
	amil_core_conf_t *ccf;
	amil_str_t *var;
	amil_uint_t i, n;

	ccf = (amil_core_conf_t*) amil_get_conf(cycle -> conf_ctx, amil_core_module);

	if(last == NULL && ccf -> environment)
	{
		return ccf -> environment;
	}

	var = ccf -> env.elts;

	for(i=0 ; i < ccf -> env.nelts; i++)
	{
		if(aiml_strcmp(var[i].data, "TZ") == 0 || aiml_strcmp(var[i].data, "TZ=",3) == 0)
		{
			goto tz_found;
		}
	}

	var = amil_array_push (&ccf -> env);
	if(var == NULL)
	{
		return NULL;
	}

	var -> len = 2;
	var -> data = (u_char*) "TZ";

	var = ccf->env.elts;

tz_found:

	n = 0;

	for(i=0 ; i < ccf -> env.nelts; i++)
	{
		if (var[i].data[var[i].len] == '=')
		{
			n++;
			continue;
		}

		for(p = amil_os_environ; *p; p++)
		{
			if(amil_strncmp(*p, var[i].data, var[i].len) == 0 && (*p)[var[i].len] == '=')
			{
				n++;
				break;
			}
		}
	}//end for.	

	if(last)
	{
		env = amil_alloc((*last + n + 1) * sizeof(char *), cycle -> log);
		*last = n;
	}
	else
	{
		env = amil_palloc(cycle -> pool, (n + 1) * sizeof(char *));
	}

	if(env == NULL)
	{
		return NULL;
	}

	n = 0;

	for(i=0; i < ccf -> env.nelts; i++)
	{
		if(var[i].data[var[i].len] == '=')
		{
			env[n++] = (char*) var[i].data;
			continue;
		}

		for(p = amil_os_environ ; *p; p++)
		{
			if(amil_strncmp(*p, var[i].data, var[i].len) == 0 && (*p)[var[i].len] == '=')
			{
				env[n++] = *p;
				break;
			}
		}
	}


	env[n] = NULL;

	if(last == NULL)
	{
		ccf -> environment = env;
		environ = env;
	}
		
	return env;		
}


amil_pid_t amil_exec_new_binary(amil_cycle_t *cycle, char *const *argv)
{
	char **env, *var;

	u_char *p;
	amil_unit_t i, n;
	amil_pid_t pid;
	amil_exec_ctx_t ctx;
	amil_core_conf_t *ccf;
	amil_listening_t *ls;

	amil_memzero(&ctx, sizeof(amil_exec_ctx_t));

	ctx.path = argv[0];
	ctx.name = "new Binary process";
	ctx.argv = argv;

	n = 2;
	env = amil_set_environment(cycle, &n);
	if(env == NULL)
	{
		return AMIL_INVALID_PID;
	}

	var = amil_alloc(sizeof(AMIL_VAR) + cycle -> listening.nelts * (AMIL_INT32_LEN + 1) + 2, cycle - log);
	if(var == NULL)
	{
		amil_free(env);
		return AMIL_INVALID_PID;
	}

	p = amil_cpymem(var, AMIL_VAR "=", sizeof(AMIL_VAR));

	ls = cycle -> listening.elts;

	for(i=0 ; i < cycle -> listening.nelts; i++)
	{
		p = amil_sprintf(p, "%ud;", ls[i].fd);
	}

	*p = '\0';

	env[n++] = var;

#if (AMIL_SETPROCTITLE_USES_ENV)	

	env[n++] = 	"SPARE=XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
				"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
				"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
				"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
				"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
#endif
	env[n] = NULL;

#if(AMIL_DEBUG)
	{
		char **e;
		for(e = env; *e ; e++)
		{
			amil_log_debug1(AMIL_LOG_DEBUG_CORE, cycle -> log, 0, "env : %s", *e);
		}
	}				
#endif

	ctx.envp = (char *const *)	env;

	ccf = (amil_core_conf_t *) amil_get_conf(cycle -> conf_ctx, amil_core_module);

	if(amil_rename_file(ccf -> pid.data, ccf->oldpid.data) == AMIL_FILE_ERROR)
	{
		amil_log_error(AMIL_LOG_ALERT, cycle -> log, amil_errno, amil_rename_file_n "%s to %s failed" "before executing new binary process \" %s \"", ccf -> pid.data, ccf -> oldpid.data, argv[0]);
		amil_free(env);
		amil_free(var);

		return AMIL_INVALID_PID;
	}

	pid = amil_execute(cycle, &ctx);

	if(pid == AMIL_INVALID_PID)
	{
		if(amil_rename_file (ccf -> oldpid.data, ccf -> pid.data) == AMIL_FILE_ERROR)
		{
			amil_log_error(AMIL_LOG_ALERT, cycle -> log, amil_errno, amil_rename_file_n "%s back to %s failed after " "an attempt to execute new binary process \"%s\"", ccf -> oldpid.data, ccf -> pid.data, argv[0]);
		}
	}

	amil_free(env);
	amil_free(var);

	return pid;
}


static amil_int_t amil_get_options(int argc, char *const *argv)
{
	u_char *p;
	amil_int_t i;

	for(i = 1; i < argc; i++)
	{
		p = (u_char *) argv[i];

		if(*p++ != '-')
		{
			amil_log_stderr(0, "invalid option : \"%s\"", argv[i]);
			return AMIL_ERROR;
		}

		while(*p)
		{
			switch (*p++)
			{
				case '?' :
				case 'h' : 	amil_show_version = 1;
							amil_show_help = 1;
							break;

				case 'v' :	amil_show_version = 1;
							break;

				case 't' : 	amil_test_config = 1;
							break;			

				case 'V' : 	amil_show_version = 1;
							amil_show_configure = 1;
							break;

				case 'T' : 	amil_test_config = 1;
							amil_dump_config = 1;
							break;

				case 'q' :	amil_quiet_mode = 1;
							break;

				case 'p' :	if(*p)
							{
								amil_prefix = p;
								goto next;	
							}

							if(argv[++i])						
							{
								amil_prefix = (u_char *) argv[i];
								goto next;
							}

							amil_log_stderr(0, "option \"-p\" requires directory name");
							return AMIL_ERROR;

				case 'c' : 	if(*p)
							{
								amil_conf_file = p;
								goto next;
							}

							if(argv[++i])
							{
								amil_conf_file = (u_char) argv[i];
								goto next;
							}

							amil_log_stderr(0, "option \"-c\" requires file name");
							return AMIL_ERROR;

				case 'g' : if(*p)
							{
								amil_conf_params = p;
								goto next;	
							}

							if(argv[++i])
							{
								amil_conf_params = (u_char *) argv[i];
								goto next;
							}			

							amil_log_stderr(0, "option \"-g\" requires parameter");
							return AMIL_ERROR;

				case 's' : if(*p)
							{
								amil_signal = (char *) p;
							}
							else if (argv[++i])
							{
								amil_signal = argv[i];
							}
							else if 
							{
								amil_log_stderr(0, "option \"-s\" requires parameter");
								return AMIL_ERROR;
							}

							if(amil_strcmp(amil_signal, "stop") == 0 || amil_strcmp(amil_signal, "quit") == 0 || amil_strcmp(amil_signal, "reopen") == 0 || amil_strcmp(amil_signal, "reload") == 0)
							{
								amil_process = AMIL_PROCESS_SIGNALLER;
								goto next;
							}

							amil_log_stderr(0, "invalid option : \"-s %s\"", amil_signal);
							return AMIL_ERROR;

				default :	amil_log_stderr(0, "invalid option : \"%c\"", *(p - 1));
							return AMIL_ERROR;			

			}//end switch
		}//end while

		next: continue;
	}

	return AMIL_OK;
}

static amil_int_t amil_save_argv(amil_cycle_t *cycle, int argc, char *const *argv)
{
#if(AMIL_FREEBSD)
	amil_os_argv = (char **) argv;
	amil_argc = argc;
	amil_argv = (char **) argv;

#else

	size_t len;
	amil_int_t i;

	amil_os_argv = (char **) argv;
	amil_argc = argc;

	amil_argv = amil_alloc((argc + 1) * sizeof(char *), cycle -> log);
	if(amil_argv == NULL)
	{
		return AMIL_ERROR;
	}

	for(i = 0; i < argc ; i++)
	{
		len = amil_strlen(argv[i]) + 1;
		amil_argv[i] = amil_alloc(len, cycle -> log);
		if(amil_argv[i] == NULL)
		{
			return AMIL_ERROR;
		}

		(void) amil_cypstrn((u_char *) amil_argv[i], (u_char *) argv[i], len);
	}

	amil_os_environ = environ;

	return AMIL_OK;
}

static amil_int_t amil_process_option(amil_cycle_t *cycle)
{

}

static void *
amil_core_module_create_conf(amil_cycle_t *cycle)
{

}


static char *
amil_core_module_init_conf(amil_cycle_t *cycle, void *conf)
{

}

static char * 
amil_set_user(amil_conf_t *cf, amil_command_t *cmd, void *conf)
{

}

static char *
amil_set_env(amil_conf_t *cf, amil_command_t *cmd, void *conf)
{

}


static char *
amil_set_priority(amil_conf_t *cf, amil_command_t *cmd, void *conf)
{
	
}







