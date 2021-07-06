/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I.-I../include/  -I../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/xstring.h>
#include <exotic/xtd/xiterator.h>

#define cester_assert_str_equal_(x,y) cester_assert_true(xstring_cstr_equals(x,y))

#ifdef __XTD_STDC_VERSION__
CESTER_TEST(xstring_cstr_length_1, _, {
    char *text1 = "libxtd xstring length";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};

    cester_assert_int_eq(xstring_cstr_length(text1), 21);
    cester_assert_int_eq(xstring_cstr_length(text2), 11);
    cester_assert_int_eq(xstring_cstr_length(XTD_NULL), 0);
})

CESTER_TEST(xstring_cstr_length_2, _, {
    char *text1 = "libxtd xstring length";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};

    cester_assert_int_eq(xstring_cstr_length_2(text1), 21);
    cester_assert_int_eq(xstring_cstr_length_2(text2), 11);
    cester_assert_int_eq(xstring_cstr_length_2(XTD_NULL), 0);
})

CESTER_TEST(xstring_cstr_length_3, _, {
    char *text1 = "libxtd xstring length";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};

    cester_assert_int_eq(xstring_cstr_length_3(text1), 21);
    cester_assert_int_eq(xstring_cstr_length_3(text2), 11);
    cester_assert_int_eq(xstring_cstr_length_3(XTD_NULL), 0);
})

CESTER_TEST(xstring_cstr_length, _, {
    char *text1 = "libxtd xstring length";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};

    cester_assert_int_eq(xstring_cstr_length_1(text1), xstring_cstr_length_2(text1));
    cester_assert_int_eq(xstring_cstr_length_1(text1), xstring_cstr_length_3(text1));
    cester_assert_int_eq(xstring_cstr_length_2(text1), xstring_cstr_length_3(text1));
    cester_assert_int_eq(xstring_cstr_length_1(text2), xstring_cstr_length_2(text2));
    cester_assert_int_eq(xstring_cstr_length_1(text2), xstring_cstr_length_3(text2));
    cester_assert_int_eq(xstring_cstr_length_2(text2), xstring_cstr_length_3(text2));
    cester_assert_int_eq(xstring_cstr_length_1(XTD_NULL), xstring_cstr_length_2(XTD_NULL));
    cester_assert_int_eq(xstring_cstr_length_1(XTD_NULL), xstring_cstr_length_3(XTD_NULL));
    cester_assert_int_eq(xstring_cstr_length_2(XTD_NULL), xstring_cstr_length_3(XTD_NULL));
})

CESTER_TEST(xstring_cstr_equals, _, {
    char *text1 = "libxtd xstring length";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};

    cester_assert_str_equal_(text1, "libxtd xstring length");
    cester_assert_true(xstring_cstr_equals(text1, "libxtd xstring length"));
    cester_assert_true(xstring_cstr_equals_1(text1, "libxtd xstring length"));
    cester_assert_false(xstring_cstr_equals_1(text1, XTD_NULL));
    cester_assert_true(xstring_cstr_equals_1(XTD_NULL, XTD_NULL));
    cester_assert_true(xstring_cstr_equals_2(text1, "libxtd xstring length"));
    cester_assert_true(xstring_cstr_equals_3(text1, "libxtd xstring length"));
    cester_assert_true(xstring_cstr_equals_4(text1, "libxtd xstring length"));
    cester_assert_true(xstring_cstr_equals_1(text2, "Hello world"));
    cester_assert_false(xstring_cstr_equals_2(text2, "Hello world"));
    cester_assert_true(xstring_cstr_equals_3(text2, "Hello world"));
    cester_assert_true(xstring_cstr_equals_4(text2, "Hello world"));
    cester_assert_false(xstring_cstr_equals_4(text2, "Hello"));
    cester_assert_false(xstring_cstr_equals_4(text2, "Hellooo World"));
    cester_assert_false(xstring_cstr_equals_4(XTD_NULL, "Hellooo World"));
})

CESTER_TEST(xstring_cstr_equals_ignore_case, _, {
    char *text1 = "libxtd xstring length";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};

    cester_assert_true(xstring_cstr_equals_ignore_case(text1, "LIBXTD XSTRING LENGTH"));
    cester_assert_true(xstring_cstr_equals_ignore_case(text2, "HELLO WORLD"));
    cester_assert_true(xstring_cstr_equals_ignore_case("exotic libraries", "exotic libraries"));
    cester_assert_true(xstring_cstr_equals_ignore_case("EXOTIC libraries", "exotic LIBRARIES"));
    cester_assert_true(xstring_cstr_equals_ignore_case("EXOTIC LIBRARIES", "exotic libraries"));
    cester_assert_false(xstring_cstr_equals_ignore_case("lib", "libxtd"));
})

