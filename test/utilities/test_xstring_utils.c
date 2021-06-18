/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I.-I../include/  -I../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/xstring.h>
#include <exotic/xtd/xiterator.h>

CESTER_TEST(xstring_str_length_1, _, {
    char *text1 = "libxtd xstring length";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};

    cester_assert_int_eq(xstring_str_length(text1), 21);
    cester_assert_int_eq(xstring_str_length(text2), 11);
    cester_assert_int_eq(xstring_str_length(XTD_NULL), 0);
})

CESTER_TEST(xstring_str_length_2, _, {
    char *text1 = "libxtd xstring length";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};

    cester_assert_int_eq(xstring_str_length_2(text1), 21);
    cester_assert_int_eq(xstring_str_length_2(text2), 11);
    cester_assert_int_eq(xstring_str_length_2(XTD_NULL), 0);
})

CESTER_TEST(xstring_str_length_3, _, {
    char *text1 = "libxtd xstring length";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};

    cester_assert_int_eq(xstring_str_length_3(text1), 21);
    cester_assert_int_eq(xstring_str_length_3(text2), 11);
    cester_assert_int_eq(xstring_str_length_3(XTD_NULL), 0);
})

CESTER_TEST(xstring_str_length, _, {
    char *text1 = "libxtd xstring length";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};

    cester_assert_int_eq(xstring_str_length_1(text1), xstring_str_length_2(text1));
    cester_assert_int_eq(xstring_str_length_1(text1), xstring_str_length_3(text1));
    cester_assert_int_eq(xstring_str_length_2(text1), xstring_str_length_3(text1));
    cester_assert_int_eq(xstring_str_length_1(text2), xstring_str_length_2(text2));
    cester_assert_int_eq(xstring_str_length_1(text2), xstring_str_length_3(text2));
    cester_assert_int_eq(xstring_str_length_2(text2), xstring_str_length_3(text2));
    cester_assert_int_eq(xstring_str_length_1(XTD_NULL), xstring_str_length_2(XTD_NULL));
    cester_assert_int_eq(xstring_str_length_1(XTD_NULL), xstring_str_length_3(XTD_NULL));
    cester_assert_int_eq(xstring_str_length_2(XTD_NULL), xstring_str_length_3(XTD_NULL));
})

CESTER_TEST(xstring_str_equals, _, {
    char *text1 = "libxtd xstring length";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};

    cester_assert_str_equal(text1, "libxtd xstring length");
    cester_assert_true(xstring_str_equals(text1, "libxtd xstring length"));
    cester_assert_true(xstring_str_equals_1(text1, "libxtd xstring length"));
    cester_assert_false(xstring_str_equals_1(text1, XTD_NULL));
    cester_assert_true(xstring_str_equals_1(XTD_NULL, XTD_NULL));
    cester_assert_true(xstring_str_equals_2(text1, "libxtd xstring length"));
    cester_assert_true(xstring_str_equals_3(text1, "libxtd xstring length"));
    cester_assert_true(xstring_str_equals_4(text1, "libxtd xstring length"));
    cester_assert_true(xstring_str_equals_1(text2, "Hello world"));
    cester_assert_false(xstring_str_equals_2(text2, "Hello world"));
    cester_assert_true(xstring_str_equals_3(text2, "Hello world"));
    cester_assert_true(xstring_str_equals_4(text2, "Hello world"));
    cester_assert_false(xstring_str_equals_4(text2, "Hello"));
    cester_assert_false(xstring_str_equals_4(text2, "Hellooo World"));
    cester_assert_false(xstring_str_equals_4(XTD_NULL, "Hellooo World"));
})

