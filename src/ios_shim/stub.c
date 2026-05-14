#include <stddef.h>
#include "proxyswitcher_tun2http.h"

int ps_t2h_android_init(void* jni_env, void* java_instance) {
    (void)jni_env;
    (void)java_instance;
    return 0;
}

int ps_t2h_android_start(void* jni_env, void* java_instance, int tun_fd, int fwd53, int rcode, const char* proxy_ip, int proxy_port) {
    (void)jni_env;
    (void)java_instance;
    (void)tun_fd;
    (void)fwd53;
    (void)rcode;
    if (proxy_ip == NULL || proxy_ip[0] == '\0') {
        return -3;
    }
    if (proxy_port <= 0 || proxy_port > 65535) {
        return -4;
    }
    return 0;
}

int ps_t2h_android_stop(void* jni_env, void* java_instance, int tun_fd) {
    (void)jni_env;
    (void)java_instance;
    (void)tun_fd;
    return 0;
}

int ps_t2h_android_get_mtu(void* jni_env, void* java_instance) {
    (void)jni_env;
    (void)java_instance;
    return 1500;
}

int ps_t2h_android_done(void* jni_env, void* java_instance) {
    (void)jni_env;
    (void)java_instance;
    return 0;
}