CESTER_TEST(xstring_cstr_compare, _, {
    char *text1 = "apple";
    char *text2 = "apply";
    char *text3 = "banana";
    char *text4 = "zebra";
    char *text5 = " space";
    char *text6 = "554212";
    char *text7 = "123456";
    char *text8 = "987654";
    char *text9 = "000000";
    char *text10 = "#@##@#";
    char *text11 = "0-__()(#@#*";

    cester_assert_false(xstring_cstr_equals(text1, text2));
    cester_assert_int_eq(xstring_cstr_compare(text2, text1), 20);
    cester_assert_int_eq(xstring_cstr_compare(text1, text1), 0);
    cester_assert_int_eq(xstring_cstr_compare("y", "e"), 20);
    cester_assert_int_eq(xstring_cstr_compare_2("y", "e"), 20);
    cester_assert_int_eq(xstring_cstr_compare_1(text3, text6), xstring_cstr_compare_2(text3, text6));
    cester_assert_int_gt(xstring_cstr_compare_1(text8, text7), xstring_cstr_compare_1(text9, text8));
})

CESTER_TEST(xstring_cstr_compare_ignore_case, _, {
    char *text1 = "APPLE";
    char *text2 = "apply";
    char *text3 = "BANANA";
    char *text4 = "zebra";
    char *text5 = " space";
    char *text6 = "554212";
    char *text7 = "123456";
    char *text8 = "987654";
    char *text9 = "000000";
    char *text10 = "#@##@#";
    char *text11 = "0-__()(#@#*";

    cester_assert_int_eq(xstring_cstr_compare_ignore_case(text2, text1), 20);
    cester_assert_int_eq(xstring_cstr_compare_ignore_case(text1, text1), 0);
    cester_assert_int_eq(xstring_cstr_compare_ignore_case("y", "E"), 20);
    cester_assert_int_eq(xstring_cstr_compare_ignore_case("Y", "e"), 20);
    cester_assert_int_eq(xstring_cstr_compare_ignore_case(text3, text6), xstring_cstr_compare_ignore_case(text3, text6));
    cester_assert_int_ne(xstring_cstr_compare(text3, text6), xstring_cstr_compare_ignore_case(text3, text6));
    cester_assert_int_gt(xstring_cstr_compare_ignore_case(text8, text7), xstring_cstr_compare_ignore_case(text9, text8));
})

CESTER_TEST(xstring_cstr_is_empty, _, {
    char *text1 = "libxtd xstring length";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "";
    char text4[20] = {};

    cester_assert_false(xstring_cstr_is_empty(text1));
    cester_assert_false(xstring_cstr_is_empty(text1));
    cester_assert_true(xstring_cstr_is_empty(text3));
    cester_assert_true(xstring_cstr_is_empty(text4));
    cester_assert_true(xstring_cstr_is_empty(""));
})

CESTER_TEST(xstring_cstr_index_of_from_pos_with_length, _, {
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "string";
    size_t text1_length = xstring_cstr_length(text1);
    size_t text2_length = xstring_cstr_length(text2);

    cester_assert_int_eq(xstring_cstr_index_of_from_pos_with_length(text1_length, text1, "xtd", 0), 3);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos_with_length(text1_length, text1, "libxtd xstring length and longer", 0), -1);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos_with_length(text1_length, text1, "libxtd xstring length xstring", 0), 0);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos_with_length(text1_length, text1, text1, 0), 0);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos_with_length(text1_length, text1, "i", 0), 1);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos_with_length(text1_length, text1, "i", 4), 11);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos_with_length(text1_length, text1, "xstring", 0), 7);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos_with_length(text1_length, text1, "xstring", 10), 22);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos_with_length(text1_length, text1, text2, 0), -1);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos_with_length(text1_length, text1, text3, 0), 8);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos_with_length(text1_length, text1, text3, 10), 23);
})

CESTER_TEST(xstring_cstr_index_of_from_pos, _, {
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "string";

    cester_assert_int_eq(xstring_cstr_index_of_from_pos(text1, "xtd", 0), 3);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos(text1, "libxtd xstring length and longer", 0), -1);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos(text1, "libxtd xstring length xstring", 0), 0);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos(text1, text1, 0), 0);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos(text1, "i", 0), 1);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos(text1, "i", 4), 11);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos(text1, "xstring", 0), 7);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos(text1, "xstring", 10), 22);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos(text1, text2, 0), -1);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos(text1, text3, 0), 8);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos(text1, text3, 10), 23);
})

CESTER_TEST(xstring_cstr_index_of, _, {
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "string";

    cester_assert_int_eq(xstring_cstr_index_of(text1, "xtd"), 3);
    cester_assert_int_eq(xstring_cstr_index_of(text1, "libxtd xstring length and longer"), -1);
    cester_assert_int_eq(xstring_cstr_index_of(text1, "libxtd xstring length xstring"), 0);
    cester_assert_int_eq(xstring_cstr_index_of(text1, text1), 0);
    cester_assert_int_eq(xstring_cstr_index_of(text1, "i"), 1);
    cester_assert_int_eq(xstring_cstr_index_of(text1, "xstring"), 7);
    cester_assert_int_eq(xstring_cstr_index_of(text1, text2), -1);
    cester_assert_int_eq(xstring_cstr_index_of(text1, text3), 8);
})

