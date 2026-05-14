#ifndef TEST_COMMON_H
#define TEST_COMMON_H

#include <stdio.h>

#define ASSERT_TRUE(expr) do { \
    if (!(expr)) { \
        fprintf(stderr, "ASSERT_TRUE failed: %s (%s:%d)\n", #expr, __FILE__, __LINE__); \
        return 1; \
    } \
} while (0)

#define ASSERT_EQ_INT(a, b) do { \
    int _va = (int)(a); \
    int _vb = (int)(b); \
    if (_va != _vb) { \
        fprintf(stderr, "ASSERT_EQ_INT failed: %s=%d, %s=%d (%s:%d)\n", #a, _va, #b, _vb, __FILE__, __LINE__); \
        return 1; \
    } \
} while (0)

#define ASSERT_STR_EQ(a, b) do { \
    const char *_sa = (a); \
    const char *_sb = (b); \
    if (((_sa) == NULL && (_sb) != NULL) || ((_sa) != NULL && (_sb) == NULL) || ((_sa) && (_sb) && strcmp(_sa, _sb) != 0)) { \
        fprintf(stderr, "ASSERT_STR_EQ failed: %s='%s', %s='%s' (%s:%d)\n", #a, (_sa ? _sa : "(null)"), #b, (_sb ? _sb : "(null)"), __FILE__, __LINE__); \
        return 1; \
    } \
} while (0)

#endif
