/*!gcc  -ansi -pedantic-errors {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xqueue.h>
#include <exotic/xiterator.h>
#include <exotic/xalgorithm.h>

CESTER_BODY(
    typedef char* str;
    typedef char** char_array;
    SETUP_XDEQUE_FOR(str)
    SETUP_ONLY_XQUEUE_FOR(str)
    SETUP_XALGORITHM_SWAP_FOR(xqueue_str)
    SETUP_XALGORITHM_SWAP_FOR(char_array)
)

CESTER_TEST(xqueue_init, _, {
    xqueue(str) *fruits;
    enum x_stat status;

    status = xqueue_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);

    xqueue_destroy(fruits);
})

CESTER_TEST(xqueue_conf_init, _, {
    struct xcontainer_config config;
    xqueue(str) *fruits;
    enum x_stat status;

    config.memory_alloc   = malloc;
    config.memory_calloc  = calloc;
    config.memory_free    = free;
    config.expansion_rate = 5;
    config.capacity       = 20;
    status = xqueue_new_config(str)(&config, &fruits);
    cester_assert_uint_eq(status, XTD_OK);

    xqueue_destroy(fruits);
})

CESTER_TEST(xqueue_enqueue, _, {
    xqueue(str) *fruits;
    enum x_stat status;
    
    status = xqueue_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_true(xqueue_is_empty(fruits));
    cester_assert_uint_eq(xqueue_size(fruits), 0);

    status = xqueue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status =xqueue_enqueue(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_false(xqueue_is_empty(fruits));
    cester_assert_uint_eq(xqueue_size(fruits), 4);

    xqueue_destroy(fruits);
})

CESTER_TEST(xqueue_peek, _, {
    xqueue(str) *fruits;
    enum x_stat status;
    char *value;

    status = xqueue_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    
    status = xqueue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_peek(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xqueue_size(fruits), 1);

    status = xqueue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_peek(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xqueue_size(fruits), 2);

    status =xqueue_enqueue(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_peek(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xqueue_size(fruits), 3);

    status = xqueue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_peek(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xqueue_size(fruits), 4);

    xqueue_destroy(fruits);
})

CESTER_TEST(xqueue_dequeue, _, {
    xqueue(str) *fruits;
    enum x_stat status;
    char *value;

    status = xqueue_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);

    status = xqueue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status =xqueue_enqueue(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);

    status = xqueue_dequeue(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xqueue_size(fruits), 3);

    status = xqueue_dequeue(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xqueue_size(fruits), 2);

    status = xqueue_dequeue(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Coconut");
    cester_assert_uint_eq(xqueue_size(fruits), 1);

    status = xqueue_dequeue(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xqueue_size(fruits), 0);

    xqueue_destroy(fruits);
})

CESTER_TEST(xqueue_dequeue_underflow, _, {
    xqueue(str) *fruits;
    enum x_stat status;
    char *value;

    status = xqueue_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);

    status = xqueue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status =xqueue_enqueue(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);

    status = xqueue_dequeue(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xqueue_size(fruits), 3);

    status = xqueue_dequeue(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xqueue_size(fruits), 2);

    status = xqueue_dequeue(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Coconut");
    cester_assert_uint_eq(xqueue_size(fruits), 1);

    status = xqueue_dequeue(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xqueue_size(fruits), 0);

    status = xqueue_dequeue(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_EMPTY_CONTAINER_ERR);

    status = xqueue_dequeue(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_EMPTY_CONTAINER_ERR);

    xqueue_destroy(fruits);
})

CESTER_TEST(xqueue_capacity, _, {
    xqueue(str) *fruits;
    enum x_stat status;

    status = xqueue_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    
    cester_assert_false(xqueue_is_empty(fruits));
    cester_assert_uint_eq(xqueue_size(fruits), 4);
    cester_assert_uint_eq(xqueue_capacity(fruits), XDEFAULT_CONTAINER_CAPACITY);
    cester_assert_equal(xqueue_max_size(fruits), XTD_CONTAINER_MAXTD_CAPACITY);

    xqueue_destroy(fruits);
})

CESTER_TEST(xqueue_max_size_1, _, {
    xqueue(str) *fruits;
    enum x_stat status;

    status = xqueue_new_max_size(str)(&fruits, 3);
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_MAXTD_SIZE_ERR);
    status = xqueue_enqueue(str)(fruits, "Watermelon");
    cester_assert_uint_eq(status, XTD_MAXTD_SIZE_ERR);
    
    cester_assert_false(xqueue_is_empty(fruits));
    cester_assert_uint_eq(xqueue_size(fruits), 3);
    cester_assert_uint_eq(xqueue_capacity(fruits), 4);
    cester_assert_llong_eq(xqueue_max_size(fruits), 3);

    xqueue_destroy(fruits);
})

CESTER_TEST(xqueue_max_size_2, _, {
    xqueue(str) *fruits;
    enum x_stat status;
    int max_size = 6;

    status = xqueue_new_max_size(str)(&fruits, max_size);
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Carrot");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Watermelon");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_MAXTD_SIZE_ERR);
    status = xqueue_enqueue(str)(fruits, "Avocado");
    cester_assert_uint_eq(status, XTD_MAXTD_SIZE_ERR);
    
    cester_assert_false(xqueue_is_empty(fruits));
    cester_assert_uint_eq(xqueue_size(fruits), max_size);
    cester_assert_uint_eq(xqueue_capacity(fruits), (XDEFAULT_CONTAINER_CAPACITY * XDEFAULT_CONTAINER_EXPANSION_RATE));
    cester_assert_llong_eq(xqueue_max_size(fruits), max_size);

    xqueue_destroy(fruits);
})

CESTER_TEST(xqueue_swap, _, {
    xqueue(str) *fruits;
    xqueue(str) *foods;
    enum x_stat status;
    char *value;

    status = xqueue_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);

    status = xqueue_new(str)(&foods);
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(foods, "Amala");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(foods, "Iyan");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(foods, "Fufu");
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_uint_eq(xqueue_peek(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xqueue_peek(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Amala");

    xswap(xqueue_str)(foods, fruits);

    cester_assert_uint_eq(xqueue_peek(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Amala");
    cester_assert_uint_eq(xqueue_peek(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");

    xqueue_destroy(fruits);
})

CESTER_TEST(xqueue_swap_buffer, _, {
    printf("NEVER EVER SWAP BUFFER OF XQUEUE\n");
})

CESTER_TEST(xqueue_iterator, _, {
    xqueue(str) *fruits;
    enum x_stat status;

    status = xqueue_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    
    while (XITERATOR_HAS_NEXT(fruits)) {
        cester_assert_str_not_equal(XITERATOR_NEXT(fruits), NULL);
    }
    XITERATOR_RESET(fruits);
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(fruits), TRUE);
    cester_assert_str_equal(XITERATOR_NEXT(fruits), "Apple");
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(fruits), TRUE);
    cester_assert_str_equal(XITERATOR_NEXT(fruits), "Banana");
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(fruits), TRUE);
    cester_assert_str_equal(XITERATOR_NEXT(fruits), "Mango");
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(fruits), TRUE);
    cester_assert_str_equal(XITERATOR_NEXT(fruits), "Pineapple");

    xqueue_destroy(fruits);
})

CESTER_TEST(xqueue_iterator_reverse, _, {
    xqueue(str) *fruits;
    enum x_stat status;

    status = xqueue_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    
    while (XITERATOR_HAS_PREV(fruits)) {
        cester_assert_str_not_equal(XITERATOR_PREV(fruits), NULL);
    }
    XITERATOR_RESET(fruits);
    cester_assert_uint_eq(XITERATOR_HAS_PREV(fruits), TRUE);
    cester_assert_str_equal(XITERATOR_PREV(fruits), "Pineapple");
    cester_assert_uint_eq(XITERATOR_HAS_PREV(fruits), TRUE);
    cester_assert_str_equal(XITERATOR_PREV(fruits), "Mango");
    cester_assert_uint_eq(XITERATOR_HAS_PREV(fruits), TRUE);
    cester_assert_str_equal(XITERATOR_PREV(fruits), "Banana");
    cester_assert_uint_eq(XITERATOR_HAS_PREV(fruits), TRUE);
    cester_assert_str_equal(XITERATOR_PREV(fruits), "Apple");

    xqueue_destroy(fruits);
})

CESTER_TEST(xqueue_foreach, _, {
    xqueue(str) *fruits;
    enum x_stat status;

    status = xqueue_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    XFOREACH(const char *fruit, fruits, {
        cester_assert_str_not_equal(fruit, NULL);
    });

    xqueue_destroy(fruits);
})

CESTER_TEST(xqueue_foreach_reverse, _, {
    xqueue(str) *fruits;
    enum x_stat status;

    status = xqueue_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    XFOREACH_REVERSE(const char *fruit, fruits, {
        cester_assert_str_not_equal(fruit, NULL);
    });

    xqueue_destroy(fruits);
})

CESTER_TEST(xqueue_foreach_with_index, _, {
    xqueue(str) *fruits;
    enum x_stat status;

    status = xqueue_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    XFOREACH_INDEX(size_t index, const char *fruit, fruits, {
        if (index == 0) {
            cester_assert_str_equal(fruit, "Apple");
        } else if (index == 1) {
            cester_assert_str_equal(fruit, "Banana");
        } else if (index == 2) {
            cester_assert_str_equal(fruit, "Mango");
        } else if (index == 3) {
            cester_assert_str_equal(fruit, "Pineapple");
        }
    });

    xqueue_destroy(fruits);
})

CESTER_TEST(xqueue_foreach_reverse_with_index, _, {
    xqueue(str) *fruits;
    enum x_stat status;

    status = xqueue_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    XFOREACH_REVERSE_INDEX(size_t index, const char *fruit, fruits, {
        if (index == 3) {
            cester_assert_str_equal(fruit, "Pineapple");
        } else if (index == 2) {
            cester_assert_str_equal(fruit, "Mango");
        } else if (index == 1) {
            cester_assert_str_equal(fruit, "Banana");
        } else if (index == 0) {
            cester_assert_str_equal(fruit, "Apple");
        }
    });

    xqueue_destroy(fruits);
})

CESTER_TEST(xqueue_modify_in_loop, _, {
    xqueue(str) *fruits;
    enum x_stat status;

    status = xqueue_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xqueue_enqueue(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    XFOREACH_INDEX(size_t index, const char *fruit, fruits, {
        if (xqueue_size(fruits) > 2) {
            status = xqueue_dequeue(str)(fruits, NULL);
            cester_assert_uint_eq(status, XTD_OK);
        }
        cester_assert_str_not_equal(fruit, "Mango");
        cester_assert_str_not_equal(fruit, "Pineapple");
    });

    xqueue_destroy(fruits);
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)