CESTER_TEST(xstring_cstr_last_index_of_from_pos_with_length, _, {
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "string";
    size_t text1_length = xstring_cstr_length(text1);
    size_t text2_length = xstring_cstr_length(text2);

    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos_with_length(text1_length, text1, "xtd", 0), 3);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos_with_length(text1_length, text1, "libxtd xstring length and longer", 0), -1);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos_with_length(text1_length, text1, "libxtd xstring length xstring", 0), 0);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos_with_length(text1_length, text1, text1, 0), 0);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos_with_length(text1_length, text1, "i", 0), 26);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos_with_length(text1_length, text1, "i", 4), 11);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos_with_length(text1_length, text1, "xstring", 0), 22);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos_with_length(text1_length, text1, "xstring", 10), 7);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos_with_length(text1_length, text1, text2, 0), -1);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos_with_length(text1_length, text1, text3, 0), 23);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos_with_length(text1_length, text1, text3, 10), 8);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos_with_length(text2_length, text2, "o", 0), 7);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos_with_length(text2_length, text2, "o", 4), 4);
})

CESTER_TEST(xstring_cstr_last_index_of_from_pos, _, {
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "string";

    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos(text1, "xtd", 0), 3);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos(text1, "libxtd xstring length and longer", 0), -1);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos(text1, "libxtd xstring length xstring", 0), 0);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos(text1, text1, 0), 0);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos(text1, "i", 0), 26);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos(text1, "i", 4), 11);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos(text1, "xstring", 0), 22);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos(text1, "xstring", 10), 7);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos(text1, text2, 0), -1);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos(text1, text3, 0), 23);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos(text1, text3, 10), 8);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos(text2, "o", 0), 7);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos(text2, "o", 4), 4);
})

CESTER_TEST(xstring_cstr_last_index_of, _, {
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "string";

    cester_assert_int_eq(xstring_cstr_last_index_of(text1, "xtd"), 3);
    cester_assert_int_eq(xstring_cstr_last_index_of(text1, "libxtd xstring length and longer"), -1);
    cester_assert_int_eq(xstring_cstr_last_index_of(text1, "libxtd xstring length xstring"), 0);
    cester_assert_int_eq(xstring_cstr_last_index_of(text1, text1), 0);
    cester_assert_int_eq(xstring_cstr_last_index_of(text1, "i"), 26);
    cester_assert_int_eq(xstring_cstr_last_index_of(text1, "xstring"), 22);
    cester_assert_int_eq(xstring_cstr_last_index_of(text1, text2), -1);
    cester_assert_int_eq(xstring_cstr_last_index_of(text1, text3), 23);
    cester_assert_int_eq(xstring_cstr_last_index_of("test_xstring_utils.h", "."), 18);
})

CESTER_TEST(xstring_cstr_contains, _, {
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "string";

    cester_assert_true(xstring_cstr_contains(text1, "xtd"));
    cester_assert_false(xstring_cstr_contains(text1, "libxtd xstring length and longer"));
    cester_assert_true(xstring_cstr_contains(text1, "libxtd xstring length xstring"));
    cester_assert_true(xstring_cstr_contains(text1, text1));
    cester_assert_true(xstring_cstr_contains(text1, "i"));
    cester_assert_true(xstring_cstr_contains(text1, "xstring"));
    cester_assert_false(xstring_cstr_contains(text1, text2));
    cester_assert_true(xstring_cstr_contains(text1, text3));
    cester_assert_true(xstring_cstr_contains("test_xstring_utils.h", "."));
    cester_assert_true(xstring_cstr_contains(text2, "Hello"));
    cester_assert_false(xstring_cstr_contains(text2, "hello"));
    cester_assert_false(xstring_cstr_contains(text2, "World"));
    cester_assert_true(xstring_cstr_contains(text2, "world"));
    cester_assert_true(xstring_cstr_contains(text2, "Hello world"));
})

CESTER_TEST(xstring_cstr_ends_with, _, {
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "string";

    cester_assert_false(xstring_cstr_ends_with(text1, "xtd"));
    cester_assert_false(xstring_cstr_ends_with(text1, "libxtd xstring length and longer"));
    cester_assert_true(xstring_cstr_ends_with(text1, "libxtd xstring length xstring"));
    cester_assert_true(xstring_cstr_ends_with(text1, text1));
    cester_assert_false(xstring_cstr_ends_with(text1, "i"));
    cester_assert_true(xstring_cstr_ends_with(text1, "g"));
    cester_assert_false(xstring_cstr_ends_with(text1, "libxtd"));
    cester_assert_true(xstring_cstr_ends_with(text1, "xstring"));
    cester_assert_true(xstring_cstr_ends_with("test_xstring_utils.h", ".h"));
    cester_assert_true(xstring_cstr_ends_with("test_xstring_utils.h", "h"));
    cester_assert_false(xstring_cstr_ends_with(text2, "Hello"));
    cester_assert_true(xstring_cstr_ends_with(text2, "world"));
    cester_assert_false(xstring_cstr_ends_with(text1, text2));
    cester_assert_true(xstring_cstr_ends_with(text1, text3));
    cester_assert_true(xstring_cstr_ends_with(text2, "Hello world"));
})

