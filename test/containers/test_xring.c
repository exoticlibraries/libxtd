/*!gcc {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */
/*!clang++ {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out.exe; ./out.exe */
/*!clang -ansi -pedantic-errors {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out.exe; ./out.exe */
/*!clang {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out.exe; ./out.exe */
/*!g++ -std=c++11 {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */
/*!gcc  -ansi -pedantic-errors {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/xiterator.h>
#include <exotic/xtd/xalgorithm.h>
#include <exotic/xtd/xring.h>

CESTER_BODY(
    typedef char* str;
    SETUP_XRING_FOR(str)
    SETUP_XRING_ONLY_FOR(int)
    typedef char** char_array;
    SETUP_XALGORITHM_SWAP_FOR(char_array)
    SETUP_XALGORITHM_SWAP_FOR(xcircular_buffer_str)

void on_ring_element_cb_int(int element) {
    cester_assert_uint_lt(element, 11);
}

void on_ring_element_cb_str(str element) {
    cester_assert_str_ne(element, XTD_NULL);
}

)

CESTER_TEST(xring_init, _, {
    xring(str) *fruits;
    enum x_stat status;

    status = xring_new(str)(&fruits, 5);
    cester_assert_uint_eq(status, XTD_OK);

    xring_destroy(fruits);
})

CESTER_TEST(xring_conf_init, _, {
    struct xcontainer_config config;
    xring(str) *fruits;
    enum x_stat status;

    config.allocator.memory_malloc   = malloc;
    config.allocator.memory_calloc  = calloc;
    config.allocator.memory_free    = free;
    config.expansion_rate = 5;
    config.capacity       = 5;
    config.max_size       = 5000;
    status = xring_new_config(str)(&config, &fruits);
    cester_assert_uint_eq(status, XTD_OK);

    xring_destroy(fruits);
})

CESTER_TEST(xring_add_int, _, {
    xring(int) *numbers;
    enum x_stat status;
    int index = 1;
    int limit = 20;

    status = xring_new(int)(&numbers, 10);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xring_size(numbers), 0);

    for (; index <= limit; ++index) {
        status = xring_add(int)(numbers, index);
        if (index <= 10) {
            cester_assert_uint_eq(status, XTD_OK);
        } else {
            cester_assert_uint_eq(status, XTD_MAX_CAPACITY_ERR);
        }
    }
    cester_assert_uint_eq(xring_size(numbers), 10);
    cester_assert_uint_eq(xget_at(numbers, 0), 1);
    cester_assert_uint_eq(xget_at(numbers, 1), 2);
    cester_assert_uint_eq(xget_at(numbers, 2), 3);
    cester_assert_uint_eq(xget_at(numbers, 8), 9);
    cester_assert_uint_eq(xget_at(numbers, 9), 10);

    xring_destroy(numbers);
})

CESTER_TEST(xring_enqueue_int, _, {
    xring(int) *numbers;
    enum x_stat status;
    int index = 1;
    int limit = 20;

    status = xring_new(int)(&numbers, 10);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xring_size(numbers), 0);

    for (; index <= limit; ++index) {
        status = xring_enqueue(int)(numbers, index);
        cester_assert_uint_eq(status, XTD_OK);
    }
    cester_assert_uint_eq(xring_size(numbers), 10);
    cester_assert_uint_eq(xget_at(numbers, 0), 11);
    cester_assert_uint_eq(xget_at(numbers, 1), 12);
    cester_assert_uint_eq(xget_at(numbers, 2), 13);
    cester_assert_uint_eq(xget_at(numbers, 8), 19);
    cester_assert_uint_eq(xget_at(numbers, 9), 20);

    xring_destroy(numbers);
})

CESTER_TEST(xring_enqueue_cb_int, _, {
    xring(int) *numbers;
    enum x_stat status;
    int index = 1;
    int limit = 20;

    status = xring_new(int)(&numbers, 10);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xring_size(numbers), 0);

    for (; index <= 10; ++index) {
        status = xring_enqueue_cb(int)(numbers, index, on_ring_element_cb_int);
        cester_assert_uint_eq(status, XTD_OK);
    }
    cester_assert_uint_eq(xring_size(numbers), 10);
    cester_assert_uint_eq(xget_at(numbers, 0), 1);
    cester_assert_uint_eq(xget_at(numbers, 1), 2);
    cester_assert_uint_eq(xget_at(numbers, 2), 3);
    cester_assert_uint_eq(xget_at(numbers, 8), 9);
    cester_assert_uint_eq(xget_at(numbers, 9), 10);

    for (; index <= limit; ++index) {
        status = xring_enqueue_cb(int)(numbers, index, on_ring_element_cb_int);
        cester_assert_uint_eq(status, XTD_OK);
    }
    cester_assert_uint_eq(xring_size(numbers), 10);
    cester_assert_uint_eq(xget_at(numbers, 0), 11);
    cester_assert_uint_eq(xget_at(numbers, 1), 12);
    cester_assert_uint_eq(xget_at(numbers, 2), 13);
    cester_assert_uint_eq(xget_at(numbers, 8), 19);
    cester_assert_uint_eq(xget_at(numbers, 9), 20);

    xring_destroy(numbers);
})

CESTER_TEST(xring_add_str, _, {
    xring(str) *fruits;
    enum x_stat status;

    status = xring_new(str)(&fruits, 5);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xring_size(fruits), 0);

    cester_assert_uint_eq(xring_add(str)(fruits, "Apple"), XTD_OK);
    cester_assert_uint_eq(xring_add(str)(fruits, "Banana"), XTD_OK);
    cester_assert_uint_eq(xring_add(str)(fruits, "Orange"), XTD_OK);
    cester_assert_uint_eq(xring_add(str)(fruits, "Coconut"), XTD_OK);
    cester_assert_uint_eq(xring_add(str)(fruits, "Mango"), XTD_OK);
    cester_assert_uint_eq(xring_add(str)(fruits, "Onion"), XTD_MAX_CAPACITY_ERR);
    cester_assert_uint_eq(xring_add(str)(fruits, "Carrot"), XTD_MAX_CAPACITY_ERR);
    cester_assert_uint_eq(xring_add(str)(fruits, "Potato"), XTD_MAX_CAPACITY_ERR);
    
    cester_assert_uint_eq(xring_size(fruits), 5);
    cester_assert_str_eq(xget_at(fruits, 0), "Apple");
    cester_assert_str_eq(xget_at(fruits, 1), "Banana");
    cester_assert_str_eq(xget_at(fruits, 2), "Orange");
    cester_assert_str_eq(xget_at(fruits, 3), "Coconut");
    cester_assert_str_eq(xget_at(fruits, 4), "Mango");

    xring_destroy(fruits);
})

CESTER_TEST(xring_enqueue_str, _, {
    xring(str) *fruits;
    enum x_stat status;

    status = xring_new(str)(&fruits, 5);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xring_size(fruits), 0);

    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Apple"), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Banana"), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Orange"), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Coconut"), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Mango"), XTD_OK);

    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Onion"), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Carrot"), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Potato"), XTD_OK);

    cester_assert_uint_eq(xring_size(fruits), 5);
    cester_assert_str_eq(xget_at(fruits, 0), "Onion");
    cester_assert_str_eq(xget_at(fruits, 1), "Carrot");
    cester_assert_str_eq(xget_at(fruits, 2), "Potato");
    cester_assert_str_eq(xget_at(fruits, 3), "Coconut");
    cester_assert_str_eq(xget_at(fruits, 4), "Mango");

    xring_destroy(fruits);
})

CESTER_TEST(xring_enqueue_cb_str, _, {
    xring(str) *fruits;
    enum x_stat status;

    status = xring_new(str)(&fruits, 5);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xring_size(fruits), 0);

    cester_assert_uint_eq(xring_enqueue_cb(str)(fruits, "Apple", on_ring_element_cb_str), XTD_OK);
    cester_assert_uint_eq(xring_enqueue_cb(str)(fruits, "Banana", on_ring_element_cb_str), XTD_OK);
    cester_assert_uint_eq(xring_enqueue_cb(str)(fruits, "Orange", on_ring_element_cb_str), XTD_OK);
    cester_assert_uint_eq(xring_enqueue_cb(str)(fruits, "Coconut", on_ring_element_cb_str), XTD_OK);
    cester_assert_uint_eq(xring_enqueue_cb(str)(fruits, "Mango", on_ring_element_cb_str), XTD_OK);

    cester_assert_uint_eq(xring_enqueue_cb(str)(fruits, "Onion", on_ring_element_cb_str), XTD_OK);
    cester_assert_uint_eq(xring_enqueue_cb(str)(fruits, "Carrot", on_ring_element_cb_str), XTD_OK);
    cester_assert_uint_eq(xring_enqueue_cb(str)(fruits, "Potato", on_ring_element_cb_str), XTD_OK);

    cester_assert_uint_eq(xring_size(fruits), 5);
    cester_assert_str_eq(xget_at(fruits, 0), "Onion");
    cester_assert_str_eq(xget_at(fruits, 1), "Carrot");
    cester_assert_str_eq(xget_at(fruits, 2), "Potato");
    cester_assert_str_eq(xget_at(fruits, 3), "Coconut");
    cester_assert_str_eq(xget_at(fruits, 4), "Mango");
})

CESTER_TEST(xring_is_empty_and_is_full, _, {
    xring(str) *fruits;
    enum x_stat status;

    status = xring_new(str)(&fruits, 5);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xring_size(fruits), 0);

    cester_assert_true(xring_enqueue_is_empty(fruits));
    cester_assert_uint_eq(xring_add(str)(fruits, "Apple"), XTD_OK);
    cester_assert_false(xring_enqueue_is_full(fruits));
    cester_assert_uint_eq(xring_add(str)(fruits, "Banana"), XTD_OK);
    cester_assert_false(xring_enqueue_is_full(fruits));
    cester_assert_uint_eq(xring_add(str)(fruits, "Orange"), XTD_OK);
    cester_assert_false(xring_enqueue_is_full(fruits));
    cester_assert_uint_eq(xring_add(str)(fruits, "Coconut"), XTD_OK);
    cester_assert_false(xring_enqueue_is_full(fruits));
    cester_assert_uint_eq(xring_add(str)(fruits, "Mango"), XTD_OK);
    cester_assert_true(xring_enqueue_is_full(fruits));
    cester_assert_uint_eq(xring_size(fruits), 5);

    xring_destroy(fruits);
})

CESTER_TEST(xring_get_at_and_get_int, _, {
    xring(int) *numbers;
    enum x_stat status;
    int index = 1;
    int limit = 10;
    int value;

    status = xring_new(int)(&numbers, 10);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xring_size(numbers), 0);

    for (; index <= limit; ++index) {
        status = xring_add(int)(numbers, index);
        cester_assert_uint_eq(status, XTD_OK);
    }

    cester_assert_uint_eq(xring_get_at(int)(numbers, 0, &value), XTD_OK); cester_assert_uint_eq(value, 1);
    cester_assert_uint_eq(xring_get_at(int)(numbers, 1, &value), XTD_OK); cester_assert_uint_eq(value, 2);
    cester_assert_uint_eq(xring_get_at(int)(numbers, 2, &value), XTD_OK); cester_assert_uint_eq(value, 3);
    cester_assert_uint_eq(xring_get_at(int)(numbers, 3, &value), XTD_OK); cester_assert_uint_eq(value, 4);
    cester_assert_uint_eq(xring_get_at(int)(numbers, 4, &value), XTD_OK); cester_assert_uint_eq(value, 5);
    cester_assert_uint_eq(xring_get_at(int)(numbers, 5, &value), XTD_OK); cester_assert_uint_eq(value, 6);
    cester_assert_uint_eq(xring_get_at(int)(numbers, 6, &value), XTD_OK); cester_assert_uint_eq(value, 7);
    cester_assert_uint_eq(xring_get_at(int)(numbers, 7, &value), XTD_OK); cester_assert_uint_eq(value, 8);
    cester_assert_uint_eq(xring_get_at(int)(numbers, 8, &value), XTD_OK); cester_assert_uint_eq(value, 9);
    cester_assert_uint_eq(xring_get_at(int)(numbers, 9, &value), XTD_OK); cester_assert_uint_eq(value, 10);
    cester_assert_uint_eq(xring_get(int)(numbers, &value), XTD_OK); cester_assert_uint_eq(value, 1);
    cester_assert_uint_eq(xring_get(int)(numbers, &value), XTD_OK); cester_assert_uint_eq(value, 1);
    cester_assert_uint_eq(xring_get_at(int)(numbers, 10, &value), XTD_INDEX_OUT_OF_RANGE_ERR);
    cester_assert_uint_eq(xring_get_at(int)(numbers, 10, XTD_NULL), XTD_OUT_PARAM_NULL_ERR);

    xring_destroy(numbers);
})

CESTER_TEST(xring_get_at_and_get_str, _, {
    xring(str) *fruits;
    enum x_stat status;
    str value;

    status = xring_new(str)(&fruits, 5);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xring_size(fruits), 0);

    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Apple"), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Banana"), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Orange"), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Coconut"), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Mango"), XTD_OK);

    cester_assert_uint_eq(xring_get_at(str)(fruits, 0, &value), XTD_OK); cester_assert_str_eq(value, "Apple");
    cester_assert_uint_eq(xring_get_at(str)(fruits, 1, &value), XTD_OK); cester_assert_str_eq(value, "Banana");
    cester_assert_uint_eq(xring_get_at(str)(fruits, 2, &value), XTD_OK); cester_assert_str_eq(value, "Orange");
    cester_assert_uint_eq(xring_get_at(str)(fruits, 3, &value), XTD_OK); cester_assert_str_eq(value, "Coconut");
    cester_assert_uint_eq(xring_get_at(str)(fruits, 4, &value), XTD_OK); cester_assert_str_eq(value, "Mango");
    cester_assert_uint_eq(xring_get(str)(fruits, &value), XTD_OK); cester_assert_str_eq(value, "Apple");
    cester_assert_uint_eq(xring_get(str)(fruits, &value), XTD_OK); cester_assert_str_eq(value, "Apple");
    cester_assert_uint_eq(xring_get_at(str)(fruits, 5, &value), XTD_INDEX_OUT_OF_RANGE_ERR);
    cester_assert_uint_eq(xring_get_at(str)(fruits, 6, XTD_NULL), XTD_OUT_PARAM_NULL_ERR);

    xring_destroy(fruits);
})

CESTER_TEST(xring_dequeue_at_int, _, {
    xring(int) *numbers;
    enum x_stat status;
    int index = 1;
    int limit = 5;
    int value;

    status = xring_new(int)(&numbers, 10);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xring_size(numbers), 0);

    for (; index <= limit; ++index) {
        status = xring_add(int)(numbers, index);
        cester_assert_uint_eq(status, XTD_OK);
    }

    cester_assert_uint_eq(xring_dequeue_at(int)(numbers, 4, &value), XTD_OK);
    cester_assert_uint_eq(value, 5); cester_assert_uint_eq(xring_size(numbers), 4);
    cester_assert_uint_eq(xring_dequeue_at(int)(numbers, 1, &value), XTD_OK);
    cester_assert_uint_eq(value, 2); cester_assert_uint_eq(xring_size(numbers), 3);
    cester_assert_uint_eq(xring_dequeue_at(int)(numbers, 0, &value), XTD_OK);
    cester_assert_uint_eq(value, 1); cester_assert_uint_eq(xring_size(numbers), 2);
    cester_assert_uint_eq(xring_dequeue(int)(numbers, &value), XTD_OK);
    cester_assert_uint_eq(value, 3); cester_assert_uint_eq(xring_size(numbers), 1);
    cester_assert_uint_eq(xring_dequeue(int)(numbers, &value), XTD_OK);
    cester_assert_uint_eq(value, 4); cester_assert_uint_eq(xring_size(numbers), 0);
    cester_assert_true(xring_enqueue_is_empty(numbers));

    xring_destroy(numbers);
})

CESTER_TEST(xring_dequeue_at_str, _, {
    xring(str) *fruits;
    enum x_stat status;
    str value;

    status = xring_new(str)(&fruits, 5);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xring_size(fruits), 0);

    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Apple"), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Banana"), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Orange"), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Coconut"), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Mango"), XTD_OK);
    cester_assert_uint_eq(xring_size(fruits), 5);

    cester_assert_uint_eq(xring_dequeue_at(str)(fruits, 4, &value), XTD_OK);
    cester_assert_str_eq(value, "Mango"); cester_assert_uint_eq(xring_size(fruits), 4);
    cester_assert_uint_eq(xring_dequeue_at(str)(fruits, 1, &value), XTD_OK);
    cester_assert_str_eq(value, "Banana"); cester_assert_uint_eq(xring_size(fruits), 3);
    cester_assert_uint_eq(xring_dequeue_at(str)(fruits, 0, &value), XTD_OK);
    cester_assert_str_eq(value, "Apple"); cester_assert_uint_eq(xring_size(fruits), 2);
    cester_assert_uint_eq(xring_dequeue(str)(fruits, &value), XTD_OK);
    cester_assert_str_eq(value, "Orange"); cester_assert_uint_eq(xring_size(fruits), 1);
    cester_assert_uint_eq(xring_dequeue(str)(fruits, &value), XTD_OK);
    cester_assert_str_eq(value, "Coconut"); cester_assert_uint_eq(xring_size(fruits), 0);
    cester_assert_true(xring_enqueue_is_empty(fruits));

    xring_destroy(fruits);
})

CESTER_TEST(xring_dequeue_int, _, {
    xring(int) *numbers;
    int value;

    cester_assert_uint_eq(xring_new(int)(&numbers, 5), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(int)(numbers, 10), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(int)(numbers, 20), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(int)(numbers, 30), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(int)(numbers, 40), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(int)(numbers, 50), XTD_OK);

    cester_assert_uint_eq(xring_dequeue(int)(numbers, &value), XTD_OK);
    cester_assert_uint_eq(value, 10);
    cester_assert_uint_eq(xring_dequeue(int)(numbers, &value), XTD_OK);
    cester_assert_uint_eq(value, 20);

    cester_assert_uint_eq(xring_enqueue(int)(numbers, 100), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(int)(numbers, 200), XTD_OK);
    
    cester_assert_uint_eq(xring_dequeue(int)(numbers, &value), XTD_OK);
    cester_assert_uint_eq(value, 30);
    cester_assert_uint_eq(xring_dequeue(int)(numbers, &value), XTD_OK);
    cester_assert_uint_eq(value, 40);
    cester_assert_uint_eq(xring_dequeue(int)(numbers, &value), XTD_OK);
    cester_assert_uint_eq(value, 50);
    cester_assert_uint_eq(xring_dequeue(int)(numbers, &value), XTD_OK);
    cester_assert_uint_eq(value, 100);
    cester_assert_uint_eq(xring_dequeue(int)(numbers, &value), XTD_OK);
    cester_assert_uint_eq(value, 200);
    cester_assert_uint_eq(xring_dequeue(int)(numbers, &value), XTD_INDEX_OUT_OF_RANGE_ERR);

    xring_destroy(numbers);
})

CESTER_TEST(xring_dequeue_str, _, {
    xring(str) *fruits;
    str value;

    cester_assert_uint_eq(xring_new(str)(&fruits, 5), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Apple"), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Banana"), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Orange"), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Coconut"), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Mango"), XTD_OK);

    cester_assert_uint_eq(xring_dequeue(str)(fruits, &value), XTD_OK);
    cester_assert_str_eq(value, "Apple");
    cester_assert_uint_eq(xring_dequeue(str)(fruits, &value), XTD_OK);
    cester_assert_str_eq(value, "Banana");

    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Onion"), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Tomato"), XTD_OK);
    
    cester_assert_uint_eq(xring_dequeue(str)(fruits, &value), XTD_OK);
    cester_assert_str_eq(value, "Orange");
    cester_assert_uint_eq(xring_dequeue(str)(fruits, &value), XTD_OK);
    cester_assert_str_eq(value, "Coconut");
    cester_assert_uint_eq(xring_dequeue(str)(fruits, &value), XTD_OK);
    cester_assert_str_eq(value, "Mango");
    cester_assert_uint_eq(xring_dequeue(str)(fruits, &value), XTD_OK);
    cester_assert_str_eq(value, "Onion");
    cester_assert_uint_eq(xring_dequeue(str)(fruits, &value), XTD_OK);
    cester_assert_str_eq(value, "Tomato");
    cester_assert_uint_eq(xring_dequeue(str)(fruits, &value), XTD_INDEX_OUT_OF_RANGE_ERR);

    xring_destroy(fruits);
})

CESTER_TEST(xring_swap, _, {
    xring(str) *fruits;
    xring(str) *foods;
    enum x_stat status;
    str value;

    status = xring_new(str)(&fruits, 3);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Apple"), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Banana"), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Mango"), XTD_OK);
    cester_assert_uint_eq(xring_size(fruits), 3);

    status = xring_new(str)(&foods, 3);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(foods, "Amala"), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(foods, "Iyan"), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(foods, "Fufu"), XTD_OK);
    cester_assert_uint_eq(xring_size(foods), 3);

    cester_assert_uint_eq(xring_get_at(str)(fruits, 0, &value), XTD_OK); cester_assert_str_eq(value, "Apple");
    cester_assert_uint_eq(xring_get_at(str)(fruits, 1, &value), XTD_OK); cester_assert_str_eq(value, "Banana");
    cester_assert_uint_eq(xring_get_at(str)(fruits, 2, &value), XTD_OK); cester_assert_str_eq(value, "Mango");

    xswap(xcircular_buffer_str)(foods, fruits);

    cester_assert_uint_eq(xring_get_at(str)(fruits, 0, &value), XTD_OK); cester_assert_str_eq(value, "Amala");
    cester_assert_uint_eq(xring_get_at(str)(fruits, 1, &value), XTD_OK); cester_assert_str_eq(value, "Iyan");
    cester_assert_uint_eq(xring_get_at(str)(fruits, 2, &value), XTD_OK); cester_assert_str_eq(value, "Fufu");

    xring_destroy(foods);
    xring_destroy(fruits);
})

CESTER_TEST(xring_swap_buffer, _, {
    xring(str) *fruits;
    xring(str) *foods;
    enum x_stat status;
    str value;

    status = xring_new(str)(&fruits, 3);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Apple"), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Banana"), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(fruits, "Mango"), XTD_OK);
    cester_assert_uint_eq(xring_size(fruits), 3);

    status = xring_new(str)(&foods, 3);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(foods, "Amala"), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(foods, "Iyan"), XTD_OK);
    cester_assert_uint_eq(xring_enqueue(str)(foods, "Fufu"), XTD_OK);
    cester_assert_uint_eq(xring_size(foods), 3);

    cester_assert_uint_eq(xring_get_at(str)(fruits, 0, &value), XTD_OK); cester_assert_str_eq(value, "Apple");
    cester_assert_uint_eq(xring_get_at(str)(fruits, 1, &value), XTD_OK); cester_assert_str_eq(value, "Banana");
    cester_assert_uint_eq(xring_get_at(str)(fruits, 2, &value), XTD_OK); cester_assert_str_eq(value, "Mango");

    xswap(char_array)(&xget_buffer(foods), &xget_buffer(fruits));

    cester_assert_uint_eq(xring_get_at(str)(fruits, 0, &value), XTD_OK); cester_assert_str_eq(value, "Amala");
    cester_assert_uint_eq(xring_get_at(str)(fruits, 1, &value), XTD_OK); cester_assert_str_eq(value, "Iyan");
    cester_assert_uint_eq(xring_get_at(str)(fruits, 2, &value), XTD_OK); cester_assert_str_eq(value, "Fufu");

    xring_destroy(foods);
    xring_destroy(fruits);
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)



