#include <stdarg.h>
#include <stddef.h>

#include "tun2http.h"

int loglevel = ANDROID_LOG_WARN;

int __android_log_print(int prio, const char *tag, const char *fmt, ...) {
    (void)prio;
    (void)tag;
    (void)fmt;
    return 0;
}

void log_android(int prio, const char *fmt, ...) {
    (void)prio;
    (void)fmt;
}

int has_udp_session(const struct arguments *args, const uint8_t *pkt, const uint8_t *payload) {
    (void)args;
    (void)pkt;
    (void)payload;
    return 0;
}

jboolean handle_icmp(const struct arguments *args,
                     const uint8_t *pkt, size_t length,
                     const uint8_t *payload,
                     int uid,
                     const int epoll_fd) {
    (void)args;
    (void)pkt;
    (void)length;
    (void)payload;
    (void)uid;
    (void)epoll_fd;
    return 0;
}

jboolean handle_udp(const struct arguments *args,
                    const uint8_t *pkt, size_t length,
                    const uint8_t *payload,
                    int uid,
                    const int epoll_fd) {
    (void)args;
    (void)pkt;
    (void)length;
    (void)payload;
    (void)uid;
    (void)epoll_fd;
    return 0;
}

jboolean handle_tcp(const struct arguments *args,
                    const uint8_t *pkt, size_t length,
                    const uint8_t *payload,
                    int uid,
                    const int epoll_fd) {
    (void)args;
    (void)pkt;
    (void)length;
    (void)payload;
    (void)uid;
    (void)epoll_fd;
    return 0;
}

jint get_uid(const int version, const int protocol,
             const void *saddr, const uint16_t sport,
             const void *daddr, const uint16_t dport) {
    (void)version;
    (void)protocol;
    (void)saddr;
    (void)sport;
    (void)daddr;
    (void)dport;
    return -1;
}
