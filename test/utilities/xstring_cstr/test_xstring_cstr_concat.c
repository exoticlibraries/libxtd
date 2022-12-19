/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I.-I../include/  -I../../include/ -I../../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../include/ -I../../include/ -I../../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/container/xstring.h>
#include <exotic/xtd/xiterator.h>

#define cester_assert_str_equal_(x,y) cester_assert_true(xstring_cstr_equals(x,y))

CESTER_TEST(xstring_cstr_concat_cstr, _, {
    char *value;
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    value = (char *) xstring_cstr_concat_cstr(allocator, "Hello", "World");
    cester_assert_str_equal_(value, "HelloWorld"); free(value);
    value = (char *) xstring_cstr_concat_cstr(allocator, "Hello", " wORLD");
    cester_assert_str_equal_(value, "Hello wORLD"); free(value);
})

CESTER_TEST(xstring_cstr_concat_char, _, {
    char *value;
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    value = (char *) xstring_cstr_concat_char(allocator, "Hell", 'o');
    cester_assert_str_equal_(value, "Hello"); free(value);
    value = (char *) xstring_cstr_concat_char(allocator, "Hello", '\n');
    cester_assert_str_equal_(value, "Hello\n"); free(value);
})

CESTER_TEST(xstring_cstr_concat_int, _, {
    char *value;
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    value = (char *) xstring_cstr_concat_int(allocator, "Hello", 987654321);
    cester_assert_str_equal_(value, "Hello987654321"); free(value);
    value = (char *) xstring_cstr_concat_int(allocator, "Year ", 2021);
    cester_assert_str_equal_(value, "Year 2021"); free(value);
})

CESTER_SKIP_TEST(xstring_cstr_concat_long, _, {
    char *value;
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    value = (char *) xstring_cstr_concat_long(allocator, "Hello", 98765471L);
    cester_assert_str_equal_(value, "Hello98765471"); free(value);
    value = (char *) xstring_cstr_concat_long(allocator, "Year ", -287372021L);
    cester_assert_str_equal_(value, "Year -287372021"); free(value);
})

#ifdef _WIN32
#define HELLO_DOUBLE_CONCAT_RESULT_1 "Hello90878787.88"
#define HELLO_DOUBLE_CONCAT_RESULT_2 "Year -678768876.88"
#else
#define HELLO_DOUBLE_CONCAT_RESULT_1 "Hello90878787.00"
#define HELLO_DOUBLE_CONCAT_RESULT_2 "Year -678768876.00"
#endif

CESTER_TEST(xstring_cstr_concat_double, _, {
    char *value;
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    value = (char *) xstring_cstr_concat_double(allocator, "Hello", 90878787.0);
    cester_assert_str_equal_(value, HELLO_DOUBLE_CONCAT_RESULT_1); printf("Value 1:%s\n", value); free(value);
    value = (char *) xstring_cstr_concat_double(allocator, "Year ", -678768876.0);
    cester_assert_str_equal_(value, HELLO_DOUBLE_CONCAT_RESULT_2); printf("Value 2:%s\n", value); free(value);
    
})

CESTER_TEST(xstring_cstr_concat_float, _, {
    char *value;
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    value = (char *) xstring_cstr_concat_float(allocator, "Hello", 908787.00);
    cester_assert_str_equal_(value, "Hello908787.00"); free(value);
    value = (char *) xstring_cstr_concat_float(allocator, "Year ", -678876.00);
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

