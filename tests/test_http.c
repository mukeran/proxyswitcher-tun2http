#include <stdint.h>
#include <string.h>

#include "test_common.h"
#include "tun2http.h"

int get_header(const char *header, const char *data, size_t data_len, char *value);
int next_header(const char **data, size_t *len);
uint8_t *find_data(uint8_t *data, size_t data_len, char *value);

int test_http_parser(void) {
    const char *req =
            "GET /index.html HTTP/1.1\r\n"
            "Host: Example.COM\r\n"
            "User-Agent: test\r\n"
            "\r\n";

    char host[256];
    memset(host, 0, sizeof(host));
    int host_len = get_header("Host:", req, strlen(req), host);
    ASSERT_TRUE(host_len > 0);
    ASSERT_STR_EQ(host, "Example.COM");

    const char *p = req;
    size_t rem = strlen(req);
    int l1 = next_header(&p, &rem); /* request line */
    ASSERT_TRUE(l1 > 0);
    int l2 = next_header(&p, &rem); /* Host */
    ASSERT_TRUE(l2 > 0);

    uint8_t *m = find_data((uint8_t *)req, strlen(req), "Host: ");
    ASSERT_TRUE(m != NULL);
    ASSERT_TRUE(strncmp((char *)m, "Host: Example.COM", 17) == 0);

    {
        const char *incomplete = "GET / HTTP/1.1\r\nUser-Agent: missing-end";
        ASSERT_EQ_INT(get_header("Host:", incomplete, strlen(incomplete), host), -1);
    }

    {
        const char *nohost =
                "GET / HTTP/1.1\r\n"
                "User-Agent: x\r\n"
                "\r\n";
        ASSERT_EQ_INT(get_header("Host:", nohost, strlen(nohost), host), -2);
    }

    return 0;
}