CESTER_TEST(xstring_cstr_starts_with, _, {
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "string";

    cester_assert_false(xstring_cstr_starts_with(text1, "xtd"));
    cester_assert_false(xstring_cstr_starts_with(text1, "libxtd xstring length and longer"));
    cester_assert_true(xstring_cstr_starts_with(text1, "libxtd xstring length xstring"));
    cester_assert_true(xstring_cstr_starts_with(text1, text1));
    cester_assert_false(xstring_cstr_starts_with(text1, "i"));
    cester_assert_true(xstring_cstr_starts_with(text1, "l"));
    cester_assert_true(xstring_cstr_starts_with(text1, "libxtd"));
    cester_assert_false(xstring_cstr_starts_with(text1, "xstring"));
    cester_assert_false(xstring_cstr_starts_with("test_xstring_utils.h", ".h"));
    cester_assert_true(xstring_cstr_starts_with("test_xstring_utils.h", "test_"));
    cester_assert_true(xstring_cstr_starts_with(text2, "Hello"));
    cester_assert_false(xstring_cstr_starts_with(text2, "world"));
    cester_assert_false(xstring_cstr_starts_with(text1, text2));
    cester_assert_false(xstring_cstr_starts_with(text1, text3));
    cester_assert_true(xstring_cstr_starts_with(text2, "Hello world"));
})

CESTER_TEST(xstring_cstr_sub_string_in_range_with_length, _, {
    enum x_stat status;
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    size_t text1_length = xstring_cstr_length(text1);
    size_t text2_length = xstring_cstr_length(text2);
    char *substr_value1 = (char *) malloc(text1_length * sizeof(char));
    char *substr_value2 = (char *) malloc(6 * sizeof(char));
    char *substr_value3 = (char *) malloc(6 * sizeof(char));
    char *substr_value4 = (char *) malloc(2 * sizeof(char));
    char *substr_value5 = (char *) malloc(5 * sizeof(char));
    
    status = xstring_cstr_sub_string_in_range_with_length(text1_length, text1, -1, text1_length, XTD_NULL);
    cester_assert_int_eq(status, XTD_OUT_OF_RANGE_ERR);
    status = xstring_cstr_sub_string_in_range_with_length(text1_length, text1, 0, text1_length+4, XTD_NULL);
    cester_assert_int_eq(status, XTD_OUT_OF_RANGE_ERR);
    status = xstring_cstr_sub_string_in_range_with_length(text1_length, text1, 0, text1_length, XTD_NULL);
    cester_assert_int_ne(status, XTD_OUT_OF_RANGE_ERR);
    status = xstring_cstr_sub_string_in_range_with_length(0, text1, 0, text1_length, XTD_NULL);
    cester_assert_int_eq(status, XTD_OUT_OF_RANGE_ERR);
    status = xstring_cstr_sub_string_in_range_with_length(text1_length, text1, text1_length+1, text1_length, XTD_NULL);
    cester_assert_int_eq(status, XTD_OUT_OF_RANGE_ERR);
    status = xstring_cstr_sub_string_in_range_with_length(text1_length, text1, 0, text1_length, XTD_NULL);
    cester_assert_int_eq(status, XTD_PARAM_NULL_ERR);
    status = xstring_cstr_sub_string_in_range_with_length(text1_length, text1, 0, text1_length, substr_value1);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal_(text1, substr_value1);
    status = xstring_cstr_sub_string_in_range_with_length(text1_length, text1, 0, 6, substr_value2);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal_(substr_value2, "libxtd");
    status = xstring_cstr_sub_string_in_range_with_length(text1_length, text1, 18, 24, substr_value3);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal_(substr_value3, "gth xs");
    status = xstring_cstr_sub_string_in_range_with_length(20, "test_xstring_utils.h", 18, 20, substr_value4);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal_(substr_value4, ".h");
    status = xstring_cstr_sub_string_in_range_with_length(text2_length, text2, 0, 5, substr_value5);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal_(substr_value5, "Hello");
    status = xstring_cstr_sub_string_in_range_with_length(text2_length, text2, 6, text2_length, substr_value5);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal_(substr_value5, "world");

    free(substr_value1);
    free(substr_value2);
    free(substr_value3);
    free(substr_value4);
    free(substr_value5);
})

