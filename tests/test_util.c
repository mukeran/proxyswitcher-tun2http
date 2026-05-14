#include "test_common.h"
#include "tun2http.h"

#ifdef UNIT_TEST
int compare_u32(uint32_t s1, uint32_t s2) {
    if (s1 == s2) {
        return 0;
    }
    {
        int i1 = (int)s1;
        int i2 = (int)s2;
        if ((i1 < i2 && i2 - i1 < 0x7FFFFFFF) ||
            (i1 > i2 && i1 - i2 > 0x7FFFFFFF)) {
            return -1;
        }
    }
    return 1;
}
#endif

int test_compare_u32(void) {
    ASSERT_EQ_INT(compare_u32(10u, 10u), 0);
    ASSERT_EQ_INT(compare_u32(10u, 11u), -1);
    ASSERT_EQ_INT(compare_u32(11u, 10u), 1);

    /* RFC1982 wrap-around ordering checks */
    ASSERT_EQ_INT(compare_u32(0xFFFFFFFFu, 0u), -1);
    ASSERT_EQ_INT(compare_u32(0u, 0xFFFFFFFFu), 1);
    ASSERT_EQ_INT(compare_u32(0x7FFFFFFFu, 0u), 1);
    ASSERT_EQ_INT(compare_u32(0u, 0x7FFFFFFFu), 1);
    return 0;
}
