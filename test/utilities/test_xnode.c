/*!gcc -ansi -pedantic-errors {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../../include/ -I../../../libcester/include -I../include/ -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/xnode.h>
#include <exotic/xtd/xiterator.h>

CESTER_BODY(
    SETUP_XSINGLE_NODE_WITH_ITER_FOR(int)
    SETUP_XNODE_WITH_ITER_FOR(int)

    void free_all_nodes(xnode(int) *node)
    {
        xnode(int) *prev = xnode_get_prev(node);
        xnode(int) *next = xnode_get_next(node);
        if (prev != NULL) {
            free_all_nodes(prev);
        }
        if (next != NULL) {
            free_all_nodes(next);
        }
        free(node);
    }

    void free_all_nodes_compact(xnode(int) *node)
    {
        if (xnode_has_prev(node)) {
            free_all_nodes_compact(xnode_get_prev(node));
        }
        if (xnode_has_next(node)) {
            free_all_nodes_compact(xnode_get_next(node));
        }
        free(node);
    }
)

CESTER_BEFORE_ALL(test_inst, {
    xnode(int) *numbers = (xnode(int) *) calloc(1, sizeof(xnode(int)));
    xnode(int) *prev1 = (xnode(int) *) calloc(1, sizeof(xnode(int)));
    xnode(int) *next1 = (xnode(int) *) calloc(1, sizeof(xnode(int)));
    xnode(int) *prev2 = (xnode(int) *) calloc(1, sizeof(xnode(int)));
    xnode(int) *next2 = (xnode(int) *) calloc(1, sizeof(xnode(int)));
    xnode(int) *prev3 = (xnode(int) *) calloc(1, sizeof(xnode(int)));
    xnode(int) *next3 = (xnode(int) *) calloc(1, sizeof(xnode(int)));
    xnode(int) *prev4 = (xnode(int) *) calloc(1, sizeof(xnode(int)));
    xnode(int) *next4 = (xnode(int) *) calloc(1, sizeof(xnode(int)));
    
    xnode_set_data(prev1, 1);
    xnode_set_data(prev2, 2);
    xnode_set_data(prev3, 3);
    xnode_set_data(prev4, 4);
    xnode_set_data(numbers, 5);
    xnode_set_data(next1, 6);
    xnode_set_data(next2, 7);
    xnode_set_data(next3, 8);
    xnode_set_data(next4, 9);
        
    xnode_link_prev(prev2, prev1);
    xnode_link_prev(prev3, prev2);
    xnode_link_prev(prev4, prev3);
    xnode_link_prev(numbers, prev4);
    xnode_link_next(numbers, next1);
    xnode_link_next(next1, next2);
    xnode_link_next(next2, next3);
    xnode_link_next(next3, next4);

    test_inst->arg = numbers;
})

CESTER_TEST(xsingle_node_init, _, {
    xsingle_node(int) *numbers = (xsingle_node(int) *) malloc(1 * sizeof(xsingle_node(int)));

    free(numbers);
})

CESTER_TEST(xsingle_node_data, _, {
    xsingle_node(int) *numbers = (xsingle_node(int) *) malloc(1 * sizeof(xsingle_node(int)));
    numbers->data = 1;

    cester_assert_uint_eq(xnode_get_data(numbers), 1);
    xnode_set_data(numbers, 2);
    cester_assert_uint_eq(xnode_get_data(numbers), 2);

    free(numbers);
})

CESTER_TEST(xsingle_node_next, _, {
    xsingle_node(int) *numbers = (xsingle_node(int) *) malloc(1 * sizeof(xsingle_node(int)));
    xsingle_node(int) *new_next1 = (xsingle_node(int) *) malloc(1 * sizeof(xsingle_node(int)));
    xsingle_node(int) *new_next2 = (xsingle_node(int) *) malloc(1 * sizeof(xsingle_node(int)));

    numbers->data = 1;
    numbers->next = new_next1;
    new_next2->data = 3;
    xnode_set_data(numbers, 1);
    xnode_set_next_data(numbers, 2);
    
    cester_assert_uint_eq(xnode_get_data(numbers), 1);
    cester_assert_uint_eq(xnode_get_next_data(numbers), 2);

    xnode_link_next(numbers, new_next2);
    cester_assert_uint_ne(xnode_get_next_data(numbers), 2);
    cester_assert_uint_eq(xnode_get_next_data(numbers), 3);
    
    free(numbers);
    free(new_next1);
    free(new_next2);
})

CESTER_TEST(xnode_init, _, {
    xnode(int) *numbers = (xnode(int) *) malloc(1 * sizeof(xnode(int)));

    free(numbers);
})

CESTER_TEST(xnode_data, _, {
    xnode(int) *numbers = (xnode(int) *) malloc(1 * sizeof(xnode(int)));
    numbers->data = 1;

    cester_assert_uint_eq(xnode_get_data(numbers), 1);
    xnode_set_data(numbers, 2);
    cester_assert_uint_eq(xnode_get_data(numbers), 2);

    free(numbers);
})

CESTER_TEST(xnode_next, _, {
    xnode(int) *numbers = (xnode(int) *) malloc(1 * sizeof(xnode(int)));
    xnode(int) *new_next1 = (xnode(int) *) malloc(1 * sizeof(xnode(int)));
    xnode(int) *new_next2 = (xnode(int) *) malloc(1 * sizeof(xnode(int)));

    numbers->data = 1;
    numbers->next = new_next1;
    new_next2->data = 3;
    xnode_set_data(numbers, 1);
    xnode_set_next_data(numbers, 2);
    
    cester_assert_uint_eq(xnode_get_data(numbers), 1);
    cester_assert_uint_eq(xnode_get_next_data(numbers), 2);

    xnode_link_next(numbers, new_next2);
    cester_assert_uint_ne(xnode_get_next_data(numbers), 2);
    cester_assert_uint_eq(xnode_get_next_data(numbers), 3);
    
    free(numbers);
    free(new_next1);
    free(new_next2);
})

CESTER_TEST(xnode_prev, _, {
    xnode(int) *numbers = (xnode(int) *) malloc(1 * sizeof(xnode(int)));
    xnode(int) *new_next1 = (xnode(int) *) malloc(1 * sizeof(xnode(int)));
    xnode(int) *new_next2 = (xnode(int) *) malloc(1 * sizeof(xnode(int)));

    numbers->data = 1;
    numbers->next = new_next1;
    new_next2->data = 3;
    xnode_set_data(numbers, 1);
    xnode_set_next_data(numbers, 2);
    
    cester_assert_uint_eq(xnode_get_data(numbers), 1);
    cester_assert_uint_eq(xnode_get_next_data(numbers), 2);

    xnode_link_next(numbers, new_next2);
    cester_assert_uint_ne(xnode_get_next_data(numbers), 2);
    cester_assert_uint_eq(xnode_get_next_data(numbers), 3);
    
    free(numbers);
    free(new_next1);
    free(new_next2);
})

CESTER_TEST(xnode_prev_next, _, {
    xnode(int) *numbers = (xnode(int) *) malloc(1 * sizeof(xnode(int)));
    xnode(int) *prev = (xnode(int) *) malloc(1 * sizeof(xnode(int)));
    xnode(int) *next = (xnode(int) *) malloc(1 * sizeof(xnode(int)));

    xnode_set_data(prev, 1);
    xnode_set_data(numbers, 2);
    xnode_set_data(next, 3);
    xnode_link_prev(numbers, prev);
    xnode_link_next(numbers, next);
    
    cester_assert_uint_eq(xnode_get_prev_data(numbers), 1);
    cester_assert_uint_eq(xnode_get_data(numbers), 2);
    cester_assert_uint_eq(xnode_get_next_data(numbers), 3);
    
    xnode_set_data(prev, 4);
    xnode_set_data(numbers, 5);
    xnode_set_data(next, 6);
    
    cester_assert_uint_eq(xnode_get_prev_data(numbers), 4);
    cester_assert_uint_eq(xnode_get_data(numbers), 5);
    cester_assert_uint_eq(xnode_get_next_data(numbers), 6);
    
    free(numbers);
    free(prev);
    free(next);
})

CESTER_TODO_TEST(xnode_iterator_prev_manual, test_inst, {
    xnode(int) *iter;
    xnode(int) *numbers = (xnode(int) *) test_inst->arg;

    iter = numbers;
    while (xnode_has_prev(iter)) {
        cester_assert_uint_lt(xnode_get_prev_data(iter), xnode_get_data(numbers));
        iter = xnode_get_prev(iter);
    }

    iter = numbers;
    cester_assert_uint_eq(xnode_get_prev_data(iter), 4);
    iter = xnode_get_prev(iter);
    cester_assert_uint_eq(xnode_get_prev_data(iter), 3);
    iter = xnode_get_prev(iter);
    cester_assert_uint_eq(xnode_get_prev_data(iter), 2);
    iter = xnode_get_prev(iter);
    cester_assert_uint_eq(xnode_get_prev_data(iter), 1);
    iter = xnode_get_prev(iter);
    
})

CESTER_TODO_TEST(xnode_iterator_next_manual, test_inst, {
    xnode(int) *iter;
    xnode(int) *numbers = (xnode(int) *) test_inst->arg;

    iter = numbers;
    while (xnode_has_next(iter)) {
        cester_assert_uint_gt(xnode_get_next_data(iter), xnode_get_data(numbers));
        iter = xnode_get_next(iter);
    }

    iter = numbers;
    cester_assert_uint_eq(xnode_get_next_data(iter), 6);
    iter = xnode_get_next(iter);
    cester_assert_uint_eq(xnode_get_next_data(iter), 7);
    iter = xnode_get_next(iter);
    cester_assert_uint_eq(xnode_get_next_data(iter), 8);
    iter = xnode_get_next(iter);
    cester_assert_uint_eq(xnode_get_next_data(iter), 9);
    iter = xnode_get_next(iter);
    
})

CESTER_TODO_TEST(xnode_custom_iterator_prev, test_inst, {
    xnode(int) *numbers = (xnode(int) *) test_inst->arg;
    
    while (XITERATOR_UD_HAS_PREV(xnode_int)(numbers)) {
        cester_assert_uint_lt(XITERATOR_UD_PREV(xnode_int)(numbers), xnode_get_data(numbers));
    }

    XITERATOR_UD_RESET(xnode_int)(numbers);
    cester_assert_uint_eq(XITERATOR_UD_HAS_PREV(xnode_int)(numbers), TRUE);
    cester_assert_uint_eq(XITERATOR_UD_PREV(xnode_int)(numbers), 4);
    cester_assert_uint_eq(XITERATOR_UD_HAS_PREV(xnode_int)(numbers), TRUE);
    cester_assert_uint_eq(XITERATOR_UD_PREV(xnode_int)(numbers), 3);
    cester_assert_uint_eq(XITERATOR_UD_HAS_PREV(xnode_int)(numbers), TRUE);
    cester_assert_uint_eq(XITERATOR_UD_PREV(xnode_int)(numbers), 2);
    cester_assert_uint_eq(XITERATOR_UD_HAS_PREV(xnode_int)(numbers), TRUE);
    cester_assert_uint_eq(XITERATOR_UD_PREV(xnode_int)(numbers), 1);
    cester_assert_uint_ne(XITERATOR_UD_HAS_PREV(xnode_int)(numbers), TRUE);
})

CESTER_TODO_TEST(xnode_custom_iterator_next, test_inst, {
    xnode(int) *numbers = (xnode(int) *) test_inst->arg;
    
    while (XITERATOR_UD_HAS_NEXT(xnode_int)(numbers)) {
        cester_assert_uint_gt(XITERATOR_UD_NEXT(xnode_int)(numbers), xnode_get_data(numbers));
    }

    XITERATOR_UD_RESET(xnode_int)(numbers);
    cester_assert_uint_eq(XITERATOR_UD_HAS_NEXT(xnode_int)(numbers), TRUE);
    cester_assert_uint_eq(XITERATOR_UD_NEXT(xnode_int)(numbers), 6);
    cester_assert_uint_eq(XITERATOR_UD_HAS_NEXT(xnode_int)(numbers), TRUE);
    cester_assert_uint_eq(XITERATOR_UD_NEXT(xnode_int)(numbers), 7);
    cester_assert_uint_eq(XITERATOR_UD_HAS_NEXT(xnode_int)(numbers), TRUE);
    cester_assert_uint_eq(XITERATOR_UD_NEXT(xnode_int)(numbers), 8);
    cester_assert_uint_eq(XITERATOR_UD_HAS_NEXT(xnode_int)(numbers), TRUE);
    cester_assert_uint_eq(XITERATOR_UD_NEXT(xnode_int)(numbers), 9);
    cester_assert_uint_ne(XITERATOR_UD_HAS_NEXT(xnode_int)(numbers), TRUE);
})

CESTER_TODO_TEST(xnode_custom_foreach, test_inst, {
    xnode(int) *numbers = (xnode(int) *) test_inst->arg;
    
    XFOREACH_UD(xnode_int, int number, numbers, {
        cester_assert_uint_gt(number, xnode_get_data(numbers));
    });
})

CESTER_TODO_TEST(xnode_custom_foreach_reverse, test_inst, {
    xnode(int) *numbers = (xnode(int) *) test_inst->arg;
    
    XFOREACH_UD_REVERSE(xnode_int, int number, numbers, {
        cester_assert_uint_lt(number, xnode_get_data(numbers));
    });
})

CESTER_AFTER_ALL(test_inst, {    
    free_all_nodes_compact((xnode(int) *)test_inst->arg);
})

CESTER_OPTIONS(
    CESTER_DEBUG_LEVEL(3);
)