CESTER_TEST(xstring_str_equals_ignore_case, _, {
    char *text1 = "libxtd xstring length";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};

    cester_assert_true(xstring_str_equals_ignore_case(text1, "LIBXTD XSTRING LENGTH"));
    cester_assert_true(xstring_str_equals_ignore_case(text2, "HELLO WORLD"));
    cester_assert_true(xstring_str_equals_ignore_case("exotic libraries", "exotic libraries"));
    cester_assert_true(xstring_str_equals_ignore_case("EXOTIC libraries", "exotic LIBRARIES"));
    cester_assert_true(xstring_str_equals_ignore_case("EXOTIC LIBRARIES", "exotic libraries"));
    cester_assert_false(xstring_str_equals_ignore_case("lib", "libxtd"));
})

CESTER_TEST(xstring_str_compare, _, {
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

    cester_assert_false(xstring_str_equals(text1, text2));
    cester_assert_int_eq(xstring_str_compare(text2, text1), 20);
    cester_assert_int_eq(xstring_str_compare(text1, text1), 0);
    cester_assert_int_eq(xstring_str_compare("y", "e"), 20);
    cester_assert_int_eq(xstring_str_compare_2("y", "e"), 20);
    cester_assert_int_eq(xstring_str_compare_1(text3, text6), xstring_str_compare_2(text3, text6));
    cester_assert_int_gt(xstring_str_compare_1(text8, text7), xstring_str_compare_1(text9, text8));
})

CESTER_TEST(xstring_str_compare_ignore_case, _, {
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

    cester_assert_int_eq(xstring_str_compare_ignore_case(text2, text1), 20);
    cester_assert_int_eq(xstring_str_compare_ignore_case(text1, text1), 0);
    cester_assert_int_eq(xstring_str_compare_ignore_case("y", "E"), 20);
    cester_assert_int_eq(xstring_str_compare_ignore_case("Y", "e"), 20);
    cester_assert_int_eq(xstring_str_compare_ignore_case(text3, text6), xstring_str_compare_ignore_case(text3, text6));
    cester_assert_int_ne(xstring_str_compare(text3, text6), xstring_str_compare_ignore_case(text3, text6));
    cester_assert_int_gt(xstring_str_compare_ignore_case(text8, text7), xstring_str_compare_ignore_case(text9, text8));
})

CESTER_TEST(xstring_str_is_empty, _, {
    char *text1 = "libxtd xstring length";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "";
    char text4[20] = {};

    cester_assert_false(xstring_str_is_empty(text1));
    cester_assert_false(xstring_str_is_empty(text1));
    cester_assert_true(xstring_str_is_empty(text3));
    cester_assert_true(xstring_str_is_empty(text4));
    cester_assert_true(xstring_str_is_empty(""));
})

CESTER_TEST(xstring_str_index_of_from_pos_with_length, _, {
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "string";
    size_t text1_length = xstring_str_length(text1);
    size_t text2_length = xstring_str_length(text2);

    cester_assert_int_eq(xstring_str_index_of_from_pos_with_length(text1_length, text1, "xtd", 0), 3);
    cester_assert_int_eq(xstring_str_index_of_from_pos_with_length(text1_length, text1, "libxtd xstring length and longer", 0), -1);
    cester_assert_int_eq(xstring_str_index_of_from_pos_with_length(text1_length, text1, "libxtd xstring length xstring", 0), 0);
    cester_assert_int_eq(xstring_str_index_of_from_pos_with_length(text1_length, text1, text1, 0), 0);
    cester_assert_int_eq(xstring_str_index_of_from_pos_with_length(text1_length, text1, "i", 0), 1);
    cester_assert_int_eq(xstring_str_index_of_from_pos_with_length(text1_length, text1, "i", 4), 11);
    cester_assert_int_eq(xstring_str_index_of_from_pos_with_length(text1_length, text1, "xstring", 0), 7);
    cester_assert_int_eq(xstring_str_index_of_from_pos_with_length(text1_length, text1, "xstring", 10), 22);
    cester_assert_int_eq(xstring_str_index_of_from_pos_with_length(text1_length, text1, text2, 0), -1);
    cester_assert_int_eq(xstring_str_index_of_from_pos_with_length(text1_length, text1, text3, 0), 8);
    cester_assert_int_eq(xstring_str_index_of_from_pos_with_length(text1_length, text1, text3, 10), 23);
})