CESTER_TEST(xstring_cstr_sub_string_in_range, _, {
    enum x_stat status;
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    size_t text1_length = xstring_cstr_length(text1);
    size_t text2_length = xstring_cstr_length(text2);
    char *substr_value1 = (char *) malloc(text1_length * sizeof(char));
    char *substr_value2 = (char *) malloc(6 * sizeof(char));
    char *substr_value3 = (char *) malloc(6 * sizeof(char));
    char *substr_value4 = (char *) malloc(2 * sizeof(char));
    char *substr_value5 = (char *) malloc(5 * sizeof(char));
    
    status = xstring_cstr_sub_string_in_range(text1, -1, text1_length, XTD_NULL);
    cester_assert_int_eq(status, XTD_OUT_OF_RANGE_ERR);
    status = xstring_cstr_sub_string_in_range(text1, 0, text1_length+4, XTD_NULL);
    cester_assert_int_eq(status, XTD_OUT_OF_RANGE_ERR);
    status = xstring_cstr_sub_string_in_range(text1, 0, text1_length, XTD_NULL);
    cester_assert_int_ne(status, XTD_OUT_OF_RANGE_ERR);
    status = xstring_cstr_sub_string_in_range(text1, 0, text1_length, XTD_NULL);
    cester_assert_int_ne(status, XTD_OUT_OF_RANGE_ERR);
    status = xstring_cstr_sub_string_in_range(text1, text1_length+1, text1_length, XTD_NULL);
    cester_assert_int_eq(status, XTD_OUT_OF_RANGE_ERR);
    status = xstring_cstr_sub_string_in_range(text1, 0, text1_length, XTD_NULL);
    cester_assert_int_eq(status, XTD_PARAM_NULL_ERR);
    status = xstring_cstr_sub_string_in_range(text1, 0, text1_length, substr_value1);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal_(text1, substr_value1);
    status = xstring_cstr_sub_string_in_range(text1, 0, 6, substr_value2);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal_(substr_value2, "libxtd");
    status = xstring_cstr_sub_string_in_range(text1, 18, 24, substr_value3);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal_(substr_value3, "gth xs");
    status = xstring_cstr_sub_string_in_range("test_xstring_utils.h", 18, 20, substr_value4);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal_(substr_value4, ".h");
    status = xstring_cstr_sub_string_in_range(text2, 0, 5, substr_value5);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal_(substr_value5, "Hello");
    status = xstring_cstr_sub_string_in_range(text2, 6, text2_length, substr_value5);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal_(substr_value5, "world");

    free(substr_value1);
    free(substr_value2);
    free(substr_value3);
    free(substr_value4);
    free(substr_value5);
})

CESTER_TEST(xstring_cstr_sub_string, _, {
    enum x_stat status;
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    size_t text1_length = xstring_cstr_length(text1);
    size_t text2_length = xstring_cstr_length(text2);
    char *substr_value1 = (char *) malloc(text1_length * sizeof(char));
    char *substr_value2 = (char *) malloc(7 * sizeof(char));
    char *substr_value4 = (char *) malloc(2 * sizeof(char));
    char *substr_value5 = (char *) malloc(5 * sizeof(char));
    
    status = xstring_cstr_sub_string(text1, -1, XTD_NULL);
    cester_assert_int_eq(status, XTD_OUT_OF_RANGE_ERR);
    status = xstring_cstr_sub_string(text1, 0, XTD_NULL);
    cester_assert_int_ne(status, XTD_OUT_OF_RANGE_ERR);
    status = xstring_cstr_sub_string(text1, 0, XTD_NULL);
    cester_assert_int_ne(status, XTD_OUT_OF_RANGE_ERR);
    status = xstring_cstr_sub_string(text1, text1_length+1, XTD_NULL);
    cester_assert_int_eq(status, XTD_OUT_OF_RANGE_ERR);
    status = xstring_cstr_sub_string(text1, 0, XTD_NULL);
    cester_assert_int_eq(status, XTD_PARAM_NULL_ERR);
    status = xstring_cstr_sub_string(text1, 0, substr_value1);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal_(text1, substr_value1);
    status = xstring_cstr_sub_string(text1, 22, substr_value2);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal_(substr_value2, "xstring");
    status = xstring_cstr_sub_string("test_xstring_utils.h", 18, substr_value4);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal_(substr_value4, ".h");
    status = xstring_cstr_sub_string(text2, 0, substr_value5);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_not_equal(substr_value5, "Hello");
    status = xstring_cstr_sub_string(text2, 6, substr_value5);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal_(substr_value5, "world");

    free(substr_value1);
    free(substr_value2);
    free(substr_value4);
    free(substr_value5);
})

CESTER_TEST(xstring_cstr_char_at, _, {
    char *text1 = "libxtd xstring length";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};

    cester_assert_char_eq(xstring_cstr_char_at(text1, 0), 'l');
    cester_assert_char_eq(xstring_cstr_char_at(text1, 20), 'h');
    cester_assert_char_eq(xstring_cstr_char_at(text2, 0), 'H');
    cester_assert_char_eq(xstring_cstr_char_at(text2, 7), 'o');
})

