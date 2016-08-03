/*amil project created by Kwon*/

#include <amil_config.h>
#include <amil_core.h>
#include <amil.h>

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

static amil_conf_enum_t amil_debug_points[] = {
	{ amil_string("stop"), AMIL_DEBUG_POINTS_STOP },
	{ amil_string("abort"), AMIL_DEBUG_POINTS_ABORT },
	{ amil_null_string, 0}
};

static amil_command_t amil_core_commands[] = {
	{ amil_string("daemon"),
	  AMIL_MAIN_CONF|AMIL_DIRECT_CONF|AMIL_CONF_FLAG,
	  amil_conf_set_flag_slot,
	  0,
	  offsetof(amil_core_conf_t, daemon),
	  NULL },

	{ amil_string("master_process"),
	  AMIL_MAIN_CONF|AMIL_DIRECT_CONF|AMIL_CONF_FLAG,
	  amil_conf_set_flag_slot,
	  0,
	  offsetof(amil_core_conf_t, master),
	  NULL },

	{ amil_string("timer_resolution"),
	  AMIL_MAIN_CONF|AMIL_DIRECT_CONF|AMIL_CONF_TAKE1,
	  amil_conf_set_msec_slot,
	  0,
	  offsetof(amil_core_conf_t, timer_resolution),
	  NULL },

	{ amil_string("pid")
	  AMIL_MAIN_CONF|AMIL_DIRECT_CONF|AMIL_CONF_TAKE1,
	  amil_conf_set_str_slot,
	  0,
	  offsetof(amil_core_conf_t, pid),
	  NULL },

	{ amil_string("lock_file"),
	AMIL_MAIN_CONF|AMIL_DIRECT_CONF|AMIL_CONF_TAKE1,
	amil_conf_set_str_slot,
	0,
	offsetof(amil_core_conf_t, lock_file),
	NULL },

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



char **
amil_set_environment(amil_cycle_t *cycle, amil_unit_t *last)
{

}


amil_pid_t
amil_exec_new_binary(amil_cycle_t *cycle, char *const *argv)
{

}

static amil_int_t
amil_get_options(int argc, char *const *argv)
{

}

static amil_int_t
amil_save_argv(amil_cycle_t *cycle, int argc, char *const *argv)
{

}

static amil_int_t
amil_process_option(amil_cycle_t *cycle)
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







