/*!gcc  -ansi -pedantic-errors {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/container/xpriority_queue.h>
#include <exotic/xtd/xiterator.h>

CESTER_BODY(
    typedef char* str;
    SETUP_XPRIORITY_QUEUE_FOR(str)

    bool cmp_str(char * const a, char * const b) {
        return *a < *b;
    }
)

CESTER_TEST(xpriority_queue_iterator, _, {
    xpriority_queue(str) *fruits;
    enum x_stat status;
    XIterator *iterator;

    status = xpriority_queue_new(str)(&fruits, cmp_str);
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_INIT(xpriority_queue, str, fruits);
    while (XITERATOR_HAS_NEXT(iterator)) {
        cester_assert_str_not_equal(XITERATOR_NEXT(iterator), NULL);
    }
    XITERATOR_RESET(iterator);
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_NEXT(iterator), "Apple");
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_NEXT(iterator), "Banana");
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_NEXT(iterator), "Mango");
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_NEXT(iterator), "Pineapple");

    XITERATOR_DESTROY(iterator);
    xpriority_queue_destroy(fruits);
})

CESTER_TEST(xpriority_queue_iterator_reverse, _, {
    xpriority_queue(str) *fruits;
    enum x_stat status;
    XIterator *iterator;

    status = xpriority_queue_new(str)(&fruits, cmp_str);
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_INIT(xpriority_queue, str, fruits);
    while (XITERATOR_HAS_PREV(iterator)) {
        cester_assert_str_not_equal(XITERATOR_PREV(iterator), NULL);
    }
    XITERATOR_RESET(iterator);
    cester_assert_uint_eq(XITERATOR_HAS_PREV(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_PREV(iterator), "Pineapple");
    cester_assert_uint_eq(XITERATOR_HAS_PREV(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_PREV(iterator), "Mango");
    cester_assert_uint_eq(XITERATOR_HAS_PREV(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_PREV(iterator), "Banana");
    cester_assert_uint_eq(XITERATOR_HAS_PREV(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_PREV(iterator), "Apple");

    XITERATOR_DESTROY(iterator);
    xpriority_queue_destroy(fruits);
})

CESTER_TEST(xpriority_queue_foreach, _, {
    xpriority_queue(str) *fruits;
    enum x_stat status;
    XIterator *iterator;

    status = xpriority_queue_new(str)(&fruits, cmp_str);
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_INIT(xpriority_queue, str, fruits);
    XFOREACH(const char *fruit, iterator, {
        cester_assert_str_not_equal(fruit, NULL);
    });

    XITERATOR_DESTROY(iterator);
    xpriority_queue_destroy(fruits);
})

CESTER_TEST(xpriority_queue_foreach_reverse, _, {
    xpriority_queue(str) *fruits;
    enum x_stat status;
    XIterator *iterator;

    status = xpriority_queue_new(str)(&fruits, cmp_str);
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_INIT(xpriority_queue, str, fruits);
    XFOREACH_REVERSE(const char *fruit, iterator, {
        cester_assert_str_not_equal(fruit, NULL);
    });

    XITERATOR_DESTROY(iterator);
    xpriority_queue_destroy(fruits);
})

CESTER_TEST(xpriority_queue_foreach_with_index, _, {
    xpriority_queue(str) *fruits;
    enum x_stat status;
    XIterator *iterator;

    status = xpriority_queue_new(str)(&fruits, cmp_str);
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_INIT(xpriority_queue, str, fruits);
    XFOREACH_INDEX(size_t index, const char *fruit, iterator, {
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

    XITERATOR_DESTROY(iterator);
    xpriority_queue_destroy(fruits);
})

CESTER_TEST(xpriority_queue_foreach_reverse_with_index, _, {
    xpriority_queue(str) *fruits;
    enum x_stat status;
    XIterator *iterator;

    status = xpriority_queue_new(str)(&fruits, cmp_str);
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_INIT(xpriority_queue, str, fruits);
    XFOREACH_REVERSE_INDEX(size_t index, const char *fruit, iterator, {
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

    XITERATOR_DESTROY(iterator);
    xpriority_queue_destroy(fruits);
})

CESTER_TEST(xpriority_queue_modify_in_loop, _, {
    xpriority_queue(str) *fruits;
    enum x_stat status;
    XIterator *iterator;

    status = xpriority_queue_new(str)(&fruits, cmp_str);
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_INIT(xpriority_queue, str, fruits);
    XFOREACH_INDEX(size_t index, const char *fruit, iterator, {
        if (xpriority_queue_size(fruits) > 2) {
            status = xpriority_queue_dequeue(str)(fruits, NULL);
            cester_assert_uint_eq(status, XTD_OK);
        }
        cester_assert_str_not_equal(fruit, "Mango");
        cester_assert_str_not_equal(fruit, "Pineapple");
    });

    XITERATOR_DESTROY(iterator);
    xpriority_queue_destroy(fruits);
})

CESTER_TEST(xpriority_queue_iterator_advance_by, _, {
    xpriority_queue(str) *fruits;
    enum x_stat status;
    XIterator *iterator;

    status = xpriority_queue_new(str)(&fruits, cmp_str);
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_INIT(xpriority_queue, str, fruits);
    XITERATOR_ADVANCE_BY(iterator, 2);
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_NEXT(iterator), "Mango");
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_NEXT(iterator), "Pineapple");
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), FALSE);

    XITERATOR_DESTROY(iterator);
    xpriority_queue_destroy(fruits);
})

CESTER_TEST(xpriority_queue_iterator_increment_decrement, _, {
    xpriority_queue(str) *fruits;
    enum x_stat status;
    XIterator *iterator;

    status = xpriority_queue_new(str)(&fruits, cmp_str);
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_INIT(xpriority_queue, str, fruits);
    XITERATOR_INCREMENT(iterator);
    XITERATOR_INCREMENT(iterator);
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_NEXT(iterator), "Mango");
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_NEXT(iterator), "Pineapple");
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), FALSE);
    XITERATOR_DECREMENT(iterator);
    XITERATOR_DECREMENT(iterator);
    XITERATOR_DECREMENT(iterator);
    XITERATOR_DECREMENT(iterator);
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_NEXT(iterator), "Apple");
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_NEXT(iterator), "Banana");

    XITERATOR_DESTROY(iterator);
    xpriority_queue_destroy(fruits);
})

CESTER_TEST(xpriority_queue_iterator_segfault, _, {
    xpriority_queue(str) *fruits;
    enum x_stat status;
    XIterator *iterator;

    status = xpriority_queue_new(str)(&fruits, cmp_str);
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_INIT(xpriority_queue, str, fruits);
    XITERATOR_ADVANCE_BY(iterator, 30);
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_NEXT(iterator), "Mango");
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_NEXT(iterator), "Pineapple");
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), FALSE);

    XITERATOR_DESTROY(iterator);
    xpriority_queue_destroy(fruits);
})

CESTER_TEST(xpriority_queue_iterator_forward_and_backward, _, {
    xpriority_queue(str) *fruits;
    enum x_stat status;
    XIterator *forward_iterator;
    XIterator *backward_iterator;
    size_t index;

    status = xpriority_queue_new(str)(&fruits, cmp_str);
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xpriority_queue_enqueue(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    index = 0;
    forward_iterator = XITERATOR_INIT(xpriority_queue, str, fruits);
    backward_iterator = XITERATOR_INIT(xpriority_queue, str, fruits);
    while (XITERATOR_HAS_NEXT(forward_iterator) && XITERATOR_HAS_PREV(backward_iterator)) {
        const char *forward_value = XITERATOR_NEXT(forward_iterator);
        const char *backward_value = XITERATOR_PREV(backward_iterator);
        cester_assert_str_not_equal(forward_value, backward_value);
        if (index == 0) {
            cester_assert_str_equal(forward_value, "Apple");
            cester_assert_str_equal(backward_value, "Pineapple");

        } else if (index == 1) {
            cester_assert_str_equal(forward_value, "Banana");
            cester_assert_str_equal(backward_value, "Mango");

        } else if (index == 2) {
            cester_assert_str_equal(forward_value, "Mango");
            cester_assert_str_equal(backward_value, "Banana");
            
        } else if (index == 3) {
            cester_assert_str_equal(forward_value, "Pineapple");
            cester_assert_str_equal(backward_value, "Apple");
            
        }
        index++;
    }

    XITERATOR_DESTROY(forward_iterator);
    XITERATOR_DESTROY(backward_iterator);
    xpriority_queue_destroy(fruits);
})

CESTER_OPTIONS(
    CESTER_TEST_SHOULD_FAIL(xpriority_queue_iterator_segfault);
    CESTER_VERBOSE_LEVEL(2);
)
