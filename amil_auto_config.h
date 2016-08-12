
/*	amil_auto_configure.h
*	This file is create check list of header file of standard library.
*	And defination configure path and local file path. 
*	<RULE>
*	1. Function is created as concise as possible.
*	2. If you must write a custom function before amil + underbar.
*	3. Function names are separated by a custom type + content + relevant work.
	   If needed, it may be written the use of the method object between custom type and content.
*	4. The macro statement is written in capital letters.
*/	


#define AMIL_CONFIGURE "--prefix=/usr --conf-path=/etc/amil/amil.conf --pid-path=/var/run/amil.pid --lock-path=/var/lock/amil.lock --error-log-path=/var/log/amil/error.log --http-log-path=/var/log/amil/access.log --http-client-body-temp-path=/var/spool/amil/body --http-proxy-temp-path=/var/spool/amil/proxy --http-fastcgi-temp-path=/var/spool/amil/fastcgi --with-http_ssl_module --with-http_spdy_module --with-http_realip_module --with-http_addition_module --with-http_xslt_module --with-http_image_filter_module --with-http_geoip_module --with-http_sub_module --with-http_dav_module --with-http_flv_module --with-http_mp4_module --with-http_gunzip_module --with-http_gzip_static_module --with-http_auth_request_module --with-http_random_index_module --with-http_secure_link_module --with-http_degradation_module --with-http_stub_status_module --with-mail --with-mail_ssl_module --with-stream --with-stream_ssl_module --with-pcre --with-pcre-jit --with-http_perl_module --user=80 --group=80"


#ifndef AMIL_HAVE_GCC_ATOMIC
#define AMIL_HAVE_GCC_ATOMIC  1
#endif


#ifndef AMIL_HAVE_C99_VARIADIC_MACROS
#define AMIL_HAVE_C99_VARIADIC_MACROS  1
#endif


#ifndef AMIL_HAVE_GCC_VARIADIC_MACROS
#define AMIL_HAVE_GCC_VARIADIC_MACROS  1
#endif


#ifndef AMIL_HAVE_EPOLL
#define AMIL_HAVE_EPOLL  1
#endif


#ifndef AMIL_HAVE_CLEAR_EVENT
#define AMIL_HAVE_CLEAR_EVENT  1
#endif


#ifndef AMIL_HAVE_EPOLLRDHUP
#define AMIL_HAVE_EPOLLRDHUP  1
#endif


#ifndef AMIL_HAVE_O_PATH
#define AMIL_HAVE_O_PATH  1
#endif


#ifndef AMIL_HAVE_SENDFILE
#define AMIL_HAVE_SENDFILE  1
#endif


#ifndef AMIL_HAVE_SENDFILE64
#define AMIL_HAVE_SENDFILE64  1
#endif


#ifndef AMIL_HAVE_PR_SET_DUMPABLE
#define AMIL_HAVE_PR_SET_DUMPABLE  1
#endif


#ifndef AMIL_HAVE_SCHED_SETAFFINITY
#define AMIL_HAVE_SCHED_SETAFFINITY  1
#endif


#ifndef AMIL_HAVE_GNU_CRYPT_R
#define AMIL_HAVE_GNU_CRYPT_R  1
#endif


#ifndef AMIL_HAVE_NONALIGNED
#define AMIL_HAVE_NONALIGNED  1
#endif


#ifndef AMIL_CPU_CACHE_LINE
#define AMIL_CPU_CACHE_LINE  32
#endif


#define AMIL_KQUEUE_UDATA_T  (void *)


#ifndef AMIL_HAVE_POSIX_FADVISE
#define AMIL_HAVE_POSIX_FADVISE  1
#endif


#ifndef AMIL_HAVE_O_DIRECT
#define AMIL_HAVE_O_DIRECT  1
#endif


#ifndef AMIL_HAVE_ALIGNED_DIRECTIO
#define AMIL_HAVE_ALIGNED_DIRECTIO  1
#endif


#ifndef AMIL_HAVE_STATFS
#define AMIL_HAVE_STATFS  1
#endif


#ifndef AMIL_HAVE_STATVFS
#define AMIL_HAVE_STATVFS  1
#endif


#ifndef AMIL_HAVE_SCHED_YIELD
#define AMIL_HAVE_SCHED_YIELD  1
#endif


#ifndef AMIL_HAVE_DEFERRED_ACCEPT
#define AMIL_HAVE_DEFERRED_ACCEPT  1
#endif


#ifndef AMIL_HAVE_KEEPALIVE_TUNABLE
#define AMIL_HAVE_KEEPALIVE_TUNABLE  1
#endif


#ifndef AMIL_HAVE_TCP_INFO
#define AMIL_HAVE_TCP_INFO  1
#endif


#ifndef AMIL_HAVE_ACCEPT4
#define AMIL_HAVE_ACCEPT4  1
#endif


#ifndef AMIL_HAVE_EVENTFD
#define AMIL_HAVE_EVENTFD  1
#endif