CESTER_TEST(xstring_str_index_of_from_pos, _, {
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "string";

    cester_assert_int_eq(xstring_str_index_of_from_pos(text1, "xtd", 0), 3);
    cester_assert_int_eq(xstring_str_index_of_from_pos(text1, "libxtd xstring length and longer", 0), -1);
    cester_assert_int_eq(xstring_str_index_of_from_pos(text1, "libxtd xstring length xstring", 0), 0);
    cester_assert_int_eq(xstring_str_index_of_from_pos(text1, text1, 0), 0);
    cester_assert_int_eq(xstring_str_index_of_from_pos(text1, "i", 0), 1);
    cester_assert_int_eq(xstring_str_index_of_from_pos(text1, "i", 4), 11);
    cester_assert_int_eq(xstring_str_index_of_from_pos(text1, "xstring", 0), 7);
    cester_assert_int_eq(xstring_str_index_of_from_pos(text1, "xstring", 10), 22);
    cester_assert_int_eq(xstring_str_index_of_from_pos(text1, text2, 0), -1);
    cester_assert_int_eq(xstring_str_index_of_from_pos(text1, text3, 0), 8);
    cester_assert_int_eq(xstring_str_index_of_from_pos(text1, text3, 10), 23);
})

CESTER_TEST(xstring_str_index_of, _, {
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "string";

    cester_assert_int_eq(xstring_str_index_of(text1, "xtd"), 3);
    cester_assert_int_eq(xstring_str_index_of(text1, "libxtd xstring length and longer"), -1);
    cester_assert_int_eq(xstring_str_index_of(text1, "libxtd xstring length xstring"), 0);
    cester_assert_int_eq(xstring_str_index_of(text1, text1), 0);
    cester_assert_int_eq(xstring_str_index_of(text1, "i"), 1);
    cester_assert_int_eq(xstring_str_index_of(text1, "xstring"), 7);
    cester_assert_int_eq(xstring_str_index_of(text1, text2), -1);
    cester_assert_int_eq(xstring_str_index_of(text1, text3), 8);
})

CESTER_TEST(xstring_str_last_index_of_from_pos_with_length, _, {
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "string";
    size_t text1_length = xstring_str_length(text1);
    size_t text2_length = xstring_str_length(text2);

    cester_assert_int_eq(xstring_str_last_index_of_from_pos_with_length(text1_length, text1, "xtd", 0), 3);
    cester_assert_int_eq(xstring_str_last_index_of_from_pos_with_length(text1_length, text1, "libxtd xstring length and longer", 0), -1);
    cester_assert_int_eq(xstring_str_last_index_of_from_pos_with_length(text1_length, text1, "libxtd xstring length xstring", 0), 0);
    cester_assert_int_eq(xstring_str_last_index_of_from_pos_with_length(text1_length, text1, text1, 0), 0);
    cester_assert_int_eq(xstring_str_last_index_of_from_pos_with_length(text1_length, text1, "i", 0), 26);
    cester_assert_int_eq(xstring_str_last_index_of_from_pos_with_length(text1_length, text1, "i", 4), 11);
    cester_assert_int_eq(xstring_str_last_index_of_from_pos_with_length(text1_length, text1, "xstring", 0), 22);
    cester_assert_int_eq(xstring_str_last_index_of_from_pos_with_length(text1_length, text1, "xstring", 10), 7);
    cester_assert_int_eq(xstring_str_last_index_of_from_pos_with_length(text1_length, text1, text2, 0), -1);
    cester_assert_int_eq(xstring_str_last_index_of_from_pos_with_length(text1_length, text1, text3, 0), 23);
    cester_assert_int_eq(xstring_str_last_index_of_from_pos_with_length(text1_length, text1, text3, 10), 8);
    cester_assert_int_eq(xstring_str_last_index_of_from_pos_with_length(text2_length, text2, "o", 0), 7);
    cester_assert_int_eq(xstring_str_last_index_of_from_pos_with_length(text2_length, text2, "o", 4), 4);
})