CESTER_COMMENT(
    all cester cester_assert_ptr_not_equal, cester_assert_str_equal_ 
    is causing segfault in a pointer to pointer scenerio, fix in libcester
)

CESTER_TEST(xstring_cstr_split_with_length, _, {
    XAllocator allocator;
    char **splited1;
    char **splited2;
    char **splited3;
    char *text1 = "libxtd xstring length and string for xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    size_t text1_length = xstring_cstr_length(text1);
    size_t text2_length = xstring_cstr_length(text2);
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    cester_assert_ptr_equal(xstring_cstr_split_with_length(text1_length, text1, XTD_NULL, allocator), XTD_NULL);
    cester_assert_ptr_equal(xstring_cstr_split_with_length(text1_length, XTD_NULL, XTD_NULL, allocator), XTD_NULL);
    splited1 = xstring_cstr_split_with_length(text1_length, text1, " ", allocator);
    /*cester_assert_ptr_not_equal(splited1, XTD_NULL);*/
    cester_assert_int_eq(xptp_array_size((void **)splited1), 7);
    cester_assert_str_equal_(splited1[0], "libxtd");
    cester_assert_str_equal_(splited1[2], "length");
    cester_assert_str_equal_(splited1[3], "and");
    cester_assert_str_equal_(splited1[6], "xstring");
    splited2 = xstring_cstr_split_with_length(text2_length, text2, "o w", allocator);
    /*cester_assert_ptr_not_equal(splited2, XTD_NULL);*/
    cester_assert_int_eq(xptp_array_size((void **)splited2), 2);
    cester_assert_str_equal_(splited2[0], "Hell");
    cester_assert_str_equal_(splited2[1], "orld");
    splited3 = xstring_cstr_split_with_length(17, "Whole cake island", "", allocator);
    /*cester_assert_ptr_not_equal(splited3, XTD_NULL);*/
    cester_assert_int_eq(xptp_array_size((void **)splited3), 1);
    cester_assert_str_equal_(splited3[0], "Whole cake island");
    /*cester_assert_ptr_equal(splited3[1], XTD_NULL);*/

    xfreep2p((void **)splited1, allocator);
    xfreep2p((void **)splited2, allocator);
    xfreep2p((void **)splited3, allocator);
})

CESTER_TEST(xstring_cstr_split, _, {
    XAllocator allocator;
    char **splited1;
    char **splited2;
    char **splited3;
    char *text1 = "libxtd xstring length and string for xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    cester_assert_ptr_equal(xstring_cstr_split(text1, XTD_NULL, allocator), XTD_NULL);
    cester_assert_ptr_equal(xstring_cstr_split(XTD_NULL, XTD_NULL, allocator), XTD_NULL);
    splited1 = xstring_cstr_split(text1, " ", allocator);
    cester_assert_ptr_not_equal(splited1, XTD_NULL);
    cester_assert_int_eq(xptp_array_size((void **)splited1), 7);
    cester_assert_str_equal_(splited1[0], "libxtd");
    cester_assert_str_equal_(splited1[2], "length");
    cester_assert_str_equal_(splited1[3], "and");
    cester_assert_str_equal_(splited1[6], "xstring");
    splited2 = xstring_cstr_split(text2, "o w", allocator);
    cester_assert_ptr_not_equal(splited2, XTD_NULL);
    cester_assert_int_eq(xptp_array_size((void **)splited2), 2);
    cester_assert_str_equal_(splited2[0], "Hell");
    cester_assert_str_equal_(splited2[1], "orld");
    splited3 = xstring_cstr_split("Whole cake island", "", allocator);
    cester_assert_ptr_not_equal(splited3, XTD_NULL);
    cester_assert_int_eq(xptp_array_size((void **)splited3), 1);
    cester_assert_str_equal_(splited3[0], "Whole cake island");
    cester_assert_ptr_equal(splited3[1], XTD_NULL);

    xfreep2p((void **)splited1, allocator);
    xfreep2p((void **)splited2, allocator);
    xfreep2p((void **)splited3, allocator);
})

CESTER_TEST(xstring_cstr_char_value, _, {
    char ch1 = '2';
    char ch2 = 'A';
    char ch3 = '&';
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    cester_assert_str_equal_(xstring_cstr_char_value(ch1, allocator), "2");
    cester_assert_str_equal_(xstring_cstr_char_value(ch2, allocator), "A");
    cester_assert_str_equal_(xstring_cstr_char_value(ch3, allocator), "&");
})

CESTER_TEST(xstring_cstr_int_value, _, {
    int int1 = 0;
    int int2 = -38276376;
    int int3 = 98895895;
    char *value;
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    value = (char *) xstring_cstr_int_value(int1, allocator);
    cester_assert_str_equal_(value, "0"); free(value);
    value = (char *) xstring_cstr_int_value(int2, allocator);
    cester_assert_str_equal_(value, "-38276376"); free(value);
    value = (char *) xstring_cstr_int_value(int3, allocator);
    cester_assert_str_equal_(value, "98895895"); free(value);
})

