#include <util/str.h>
#include <utest.h>

UTEST_TEST_CASE(str_start_with){
    // Basic cases
    EXPECT_TRUE(str_start_with("hello", "hello"));
    EXPECT_TRUE(str_start_with("hello world", "hello"));
    EXPECT_FALSE(str_start_with("hello", "world"));
    
    // Empty strings
    EXPECT_TRUE(str_start_with("hello", ""));
    EXPECT_FALSE(str_start_with("", "hello"));
    EXPECT_TRUE(str_start_with("", ""));
    
    // Partial matches
    EXPECT_TRUE(str_start_with("hello", "hel"));
    EXPECT_FALSE(str_start_with("hello", "ello"));
    
    // Case sensitivity
    EXPECT_FALSE(str_start_with("Hello", "hello"));
    EXPECT_FALSE(str_start_with("hello", "Hello"));
}

UTEST_TEST_CASE(str_end_with){
    // Basic cases
    EXPECT_TRUE(str_end_with("hello", "hello")); 
    EXPECT_TRUE(str_end_with("world hello", "hello"));
    EXPECT_FALSE(str_end_with("hello", "world"));
    
    // Empty strings
    EXPECT_TRUE(str_end_with("hello", ""));
    EXPECT_FALSE(str_end_with("", "hello"));
    EXPECT_TRUE(str_end_with("", ""));
    
    // Partial matches
    EXPECT_TRUE(str_end_with("hello", "llo"));
    EXPECT_FALSE(str_end_with("hello", "hel"));
    
    // Case sensitivity
    EXPECT_FALSE(str_end_with("Hello", "hello"));
    EXPECT_FALSE(str_end_with("hello", "Hello"));
}

UTEST_TEST_CASE(str_contains){
    // Basic cases
    EXPECT_TRUE(str_contains("hello", "hello"));
    EXPECT_TRUE(str_contains("hello world", "hello"));
    EXPECT_TRUE(str_contains("hello world", "world"));
    EXPECT_FALSE(str_contains("hello", "world"));
    
    // Empty strings
    EXPECT_TRUE(str_contains("hello", ""));
    EXPECT_FALSE(str_contains("", "hello"));
    EXPECT_TRUE(str_contains("", ""));
    
    // Substring in middle
    EXPECT_TRUE(str_contains("hello world", "o w"));
    EXPECT_TRUE(str_contains("abcdef", "cde"));
    
    // Case sensitivity
    EXPECT_FALSE(str_contains("Hello", "hello"));
    EXPECT_FALSE(str_contains("hello", "Hello"));
    
    // Multiple occurrences
    EXPECT_TRUE(str_contains("hello hello", "hello"));
}

UTEST_TEST_CASE(str_equals){
    // Basic cases
    EXPECT_TRUE(str_equals("hello", "hello"));
    EXPECT_FALSE(str_equals("hello", "world"));
    
    // Empty strings
    EXPECT_TRUE(str_equals("", ""));
    EXPECT_FALSE(str_equals("hello", ""));
    EXPECT_FALSE(str_equals("", "hello"));
    
    // Similar strings
    EXPECT_FALSE(str_equals("hello", "hello "));
    EXPECT_FALSE(str_equals("hello ", "hello"));
    
    // Case sensitivity
    EXPECT_FALSE(str_equals("Hello", "hello"));
    EXPECT_FALSE(str_equals("hello", "Hello"));
    
    // Special characters
    EXPECT_TRUE(str_equals("hello\n", "hello\n"));
    EXPECT_TRUE(str_equals("hello\t", "hello\t"));
}


UTEST_TEST_SUITE(str){
    UTEST_RUN_TEST_CASE(str_start_with);
    UTEST_RUN_TEST_CASE(str_end_with);
    UTEST_RUN_TEST_CASE(str_contains);
    UTEST_RUN_TEST_CASE(str_equals);
}