CESTER_TEST(xstring_str_last_index_of_from_pos, _, {
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "string";

    cester_assert_int_eq(xstring_str_last_index_of_from_pos(text1, "xtd", 0), 3);
    cester_assert_int_eq(xstring_str_last_index_of_from_pos(text1, "libxtd xstring length and longer", 0), -1);
    cester_assert_int_eq(xstring_str_last_index_of_from_pos(text1, "libxtd xstring length xstring", 0), 0);
    cester_assert_int_eq(xstring_str_last_index_of_from_pos(text1, text1, 0), 0);
    cester_assert_int_eq(xstring_str_last_index_of_from_pos(text1, "i", 0), 26);
    cester_assert_int_eq(xstring_str_last_index_of_from_pos(text1, "i", 4), 11);
    cester_assert_int_eq(xstring_str_last_index_of_from_pos(text1, "xstring", 0), 22);
    cester_assert_int_eq(xstring_str_last_index_of_from_pos(text1, "xstring", 10), 7);
    cester_assert_int_eq(xstring_str_last_index_of_from_pos(text1, text2, 0), -1);
    cester_assert_int_eq(xstring_str_last_index_of_from_pos(text1, text3, 0), 23);
    cester_assert_int_eq(xstring_str_last_index_of_from_pos(text1, text3, 10), 8);
    cester_assert_int_eq(xstring_str_last_index_of_from_pos(text2, "o", 0), 7);
    cester_assert_int_eq(xstring_str_last_index_of_from_pos(text2, "o", 4), 4);
})

CESTER_TEST(xstring_str_last_index_of, _, {
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "string";

    cester_assert_int_eq(xstring_str_last_index_of(text1, "xtd"), 3);
    cester_assert_int_eq(xstring_str_last_index_of(text1, "libxtd xstring length and longer"), -1);
    cester_assert_int_eq(xstring_str_last_index_of(text1, "libxtd xstring length xstring"), 0);
    cester_assert_int_eq(xstring_str_last_index_of(text1, text1), 0);
    cester_assert_int_eq(xstring_str_last_index_of(text1, "i"), 26);
    cester_assert_int_eq(xstring_str_last_index_of(text1, "xstring"), 22);
    cester_assert_int_eq(xstring_str_last_index_of(text1, text2), -1);
    cester_assert_int_eq(xstring_str_last_index_of(text1, text3), 23);
    cester_assert_int_eq(xstring_str_last_index_of("test_xstring_utils.h", "."), 18);
})

CESTER_TEST(xstring_str_contains, _, {
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "string";

    cester_assert_true(xstring_str_contains(text1, "xtd"));
    cester_assert_false(xstring_str_contains(text1, "libxtd xstring length and longer"));
    cester_assert_true(xstring_str_contains(text1, "libxtd xstring length xstring"));
    cester_assert_true(xstring_str_contains(text1, text1));
    cester_assert_true(xstring_str_contains(text1, "i"));
    cester_assert_true(xstring_str_contains(text1, "xstring"));
    cester_assert_false(xstring_str_contains(text1, text2));
    cester_assert_true(xstring_str_contains(text1, text3));
    cester_assert_true(xstring_str_contains("test_xstring_utils.h", "."));
    cester_assert_true(xstring_str_contains(text2, "Hello"));
    cester_assert_false(xstring_str_contains(text2, "hello"));
    cester_assert_false(xstring_str_contains(text2, "World"));
    cester_assert_true(xstring_str_contains(text2, "world"));
    cester_assert_true(xstring_str_contains(text2, "Hello world"));
})

