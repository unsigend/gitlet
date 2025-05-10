#include <gtest/gtest.h>
#include <argparse/argparse.hpp>

using namespace argparse;
using namespace __argparse__;

TEST(argparse, is_valid_option){
    EXPECT_TRUE(_is_valid_short_option("-a"));
    EXPECT_TRUE(_is_valid_short_option("-b"));
    EXPECT_FALSE(_is_valid_short_option("-ab"));
    EXPECT_FALSE(_is_valid_short_option("a"));
    EXPECT_FALSE(_is_valid_short_option("-aa"));
    EXPECT_FALSE(_is_valid_short_option("-"));
    EXPECT_FALSE(_is_valid_short_option(""));

    EXPECT_TRUE(_is_valid_long_option("--aa"));
    EXPECT_FALSE(_is_valid_long_option("aa"));
    EXPECT_TRUE(_is_valid_long_option("--a"));
    EXPECT_FALSE(_is_valid_long_option("--"));
    EXPECT_TRUE(_is_valid_long_option("--W"));
    EXPECT_TRUE(_is_valid_long_option("--ABC"));
    EXPECT_TRUE(_is_valid_long_option("--Wall"));
}

TEST(argparse, add_option){
    Argparse parser;
    parser.add_option("-a", "--aa", "");
    parser.add_option("--bb", "");
    parser.add_option("-c", "--cc", "", Argparse::argument_type::optional_argument);
    parser.add_option("--dd", "", Argparse::argument_type::no_argument);
    parser.add_option("-e", "--eee", "");
    parser.add_option("-f", "--ffffff", "", Argparse::argument_type::required_argument);

    EXPECT_TRUE(parser.has_option("-a"));
    EXPECT_TRUE(parser.has_option("--aa"));
    EXPECT_TRUE(parser.has_option("--bb"));
    EXPECT_TRUE(parser.has_option("-c"));
    EXPECT_TRUE(parser.has_option("--cc"));
    EXPECT_TRUE(parser.has_option("--dd"));
    EXPECT_TRUE(parser.has_option("-e"));
    EXPECT_TRUE(parser.has_option("--eee"));
    EXPECT_TRUE(parser.has_option("-f"));
    EXPECT_TRUE(parser.has_option("--ffffff"));

    // invalid short option
    EXPECT_THROW(parser.add_option("--a", "--aa", ""), std::invalid_argument);
    EXPECT_THROW(parser.add_option("a", "--bb", ""), std::invalid_argument);
    EXPECT_THROW(parser.add_option("abc", "--bb", ""), std::invalid_argument);
    // invalid long option
    EXPECT_THROW(parser.add_option("-a", "-aa", ""), std::invalid_argument);
    EXPECT_THROW(parser.add_option("-b", "-bbbb", ""), std::invalid_argument);
    EXPECT_THROW(parser.add_option("-b", "b--bbbb", ""), std::invalid_argument);
}