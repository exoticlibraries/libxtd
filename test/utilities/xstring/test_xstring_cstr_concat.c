/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I.-I../include/  -I../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/xstring.h>
#include <exotic/xtd/xiterator.h>

#define cester_assert_str_equal_(x,y) cester_assert_true(xstring_cstr_equals(x,y))

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

CESTER_TODO_TEST(xstring_cstr_concat_pointer, _, {

})

CESTER_TODO_TEST(xstring_cstr_concat_cstr_free_old, _, {

})

CESTER_TODO_TEST(xstring_cstr_concat_char_free_old, _, {

})

CESTER_TODO_TEST(xstring_cstr_concat_int_free_old, _, {

})

CESTER_TODO_TEST(xstring_cstr_concat_long_free_old, _, {

})

CESTER_TODO_TEST(xstring_cstr_concat_double_free_old, _, {

})

CESTER_TODO_TEST(xstring_cstr_concat_float_free_old, _, {

})

CESTER_TODO_TEST(xstring_cstr_concat_pointer_free_old, _, {

})

CESTER_TODO_TEST(xstring_cstr_format, _, {
    
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)

