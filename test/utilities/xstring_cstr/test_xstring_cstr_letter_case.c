/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I.-I../include/  -I../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/container/xstring.h>
#include <exotic/xtd/xiterator.h>

#ifdef __XTD_STDC_VERSION__
#define TEST_CASE_CHAR_ARRAY_HELLO_WORLD_1 {'H', 'E', 'L', 'L', 'O', ' ', 'W', 'O', 'R', 'L', 'D'}
#define TEST_CASE_CHAR_ARRAY_HELLO_WORLD_2 {'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'}
#else
#define TEST_CASE_CHAR_ARRAY_HELLO_WORLD_1 "HELLO WORLD"
#define TEST_CASE_CHAR_ARRAY_HELLO_WORLD_2 "hello world"
#endif

CESTER_TEST(xstring_cstr_to_lower_case, _, {
    char *value;
    char *text1 = "LIBXTD XSTRING LENGTH XSTRING";
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD_1;
    char *text3 = "STRING";
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    cester_assert_uint_eq(xstring_cstr_to_lower_case(allocator, XTD_NULL, XTD_NULL), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_to_lower_case(allocator, text1, XTD_NULL), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_to_lower_case(allocator, "", XTD_NULL), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_to_lower_case(allocator, "", &value), XTD_NO_OP_ERR);
    cester_assert_str_not_equal(text1, "libxtd xstring length xstring");
    cester_assert_uint_eq(xstring_cstr_to_lower_case(allocator, text1, &value), XTD_OK);
    cester_assert_str_equal(value, "libxtd xstring length xstring"); allocator.memory_free(value);
    cester_assert_str_not_equal(text2, "hello world");
    cester_assert_str_equal(xstring_cstr_to_lower_case_mut(text2), "hello world");
    cester_assert_str_not_equal(text3, "string");
    cester_assert_uint_eq(xstring_cstr_to_lower_case(allocator, text3, &value), XTD_OK);
    cester_assert_str_equal(value, "string"); allocator.memory_free(value);
})

CESTER_TEST(xstring_cstr_to_upper_case, _, {
    char *value;
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD_2;
    char *text3 = "string";
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    cester_assert_uint_eq(xstring_cstr_to_upper_case(allocator, XTD_NULL, XTD_NULL), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_to_upper_case(allocator, text1, XTD_NULL), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_to_upper_case(allocator, "", XTD_NULL), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_to_upper_case(allocator, "", &value), XTD_NO_OP_ERR);
    cester_assert_str_not_equal(text1, "LIBXTD XSTRING LENGTH XSTRING");
    cester_assert_uint_eq(xstring_cstr_to_upper_case(allocator, text1, &value), XTD_OK);
    cester_assert_str_equal(value, "LIBXTD XSTRING LENGTH XSTRING"); allocator.memory_free(value);
    cester_assert_str_not_equal(text2, "HELLO WORLD");
    cester_assert_str_equal(xstring_cstr_to_upper_case_mut(text2), "HELLO WORLD");
    cester_assert_str_not_equal(text3, "STRING");
    cester_assert_uint_eq(xstring_cstr_to_upper_case(allocator, text3, &value), XTD_OK);
    cester_assert_str_equal(value, "STRING"); allocator.memory_free(value);
})

