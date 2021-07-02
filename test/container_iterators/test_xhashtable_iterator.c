/*!gcc  -ansi -pedantic-errors {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/xcrypto.h>
#include <exotic/xtd/xhashtable.h>
#include <exotic/xtd/xiterator.h>

CESTER_BODY(
    typedef char* str;
    SETUP_XHASHTABLE_FOR(str, int)
)

CESTER_TEST(xhashtable_iterator, _, {
    xhashtable_entry(str, int) *entry;
    xhashtable(str, int) *fruits_count;
    enum x_stat status;
    XIterator *iterator;

    status = xhashtable_new(str, int)(&fruits_count, cester_string_equals, xcrypto_hash_string);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Apple", 13);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Banana", 1);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Mango", 42);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Pineapple", 1009);
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_INIT2(xhashtable, str, int, fruits_count);
    while (XITERATOR_HAS_NEXT(iterator)) {
        entry = XITERATOR_NEXT(iterator);
        cester_assert_str_not_equal(entry->key, XTD_NULL);
    }

    XITERATOR_RESET(iterator);
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), TRUE);
    entry = XITERATOR_NEXT(iterator);
    cester_assert_str_equal(entry->key, "Apple");
    cester_assert_uint_eq(entry->value, 13);
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), TRUE);
    entry = XITERATOR_NEXT(iterator);
    cester_assert_str_equal(entry->key, "Banana");
    cester_assert_uint_eq(entry->value, 1);
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), TRUE);
    entry = XITERATOR_NEXT(iterator);
    cester_assert_str_equal(entry->key, "Pineapple");
    cester_assert_uint_eq(entry->value, 1009);
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), TRUE);
    entry = XITERATOR_NEXT(iterator); 
    cester_assert_str_equal(entry->key, "Mango");
    cester_assert_uint_eq(entry->value, 42);

    XITERATOR_DESTROY(iterator);
    xhashtable_destroy(str, int)(fruits_count);
})

CESTER_TEST(xhashtable_iterator_reverse, _, {
    xhashtable_entry(str, int) *entry;
    xhashtable(str, int) *fruits_count;
    enum x_stat status;
    XIterator *iterator;

    status = xhashtable_new(str, int)(&fruits_count, cester_string_equals, xcrypto_hash_string);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Apple", 13);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Banana", 1);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Mango", 42);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Pineapple", 1009);
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_INIT2(xhashtable, str, int, fruits_count);
    while (XITERATOR_HAS_PREV(iterator)) {
        entry = XITERATOR_PREV(iterator);
        cester_assert_str_not_equal(entry->key, XTD_NULL);
    }

    XITERATOR_RESET(iterator);
    cester_assert_uint_eq(XITERATOR_HAS_PREV(iterator), TRUE);
    entry = XITERATOR_PREV(iterator);
    cester_assert_str_equal(entry->key, "Pineapple");
    cester_assert_uint_eq(entry->value, 1009);
    cester_assert_uint_eq(XITERATOR_HAS_PREV(iterator), TRUE);
    entry = XITERATOR_PREV(iterator);
    cester_assert_str_equal(entry->key, "Mango");
    cester_assert_uint_eq(entry->value, 42);
    cester_assert_uint_eq(XITERATOR_HAS_PREV(iterator), TRUE);
    entry = XITERATOR_PREV(iterator);
    cester_assert_str_equal(entry->key, "Banana");
    cester_assert_uint_eq(entry->value, 1);
    cester_assert_uint_eq(XITERATOR_HAS_PREV(iterator), TRUE);
    entry = XITERATOR_PREV(iterator);
    cester_assert_str_equal(entry->key, "Apple");
    cester_assert_uint_eq(entry->value, 13);

    XITERATOR_DESTROY(iterator);
    xhashtable_destroy(str, int)(fruits_count);
})

CESTER_TEST(xhashtable_foreach, _, {
    xhashtable(str, int) *fruits_count;
    enum x_stat status;
    XIterator *iterator;

    status = xhashtable_new(str, int)(&fruits_count, cester_string_equals, xcrypto_hash_string);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Apple", 13);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Banana", 1);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Mango", 42);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Pineapple", 1009);
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_INIT2(xhashtable, str, int, fruits_count);
    XFOREACH(const xhashtable_entry(str, int) *entry, iterator, {
        cester_assert_str_not_equal(entry->key, XTD_NULL);
    });

    XITERATOR_DESTROY(iterator);
    xhashtable_destroy(str, int)(fruits_count);
})

CESTER_TEST(xhashtable_foreach_reverse, _, {
    xhashtable(str, int) *fruits_count;
    enum x_stat status;
    XIterator *iterator;

    status = xhashtable_new(str, int)(&fruits_count, cester_string_equals, xcrypto_hash_string);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Apple", 13);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Banana", 1);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Mango", 42);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Pineapple", 1009);
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_INIT2(xhashtable, str, int, fruits_count);
    XFOREACH_REVERSE(const xhashtable_entry(str, int) *entry, iterator, {
        cester_assert_str_not_equal(entry->key, XTD_NULL);
    });

    XITERATOR_DESTROY(iterator);
    xhashtable_destroy(str, int)(fruits_count);
})

CESTER_TEST(xhashtable_foreach_with_index, _, {
    xhashtable(str, int) *fruits_count;
    enum x_stat status;
    XIterator *iterator;

    status = xhashtable_new(str, int)(&fruits_count, cester_string_equals, xcrypto_hash_string);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Apple", 13);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Banana", 1);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Mango", 42);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Pineapple", 1009);
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_INIT2(xhashtable, str, int, fruits_count);
    XFOREACH_INDEX(size_t index, const xhashtable_entry(str, int) *entry, iterator, {
        if (index == 0) {
            cester_assert_str_equal(entry->key, "Apple");
        } else if (index == 1) {
            cester_assert_str_equal(entry->key, "Banana");
        } else if (index == 2) {
            cester_assert_str_equal(entry->key, "Pineapple");
        } else if (index == 3) {
            cester_assert_str_equal(entry->key, "Mango");
        }
    });

    XITERATOR_DESTROY(iterator);
    xhashtable_destroy(str, int)(fruits_count);
})

CESTER_TEST(xhashtable_foreach_reverse_with_index, _, {
    xhashtable(str, int) *fruits_count;
    enum x_stat status;
    XIterator *iterator;

    status = xhashtable_new(str, int)(&fruits_count, cester_string_equals, xcrypto_hash_string);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Apple", 13);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Banana", 1);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Mango", 42);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Pineapple", 1009);
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_INIT2(xhashtable, str, int, fruits_count);
    XFOREACH_REVERSE_INDEX(size_t index, const xhashtable_entry(str, int) *entry, iterator, {
        if (index == 3) {
            cester_assert_str_equal(entry->key, "Pineapple");
        } else if (index == 2) {
            cester_assert_str_equal(entry->key, "Mango");
        } else if (index == 1) {
            cester_assert_str_equal(entry->key, "Banana");
        } else if (index == 0) {
            cester_assert_str_equal(entry->key, "Apple");
        }
    });

    XITERATOR_DESTROY(iterator);
    xhashtable_destroy(str, int)(fruits_count);
})

CESTER_TODO_TEST(xhashtable_modify_in_loop, _, {
    xhashtable(str, int) *fruits_count;
    enum x_stat status;
    XIterator *iterator;

    status = xhashtable_new(str, int)(&fruits_count, cester_string_equals, xcrypto_hash_string);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Apple", 13);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Banana", 1);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Mango", 42);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Pineapple", 1009);
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_INIT2(xhashtable, str, int, fruits_count);
    XFOREACH_INDEX(size_t index, const xhashtable_entry(str, int) *entry, iterator, {
        if (xhashtable_size(fruits_count) == 0) {
            status = xhashtable_remove(str, int)(fruits_count, "Mango", XTD_NULL);
            cester_assert_uint_eq(status, XTD_OK);
        }
        if (xhashtable_size(fruits_count) > 2) {
            status = xhashtable_remove(str, int)(fruits_count, "Pineapple", XTD_NULL);
            cester_assert_uint_eq(status, XTD_OK);
        }
        cester_assert_str_not_equal(entry->key, "Mango");
        cester_assert_str_not_equal(entry->key, "Pineapple");
    });

    XITERATOR_DESTROY(iterator);
    xhashtable_destroy(str, int)(fruits_count);
})

CESTER_TEST(xhashtable_iterator_advance_by, _, {
    xhashtable_entry(str, int) *entry;
    xhashtable(str, int) *fruits_count;
    enum x_stat status;
    XIterator *iterator;

    status = xhashtable_new(str, int)(&fruits_count, cester_string_equals, xcrypto_hash_string);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Apple", 13);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Banana", 1);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Mango", 42);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Pineapple", 1009);
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_INIT2(xhashtable, str, int, fruits_count);
    XITERATOR_ADVANCE_BY(iterator, 2);
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), TRUE);
    entry = XITERATOR_NEXT(iterator);
    cester_assert_str_equal(entry->key, "Pineapple");
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), TRUE);
    entry = XITERATOR_NEXT(iterator);
    cester_assert_str_equal(entry->key, "Mango");
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), FALSE);

    XITERATOR_DESTROY(iterator);
    xhashtable_destroy(str, int)(fruits_count);
})

CESTER_TEST(xhashtable_iterator_increment_decrement, _, {
    xhashtable(str, int) *fruits_count;
    xhashtable_entry(str, int) *entry;
    enum x_stat status;
    XIterator *iterator;

    status = xhashtable_new(str, int)(&fruits_count, cester_string_equals, xcrypto_hash_string);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Apple", 13);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Banana", 1);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Mango", 42);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Pineapple", 1009);
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_INIT2(xhashtable, str, int, fruits_count);
    XITERATOR_INCREMENT(iterator);
    XITERATOR_INCREMENT(iterator);
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), TRUE);
    entry = XITERATOR_NEXT(iterator);
    cester_assert_str_equal(entry->key, "Pineapple");
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), TRUE);
    entry = XITERATOR_NEXT(iterator);
    cester_assert_str_equal(entry->key, "Mango");
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), FALSE);
    XITERATOR_DECREMENT(iterator);
    XITERATOR_DECREMENT(iterator);
    XITERATOR_DECREMENT(iterator);
    XITERATOR_DECREMENT(iterator);
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), TRUE);
    entry = XITERATOR_NEXT(iterator);
    cester_assert_str_equal(entry->key, "Apple");
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), TRUE);
    entry = XITERATOR_NEXT(iterator);
    cester_assert_str_equal(entry->key, "Banana");

    XITERATOR_DESTROY(iterator);
    xhashtable_destroy(str, int)(fruits_count);
})

CESTER_TEST(xhashtable_iterator_segfault, _, {
    xhashtable(str, int) *fruits_count;
    enum x_stat status;
    XIterator *iterator;

    status = xhashtable_new(str, int)(&fruits_count, cester_string_equals, xcrypto_hash_string);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Apple", 13);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Banana", 1);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Mango", 42);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Pineapple", 1009);
    cester_assert_uint_eq(status, XTD_OK);
    
    iterator = XITERATOR_INIT2(xhashtable, str, int, fruits_count);
    XITERATOR_ADVANCE_BY(iterator, 30);
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_NEXT(iterator), "Mango");
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), TRUE);
    cester_assert_str_equal(XITERATOR_NEXT(iterator), "Pineapple");
    cester_assert_uint_eq(XITERATOR_HAS_NEXT(iterator), FALSE);

    XITERATOR_DESTROY(iterator);
    xhashtable_destroy(str, int)(fruits_count);
})

CESTER_TEST(xhashtable_iterator_forward_and_backward, _, {
    xhashtable(str, int) *fruits_count;
    enum x_stat status;
    XIterator *forward_iterator;
    XIterator *backward_iterator;
    size_t index;

    status = xhashtable_new(str, int)(&fruits_count, cester_string_equals, xcrypto_hash_string);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Apple", 13);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Banana", 1);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Mango", 42);
    cester_assert_uint_eq(status, XTD_OK);
    status = xhashtable_put(str, int)(fruits_count, "Pineapple", 1009);
    cester_assert_uint_eq(status, XTD_OK);
    
    index = 0;
    forward_iterator = XITERATOR_INIT2(xhashtable, str, int, fruits_count);
    backward_iterator = XITERATOR_INIT2(xhashtable, str, int, fruits_count);
    while (XITERATOR_HAS_NEXT(forward_iterator) && XITERATOR_HAS_PREV(backward_iterator)) {
        const xhashtable_entry(str, int) *forward_entry = XITERATOR_NEXT(forward_iterator);
        const xhashtable_entry(str, int) *backward_entry = XITERATOR_PREV(backward_iterator);
        cester_assert_str_not_equal(forward_entry->key, backward_entry->key);
        if (index == 0) {
            cester_assert_str_equal(forward_entry->key, "Apple");
            cester_assert_str_equal(backward_entry->key, "Pineapple");

        } else if (index == 1) {
            cester_assert_str_equal(forward_entry->key, "Banana");
            cester_assert_str_equal(backward_entry->key, "Mango");

        } else if (index == 2) {
            cester_assert_str_equal(forward_entry->key, "Pineapple");
            cester_assert_str_equal(backward_entry->key, "Banana");
            
        } else if (index == 3) {
            cester_assert_str_equal(forward_entry->key, "Mango");
            cester_assert_str_equal(backward_entry->key, "Apple");
            
        }
        index++;
    }

    XITERATOR_DESTROY(forward_iterator);
    XITERATOR_DESTROY(backward_iterator);
    xhashtable_destroy(str, int)(fruits_count);
})

CESTER_OPTIONS(
    CESTER_TEST_SHOULD_FAIL(xhashtable_iterator_segfault);
    CESTER_VERBOSE_LEVEL(2);
)
