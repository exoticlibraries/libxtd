/*!gcc {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */
/*!gcc  -ansi -pedantic-errors {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/container/xvector.h>
#include <exotic/xtd/container/xhashtable.h>
#include <exotic/xtd/xiterator.h>
#include <exotic/xtd/algorithm/xalgorithm.h>

CESTER_BODY(
    typedef char* str;
    typedef char** char_array;
    SETUP_XVECTOR_FOR(char)
    SETUP_XVECTOR_FOR(int)
    SETUP_XHASHTABLE_FOR(char, int)
    SETUP_GET_KEYS_VALUES_XVECTOR_FOR_XHASHTABLE(char, int)

bool compare_char(const char key1, const char key2) {
    return key1 == key2;
}

size_t hash_char(const char key, int length, uint32_t seed) {
    return (size_t)key;
}

)

CESTER_TEST(xhashtable_get_keys, _, {
    xhashtable(char, int) *intechars;
    enum x_stat status;
    xvector(char) *keys;
    char key;

    status = xhashtable_new(char, int)(&intechars, compare_char, hash_char);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'a', 10), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'b', 20), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'c', 30), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'd', 40), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'e', 50), XTD_OK);
    cester_assert_uint_eq(xhashtable_put_null_key(char, int)(intechars, 60), XTD_OK);

    cester_assert_uint_eq(xhashtable_get_keys(char, int)(intechars, &keys), XTD_OK);
    cester_assert_uint_eq(xvector_size(keys), xhashtable_size(intechars));
    cester_assert_uint_eq(xvector_max_size(keys), xhashtable_size(intechars));
    cester_assert_uint_eq(xvector_capacity(keys), xhashtable_size(intechars));
    cester_assert_uint_eq(xvector_add(char)(keys, 'f'), XTD_MAX_SIZE_ERR);
    cester_assert_uint_eq(xvector_size(keys), xhashtable_size(intechars));

    cester_assert_uint_eq(xvector_get_at(char)(keys, 0, &key), XTD_OK);
    cester_assert_char_eq(key, XTD_NULL);
    cester_assert_uint_eq(xvector_get_at(char)(keys, 1, &key), XTD_OK);
    cester_assert_char_eq(key, 'a');
    cester_assert_uint_eq(xvector_get_at(char)(keys, 2, &key), XTD_OK);
    cester_assert_char_eq(key, 'b');
    cester_assert_uint_eq(xvector_get_at(char)(keys, 3, &key), XTD_OK);
    cester_assert_char_eq(key, 'c');
    cester_assert_uint_eq(xvector_get_at(char)(keys, 4, &key), XTD_OK);
    cester_assert_char_eq(key, 'd');
    cester_assert_uint_eq(xvector_get_at(char)(keys, 5, &key), XTD_OK);
    cester_assert_char_eq(key, 'e');

    xvector_destroy(keys);
    xhashtable_destroy(char, int)(intechars);
})

CESTER_TEST(xhashtable_get_values, _, {
    xhashtable(char, int) *intechars;
    enum x_stat status;
    xvector(int) *values;
    int value;

    status = xhashtable_new(char, int)(&intechars, compare_char, hash_char);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'a', 10), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'b', 20), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'c', 30), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'd', 40), XTD_OK);
    cester_assert_uint_eq(xhashtable_put(char, int)(intechars, 'e', 50), XTD_OK);
    cester_assert_uint_eq(xhashtable_put_null_key(char, int)(intechars, 60), XTD_OK);

    cester_assert_uint_eq(xhashtable_get_values(char, int)(intechars, &values), XTD_OK);
    cester_assert_uint_eq(xvector_size(values), xhashtable_size(values));
    cester_assert_uint_eq(xvector_max_size(values), xhashtable_size(values));
    cester_assert_uint_eq(xvector_capacity(values), xhashtable_size(values));
    cester_assert_uint_eq(xvector_add(int)(values, 70), XTD_MAX_SIZE_ERR);
    cester_assert_uint_eq(xvector_size(values), xhashtable_size(values));

    cester_assert_uint_eq(xvector_get_at(int)(values, 0, &value), XTD_OK);
    cester_assert_uint_eq(value, 60);
    cester_assert_uint_eq(xvector_get_at(int)(values, 1, &value), XTD_OK);
    cester_assert_uint_eq(value, 10);
    cester_assert_uint_eq(xvector_get_at(int)(values, 2, &value), XTD_OK);
    cester_assert_uint_eq(value, 20);
    cester_assert_uint_eq(xvector_get_at(int)(values, 3, &value), XTD_OK);
    cester_assert_uint_eq(value, 30);
    cester_assert_uint_eq(xvector_get_at(int)(values, 4, &value), XTD_OK);
    cester_assert_uint_eq(value, 40);
    cester_assert_uint_eq(xvector_get_at(int)(values, 5, &value), XTD_OK);
    cester_assert_uint_eq(value, 50);

    xvector_destroy(values);
    xhashtable_destroy(char, int)(intechars);
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)