CESTER_TEST(xstring_cstr_long_value, _, {
    long long1 = 0L;
    long long2 = -2147483645;
    long long3 = 2147483647;
    char *value;
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    value = (char *) xstring_cstr_long_value(long1, allocator);
    cester_assert_str_equal_(value, "0"); free(value);
    value = (char *) xstring_cstr_long_value(long2, allocator);
    cester_assert_str_equal_(value, "-2147483645"); free(value);
    value = (char *) xstring_cstr_long_value(long3, allocator);
    cester_assert_str_equal_(value, "2147483647"); free(value);
})

CESTER_TEST(xstring_cstr_double_value, _, {
    double double1 = 0.00;
    double double2 = -736627.23728378;
    double double3 = 998958989.9458945894;
    char *value;
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    value = (char *) xstring_cstr_double_value(double1, 2, allocator);
    cester_assert_str_equal_(value, "0.00"); free(value);
    value = (char *) xstring_cstr_double_value(double2, 2, allocator);
    cester_assert_str_equal_(value, "-736627.23"); free(value);
    value = (char *) xstring_cstr_double_value(double3, 2, allocator);
    cester_assert_str_equal_(value, "998958989.88"); free(value);
})

CESTER_TEST(xstring_cstr_float_value, _, {
    float float1 = 0.00;
    float float2 = -736627.23728;
    float float3 = 998958.958946;
    char *value;
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    value = (char *) xstring_cstr_float_value(float1, 2, allocator);
    cester_assert_str_equal_(value, "0.00"); free(value);
    value = (char *) xstring_cstr_float_value(float2, 2, allocator);
    cester_assert_str_equal_(value, "-736627.25"); free(value);
    value = (char *) xstring_cstr_float_value(float3, 2, allocator);
    cester_assert_str_equal_(value, "998958.93"); free(value);
})

CESTER_TODO_TEST(xstring_cstr_pointer_value, _, {
    
})

CESTER_TEST(xstring_cstr_concat_cstr, _, {
    char *value;
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    value = (char *) xstring_cstr_concat_cstr("Hello", "World", allocator);
    cester_assert_str_equal_(value, "HelloWorld"); free(value);
    value = (char *) xstring_cstr_concat_cstr("Hello", " wORLD", allocator);
    cester_assert_str_equal_(value, "Hello wORLD"); free(value);
})

CESTER_TEST(xstring_cstr_concat_char, _, {
    char *value;
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    value = (char *) xstring_cstr_concat_char("Hell", 'o', allocator);
    cester_assert_str_equal_(value, "Hello"); free(value);
    value = (char *) xstring_cstr_concat_char("Hello", '\n', allocator);
    cester_assert_str_equal_(value, "Hello\n"); free(value);
})

CESTER_TEST(xstring_cstr_concat_int, _, {
    char *value;
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    value = (char *) xstring_cstr_concat_int("Hello", 987654321, allocator);
    cester_assert_str_equal_(value, "Hello987654321"); free(value);
    value = (char *) xstring_cstr_concat_int("Year ", 2021, allocator);
    cester_assert_str_equal_(value, "Year 2021"); free(value);
})

CESTER_TEST(xstring_cstr_concat_long, _, {
    char *value;
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    value = (char *) xstring_cstr_concat_long("Hello", 98765471L, allocator);
    cester_assert_str_equal_(value, "Hello98765471"); free(value);
    value = (char *) xstring_cstr_concat_long("Year ", -287372021L, allocator);
    cester_assert_str_equal_(value, "Year -287372021"); free(value);
})

CESTER_TEST(xstring_cstr_concat_double, _, {
    char *value;
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    value = (char *) xstring_cstr_concat_double("Hello", 90878787.0, allocator);
    cester_assert_str_equal_(value, "Hello90878787.88"); free(value);
    value = (char *) xstring_cstr_concat_double("Year ", -678768876.0, allocator);
    cester_assert_str_equal_(value, "Year -678768876.88"); free(value);
})

CESTER_TEST(xstring_cstr_concat_float, _, {
    char *value;
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    value = (char *) xstring_cstr_concat_float("Hello", 908787.00, allocator);
    cester_assert_str_equal_(value, "Hello908787.00"); free(value);
    value = (char *) xstring_cstr_concat_float("Year ", -678876.00, allocator);
    cester_assert_str_equal_(value, "Year -678876.00"); free(value);
})

