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

CESTER_TEST(xbound_cstr_is_number, _, {
    cester_assert_true(xbound_cstr_is_number("12345"));
    cester_assert_true(xbound_cstr_is_number("12345.90778"));
    cester_assert_true(xbound_cstr_is_number("12345f"));
})




