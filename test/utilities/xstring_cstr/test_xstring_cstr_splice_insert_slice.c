/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I.-I../include/  -I../../include/ -I../../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../include/ -I../../include/ -I../../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/container/xstring.h>

CESTER_BODY(
    void *calloc_mock(size_t nitems, size_t size) {
        return XTD_NULL;
    }
)

CESTER_TEST(xstring_cstr_splice__no_item, _, {
    char *value;
    XAllocator allocator;
    allocator.memory_free = free;
    allocator.memory_malloc = malloc;
    allocator.memory_realloc = realloc;
    allocator.memory_calloc = calloc_mock;

    cester_assert_uint_eq(xstring_cstr_splice(allocator, XTD_NULL, 0, 1, XTD_NULL, &value), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", 0, 1, XTD_NULL, XTD_NULL), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", 0, 1, XTD_NULL, &value), XTD_ALLOC_ERR);
    allocator.memory_calloc = calloc;
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", -1, 0, XTD_NULL, &value), XTD_OK);
    cester_assert_str_equal(value, "Hello"); free(value);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", -1, 1, XTD_NULL, &value), XTD_OK);
    cester_assert_str_equal(value, "Hell"); free(value);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", -1, -1, XTD_NULL, &value), XTD_OK);
    cester_assert_str_equal(value, "Hello"); free(value);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", 0, -1, XTD_NULL, &value), XTD_OK);
    cester_assert_str_equal(value, "Hello"); free(value);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", 0, 0, XTD_NULL, &value), XTD_OK);
    cester_assert_str_equal(value, "Hello"); free(value);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", 0, 1, XTD_NULL, &value), XTD_OK);
    cester_assert_str_equal(value, "ello"); free(value);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", 1, 1, XTD_NULL, &value), XTD_OK);
    cester_assert_str_equal(value, "Hllo"); free(value);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", 1, 2, XTD_NULL, &value), XTD_OK);
    cester_assert_str_equal(value, "Hlo"); free(value);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", 1, 5, XTD_NULL, &value), XTD_OK);
    cester_assert_str_equal(value, "H"); free(value);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", 2, -1, XTD_NULL, &value), XTD_OK);
    cester_assert_str_equal(value, "Hello"); free(value);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", 2, 2, XTD_NULL, &value), XTD_OK);
    cester_assert_str_equal(value, "Heo"); free(value);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", 30, 1, XTD_NULL, &value), XTD_OK);
    cester_assert_str_equal(value, "Hello"); free(value);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", 0, 30, XTD_NULL, &value), XTD_OK);
    cester_assert_str_equal(value, ""); free(value);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", 30, 30, XTD_NULL, &value), XTD_OK);
    cester_assert_str_equal(value, "Hello"); free(value);
})

CESTER_TEST(xstring_cstr_splice, _, {
    char *value;
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", -1, 0, "World", &value), XTD_OK);
    cester_assert_str_equal(value, "HellWorldo"); free(value);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", -1, 1, "World", &value), XTD_OK);
    cester_assert_str_equal(value, "HellWorld"); free(value);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", -1, -1, "World", &value), XTD_OK);
    cester_assert_str_equal(value, "HellWorldo"); free(value);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", 0, -1, "World", &value), XTD_OK);
    cester_assert_str_equal(value, "WorldHello"); free(value);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", 0, 0, "World", &value), XTD_OK);
    cester_assert_str_equal(value, "WorldHello"); free(value);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", 0, 1, "World", &value), XTD_OK);
    cester_assert_str_equal(value, "Worldello"); free(value);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", 1, 1, "World", &value), XTD_OK);
    cester_assert_str_equal(value, "HWorldllo"); free(value);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", 1, 2, "World", &value), XTD_OK);
    cester_assert_str_equal(value, "HWorldlo"); free(value);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", 1, 5, "World", &value), XTD_OK);
    cester_assert_str_equal(value, "HWorld"); free(value);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", 2, -1, "World", &value), XTD_OK);
    cester_assert_str_equal(value, "HeWorldllo"); free(value);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", 2, 2, "World", &value), XTD_OK);
    cester_assert_str_equal(value, "HeWorldo"); free(value);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", 30, 1, "World", &value), XTD_OK);
    cester_assert_str_equal(value, "HelloWorld"); free(value);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", 0, 30, "World", &value), XTD_OK);
    cester_assert_str_equal(value, "World"); free(value);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", 30, 30, "World", &value), XTD_OK);
    cester_assert_str_equal(value, "HelloWorld"); free(value);
})