CESTER_TEST(xstring_cstr_escape_sequences, _, {
    char *value;
    size_t err_pos;
    char *cstr1 = "Hello\tWorld";
    char *cstr2 = "Hello\\tWorld";
    char *cstr3 = "Hello\\qWorld";
    char *cstr4 = "Tab\t\tNew Line\tCariage \rAlert beep\aBackspacee\bEscape char\eFormfeed PageBreak\fVertical tab \vBackslash\\Apostle\'Double quote\"Question Mark \?";
    char *cstr5 = "Tab\\t\\tNew Line\\tCariage \\rAlert beep\\aBackspacee\\bEscape char\\eFormfeed PageBreak\\fVertical tab \\vBackslash\\\\Apostle\\'Double quote\\\"Question Mark \\?";
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    cester_assert_str_equal(cstr1, "Hello\tWorld");
    cester_assert_str_not_equal(cstr2, "Hello\tWorld");
    cester_assert_uint_eq(xstring_cstr_escape_sequences(cstr2, allocator, &value, XTD_NULL), XTD_OK);
    cester_assert_str_equal(value, cstr1);
    cester_assert_str_equal(value, "Hello\tWorld");
    cester_assert_uint_ne(xstring_cstr_escape_sequences(cstr3, allocator, &value, XTD_NULL), XTD_OK);
    cester_assert_uint_eq(xstring_cstr_escape_sequences(cstr3, allocator, &value, &err_pos), XTD_PARSING_ERR);
    cester_assert_int_eq(err_pos, 6);
    cester_assert_char_eq(cstr3[err_pos], 'q');
    cester_assert_str_equal(cstr4, "Tab\t\tNew Line\tCariage \rAlert beep\aBackspacee\bEscape char\eFormfeed PageBreak\fVertical tab \vBackslash\\Apostle\'Double quote\"Question Mark \?");
    cester_assert_str_not_equal(cstr5, cstr4);
    cester_assert_uint_eq(xstring_cstr_escape_sequences(cstr5, allocator, &value, &err_pos), XTD_OK);
    cester_assert_str_equal(value, cstr4);
    cester_assert_str_equal(value, "Tab\t\tNew Line\tCariage \rAlert beep\aBackspacee\bEscape char\eFormfeed PageBreak\fVertical tab \vBackslash\\Apostle\'Double quote\"Question Mark \?");
})

CESTER_TEST(xstring_cstr_unescape_sequences, _, {
    char *value;
    size_t err_pos;
    char *cstr1 = "Hello\tWorld";
    char *cstr2 = "Hello\\tWorld";
    char *cstr3 = "Hello\\qWorld";
    char *cstr4 = "Tab\t\tNew Line\tCariage \rAlert beep\aBackspacee\bEscape char\eFormfeed PageBreak\fVertical tab \vBackslash\\Apostle\'Double quote\"Question Mark \?";
    char *cstr5 = "Tab\\t\\tNew Line\\tCariage \\rAlert beep\\aBackspacee\\bEscape char\\eFormfeed PageBreak\\fVertical tab \\vBackslash\\\\Apostle\\'Double quote\\\"Question Mark \\?";
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    cester_assert_str_equal(cstr2, "Hello\\tWorld");
    cester_assert_str_not_equal(cstr2, "Hello\tWorld");
    cester_assert_uint_eq(xstring_cstr_unescape_sequences(cstr1, allocator, &value, XTD_NULL), XTD_OK);
    cester_assert_str_equal(value, cstr2);
    cester_assert_str_equal(value, "Hello\\tWorld");
    cester_assert_str_equal(cstr5, "Tab\\t\\tNew Line\\tCariage \\rAlert beep\\aBackspacee\\bEscape char\\eFormfeed PageBreak\\fVertical tab \\vBackslash\\\\Apostle\\'Double quote\\\"Question Mark \\?");
    cester_assert_str_not_equal(cstr5, cstr4);
    cester_assert_uint_eq(xstring_cstr_unescape_sequences(cstr4, allocator, &value, &err_pos), XTD_OK);
    cester_assert_str_equal(value, cstr5);
    cester_assert_str_equal(value, "Tab\\t\\tNew Line\\tCariage \\rAlert beep\\aBackspacee\\bEscape char\\eFormfeed PageBreak\\fVertical tab \\vBackslash\\\\Apostle\\'Double quote\\\"Question Mark \\?");
})

CESTER_TODO_TEST(xstring_cstr_escape_sequences_extended, _, {
    char *cstr1 = "Hello\tWorld";

    cester_assert_str_equal_(cstr1, "Hello\tWorld");
})

CESTER_TODO_TEST(xstring_cstr_concat_pointer, _, {
    
})

CESTER_TODO_TEST(xstring_cstr_format, _, {
    
})

CESTER_TODO_TEST(xstring_cstr_hashcode, _, {
    
})

CESTER_TODO_TEST(xstring_cstr_replace, _, {
    
})

CESTER_TODO_TEST(xstring_cstr_replace_first, _, {
    
})

CESTER_TODO_TEST(xstring_cstr_replace_last, _, {
    
})

CESTER_TODO_TEST(xstring_cstr_to_lower_case, _, {
    
})

CESTER_TODO_TEST(xstring_cstr_to_upper_case, _, {
    
})

CESTER_TODO_TEST(xstring_cstr_trim, _, {
    
})
#endif

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)

/*
write tests for 
xstring_cstr_copy
xstring_cstr_trim_memory_to_size
*/
