/*!gcc -ansi -pedantic-errors {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../../include/ -I../../../libcester/include -I../include/ -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/container/xslist.h>
#include <exotic/xtd/xiterator.h>
#include <exotic/xtd/algorithm/xalgorithm.h>

CESTER_BODY(
    typedef char* str;
    SETUP_XSLIST_FOR(int)
    SETUP_XSLIST_FOR(str)
    SETUP_XALGORITHM_SWAP_FOR(xslist_str)
)

CESTER_TEST(xslist_init, _, {
    xslist(str) *fruits;
    enum x_stat status;

    status = xslist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);

    xslist_destroy(str)(fruits);
})

CESTER_TEST(xslist_conf_init, _, {
    struct xcontainer_config config;
    xslist(str) *fruits;
    enum x_stat status;

    config.allocator.memory_malloc   = malloc;
    config.allocator.memory_calloc  = calloc;
    config.allocator.memory_free    = free;
    config.expansion_rate = 5;
    config.capacity       = 20;
    config.max_size       = 5000;
    status = xslist_new_config(str)(&config, &fruits);
    cester_assert_uint_eq(status, XTD_OK);

    xslist_destroy(str)(fruits);
})

CESTER_TEST(xslist_add_int, _, {
    xslist(int) *numbers;
    enum x_stat status;
    int index = 1;
    int limit = 20;

    status = xslist_new(int)(&numbers);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xslist_size(numbers), 0);

    for (; index <= limit; ++index) {
        status = xslist_add(int)(numbers, index);
        cester_assert_uint_eq(status, XTD_OK);
    }
    cester_assert_uint_eq(xslist_size(numbers), limit);

    xslist_destroy(int)(numbers);
})

CESTER_TEST(xslist_add_str, _, {
    xslist(str) *fruits;
    enum x_stat status;

    status = xslist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xslist_size(fruits), 0);

    status = xslist_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xslist_size(fruits), 1);

    status = xslist_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xslist_size(fruits), 2);

    status = xslist_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xslist_size(fruits), 3);

    status = xslist_add(str)(fruits, "Pawpaw");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xslist_size(fruits), 4);

    status = xslist_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xslist_size(fruits), 5); 

    xslist_destroy(str)(fruits);
})

CESTER_TEST(xslist_index_of, _, {
    size_t index;
    xslist(str) *fruits;
    enum x_stat status;

    status = xslist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xslist_add(str)(fruits, "Apple"), XTD_OK);
    cester_assert_uint_eq(xslist_add(str)(fruits, "Banana"), XTD_OK);
    cester_assert_uint_eq(xslist_add(str)(fruits, "Coconut"), XTD_OK);
    cester_assert_uint_eq(xslist_add(str)(fruits, "Mango"), XTD_OK);

    cester_assert_uint_eq(xslist_index_of(str)(fruits, "Avocado", &index), XTD_OUT_OF_RANGE_ERR);
    cester_assert_uint_eq(xslist_index_of(str)(fruits, "Banana", &index), XTD_OK);
    cester_assert_uint_eq(index, 1);
    cester_assert_uint_eq(xslist_index_of(str)(fruits, "Mango", &index), XTD_OK);
    cester_assert_uint_eq(index, 3);
    cester_assert_uint_eq(xslist_index_of(str)(fruits, "Grape", &index), XTD_OUT_OF_RANGE_ERR);
    cester_assert_uint_eq(xslist_index_of(str)(fruits, "Apple", &index), XTD_OK);
    cester_assert_uint_eq(index, 0);

    xslist_destroy(str)(fruits);
})

CESTER_TEST(xslist_contains, _, {
    xslist(str) *fruits;
    enum x_stat status;

    status = xslist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xslist_add(str)(fruits, "Apple"), XTD_OK);
    cester_assert_uint_eq(xslist_add(str)(fruits, "Banana"), XTD_OK);
    cester_assert_uint_eq(xslist_add(str)(fruits, "Coconut"), XTD_OK);
    cester_assert_uint_eq(xslist_add(str)(fruits, "Mango"), XTD_OK);

    cester_assert_uint_eq(xslist_contains(str)(fruits, "Avocado"), FALSE);
    cester_assert_uint_eq(xslist_contains(str)(fruits, "Banana"), TRUE);
    cester_assert_uint_eq(xslist_contains(str)(fruits, "Mango"), TRUE);
    cester_assert_uint_eq(xslist_contains(str)(fruits, "Grape"), FALSE);
    cester_assert_uint_eq(xslist_contains(str)(fruits, "Apple"), TRUE);

    xslist_destroy(str)(fruits);
})

CESTER_TEST(xslist_element_count, _, {
    xslist(str) *fruits;
    enum x_stat status;

    status = xslist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xslist_add(str)(fruits, "Apple"), XTD_OK);
    cester_assert_uint_eq(xslist_add(str)(fruits, "Banana"), XTD_OK);
    cester_assert_uint_eq(xslist_add(str)(fruits, "Coconut"), XTD_OK);
    cester_assert_uint_eq(xslist_add(str)(fruits, "Mango"), XTD_OK);
    cester_assert_uint_eq(xslist_add(str)(fruits, "Banana"), XTD_OK);
    cester_assert_uint_eq(xslist_add(str)(fruits, "Apple"), XTD_OK);
    cester_assert_uint_eq(xslist_add(str)(fruits, "Banana"), XTD_OK);

    cester_assert_uint_eq(xslist_element_count(str)(fruits, "Avocado"), 0);
    cester_assert_uint_eq(xslist_element_count(str)(fruits, "Banana"), 3);
    cester_assert_uint_eq(xslist_element_count(str)(fruits, "Mango"), 1);
    cester_assert_uint_eq(xslist_element_count(str)(fruits, "Grape"), 0);
    cester_assert_uint_eq(xslist_element_count(str)(fruits, "Apple"), 2);

    xslist_destroy(str)(fruits);
})

CESTER_TEST(xslist_add_at, _, {
    xslist(str) *fruits;
    enum x_stat status;
    char *value;

    status = xslist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xslist_size(fruits), 0);

    status = xslist_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xslist_size(fruits), 1);
    cester_assert_uint_eq(xslist_get_at(str)(fruits, 0, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");

    status = xslist_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xslist_size(fruits), 2);
    cester_assert_uint_eq(xslist_get_at(str)(fruits, 1, &value), XTD_OK);
    cester_assert_str_equal(value, "Banana");

    status = xslist_add_at(str)(fruits, "Coconut", 4);
    cester_assert_uint_eq(status, XTD_INDEX_OUT_OF_RANGE_ERR);

    status = xslist_add_at(str)(fruits, "Coconut", 2);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xslist_size(fruits), 3);

    status = xslist_add_at(str)(fruits, "Mango", 1);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xslist_size(fruits), 4);

    cester_assert_uint_eq(xslist_get_at(str)(fruits, 0, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xslist_get_at(str)(fruits, 1, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xslist_get_at(str)(fruits, 2, &value), XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xslist_get_at(str)(fruits, 3, &value), XTD_OK);
    cester_assert_str_equal(value, "Coconut");

    xslist_destroy(str)(fruits);
})

CESTER_TEST(xslist_get_str, _, {
    xslist(str) *fruits;
    enum x_stat status;
    char *value;

    status = xslist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add_at(str)(fruits, "Coconut", 4);
    cester_assert_uint_eq(status, XTD_INDEX_OUT_OF_RANGE_ERR);
    status = xslist_add_at(str)(fruits, "Coconut", 2);
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add_at(str)(fruits, "Mango", 1);
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_uint_eq(xslist_get_at(str)(fruits, 0, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xslist_get_at(str)(fruits, 3, &value), XTD_OK);
    cester_assert_str_equal(value, "Coconut");
    cester_assert_uint_eq(xslist_get_at(str)(fruits, 1, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xslist_get_at(str)(fruits, 2, &value), XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xslist_get_at(str)(fruits, 5, &value), XTD_INDEX_OUT_OF_RANGE_ERR);
    cester_assert_uint_eq(xslist_get_at(str)(fruits, -40, &value), XTD_INDEX_OUT_OF_RANGE_ERR);

    xslist_destroy(str)(fruits);
})

CESTER_TEST(xslist_replace_at, _, {
    xslist(str) *fruits;
    enum x_stat status;
    char *value;

    status = xslist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_uint_eq(xslist_get_at(str)(fruits, 0, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xslist_get_at(str)(fruits, 1, &value), XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xslist_get_at(str)(fruits, 2, &value), XTD_OK);
    cester_assert_str_equal(value, "Coconut");
    cester_assert_uint_eq(xslist_get_at(str)(fruits, 3, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");
    
    cester_assert_uint_eq(xslist_replace_at(str)(fruits, 0, "Orange", NULL), XTD_OK);
    cester_assert_uint_eq(xslist_replace_at(str)(fruits, 1, "Strawberry", NULL), XTD_OK);
    cester_assert_uint_eq(xslist_replace_at(str)(fruits, 2, "Pineapple", NULL), XTD_OK);
    cester_assert_uint_eq(xslist_replace_at(str)(fruits, 3, "Avocado", NULL), XTD_OK);

    cester_assert_uint_eq(xslist_get_at(str)(fruits, 0, &value), XTD_OK);
    cester_assert_str_equal(value, "Orange");
    cester_assert_uint_eq(xslist_get_at(str)(fruits, 1, &value), XTD_OK);
    cester_assert_str_equal(value, "Strawberry");
    cester_assert_uint_eq(xslist_get_at(str)(fruits, 2, &value), XTD_OK);
    cester_assert_str_equal(value, "Pineapple");
    cester_assert_uint_eq(xslist_get_at(str)(fruits, 3, &value), XTD_OK);
    cester_assert_str_equal(value, "Avocado");

    xslist_destroy(str)(fruits);
})

CESTER_TEST(xslist_front_back, _, {
    xslist(str) *fruits;
    enum x_stat status;
    char *value;

    status = xslist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_uint_eq(xslist_get_front(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xslist_get_back(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");

    xslist_destroy(str)(fruits);
})

CESTER_TEST(xslist_front_back_2, _, {
    xslist(str) *fruits;
    enum x_stat status;
    char *value;

    status = xslist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_uint_eq(xslist_get_front(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xslist_get_back(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");

    xslist_destroy(str)(fruits);
})

CESTER_TEST(xslist_front_back_3, _, {
    xslist(str) *fruits;
    enum x_stat status;
    char *value;

    status = xslist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_uint_eq(xslist_get_front(str)(fruits, &value), XTD_EMPTY_CONTAINER_ERR);
    cester_assert_uint_eq(xslist_get_back(str)(fruits, &value), XTD_EMPTY_CONTAINER_ERR);

    xslist_destroy(str)(fruits);
})

CESTER_TEST(xslist_max_size_1, _, {
    xslist(str) *fruits;
    enum x_stat status;

    status = xslist_new_max_size(str)(&fruits, 3);
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_MAX_SIZE_ERR);
    status = xslist_add(str)(fruits, "Watermelon");
    cester_assert_uint_eq(status, XTD_MAX_SIZE_ERR);
    
    cester_assert_false(xslist_is_empty(fruits));
    cester_assert_uint_eq(xslist_size(fruits), 3);
    cester_assert_llong_eq(xslist_max_size(fruits), 3);

    xslist_destroy(str)(fruits);
})

CESTER_TEST(xslist_max_size_2, _, {
    xslist(str) *fruits;
    enum x_stat status;
    int max_size = 6;

    status = xslist_new_max_size(str)(&fruits, max_size);
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Watermelon");
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Avocado");
    cester_assert_uint_eq(status, XTD_MAX_SIZE_ERR);
    
    cester_assert_false(xslist_is_empty(fruits));
    cester_assert_uint_eq(xslist_size(fruits), max_size);
    cester_assert_llong_eq(xslist_max_size(fruits), max_size);

    xslist_destroy(str)(fruits);
})

CESTER_TEST(xslist_swap, _, {
    xslist(str) *fruits;
    xslist(str) *foods;
    enum x_stat status;
    char *value;

    status = xslist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);

    status = xslist_new(str)(&foods);
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(foods, "Amala");
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(foods, "Iyan");
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(foods, "Fufu");
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_uint_eq(xslist_get_front(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xslist_get_back(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xslist_get_front(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Amala");
    cester_assert_uint_eq(xslist_get_back(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Fufu");

    xswap(xslist_str)(foods, fruits);

    cester_assert_uint_eq(xslist_get_front(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xslist_get_back(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xslist_get_front(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Amala");
    cester_assert_uint_eq(xslist_get_back(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Fufu");

    xslist_destroy(str)(fruits);
})

CESTER_TEST(xslist_remove_front_and_back, _, {
    xslist(str) *fruits;
    enum x_stat status;
    char *value;

    status = xslist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    
    cester_assert_uint_eq(xslist_get_at(str)(fruits, 1, &value), XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xslist_size(fruits), 3);
    
    cester_assert_uint_eq(xslist_get_front(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    status = xslist_remove_front(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xslist_get_front(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xslist_size(fruits), 2);
    
    cester_assert_uint_eq(xslist_get_back(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");
    status = xslist_remove_back(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xslist_get_back(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xslist_size(fruits), 1);

    xslist_destroy(str)(fruits);
})

CESTER_TEST(xslist_remove_at, _, {
    xslist(str) *fruits;
    enum x_stat status;
    char *value;

    status = xslist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    
    cester_assert_uint_eq(xslist_get_at(str)(fruits, 1, &value), XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xslist_size(fruits), 3);

    status = xslist_remove_at(str)(fruits, 1, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xslist_get_at(str)(fruits, 1, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xslist_size(fruits), 2);

    status = xslist_remove_at(str)(fruits, 0, NULL);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xslist_get_at(str)(fruits, 1, &value), XTD_INDEX_OUT_OF_RANGE_ERR);
    cester_assert_uint_eq(xslist_size(fruits), 1);


    xslist_destroy(str)(fruits);
})

CESTER_TEST(xslist_clear, _, {
    xslist(str) *fruits;
    enum x_stat status;

    status = xslist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    
    cester_assert_uint_eq(xslist_size(fruits), 3);
    cester_assert_uint_eq(xslist_clear(str)(fruits), XTD_OK);
    cester_assert_uint_eq(xslist_size(fruits), 0);

    xslist_destroy(str)(fruits);
})

CESTER_TEST(xslist_previous_node, _, {
    xslist(str) *fruits;
    xsingle_node(str) *node;
    xsingle_node(str) *prev;
    enum x_stat status;

    status = xslist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xslist_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    
    cester_assert_uint_eq(xslist_size(fruits), 3);
    status = xslist_str_get_node_at(fruits, 0, &node, &prev);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_ptr_equal(xnode_get_data(prev), XTD_NULL);
    status = xslist_str_get_node_at(fruits, 1, &node, &prev);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(xnode_get_data(prev), "Apple");
    status = xslist_str_get_node_at(fruits, 2, &node, &prev);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(xnode_get_data(prev), "Banana");

    
    status = xslist_str_get_node_at(fruits, 0, &node, &prev);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_ptr_equal(xslist_previous_node(str)(fruits, node), XTD_NULL);
    status = xslist_str_get_node_at(fruits, 1, &node, &prev);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(xnode_get_data(xslist_previous_node(str)(fruits, node)), "Apple");
    status = xslist_str_get_node_at(fruits, 2, &node, &prev);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(xnode_get_data(xslist_previous_node(str)(fruits, node)), "Banana");
    
    xslist_destroy(str)(fruits);
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)
