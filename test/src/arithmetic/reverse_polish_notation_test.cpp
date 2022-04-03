#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "reverse_polish_notation.hpp"

using testing::ElementsAre;
using testing::Return;
using testing::InSequence;
using testing::StrictMock;
using testing::Mock;

TEST(reverse_polish_notation, to_rpn_test)
{
    std::list<std::string_view> rpn_expression;

    rpn_expression = rpn::to_rpn("0");
    EXPECT_EQ(rpn_expression.size(), 1u);
    EXPECT_THAT(rpn_expression, ElementsAre("0"));

    rpn_expression = rpn::to_rpn("-0");
    EXPECT_EQ(rpn_expression.size(), 1u);
    EXPECT_THAT(rpn_expression, ElementsAre("-0"));

    rpn_expression = rpn::to_rpn("95");
    EXPECT_EQ(rpn_expression.size(), 1u);
    EXPECT_THAT(rpn_expression, ElementsAre("95"));

    rpn_expression = rpn::to_rpn("-42");
    EXPECT_EQ(rpn_expression.size(), 1u);
    EXPECT_THAT(rpn_expression, ElementsAre("-42"));

    rpn_expression = rpn::to_rpn("000004121300");
    EXPECT_EQ(rpn_expression.size(), 1u);
    EXPECT_THAT(rpn_expression, ElementsAre("000004121300"));

    rpn_expression = rpn::to_rpn("-00954");
    EXPECT_EQ(rpn_expression.size(), 1u);
    EXPECT_THAT(rpn_expression, ElementsAre("-00954"));

    rpn_expression = rpn::to_rpn("123000");
    EXPECT_EQ(rpn_expression.size(), 1u);
    EXPECT_THAT(rpn_expression, ElementsAre("123000"));

    rpn_expression = rpn::to_rpn("((((\t99999999999999999999\t))))");
    EXPECT_EQ(rpn_expression.size(), 1u);
    EXPECT_THAT(rpn_expression, ElementsAre("99999999999999999999"));

    rpn_expression = rpn::to_rpn("2+-3");
    EXPECT_EQ(rpn_expression.size(), 3u);
    EXPECT_THAT(rpn_expression, ElementsAre("2", "-3", "+"));

    rpn_expression = rpn::to_rpn("32--32");
    EXPECT_EQ(rpn_expression.size(), 3u);
    EXPECT_THAT(rpn_expression, ElementsAre("32", "-32", "-"));

    rpn_expression = rpn::to_rpn("   \t-42 \t--42");
    EXPECT_EQ(rpn_expression.size(), 3u);
    EXPECT_THAT(rpn_expression, ElementsAre("-42", "-42", "-"));

    rpn_expression = rpn::to_rpn("    ((9)) *-31\t  ");
    EXPECT_EQ(rpn_expression.size(), 3u);
    EXPECT_THAT(rpn_expression, ElementsAre("9", "-31", "*"));

    rpn_expression = rpn::to_rpn("9555 -   32");
    EXPECT_EQ(rpn_expression.size(), 3u);
    EXPECT_THAT(rpn_expression, ElementsAre("9555", "32", "-"));

    rpn_expression = rpn::to_rpn("2 + 6 - 1");
    EXPECT_EQ(rpn_expression.size(), 5u);
    EXPECT_THAT(rpn_expression, ElementsAre("2", "6", "+", "1", "-"));

    rpn_expression = rpn::to_rpn("5   *   3 + 4 \t");
    EXPECT_EQ(rpn_expression.size(), 5u);
    EXPECT_THAT(rpn_expression, ElementsAre("5", "3", "*", "4", "+"));

    rpn_expression = rpn::to_rpn(" \t   \t  (-5) / (-42)-99");
    EXPECT_EQ(rpn_expression.size(), 5u);
    EXPECT_THAT(rpn_expression, ElementsAre("-5", "-42", "/", "99", "-"));

    rpn_expression = rpn::to_rpn("   ((1+2) * 4)   + 3");
    EXPECT_EQ(rpn_expression.size(), 7u);
    EXPECT_THAT(rpn_expression, ElementsAre("1", "2", "+", "4", "*",
                                            "3", "+"));

    rpn_expression = rpn::to_rpn("(5/3)    + (((5 * 9)))%42");
    EXPECT_EQ(rpn_expression.size(), 9u);
    EXPECT_THAT(rpn_expression, ElementsAre("5", "3", "/", "5", "9", "*", "42",
                                            "%", "+"));

    rpn_expression = rpn::to_rpn("((((14/42\t)+95    )))    %42*84");
    EXPECT_EQ(rpn_expression.size(), 9u);
    EXPECT_THAT(rpn_expression, ElementsAre("14", "42", "/", "95", "+", "42",
                                            "%", "84", "*"));

    rpn_expression = rpn::to_rpn("4242 % 4242 +  (   50 -  50  \t) / 50 -9");
    EXPECT_EQ(rpn_expression.size(), 11u);
    EXPECT_THAT(rpn_expression, ElementsAre("4242", "4242", "%", "50",
                                            "50", "-", "50", "/", "+", "9",
                                            "-"));

    rpn_expression = rpn::to_rpn("    -6 -18 *    4 % 10 + (-5 - -9) * -42");
    EXPECT_EQ(rpn_expression.size(), 13u);
    EXPECT_THAT(rpn_expression, ElementsAre("-6", "18", "4", "*", "10",
                                            "%", "-", "-5", "-9", "-",
                                            "-42", "*", "+"));

    rpn_expression = rpn::to_rpn("5*(8-3)*3+((3-1)*2)/3");
    EXPECT_EQ(rpn_expression.size(), 15u);
    EXPECT_THAT(rpn_expression, ElementsAre("5", "8", "3", "-", "*", "3", "*",
                                            "3", "1", "-", "2", "*", "3",
                                            "/", "+"));

}

