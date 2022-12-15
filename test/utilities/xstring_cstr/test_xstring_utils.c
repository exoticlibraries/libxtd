/*!gcc {0} -I. -I../include/ -I../../../include/ -I../../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I.-I../../include/  -I../../include/ -I../../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../include/ -I../....//include/ -I../../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../include/ -I../../../include/ -I../../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/container/xstring.h>
#include <exotic/xtd/xiterator.h>

CESTER_COMMENT(
    all cester cester_assert_ptr_not_equal, cester_assert_str_equal_ 
    is causing segfault in a pointer to pointer scenerio, fix in libcester
)

#define cester_assert_str_equal_(x,y) cester_assert_true(xstring_cstr_equals(x,y))

#ifdef __XTD_STDC_VERSION__
#define TEST_CASE_CHAR_ARRAY_HELLO_WORLD {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'}
#else
#define TEST_CASE_CHAR_ARRAY_HELLO_WORLD "Hello world"
#endif

CESTER_TEST(xstring_cstr_length_1, _, {
    char *text1 = "libxtd xstring length";
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD;

    cester_assert_int_eq(xstring_cstr_length(text1), 21);
    cester_assert_int_eq(xstring_cstr_length(text2), 11);
    cester_assert_int_eq(xstring_cstr_length(XTD_NULL), 0);
})

CESTER_TEST(xstring_cstr_length_2, _, {
    char *text1 = "libxtd xstring length";
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD;

    cester_assert_int_eq(xstring_cstr_length_2(text1), 21);
    cester_assert_int_eq(xstring_cstr_length_2(text2), 11);
    cester_assert_int_eq(xstring_cstr_length_2(XTD_NULL), 0);
})

CESTER_TEST(xstring_cstr_length_3, _, {
    char *text1 = "libxtd xstring length";
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD;

    cester_assert_int_eq(xstring_cstr_length_3(text1), 21);
    cester_assert_int_eq(xstring_cstr_length_3(text2), 11);
    cester_assert_int_eq(xstring_cstr_length_3(XTD_NULL), 0);
})

CESTER_TEST(xstring_cstr_length, _, {
    char *text1 = "libxtd xstring length";
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD;

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
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD;

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
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD;

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
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD;
    char *text3 = "";
    char text4[20] = {};

    cester_assert_false(xstring_cstr_is_empty(text1));
    cester_assert_false(xstring_cstr_is_empty(text1));
    cester_assert_true(xstring_cstr_is_empty(text3));
    cester_assert_true(xstring_cstr_is_empty(text4));
    cester_assert_true(xstring_cstr_is_empty(""));
})

CESTER_TODO_TEST(xstring_cstr_hashcode, _, {
    
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)

/*
write tests for 
xstring_cstr_copy
xstring_cstr_trim_memory_to_size
*/
