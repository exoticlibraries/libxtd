/*!gcc {0} -I. -I../include/ -I../../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I.-I../include/  -I../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/container/xstring.h>
#include <exotic/xtd/xiterator.h>

#define cester_assert_str_equal_(x,y) cester_assert_true(xstring_cstr_equals(x,y))

#ifdef __XTD_STDC_VERSION__
#define TEST_CASE_CHAR_ARRAY_HELLO_WORLD {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'}
#else
#define TEST_CASE_CHAR_ARRAY_HELLO_WORLD "Hello world"
#endif

CESTER_TEST(xstring_cstr_sub_string_in_range_with_length, _, {
    enum x_stat status;
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD;
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
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD;
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
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD;
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
    status = xstring_cstr_sub_string(text2, 5, substr_value5);
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
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD;

    cester_assert_char_eq(xstring_cstr_char_at(text1, 0), 'l');
    cester_assert_char_eq(xstring_cstr_char_at(text1, 20), 'h');
    cester_assert_char_eq(xstring_cstr_char_at(text2, 0), 'H');
    cester_assert_char_eq(xstring_cstr_char_at(text2, 7), 'o');
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)

