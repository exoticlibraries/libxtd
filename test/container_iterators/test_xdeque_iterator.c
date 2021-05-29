/*!clang -ansi -pedantic-errors {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/xdeque.h>
#include <exotic/xtd/xiterator.h>

CESTER_BODY(
    typedef char* str;
    SETUP_XDEQUE_FOR(str)
)

CESTER_TEST(xdeque_iterator, _, {
    xdeque(str) *fruits;
    enum x_stat status;
    XIterator *iterator;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_INIT(xdeque, str, fruits);
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
    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_iterator_reverse, _, {
    xdeque(str) *fruits;
    enum x_stat status;
    XIterator *iterator;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_INIT(xdeque, str, fruits);
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
    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_foreach, _, {
    xdeque(str) *fruits;
    enum x_stat status;
    XIterator *iterator;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_INIT(xdeque, str, fruits);
    XFOREACH(const char *fruit, iterator, {
        cester_assert_str_not_equal(fruit, NULL);
    });

    XITERATOR_DESTROY(iterator);
    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_foreach_reverse, _, {
    xdeque(str) *fruits;
    enum x_stat status;
    XIterator *iterator;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_INIT(xdeque, str, fruits);
    XFOREACH_REVERSE(const char *fruit, iterator, {
        cester_assert_str_not_equal(fruit, NULL);
    });

    XITERATOR_DESTROY(iterator);
    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_foreach_with_index, _, {
    xdeque(str) *fruits;
    enum x_stat status;
    XIterator *iterator;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);

    iterator = XITERATOR_INIT(xdeque, str, fruits);
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
    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_foreach_reverse_with_index, _, {
    xdeque(str) *fruits;
    enum x_stat status;
    XIterator *iterator;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_INIT(xdeque, str, fruits);
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
    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_modify_in_loop, _, {
    xdeque(str) *fruits;
    enum x_stat status;
    XIterator *iterator;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_INIT(xdeque, str, fruits);
    XFOREACH_INDEX(size_t index, const char *fruit, iterator, {
        if (xdeque_size(fruits) > 3) {
            status = xdeque_remove_at(str)(fruits, 3, NULL);
            cester_assert_uint_eq(status, XTD_OK);
        }
        if (xdeque_size(fruits) > 2) {
            status = xdeque_remove_at(str)(fruits, 1, NULL);
            cester_assert_uint_eq(status, XTD_OK);
        }
        cester_assert_str_not_equal(fruit, "Banana");
        cester_assert_str_not_equal(fruit, "Pineapple");
    });

    XITERATOR_DESTROY(iterator);
    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_iterator_advance_by, _, {
    xdeque(str) *fruits;
    enum x_stat status;
    XIterator *iterator;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_INIT(xdeque, str, fruits);
    XITERATOR_ADVANCE_BY(iterator, 2);
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_NEXT(iterator), "Mango");
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_NEXT(iterator), "Pineapple");
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), FALSE);

    XITERATOR_DESTROY(iterator);
    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_iterator_increment_decrement, _, {
    xdeque(str) *fruits;
    enum x_stat status;
    XIterator *iterator;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_INIT(xdeque, str, fruits);
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
    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_iterator_segfault, _, {
    xdeque(str) *fruits;
    enum x_stat status;
    XIterator *iterator;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_INIT(xdeque, str, fruits);
    XITERATOR_ADVANCE_BY(iterator, 30);
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_NEXT(iterator), "Mango");
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_NEXT(iterator), "Pineapple");
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), FALSE);

    XITERATOR_DESTROY(iterator);
    xdeque_destroy(fruits);
})

CESTER_TEST(xdeque_iterator_forward_and_backward, _, {
    xdeque(str) *fruits;
    enum x_stat status;
    XIterator *forward_iterator;
    XIterator *backward_iterator;
    size_t index;

    status = xdeque_new(str)(&fruits);
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Apple");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Banana");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Mango");
    cester_assert_uint_eq(status, XTD_OK);
    status = xdeque_add(str)(fruits, "Pineapple");
    cester_assert_uint_eq(status, XTD_OK);
    
    index = 0;
    forward_iterator = XITERATOR_INIT(xdeque, str, fruits);
    backward_iterator = XITERATOR_INIT(xdeque, str, fruits);
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
    xdeque_destroy(fruits);
})

CESTER_OPTIONS(
    CESTER_TEST_SHOULD_FAIL(xdeque_iterator_segfault);
    CESTER_VERBOSE_LEVEL(2);
)
