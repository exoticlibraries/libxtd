/*!gcc {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */
/*!gcc  -ansi -pedantic-errors {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/xunordered_set.h>
#include <exotic/xtd/xiterator.h>
#include <exotic/xtd/xalgorithm.h>

CESTER_BODY(
    typedef char* str;
    typedef char** char_array;
    SETUP_XUNORDERED_SET_ONLY_FOR(int)
    SETUP_XUNORDERED_SET_FOR(str)
    SETUP_XALGORITHM_SWAP_FOR(xunordered_set_str)
    SETUP_XALGORITHM_SWAP_FOR(char_array)

bool xunordered_set_test_int_equals(int first, int second) {
    return first == second;
}

)

CESTER_TEST(xunordered_set_init, _, {
    xunordered_set(str) *fruits;
    enum x_stat status;

    status = xunordered_set_new(str)(&fruits, cester_string_equals);
    cester_assert_uint_eq(status, XTD_OK);

    xunordered_set_destroy(fruits);
})

CESTER_TEST(xunordered_set_conf_init, _, {
    struct xcontainer_config config;
    xunordered_set(str) *fruits;
    enum x_stat status;

    config.allocator.memory_malloc   = malloc;
    config.allocator.memory_calloc  = calloc;
    config.allocator.memory_free    = free;
    config.expansion_rate = 5;
    config.capacity       = 20;
    config.max_size       = 5000;
    status = xunordered_set_new_config(str)(&config, &fruits, cester_string_equals);
    cester_assert_uint_eq(status, XTD_OK);

    xunordered_set_destroy(fruits);
})

CESTER_TEST(xunordered_set_add_int, _, {
    xunordered_set(int) *numbers;
    enum x_stat status;
    int index = 1;
    int limit = 20;

    status = xunordered_set_new(int)(&numbers, xunordered_set_test_int_equals);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xunordered_set_size(numbers), 0);

    for (; index <= limit; ++index) {
        status = xunordered_set_add(int)(numbers, index);
        cester_assert_uint_eq(status, XTD_OK);
    }
    cester_assert_uint_eq(xunordered_set_size(numbers), limit);

    xunordered_set_destroy(numbers);
})

CESTER_TEST(xunordered_set_add_str, _, {
    xunordered_set(str) *fruits;
    enum x_stat status;

    status = xunordered_set_new(str)(&fruits, cester_string_equals);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xunordered_set_size(fruits), 0);

    status = xunordered_set_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xunordered_set_size(fruits), 1);

    status = xunordered_set_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xunordered_set_size(fruits), 2);

    status = xunordered_set_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xunordered_set_size(fruits), 3);

    status = xunordered_set_add(str)(fruits, "Pawpaw");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xunordered_set_size(fruits), 4);

    status = xunordered_set_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xunordered_set_size(fruits), 5); 

    xunordered_set_destroy(fruits);
})

CESTER_TEST(xunordered_set_index_of, _, {
    size_t index;
    xset(str) *fruits;
    enum x_stat status;

    status = xunordered_set_new(str)(&fruits, cester_string_equals);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xunordered_set_add(str)(fruits, "Banana"), XTD_OK);
    cester_assert_uint_eq(xunordered_set_add(str)(fruits, "Coconut"), XTD_OK);
    cester_assert_uint_eq(xunordered_set_add(str)(fruits, "Apple"), XTD_OK);
    cester_assert_uint_eq(xunordered_set_add(str)(fruits, "Pawpaw"), XTD_OK);
    cester_assert_uint_eq(xunordered_set_add(str)(fruits, "Mango"), XTD_OK);
    cester_assert_uint_eq(xunordered_set_add(str)(fruits, "Avocado"), XTD_OK);

    cester_assert_uint_eq(xunordered_set_index_of(str)(fruits, "Avocado", &index), XTD_OK);
    cester_assert_uint_eq(index, 5);
    cester_assert_uint_eq(xunordered_set_index_of(str)(fruits, "Banana", &index), XTD_OK);
    cester_assert_uint_eq(index, 0);
    cester_assert_uint_eq(xunordered_set_index_of(str)(fruits, "Mango", &index), XTD_OK);
    cester_assert_uint_eq(index, 4);
    cester_assert_uint_eq(xunordered_set_index_of(str)(fruits, "Grape", &index), XTD_OUT_OF_RANGE_ERR);
    cester_assert_uint_eq(xunordered_set_index_of(str)(fruits, "Apple", &index), XTD_OK);
    cester_assert_uint_eq(index, 2);

    xunordered_set_destroy(fruits);
})

CESTER_TEST(xunordered_set_contains, _, {
    xset(str) *fruits;
    enum x_stat status;

    status = xunordered_set_new(str)(&fruits, cester_string_equals);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xunordered_set_add(str)(fruits, "Banana"), XTD_OK);
    cester_assert_uint_eq(xunordered_set_add(str)(fruits, "Coconut"), XTD_OK);
    cester_assert_uint_eq(xunordered_set_add(str)(fruits, "Apple"), XTD_OK);
    cester_assert_uint_eq(xunordered_set_add(str)(fruits, "Pawpaw"), XTD_OK);
    cester_assert_uint_eq(xunordered_set_add(str)(fruits, "Mango"), XTD_OK);
    cester_assert_uint_eq(xunordered_set_add(str)(fruits, "Avocado"), XTD_OK);

    cester_assert_uint_eq(xunordered_set_contains(str)(fruits, "Avocado"), TRUE);
    cester_assert_uint_eq(xunordered_set_contains(str)(fruits, "Banana"), TRUE);
    cester_assert_uint_eq(xunordered_set_contains(str)(fruits, "Mango"), TRUE);
    cester_assert_uint_eq(xunordered_set_contains(str)(fruits, "Grape"), FALSE);
    cester_assert_uint_eq(xunordered_set_contains(str)(fruits, "Apple"), TRUE);

    xunordered_set_destroy(fruits);
})

CESTER_TEST(xunordered_set_element_count, _, {
    xset(str) *fruits;
    enum x_stat status;

    status = xunordered_set_new(str)(&fruits, cester_string_equals);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xunordered_set_add(str)(fruits, "Banana"), XTD_OK);
    cester_assert_uint_eq(xunordered_set_add(str)(fruits, "Coconut"), XTD_OK);
    cester_assert_uint_eq(xunordered_set_add(str)(fruits, "Apple"), XTD_OK);
    cester_assert_uint_eq(xunordered_set_add(str)(fruits, "Mango"), XTD_OK);
    cester_assert_uint_eq(xunordered_set_add(str)(fruits, "Pawpaw"), XTD_OK);
    cester_assert_uint_eq(xunordered_set_add(str)(fruits, "Banana"), XTD_ALREADY_IN_CONTAINER_ERR);
    cester_assert_uint_eq(xunordered_set_add(str)(fruits, "Mango"), XTD_ALREADY_IN_CONTAINER_ERR);
    cester_assert_uint_eq(xunordered_set_add(str)(fruits, "Banana"), XTD_ALREADY_IN_CONTAINER_ERR);
    cester_assert_uint_eq(xunordered_set_add(str)(fruits, "Avocado"), XTD_OK);
    cester_assert_uint_eq(xunordered_set_add(str)(fruits, "Apple"), XTD_ALREADY_IN_CONTAINER_ERR);

    cester_assert_uint_eq(xunordered_set_element_count(str)(fruits, "Avocado"), 1);
    cester_assert_uint_eq(xunordered_set_element_count(str)(fruits, "Banana"), 1);
    cester_assert_uint_eq(xunordered_set_element_count(str)(fruits, "Mango"), 1);
    cester_assert_uint_eq(xunordered_set_element_count(str)(fruits, "Grape"), 0);
    cester_assert_uint_eq(xunordered_set_element_count(str)(fruits, "Apple"), 1);

    xunordered_set_destroy(fruits);
})

CESTER_TEST(xunordered_set_add_str_unique, _, {
    xunordered_set(str) *fruits;
    enum x_stat status;

    status = xunordered_set_new(str)(&fruits, cester_string_equals);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xunordered_set_size(fruits), 0);

    status = xunordered_set_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xunordered_set_size(fruits), 1);

    status = xunordered_set_add(str)(fruits, "Pawpaw");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xunordered_set_size(fruits), 2);

    status = xunordered_set_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xunordered_set_size(fruits), 3);

    status = xunordered_set_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xunordered_set_size(fruits), 4);

    status = xunordered_set_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xunordered_set_size(fruits), 5);

    status = xunordered_set_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_ALREADY_IN_CONTAINER_ERR);
    cester_assert_uint_ne(xunordered_set_size(fruits), 6);

    status = xunordered_set_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_ALREADY_IN_CONTAINER_ERR);
    cester_assert_uint_ne(xunordered_set_size(fruits), 7);

    status = xunordered_set_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_ALREADY_IN_CONTAINER_ERR);
    cester_assert_uint_ne(xunordered_set_size(fruits), 8);

    xunordered_set_destroy(fruits);
})

CESTER_TEST(xunordered_set_add_at, _, {
    xunordered_set(str) *fruits;
    enum x_stat status;

    status = xunordered_set_new(str)(&fruits, cester_string_equals);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xunordered_set_size(fruits), 0);

    status = xunordered_set_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xunordered_set_size(fruits), 1);
    cester_assert_str_equal(xget_at(fruits, 0), "Apple");

    status = xunordered_set_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xunordered_set_size(fruits), 2);
    cester_assert_str_equal(xget_at(fruits, 1), "Banana");

    status = xunordered_set_add_at(str)(fruits, "Coconut", 4);
    cester_assert_uint_eq(status, XTD_INDEX_OUT_OF_RANGE_ERR);

    status = xunordered_set_add_at(str)(fruits, "Coconut", 2);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xunordered_set_size(fruits), 3);

    status = xunordered_set_add_at(str)(fruits, "Mango", 1);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xunordered_set_size(fruits), 4);

    cester_assert_str_equal(xget_at(fruits, 0), "Apple");
    cester_assert_str_equal(xget_at(fruits, 1), "Mango");
    cester_assert_str_equal(xget_at(fruits, 2), "Banana");
    cester_assert_str_equal(xget_at(fruits, 3), "Coconut");

    xunordered_set_destroy(fruits);
})

CESTER_TEST(xunordered_set_get_str, _, {
    xunordered_set(str) *fruits;
    enum x_stat status;
    char *value;

    status = xunordered_set_new(str)(&fruits, cester_string_equals);
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add_at(str)(fruits, "Coconut", 4);
    cester_assert_uint_eq(status, XTD_INDEX_OUT_OF_RANGE_ERR);
    status = xunordered_set_add_at(str)(fruits, "Coconut", 2);
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add_at(str)(fruits, "Mango", 1);
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_uint_eq(xunordered_set_get_at(str)(fruits, 0, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xunordered_set_get_at(str)(fruits, 3, &value), XTD_OK);
    cester_assert_str_equal(value, "Coconut");
    cester_assert_uint_eq(xunordered_set_get_at(str)(fruits, 1, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xunordered_set_get_at(str)(fruits, 2, &value), XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xunordered_set_get_at(str)(fruits, 5, &value), XTD_INDEX_OUT_OF_RANGE_ERR);
    cester_assert_uint_eq(xunordered_set_get_at(str)(fruits, -40, &value), XTD_INDEX_OUT_OF_RANGE_ERR);

    xunordered_set_destroy(fruits);
})

CESTER_TEST(xunordered_set_replace_at, _, {
    xunordered_set(str) *fruits;
    enum x_stat status;

    status = xunordered_set_new(str)(&fruits, cester_string_equals);
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_str_equal(xget_at(fruits, 0), "Apple");
    cester_assert_str_equal(xget_at(fruits, 1), "Banana");
    cester_assert_str_equal(xget_at(fruits, 2), "Coconut");
    cester_assert_str_equal(xget_at(fruits, 3), "Mango");
    
    cester_assert_uint_eq(xunordered_set_replace_at(str)(fruits, 0, "Orange", NULL), XTD_OK);
    cester_assert_uint_eq(xunordered_set_replace_at(str)(fruits, 1, "Strawberry", NULL), XTD_OK);
    cester_assert_uint_eq(xunordered_set_replace_at(str)(fruits, 2, "Pineapple", NULL), XTD_OK);
    cester_assert_uint_eq(xunordered_set_replace_at(str)(fruits, 3, "Avocado", NULL), XTD_OK);

    cester_assert_str_equal(xget_at(fruits, 0), "Orange");
    cester_assert_str_equal(xget_at(fruits, 1), "Strawberry");
    cester_assert_str_equal(xget_at(fruits, 2), "Pineapple");
    cester_assert_str_equal(xget_at(fruits, 3), "Avocado");

    xunordered_set_destroy(fruits);
})

CESTER_TEST(xunordered_set_front_back, _, {
    xunordered_set(str) *fruits;
    enum x_stat status;
    char *value;

    status = xunordered_set_new(str)(&fruits, cester_string_equals);
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_uint_eq(xunordered_set_get_front(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xunordered_set_get_back(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");

    xunordered_set_destroy(fruits);
})

CESTER_TEST(xunordered_set_front_back_2, _, {
    xunordered_set(str) *fruits;
    enum x_stat status;
    char *value;

    status = xunordered_set_new(str)(&fruits, cester_string_equals);
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_uint_eq(xunordered_set_get_front(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xunordered_set_get_back(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");

    xunordered_set_destroy(fruits);
})

CESTER_TEST(xunordered_set_front_back_3, _, {
    xunordered_set(str) *fruits;
    enum x_stat status;
    char *value;

    status = xunordered_set_new(str)(&fruits, cester_string_equals);
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_uint_eq(xunordered_set_get_front(str)(fruits, &value), XTD_EMPTY_CONTAINER_ERR);
    cester_assert_uint_eq(xunordered_set_get_back(str)(fruits, &value), XTD_EMPTY_CONTAINER_ERR);

    xunordered_set_destroy(fruits);
})

CESTER_TEST(xunordered_set_capacity, _, {
    xunordered_set(str) *fruits;
    enum x_stat status;

    status = xunordered_set_new(str)(&fruits, cester_string_equals);
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    
    cester_assert_false(xunordered_set_is_empty(fruits));
    cester_assert_uint_eq(xunordered_set_size(fruits), 4);
    cester_assert_uint_eq(xunordered_set_capacity(fruits), XDEFAULT_CONTAINER_CAPACITY);
    cester_assert_equal(xunordered_set_max_size(fruits), XTD_CONTAINER_MAX_CAPACITY);

    xunordered_set_destroy(fruits);
})

CESTER_TEST(xunordered_set_max_size_1, _, {
    xunordered_set(str) *fruits;
    enum x_stat status;

    status = xunordered_set_new_max_size(str)(&fruits, 3, cester_string_equals);
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_MAX_SIZE_ERR);
    status = xunordered_set_add(str)(fruits, "Watermelon");
    cester_assert_uint_eq(status, XTD_MAX_SIZE_ERR);
    
    cester_assert_false(xunordered_set_is_empty(fruits));
    cester_assert_uint_eq(xunordered_set_size(fruits), 3);
    cester_assert_uint_eq(xunordered_set_capacity(fruits), 3);
    cester_assert_llong_eq(xunordered_set_max_size(fruits), 3);

    xunordered_set_destroy(fruits);
})

CESTER_TEST(xunordered_set_max_size_2, _, {
    xunordered_set(str) *fruits;
    enum x_stat status;
    int max_size = 6;

    status = xunordered_set_new_max_size(str)(&fruits, max_size, cester_string_equals);
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Watermelon");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Avocado");
    cester_assert_uint_eq(status, XTD_MAX_SIZE_ERR);
    
    cester_assert_false(xunordered_set_is_empty(fruits));
    cester_assert_uint_eq(xunordered_set_size(fruits), max_size);
    cester_assert_uint_eq(xunordered_set_capacity(fruits), (XDEFAULT_CONTAINER_CAPACITY * XDEFAULT_CONTAINER_EXPANSION_RATE));
    cester_assert_llong_eq(xunordered_set_max_size(fruits), max_size);

    xunordered_set_destroy(fruits);
})

CESTER_TEST(xunordered_set_shrink_to_fit, _, {
    xunordered_set(str) *fruits;
    enum x_stat status;

    status = xunordered_set_new(str)(&fruits, cester_string_equals);
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    cester_assert_false(xunordered_set_is_empty(fruits));
    cester_assert_uint_eq(xunordered_set_size(fruits), 5);
    cester_assert_uint_eq(xunordered_set_capacity(fruits), (XDEFAULT_CONTAINER_CAPACITY * XDEFAULT_CONTAINER_EXPANSION_RATE));
    status = xunordered_set_shrink_to_fit(str)(fruits);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xunordered_set_capacity(fruits), 5);

    xunordered_set_destroy(fruits);
})

CESTER_TEST(xunordered_set_swap, _, {
    xunordered_set(str) *fruits;
    xunordered_set(str) *foods;
    enum x_stat status;
    char *value;

    status = xunordered_set_new(str)(&fruits, cester_string_equals);
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);

    status = xunordered_set_new(str)(&foods, cester_string_equals);
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(foods, "Amala");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(foods, "Iyan");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(foods, "Fufu");
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_uint_eq(xunordered_set_get_front(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xunordered_set_get_back(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xunordered_set_get_front(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Amala");
    cester_assert_uint_eq(xunordered_set_get_back(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Fufu");

    xswap(xunordered_set_str)(foods, fruits);

    cester_assert_uint_eq(xunordered_set_get_front(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xunordered_set_get_back(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xunordered_set_get_front(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Amala");
    cester_assert_uint_eq(xunordered_set_get_back(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Fufu");

    xunordered_set_destroy(fruits);
})

CESTER_TEST(xunordered_set_swap_buffer, _, {
    xunordered_set(str) *fruits;
    xunordered_set(str) *foods;
    enum x_stat status;
    char *value;

    status = xunordered_set_new(str)(&fruits, cester_string_equals);
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);

    status = xunordered_set_new(str)(&foods, cester_string_equals);
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(foods, "Amala");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(foods, "Iyan");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(foods, "Fufu");
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_uint_eq(xunordered_set_get_front(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xunordered_set_get_back(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xunordered_set_get_front(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Amala");
    cester_assert_uint_eq(xunordered_set_get_back(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Fufu");

    xswap(char_array)(&xget_buffer(foods), &xget_buffer(fruits));

    cester_assert_uint_eq(xunordered_set_get_front(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xunordered_set_get_back(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xunordered_set_get_front(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Amala");
    cester_assert_uint_eq(xunordered_set_get_back(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Fufu");

    xunordered_set_destroy(fruits);
})

CESTER_TEST(xunordered_set_remove_front_and_back, _, {
    xunordered_set(str) *fruits;
    enum x_stat status;
    char *value;

    status = xunordered_set_new(str)(&fruits, cester_string_equals);
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    
    cester_assert_uint_eq(xunordered_set_get_at(str)(fruits, 1, &value), XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xunordered_set_size(fruits), 3);
    
    cester_assert_uint_eq(xunordered_set_get_front(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    status = xunordered_set_remove_front(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xunordered_set_get_front(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xunordered_set_size(fruits), 2);
    
    cester_assert_uint_eq(xunordered_set_get_back(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");
    status = xunordered_set_remove_back(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xunordered_set_get_back(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xunordered_set_size(fruits), 1);

    xunordered_set_destroy(fruits);
})

CESTER_TEST(xunordered_set_remove_at, _, {
    xunordered_set(str) *fruits;
    enum x_stat status;
    char *value;

    status = xunordered_set_new(str)(&fruits, cester_string_equals);
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    
    cester_assert_uint_eq(xunordered_set_get_at(str)(fruits, 1, &value), XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xunordered_set_size(fruits), 3);

    status = xunordered_set_remove_at(str)(fruits, 1, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xunordered_set_get_at(str)(fruits, 1, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xunordered_set_size(fruits), 2);

    status = xunordered_set_remove_at(str)(fruits, 0, NULL);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xunordered_set_get_at(str)(fruits, 1, &value), XTD_INDEX_OUT_OF_RANGE_ERR);
    cester_assert_uint_eq(xunordered_set_size(fruits), 1);


    xunordered_set_destroy(fruits);
})

CESTER_TEST(xunordered_set_clear, _, {
    xunordered_set(str) *fruits;
    enum x_stat status;

    status = xunordered_set_new(str)(&fruits, cester_string_equals);
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xunordered_set_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    
    cester_assert_uint_eq(xunordered_set_size(fruits), 3);
    cester_assert_uint_eq(xunordered_set_clear(str)(fruits), XTD_OK);
    cester_assert_uint_eq(xunordered_set_size(fruits), 0);


    xunordered_set_destroy(fruits);
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)
