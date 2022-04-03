#include <gtest/gtest.h>

#include "test_utils.hpp"
#include "custom_exceptions.hpp"
#include "arithmetic_operation.hpp"

TEST(arithmetic_operation, add_test)
{
    EXPECT_EQ(arithm_op::add("0", "0"), "0");
    EXPECT_EQ(arithm_op::add("-0", "0"), "0");
    EXPECT_EQ(arithm_op::add("0", "-0"), "0");
    EXPECT_EQ(arithm_op::add("-0", "-0"), "0");
    EXPECT_EQ(arithm_op::add("0000000000", "00000000"), "0");
    EXPECT_EQ(arithm_op::add("000000000000001", "0000000040000"), "40001");
    EXPECT_EQ(arithm_op::add("0", "84"), "84");
    EXPECT_EQ(arithm_op::add("3323232", "000"), "3323232");
    EXPECT_EQ(arithm_op::add("0012", "034"), "46");
    EXPECT_EQ(arithm_op::add("00100", "003500"), "3600");
    EXPECT_EQ(arithm_op::add("42", "84"), "126");
    EXPECT_EQ(arithm_op::add("-15", "32"), "17");
    EXPECT_EQ(arithm_op::add("-211", "30"), "-181");
    EXPECT_EQ(arithm_op::add("98765", "-777"), "97988");
    EXPECT_EQ(arithm_op::add("2", "-9"), "-7");
    EXPECT_EQ(arithm_op::add("-14", "-66"), "-80");
    EXPECT_EQ(arithm_op::add("-1", "-4"), "-5");
    EXPECT_EQ(arithm_op::add("-567", "-567"), "-1134");
    EXPECT_EQ(arithm_op::add("384208484", "-978"), "384207506");
    EXPECT_EQ(arithm_op::add("-12345", "768484284824"), "768484272479");
    EXPECT_EQ(arithm_op::add(
        "111111111111111111111111111111", "111111111111111111111111111111"),
              "222222222222222222222222222222");
    EXPECT_EQ(arithm_op::add(
        "7402804084844018084", "00000000033335355535353"),
              "7402837420199553437");
    EXPECT_EQ(arithm_op::add(
        "99999999999999999999999999", "9999999999999999999999"),
              "100009999999999999999999998");
    EXPECT_EQ(arithm_op::add(
        "0000000001333000000000", "4277321908074170"),
              "4278654908074170");
    EXPECT_EQ(arithm_op::add(
        "-703233233028323314949482048024820424", "986838433"),
              "-703233233028323314949482047037981991");
    EXPECT_EQ(arithm_op::add(
        "-93290840284084042", "-23361316893668666786345323232"),
              "-23361316893761957626629407274");
    EXPECT_EQ(arithm_op::add(
        "000000000000000000000000001", "999999999999999999999999999999999990"),
              "999999999999999999999999999999999991");
}

