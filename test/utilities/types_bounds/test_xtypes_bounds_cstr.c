/*!gcc -ansi -pedantic-errors {0} -I. -I../../include/ -I../include/  -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I. -I../../include/ -I../include -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../../include/ -I../include -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../../include/ -I../include -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/xtypes_bounds.h>

CESTER_TEST(xbound_cstr_is_uppercase, _, {
    cester_assert_false(xbound_cstr_is_uppercase("a"));
    cester_assert_true(xbound_cstr_is_uppercase("A"));
    cester_assert_false(xbound_cstr_is_uppercase("LIBxTD"));
    cester_assert_false(xbound_cstr_is_uppercase("libxtd"));
    cester_assert_true(xbound_cstr_is_uppercase("LIBXTD"));
})

CESTER_TEST(xbound_cstr_is_lowercase, _, {
    cester_assert_true(xbound_cstr_is_lowercase("a"));
    cester_assert_false(xbound_cstr_is_lowercase("A"));
    cester_assert_false(xbound_cstr_is_lowercase("LIBxTD"));
    cester_assert_true(xbound_cstr_is_lowercase("libxtd"));
    cester_assert_false(xbound_cstr_is_lowercase("LIBXTD"));
})

CESTER_TEST(xbound_cstr_is_alpha, _, {
    cester_assert_true(xbound_cstr_is_alpha("a"));
    cester_assert_true(xbound_cstr_is_alpha("A"));
    cester_assert_true(xbound_cstr_is_alpha("LIBxTD"));
    cester_assert_true(xbound_cstr_is_alpha("libxtd"));
    cester_assert_true(xbound_cstr_is_alpha("LIBXTD"));
    cester_assert_false(xbound_cstr_is_alpha("12"));
    cester_assert_false(xbound_cstr_is_alpha("(3a"));
})

CESTER_TEST(xbound_cstr_is_digit, _, {
    cester_assert_false(xbound_cstr_is_digit("a1"));
    cester_assert_false(xbound_cstr_is_digit("54154f"));
    cester_assert_true(xbound_cstr_is_digit("435454"));
    cester_assert_false(xbound_cstr_is_digit("20libxtd"));
    cester_assert_false(xbound_cstr_is_digit("20_LIBXTD"));
    cester_assert_true(xbound_cstr_is_digit("12"));
    cester_assert_false(xbound_cstr_is_digit("(3a"));
})

CESTER_TEST(xbound_cstr_is_alphanum, _, {
    cester_assert_true(xbound_cstr_is_alphanum("a1"));
    cester_assert_true(xbound_cstr_is_alphanum("54154f"));
    cester_assert_true(xbound_cstr_is_alphanum("LIBxTD"));
    cester_assert_true(xbound_cstr_is_alphanum("20libxtd"));
    cester_assert_false(xbound_cstr_is_alphanum("20_LIBXTD"));
    cester_assert_true(xbound_cstr_is_alphanum("12"));
    cester_assert_false(xbound_cstr_is_alphanum("(3a"));
})

CESTER_TEST(xbound_cstr_is_white_space, _, {
    cester_assert_true(xbound_cstr_is_white_space("\v"));
    cester_assert_true(xbound_cstr_is_white_space("     "));
    cester_assert_false(xbound_cstr_is_white_space("54154f"));
    cester_assert_true(xbound_cstr_is_white_space("\n\n\n"));
    cester_assert_true(xbound_cstr_is_white_space(" "));
    cester_assert_false(xbound_cstr_is_white_space("20_LIBXTD"));
    cester_assert_true(xbound_cstr_is_white_space(" \t\t\n\r"));
    cester_assert_false(xbound_cstr_is_white_space("(3a"));
})

CESTER_TEST(xbound_cstr_is_cntrl, _, {
    cester_assert_true(xbound_cstr_is_cntrl("\v"));
    cester_assert_true(xbound_cstr_is_cntrl("\b"));
    cester_assert_false(xbound_cstr_is_cntrl("54154f"));
    cester_assert_true(xbound_cstr_is_cntrl("\n\n\n"));
    cester_assert_true(xbound_cstr_is_cntrl("\t"));
    cester_assert_false(xbound_cstr_is_cntrl("20_LIBXTD"));
    cester_assert_true(xbound_cstr_is_cntrl("\v\t\t\n\r"));
    cester_assert_false(xbound_cstr_is_cntrl("(3a"));
})

CESTER_TEST(xbound_cstr_is_printable, _, {
    cester_assert_false(xbound_cstr_is_printable("\v"));
    cester_assert_false(xbound_cstr_is_printable("\b"));
    cester_assert_true(xbound_cstr_is_printable("54154f"));
    cester_assert_true(xbound_cstr_is_printable("\n\nade\n"));
    cester_assert_false(xbound_cstr_is_printable("\t"));
    cester_assert_true(xbound_cstr_is_printable("20_LIBXTD"));
    cester_assert_false(xbound_cstr_is_printable("\v\t\t\n\r"));
    cester_assert_true(xbound_cstr_is_printable("(3a"));
})

CESTER_TEST(xbound_cstr_is_graphical, _, {
    cester_assert_false(xbound_cstr_is_graphical("\v"));
    cester_assert_false(xbound_cstr_is_graphical("\b"));
    cester_assert_true(xbound_cstr_is_graphical("54154f"));
    cester_assert_false(xbound_cstr_is_graphical("\n\n\n"));
    cester_assert_false(xbound_cstr_is_graphical("\t"));
    cester_assert_true(xbound_cstr_is_graphical("20_LIBXTD"));
    cester_assert_true(xbound_cstr_is_graphical("\vy\t\t\n\r"));
    cester_assert_true(xbound_cstr_is_graphical("(3a"));
})

CESTER_TEST(xbound_cstr_is_mixed_case, _, {
    cester_assert_false(xbound_cstr_is_mixed_case("LIBXTD"));
    cester_assert_false(xbound_cstr_is_mixed_case("libxtd"));
    cester_assert_true(xbound_cstr_is_mixed_case("LIBxtd"));
    cester_assert_false(xbound_cstr_is_mixed_case("LIBXTD123"));
    cester_assert_true(xbound_cstr_is_mixed_case("LIBxtd123"));
})

CESTER_TEST(xbound_cstr_is_sentence_case, _, {
    cester_assert_true(xbound_cstr_is_sentence_case("LIBXTD"));
    cester_assert_true(xbound_cstr_is_sentence_case("Libxtd"));
    cester_assert_false(xbound_cstr_is_sentence_case("llIBxtd"));
    cester_assert_true(xbound_cstr_is_sentence_case("LIBXTD123"));
    cester_assert_false(xbound_cstr_is_sentence_case("123libxtd"));
})

CESTER_TEST(xbound_cstr_is_decimal_with_seperator, _, {
    cester_assert_true(xbound_cstr_is_decimal_with_seperator("1_000_000", '_'));
    cester_assert_true(xbound_cstr_is_decimal_with_seperator("1.000.000", '.'));
    cester_assert_true(xbound_cstr_is_decimal_with_seperator("1,000,000", ','));
    cester_assert_false(xbound_cstr_is_decimal_with_seperator("_000_000", '_'));
    cester_assert_false(xbound_cstr_is_decimal_with_seperator("1_000_000_", '_'));
    cester_assert_false(xbound_cstr_is_decimal_with_seperator("1_000__000", '_'));
})

CESTER_TEST(xbound_cstr_is_decimal, _, {
    cester_assert_true(xbound_cstr_is_decimal("12345"));
    cester_assert_true(xbound_cstr_is_decimal(".12345"));
    cester_assert_true(xbound_cstr_is_decimal("12345.90778"));
    cester_assert_true(xbound_cstr_is_decimal("10e10"));
    cester_assert_true(xbound_cstr_is_decimal("10e10"));
    cester_assert_true(xbound_cstr_is_decimal("0090"));
    cester_assert_true(xbound_cstr_is_decimal("-0.05"));
    cester_assert_true(xbound_cstr_is_decimal("+9.56"));
    cester_assert_true(xbound_cstr_is_decimal("5."));
    cester_assert_true(xbound_cstr_is_decimal("5+1"));
    cester_assert_true(xbound_cstr_is_decimal(".5"));
    cester_assert_true(xbound_cstr_is_decimal("-.5"));
    cester_assert_true(xbound_cstr_is_decimal("5e10"));
    cester_assert_true(xbound_cstr_is_decimal("-80E1"));
    cester_assert_true(xbound_cstr_is_decimal("4e+2"));
    cester_assert_true(xbound_cstr_is_decimal("+6e-1"));
    cester_assert_true(xbound_cstr_is_decimal("+200"));
    cester_assert_true(xbound_cstr_is_decimal("-0.987887"));
    cester_assert_true(xbound_cstr_is_decimal("200."));
    cester_assert_true(xbound_cstr_is_decimal("12345."));
    cester_assert_false(xbound_cstr_is_decimal("1.000_000"));
    cester_assert_false(xbound_cstr_is_decimal("1_000_000"));
    cester_assert_false(xbound_cstr_is_decimal("_000_000"));
    cester_assert_false(xbound_cstr_is_decimal("12e90.10"));
    cester_assert_false(xbound_cstr_is_decimal("1Q000.000"));
    cester_assert_false(xbound_cstr_is_decimal("e"));
    cester_assert_false(xbound_cstr_is_decimal("a123"));
    cester_assert_false(xbound_cstr_is_decimal("10e10e"));
    cester_assert_false(xbound_cstr_is_decimal("10e10e10"));
    cester_assert_false(xbound_cstr_is_decimal("e10"));
    cester_assert_false(xbound_cstr_is_decimal(".e123"));
    cester_assert_false(xbound_cstr_is_decimal("12345e"));
    cester_assert_false(xbound_cstr_is_decimal("12345.e"));
    cester_assert_false(xbound_cstr_is_decimal("e.98"));
    cester_assert_false(xbound_cstr_is_decimal("12W345"));
    cester_assert_false(xbound_cstr_is_decimal("+e98"));
    cester_assert_false(xbound_cstr_is_decimal("1234e5.90778"));
    cester_assert_false(xbound_cstr_is_decimal("1234e.90778"));
    cester_assert_false(xbound_cstr_is_decimal("..12345"));
    cester_assert_false(xbound_cstr_is_decimal("100e"));
    cester_assert_false(xbound_cstr_is_decimal("1a"));
    cester_assert_false(xbound_cstr_is_decimal("67e2.3"));
    cester_assert_false(xbound_cstr_is_decimal("--12"));
    cester_assert_false(xbound_cstr_is_decimal("++12"));
    cester_assert_false(xbound_cstr_is_decimal("+-12"));
    cester_assert_false(xbound_cstr_is_decimal("++12"));
    cester_assert_false(xbound_cstr_is_decimal("e"));
    cester_assert_false(xbound_cstr_is_decimal("95a54e53"));
})

CESTER_TEST(xbound_cstr_is_hex_with_prefix, _, {
    cester_assert_true(xbound_cstr_is_hex_with_prefix("0x7FFF", "0x"));
    cester_assert_true(xbound_cstr_is_hex_with_prefix("HEX7FFF", "HEX"));
    cester_assert_true(xbound_cstr_is_hex_with_prefix("X7FFF", "X"));
    cester_assert_true(xbound_cstr_is_hex_with_prefix("X____7FFF", "X____"));
    cester_assert_true(xbound_cstr_is_hex_with_prefix("12345", XTD_NULL));
    cester_assert_true(xbound_cstr_is_hex_with_prefix("12345f", XTD_NULL));
    cester_assert_true(xbound_cstr_is_hex_with_prefix("12345f", XTD_NULL));
    cester_assert_true(xbound_cstr_is_hex_with_prefix("0xff", "0x"));
    cester_assert_false(xbound_cstr_is_hex_with_prefix("0xff", XTD_NULL));
    cester_assert_false(xbound_cstr_is_hex_with_prefix("12345", "0x"));
    cester_assert_false(xbound_cstr_is_hex_with_prefix("123.123", XTD_NULL));
    cester_assert_false(xbound_cstr_is_hex_with_prefix("+123", XTD_NULL));
    cester_assert_false(xbound_cstr_is_hex_with_prefix("-123", XTD_NULL));
    cester_assert_false(xbound_cstr_is_hex_with_prefix(".123", XTD_NULL));
    cester_assert_false(xbound_cstr_is_hex_with_prefix("123.", XTD_NULL));
    cester_assert_false(xbound_cstr_is_hex_with_prefix("123.123e", XTD_NULL));
})

CESTER_TEST(xbound_cstr_is_hex, _, {
    cester_assert_false(xbound_cstr_is_hex("0x7FFF"));
    cester_assert_true(xbound_cstr_is_hex("12345"));
    cester_assert_true(xbound_cstr_is_hex("12345f"));
    cester_assert_true(xbound_cstr_is_hex("12345f"));
    cester_assert_true(xbound_cstr_is_hex("12345"));
    cester_assert_false(xbound_cstr_is_hex("0xff"));
    cester_assert_false(xbound_cstr_is_hex("0xff"));
    cester_assert_false(xbound_cstr_is_hex("123.123"));
    cester_assert_false(xbound_cstr_is_hex("+123"));
    cester_assert_false(xbound_cstr_is_hex("-123"));
    cester_assert_false(xbound_cstr_is_hex(".123"));
    cester_assert_false(xbound_cstr_is_hex("123."));
    cester_assert_false(xbound_cstr_is_hex("123.123e"));
})

CESTER_TEST(xbound_cstr_is_octal_with_prefix, _, {
    cester_assert_true(xbound_cstr_is_octal_with_prefix("144", XTD_NULL));
    cester_assert_true(xbound_cstr_is_octal_with_prefix("0o144", "0o"));
    cester_assert_true(xbound_cstr_is_octal_with_prefix("111203", XTD_NULL));
    cester_assert_false(xbound_cstr_is_octal_with_prefix("9001", XTD_NULL));
    cester_assert_false(xbound_cstr_is_octal_with_prefix("0b144", XTD_NULL));
    cester_assert_false(xbound_cstr_is_octal_with_prefix("12345f", XTD_NULL));
    cester_assert_false(xbound_cstr_is_octal_with_prefix("12345f", "0b"));
    cester_assert_false(xbound_cstr_is_octal_with_prefix("+123", XTD_NULL));
    cester_assert_false(xbound_cstr_is_octal_with_prefix("-123", XTD_NULL));
    cester_assert_false(xbound_cstr_is_octal_with_prefix(".123", XTD_NULL));
    cester_assert_false(xbound_cstr_is_octal_with_prefix("123.", XTD_NULL));
})

CESTER_TEST(xbound_cstr_is_octal, _, {
    cester_assert_true(xbound_cstr_is_octal("144"));
    cester_assert_true(xbound_cstr_is_octal("111203"));
    cester_assert_false(xbound_cstr_is_octal("9001"));
    cester_assert_false(xbound_cstr_is_octal("0b144"));
    cester_assert_false(xbound_cstr_is_octal("0o144"));
    cester_assert_false(xbound_cstr_is_octal("12345f"));
    cester_assert_false(xbound_cstr_is_octal("12345f"));
    cester_assert_false(xbound_cstr_is_octal("+123"));
    cester_assert_false(xbound_cstr_is_octal("-123"));
    cester_assert_false(xbound_cstr_is_octal(".123"));
    cester_assert_false(xbound_cstr_is_octal("123."));
})

CESTER_TEST(xbound_cstr_is_binary_with_prefix_and_underscore, _, {
    cester_assert_true(xbound_cstr_is_binary_with_prefix_and_seperator("0b0000_1111_001010", "0b", '_'));
    cester_assert_true(xbound_cstr_is_binary_with_prefix_and_seperator("0b0000,1111,001010", "0b", ','));
    cester_assert_true(xbound_cstr_is_binary_with_prefix_and_seperator("0000,1111,001010", XTD_NULL, ','));
    cester_assert_true(xbound_cstr_is_binary_with_prefix_and_seperator("0000.1111.001010", XTD_NULL, '.'));
    cester_assert_false(xbound_cstr_is_binary_with_prefix_and_seperator("0b0000,1111,001010", XTD_NULL, ','));
    cester_assert_false(xbound_cstr_is_binary_with_prefix_and_seperator("0b0000_1111__001010", "0b", TRUE));
    cester_assert_false(xbound_cstr_is_binary_with_prefix_and_seperator("_0000_1111_001010", XTD_NULL, TRUE));
    cester_assert_false(xbound_cstr_is_binary_with_prefix_and_seperator("_0000_1111_001010", XTD_NULL, TRUE));
    cester_assert_false(xbound_cstr_is_binary_with_prefix_and_seperator("0b0000_1111_001010_", "0b", TRUE));
})

CESTER_TEST(xbound_cstr_is_binary_with_prefix, _, {
    cester_assert_true(xbound_cstr_is_binary_with_prefix("1111", XTD_NULL));
    cester_assert_true(xbound_cstr_is_binary_with_prefix("0b0000111001010", "0b"));
    cester_assert_true(xbound_cstr_is_binary_with_prefix("0", XTD_NULL));
    cester_assert_false(xbound_cstr_is_binary_with_prefix("0b0000_1111_001010", "0b"));
    cester_assert_false(xbound_cstr_is_binary_with_prefix("0b0000_1111__001010", "0b"));
    cester_assert_false(xbound_cstr_is_binary_with_prefix("_0b0000_1111_001010", "0b"));
    cester_assert_false(xbound_cstr_is_binary_with_prefix("0b0000_1111_001010_", "0b"));
    cester_assert_false(xbound_cstr_is_binary_with_prefix("9001", XTD_NULL));
    cester_assert_false(xbound_cstr_is_binary_with_prefix("0b144", XTD_NULL));
    cester_assert_false(xbound_cstr_is_binary_with_prefix("12345f", XTD_NULL));
    cester_assert_false(xbound_cstr_is_binary_with_prefix("12345f", "0b"));
    cester_assert_false(xbound_cstr_is_binary_with_prefix("+123", XTD_NULL));
    cester_assert_false(xbound_cstr_is_binary_with_prefix("-123", XTD_NULL));
    cester_assert_false(xbound_cstr_is_binary_with_prefix(".123", XTD_NULL));
    cester_assert_false(xbound_cstr_is_binary_with_prefix("123.", XTD_NULL));
})

CESTER_TEST(xbound_cstr_is_binary, _, {
    cester_assert_true(xbound_cstr_is_binary("1111"));
    cester_assert_true(xbound_cstr_is_binary("00000"));
    cester_assert_true(xbound_cstr_is_binary("00000111000111"));
    cester_assert_false(xbound_cstr_is_binary("9001"));
    cester_assert_false(xbound_cstr_is_binary("0b144"));
    cester_assert_false(xbound_cstr_is_binary("0o144"));
    cester_assert_false(xbound_cstr_is_binary("12345f"));
    cester_assert_false(xbound_cstr_is_binary("12345f"));
    cester_assert_false(xbound_cstr_is_binary("+123"));
    cester_assert_false(xbound_cstr_is_binary("-123"));
    cester_assert_false(xbound_cstr_is_binary(".123"));
    cester_assert_false(xbound_cstr_is_binary("123."));
})



