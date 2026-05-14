#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int test_compare_u32(void);
int test_dns_query(void);
int test_http_parser(void);

static int run_test(const char *name, int (*fn)(void)) {
    int rc = fn();
    if (rc != 0) {
        fprintf(stderr, "[FAIL] %s\n", name);
        return 1;
    }
    fprintf(stdout, "[PASS] %s\n", name);
    return 0;
}

int main(void) {
    int failed = 0;
    failed += run_test("compare_u32", test_compare_u32);
    failed += run_test("dns_query", test_dns_query);
    failed += run_test("http_parser", test_http_parser);

    if (failed != 0) {
        fprintf(stderr, "Tests failed: %d\n", failed);
        return 1;
    }
    fprintf(stdout, "All tests passed.\n");
    return 0;
}