TEST(arithmetic_operation, sub_test)
{
    EXPECT_EQ(arithm_op::sub("0", "0"), "0");
    EXPECT_EQ(arithm_op::sub("-0", "0"), "0");
    EXPECT_EQ(arithm_op::sub("0", "-0"), "0");
    EXPECT_EQ(arithm_op::sub("-0", "-0"), "0");
    EXPECT_EQ(arithm_op::sub("0000000000", "00000000"), "0");
    EXPECT_EQ(arithm_op::sub("000000000000001", "0000000040000"), "-39999");
    EXPECT_EQ(arithm_op::sub("0", "84"), "-84");
    EXPECT_EQ(arithm_op::sub("3323232", "000"), "3323232");
    EXPECT_EQ(arithm_op::sub("0012", "034"), "-22");
    EXPECT_EQ(arithm_op::sub("00100", "003500"), "-3400");
    EXPECT_EQ(arithm_op::sub("42", "84"), "-42");
    EXPECT_EQ(arithm_op::sub("-15", "32"), "-47");
    EXPECT_EQ(arithm_op::sub("-211", "30"), "-241");
    EXPECT_EQ(arithm_op::sub("98765", "-777"), "99542");
    EXPECT_EQ(arithm_op::sub("2", "-9"), "11");
    EXPECT_EQ(arithm_op::sub("-14", "-66"), "52");
    EXPECT_EQ(arithm_op::sub("-1", "-4"), "3");
    EXPECT_EQ(arithm_op::sub("-567", "-567"), "0");
    EXPECT_EQ(arithm_op::sub("384208484", "-978"), "384209462");
    EXPECT_EQ(arithm_op::sub("-12345", "768484284824"), "-768484297169");
    EXPECT_EQ(arithm_op::sub(
        "111111111111111111111111111111", "111111111111111111111111111111"),
              "0");
    EXPECT_EQ(arithm_op::sub(
        "7402804084844018084", "00000000033335355535353"),
              "7402770749488482731");
    EXPECT_EQ(arithm_op::sub(
        "99999999999999999999999999", "9999999999999999999999"),
              "99990000000000000000000000");
    EXPECT_EQ(arithm_op::sub(
        "0000000001333000000000", "4277321908074170"),
              "-4275988908074170");
    EXPECT_EQ(arithm_op::sub(
        "-703233233028323314949482048024820424", "986838433"),
              "-703233233028323314949482049011658857");
    EXPECT_EQ(arithm_op::sub(
        "-93290840284084042", "-23361316893668666786345323232"),
              "23361316893575375946061239190");
    EXPECT_EQ(arithm_op::sub(
        "000000000000000000000000001", "999999999999999999999999999999999990"),
              "-999999999999999999999999999999999989");
}

TEST(arithmetic_operation, mult_test)
{
    EXPECT_EQ(arithm_op::mult("0", "0"), "0");
    EXPECT_EQ(arithm_op::mult("-0", "0"), "0");
    EXPECT_EQ(arithm_op::mult("0", "-0"), "0");
    EXPECT_EQ(arithm_op::mult("-0", "-0"), "0");
    EXPECT_EQ(arithm_op::mult("0000000000", "00000000"), "0");
    EXPECT_EQ(arithm_op::mult("000000000000001", "0000000040000"), "40000");
    EXPECT_EQ(arithm_op::mult("0", "84"), "0");
    EXPECT_EQ(arithm_op::mult("3323232", "000"), "0");
    EXPECT_EQ(arithm_op::mult("0012", "034"), "408");
    EXPECT_EQ(arithm_op::mult("00100", "003500"), "350000");
    EXPECT_EQ(arithm_op::mult("42", "84"), "3528");
    EXPECT_EQ(arithm_op::mult("-15", "32"), "-480");
    EXPECT_EQ(arithm_op::mult("-211", "30"), "-6330");
    EXPECT_EQ(arithm_op::mult("98765", "-777"), "-76740405");
    EXPECT_EQ(arithm_op::mult("2", "-9"), "-18");
    EXPECT_EQ(arithm_op::mult("-14", "-66"), "924");
    EXPECT_EQ(arithm_op::mult("-1", "-4"), "4");
    EXPECT_EQ(arithm_op::mult("-567", "-567"), "321489");
    EXPECT_EQ(arithm_op::mult("384208484", "-978"), "-375755897352");
    EXPECT_EQ(arithm_op::mult("-12345", "768484284824"), "-9486938496152280");
    EXPECT_EQ(arithm_op::mult(
        "111111111111111111111111111111", "111111111111111111111111111111"),
              "12345679012345679012345679012320987654320987654320987654321");
    EXPECT_EQ(arithm_op::mult(
        "7402804084844018084", "00000000033335355535353"),
              "246775106126838837690059433323652");
    EXPECT_EQ(arithm_op::mult(
        "99999999999999999999999999", "9999999999999999999999"),
              "999999999999999999999899990000000000000000000001");
    EXPECT_EQ(arithm_op::mult(
        "0000000001333000000000", "4277321908074170"),
              "5701670103462868610000000000");
    EXPECT_EQ(arithm_op::mult(
        "-703233233028323314949482048024820424", "986838433"),
              "-693977581715194424742112338434444532326555592");
    EXPECT_EQ(arithm_op::mult(
        "-93290840284084042", "-23361316893668666786345323232"),
              "2179396883153117935774534803800924711543063744");
    EXPECT_EQ(arithm_op::mult(
        "000000000000000000000000001", "999999999999999999999999999999999990"),
              "999999999999999999999999999999999990");
}

