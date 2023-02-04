/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I.-I../include/  -I../../include/ -I../../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../include/ -I../../include/ -I../../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/container/xstring.h>

#define XSTRING_MAP xhashtable(char, void_ptr) *__m; 
#define XSME(k,v) xhashtable_put(char, void_ptr)(__m, k, v)

CESTER_BODY(
    void *calloc_mock(size_t nitems, size_t size) {
        return XTD_NULL;
    }
)

CESTER_TEST(quick_test, _, {
    /*xstring_cstr_format("Hello {name}, your age is {age}", XSTRING_MAP(
        XSME("name", "Thecarisma"),
        XSME("age", 10)));*/
})

CESTER_BEFORE_ALL(test_instance, {
    xhashtable(XSTRH_CHAR_PTR, XSTRH_VOID_PTR) *data_map;
    float fl = 20.012;
    double dob = 30.49480L;

    xhashtable_new(XSTRH_CHAR_PTR, XSTRH_VOID_PTR)(&data_map, xstring_cstr_starts_with, xstring_cstr_format_hash_string__internal);
    xhashtable_put(XSTRH_CHAR_PTR, XSTRH_VOID_PTR)(data_map, "0~string", "exotic");
    xhashtable_put(XSTRH_CHAR_PTR, XSTRH_VOID_PTR)(data_map, "1~string", "libxtd");
    xhashtable_put(XSTRH_CHAR_PTR, XSTRH_VOID_PTR)(data_map, "st~string", "Thecarisma");
    xhashtable_put(XSTRH_CHAR_PTR, XSTRH_VOID_PTR)(data_map, "in~int", (void *) 20);
    xhashtable_put(XSTRH_CHAR_PTR, XSTRH_VOID_PTR)(data_map, "in2~int", (void *) 200);
    xhashtable_put(XSTRH_CHAR_PTR, XSTRH_VOID_PTR)(data_map, "negin~int", (void *) -20);
    xhashtable_put(XSTRH_CHAR_PTR, XSTRH_VOID_PTR)(data_map, "lo~long", (void *) 3787887L);
    xhashtable_put(XSTRH_CHAR_PTR, XSTRH_VOID_PTR)(data_map, "fl~float", (void *) &fl);
    xhashtable_put(XSTRH_CHAR_PTR, XSTRH_VOID_PTR)(data_map, "do~double", (void *) &dob);
    xhashtable_put(XSTRH_CHAR_PTR, XSTRH_VOID_PTR)(data_map, "po~pointer", (void *) &data_map);

    test_instance->arg = (void *) data_map;
})

CESTER_TEST(xstring_cstr_format__named_indexes, test_instance, {
    char *result;
    XAllocator allocator;
    xhashtable(XSTRH_CHAR_PTR, XSTRH_VOID_PTR) *data_map = test_instance->arg;
    allocator.memory_free = free;
    allocator.memory_malloc = malloc;
    allocator.memory_realloc = realloc;
    allocator.memory_calloc = calloc_mock;

    cester_assert_uint_eq(xstring_cstr_format(allocator, "Hello={st}", data_map, &result), XTD_ALLOC_ERR);
    cester_assert_uint_eq(xstring_cstr_format(allocator, "Hello={st}", XTD_NULL, &result), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_format(allocator, "Hello={st}", data_map, XTD_NULL), XTD_OUT_PARAM_NULL_ERR);
    allocator.memory_calloc = calloc;
    cester_assert_uint_eq(xstring_cstr_format(allocator, "Hello {st}", data_map, &result), XTD_OK);
    cester_assert_str_equal(result, "Hello Thecarisma"); free(result);
    cester_assert_uint_eq(xstring_cstr_format(allocator, "Number {in}", data_map, &result), XTD_OK);
    cester_assert_str_equal(result, "Number 20"); free(result);
    cester_assert_uint_eq(xstring_cstr_format(allocator, "Long Number {lo}", data_map, &result), XTD_OK);
    cester_assert_str_equal(result, "Long Number 3787887"); free(result);
    cester_assert_uint_eq(xstring_cstr_format(allocator, "Float Number {fl}", data_map, &result), XTD_OK);
    cester_assert_str_equal(result, "Float Number 0.00"); free(result);
    cester_assert_uint_eq(xstring_cstr_format(allocator, "Double Number {do}", data_map, &result), XTD_OK);
    cester_assert_str_equal(result, "Double Number 0.00"); free(result);
    cester_assert_uint_eq(xstring_cstr_format(allocator, "Pointer {po}", data_map, &result), XTD_OK);
    cester_assert_true(cester_string_contains(result, "0x")); free(result);
    cester_assert_uint_eq(xstring_cstr_format(allocator, "str={st}, int={in}, long={lo}, float={fl}, double={do}, pointer={po}", data_map, &result), XTD_OK);
    cester_assert_true(cester_string_starts_with(result, "str=Thecarisma, int=20, long=3787887, float=0.00, double=0.00, pointer=0x"));
    free(result);
})