CESTER_TEST(xstring_cstr_insert_at, _, {
    char *value;
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc_mock;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    cester_assert_uint_eq(xstring_cstr_insert_at(allocator, XTD_NULL, 1, XTD_NULL, &value), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_insert_at(allocator, "Hello", 1, XTD_NULL, XTD_NULL), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_insert_at(allocator, "Hello", 1, XTD_NULL, &value), XTD_ALLOC_ERR);
    allocator.memory_calloc = calloc;
    cester_assert_uint_eq(xstring_cstr_insert_at(allocator, "Hello", 0, "World", &value), XTD_OK);
    cester_assert_str_equal(value, "WorldHello"); free(value);
    cester_assert_uint_eq(xstring_cstr_insert_at(allocator, "Hello", -1, "World", &value), XTD_OK);
    cester_assert_str_equal(value, "HellWorldo"); free(value);
    cester_assert_uint_eq(xstring_cstr_insert_at(allocator, "Hello", -3, "World", &value), XTD_OK);
    cester_assert_str_equal(value, "HeWorldllo"); free(value);
    cester_assert_uint_eq(xstring_cstr_insert_at(allocator, "Hello", 1, "World", &value), XTD_OK);
    cester_assert_str_equal(value, "HWorldello"); free(value);
    cester_assert_uint_eq(xstring_cstr_insert_at(allocator, "Hello", 3, "World", &value), XTD_OK);
    cester_assert_str_equal(value, "HelWorldlo"); free(value);
    cester_assert_uint_eq(xstring_cstr_insert_at(allocator, "Hello", xstring_cstr_length("Hello"), "World", &value), XTD_OK);
    cester_assert_str_equal(value, "HelloWorld"); free(value);
})

CESTER_TEST(xstring_cstr_insert, _, {
    char *value;
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc_mock;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    cester_assert_uint_eq(xstring_cstr_insert_at(allocator, XTD_NULL, 1, XTD_NULL, &value), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_insert_at(allocator, "Hello", 1, XTD_NULL, XTD_NULL), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_insert_at(allocator, "Hello", 1, XTD_NULL, &value), XTD_ALLOC_ERR);
    allocator.memory_calloc = calloc;
    cester_assert_uint_eq(xstring_cstr_insert(allocator, "Hello", "World", &value), XTD_OK);
    cester_assert_str_equal(value, "HelloWorld"); free(value);
})

CESTER_TEST(xstring_cstr_slice, _, {
    char *value;
    XAllocator allocator;
    allocator.memory_free = free;
    allocator.memory_malloc = malloc;
    allocator.memory_realloc = realloc;
    allocator.memory_calloc = calloc_mock;

    cester_assert_uint_eq(xstring_cstr_splice(allocator, XTD_NULL, 0, 1, XTD_NULL, &value), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", 0, 1, XTD_NULL, XTD_NULL), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_splice(allocator, "Hello", 0, 1, XTD_NULL, &value), XTD_ALLOC_ERR);
    allocator.memory_calloc = calloc;
    cester_assert_uint_eq(xstring_cstr_slice(allocator, "Hello", -1, 0, &value), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_slice(allocator, "Hello", -1, 1, &value), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_slice(allocator, "Hello", -1, -1, &value), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_slice(allocator, "Hello", 0, -1, &value), XTD_OK);
    cester_assert_str_equal(value, "Hell"); free(value);
    cester_assert_uint_eq(xstring_cstr_slice(allocator, "Hello", 0, 0, &value), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_slice(allocator, "Hello", 0, 1, &value), XTD_OK);
    cester_assert_str_equal(value, "H"); free(value);
    cester_assert_uint_eq(xstring_cstr_slice(allocator, "Hello", 1, 1, &value), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_slice(allocator, "Hello", 1, 2, &value), XTD_OK);
    cester_assert_str_equal(value, "e"); free(value);
    cester_assert_uint_eq(xstring_cstr_slice(allocator, "Hello", 1, 5, &value), XTD_OK);
    cester_assert_str_equal(value, "ello"); free(value);
    cester_assert_uint_eq(xstring_cstr_slice(allocator, "Hello", 2, -1, &value), XTD_OK);
    cester_assert_str_equal(value, "ll"); free(value);
    cester_assert_uint_eq(xstring_cstr_slice(allocator, "Hello", 2, 2, &value), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_slice(allocator, "Hello", 5, 1, &value), XTD_NO_OP_ERR);
    cester_assert_uint_eq(xstring_cstr_slice(allocator, "Hello", 0, 30, &value), XTD_OK);
    cester_assert_str_equal(value, "Hello"); free(value);
    cester_assert_uint_eq(xstring_cstr_slice(allocator, "Hello", 0, 5, &value), XTD_OK);
    cester_assert_str_equal(value, "Hello"); free(value);
    cester_assert_uint_eq(xstring_cstr_slice(allocator, "Hello", 0, 4, &value), XTD_OK);
    cester_assert_str_equal(value, "Hell"); free(value);
    cester_assert_uint_eq(xstring_cstr_slice(allocator, "Hello", 30, 30, &value), XTD_NO_OP_ERR);
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)