TEST(arithmetic_operation, div_test)
{
    EXPECT_THROW_MSG(
        arithm_op::div("0", "0"),
        custom_exceptions::arithmetic_error,
        "attempted to divide by zero");
    EXPECT_THROW_MSG(
        arithm_op::div("-0", "0"),
        custom_exceptions::arithmetic_error,
        "attempted to divide by zero");
    EXPECT_THROW_MSG(
        arithm_op::div("0", "-0"),
        custom_exceptions::arithmetic_error,
        "attempted to divide by zero");
    EXPECT_THROW_MSG(
        arithm_op::div("-0", "-0"),
        custom_exceptions::arithmetic_error,
        "attempted to divide by zero");
    EXPECT_THROW_MSG(
        arithm_op::div("0000000000", "00000000"),
        custom_exceptions::arithmetic_error,
        "attempted to divide by zero");
    EXPECT_THROW_MSG(
        arithm_op::div("3323232", "000"),
        custom_exceptions::arithmetic_error,
        "attempted to divide by zero");
    EXPECT_THROW_MSG(
        arithm_op::div("-99999999", "000"),
        custom_exceptions::arithmetic_error,
        "attempted to divide by zero");
    EXPECT_THROW_MSG(
        arithm_op::div("4142424", "-000000"),
        custom_exceptions::arithmetic_error,
        "attempted to divide by zero");
    EXPECT_THROW_MSG(
        arithm_op::div("-12345", "-000000"),
        custom_exceptions::arithmetic_error,
        "attempted to divide by zero");

    EXPECT_EQ(arithm_op::div("000000000000001", "-0000000040000"), "0");
    EXPECT_EQ(arithm_op::div("84", "17"), "4");
    EXPECT_EQ(arithm_op::div("009", "00001"), "9");
    EXPECT_EQ(arithm_op::div("-003500", "0020000"), "0");
    EXPECT_EQ(arithm_op::div("321", "84"), "3");
    EXPECT_EQ(arithm_op::div("-87", "2"), "-43");
    EXPECT_EQ(arithm_op::div("-211", "30"), "-7");
    EXPECT_EQ(arithm_op::div("98765", "-777"), "-127");
    EXPECT_EQ(arithm_op::div("9", "-2"), "-4");
    EXPECT_EQ(arithm_op::div("-312", "-14"), "22");
    EXPECT_EQ(arithm_op::div("-1", "1"), "-1");
    EXPECT_EQ(arithm_op::div("-567", "-567"), "1");
    EXPECT_EQ(arithm_op::div("-12", "-42"), "0");
    EXPECT_EQ(arithm_op::div("384208484", "-978"), "-392851");
    EXPECT_EQ(arithm_op::div("-768484284824", "12345"), "-62250650");
    EXPECT_EQ(arithm_op::div(
        "111111111111111111111111111111", "111111111111111111111111111111"),
              "1");
    EXPECT_EQ(arithm_op::div(
        "7402804084844018084", "00000000033335355535353"),
              "222070");
    EXPECT_EQ(arithm_op::div(
        "99999999999999999999999999", "9999999999999999999999"),
              "10000");
    EXPECT_EQ(arithm_op::div(
        "4277321908074170", "0000000001333000000000"),
              "3208");
    EXPECT_EQ(arithm_op::div(
        "-703233233028323314949482048024820424", "986838433"),
              "-712612327927365304538642799");
    EXPECT_EQ(arithm_op::div(
        "-23361316893668666786345323232", "-93290840284084042"),
              "250413832939");
    EXPECT_EQ(arithm_op::div(
        "999999999999999999999999999999999990", "000000000000000000000000001"),
              "999999999999999999999999999999999990");
    EXPECT_EQ(arithm_op::div(
        "1354805640061660168348427617441528359717658213075920", "6"),
              "225800940010276694724737936240254726619609702179320");
}

