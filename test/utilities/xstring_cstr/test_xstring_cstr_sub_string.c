/*!gcc {0} -I. -I../include/ -I../../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I.-I../include/  -I../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/container/xstring.h>
#include <exotic/xtd/xiterator.h>

#ifdef __XTD_STDC_VERSION__
#define TEST_CASE_CHAR_ARRAY_HELLO_WORLD {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'}
#else
#define TEST_CASE_CHAR_ARRAY_HELLO_WORLD "Hello world"
#endif

CESTER_TEST(xstring_cstr_sub_string_in_range_with_length, _, {
    char *value;
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD;
    size_t text1_length = xstring_cstr_length(text1);
    size_t text2_length = xstring_cstr_length(text2);
    XAllocator allocator;
    allocator.memory_free = free;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    
    cester_assert_int_eq(xstring_cstr_sub_string_in_range_with_length(allocator, text1_length, text1, -1, text1_length, XTD_NULL), XTD_OUT_OF_RANGE_ERR);
    cester_assert_int_eq(xstring_cstr_sub_string_in_range_with_length(allocator, text1_length, text1, 0, text1_length+4, XTD_NULL), XTD_OUT_OF_RANGE_ERR);
    cester_assert_int_ne(xstring_cstr_sub_string_in_range_with_length(allocator, text1_length, text1, 0, text1_length, XTD_NULL), XTD_OUT_OF_RANGE_ERR);
    cester_assert_int_eq(xstring_cstr_sub_string_in_range_with_length(allocator, 0, text1, 0, text1_length, XTD_NULL), XTD_OUT_OF_RANGE_ERR);
    cester_assert_int_eq(xstring_cstr_sub_string_in_range_with_length(allocator, text1_length, text1, text1_length+1, text1_length, XTD_NULL), XTD_OUT_OF_RANGE_ERR);
    cester_assert_int_eq(xstring_cstr_sub_string_in_range_with_length(allocator, text1_length, text1, 0, text1_length, XTD_NULL), XTD_PARAM_NULL_ERR);
    cester_assert_int_eq(xstring_cstr_sub_string_in_range_with_length(allocator, text1_length, text1, 0, text1_length, &value), XTD_OK);
    cester_assert_str_equal(text1, value); free(value);
    cester_assert_int_eq(xstring_cstr_sub_string_in_range_with_length(allocator, text1_length, text1, 0, 6, &value), XTD_OK);
    cester_assert_str_equal(value, "libxtd"); free(value);
    cester_assert_int_eq(xstring_cstr_sub_string_in_range_with_length(allocator, text1_length, text1, 18, 24, &value), XTD_OK);
    cester_assert_str_equal(value, "gth xs"); free(value);
    cester_assert_int_eq(xstring_cstr_sub_string_in_range_with_length(allocator, 20, "test_xstring_utils.h", 18, 20, &value), XTD_OK);
    cester_assert_str_equal(value, ".h"); free(value);
    cester_assert_int_eq(xstring_cstr_sub_string_in_range_with_length(allocator, text2_length, text2, 0, 5, &value), XTD_OK);
    cester_assert_str_equal(value, "Hello"); free(value);
    cester_assert_int_eq(xstring_cstr_sub_string_in_range_with_length(allocator, text2_length, text2, 6, text2_length, &value), XTD_OK);
    cester_assert_str_equal(value, "world"); free(value);
})

CESTER_TEST(xstring_cstr_sub_string_in_range, _, {
    char *value;
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD;
    size_t text1_length = xstring_cstr_length(text1);
    size_t text2_length = xstring_cstr_length(text2);
    XAllocator allocator;
    allocator.memory_free = free;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    
    cester_assert_int_eq(xstring_cstr_sub_string_in_range(allocator, text1, -1, text1_length, XTD_NULL), XTD_OUT_OF_RANGE_ERR);
    cester_assert_int_eq(xstring_cstr_sub_string_in_range(allocator, text1, 0, text1_length+4, XTD_NULL), XTD_OUT_OF_RANGE_ERR);
    cester_assert_int_ne(xstring_cstr_sub_string_in_range(allocator, text1, 0, text1_length, XTD_NULL), XTD_OUT_OF_RANGE_ERR);
    cester_assert_int_ne(xstring_cstr_sub_string_in_range(allocator, text1, 0, text1_length, XTD_NULL), XTD_OUT_OF_RANGE_ERR);
    cester_assert_int_eq(xstring_cstr_sub_string_in_range(allocator, text1, text1_length+1, text1_length, XTD_NULL), XTD_OUT_OF_RANGE_ERR);
    cester_assert_int_eq(xstring_cstr_sub_string_in_range(allocator, text1, 0, text1_length, XTD_NULL), XTD_PARAM_NULL_ERR);
    cester_assert_int_eq(xstring_cstr_sub_string_in_range(allocator, text1, 0, text1_length, &value), XTD_OK);
    cester_assert_str_equal(text1, value); free(value);
    cester_assert_int_eq(xstring_cstr_sub_string_in_range(allocator, text1, 0, 6, &value), XTD_OK);
    cester_assert_str_equal(value, "libxtd"); free(value);
    cester_assert_int_eq(xstring_cstr_sub_string_in_range(allocator, text1, 18, 24, &value), XTD_OK);
    cester_assert_str_equal(value, "gth xs"); free(value);
    cester_assert_int_eq(xstring_cstr_sub_string_in_range(allocator, "test_xstring_utils.h", 18, 20, &value), XTD_OK);
    cester_assert_str_equal(value, ".h"); free(value);
    cester_assert_int_eq(xstring_cstr_sub_string_in_range(allocator, text2, 0, 5, &value), XTD_OK);
    cester_assert_str_equal(value, "Hello"); free(value);
    cester_assert_int_eq(xstring_cstr_sub_string_in_range(allocator, text2, 6, text2_length, &value), XTD_OK);
    cester_assert_str_equal(value, "world"); free(value);
})

CESTER_TEST(xstring_cstr_sub_string, _, {
    char *value;
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD;
    size_t text1_length = xstring_cstr_length(text1);
    size_t text2_length = xstring_cstr_length(text2);
    XAllocator allocator;
    allocator.memory_free = free;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    
    cester_assert_int_ne(xstring_cstr_sub_string(allocator, text1, 0, XTD_NULL), XTD_OUT_OF_RANGE_ERR);
    cester_assert_int_ne(xstring_cstr_sub_string(allocator, text1, 0, XTD_NULL), XTD_OUT_OF_RANGE_ERR);
    cester_assert_int_eq(xstring_cstr_sub_string(allocator, text1, -1, XTD_NULL), XTD_OUT_OF_RANGE_ERR);
    cester_assert_int_eq(xstring_cstr_sub_string(allocator, text1, text1_length+1, XTD_NULL), XTD_OUT_OF_RANGE_ERR);
    cester_assert_int_eq(xstring_cstr_sub_string(allocator, text1, 0, XTD_NULL), XTD_PARAM_NULL_ERR);
    cester_assert_int_eq(xstring_cstr_sub_string(allocator, text1, 0, &value), XTD_OK);
    cester_assert_str_equal(text1, value); free(value);
    cester_assert_int_eq(xstring_cstr_sub_string(allocator, text1, 22, &value), XTD_OK);
    cester_assert_str_equal(value, "xstring"); free(value);
    cester_assert_int_eq(xstring_cstr_sub_string(allocator, "test_xstring_utils.h", 18, &value), XTD_OK);
    cester_assert_str_equal(value, ".h"); free(value);
    cester_assert_int_eq(xstring_cstr_sub_string(allocator, text2, 5, &value), XTD_OK);
    cester_assert_str_not_equal(value, "Hello"); free(value);
    cester_assert_int_eq(xstring_cstr_sub_string(allocator, text2, 6, &value), XTD_OK);
    cester_assert_str_equal(value, "world"); free(value);

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

