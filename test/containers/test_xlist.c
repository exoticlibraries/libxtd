/*!gcc {0} -I. -I../../include/ -I../../../libcester/include -I../include/ -o out; ./out */
/*!gcc -ansi -pedantic-errors {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/container/xlist.h>
#include <exotic/xtd/xiterator.h>
#include <exotic/xtd/algorithm/xalgorithm.h>

CESTER_BODY(
    typedef char* str;
    SETUP_XLIST_FOR(int)
    SETUP_XLIST_FOR(str)
    SETUP_XALGORITHM_SWAP_FOR(xlist_str)
)

CESTER_TEST(xlist_init, _, {
    xlist(str) *fruits;
    enum x_stat status;

    status = xlist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);

    xlist_destroy(str)(fruits);
})

CESTER_TEST(xlist_conf_init, _, {
    struct xcontainer_config config;
    xlist(str) *fruits;
    enum x_stat status;

    config.allocator.memory_malloc   = malloc;
    config.allocator.memory_calloc  = calloc;
    config.allocator.memory_free    = free;
    config.expansion_rate = 5;
    config.capacity       = 20;
    config.max_size       = 5000;
    status = xlist_new_config(str)(&config, &fruits);
    cester_assert_uint_eq(status, XTD_OK);

    xlist_destroy(str)(fruits);
})

CESTER_TEST(xlist_add_int, _, {
    xlist(int) *numbers;
    enum x_stat status;
    int index = 1;
    int limit = 20;

    status = xlist_new(int)(&numbers);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xlist_size(numbers), 0);

    for (; index <= limit; ++index) {
        status = xlist_add(int)(numbers, index);
        cester_assert_uint_eq(status, XTD_OK);
    }
    cester_assert_uint_eq(xlist_size(numbers), limit);

    xlist_destroy(int)(numbers);
})

CESTER_TEST(xlist_add_str, _, {
    xlist(str) *fruits;
    enum x_stat status;

    status = xlist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xlist_size(fruits), 0);

    status = xlist_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xlist_size(fruits), 1);

    status = xlist_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xlist_size(fruits), 2);

    status = xlist_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xlist_size(fruits), 3);

    status = xlist_add(str)(fruits, "Pawpaw");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xlist_size(fruits), 4);

    status = xlist_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xlist_size(fruits), 5); 

    xlist_destroy(str)(fruits);
})

CESTER_TEST(xlist_index_of, _, {
    size_t index;
    xlist(str) *fruits;
    enum x_stat status;

    status = xlist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xlist_add(str)(fruits, "Apple"), XTD_OK);
    cester_assert_uint_eq(xlist_add(str)(fruits, "Banana"), XTD_OK);
    cester_assert_uint_eq(xlist_add(str)(fruits, "Coconut"), XTD_OK);
    cester_assert_uint_eq(xlist_add(str)(fruits, "Mango"), XTD_OK);

    cester_assert_uint_eq(xlist_index_of(str)(fruits, "Avocado", &index), XTD_OUT_OF_RANGE_ERR);
    cester_assert_uint_eq(xlist_index_of(str)(fruits, "Banana", &index), XTD_OK);
    cester_assert_uint_eq(index, 1);
    cester_assert_uint_eq(xlist_index_of(str)(fruits, "Mango", &index), XTD_OK);
    cester_assert_uint_eq(index, 3);
    cester_assert_uint_eq(xlist_index_of(str)(fruits, "Grape", &index), XTD_OUT_OF_RANGE_ERR);
    cester_assert_uint_eq(xlist_index_of(str)(fruits, "Apple", &index), XTD_OK);
    cester_assert_uint_eq(index, 0);

    xlist_destroy(str)(fruits);
})

CESTER_TEST(xlist_contains, _, {
    xlist(str) *fruits;
    enum x_stat status;

    status = xlist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xlist_add(str)(fruits, "Apple"), XTD_OK);
    cester_assert_uint_eq(xlist_add(str)(fruits, "Banana"), XTD_OK);
    cester_assert_uint_eq(xlist_add(str)(fruits, "Coconut"), XTD_OK);
    cester_assert_uint_eq(xlist_add(str)(fruits, "Mango"), XTD_OK);

    cester_assert_uint_eq(xlist_contains(str)(fruits, "Avocado"), FALSE);
    cester_assert_uint_eq(xlist_contains(str)(fruits, "Banana"), TRUE);
    cester_assert_uint_eq(xlist_contains(str)(fruits, "Mango"), TRUE);
    cester_assert_uint_eq(xlist_contains(str)(fruits, "Grape"), FALSE);
    cester_assert_uint_eq(xlist_contains(str)(fruits, "Apple"), TRUE);

    xlist_destroy(str)(fruits);
})

CESTER_TEST(xlist_element_count, _, {
    xlist(str) *fruits;
    enum x_stat status;

    status = xlist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xlist_add(str)(fruits, "Apple"), XTD_OK);
    cester_assert_uint_eq(xlist_add(str)(fruits, "Banana"), XTD_OK);
    cester_assert_uint_eq(xlist_add(str)(fruits, "Coconut"), XTD_OK);
    cester_assert_uint_eq(xlist_add(str)(fruits, "Mango"), XTD_OK);
    cester_assert_uint_eq(xlist_add(str)(fruits, "Banana"), XTD_OK);
    cester_assert_uint_eq(xlist_add(str)(fruits, "Apple"), XTD_OK);
    cester_assert_uint_eq(xlist_add(str)(fruits, "Banana"), XTD_OK);

    cester_assert_uint_eq(xlist_element_count(str)(fruits, "Avocado"), 0);
    cester_assert_uint_eq(xlist_element_count(str)(fruits, "Banana"), 3);
    cester_assert_uint_eq(xlist_element_count(str)(fruits, "Mango"), 1);
    cester_assert_uint_eq(xlist_element_count(str)(fruits, "Grape"), 0);
    cester_assert_uint_eq(xlist_element_count(str)(fruits, "Apple"), 2);

    xlist_destroy(str)(fruits);
})

CESTER_TEST(xlist_add_at, _, {
    xlist(str) *fruits;
    enum x_stat status;
    char *value;

    status = xlist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xlist_size(fruits), 0);

    status = xlist_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xlist_size(fruits), 1);
    cester_assert_uint_eq(xlist_get_at(str)(fruits, 0, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");

    status = xlist_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xlist_size(fruits), 2);
    cester_assert_uint_eq(xlist_get_at(str)(fruits, 1, &value), XTD_OK);
    cester_assert_str_equal(value, "Banana");

    status = xlist_add_at(str)(fruits, "Coconut", 4);
    cester_assert_uint_eq(status, XTD_INDEX_OUT_OF_RANGE_ERR);

    status = xlist_add_at(str)(fruits, "Coconut", 2);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xlist_size(fruits), 3);

    status = xlist_add_at(str)(fruits, "Mango", 1);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xlist_size(fruits), 4);

    cester_assert_uint_eq(xlist_get_at(str)(fruits, 0, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xlist_get_at(str)(fruits, 1, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xlist_get_at(str)(fruits, 2, &value), XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xlist_get_at(str)(fruits, 3, &value), XTD_OK);
    cester_assert_str_equal(value, "Coconut");

    xlist_destroy(str)(fruits);
})

CESTER_TEST(xlist_get_str, _, {
    xlist(str) *fruits;
    enum x_stat status;
    char *value;

    status = xlist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add_at(str)(fruits, "Coconut", 4);
    cester_assert_uint_eq(status, XTD_INDEX_OUT_OF_RANGE_ERR);
    status = xlist_add_at(str)(fruits, "Coconut", 2);
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add_at(str)(fruits, "Mango", 1);
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_uint_eq(xlist_get_at(str)(fruits, 0, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xlist_get_at(str)(fruits, 3, &value), XTD_OK);
    cester_assert_str_equal(value, "Coconut");
    cester_assert_uint_eq(xlist_get_at(str)(fruits, 1, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xlist_get_at(str)(fruits, 2, &value), XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xlist_get_at(str)(fruits, 5, &value), XTD_INDEX_OUT_OF_RANGE_ERR);
    cester_assert_uint_eq(xlist_get_at(str)(fruits, -40, &value), XTD_INDEX_OUT_OF_RANGE_ERR);

    xlist_destroy(str)(fruits);
})

CESTER_TEST(xlist_replace_at, _, {
    xlist(str) *fruits;
    enum x_stat status;
    char *value;

    status = xlist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_uint_eq(xlist_get_at(str)(fruits, 0, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xlist_get_at(str)(fruits, 1, &value), XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xlist_get_at(str)(fruits, 2, &value), XTD_OK);
    cester_assert_str_equal(value, "Coconut");
    cester_assert_uint_eq(xlist_get_at(str)(fruits, 3, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");
    
    cester_assert_uint_eq(xlist_replace_at(str)(fruits, 0, "Orange", NULL), XTD_OK);
    cester_assert_uint_eq(xlist_replace_at(str)(fruits, 1, "Strawberry", NULL), XTD_OK);
    cester_assert_uint_eq(xlist_replace_at(str)(fruits, 2, "Pineapple", NULL), XTD_OK);
    cester_assert_uint_eq(xlist_replace_at(str)(fruits, 3, "Avocado", NULL), XTD_OK);

    cester_assert_uint_eq(xlist_get_at(str)(fruits, 0, &value), XTD_OK);
    cester_assert_str_equal(value, "Orange");
    cester_assert_uint_eq(xlist_get_at(str)(fruits, 1, &value), XTD_OK);
    cester_assert_str_equal(value, "Strawberry");
    cester_assert_uint_eq(xlist_get_at(str)(fruits, 2, &value), XTD_OK);
    cester_assert_str_equal(value, "Pineapple");
    cester_assert_uint_eq(xlist_get_at(str)(fruits, 3, &value), XTD_OK);
    cester_assert_str_equal(value, "Avocado");

    xlist_destroy(str)(fruits);
})

CESTER_TEST(xlist_front_back, _, {
    xlist(str) *fruits;
    enum x_stat status;
    char *value;

    status = xlist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_uint_eq(xlist_get_front(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xlist_get_back(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");

    xlist_destroy(str)(fruits);
})

CESTER_TEST(xlist_front_back_2, _, {
    xlist(str) *fruits;
    enum x_stat status;
    char *value;

    status = xlist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_uint_eq(xlist_get_front(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xlist_get_back(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");

    xlist_destroy(str)(fruits);
})

CESTER_TEST(xlist_front_back_3, _, {
    xlist(str) *fruits;
    enum x_stat status;
    char *value;

    status = xlist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_uint_eq(xlist_get_front(str)(fruits, &value), XTD_EMPTY_CONTAINER_ERR);
    cester_assert_uint_eq(xlist_get_back(str)(fruits, &value), XTD_EMPTY_CONTAINER_ERR);

    xlist_destroy(str)(fruits);
})

CESTER_TEST(xlist_max_size_1, _, {
    xlist(str) *fruits;
    enum x_stat status;

    status = xlist_new_max_size(str)(&fruits, 3);
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_MAX_SIZE_ERR);
    status = xlist_add(str)(fruits, "Watermelon");
    cester_assert_uint_eq(status, XTD_MAX_SIZE_ERR);
    
    cester_assert_false(xlist_is_empty(fruits));
    cester_assert_uint_eq(xlist_size(fruits), 3);
    cester_assert_llong_eq(xlist_max_size(fruits), 3);

    xlist_destroy(str)(fruits);
})

CESTER_TEST(xlist_max_size_2, _, {
    xlist(str) *fruits;
    enum x_stat status;
    int max_size = 6;

    status = xlist_new_max_size(str)(&fruits, max_size);
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Watermelon");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Avocado");
    cester_assert_uint_eq(status, XTD_MAX_SIZE_ERR);
    
    cester_assert_false(xlist_is_empty(fruits));
    cester_assert_uint_eq(xlist_size(fruits), max_size);
    cester_assert_llong_eq(xlist_max_size(fruits), max_size);

    xlist_destroy(str)(fruits);
})

CESTER_TEST(xlist_swap, _, {
    xlist(str) *fruits;
    xlist(str) *foods;
    enum x_stat status;
    char *value;

    status = xlist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);

    status = xlist_new(str)(&foods);
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(foods, "Amala");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(foods, "Iyan");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(foods, "Fufu");
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_uint_eq(xlist_get_front(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xlist_get_back(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xlist_get_front(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Amala");
    cester_assert_uint_eq(xlist_get_back(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Fufu");

    xswap(xlist_str)(foods, fruits);

    cester_assert_uint_eq(xlist_get_front(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xlist_get_back(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xlist_get_front(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Amala");
    cester_assert_uint_eq(xlist_get_back(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Fufu");

    xlist_destroy(str)(fruits);
})

CESTER_TEST(xlist_remove_front_and_back, _, {
    xlist(str) *fruits;
    enum x_stat status;
    char *value;

    status = xlist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    
    cester_assert_uint_eq(xlist_get_at(str)(fruits, 1, &value), XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xlist_size(fruits), 3);
    
    cester_assert_uint_eq(xlist_get_front(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    status = xlist_remove_front(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xlist_get_front(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xlist_size(fruits), 2);
    
    cester_assert_uint_eq(xlist_get_back(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");
    status = xlist_remove_back(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xlist_get_back(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xlist_size(fruits), 1);

    xlist_destroy(str)(fruits);
})

CESTER_TEST(xlist_remove_at, _, {
    xlist(str) *fruits;
    enum x_stat status;
    char *value;

    status = xlist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    
    cester_assert_uint_eq(xlist_get_at(str)(fruits, 1, &value), XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xlist_size(fruits), 3);

    status = xlist_remove_at(str)(fruits, 1, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xlist_get_at(str)(fruits, 1, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xlist_size(fruits), 2);

    status = xlist_remove_at(str)(fruits, 0, NULL);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xlist_get_at(str)(fruits, 1, &value), XTD_INDEX_OUT_OF_RANGE_ERR);
    cester_assert_uint_eq(xlist_size(fruits), 1);


    xlist_destroy(str)(fruits);
})

CESTER_TEST(xlist_clear, _, {
    xlist(str) *fruits;
    enum x_stat status;

    status = xlist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    
    cester_assert_uint_eq(xlist_size(fruits), 3);
    cester_assert_uint_eq(xlist_clear(str)(fruits), XTD_OK);
    cester_assert_uint_eq(xlist_size(fruits), 0);

    xlist_destroy(str)(fruits);
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)
