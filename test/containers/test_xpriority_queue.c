/*!gcc  -ansi -pedantic-errors {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/container/xpriority_queue.h>
#include <exotic/xtd/xiterator.h>
#include <exotic/xtd/algorithm/xalgorithm.h>

CESTER_BODY(
    typedef char* str;
    typedef char** char_array;
    SETUP_XPRIORITY_QUEUE_FOR(str)
    SETUP_XPRIORITY_QUEUE_ONLY_FOR(int)
    SETUP_XALGORITHM_SWAP_FOR(xpriority_queue_str)
    SETUP_XALGORITHM_SWAP_FOR(char_array)

    bool cmp_str(char * const a, char * const b) {
        return *a < *b;
    }

    bool cmp_int_gt(int const a, int const b) {
        return a > b;
    }

    bool cmp_int_lt(int const a, int const b) {
        return a < b;
    }
)

CESTER_TEST(xpriority_queue_init, _, {
    xpriority_queue(str) *fruits;
    enum x_stat status;

    status = xpriority_queue_new(str)(&fruits, cmp_str);
    cester_assert_uint_eq(status, XTD_OK);

    xpriority_queue_destroy(fruits);
})

CESTER_TEST(xpriority_queue_conf_init, _, {
    struct xcontainer_config config;
    xpriority_queue(str) *fruits;
    enum x_stat status;

    config.allocator.memory_malloc   = malloc;
    config.allocator.memory_calloc  = calloc;
    config.allocator.memory_free    = free;
    config.expansion_rate = 5;
    config.capacity       = 20;
    config.max_size       = 5000;
    status = xpriority_queue_new_config(str)(&config, &fruits, cmp_str);
    cester_assert_uint_eq(status, XTD_OK);

    xpriority_queue_destroy(fruits);
})

CESTER_TEST(xpriority_queue_enqueue, _, {
    xpriority_queue(str) *fruits;
    enum x_stat status;
    
    status = xpriority_queue_new(str)(&fruits, cmp_str);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_true(xpriority_queue_is_empty(fruits));
    cester_assert_uint_eq(xpriority_queue_size(fruits), 0);

    status = xpriority_queue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status =xpriority_queue_enqueue(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_false(xpriority_queue_is_empty(fruits));
    cester_assert_uint_eq(xpriority_queue_size(fruits), 4);

    xpriority_queue_destroy(fruits);
})

CESTER_TEST(xpriority_queue_peek, _, {
    xpriority_queue(str) *fruits;
    enum x_stat status;
    char *value;

    status = xpriority_queue_new(str)(&fruits, cmp_str);
    cester_assert_uint_eq(status, XTD_OK);
    
    status = xpriority_queue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_peek(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xpriority_queue_size(fruits), 1);

    status = xpriority_queue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_peek(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xpriority_queue_size(fruits), 2);

    status =xpriority_queue_enqueue(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_peek(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xpriority_queue_size(fruits), 3);

    status = xpriority_queue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_peek(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xpriority_queue_size(fruits), 4);

    xpriority_queue_destroy(fruits);
})

CESTER_TEST(xpriority_queue_dequeue, _, {
    xpriority_queue(str) *fruits;
    enum x_stat status;
    char *value;

    status = xpriority_queue_new(str)(&fruits, cmp_str);
    cester_assert_uint_eq(status, XTD_OK);

    status = xpriority_queue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status =xpriority_queue_enqueue(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);

    status = xpriority_queue_dequeue(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xpriority_queue_size(fruits), 3);

    status = xpriority_queue_dequeue(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xpriority_queue_size(fruits), 2);

    status = xpriority_queue_dequeue(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Coconut");
    cester_assert_uint_eq(xpriority_queue_size(fruits), 1);

    status = xpriority_queue_dequeue(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xpriority_queue_size(fruits), 0);

    xpriority_queue_destroy(fruits);
})

CESTER_TEST(xpriority_queue_dequeue_underflow, _, {
    xpriority_queue(str) *fruits;
    enum x_stat status;
    char *value;

    status = xpriority_queue_new(str)(&fruits, cmp_str);
    cester_assert_uint_eq(status, XTD_OK);

    status = xpriority_queue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status =xpriority_queue_enqueue(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);

    status = xpriority_queue_dequeue(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xpriority_queue_size(fruits), 3);

    status = xpriority_queue_dequeue(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Mango");
    cester_assert_uint_eq(xpriority_queue_size(fruits), 2);

    status = xpriority_queue_dequeue(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Coconut");
    cester_assert_uint_eq(xpriority_queue_size(fruits), 1);

    status = xpriority_queue_dequeue(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_equal(value, "Banana");
    cester_assert_uint_eq(xpriority_queue_size(fruits), 0);

    status = xpriority_queue_dequeue(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_EMPTY_CONTAINER_ERR);

    status = xpriority_queue_dequeue(str)(fruits, &value);
    cester_assert_uint_eq(status, XTD_EMPTY_CONTAINER_ERR);

    xpriority_queue_destroy(fruits);
})

CESTER_TEST(xpriority_queue_priority_greater_than, _, {
    xpriority_queue(int) *numbers;
    enum x_stat status;
    int value;

    status = xpriority_queue_new(int)(&numbers, cmp_int_gt);
    cester_assert_uint_eq(status, XTD_OK);

    status = xpriority_queue_enqueue(int)(numbers, 3);
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(int)(numbers, 4);
    cester_assert_uint_eq(status, XTD_OK);
    status =xpriority_queue_enqueue(int)(numbers, 9);
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(int)(numbers, 5);
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(int)(numbers, 2);
    cester_assert_uint_eq(status, XTD_OK);

    status = xpriority_queue_dequeue(int)(numbers, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(value, 9);
    cester_assert_uint_eq(xpriority_queue_size(numbers), 4);

    status = xpriority_queue_dequeue(int)(numbers, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(value, 2);
    cester_assert_uint_eq(xpriority_queue_size(numbers), 3);

    status = xpriority_queue_dequeue(int)(numbers, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(value, 3);
    cester_assert_uint_eq(xpriority_queue_size(numbers), 2);

    status = xpriority_queue_dequeue(int)(numbers, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(value, 4);
    cester_assert_uint_eq(xpriority_queue_size(numbers), 1);

    status = xpriority_queue_dequeue(int)(numbers, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(value, 5);
    cester_assert_uint_eq(xpriority_queue_size(numbers), 0);

    xpriority_queue_destroy(numbers);
})

CESTER_TEST(xpriority_queue_priority_lesser_than, _, {
    xpriority_queue(int) *numbers;
    enum x_stat status;
    int value;

    status = xpriority_queue_new(int)(&numbers, cmp_int_lt);
    cester_assert_uint_eq(status, XTD_OK);

    status = xpriority_queue_enqueue(int)(numbers, 3);
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(int)(numbers, 4);
    cester_assert_uint_eq(status, XTD_OK);
    status =xpriority_queue_enqueue(int)(numbers, 9);
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(int)(numbers, 5);
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(int)(numbers, 2);
    cester_assert_uint_eq(status, XTD_OK);

    status = xpriority_queue_dequeue(int)(numbers, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(value, 2);
    cester_assert_uint_eq(xpriority_queue_size(numbers), 4);

    status = xpriority_queue_dequeue(int)(numbers, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(value, 4);
    cester_assert_uint_eq(xpriority_queue_size(numbers), 3);

    status = xpriority_queue_dequeue(int)(numbers, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(value, 5);
    cester_assert_uint_eq(xpriority_queue_size(numbers), 2);

    status = xpriority_queue_dequeue(int)(numbers, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(value, 9);
    cester_assert_uint_eq(xpriority_queue_size(numbers), 1);

    status = xpriority_queue_dequeue(int)(numbers, &value);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(value, 3);
    cester_assert_uint_eq(xpriority_queue_size(numbers), 0);

    xpriority_queue_destroy(numbers);
})

CESTER_TEST(xpriority_queue_capacity, _, {
    xpriority_queue(str) *fruits;
    enum x_stat status;

    status = xpriority_queue_new(str)(&fruits, cmp_str);
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    
    cester_assert_false(xpriority_queue_is_empty(fruits));
    cester_assert_uint_eq(xpriority_queue_size(fruits), 4);
    cester_assert_uint_eq(xpriority_queue_capacity(fruits), XDEFAULT_CONTAINER_CAPACITY);
    cester_assert_equal(xpriority_queue_max_size(fruits), XTD_CONTAINER_MAX_CAPACITY);

    xpriority_queue_destroy(fruits);
})

CESTER_TEST(xpriority_queue_max_size_1, _, {
    xpriority_queue(str) *fruits;
    enum x_stat status;

    status = xpriority_queue_new_max_size(str)(&fruits, 3, cmp_str);
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_MAX_SIZE_ERR);
    status = xpriority_queue_enqueue(str)(fruits, "Watermelon");
    cester_assert_uint_eq(status, XTD_MAX_SIZE_ERR);
    
    cester_assert_false(xpriority_queue_is_empty(fruits));
    cester_assert_uint_eq(xpriority_queue_size(fruits), 3);
    cester_assert_uint_eq(xpriority_queue_capacity(fruits), 3);
    cester_assert_llong_eq(xpriority_queue_max_size(fruits), 3);

    xpriority_queue_destroy(fruits);
})

CESTER_TEST(xpriority_queue_max_size_2, _, {
    xpriority_queue(str) *fruits;
    enum x_stat status;
    int max_size = 6;

    status = xpriority_queue_new_max_size(str)(&fruits, max_size, cmp_str);
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Carrot");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Coconut");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Watermelon");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_MAX_SIZE_ERR);
    status = xpriority_queue_enqueue(str)(fruits, "Avocado");
    cester_assert_uint_eq(status, XTD_MAX_SIZE_ERR);
    
    cester_assert_false(xpriority_queue_is_empty(fruits));
    cester_assert_uint_eq(xpriority_queue_size(fruits), max_size);
    cester_assert_uint_eq(xpriority_queue_capacity(fruits), (XDEFAULT_CONTAINER_CAPACITY * XDEFAULT_CONTAINER_EXPANSION_RATE));
    cester_assert_llong_eq(xpriority_queue_max_size(fruits), max_size);

    xpriority_queue_destroy(fruits);
})

CESTER_TEST(xpriority_queue_swap, _, {
    xpriority_queue(str) *fruits;
    xpriority_queue(str) *foods;
    enum x_stat status;
    char *value;

    status = xpriority_queue_new(str)(&fruits, cmp_str);
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);

    status = xpriority_queue_new(str)(&foods, cmp_str);
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(foods, "Amala");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(foods, "Iyan");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(foods, "Fufu");
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_uint_eq(xpriority_queue_peek(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xpriority_queue_peek(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Amala");

    xswap(xpriority_queue_str)(foods, fruits);

    cester_assert_uint_eq(xpriority_queue_peek(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Amala");
    cester_assert_uint_eq(xpriority_queue_peek(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");

    xpriority_queue_destroy(fruits);
})

CESTER_TEST(xpriority_queue_swap_buffer, _, {
    xpriority_queue(str) *fruits;
    xpriority_queue(str) *foods;
    enum x_stat status;
    char *value;

    status = xpriority_queue_new(str)(&fruits, cmp_str);
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);

    status = xpriority_queue_new(str)(&foods, cmp_str);
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(foods, "Amala");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(foods, "Iyan");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(foods, "Fufu");
    cester_assert_uint_eq(status, XTD_OK);

    cester_assert_uint_eq(xpriority_queue_peek(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");
    cester_assert_uint_eq(xpriority_queue_peek(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Amala");

    xswap(char_array)(&xget_buffer(foods), &xget_buffer(fruits));

    cester_assert_uint_eq(xpriority_queue_peek(str)(fruits, &value), XTD_OK);
    cester_assert_str_equal(value, "Amala");
    cester_assert_uint_eq(xpriority_queue_peek(str)(foods, &value), XTD_OK);
    cester_assert_str_equal(value, "Apple");

    xpriority_queue_destroy(fruits);
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)