#ifndef AMIL_HAVE_SYS_EVENTFD_H
#define AMIL_HAVE_SYS_EVENTFD_H  1
#endif


#ifndef AMIL_HAVE_UNIX_DOMAIN
#define AMIL_HAVE_UNIX_DOMAIN  1
#endif


#ifndef AMIL_PTR_SIZE
#define AMIL_PTR_SIZE  4
#endif


#ifndef AMIL_SIG_ATOMIC_T_SIZE
#define AMIL_SIG_ATOMIC_T_SIZE  4
#endif


#ifndef AMIL_HAVE_LITTLE_ENDIAN
#define AMIL_HAVE_LITTLE_ENDIAN  1
#endif


#ifndef AMIL_MAX_SIZE_T_VALUE
#define AMIL_MAX_SIZE_T_VALUE  2147483647
#endif


#ifndef AMIL_SIZE_T_LEN
#define AMIL_SIZE_T_LEN  (sizeof("-2147483648") - 1)
#endif


#ifndef AMIL_MAX_OFF_T_VALUE
#define AMIL_MAX_OFF_T_VALUE  9223372036854775807LL
#endif


#ifndef AMIL_OFF_T_LEN
#define AMIL_OFF_T_LEN  (sizeof("-9223372036854775808") - 1)
#endif


#ifndef AMIL_TIME_T_SIZE
#define AMIL_TIME_T_SIZE  4
#endif


#ifndef AMIL_TIME_T_LEN
#define AMIL_TIME_T_LEN  (sizeof("-2147483648") - 1)
#endif


#ifndef AMIL_MAX_TIME_T_VALUE
#define AMIL_MAX_TIME_T_VALUE  2147483647
#endif


#ifndef AMIL_HAVE_PREAD
#define AMIL_HAVE_PREAD  1
#endif


#ifndef AMIL_HAVE_PWRITE
#define AMIL_HAVE_PWRITE  1
#endif


#ifndef AMIL_SYS_NERR
#define AMIL_SYS_NERR  135
#endif


#ifndef AMIL_HAVE_LOCALTIME_R
#define AMIL_HAVE_LOCALTIME_R  1
#endif


#ifndef AMIL_HAVE_POSIX_MEMALIGN
#define AMIL_HAVE_POSIX_MEMALIGN  1
#endif


#ifndef AMIL_HAVE_MEMALIGN
#define AMIL_HAVE_MEMALIGN  1
#endif


#ifndef AMIL_HAVE_MAP_ANON
#define AMIL_HAVE_MAP_ANON  1
#endif


#ifndef AMIL_HAVE_MAP_DEVZERO
#define AMIL_HAVE_MAP_DEVZERO  1
#endif


#ifndef AMIL_HAVE_SYSVSHM
#define AMIL_HAVE_SYSVSHM  1
#endif


#ifndef AMIL_HAVE_POSIX_SEM
#define AMIL_HAVE_POSIX_SEM  1
#endif


#ifndef AMIL_HAVE_MSGHDR_MSG_CONTROL
#define AMIL_HAVE_MSGHDR_MSG_CONTROL  1
#endif


#ifndef AMIL_HAVE_FIONBIO
#define AMIL_HAVE_FIONBIO  1
#endif


#ifndef AMIL_HAVE_GMTOFF
#define AMIL_HAVE_GMTOFF  1
#endif


#ifndef AMIL_HAVE_D_TYPE
#define AMIL_HAVE_D_TYPE  1
#endif


#ifndef AMIL_HAVE_SC_NPROCESSORS_ONLN
#define AMIL_HAVE_SC_NPROCESSORS_ONLN  1
#endif


#ifndef AMIL_HAVE_OPENAT
#define AMIL_HAVE_OPENAT  1
#endif


#ifndef AMIL_HAVE_GETADDRINFO
#define AMIL_HAVE_GETADDRINFO  1
#endif


#ifndef AMIL_HTTP_CACHE
#define AMIL_HTTP_CACHE  1
#endif


#ifndef AMIL_HTTP_GZIP
#define AMIL_HTTP_GZIP  1
#endif


#ifndef AMIL_HTTP_SSI
#define AMIL_HTTP_SSI  1
#endif


#ifndef AMIL_HTTP_GZIP
#define AMIL_HTTP_GZIP  1
#endif


#ifndef AMIL_HTTP_SPDY
#define AMIL_HTTP_SPDY  1
#endif


#ifndef AMIL_HTTP_GZIP
#define AMIL_HTTP_GZIP  1
#endif


#ifndef AMIL_HTTP_DAV
#define AMIL_HTTP_DAV  1
#endif


#ifndef AMIL_CRYPT
#define AMIL_CRYPT  1
#endif


#ifndef AMIL_HTTP_REALIP
#define AMIL_HTTP_REALIP  1
#endif


#ifndef AMIL_HTTP_X_FORWARDED_FOR
#define AMIL_HTTP_X_FORWARDED_FOR  1
#endif


