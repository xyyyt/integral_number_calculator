#include <gtest/gtest.h>

#include "test_utils.hpp"
#include "custom_exceptions.hpp"
#include "arithmetic_expression_parser.hpp"
#include "arithmetic_operation.hpp"
#include "reverse_polish_notation.hpp"

struct arithmetic_operations
{
    std::string add(std::string_view s, std::string_view s2) const
    {
        return arithm_op::add(s, s2);
    }

    std::string sub(std::string_view s, std::string_view s2) const
    {
        return arithm_op::sub(s, s2);
    }

    std::string mult(std::string_view s, std::string_view s2) const
    {
        return arithm_op::mult(s, s2);
    }

    std::string div(std::string_view s, std::string_view s2) const
    {
        return arithm_op::div(s, s2);
    }

    std::string mod(std::string_view s, std::string_view s2) const
    {
        return arithm_op::mod(s, s2);
    }
};

// Fixture class
class calculate_arithmetic_expression : public testing::Test
{
protected :
    std::string calc_arithmetic_expression(std::string_view line)
    {
        parser::is_arithmetic_expression(line);

        std::list<std::string_view> rpn_expression = rpn::to_rpn(line);

        return rpn::rpn_evaluate(_operations, rpn_expression);
    }

private :
    arithmetic_operations _operations;
};

TEST_F(calculate_arithmetic_expression, test)
{
    EXPECT_EQ(calc_arithmetic_expression("7"), "7");
    EXPECT_EQ(calc_arithmetic_expression("-21"), "-21");
    EXPECT_EQ(calc_arithmetic_expression("(766)"), "766");
    EXPECT_EQ(calc_arithmetic_expression("(-42)"), "-42");
    EXPECT_EQ(calc_arithmetic_expression("(\t\t-352\t\t)"), "-352");
    EXPECT_EQ(
        calc_arithmetic_expression("((((99999999999999999999))))"),
        "99999999999999999999");
    EXPECT_EQ(
        calc_arithmetic_expression("((((((((((-000001234567890000))))))))))"),
        "-1234567890000");
    EXPECT_EQ(calc_arithmetic_expression("95 -   32"), "63");
    EXPECT_EQ(calc_arithmetic_expression("  0 - -0"), "0");
    EXPECT_EQ(calc_arithmetic_expression("-52 --52"), "0");
    EXPECT_EQ(calc_arithmetic_expression("-532 -  \t-194"), "-338");
    EXPECT_EQ(calc_arithmetic_expression("  80 / -50   "), "-1");
    EXPECT_EQ(calc_arithmetic_expression(
        "999999999999999 * 999999999"), "999999998999999000000001");
    EXPECT_EQ(calc_arithmetic_expression(
        "-427429874974123139 - 0000323291881313003"), "-427753166855436142");
    EXPECT_EQ(calc_arithmetic_expression(
        "9913332429474297492749 / 1"), "9913332429474297492749");
    EXPECT_EQ(calc_arithmetic_expression("\t    -654 % 4"), "-2");
    EXPECT_EQ(calc_arithmetic_expression("2 + 6 - 1"), "7");
    EXPECT_EQ(calc_arithmetic_expression("-0-1-2-3-4-5-6"), "-21");
    EXPECT_EQ(calc_arithmetic_expression("  ((1+2) * 4)   + 3"), "15");
    EXPECT_EQ(calc_arithmetic_expression("5   *   3 + 4 \t"), "19");
    EXPECT_EQ(calc_arithmetic_expression("52 * ((52))"), "2704");
    EXPECT_EQ(calc_arithmetic_expression(" \t   \t  (-5) / (-42)-99"), "-99");
    EXPECT_EQ(calc_arithmetic_expression("3 * ((1 + 4)    *6) /42"), "2");
    EXPECT_EQ(calc_arithmetic_expression("(12      + 4)"), "16");
    EXPECT_EQ(calc_arithmetic_expression("(5/3)    + (((5 * 9)))%42"), "4");
    EXPECT_EQ(calc_arithmetic_expression("    (5) * ((((8 -    3))))"), "25");
    EXPECT_EQ(calc_arithmetic_expression("5*(8-3)*3+((3-1)*2)/3"), "76");
    EXPECT_EQ(calc_arithmetic_expression("   (21+ (42 / 9)-76   % -2)"), "25");
    EXPECT_EQ(
        calc_arithmetic_expression("-6 -18 *    4 % 10 + (-5 - -9) * -42"),
        "-176");
    EXPECT_EQ(
        calc_arithmetic_expression("4242 % 4242 +  (   50 -  50  \t) / 50 -9"),
        "-9");
    EXPECT_EQ(
        calc_arithmetic_expression(
            "  \t   \t(((800)))*(1 - 2)     / 43 % 57 + ((32 * 9999) * -42)"),
        "-13438674");
    EXPECT_EQ(
        calc_arithmetic_expression(
            "3 + (5 - 9 * 45225525525) % 12 + 9999999999999999"),
        "9999999999999998");
    EXPECT_EQ(
        calc_arithmetic_expression(
            "111111*22222222*333333333*444444444*55555555555555*66666666"),
        "1354805640061660168348427617441528359717658213075920");
    EXPECT_EQ(
        calc_arithmetic_expression(
            "1354805640061660168348427617441528359717658213075920/   6"),
        "225800940010276694724737936240254726619609702179320");
    EXPECT_EQ(
        calc_arithmetic_expression(
            "3232830238393028330823823038290893203"
            " * 32832382038320832038238298328328323230298303"
            " + 4248240814810984199999999999"
            " * 9999999999999999999"
            " - 131813018310938"),
        "10614151745195571686802724843082080938885503504925437496471045839266"
        "9280986823572");
    EXPECT_EQ(
        calc_arithmetic_expression(
            "-9090792873973739233"
            " + 31312812018242424"
            " * 9993939392192939393"
            " % 355525"
            " * -999999999999999999999999999999"),
        "-239282000000000009090792873973499951");


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
    EXPECT_THROW_MSG(
        calc_arithmetic_expression("(1/0-5) + 5"),
        custom_exceptions::arithmetic_error,
        "attempted to divide by zero");
    EXPECT_THROW_MSG(
        calc_arithmetic_expression("(3523) * -4 /-0"),
        custom_exceptions::arithmetic_error,
        "attempted to divide by zero");
    EXPECT_THROW_MSG(
        calc_arithmetic_expression("13 / 0"),
        custom_exceptions::arithmetic_error,
        "attempted to divide by zero");
    EXPECT_THROW_MSG(
        calc_arithmetic_expression("1+2+3+4+5+6+7/0%0%0/0"),
        custom_exceptions::arithmetic_error,
        "attempted to divide by zero");
    EXPECT_THROW_MSG(
        calc_arithmetic_expression("5555555 * (999999999) * 0 % 0 - 42"),
        custom_exceptions::arithmetic_error,
        "attempted to modulo by zero");
    EXPECT_THROW_MSG(
        calc_arithmetic_expression("((((((42)))))) % 0"),
        custom_exceptions::arithmetic_error,
        "attempted to modulo by zero");
    EXPECT_THROW_MSG(
        calc_arithmetic_expression("-4-6-7-8%-0"),
        custom_exceptions::arithmetic_error,
        "attempted to modulo by zero");
    EXPECT_THROW_MSG(
        calc_arithmetic_expression("3 - 5 * ((((524))))%0 -2367"),
        custom_exceptions::arithmetic_error,
        "attempted to modulo by zero");
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
