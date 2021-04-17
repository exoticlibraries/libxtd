/*!gcc -ansi -pedantic-errors {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/xlist.h>
#include <exotic/xtd/xiterator.h>
#include <exotic/xtd/xalgorithm.h>

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

    config.memory_alloc   = malloc;
    config.memory_calloc  = calloc;
    config.memory_free    = free;
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

CESTER_TEST(xlist_iterator, _, {
    enum x_stat status;
    xlist(str) *fruits;
    xlist_iterator(str) *iterator;

    status = xlist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_UD_INIT(xlist_str)(fruits);
    while (XITERATOR_UD_HAS_NEXT(xlist_str)(iterator)) {
        cester_assert_str_not_equal(XITERATOR_UD_NEXT(xlist_str)(iterator), NULL);
    }
    XITERATOR_UD_RESET(xlist_str)(iterator);
    cester_assert_uint_eq(XITERATOR_UD_HAS_NEXT(xlist_str)(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_UD_NEXT(xlist_str)(iterator), "Apple");
    cester_assert_uint_eq(XITERATOR_UD_HAS_NEXT(xlist_str)(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_UD_NEXT(xlist_str)(iterator), "Banana");
    cester_assert_uint_eq(XITERATOR_UD_HAS_NEXT(xlist_str)(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_UD_NEXT(xlist_str)(iterator), "Mango");
    cester_assert_uint_eq(XITERATOR_UD_HAS_NEXT(xlist_str)(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_UD_NEXT(xlist_str)(iterator), "Pineapple");
    
    XITERATOR_UD_DESTROY(xlist_str)(iterator);
    xlist_destroy(str)(fruits);
})

CESTER_TEST(xlist_iterator_reverse, _, {
    enum x_stat status;
    xlist(str) *fruits;
    xlist_iterator(str) *iterator;

    status = xlist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_UD_INIT(xlist_str)(fruits);
    while (XITERATOR_UD_HAS_PREV(xlist_str)(iterator)) {
        cester_assert_str_not_equal(XITERATOR_UD_PREV(xlist_str)(iterator), NULL);
    }
    XITERATOR_UD_RESET(xlist_str)(iterator);
    cester_assert_uint_eq(XITERATOR_UD_HAS_PREV(xlist_str)(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_UD_PREV(xlist_str)(iterator), "Pineapple");
    cester_assert_uint_eq(XITERATOR_UD_HAS_PREV(xlist_str)(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_UD_PREV(xlist_str)(iterator), "Mango");
    cester_assert_uint_eq(XITERATOR_UD_HAS_PREV(xlist_str)(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_UD_PREV(xlist_str)(iterator), "Banana");
    cester_assert_uint_eq(XITERATOR_UD_HAS_PREV(xlist_str)(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_UD_PREV(xlist_str)(iterator), "Apple");

    XITERATOR_UD_DESTROY(xlist_str)(iterator);
    xlist_destroy(str)(fruits);
})

CESTER_TEST(xlist_foreach, _, {
    xlist(str) *fruits;
    enum x_stat status;
    xlist_iterator(str) *iterator;

    status = xlist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_UD_INIT(xlist_str)(fruits);
    XFOREACH_UD(xlist_str, const char *fruit, iterator, {
        cester_assert_str_not_equal(fruit, NULL);
    });

    XITERATOR_UD_DESTROY(xlist_str)(iterator);
    xlist_destroy(str)(fruits);
})

CESTER_TEST(xlist_foreach_reverse, _, {
    xlist(str) *fruits;
    enum x_stat status;
    xlist_iterator(str) *iterator;

    status = xlist_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xlist_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_UD_INIT(xlist_str)(fruits);
    XFOREACH_UD_REVERSE(xlist_str, const char *fruit, iterator, {
        cester_assert_str_not_equal(fruit, NULL);
    });

    XITERATOR_UD_DESTROY(xlist_str)(iterator);
    xlist_destroy(str)(fruits);
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)
