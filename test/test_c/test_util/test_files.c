#include <util/files.h>

#include <utest.h>
#include <unistd.h>
#include <stdio.h>

UTEST_TEST_CASE(exists){
    EXPECT_TRUE(exists("."));
    EXPECT_FALSE(exists("nonexistent"));

    char current_dir[512];
    char current_dir_const[64];

    EXPECT_NOT_NULL(getcwd(current_dir, sizeof(current_dir)));
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
UTEST_TEST_CASE(directory){
    EXPECT_FALSE(exists("temp"));
    EXPECT_TRUE(create_directory("temp"));
    EXPECT_TRUE(exists("temp"));
    EXPECT_TRUE(remove_directory("temp"));
    EXPECT_FALSE(exists("temp"));
}
UTEST_TEST_CASE(file){
    EXPECT_FALSE(exists("temp.txt"));
    EXPECT_TRUE(create_file("temp.txt"));
    EXPECT_TRUE(exists("temp.txt"));
    EXPECT_TRUE(remove_file("temp.txt"));
    EXPECT_FALSE(exists("temp.txt"));
}
UTEST_TEST_CASE(is_directory){
    EXPECT_TRUE(is_directory("."));
    EXPECT_FALSE(is_directory("nonexistent"));

    EXPECT_TRUE(create_directory("temp"));
    EXPECT_TRUE(is_directory("temp"));
    EXPECT_TRUE(remove_directory("temp"));

    EXPECT_TRUE(create_file("temp.txt"));
    EXPECT_FALSE(is_directory("temp.txt"));
    EXPECT_TRUE(remove_file("temp.txt"));

    EXPECT_TRUE(create_directory("temp"));
    EXPECT_TRUE(create_file("temp/temp.txt"));
    EXPECT_TRUE(is_directory("temp"));
    EXPECT_TRUE(remove_directory("temp"));
}
UTEST_TEST_SUITE(files){
    UTEST_RUN_TEST_CASE(exists);
    UTEST_RUN_TEST_CASE(directory);
    UTEST_RUN_TEST_CASE(file);
}