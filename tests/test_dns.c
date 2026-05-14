#include <arpa/inet.h>
#include <stdint.h>
#include <string.h>

#include "test_common.h"
#include "tun2http.h"

static size_t build_dns_query(uint8_t *buf, size_t cap, const char *domain, uint16_t qtype, uint16_t qclass) {
    if (cap < sizeof(struct dns_header) + 32) {
        return 0;
    }

    memset(buf, 0, cap);
    struct dns_header *hdr = (struct dns_header *)buf;
    hdr->id = htons(0x1234);
    hdr->qr = 0;
    hdr->opcode = 0;
    hdr->rd = 1;
    hdr->q_count = htons(1);

    size_t off = sizeof(struct dns_header);
    const char *p = domain;
    while (*p != '\0') {
        const char *dot = strchr(p, '.');
        size_t len = dot ? (size_t)(dot - p) : strlen(p);
        if (len == 0 || len > 63 || off + 1 + len >= cap) {
            return 0;
        }
        buf[off++] = (uint8_t)len;
        memcpy(buf + off, p, len);
        off += len;
        if (!dot) {
            break;
        }
        p = dot + 1;
    }
    if (off + 1 + 4 > cap) {
        return 0;
    }
    buf[off++] = 0;
    *((uint16_t *)(buf + off)) = htons(qtype);
    off += 2;
    *((uint16_t *)(buf + off)) = htons(qclass);
    off += 2;
    return off;
}

int test_dns_query(void) {
    uint8_t packet[512];
    char qname[DNS_QNAME_MAX + 1];
    uint16_t qtype = 0;
    uint16_t qclass = 0;
    struct arguments args;
    struct udp_session udp;
    memset(&args, 0, sizeof(args));
    memset(&udp, 0, sizeof(udp));

    size_t len = build_dns_query(packet, sizeof(packet), "www.example.com", DNS_QTYPE_A, DNS_QCLASS_IN);
    ASSERT_TRUE(len > 0);
    ASSERT_EQ_INT(get_dns_query(&args, &udp, packet, len, &qtype, &qclass, qname), 0);
    ASSERT_STR_EQ(qname, "www.example.com");
    ASSERT_EQ_INT(qtype, DNS_QTYPE_A);
    ASSERT_EQ_INT(qclass, DNS_QCLASS_IN);

    packet[2] = 0x81; /* qr=1 response */
    ASSERT_EQ_INT(get_dns_query(&args, &udp, packet, len, &qtype, &qclass, qname), -1);
    packet[2] = 0x01; /* restore query rd=1 */

    ASSERT_EQ_INT(get_dns_query(&args, &udp, packet, sizeof(struct dns_header), &qtype, &qclass, qname), -1);

    return 0;
}