#ifndef AMIL_HTTP_X_FORWARDED_FOR
#define AMIL_HTTP_X_FORWARDED_FOR  1
#endif


#ifndef AMIL_HTTP_X_FORWARDED_FOR
#define AMIL_HTTP_X_FORWARDED_FOR  1
#endif


#ifndef AMIL_HTTP_SSL
#define AMIL_HTTP_SSL  1
#endif


#ifndef AMIL_HTTP_X_FORWARDED_FOR
#define AMIL_HTTP_X_FORWARDED_FOR  1
#endif


#ifndef AMIL_HTTP_DEGRADATION
#define AMIL_HTTP_DEGRADATION  1
#endif


#ifndef AMIL_HTTP_UPSTREAM_ZONE
#define AMIL_HTTP_UPSTREAM_ZONE  1
#endif


#ifndef AMIL_STAT_STUB
#define AMIL_STAT_STUB  1
#endif


#ifndef AMIL_MAIL_SSL
#define AMIL_MAIL_SSL  1
#endif


#ifndef AMIL_STREAM_SSL
#define AMIL_STREAM_SSL  1
#endif


#ifndef AMIL_STREAM
#define AMIL_STREAM  1
#endif


#ifndef AMIL_STREAM_UPSTREAM_ZONE
#define AMIL_STREAM_UPSTREAM_ZONE  1
#endif


#ifndef AMIL_PCRE
#define AMIL_PCRE  1
#endif


#ifndef AMIL_HAVE_PCRE_JIT
#define AMIL_HAVE_PCRE_JIT  1
#endif


#ifndef AMIL_OPENSSL
#define AMIL_OPENSSL  1
#endif


#ifndef AMIL_SSL
#define AMIL_SSL  1
#endif


#ifndef AMIL_HAVE_OPENSSL_MD5_H
#define AMIL_HAVE_OPENSSL_MD5_H  1
#endif


#ifndef AMIL_OPENSSL_MD5
#define AMIL_OPENSSL_MD5  1
#endif


#ifndef AMIL_HAVE_MD5
#define AMIL_HAVE_MD5  1
#endif


#ifndef AMIL_HAVE_OPENSSL_SHA1_H
#define AMIL_HAVE_OPENSSL_SHA1_H  1
#endif


#ifndef AMIL_HAVE_SHA1
#define AMIL_HAVE_SHA1  1
#endif


#ifndef AMIL_ZLIB
#define AMIL_ZLIB  1
#endif


#ifndef AMIL_HAVE_EXSLT
#define AMIL_HAVE_EXSLT  1
#endif


#ifndef AMIL_PREFIX
#define AMIL_PREFIX  "/usr/"
#endif


#ifndef AMIL_CONF_PREFIX
#define AMIL_CONF_PREFIX  "/etc/amil/"
#endif


#ifndef AMIL_SBIN_PATH
#define AMIL_SBIN_PATH  "sbin/amil"
#endif


#ifndef AMIL_CONF_PATH
#define AMIL_CONF_PATH  "/etc/amil/amil.conf"
#endif


#ifndef AMIL_PID_PATH
#define AMIL_PID_PATH  "/var/run/amil.pid"
#endif


#ifndef AMIL_LOCK_PATH
#define AMIL_LOCK_PATH  "/var/lock/amil.lock"
#endif


#ifndef AMIL_ERROR_LOG_PATH
#define AMIL_ERROR_LOG_PATH  "/var/log/amil/error.log"
#endif


#ifndef AMIL_HTTP_LOG_PATH
#define AMIL_HTTP_LOG_PATH  "/var/log/amil/access.log"
#endif


#ifndef AMIL_HTTP_CLIENT_TEMP_PATH
#define AMIL_HTTP_CLIENT_TEMP_PATH  "/var/spool/amil/body"
#endif


#ifndef AMIL_HTTP_PROXY_TEMP_PATH
#define AMIL_HTTP_PROXY_TEMP_PATH  "/var/spool/amil/proxy"
#endif


#ifndef AMIL_HTTP_FASTCGI_TEMP_PATH
#define AMIL_HTTP_FASTCGI_TEMP_PATH  "/var/spool/amil/fastcgi"
#endif


#ifndef AMIL_HTTP_UWSGI_TEMP_PATH
#define AMIL_HTTP_UWSGI_TEMP_PATH  "uwsgi_temp"
#endif


#ifndef AMIL_HTTP_SCGI_TEMP_PATH
#define AMIL_HTTP_SCGI_TEMP_PATH  "scgi_temp"
#endif


#ifndef AMIL_SUPPRESS_WARN
#define AMIL_SUPPRESS_WARN  1
#endif


#ifndef AMIL_SMP
#define AMIL_SMP  1
#endif


#ifndef AMIL_USER
#define AMIL_USER  "80"
#endif


#ifndef AMIL_GROUP
#define AMIL_GROUP  "80"
#endif
