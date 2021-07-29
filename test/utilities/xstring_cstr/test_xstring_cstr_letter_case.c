/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I.-I../include/  -I../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/xstring.h>
#include <exotic/xtd/xiterator.h>

#define cester_assert_str_equal_(x,y) cester_assert_true(xstring_cstr_equals(x,y))
#define cester_assert_str_not_equal_(x,y) cester_assert_false(xstring_cstr_equals(x,y))

#ifdef __XTD_STDC_VERSION__
#define TEST_CASE_CHAR_ARRAY_HELLO_WORLD_1 {'H', 'E', 'L', 'L', 'O', ' ', 'W', 'O', 'R', 'L', 'D'}
#define TEST_CASE_CHAR_ARRAY_HELLO_WORLD_2 {'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'}
#else
#define TEST_CASE_CHAR_ARRAY_HELLO_WORLD_1 "HELLO WORLD"
#define TEST_CASE_CHAR_ARRAY_HELLO_WORLD_2 "hello world"
#endif

CESTER_TEST(xstring_cstr_to_lower_case__ref, _, {
    char *value;
    char *text1 = "LIBXTD XSTRING LENGTH XSTRING";
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD_1;
    char *text3 = "STRING";
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    cester_assert_uint_eq(xstring_cstr_to_lower_case(allocator, XTD_NULL, XTD_NULL), XTD_NO_OP);
    cester_assert_uint_eq(xstring_cstr_to_lower_case(allocator, text1, XTD_NULL), XTD_NO_OP);
    cester_assert_uint_eq(xstring_cstr_to_lower_case(allocator, "", XTD_NULL), XTD_NO_OP);
    cester_assert_uint_eq(xstring_cstr_to_lower_case(allocator, "", &value), XTD_NO_OP);
    cester_assert_str_not_equal_(text1, "libxtd xstring length xstring");
    cester_assert_uint_eq(xstring_cstr_to_lower_case(allocator, text1, &value), XTD_OK);
    cester_assert_str_equal_(value, "libxtd xstring length xstring"); allocator.memory_free(value);
    cester_assert_str_not_equal_(text2, "hello world");
    cester_assert_str_equal_(xstring_cstr_to_lower_case_ref(text2), "hello world");
    cester_assert_str_not_equal_(text3, "string");
    cester_assert_uint_eq(xstring_cstr_to_lower_case(allocator, text3, &value), XTD_OK);
    cester_assert_str_equal_(value, "string"); allocator.memory_free(value);
})

CESTER_TEST(xstring_cstr_to_upper_case__ref, _, {
    char *value;
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD_2;
    char *text3 = "string";
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    cester_assert_uint_eq(xstring_cstr_to_upper_case(allocator, XTD_NULL, XTD_NULL), XTD_NO_OP);
    cester_assert_uint_eq(xstring_cstr_to_upper_case(allocator, text1, XTD_NULL), XTD_NO_OP);
    cester_assert_uint_eq(xstring_cstr_to_upper_case(allocator, "", XTD_NULL), XTD_NO_OP);
    cester_assert_uint_eq(xstring_cstr_to_upper_case(allocator, "", &value), XTD_NO_OP);
    cester_assert_str_not_equal_(text1, "LIBXTD XSTRING LENGTH XSTRING");
    cester_assert_uint_eq(xstring_cstr_to_upper_case(allocator, text1, &value), XTD_OK);
    cester_assert_str_equal_(value, "LIBXTD XSTRING LENGTH XSTRING"); allocator.memory_free(value);
    cester_assert_str_not_equal_(text2, "HELLO WORLD");
    cester_assert_str_equal_(xstring_cstr_to_upper_case_ref(text2), "HELLO WORLD");
    cester_assert_str_not_equal_(text3, "STRING");
    cester_assert_uint_eq(xstring_cstr_to_upper_case(allocator, text3, &value), XTD_OK);
    cester_assert_str_equal_(value, "STRING"); allocator.memory_free(value);
})