CESTER_TEST(xstring_str_ends_with, _, {
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "string";

    cester_assert_false(xstring_str_ends_with(text1, "xtd"));
    cester_assert_false(xstring_str_ends_with(text1, "libxtd xstring length and longer"));
    cester_assert_true(xstring_str_ends_with(text1, "libxtd xstring length xstring"));
    cester_assert_true(xstring_str_ends_with(text1, text1));
    cester_assert_false(xstring_str_ends_with(text1, "i"));
    cester_assert_true(xstring_str_ends_with(text1, "g"));
    cester_assert_false(xstring_str_ends_with(text1, "libxtd"));
    cester_assert_true(xstring_str_ends_with(text1, "xstring"));
    cester_assert_true(xstring_str_ends_with("test_xstring_utils.h", ".h"));
    cester_assert_true(xstring_str_ends_with("test_xstring_utils.h", "h"));
    cester_assert_false(xstring_str_ends_with(text2, "Hello"));
    cester_assert_true(xstring_str_ends_with(text2, "world"));
    cester_assert_false(xstring_str_ends_with(text1, text2));
    cester_assert_true(xstring_str_ends_with(text1, text3));
    cester_assert_true(xstring_str_ends_with(text2, "Hello world"));
})

CESTER_TEST(xstring_str_starts_with, _, {
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "string";

    cester_assert_false(xstring_str_starts_with(text1, "xtd"));
    cester_assert_false(xstring_str_starts_with(text1, "libxtd xstring length and longer"));
    cester_assert_true(xstring_str_starts_with(text1, "libxtd xstring length xstring"));
    cester_assert_true(xstring_str_starts_with(text1, text1));
    cester_assert_false(xstring_str_starts_with(text1, "i"));
    cester_assert_true(xstring_str_starts_with(text1, "l"));
    cester_assert_true(xstring_str_starts_with(text1, "libxtd"));
    cester_assert_false(xstring_str_starts_with(text1, "xstring"));
    cester_assert_false(xstring_str_starts_with("test_xstring_utils.h", ".h"));
    cester_assert_true(xstring_str_starts_with("test_xstring_utils.h", "test_"));
    cester_assert_true(xstring_str_starts_with(text2, "Hello"));
    cester_assert_false(xstring_str_starts_with(text2, "world"));
    cester_assert_false(xstring_str_starts_with(text1, text2));
    cester_assert_false(xstring_str_starts_with(text1, text3));
    cester_assert_true(xstring_str_starts_with(text2, "Hello world"));
})

CESTER_TEST(xstring_str_sub_string_in_range_with_length, _, {
    enum x_stat status;
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    size_t text1_length = xstring_str_length(text1);
    size_t text2_length = xstring_str_length(text2);
    char *substr_value1 = (char *) malloc(text1_length * sizeof(char));
    char *substr_value2 = (char *) malloc(6 * sizeof(char));
    char *substr_value3 = (char *) malloc(6 * sizeof(char));
    char *substr_value4 = (char *) malloc(2 * sizeof(char));
    char *substr_value5 = (char *) malloc(5 * sizeof(char));
    
    status = xstring_str_sub_string_in_range_with_length(text1_length, text1, -1, text1_length, XTD_NULL);
    cester_assert_int_eq(status, XTD_OUT_OF_RANGE_ERR);
    status = xstring_str_sub_string_in_range_with_length(text1_length, text1, 0, text1_length+4, XTD_NULL);
    cester_assert_int_eq(status, XTD_OUT_OF_RANGE_ERR);
    status = xstring_str_sub_string_in_range_with_length(text1_length, text1, 0, text1_length, XTD_NULL);
    cester_assert_int_ne(status, XTD_OUT_OF_RANGE_ERR);
    status = xstring_str_sub_string_in_range_with_length(0, text1, 0, text1_length, XTD_NULL);
    cester_assert_int_eq(status, XTD_OUT_OF_RANGE_ERR);
    status = xstring_str_sub_string_in_range_with_length(text1_length, text1, text1_length+1, text1_length, XTD_NULL);
    cester_assert_int_eq(status, XTD_OUT_OF_RANGE_ERR);
    status = xstring_str_sub_string_in_range_with_length(text1_length, text1, 0, text1_length, XTD_NULL);
    cester_assert_int_eq(status, XTD_PARAM_NULL_ERR);
    status = xstring_str_sub_string_in_range_with_length(text1_length, text1, 0, text1_length, substr_value1);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal(text1, substr_value1);
    status = xstring_str_sub_string_in_range_with_length(text1_length, text1, 0, 6, substr_value2);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal(substr_value2, "libxtd");
    status = xstring_str_sub_string_in_range_with_length(text1_length, text1, 18, 24, substr_value3);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal(substr_value3, "gth xs");
    status = xstring_str_sub_string_in_range_with_length(20, "test_xstring_utils.h", 18, 20, substr_value4);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal(substr_value4, ".h");
    status = xstring_str_sub_string_in_range_with_length(text2_length, text2, 0, 5, substr_value5);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal(substr_value5, "Hello");
    status = xstring_str_sub_string_in_range_with_length(text2_length, text2, 6, text2_length, substr_value5);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal(substr_value5, "world");

    free(substr_value1);
    free(substr_value2);
    free(substr_value3);
    free(substr_value4);
    free(substr_value5);
})