TEST(arithmetic_operation, mod_test)
{
    EXPECT_THROW_MSG(
        arithm_op::mod("0", "0"),
        custom_exceptions::arithmetic_error,
        "attempted to modulo by zero");
    EXPECT_THROW_MSG(
        arithm_op::mod("-0", "0"),
        custom_exceptions::arithmetic_error,
        "attempted to modulo by zero");
    EXPECT_THROW_MSG(
        arithm_op::mod("0", "-0"),
        custom_exceptions::arithmetic_error,
        "attempted to modulo by zero");
    EXPECT_THROW_MSG(
        arithm_op::mod("-0", "-0"),
        custom_exceptions::arithmetic_error,
        "attempted to modulo by zero");
    EXPECT_THROW_MSG(
        arithm_op::mod("0000000000", "00000000"),
        custom_exceptions::arithmetic_error,
        "attempted to modulo by zero");
    EXPECT_THROW_MSG(
        arithm_op::mod("3323232", "000"),
        custom_exceptions::arithmetic_error,
        "attempted to modulo by zero");
    EXPECT_THROW_MSG(
        arithm_op::mod("-99999999", "000"),
        custom_exceptions::arithmetic_error,
        "attempted to modulo by zero");
    EXPECT_THROW_MSG(
        arithm_op::mod("4142424", "-000000"),
        custom_exceptions::arithmetic_error,
        "attempted to modulo by zero");
    EXPECT_THROW_MSG(
        arithm_op::mod("-12345", "-000000"),
        custom_exceptions::arithmetic_error,
        "attempted to modulo by zero");

    EXPECT_EQ(arithm_op::mod("000000000000001", "-0000000040000"), "1");
    EXPECT_EQ(arithm_op::mod("84", "17"), "16");
    EXPECT_EQ(arithm_op::mod("009", "00001"), "0");
    EXPECT_EQ(arithm_op::mod("-003500", "0020000"), "-3500");
    EXPECT_EQ(arithm_op::mod("321", "84"), "69");
    EXPECT_EQ(arithm_op::mod("-87", "2"), "-1");
    EXPECT_EQ(arithm_op::mod("-211", "30"), "-1");
    EXPECT_EQ(arithm_op::mod("98765", "-777"), "86");
    EXPECT_EQ(arithm_op::mod("9", "-2"), "1");
    EXPECT_EQ(arithm_op::mod("-312", "-14"), "-4");
    EXPECT_EQ(arithm_op::mod("-1", "1"), "0");
    EXPECT_EQ(arithm_op::mod("-567", "-567"), "0");
    EXPECT_EQ(arithm_op::mod("-12", "-42"), "-12");
    EXPECT_EQ(arithm_op::mod("384208484", "-978"), "206");
    EXPECT_EQ(arithm_op::mod("-768484284824", "12345"), "-10574");
    EXPECT_EQ(arithm_op::mod(
        "111111111111111111111111111111", "111111111111111111111111111111"),
              "0");
    EXPECT_EQ(arithm_op::mod(
        "7402804084844018084", "00000000033335355535353"),
              "21681108177374");
    EXPECT_EQ(arithm_op::mod(
        "99999999999999999999999999", "9999999999999999999999"),
              "9999");
    EXPECT_EQ(arithm_op::mod(
        "4277321908074170", "0000000001333000000000"),
              "1057908074170");
    EXPECT_EQ(arithm_op::mod(
        "-703233233028323314949482048024820424", "986838433"),
              "-312926457");
    EXPECT_EQ(arithm_op::mod(
        "-23361316893668666786345323232", "-93290840284084042"),
              "-31114192321463794");
    EXPECT_EQ(arithm_op::mod(
        "999999999999999999999999999999999990", "000000000000000000000000001"),
              "0");
    EXPECT_EQ(arithm_op::mod(
        "1354805640061660168348427617441528359717658213075920", "6"),
              "0");
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