CESTER_TEST(xstring_cstr_format__numbered_indexes, test_instance, {
    char *result;
    XAllocator allocator;
    xhashtable(XSTRH_CHAR_PTR, XSTRH_VOID_PTR) *data_map = test_instance->arg;
    allocator.memory_free = free;
    allocator.memory_malloc = malloc;
    allocator.memory_realloc = realloc;
    allocator.memory_calloc = calloc_mock;

    cester_assert_uint_eq(xstring_cstr_format(allocator, "Hello={0}", data_map, &result), XTD_ALLOC_ERR);
    cester_assert_uint_eq(xstring_cstr_format(allocator, "Hello={0}", XTD_NULL, &result), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_format(allocator, "Hello={0}", data_map, XTD_NULL), XTD_OUT_PARAM_NULL_ERR);
    allocator.memory_calloc = calloc;
    cester_assert_uint_eq(xstring_cstr_format(allocator, "Hello {0}", data_map, &result), XTD_OK);
    cester_assert_str_equal(result, "Hello exotic"); free(result);
    cester_assert_uint_eq(xstring_cstr_format(allocator, "Hello {1}", data_map, &result), XTD_OK);
    cester_assert_str_equal(result, "Hello libxtd"); free(result);
    cester_assert_uint_eq(xstring_cstr_format(allocator, "{1} under {0} libraries again {0}", data_map, &result), XTD_OK);
    cester_assert_str_equal(result, "libxtd under exotic libraries again exotic"); free(result);
})

CESTER_TEST(xstring_cstr_format__empty_placeholder, test_instance, {
    char *result;
    XAllocator allocator;
    xhashtable(XSTRH_CHAR_PTR, XSTRH_VOID_PTR) *data_map = test_instance->arg;
    allocator.memory_free = free;
    allocator.memory_malloc = malloc;
    allocator.memory_realloc = realloc;
    allocator.memory_calloc = calloc_mock;

    cester_assert_uint_eq(xstring_cstr_format(allocator, "Hello={}", data_map, &result), XTD_ALLOC_ERR);
    cester_assert_uint_eq(xstring_cstr_format(allocator, "Hello={}", XTD_NULL, &result), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_format(allocator, "Hello={}", data_map, XTD_NULL), XTD_OUT_PARAM_NULL_ERR);
    allocator.memory_calloc = calloc;
    cester_assert_uint_eq(xstring_cstr_format(allocator, "Hello {}", data_map, &result), XTD_OK);
    cester_assert_str_equal(result, "Hello exotic"); free(result);
    cester_assert_uint_eq(xstring_cstr_format(allocator, "Hello {}-{}", data_map, &result), XTD_OK);
    cester_assert_str_equal(result, "Hello exotic-libxtd"); free(result);
    cester_assert_uint_eq(xstring_cstr_format(allocator, "{} under {} libraries", data_map, &result), XTD_OK);
    cester_assert_str_equal(result, "exotic under libxtd libraries"); free(result);
})

CESTER_TEST(xstring_cstr_format__mixed_indexes, test_instance, {
    char *result;
    XAllocator allocator;
    xhashtable(XSTRH_CHAR_PTR, XSTRH_VOID_PTR) *data_map = test_instance->arg;
    allocator.memory_free = free;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;

    cester_assert_uint_eq(xstring_cstr_format(allocator, "Hello {1} under {0} libraries by {st}", data_map, &result), XTD_OK);
    cester_assert_str_equal(result, "Hello libxtd under exotic libraries by Thecarisma"); free(result);
    cester_assert_uint_eq(xstring_cstr_format(allocator, "{} {} {in}", data_map, &result), XTD_KEY_SWITCH_FROM_AUTO_ERR);
    cester_assert_uint_eq(xstring_cstr_format(allocator, "{0} {1} {in}", data_map, &result), XTD_OK);
    cester_assert_str_equal(result, "exotic libxtd 20"); free(result);
    cester_assert_uint_eq(xstring_cstr_format(allocator, "{0} {1} {}", data_map, &result), XTD_OK);
    cester_assert_str_equal(result, "exotic libxtd exotic"); free(result);
    cester_assert_uint_eq(xstring_cstr_format(allocator, "{st} {in} {}", data_map, &result), XTD_OK);
    cester_assert_str_equal(result, "Thecarisma 20 exotic"); free(result);
    cester_assert_uint_eq(xstring_cstr_format(allocator, "{0} {1} {} {in}", data_map, &result), XTD_KEY_SWITCH_FROM_AUTO_ERR);
})

CESTER_TEST(xstring_cstr_format__named_indexes_format_specifier, test_instance, {
    char *result;
    XAllocator allocator;
    xhashtable(XSTRH_CHAR_PTR, XSTRH_VOID_PTR) *data_map = test_instance->arg;
    allocator.memory_free = free;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;

    cester_assert_uint_eq(xstring_cstr_format(allocator, "They have '{in:>4}' minutes", data_map, &result), XTD_OK);
    cester_assert_str_equal(result, "They have '  20' minutes"); free(result);
    cester_assert_uint_eq(xstring_cstr_format(allocator, "They have '{in:<4}' minutes", data_map, &result), XTD_OK);
    cester_assert_str_equal(result, "They have '20  ' minutes"); free(result);
    cester_assert_uint_eq(xstring_cstr_format(allocator, "They have '{in:^7}' minutes", data_map, &result), XTD_OK);
    cester_assert_str_equal(result, "They have '  20   ' minutes"); free(result);
    cester_assert_uint_eq(xstring_cstr_format(allocator, "They have '{negin:^10}' minutes", data_map, &result), XTD_OK);
    cester_assert_str_equal(result, "They have '   -20    ' minutes"); free(result);
})
/* test for number, and no index */

CESTER_AFTER_ALL(test_instance, {
    xhashtable_destroy(XSTRH_CHAR_PTR, XSTRH_VOID_PTR)(test_instance->arg);
})

CESTER_OPTIONS(
    CESTER_NO_MEMTEST();
    CESTER_VERBOSE_LEVEL(2);
)

