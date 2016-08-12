
/*	amil_syslog.c
*	This file get system log from OS. 
*	<RULE>
*	1. Function is created as concise as possible.
*	2. If you must write a custom function before amil + underbar.
*	3. Function names are separated by a custom type + content + relevant work.
	   If needed, it may be written the use of the method object between custom type and content.
*	4. The macro statement is written in capital letters.
*/	

#include <amil_config.h>
#include <amil_core.h>

#define AMIL_SYSLOG_MAX_STR AMIL_MAX_ERROR_STR + sizeof("<255>Jan 01 00:00:00 ") - 1 + (AMIL_MAXHOSTNAMELEN - 1) + 1/*space size*/ + 32/*tag size*/ + 2/*space + colon size*/

static char *amil_syslog_parse_args(amil_conf_t *cf, amil_syslog_peer_t *peer);
static amil_int_t amil_syslog_init_peer(amil_syslog_peer_t *peer);
static void amil_syslog_cleanup(void *data);

void amil_syslog_writer(amil_log_t *log, amil_uint_t level, u_char *buf, size_t len)
{
	u_char			*p, msg[AMIL_SYSLOG_MAX_STR];
	amil_uint_t		head_len;
	amil_syslog_peer_t *peer;

	peer = log -> wdata;

	if(peer -> busy) 
	{
		return;
	}

	peer -> busy = 1;
	peer -> severity = level - 1;

	p = amil_syslog_add_header(peer, msg);
	head_len = p - msg;

	len -= AMIL_LINEFEED_SIZE;

	if()

}