CESTER_TEST(xstring_str_sub_string_in_range, _, {
    enum x_stat status;
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    size_t text1_length = xstring_str_length(text1);
    size_t text2_length = xstring_str_length(text2);
    char *substr_value1 = (char *) malloc(text1_length * sizeof(char));
    char *substr_value2 = (char *) malloc(6 * sizeof(char));
    char *substr_value3 = (char *) malloc(6 * sizeof(char));
    char *substr_value4 = (char *) malloc(2 * sizeof(char));
    char *substr_value5 = (char *) malloc(5 * sizeof(char));
    
    status = xstring_str_sub_string_in_range(text1, -1, text1_length, XTD_NULL);
    cester_assert_int_eq(status, XTD_OUT_OF_RANGE_ERR);
    status = xstring_str_sub_string_in_range(text1, 0, text1_length+4, XTD_NULL);
    cester_assert_int_eq(status, XTD_OUT_OF_RANGE_ERR);
    status = xstring_str_sub_string_in_range(text1, 0, text1_length, XTD_NULL);
    cester_assert_int_ne(status, XTD_OUT_OF_RANGE_ERR);
    status = xstring_str_sub_string_in_range(text1, 0, text1_length, XTD_NULL);
    cester_assert_int_ne(status, XTD_OUT_OF_RANGE_ERR);
    status = xstring_str_sub_string_in_range(text1, text1_length+1, text1_length, XTD_NULL);
    cester_assert_int_eq(status, XTD_OUT_OF_RANGE_ERR);
    status = xstring_str_sub_string_in_range(text1, 0, text1_length, XTD_NULL);
    cester_assert_int_eq(status, XTD_PARAM_NULL_ERR);
    status = xstring_str_sub_string_in_range(text1, 0, text1_length, substr_value1);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal(text1, substr_value1);
    status = xstring_str_sub_string_in_range(text1, 0, 6, substr_value2);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal(substr_value2, "libxtd");
    status = xstring_str_sub_string_in_range(text1, 18, 24, substr_value3);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal(substr_value3, "gth xs");
    status = xstring_str_sub_string_in_range("test_xstring_utils.h", 18, 20, substr_value4);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal(substr_value4, ".h");
    status = xstring_str_sub_string_in_range(text2, 0, 5, substr_value5);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal(substr_value5, "Hello");
    status = xstring_str_sub_string_in_range(text2, 6, text2_length, substr_value5);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal(substr_value5, "world");

    free(substr_value1);
    free(substr_value2);
    free(substr_value3);
    free(substr_value4);
    free(substr_value5);
})

