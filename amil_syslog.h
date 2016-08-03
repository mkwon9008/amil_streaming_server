


#ifndef AMIL_SYSLOG_HEADER_INCLUDE
#define AMIL_SYSLOG_HEADER_INCLUDE

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

char *amil_syslog_process_conf(amil_conf_t *cf, amil_syslog_peer_t *peer);
u_char *amil_syslog_add_header(amil_syslog_peer_t *peer, u_char *buf);
void aiml_syslog_writer(amil_log_t *log, amil_uint_t level, u_char *buf, size_t len);
ssize_t amil_syslog_send(amil_syslog_peer_t *peer, u_char *buf, size_t len);

#endif