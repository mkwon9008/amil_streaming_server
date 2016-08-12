
/*	amil_syslog.h
*	This file is defined macros and structs for system log. 
*	<RULE>
*	1. Function is created as concise as possible.
*	2. If you must write a custom function before amil + underbar.
*	3. Function names are separated by a custom type + content + relevant work.
	   If needed, it may be written the use of the method object between custom type and content.
*	4. The macro statement is written in capital letters.
*/	


#ifndef AMIL_SYSLOG_HEADER_INCLUDE
#define AMIL_SYSLOG_HEADER_INCLUDE

/* type defined amil_syslog_peer_t */
typedef struct 
{
	amil_pool_t *pool;
	amil_uint_t facility;
	amil_uint_t severity;
	amil_str_t tag;

	amil_addr_t server;
	amil_connection_t conn;
	unsigned busy:1;
	unsigned nohostname:1;
} amil_syslog_peer_t;


/* functionality preprocessing start. */
char *amil_syslog_process_conf(amil_conf_t *cf, amil_syslog_peer_t *peer);
u_char *amil_syslog_add_header(amil_syslog_peer_t *peer, u_char *buf);
void aiml_syslog_writer(amil_log_t *log, amil_uint_t level, u_char *buf, size_t len);
ssize_t amil_syslog_send(amil_syslog_peer_t *peer, u_char *buf, size_t len);

#endif