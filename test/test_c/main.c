// Test Entry for gitlet library using Utest C Framework

#include <utest.h>

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    UTEST_BEGIN();
    UTEST_CLEAR_FLAG(UTEST_FLAG_STYLE_FULL);

    UTEST_END();

    return 0;
}