CESTER_TEST(xstring_cstr_to_sentence_case, _, {
    char *value;
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD_2;
    char *text3 = "string";
    char *text4 = "this Sentence. Have @ symbols 123";
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    cester_assert_uint_eq(xstring_cstr_to_sentence_case(allocator, XTD_NULL, XTD_NULL), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_to_sentence_case(allocator, text1, XTD_NULL), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_to_sentence_case(allocator, "", XTD_NULL), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_to_sentence_case(allocator, "", &value), XTD_NO_OP_ERR);
    cester_assert_str_not_equal(text1, "Libxtd xstring length xstring");
    cester_assert_uint_eq(xstring_cstr_to_sentence_case(allocator, text1, &value), XTD_OK);
    cester_assert_str_equal(value, "Libxtd xstring length xstring"); allocator.memory_free(value);
    cester_assert_str_not_equal(text2, "Hello world");
    cester_assert_str_equal(xstring_cstr_to_sentence_case_mut(text2), "Hello world");
    cester_assert_str_not_equal(text3, "String");
    cester_assert_uint_eq(xstring_cstr_to_sentence_case(allocator, text3, &value), XTD_OK);
    cester_assert_str_equal(value, "String"); allocator.memory_free(value);
    cester_assert_str_not_equal(text4, "This sentence. have @ symbols 123");
    cester_assert_uint_eq(xstring_cstr_to_sentence_case(allocator, text4, &value), XTD_OK);
    cester_assert_str_equal(value, "This sentence. have @ symbols 123"); allocator.memory_free(value);
})

CESTER_TEST(xstring_cstr_to_title_case, _, {
    char *value;
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD_2;
    char *text3 = "string";
    char *text4 = "this Sentence. Have @ symbols 123";
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    cester_assert_uint_eq(xstring_cstr_to_title_case(allocator, XTD_NULL, XTD_NULL), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_to_title_case(allocator, text1, XTD_NULL), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_to_title_case(allocator, "", XTD_NULL), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_to_title_case(allocator, "", &value), XTD_NO_OP_ERR);
    cester_assert_str_not_equal(text1, "Libxtd Xstring Length Xstring");
    cester_assert_uint_eq(xstring_cstr_to_title_case(allocator, text1, &value), XTD_OK);
    cester_assert_str_equal(value, "Libxtd Xstring Length Xstring"); allocator.memory_free(value);
    cester_assert_str_not_equal(text2, "Hello World");
    cester_assert_str_equal(xstring_cstr_to_title_case_mut(text2), "Hello World");
    cester_assert_str_not_equal(text3, "String");
    cester_assert_uint_eq(xstring_cstr_to_title_case(allocator, text3, &value), XTD_OK);
    cester_assert_str_equal(value, "String"); allocator.memory_free(value);
    cester_assert_str_not_equal(text4, "This Sentence. Have @ Symbols 123");
    cester_assert_uint_eq(xstring_cstr_to_title_case(allocator, text4, &value), XTD_OK);
    cester_assert_str_equal(value, "This Sentence. Have @ Symbols 123"); allocator.memory_free(value);
})

CESTER_TEST(xstring_cstr_invert_case, _, {
    char *value;
    char *text1 = "Libxtd Xstring length xString";
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD_1;
    char *text3 = "String";
    char *text4 = "this Sentence. Have @ symbols 123";
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    cester_assert_uint_eq(xstring_cstr_invert_case(allocator, XTD_NULL, XTD_NULL), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_invert_case(allocator, text1, XTD_NULL), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_invert_case(allocator, "", XTD_NULL), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_invert_case(allocator, "", &value), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_invert_case(allocator, text1, &value), XTD_OK);
    cester_assert_str_equal(value, "lIBXTD xSTRING LENGTH XsTRING"); allocator.memory_free(value);
    cester_assert_str_equal(xstring_cstr_invert_case_mut(text2), "hello world");
    cester_assert_uint_eq(xstring_cstr_invert_case(allocator, text3, &value), XTD_OK);
    cester_assert_str_equal(value, "sTRING"); allocator.memory_free(value);
    cester_assert_uint_eq(xstring_cstr_invert_case(allocator, text4, &value), XTD_OK);
    cester_assert_str_equal(value, "THIS sENTENCE. hAVE @ SYMBOLS 123"); allocator.memory_free(value);
})

/*https://en.wikipedia.org/wiki/Naming_convention_(programming)#Multiple-word_identifiers*/
/*https://stackoverflow.com/questions/17326185/what-are-the-different-kinds-of-cases*/
/*CESTER_TODO_TEST(xstring_cstr_to_camel_case__ref, _, {

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

})*/

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)


