/*!gcc  -ansi -pedantic-errors {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/xvector.h>
#include <exotic/xtd/xiterator.h>
#include <exotic/xtd/xalgorithm.h>

CESTER_BODY(
    typedef char* str;
    typedef char** char_array;
    SETUP_XVECTOR_ONLY_FOR(int)
    SETUP_XVECTOR_FOR(str)
    SETUP_XALGORITHM_SWAP_FOR(xvector_str)
    SETUP_XALGORITHM_SWAP_FOR(char_array)
)

CESTER_TEST(xvector_init, _, {
    xvector(str) *fruits;
    enum x_stat status;

    status = xvector_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);

    xvector_destroy(fruits);
})

CESTER_TEST(xvector_conf_init, _, {
    struct xcontainer_config config;
    xvector(str) *fruits;
    enum x_stat status;

    config.memory_alloc   = malloc;
    config.memory_calloc  = calloc;
    config.memory_free    = free;
    config.expansion_rate = 5;
    config.capacity       = 20;
    config.max_size       = 5000;
    status = xvector_new_config(str)(&config, &fruits);
    cester_assert_uint_eq(status, XTD_OK);

    xvector_destroy(fruits);
})

CESTER_TEST(xvector_add_int, _, {
    xvector(int) *numbers;
    enum x_stat status;
    int index = 1;
    int limit = 20;

    status = xvector_new(int)(&numbers);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xvector_size(numbers), 0);

    for (; index <= limit; ++index) {
        status = xvector_add(int)(numbers, index);
        cester_assert_uint_eq(status, XTD_OK);
    }
    cester_assert_uint_eq(xvector_size(numbers), limit);

    xvector_destroy(numbers);
})

CESTER_TEST(xvector_add_str, _, {
    xvector(str) *fruits;
    enum x_stat status;

    status = xvector_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xvector_size(fruits), 0);

    status = xvector_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xvector_size(fruits), 1);

    status = xvector_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xvector_size(fruits), 2);

    status = xvector_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xvector_size(fruits), 3);

    status = xvector_add(str)(fruits, "Pawpaw");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xvector_size(fruits), 4);

    status = xvector_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xvector_size(fruits), 5); 

    xvector_destroy(fruits);
})

CESTER_TEST(xvector_add_at, _, {
    xvector(str) *fruits;
    enum x_stat status;

    status = xvector_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xvector_size(fruits), 0);

    status = xvector_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xvector_size(fruits), 1);
    cester_assert_str_equal(xget_at(fruits, 0), "Apple");

    status = xvector_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xvector_size(fruits), 2);
    cester_assert_str_equal(xget_at(fruits, 1), "Banana");

    status = xvector_add_at(str)(fruits, "Coconut", 4);
    cester_assert_uint_eq(status, XTD_INDEX_OUT_OF_RANGE_ERR);

    status = xvector_add_at(str)(fruits, "Coconut", 2);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xvector_size(fruits), 3);

    status = xvector_add_at(str)(fruits, "Mango", 1);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xvector_size(fruits), 4);

    cester_assert_str_equal(xget_at(fruits, 0), "Apple");
    cester_assert_str_equal(xget_at(fruits, 1), "Mango");
    cester_assert_str_equal(xget_at(fruits, 2), "Banana");
    cester_assert_str_equal(xget_at(fruits, 3), "Coconut");

    xvector_destroy(fruits);
})

CESTER_TEST(xvector_get_str, _, {
    xvector(str) *fruits;
    enum x_stat status;
    char *value;

    status = xvector_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add_at(str)(fruits, "Coconut", 4);
    cester_assert_uint_eq(status, XTD_INDEX_OUT_OF_RANGE_ERR);
    status = xvector_add_at(str)(fruits, "Coconut", 2);
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add_at(str)(fruits, "Mango", 1);
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_uint_eq(xvector_get_at(str)(fruits, 0, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xvector_get_at(str)(fruits, 3, &value), XTD_OK);
    cester_assert_str_equal(value, "Coconut");
    cester_assert_uint_eq(xvector_get_at(str)(fruits, 1, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xvector_get_at(str)(fruits, 2, &value), XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xvector_get_at(str)(fruits, 5, &value), XTD_INDEX_OUT_OF_RANGE_ERR);
    cester_assert_uint_eq(xvector_get_at(str)(fruits, -40, &value), XTD_INDEX_OUT_OF_RANGE_ERR);

    xvector_destroy(fruits);
})

CESTER_TEST(xvector_replace_at, _, {
    xvector(str) *fruits;
    enum x_stat status;

    status = xvector_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_str_equal(xget_at(fruits, 0), "Apple");
    cester_assert_str_equal(xget_at(fruits, 1), "Banana");
    cester_assert_str_equal(xget_at(fruits, 2), "Coconut");
    cester_assert_str_equal(xget_at(fruits, 3), "Mango");
    
    cester_assert_uint_eq(xvector_replace_at(str)(fruits, 0, "Orange", NULL), XTD_OK);
    cester_assert_uint_eq(xvector_replace_at(str)(fruits, 1, "Strawberry", NULL), XTD_OK);
    cester_assert_uint_eq(xvector_replace_at(str)(fruits, 2, "Pineapple", NULL), XTD_OK);
    cester_assert_uint_eq(xvector_replace_at(str)(fruits, 3, "Avocado", NULL), XTD_OK);

    cester_assert_str_equal(xget_at(fruits, 0), "Orange");
    cester_assert_str_equal(xget_at(fruits, 1), "Strawberry");
    cester_assert_str_equal(xget_at(fruits, 2), "Pineapple");
    cester_assert_str_equal(xget_at(fruits, 3), "Avocado");

    xvector_destroy(fruits);
})

CESTER_TEST(xvector_front_back, _, {
    xvector(str) *fruits;
    enum x_stat status;
    char *value;

    status = xvector_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_uint_eq(xvector_get_front(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xvector_get_back(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");

    xvector_destroy(fruits);
})

CESTER_TEST(xvector_front_back_2, _, {
    xvector(str) *fruits;
    enum x_stat status;
    char *value;

    status = xvector_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_uint_eq(xvector_get_front(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xvector_get_back(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");

    xvector_destroy(fruits);
})

CESTER_TEST(xvector_front_back_3, _, {
    xvector(str) *fruits;
    enum x_stat status;
    char *value;

    status = xvector_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_uint_eq(xvector_get_front(str)(fruits, &value), XTD_EMPTY_CONTAINER_ERR);
    cester_assert_uint_eq(xvector_get_back(str)(fruits, &value), XTD_EMPTY_CONTAINER_ERR);

    xvector_destroy(fruits);
})

CESTER_TEST(xvector_capacity, _, {
    xvector(str) *fruits;
    enum x_stat status;

    status = xvector_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    
    cester_assert_false(xvector_is_empty(fruits));
    cester_assert_uint_eq(xvector_size(fruits), 4);
    cester_assert_uint_eq(xvector_capacity(fruits), XDEFAULT_CONTAINER_CAPACITY);
    cester_assert_equal(xvector_max_size(fruits), XTD_CONTAINER_MAX_CAPACITY);

    xvector_destroy(fruits);
})

CESTER_TEST(xvector_max_size_1, _, {
    xvector(str) *fruits;
    enum x_stat status;

    status = xvector_new_max_size(str)(&fruits, 3);
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_MAX_SIZE_ERR);
    status = xvector_add(str)(fruits, "Watermelon");
    cester_assert_uint_eq(status, XTD_MAX_SIZE_ERR);
    
    cester_assert_false(xvector_is_empty(fruits));
    cester_assert_uint_eq(xvector_size(fruits), 3);
    cester_assert_uint_eq(xvector_capacity(fruits), 3);
    cester_assert_llong_eq(xvector_max_size(fruits), 3);

    xvector_destroy(fruits);
})

CESTER_TEST(xvector_max_size_2, _, {
    xvector(str) *fruits;
    enum x_stat status;
    int max_size = 6;

    status = xvector_new_max_size(str)(&fruits, max_size);
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Watermelon");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Avocado");
    cester_assert_uint_eq(status, XTD_MAX_SIZE_ERR);
    
    cester_assert_false(xvector_is_empty(fruits));
    cester_assert_uint_eq(xvector_size(fruits), max_size);
    cester_assert_uint_eq(xvector_capacity(fruits), (XDEFAULT_CONTAINER_CAPACITY * XDEFAULT_CONTAINER_EXPANSION_RATE));
    cester_assert_llong_eq(xvector_max_size(fruits), max_size);

    xvector_destroy(fruits);
})

CESTER_TEST(xvector_shrink_to_fit, _, {
    xvector(str) *fruits;
    enum x_stat status;

    status = xvector_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    cester_assert_false(xvector_is_empty(fruits));
    cester_assert_uint_eq(xvector_size(fruits), 5);
    cester_assert_uint_eq(xvector_capacity(fruits), (XDEFAULT_CONTAINER_CAPACITY * XDEFAULT_CONTAINER_EXPANSION_RATE));
    status = xvector_shrink_to_fit(str)(fruits);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xvector_capacity(fruits), 5);

    xvector_destroy(fruits);
})

CESTER_TEST(xvector_swap, _, {
    xvector(str) *fruits;
    xvector(str) *foods;
    enum x_stat status;
    char *value;

    status = xvector_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);

    status = xvector_new(str)(&foods);
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(foods, "Amala");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(foods, "Iyan");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(foods, "Fufu");
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_uint_eq(xvector_get_front(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xvector_get_back(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xvector_get_front(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Amala");
    cester_assert_uint_eq(xvector_get_back(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Fufu");

    xswap(xvector_str)(foods, fruits);

    cester_assert_uint_eq(xvector_get_front(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xvector_get_back(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xvector_get_front(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Amala");
    cester_assert_uint_eq(xvector_get_back(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Fufu");

    xvector_destroy(fruits);
})

CESTER_TEST(xvector_swap_buffer, _, {
    xvector(str) *fruits;
    xvector(str) *foods;
    enum x_stat status;
    char *value;

    status = xvector_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);

    status = xvector_new(str)(&foods);
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(foods, "Amala");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(foods, "Iyan");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(foods, "Fufu");
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_uint_eq(xvector_get_front(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xvector_get_back(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xvector_get_front(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Amala");
    cester_assert_uint_eq(xvector_get_back(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Fufu");

    xswap(char_array)(&xget_buffer(foods), &xget_buffer(fruits));

    cester_assert_uint_eq(xvector_get_front(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xvector_get_back(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xvector_get_front(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Amala");
    cester_assert_uint_eq(xvector_get_back(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Fufu");

    xvector_destroy(fruits);
})

CESTER_TEST(xvector_remove_front_and_back, _, {
    xvector(str) *fruits;
    enum x_stat status;
    char *value;

    status = xvector_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    
    cester_assert_uint_eq(xvector_get_at(str)(fruits, 1, &value), XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xvector_size(fruits), 3);
    
    cester_assert_uint_eq(xvector_get_front(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    status = xvector_remove_front(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xvector_get_front(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xvector_size(fruits), 2);
    
    cester_assert_uint_eq(xvector_get_back(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");
    status = xvector_remove_back(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xvector_get_back(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xvector_size(fruits), 1);

    xvector_destroy(fruits);
})

CESTER_TEST(xvector_remove_at, _, {
    xvector(str) *fruits;
    enum x_stat status;
    char *value;

    status = xvector_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    
    cester_assert_uint_eq(xvector_get_at(str)(fruits, 1, &value), XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xvector_size(fruits), 3);

    status = xvector_remove_at(str)(fruits, 1, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xvector_get_at(str)(fruits, 1, &value), XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xvector_size(fruits), 2);

    status = xvector_remove_at(str)(fruits, 0, NULL);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xvector_get_at(str)(fruits, 1, &value), XTD_INDEX_OUT_OF_RANGE_ERR);
    cester_assert_uint_eq(xvector_size(fruits), 1);


    xvector_destroy(fruits);
})

CESTER_TEST(xvector_clear, _, {
    xvector(str) *fruits;
    enum x_stat status;

    status = xvector_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xvector_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    
    cester_assert_uint_eq(xvector_size(fruits), 3);
    cester_assert_uint_eq(xvector_clear(str)(fruits), XTD_OK);
    cester_assert_uint_eq(xvector_size(fruits), 0);


    xvector_destroy(fruits);
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)