TEST(reverse_polish_notation, rpn_evaluate_test)
{
    using namespace std::string_view_literals;

    struct arithmetic_operations
    {
        MOCK_CONST_METHOD2(add, std::string(
            std::string_view s, std::string_view s2));
        MOCK_CONST_METHOD2(sub, std::string(
            std::string_view s, std::string_view s2));
        MOCK_CONST_METHOD2(mult, std::string(
            std::string_view s, std::string_view s2));
        MOCK_CONST_METHOD2(div, std::string(
            std::string_view s, std::string_view s2));
        MOCK_CONST_METHOD2(mod, std::string(
            std::string_view s, std::string_view s2));
    };


    StrictMock<arithmetic_operations> mock_operations;

    EXPECT_EQ(
        rpn::rpn_evaluate(mock_operations, {"0"}), "0");
    EXPECT_EQ(
        rpn::rpn_evaluate(mock_operations, {"-0"}), "0");
    EXPECT_EQ(
        rpn::rpn_evaluate(mock_operations, {"95"}), "95");
    EXPECT_EQ(
        rpn::rpn_evaluate(mock_operations, {"-42"}), "-42");
    EXPECT_EQ(
        rpn::rpn_evaluate(mock_operations, {"000004121300"}), "4121300");
    EXPECT_EQ(
        rpn::rpn_evaluate(mock_operations, {"-00954"}), "-954");
    EXPECT_EQ(
        rpn::rpn_evaluate(mock_operations, {"123000"}), "123000");
    EXPECT_EQ(
        rpn::rpn_evaluate(mock_operations, {"99999999999999999999"}),
        "99999999999999999999");

    {
        EXPECT_CALL(mock_operations, add("2"sv, "-3"sv))
            .Times(1).WillRepeatedly(Return("-1"));
        EXPECT_EQ(
            rpn::rpn_evaluate(mock_operations, {"2", "-3", "+"}), "-1");
        Mock::VerifyAndClearExpectations(&mock_operations);
    }

    {
        EXPECT_CALL(mock_operations, sub("32"sv, "-32"sv))
            .Times(1).WillRepeatedly(Return("64"));
        EXPECT_EQ(
            rpn::rpn_evaluate(mock_operations, {"32", "-32", "-"}), "64");
        Mock::VerifyAndClearExpectations(&mock_operations);
    }

    {
        EXPECT_CALL(mock_operations, sub("-42"sv, "-42"sv))
            .Times(1).WillRepeatedly(Return("0"));
        EXPECT_EQ(
            rpn::rpn_evaluate(mock_operations, {"-42", "-42", "-"}), "0");
        Mock::VerifyAndClearExpectations(&mock_operations);
    }

    {
        EXPECT_CALL(mock_operations, mult("9"sv, "-31"sv))
            .Times(1).WillRepeatedly(Return("-279"));
        EXPECT_EQ(
            rpn::rpn_evaluate(mock_operations, {"9", "-31", "*"}), "-279");
        Mock::VerifyAndClearExpectations(&mock_operations);
    }

    {
        EXPECT_CALL(mock_operations, sub("9555"sv, "32"sv))
            .Times(1).WillRepeatedly(Return("9523"));
        EXPECT_EQ(
            rpn::rpn_evaluate(mock_operations, {"9555", "32", "-"}), "9523");
        Mock::VerifyAndClearExpectations(&mock_operations);
    }

    {
        InSequence s;

        EXPECT_CALL(mock_operations, div("-5"sv, "-42"sv))
            .Times(1).WillRepeatedly(Return("0"));
        EXPECT_CALL(mock_operations, sub("0"sv, "99"sv))
            .Times(1).WillRepeatedly(Return("-99"));
        EXPECT_EQ(
            rpn::rpn_evaluate(mock_operations, {"-5", "-42", "/", "99", "-"}),
            "-99");
        Mock::VerifyAndClearExpectations(&mock_operations);
    }

    {
        InSequence s;

        EXPECT_CALL(mock_operations, mult("5"sv, "3"sv))
            .Times(1).WillRepeatedly(Return("15"));
        EXPECT_CALL(mock_operations, add("15"sv, "4"sv))
            .Times(1).WillRepeatedly(Return("19"));
        EXPECT_EQ(
            rpn::rpn_evaluate(mock_operations, {"5", "3", "*", "4", "+"}),
            "19");
        Mock::VerifyAndClearExpectations(&mock_operations);
    }

    {
        InSequence s;

        EXPECT_CALL(mock_operations, add("1"sv, "2"sv))
            .Times(1).WillRepeatedly(Return("3"));
        EXPECT_CALL(mock_operations, mult("3"sv, "4"sv))
            .Times(1).WillRepeatedly(Return("12"));
        EXPECT_CALL(mock_operations, add("12"sv, "3"sv))
            .Times(1).WillRepeatedly(Return("15"));
        EXPECT_EQ(
            rpn::rpn_evaluate(
                mock_operations, {"1", "2", "+", "4", "*", "3", "+"}),
            "15");
        Mock::VerifyAndClearExpectations(&mock_operations);
    }

    {
        InSequence s;

        EXPECT_CALL(mock_operations, div("5"sv, "3"sv))
            .Times(1).WillRepeatedly(Return("1"));
        EXPECT_CALL(mock_operations, mult("5"sv, "9"sv))
            .Times(1).WillRepeatedly(Return("45"));
        EXPECT_CALL(mock_operations, mod("45"sv, "42"sv))
            .Times(1).WillRepeatedly(Return("3"));
        EXPECT_CALL(mock_operations, add("1"sv, "3"sv))
            .Times(1).WillRepeatedly(Return("4"));
        EXPECT_EQ(
            rpn::rpn_evaluate(
                mock_operations,
                {"5", "3", "/", "5", "9", "*", "42", "%", "+"}),
            "4");
        Mock::VerifyAndClearExpectations(&mock_operations);
    }

    {
        InSequence s;

        EXPECT_CALL(mock_operations, div("14"sv, "42"sv))
            .Times(1).WillRepeatedly(Return("0"));
        EXPECT_CALL(mock_operations, add("0"sv, "95"sv))
            .Times(1).WillRepeatedly(Return("95"));
        EXPECT_CALL(mock_operations, mod("95"sv, "42"sv))
            .Times(1).WillRepeatedly(Return("11"));
        EXPECT_CALL(mock_operations, mult("11"sv, "84"sv))
            .Times(1).WillRepeatedly(Return("924"));
        EXPECT_EQ(
            rpn::rpn_evaluate(
                mock_operations,
                {"14", "42", "/", "95", "+", "42", "%", "84", "*"}),
            "924");
        Mock::VerifyAndClearExpectations(&mock_operations);
    }

    {
        InSequence s;

        EXPECT_CALL(mock_operations, mod("4242"sv, "4242"sv))
            .Times(1).WillRepeatedly(Return("0"));
        EXPECT_CALL(mock_operations, sub("50"sv, "50"sv))
            .Times(1).WillRepeatedly(Return("0"));
        EXPECT_CALL(mock_operations, div("0"sv, "50"sv))
            .Times(1).WillRepeatedly(Return("0"));
        EXPECT_CALL(mock_operations, add("0"sv, "0"sv))
            .Times(1).WillRepeatedly(Return("0"));
        EXPECT_CALL(mock_operations, sub("0"sv, "9"sv))
            .Times(1).WillRepeatedly(Return("-9"));
        EXPECT_EQ(
            rpn::rpn_evaluate(
                mock_operations,
                {"4242", "4242", "%", "50", "50", "-", "50", "/", "+",
                 "9", "-"}),
            "-9");
        Mock::VerifyAndClearExpectations(&mock_operations);
    }

    {
        InSequence s;

        EXPECT_CALL(mock_operations, mult("18"sv, "4"sv))
            .Times(1).WillRepeatedly(Return("72"));
        EXPECT_CALL(mock_operations, mod("72"sv, "10"sv))
            .Times(1).WillRepeatedly(Return("2"));
        EXPECT_CALL(mock_operations, sub("-6"sv, "2"sv))
            .Times(1).WillRepeatedly(Return("-8"));
        EXPECT_CALL(mock_operations, sub("-5"sv, "-9"sv))
            .Times(1).WillRepeatedly(Return("4"));
        EXPECT_CALL(mock_operations, mult("4"sv, "-42"sv))
            .Times(1).WillRepeatedly(Return("-168"));
        EXPECT_CALL(mock_operations, add("-8"sv, "-168"sv))
            .Times(1).WillRepeatedly(Return("-176"));
        EXPECT_EQ(
            rpn::rpn_evaluate(
                mock_operations,
                {"-6", "18", "4", "*", "10", "%", "-", "-5", "-9", "-",
                 "-42", "*", "+"}),
            "-176");
        Mock::VerifyAndClearExpectations(&mock_operations);
    }

    {
        InSequence s;

        EXPECT_CALL(mock_operations, sub("8"sv, "3"sv))
            .Times(1).WillRepeatedly(Return("5"));
        EXPECT_CALL(mock_operations, mult("5"sv, "5"sv))
            .Times(1).WillRepeatedly(Return("25"));
        EXPECT_CALL(mock_operations, mult("25"sv, "3"sv))
            .Times(1).WillRepeatedly(Return("75"));
        EXPECT_CALL(mock_operations, sub("3"sv, "1"sv))
            .Times(1).WillRepeatedly(Return("2"));
        EXPECT_CALL(mock_operations, mult("2"sv, "2"sv))
            .Times(1).WillRepeatedly(Return("4"));
        EXPECT_CALL(mock_operations, div("4"sv, "3"sv))
            .Times(1).WillRepeatedly(Return("1"));
        EXPECT_CALL(mock_operations, add("75"sv, "1"sv))
            .Times(1).WillRepeatedly(Return("76"));
        EXPECT_EQ(
            rpn::rpn_evaluate(
                mock_operations,
                {"5", "8", "3", "-", "*", "3", "*", "3", "1", "-",
                 "2", "*", "3", "/", "+"}),
            "76");
        Mock::VerifyAndClearExpectations(&mock_operations);
    }
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
