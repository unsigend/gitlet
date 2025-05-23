// Test Entry for gitlet library using Utest C Framework

#include <utest.h>

extern UTEST_TEST_SUITE(test_str);

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    UTEST_BEGIN();
    UTEST_CLEAR_FLAG(UTEST_FLAG_STYLE_FULL);

    UTEST_RUN_TEST_SUITE(test_str);

    UTEST_END();

    return 0;
}