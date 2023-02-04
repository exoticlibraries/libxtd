/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I.-I../include/  -I../../include/ -I../../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../include/ -I../../include/ -I../../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/container/xstring.h>
#include <exotic/xtd/xiterator.h>

CESTER_TEST(xstring_cstr_concat_cstr, _, {
    char *value;
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    value = (char *) xstring_cstr_concat_cstr(allocator, "Hello", "World");
    cester_assert_str_equal(value, "HelloWorld"); free(value);
    value = (char *) xstring_cstr_concat_cstr(allocator, "Hello", " wORLD");
    cester_assert_str_equal(value, "Hello wORLD"); free(value);
})

CESTER_TEST(xstring_cstr_concat_cstr_free_old, _, {
    char *value;
    XAllocator allocator;
    char *leftmost_str1 = malloc(sizeof(char) * 5);
    char *leftmost_str2 = malloc(sizeof(char) * 6);
    allocator.memory_free = free;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;

    value = (char *) xstring_cstr_concat_cstr_free_old(allocator, leftmost_str1, "World");
    cester_assert_str_equal(value, "World"); free(value);
    value = (char *) xstring_cstr_concat_cstr_free_old(allocator, leftmost_str2, " wORLD");
    cester_assert_str_equal(value, " wORLD");
    value = (char *) xstring_cstr_concat_cstr_free_old(allocator, value, "  Hello");
    cester_assert_str_equal(value, " wORLD  Hello"); free(value);
})

CESTER_TEST(xstring_cstr_concat_char, _, {
    char *value;
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    value = (char *) xstring_cstr_concat_char(allocator, "Hell", 'o');
    cester_assert_str_equal(value, "Hello"); free(value);
    value = (char *) xstring_cstr_concat_char(allocator, "Hello", '\n');
    cester_assert_str_equal(value, "Hello\n"); free(value);
})

CESTER_TEST(xstring_cstr_concat_char_free_old, _, {
    char *value;
    XAllocator allocator;
    char *leftmost_str1 = malloc(sizeof(char) * 5);
    char *leftmost_str2 = malloc(sizeof(char) * 6);
    allocator.memory_free = free;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;

    value = (char *) xstring_cstr_concat_char_free_old(allocator, leftmost_str1, 'o');
    cester_assert_str_equal(value, "o"); free(value);
    value = (char *) xstring_cstr_concat_char_free_old(allocator, leftmost_str2, '\n');
    cester_assert_str_equal(value, "\n");
    value = (char *) xstring_cstr_concat_char_free_old(allocator, value, '\t');
    cester_assert_str_equal(value, "\n\t"); free(value);
})

CESTER_TEST(xstring_cstr_concat_int, _, {
    char *value;
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    value = (char *) xstring_cstr_concat_int(allocator, "Hello", 987654321);
    cester_assert_str_equal(value, "Hello987654321"); free(value);
    value = (char *) xstring_cstr_concat_int(allocator, "Year ", 2021);
    cester_assert_str_equal(value, "Year 2021"); free(value);
})

CESTER_TEST(xstring_cstr_concat_int_free_old, _, {
    char *value;
    XAllocator allocator;
    char *leftmost_str1 = malloc(sizeof(char) * 5);
    char *leftmost_str2 = malloc(sizeof(char) * 6);
    allocator.memory_free = free;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;

    value = (char *) xstring_cstr_concat_int_free_old(allocator, leftmost_str1, 987654321);
    cester_assert_str_equal(value, "987654321"); free(value);
    value = (char *) xstring_cstr_concat_int_free_old(allocator, leftmost_str2, 2021);
    cester_assert_str_equal(value, "2021");
    value = (char *) xstring_cstr_concat_int_free_old(allocator, value, 2023);
    cester_assert_str_equal(value, "20212023"); free(value);
})

#ifndef _WIN32
CESTER_TEST(xstring_cstr_concat_long, _, {
    char *value;
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    value = (char *) xstring_cstr_concat_long(allocator, "Hello", 98765471L);
    cester_assert_str_equal(value, "Hello98765471"); free(value);
    value = (char *) xstring_cstr_concat_long(allocator, "Year ", -287372021L);
    cester_assert_str_equal(value, "Year -287372021"); free(value);
})

CESTER_TEST(xstring_cstr_concat_long_free_old, _, {
    char *value;
    XAllocator allocator;
    char *leftmost_str1 = malloc(sizeof(char) * 5);
    char *leftmost_str2 = malloc(sizeof(char) * 6);
    allocator.memory_free = free;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;

    value = (char *) xstring_cstr_concat_long_free_old(allocator, leftmost_str1, 98765471L);
    cester_assert_str_equal(value, "98765471"); free(value);
    value = (char *) xstring_cstr_concat_long_free_old(allocator, leftmost_str2, -287372021L);
    cester_assert_str_equal(value, "-287372021");
    value = (char *) xstring_cstr_concat_long_free_old(allocator, value, 3456L);
    cester_assert_str_equal(value, "-2873720213456"); free(value);
})
#endif

