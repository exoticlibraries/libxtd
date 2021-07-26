/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I.-I../include/  -I../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/xstring.h>
#include <exotic/xtd/xiterator.h>

#define cester_assert_str_equal_(x,y) cester_assert_true(xstring_cstr_equals(x,y))

CESTER_TEST(xstring_cstr_char_value, _, {
    char ch1 = '2';
    char ch2 = 'A';
    char ch3 = '&';
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    cester_assert_str_equal_(xstring_cstr_char_value(ch1, allocator), "2");
    cester_assert_str_equal_(xstring_cstr_char_value(ch2, allocator), "A");
    cester_assert_str_equal_(xstring_cstr_char_value(ch3, allocator), "&");
})

CESTER_TEST(xstring_cstr_int_value, _, {
    int int1 = 0;
    int int2 = -38276376;
    int int3 = 98895895;
    char *value;
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    value = (char *) xstring_cstr_int_value(int1, allocator);
    cester_assert_str_equal_(value, "0"); free(value);
    value = (char *) xstring_cstr_int_value(int2, allocator);
    cester_assert_str_equal_(value, "-38276376"); free(value);
    value = (char *) xstring_cstr_int_value(int3, allocator);
    cester_assert_str_equal_(value, "98895895"); free(value);
})

CESTER_TEST(xstring_cstr_long_value, _, {
    long long1 = 0L;
    long long2 = -2147483645;
    long long3 = 2147483647;
    char *value;
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    value = (char *) xstring_cstr_long_value(long1, allocator);
    cester_assert_str_equal_(value, "0"); free(value);
    value = (char *) xstring_cstr_long_value(long2, allocator);
    cester_assert_str_equal_(value, "-2147483645"); free(value);
    value = (char *) xstring_cstr_long_value(long3, allocator);
    cester_assert_str_equal_(value, "2147483647"); free(value);
})

CESTER_TEST(xstring_cstr_double_value, _, {
    double double1 = 0.00;
    double double2 = -736627.23728378;
    double double3 = 998958989.9458945894;
    char *value;
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    value = (char *) xstring_cstr_double_value(double1, 2, allocator);
    cester_assert_str_equal_(value, "0.00"); free(value);
    value = (char *) xstring_cstr_double_value(double2, 2, allocator);
    cester_assert_str_equal_(value, "-736627.23"); free(value);
    value = (char *) xstring_cstr_double_value(double3, 2, allocator);
    cester_assert_str_equal_(value, "998958989.88"); free(value);
})

CESTER_TEST(xstring_cstr_float_value, _, {
    float float1 = 0.00;
    float float2 = -736627.23728;
    float float3 = 998958.958946;
    char *value;
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    value = (char *) xstring_cstr_float_value(float1, 2, allocator);
    cester_assert_str_equal_(value, "0.00"); free(value);
    value = (char *) xstring_cstr_float_value(float2, 2, allocator);
    cester_assert_str_equal_(value, "-736627.25"); free(value);
    value = (char *) xstring_cstr_float_value(float3, 2, allocator);
    cester_assert_str_equal_(value, "998958.93"); free(value);
})

CESTER_TODO_TEST(xstring_cstr_pointer_value, _, {
    
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)
