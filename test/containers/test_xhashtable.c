/*!gcc {0} -Wno-pointer-to-int-cast -Wno-int-conversion -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */
/*!gcc  -ansi -pedantic-errors {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/xhashtable.h>
#include <exotic/xtd/xiterator.h>
#include <exotic/xtd/xalgorithm.h>

CESTER_BODY(
    typedef char* str;
    typedef char** char_array;
    SETUP_XHASHTABLE_FOR(char, int)

bool compare_char(const char key1, const char key2) {
    return key1 == key2;
}

size_t hash_char(const char key, int length, uint32_t seed) {
    return (size_t)key;
}

)

CESTER_TEST(crash_test, _, {
    xhashtable(char, int) *intechars;
    enum x_stat status;

    status = xhashtable_new(char, int)(&intechars, compare_char, hash_char);
    cester_assert_uint_eq(status, XTD_OK);

    xhashtable_destroy(char, int)(intechars);
})

CESTER_TEST(xhashtable_conf_init, _, {
    struct xcontainer_config config;
    xhashtable(char, int) *intechars;
    enum x_stat status;

    config.allocator.memory_malloc   = malloc;
    config.allocator.memory_calloc  = calloc;
    config.allocator.memory_free    = free;
    config.expansion_rate = 5;
    config.capacity       = 20;
    config.max_size       = 5000;
    config.key_length     = -1;
    config.load_factor    = 0.5f;
    status = xhashtable_new_config(char, int)(&config, &intechars, compare_char, hash_char);
    cester_assert_uint_eq(status, XTD_OK);

    xhashtable_destroy(char, int)(intechars);
})

CESTER_TEST(xhashtable_put, _, {
    xhashtable(char, int) *intechars;
    enum x_stat status;

    status = xhashtable_new(char, int)(&intechars, compare_char, hash_char);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'a', 10), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'b', 20), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'c', 30), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'd', 40), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'e', 50), XTD_OK);

    xhashtable_destroy(char, int)(intechars);
})

CESTER_TEST(xhashtable_put_null_key, _, {
    xhashtable(char, int) *intechars;
    enum x_stat status;

    status = xhashtable_new(char, int)(&intechars, compare_char, hash_char);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xhashtable_put_null_key(char, int)(intechars, 60), XTD_OK);
    cester_assert_uint_eq(xhashtable_put_null_key(char, int)(intechars, 70), XTD_OK);
    cester_assert_uint_eq(xhashtable_put_null_key(char, int)(intechars, 80), XTD_OK);
    cester_assert_uint_eq(xhashtable_put_null_key(char, int)(intechars, 90), XTD_OK);
    cester_assert_uint_eq(xhashtable_put_null_key(char, int)(intechars, 100), XTD_OK);

    xhashtable_destroy(char, int)(intechars);
})

CESTER_TEST(xhashtable_get, _, {
    xhashtable(char, int) *intechars;
    enum x_stat status;
    int value;

    status = xhashtable_new(char, int)(&intechars, compare_char, hash_char);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'a', 10), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'b', 20), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'c', 30), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'd', 40), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'e', 50), XTD_OK);

    cester_assert_uint_eq(xhashtable_get(char, int)(intechars, 'd', &value), XTD_OK);
    cester_assert_uint_eq(value, 40);
    cester_assert_uint_eq(xhashtable_get(char, int)(intechars, 'b', &value), XTD_OK);
    cester_assert_uint_eq(value, 20);
    cester_assert_uint_eq(xhashtable_get(char, int)(intechars, 'a', &value), XTD_OK);
    cester_assert_uint_eq(value, 10);
    cester_assert_uint_eq(xhashtable_get(char, int)(intechars, 'c', &value), XTD_OK);
    cester_assert_uint_eq(value, 30);
    cester_assert_uint_eq(xhashtable_get(char, int)(intechars, 'e', &value), XTD_OK);
    cester_assert_uint_eq(value, 50);

    xhashtable_destroy(char, int)(intechars);
})

CESTER_TEST(xhashtable_get_null_key, _, {
    xhashtable(char, int) *intechars;
    enum x_stat status;
    int value;

    status = xhashtable_new(char, int)(&intechars, compare_char, hash_char);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xhashtable_put_null_key(char, int)(intechars, 60), XTD_OK);
    cester_assert_uint_eq(xhashtable_put_null_key(char, int)(intechars, 70), XTD_OK);
    cester_assert_uint_eq(xhashtable_put_null_key(char, int)(intechars, 80), XTD_OK);
    cester_assert_uint_eq(xhashtable_put_null_key(char, int)(intechars, 90), XTD_OK);
    cester_assert_uint_eq(xhashtable_put_null_key(char, int)(intechars, 100), XTD_OK);

    cester_assert_uint_eq(xhashtable_get_null_key(char, int)(intechars, &value), XTD_OK);
    cester_assert_uint_eq(value, 100);
    cester_assert_uint_eq(xhashtable_get_null_key(char, int)(intechars, &value), XTD_OK);
    cester_assert_uint_eq(value, 100);

    xhashtable_destroy(char, int)(intechars);
})

CESTER_TEST(xhashtable_get_get_null_key, _, {
    xhashtable(char, int) *intechars;
    enum x_stat status;
    int value;

    status = xhashtable_new(char, int)(&intechars, compare_char, hash_char);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'a', 10), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'b', 20), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'c', 30), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'd', 40), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'e', 50), XTD_OK);
    cester_assert_uint_eq(xhashtable_put_null_key(char, int)(intechars, 55), XTD_OK);
    cester_assert_uint_eq(xhashtable_put_null_key(char, int)(intechars, 60), XTD_OK);

    cester_assert_uint_eq(xhashtable_get_null_key(char, int)(intechars, &value), XTD_OK);
    cester_assert_uint_eq(value, 60);
    cester_assert_uint_eq(xhashtable_get_null_key(char, int)(intechars, &value), XTD_OK);
    cester_assert_uint_eq(value, 60);
    cester_assert_uint_eq(xhashtable_get(char, int)(intechars, 'd', &value), XTD_OK);
    cester_assert_uint_eq(value, 40);
    cester_assert_uint_eq(xhashtable_get(char, int)(intechars, 'b', &value), XTD_OK);
    cester_assert_uint_eq(value, 20);
    cester_assert_uint_eq(xhashtable_get(char, int)(intechars, 'a', &value), XTD_OK);
    cester_assert_uint_eq(value, 10);
    cester_assert_uint_eq(xhashtable_get(char, int)(intechars, 'c', &value), XTD_OK);
    cester_assert_uint_eq(value, 30);
    cester_assert_uint_eq(xhashtable_get(char, int)(intechars, 'e', &value), XTD_OK);
    cester_assert_uint_eq(value, 50);

    xhashtable_destroy(char, int)(intechars);
})

CESTER_TEST(xhashtable_remove, _, {
    xhashtable(char, int) *intechars;
    enum x_stat status;
    int value;

    status = xhashtable_new(char, int)(&intechars, compare_char, hash_char);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'a', 10), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'b', 20), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'c', 30), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'd', 40), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'e', 50), XTD_OK);

    cester_assert_uint_eq(xhashtable_remove(char, int)(intechars, 'd', &value), XTD_OK);
    cester_assert_uint_eq(value, 40);
    cester_assert_uint_eq(xhashtable_remove(char, int)(intechars, 'b', &value), XTD_OK);
    cester_assert_uint_eq(value, 20);
    cester_assert_uint_eq(xhashtable_remove(char, int)(intechars, 'a', &value), XTD_OK);
    cester_assert_uint_eq(value, 10);
    cester_assert_uint_eq(xhashtable_remove(char, int)(intechars, 'c', &value), XTD_OK);
    cester_assert_uint_eq(value, 30);
    cester_assert_uint_eq(xhashtable_remove(char, int)(intechars, 'e', &value), XTD_OK);
    cester_assert_uint_eq(value, 50);
    cester_assert_uint_eq(xhashtable_get(char, int)(intechars, 'c', &value), XTD_KEY_NOT_FOUND_ERR);
    cester_assert_uint_ne(value, 30);
    cester_assert_uint_eq(xhashtable_get(char, int)(intechars, 'b', &value), XTD_KEY_NOT_FOUND_ERR);
    cester_assert_uint_ne(value, 20);

    xhashtable_destroy(char, int)(intechars);
})

CESTER_TEST(xhashtable_remove_null_key, _, {
    xhashtable(char, int) *intechars;
    enum x_stat status;
    int value;

    status = xhashtable_new(char, int)(&intechars, compare_char, hash_char);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xhashtable_put_null_key(char, int)(intechars, 60), XTD_OK);
    cester_assert_uint_eq(xhashtable_put_null_key(char, int)(intechars, 100), XTD_OK);

    cester_assert_uint_eq(xhashtable_remove_null_key(char, int)(intechars, &value), XTD_OK);
    cester_assert_uint_eq(value, 100); value = 0;
    cester_assert_uint_eq(xhashtable_get_null_key(char, int)(intechars, &value), XTD_KEY_NOT_FOUND_ERR);
    cester_assert_uint_ne(value, 100);

    xhashtable_destroy(char, int)(intechars);
})

CESTER_TEST(xhashtable_remove_all, _, {
    xhashtable(char, int) *intechars;
    enum x_stat status;
    int value;

    status = xhashtable_new(char, int)(&intechars, compare_char, hash_char);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'a', 10), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'b', 20), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'c', 30), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'd', 40), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'e', 50), XTD_OK);
    cester_assert_uint_eq(xhashtable_put_null_key(char, int)(intechars, 55), XTD_OK);
    cester_assert_uint_eq(xhashtable_put_null_key(char, int)(intechars, 60), XTD_OK);

    xhashtable_remove_all(char, int)(intechars);
    cester_assert_uint_eq(xhashtable_get_null_key(char, int)(intechars, &value), XTD_KEY_NOT_FOUND_ERR);
    cester_assert_uint_ne(value, 60);
    cester_assert_uint_eq(xhashtable_get_null_key(char, int)(intechars, &value), XTD_KEY_NOT_FOUND_ERR);
    cester_assert_uint_ne(value, 60);
    cester_assert_uint_eq(xhashtable_get(char, int)(intechars, 'd', &value), XTD_KEY_NOT_FOUND_ERR);
    cester_assert_uint_ne(value, 40);
    cester_assert_uint_eq(xhashtable_get(char, int)(intechars, 'b', &value), XTD_KEY_NOT_FOUND_ERR);
    cester_assert_uint_ne(value, 20);
    cester_assert_uint_eq(xhashtable_get(char, int)(intechars, 'a', &value), XTD_KEY_NOT_FOUND_ERR);
    cester_assert_uint_ne(value, 10);
    cester_assert_uint_eq(xhashtable_get(char, int)(intechars, 'c', &value), XTD_KEY_NOT_FOUND_ERR);
    cester_assert_uint_ne(value, 30);
    cester_assert_uint_eq(xhashtable_get(char, int)(intechars, 'e', &value), XTD_KEY_NOT_FOUND_ERR);
    cester_assert_uint_ne(value, 50);

    xhashtable_destroy(char, int)(intechars);
})

CESTER_TEST(xhashtable_contains_key, _, {
    xhashtable(char, int) *intechars;
    enum x_stat status;

    status = xhashtable_new(char, int)(&intechars, compare_char, hash_char);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'a', 10), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'b', 20), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'c', 30), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'd', 40), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'e', 50), XTD_OK);
    cester_assert_uint_eq(xhashtable_put_null_key(char, int)(intechars, 60), XTD_OK);

    cester_assert_uint_eq(xhashtable_contains_key(char, int)(intechars, (char) XTD_NULL), TRUE);
    cester_assert_uint_eq(xhashtable_contains_key(char, int)(intechars, 'd'), TRUE);
    cester_assert_uint_eq(xhashtable_contains_key(char, int)(intechars, 'b'), TRUE);
    cester_assert_uint_eq(xhashtable_contains_key(char, int)(intechars, 'a'), TRUE);
    cester_assert_uint_eq(xhashtable_contains_key(char, int)(intechars, 'c'), TRUE);
    cester_assert_uint_eq(xhashtable_contains_key(char, int)(intechars, 'e'), TRUE);

    xhashtable_remove_all(char, int)(intechars);
    cester_assert_uint_eq(xhashtable_contains_key(char, int)(intechars, (char) XTD_NULL), FALSE);
    cester_assert_uint_eq(xhashtable_contains_key(char, int)(intechars, 'd'), FALSE);
    cester_assert_uint_eq(xhashtable_contains_key(char, int)(intechars, 'b'), FALSE);
    cester_assert_uint_eq(xhashtable_contains_key(char, int)(intechars, 'a'), FALSE);
    cester_assert_uint_eq(xhashtable_contains_key(char, int)(intechars, 'c'), FALSE);
    cester_assert_uint_eq(xhashtable_contains_key(char, int)(intechars, 'e'), FALSE);

    xhashtable_destroy(char, int)(intechars);
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)