CESTER_TEST(xstring_str_sub_string, _, {
    enum x_stat status;
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    size_t text1_length = xstring_str_length(text1);
    size_t text2_length = xstring_str_length(text2);
    char *substr_value1 = (char *) malloc(text1_length * sizeof(char));
    char *substr_value2 = (char *) malloc(7 * sizeof(char));
    char *substr_value4 = (char *) malloc(2 * sizeof(char));
    char *substr_value5 = (char *) malloc(5 * sizeof(char));
    
    status = xstring_str_sub_string(text1, -1, XTD_NULL);
    cester_assert_int_eq(status, XTD_OUT_OF_RANGE_ERR);
    status = xstring_str_sub_string(text1, 0, XTD_NULL);
    cester_assert_int_ne(status, XTD_OUT_OF_RANGE_ERR);
    status = xstring_str_sub_string(text1, 0, XTD_NULL);
    cester_assert_int_ne(status, XTD_OUT_OF_RANGE_ERR);
    status = xstring_str_sub_string(text1, text1_length+1, XTD_NULL);
    cester_assert_int_eq(status, XTD_OUT_OF_RANGE_ERR);
    status = xstring_str_sub_string(text1, 0, XTD_NULL);
    cester_assert_int_eq(status, XTD_PARAM_NULL_ERR);
    status = xstring_str_sub_string(text1, 0, substr_value1);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal(text1, substr_value1);
    status = xstring_str_sub_string(text1, 22, substr_value2);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal(substr_value2, "xstring");
    status = xstring_str_sub_string("test_xstring_utils.h", 18, substr_value4);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal(substr_value4, ".h");
    status = xstring_str_sub_string(text2, 0, substr_value5);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_not_equal(substr_value5, "Hello");
    status = xstring_str_sub_string(text2, 6, substr_value5);
    cester_assert_int_eq(status, XTD_OK);
    cester_assert_str_equal(substr_value5, "world");

    free(substr_value1);
    free(substr_value2);
    free(substr_value4);
    free(substr_value5);
})

CESTER_TEST(xstring_str_char_at, _, {
    char *text1 = "libxtd xstring length";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};

    cester_assert_char_eq(xstring_str_char_at(text1, 0), 'l');
    cester_assert_char_eq(xstring_str_char_at(text1, 20), 'h');
    cester_assert_char_eq(xstring_str_char_at(text2, 0), 'H');
    cester_assert_char_eq(xstring_str_char_at(text2, 7), 'o');
})

CESTER_COMMENT(
    all cester cester_assert_ptr_not_equal, cester_assert_str_equal 
    is causing segfault in a pointer to pointer scenerio, fix in libcester
)

CESTER_TODO_TEST(xstring_str_split_with_length, _, {
    XAllocator allocator;
    char **splited1;
    char **splited2;
    char **splited3;
    char *text1 = "libxtd xstring length and string for xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    size_t text1_length = xstring_str_length(text1);
    size_t text2_length = xstring_str_length(text2);
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    cester_assert_ptr_equal(xstring_str_split_with_length(text1_length, text1, XTD_NULL, allocator), XTD_NULL);
    cester_assert_ptr_equal(xstring_str_split_with_length(text1_length, XTD_NULL, XTD_NULL, allocator), XTD_NULL);
    splited1 = xstring_str_split_with_length(text1_length, text1, " ", allocator);
    cester_assert_ptr_not_equal(splited1, XTD_NULL);
    cester_assert_int_eq(xptp_array_size((void **)splited1), 7);
    cester_assert_str_equal(splited1[0], "libxtd");
    cester_assert_str_equal(splited1[2], "length");
    cester_assert_str_equal(splited1[3], "and");
    cester_assert_str_equal(splited1[6], "xstring");
    splited2 = xstring_str_split_with_length(text2_length, text2, "o w", allocator);
    cester_assert_ptr_not_equal(splited2, XTD_NULL);
    cester_assert_int_eq(xptp_array_size((void **)splited2), 2);
    cester_assert_str_equal(splited2[0], "Hell");
    cester_assert_str_equal(splited2[1], "orld");
    splited3 = xstring_str_split_with_length(17, "Whole cake island", "", allocator);
    cester_assert_ptr_not_equal(splited3, XTD_NULL);
    cester_assert_int_eq(xptp_array_size((void **)splited3), 1);
    cester_assert_str_equal(splited3[0], "Whole cake island");
    cester_assert_ptr_equal(splited3[1], XTD_NULL);

    xfreep2p((void **)splited1, allocator);
    xfreep2p((void **)splited2, allocator);
    xfreep2p((void **)splited3, allocator);
})

