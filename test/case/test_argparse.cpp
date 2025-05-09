#include <gtest/gtest.h>
#include <argparse/argparse.hpp>

TEST(ArgparseTest, add_option) {
    argparse::Parser parser(1, nullptr, "test", "description");
    EXPECT_THROW(parser.add_option("a", "all", argparse::Parser::required_argument),
    std::invalid_argument);
    EXPECT_NO_THROW(parser.add_option("-a", "all", argparse::Parser::required_argument));
    EXPECT_THROW(parser.add_option("-a", "-b","all", argparse::Parser::required_argument),
    std::invalid_argument);
}

TEST(ArgparseTest, has_option) {
    argparse::Parser parser(1, nullptr, "test", "description");
    EXPECT_FALSE(parser.has_option("-a"));
    EXPECT_NO_THROW(parser.add_option("-a", "all", argparse::Parser::required_argument));
    EXPECT_TRUE(parser.has_option("-a"));
    EXPECT_NO_THROW(parser.add_option("-b", "all", argparse::Parser::required_argument));
    EXPECT_NO_THROW(parser.add_option("-c", "all", argparse::Parser::required_argument));
    EXPECT_NO_THROW(parser.add_option("-d", "all", argparse::Parser::required_argument));
    EXPECT_TRUE(parser.has_option("-b"));
    EXPECT_TRUE(parser.has_option("-c"));
    EXPECT_TRUE(parser.has_option("-d"));
    EXPECT_FALSE(parser.has_option("-e"));
    EXPECT_FALSE(parser.has_option("-f"));
    EXPECT_FALSE(parser.has_option("-g"));

}