/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
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

CESTER_TEST(xstring_cstr_append_cstr, _, {
    char *value;
    XAllocator allocator;
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;
    
    value = (char *) xstring_cstr_append_cstr(allocator, "World", "Hello", 6);
    cester_assert_str_equal_(value, XTD_NULL);
    value = (char *) xstring_cstr_append_cstr(allocator, "World", "Hello", 0);
    cester_assert_str_equal_(value, "HelloWorld"); free(value);
    value = (char *) xstring_cstr_append_cstr(allocator, "World", "Hello", 5);
    cester_assert_str_equal_(value, "WorldHello"); free(value);
    value = (char *) xstring_cstr_append_cstr(allocator, "World", "Hello", 1);
    cester_assert_str_equal_(value, "WHelloorld"); free(value);
    value = (char *) xstring_cstr_append_cstr(allocator, "World", "Hello", 2);
    cester_assert_str_equal_(value, "WoHellorld"); free(value);
    value = (char *) xstring_cstr_append_cstr(allocator, "World", "Hello", 3);
    cester_assert_str_equal_(value, "WorHellold"); free(value);
    value = (char *) xstring_cstr_append_cstr(allocator, "World", "Hello", 4);
    cester_assert_str_equal_(value, "WorlHellod"); free(value);
    value = (char *) xstring_cstr_append_cstr(allocator, text2, "Heyo :) ", 0);
    cester_assert_str_equal_(value, "Heyo :) Hello world"); free(value);
    value = (char *) xstring_cstr_append_cstr(allocator, text2, " Jay", 5);
    cester_assert_str_equal_(value, "Hello Jay world"); free(value);
})

CESTER_TEST(xstring_cstr_append_cstr_free_old, _, {
    char *value;
    XAllocator allocator;
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;
    
    value = (char *) xstring_cstr_append_cstr(allocator, "World", "Hello", 6);
    cester_assert_str_equal_(value, XTD_NULL);
    value = (char *) xstring_cstr_append_cstr(allocator, "World", "Hello", 0);
    cester_assert_str_equal_(value, "HelloWorld");
    value = (char *) xstring_cstr_append_cstr_free_old(allocator, value, " ", 5);
    cester_assert_str_equal_(value, "Hello World");
    value = (char *) xstring_cstr_append_cstr_free_old(allocator, value, " libxtd", 11);
    cester_assert_str_equal_(value, "Hello World libxtd");
    value = (char *) xstring_cstr_append_cstr_free_old(allocator, value, ",", 11);
    cester_assert_str_equal_(value, "Hello World, libxtd");
    value = (char *) xstring_cstr_append_cstr_free_old(allocator, value, ":) ", 0);
    cester_assert_str_equal_(value, ":) Hello World, libxtd");
    value = (char *) xstring_cstr_append_cstr_free_old(allocator, value, " This is", 15);
    cester_assert_str_equal_(value, ":) Hello World, This is libxtd");

    free(value);
})

CESTER_TEST(xstring_cstr_append_cstr_prefix, _, {
    char *value;
    XAllocator allocator;
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;
    
    value = (char *) xstring_cstr_append_cstr_prefix(allocator, "World", "Hello");
    cester_assert_str_equal_(value, "HelloWorld"); free(value);
    value = (char *) xstring_cstr_append_cstr_prefix(allocator, "=", "+");
    cester_assert_str_equal_(value, "+="); free(value);
})

CESTER_TEST(xstring_cstr_append_cstr_suffix, _, {
    char *value;
    XAllocator allocator;
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;
    
    value = (char *) xstring_cstr_append_cstr_suffix(allocator, "Hello", "World");
    cester_assert_str_equal_(value, "HelloWorld"); free(value);
    value = (char *) xstring_cstr_append_cstr_suffix(allocator, "+", "=");
    cester_assert_str_equal_(value, "+="); free(value);
})

CESTER_TEST(xstring_cstr_append_int, _, {
    char *value;
    XAllocator allocator;
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;
    
    value = (char *) xstring_cstr_append_int(allocator, "World", 1, 6);
    cester_assert_str_equal_(value, XTD_NULL);
    value = (char *) xstring_cstr_append_int(allocator, "World", 3232, 0);
    cester_assert_str_equal_(value, "3232World"); free(value);
    value = (char *) xstring_cstr_append_int(allocator, "World", 987654321, 5);
    cester_assert_str_equal_(value, "World987654321"); free(value);
    value = (char *) xstring_cstr_append_int(allocator, "World", 122, 1);
    cester_assert_str_equal_(value, "W122orld"); free(value);
    value = (char *) xstring_cstr_append_int(allocator, "World", 23255, 2);
    cester_assert_str_equal_(value, "Wo23255rld"); free(value);
    value = (char *) xstring_cstr_append_int(allocator, "World", 87, 3);
    cester_assert_str_equal_(value, "Wor87ld"); free(value);
    value = (char *) xstring_cstr_append_int(allocator, "World", 3233, 4);
    cester_assert_str_equal_(value, "Worl3233d"); free(value);
    value = (char *) xstring_cstr_append_int(allocator, text2, -4545, 0);
    cester_assert_str_equal_(value, "-4545Hello world"); free(value);
    value = (char *) xstring_cstr_append_int(allocator, text2, -1234567890, 5);
    cester_assert_str_equal_(value, "Hello-1234567890 world"); free(value);
})

CESTER_TEST(xstring_cstr_append_int_free_old, _, {
    char *value;
    XAllocator allocator;
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;
    
    value = (char *) xstring_cstr_append_int(allocator, "World", 1, 0);
    cester_assert_str_equal_(value, "1World");
    value = (char *) xstring_cstr_append_int_free_old(allocator, value, -87787, 6);
    cester_assert_str_equal_(value, "1World-87787");
    value = (char *) xstring_cstr_append_int_free_old(allocator, value, +67676, 12);
    cester_assert_str_equal_(value, "1World-8778767676");

    free(value);
})

/* TODO write test for other appends */

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)