CESTER_TEST(xstring_str_split, _, {
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

    cester_assert_ptr_equal(xstring_str_split(text1, XTD_NULL, allocator), XTD_NULL);
    cester_assert_ptr_equal(xstring_str_split(XTD_NULL, XTD_NULL, allocator), XTD_NULL);
    splited1 = xstring_str_split(text1, " ", allocator);
    cester_assert_ptr_not_equal(splited1, XTD_NULL);
    cester_assert_int_eq(xptp_array_size((void **)splited1), 7);
    cester_assert_str_equal(splited1[0], "libxtd");
    cester_assert_str_equal(splited1[2], "length");
    cester_assert_str_equal(splited1[3], "and");
    cester_assert_str_equal(splited1[6], "xstring");
    splited2 = xstring_str_split(text2, "o w", allocator);
    cester_assert_ptr_not_equal(splited2, XTD_NULL);
    cester_assert_int_eq(xptp_array_size((void **)splited2), 2);
    cester_assert_str_equal(splited2[0], "Hell");
    cester_assert_str_equal(splited2[1], "orld");
    splited3 = xstring_str_split("Whole cake island", "", allocator);
    cester_assert_ptr_not_equal(splited3, XTD_NULL);
    cester_assert_int_eq(xptp_array_size((void **)splited3), 1);
    cester_assert_str_equal(splited3[0], "Whole cake island");
    cester_assert_ptr_equal(splited3[1], XTD_NULL);

    xfreep2p((void **)splited1, allocator);
    xfreep2p((void **)splited2, allocator);
    xfreep2p((void **)splited3, allocator);
})

CESTER_TODO_TEST(xstring_str_char_value, _, {
    
})

CESTER_TODO_TEST(xstring_str_int_value, _, {
    
})

CESTER_TODO_TEST(xstring_str_long_value, _, {
    
})

CESTER_TODO_TEST(xstring_str_double_value, _, {
    
})

CESTER_TODO_TEST(xstring_str_float_value, _, {
    
})

CESTER_TODO_TEST(xstring_str_pointer_value, _, {
    
})

CESTER_TODO_TEST(xstring_str_concat_str, _, {
    
})

CESTER_TODO_TEST(xstring_str_concat_char, _, {
    
})

CESTER_TODO_TEST(xstring_str_concat_int, _, {
    
})

CESTER_TODO_TEST(xstring_str_concat_long, _, {
    
})

CESTER_TODO_TEST(xstring_str_concat_double, _, {
    
})

CESTER_TODO_TEST(xstring_str_concat_float, _, {
    
})

CESTER_TODO_TEST(xstring_str_concat_pointer, _, {
    
})

CESTER_TODO_TEST(xstring_str_format, _, {
    
})

CESTER_TODO_TEST(xstring_str_hashcode, _, {
    
})

CESTER_TODO_TEST(xstring_str_replace, _, {
    
})

CESTER_TODO_TEST(xstring_str_replace_first, _, {
    
})

CESTER_TODO_TEST(xstring_str_replace_last, _, {
    
})

CESTER_TODO_TEST(xstring_str_to_lower_case, _, {
    
})

CESTER_TODO_TEST(xstring_str_to_upper_case, _, {
    
})

CESTER_TODO_TEST(xstring_str_trim, _, {
    
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)


