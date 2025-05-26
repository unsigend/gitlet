#include <util/files.h>

#include <utest.h>
#include <unistd.h>
#include <stdio.h>

UTEST_TEST_CASE(exists){
    EXPECT_TRUE(exists("."));
    EXPECT_FALSE(exists("nonexistent"));

    char current_dir[512];
    char current_dir_const[64];

    getcwd(current_dir, sizeof(current_dir));
    strcpy(current_dir_const, current_dir);
    const size_t current_dir_len = strlen(current_dir_const);

    EXPECT_TRUE(exists(current_dir));
    EXPECT_TRUE(exists(current_dir_const));

    sprintf(current_dir + current_dir_len, "/test_c");
    EXPECT_TRUE(exists(current_dir));
    strcpy(current_dir, current_dir_const);

    sprintf(current_dir + current_dir_len, "/test_c/test_util");
    EXPECT_TRUE(exists(current_dir));
    strcpy(current_dir, current_dir_const);

    sprintf(current_dir + current_dir_len, "/test_c/test_util/test_files.c");
    EXPECT_TRUE(exists(current_dir));
    strcpy(current_dir, current_dir_const);

    sprintf(current_dir + current_dir_len, "/test_python");
    EXPECT_TRUE(exists(current_dir));
    strcpy(current_dir, current_dir_const);

    sprintf(current_dir + current_dir_len, "/utest");
    EXPECT_TRUE(exists(current_dir));
    strcpy(current_dir, current_dir_const);

    sprintf(current_dir + current_dir_len, "/utest/include");
    EXPECT_TRUE(exists(current_dir));
    strcpy(current_dir, current_dir_const);

    sprintf(current_dir + current_dir_len, "/utest/src");
    EXPECT_TRUE(exists(current_dir));
    strcpy(current_dir, current_dir_const);

    sprintf(current_dir + current_dir_len, "/Makefile");
    EXPECT_TRUE(exists(current_dir));
    memset(current_dir, 0, sizeof(current_dir));
}

UTEST_TEST_SUITE(files){
    UTEST_RUN_TEST_CASE(exists);
}