#ifdef _WIN32
#define DOUBLE_CONCAT_RESULT_1 "90878787.88"
#define DOUBLE_CONCAT_RESULT_2 "-678768876.88"
#define DOUBLE_CONCAT_RESULT_3 "-678768876.883456.88"
#define HELLO_DOUBLE_CONCAT_RESULT_1 "Hello90878787.88"
#define HELLO_DOUBLE_CONCAT_RESULT_2 "Year -678768876.88"
#else
#define DOUBLE_CONCAT_RESULT_1 "90878787.00"
#define DOUBLE_CONCAT_RESULT_2 "-678768876.00"
#define DOUBLE_CONCAT_RESULT_3 "-678768876.003456.00"
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
    cester_assert_str_equal(value, HELLO_DOUBLE_CONCAT_RESULT_1); printf("Value 1:%s\n", value); free(value);
    value = (char *) xstring_cstr_concat_double(allocator, "Year ", -678768876.0);
    cester_assert_str_equal(value, HELLO_DOUBLE_CONCAT_RESULT_2); printf("Value 2:%s\n", value); free(value);
    
})

CESTER_TEST(xstring_cstr_concat_double_free_old, _, {
    char *value;
    XAllocator allocator;
    char *leftmost_str1 = malloc(sizeof(char) * 5);
    char *leftmost_str2 = malloc(sizeof(char) * 6);
    allocator.memory_free = free;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;

    value = (char *) xstring_cstr_concat_double_free_old(allocator, leftmost_str1, 90878787.0);
    cester_assert_str_equal(value, DOUBLE_CONCAT_RESULT_1); free(value);
    value = (char *) xstring_cstr_concat_double_free_old(allocator, leftmost_str2, -678768876.0);
    cester_assert_str_equal(value, DOUBLE_CONCAT_RESULT_2);
    value = (char *) xstring_cstr_concat_double_free_old(allocator, value, 3456.0);
    cester_assert_str_equal(value, DOUBLE_CONCAT_RESULT_3); free(value);
})

CESTER_TEST(xstring_cstr_concat_float, _, {
    char *value;
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    value = (char *) xstring_cstr_concat_float(allocator, "Hello", 908787.00);
    cester_assert_str_equal(value, "Hello908787.00"); free(value);
    value = (char *) xstring_cstr_concat_float(allocator, "Year ", -678876.00);
    cester_assert_str_equal(value, "Year -678876.00"); free(value);
})

CESTER_TEST(xstring_cstr_concat_float_free_old, _, {
    char *value;
    XAllocator allocator;
    char *leftmost_str1 = malloc(sizeof(char) * 5);
    char *leftmost_str2 = malloc(sizeof(char) * 6);
    allocator.memory_free = free;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;

    value = (char *) xstring_cstr_concat_float_free_old(allocator, leftmost_str1, 908787.00);
    cester_assert_str_equal(value, "908787.00"); free(value);
    value = (char *) xstring_cstr_concat_float_free_old(allocator, leftmost_str2, -678876.00);
    cester_assert_str_equal(value, "-678876.00");
    value = (char *) xstring_cstr_concat_float_free_old(allocator, value, 3456.00);
    cester_assert_str_equal(value, "-678876.003456.00"); free(value);
})

CESTER_TEST(xstring_cstr_concat_pointer, _, {
    char *value;
    void *pointer1 = NULL;
    void *pointer2 = malloc(10);
    XAllocator allocator;
    allocator.memory_free = free;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;

    value = (char *) xstring_cstr_concat_pointer(allocator, "Hello", pointer1);
    cester_assert_str_equal(value, "Hello0x0"); free(value);
    value = (char *) xstring_cstr_concat_pointer(allocator, "Year ", pointer2);
    cester_assert_str_ne(value, "Year -678876.00"); free(value);

    free(pointer2);
})

CESTER_TEST(xstring_cstr_concat_pointer_free_old, _, {
    char *value;
    void *pointer1 = NULL;
    void *pointer2 = malloc(10);
    char *leftmost_str1 = malloc(sizeof(char) * 5);
    char *leftmost_str2 = malloc(sizeof(char) * 6);
    XAllocator allocator;
    allocator.memory_free = free;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;

    value = (char *) xstring_cstr_concat_pointer_free_old(allocator, leftmost_str1, pointer1);
    cester_assert_str_equal(value, "0x0"); free(value);
    value = (char *) xstring_cstr_concat_pointer_free_old(allocator, leftmost_str2, pointer2);
    cester_assert_str_ne(value, "Year -678876.00"); free(value);

    free(pointer2);
})

CESTER_OPTIONS(
    CESTER_NO_MEMTEST();
    CESTER_VERBOSE_LEVEL(2);
)

