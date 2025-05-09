#include <argparse.hpp>
#include <gtest/gtest.h>

TEST(some, simple) {
    EXPECT_EQ(1, 1);
}
int main(){
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();   
}