CESTER_TODO_TEST(xstring_cstr_to_sentence_case__ref, _, {
    char *value;
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD_2;
    char *text3 = "string";
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    cester_assert_uint_eq(xstring_cstr_to_sentence_case(allocator, XTD_NULL, XTD_NULL), XTD_NO_OP);
    cester_assert_uint_eq(xstring_cstr_to_sentence_case(allocator, text1, XTD_NULL), XTD_NO_OP);
    cester_assert_uint_eq(xstring_cstr_to_sentence_case(allocator, "", XTD_NULL), XTD_NO_OP);
    cester_assert_uint_eq(xstring_cstr_to_sentence_case(allocator, "", &value), XTD_NO_OP);
    cester_assert_str_not_equal_(text1, "Libxtd xstring length xstring");
    cester_assert_uint_eq(xstring_cstr_to_sentence_case(allocator, text1, &value), XTD_OK);
    cester_assert_str_equal_(value, "Libxtd xstring length xstring"); allocator.memory_free(value);
    cester_assert_str_not_equal_(text2, "Hello world");
    cester_assert_str_equal_(xstring_cstr_to_sentence_case_ref(text2), "Hello world");
    cester_assert_str_not_equal_(text3, "String");
    cester_assert_uint_eq(xstring_cstr_to_sentence_case(allocator, text3, &value), XTD_OK);
    cester_assert_str_equal_(value, "String"); allocator.memory_free(value);
})

CESTER_TODO_TEST(xstring_cstr_to_title_case__ref, _, {
    char *value;
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD_2;
    char *text3 = "string";
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    cester_assert_uint_eq(xstring_cstr_to_title_case(allocator, XTD_NULL, XTD_NULL), XTD_NO_OP);
    cester_assert_uint_eq(xstring_cstr_to_title_case(allocator, text1, XTD_NULL), XTD_NO_OP);
    cester_assert_uint_eq(xstring_cstr_to_title_case(allocator, "", XTD_NULL), XTD_NO_OP);
    cester_assert_uint_eq(xstring_cstr_to_title_case(allocator, "", &value), XTD_NO_OP);
    cester_assert_str_not_equal_(text1, "Libxtd Xstring Length Xstring");
    cester_assert_uint_eq(xstring_cstr_to_title_case(allocator, text1, &value), XTD_OK);
    cester_assert_str_equal_(value, "Libxtd Xstring Length Xstring"); allocator.memory_free(value);
    cester_assert_str_not_equal_(text2, "Hello World");
    cester_assert_str_equal_(xstring_cstr_to_title_case_ref(text2), "Hello World");
    cester_assert_str_not_equal_(text3, "String");
    cester_assert_uint_eq(xstring_cstr_to_title_case(allocator, text3, &value), XTD_OK);
    cester_assert_str_equal_(value, "String"); allocator.memory_free(value);
})

/*https://en.wikipedia.org/wiki/Naming_convention_(programming)#Multiple-word_identifiers*/
/*https://stackoverflow.com/questions/17326185/what-are-the-different-kinds-of-cases*/
CESTER_TODO_TEST(xstring_cstr_to_camel_case__ref, _, {

})

CESTER_TODO_TEST(xstring_cstr_to_pascal_case__ref, _, {

})

CESTER_TODO_TEST(xstring_cstr_to_macro_case__ref, _, {

})

CESTER_TODO_TEST(xstring_cstr_to_cobol_case__ref, _, {

})

CESTER_TODO_TEST(xstring_cstr_to_lower_camel_case__ref, _, {

})

CESTER_TODO_TEST(xstring_cstr_to_kebab_case__ref, _, {

})

CESTER_TODO_TEST(xstring_cstr_to_snake_case__ref, _, {

})

CESTER_TODO_TEST(xstring_cstr_to_skicky_caps_case__ref, _, {

})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)


