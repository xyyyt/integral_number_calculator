#include <gtest/gtest.h>

#include "test_utils.hpp"
#include "custom_exceptions.hpp"
#include "arithmetic_expression_parser.hpp"

TEST(arithmetic_expression_parser, is_arithmetic_expression_test)
{
    EXPECT_NO_THROW(parser::is_arithmetic_expression(
        "7"));
    EXPECT_NO_THROW(parser::is_arithmetic_expression(
        "-21"));
    EXPECT_NO_THROW(parser::is_arithmetic_expression(
        "(766)"));
    EXPECT_NO_THROW(parser::is_arithmetic_expression(
        "(-42)"));
    EXPECT_NO_THROW(parser::is_arithmetic_expression(
        "(\t\t-352\t\t)"));
    EXPECT_NO_THROW(parser::is_arithmetic_expression(
        "((((99999999999999999999))))"));
    EXPECT_NO_THROW(parser::is_arithmetic_expression(
        "((((((((((-000001234567890000))))))))))"));
    EXPECT_NO_THROW(parser::is_arithmetic_expression(
        "95 -   32"));
    EXPECT_NO_THROW(parser::is_arithmetic_expression(
        "  0 - -0"));
    EXPECT_NO_THROW(parser::is_arithmetic_expression(
        "-52 --52"));
    EXPECT_NO_THROW(parser::is_arithmetic_expression(
        "-532 -  \t-194"));
    EXPECT_NO_THROW(parser::is_arithmetic_expression(
        "  80 / -50   "));
    EXPECT_NO_THROW(parser::is_arithmetic_expression(
        "\t    -654 % 4"));
    EXPECT_NO_THROW(parser::is_arithmetic_expression(
        "-0-1-2-3-4-5-6"));
    EXPECT_NO_THROW(parser::is_arithmetic_expression(
        "52 * ((52))"));
    EXPECT_NO_THROW(parser::is_arithmetic_expression(
        "(1/0-5) + 5"));
    EXPECT_NO_THROW(parser::is_arithmetic_expression(
        " \t   \t  (-5) / (-42)-99"));
    EXPECT_NO_THROW(parser::is_arithmetic_expression(
        "3 * ((1 + 4)    *6) /42"));
    EXPECT_NO_THROW(parser::is_arithmetic_expression(
        "(12      + 4)"));
    EXPECT_NO_THROW(parser::is_arithmetic_expression(
        "    (5) * ((((8 -    3))))"));
    EXPECT_NO_THROW(parser::is_arithmetic_expression(
        "5*(8-3)*3+((3-1)*2)/3"));
    EXPECT_NO_THROW(parser::is_arithmetic_expression(
        "   (21+ (42 / 9)-76   % -2)"));
    EXPECT_NO_THROW(parser::is_arithmetic_expression(
        "  \t   \t(((800)))*(1 - 2)     / 43 % 57 + ((32 * 9999) * -42)"));

    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression(""),
        custom_exceptions::parsing_error,
        "empty line");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("\t\t   "),
        custom_exceptions::parsing_error,
        "empty arithmetic expression");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("     "),
        custom_exceptions::parsing_error,
        "empty arithmetic expression");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression(") 2000 ("),
        custom_exceptions::parsing_error,
        "arithmetic expression cannot start with closing parenthesis");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression(" )45  "),
        custom_exceptions::parsing_error,
        "arithmetic expression cannot start with closing parenthesis");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("     +17"),
        custom_exceptions::parsing_error,
        "arithmetic expression cannot start with operator");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("- 9999    \t"),
        custom_exceptions::parsing_error,
        "arithmetic expression cannot start with operator");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("*32    "),
        custom_exceptions::parsing_error,
        "arithmetic expression cannot start with operator");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("   / 4"),
        custom_exceptions::parsing_error,
        "arithmetic expression cannot start with operator");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("% 87"),
        custom_exceptions::parsing_error,
        "arithmetic expression cannot start with operator");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("a + b"),
        custom_exceptions::parsing_error,
        "arithmetic expression cannot start with unknown character");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("    p12345"),
        custom_exceptions::parsing_error,
        "arithmetic expression cannot start with unknown character");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("\tn000000"),
        custom_exceptions::parsing_error,
        "arithmetic expression cannot start with unknown character");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression(" \t   M16"),
        custom_exceptions::parsing_error,
        "arithmetic expression cannot start with unknown character");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("     42abcd"),
        custom_exceptions::parsing_error,
        "error after number");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("  42  a"),
        custom_exceptions::parsing_error,
        "error after number");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("13 \t   (42)"),
        custom_exceptions::parsing_error,
        "error after number");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("13 13"),
        custom_exceptions::parsing_error,
        "error after number");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("5 +"),
        custom_exceptions::parsing_error,
        "arithmetic expression cannot end with operator");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("5 \t-"),
        custom_exceptions::parsing_error,
        "arithmetic expression cannot end with operator");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("    5     *"),
        custom_exceptions::parsing_error,
        "arithmetic expression cannot end with operator");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("   (5)/"),
        custom_exceptions::parsing_error,
        "arithmetic expression cannot end with operator");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("       5 %"),
        custom_exceptions::parsing_error,
        "arithmetic expression cannot end with operator");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("  5 +)"),
        custom_exceptions::parsing_error,
        "error after operator");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("5 -/"),
        custom_exceptions::parsing_error,
        "error after operator");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("5 **"),
        custom_exceptions::parsing_error,
        "error after operator");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("5 /   )"),
        custom_exceptions::parsing_error,
        "error after operator");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression(" 5 %   % 5"),
        custom_exceptions::parsing_error,
        "error after operator");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("2---2"),
        custom_exceptions::parsing_error,
        "error after operator");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("3 *(5) + --42"),
        custom_exceptions::parsing_error,
        "error after operator");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("("),
        custom_exceptions::parsing_error,
        "arithmetic expression cannot end with opening parenthesis");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("   4/5   *("),
        custom_exceptions::parsing_error,
        "arithmetic expression cannot end with opening parenthesis");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression(" 4 / 2 %(+"),
        custom_exceptions::parsing_error,
        "error after opening parenthesis");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("\t9+2/(   -"),
        custom_exceptions::parsing_error,
        "error after opening parenthesis");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("(**)"),
        custom_exceptions::parsing_error,
        "error after opening parenthesis");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("12 )"),
        custom_exceptions::parsing_error,
        "missing opening parenthesis");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("((4 + 2) ) )"),
        custom_exceptions::parsing_error,
        "missing opening parenthesis");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression(" ((((1))))))))"),
        custom_exceptions::parsing_error,
        "missing opening parenthesis");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("  (1)  42"),
        custom_exceptions::parsing_error,
        "error after closing parenthesis");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("(1 * 3) 5"),
        custom_exceptions::parsing_error,
        "error after closing parenthesis");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("(((5)))          3333"),
        custom_exceptions::parsing_error,
        "error after closing parenthesis");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("((12"),
        custom_exceptions::parsing_error,
        "missing closing parenthesis");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("1 * ((2+3) * 4"),
        custom_exceptions::parsing_error,
        "missing closing parenthesis");
    EXPECT_THROW_MSG(
        parser::is_arithmetic_expression("(12 + 3) / (3 + 5"),
        custom_exceptions::parsing_error,
        "missing closing parenthesis");
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
