/*! gcc -ansi -pedantic-errors {0} -I../include/ -I../../libmetaref/include/ -o out.exe; ./out.exe */

#include <exotic/cester.h>
#include <exotic/xtd/xcommon.h>

CESTER_BODY(

typedef int (*xiterator_next)(void*);
typedef unsigned (*xiterator_has_next)(void*);
typedef unsigned (*xiterator_destroy)(void*);

struct xiterator_s {
    size_t index;
    size_t backward_index;
    xiterator_next next;
    xiterator_has_next has_next;
    xiterator_destroy destroy;
} ;

int index = 20;

unsigned _destroy_iterator_(void *iterator) {
    if (iterator != NULL) {
        x_free(iterator);
    }
}

unsigned _has_next_iterator_(void *iterator) {
    return index != 0;
}

int _next_iterator_(void *iterator) {
    return index--;
}

Iterator *init_iterator() {
    Iterator *iterator = malloc(1 * sizeof(Iterator));
    iterator->destroy = _destroy_iterator_;
    iterator->has_next = _has_next_iterator_;
    iterator->next = _next_iterator_;
    return iterator;
}


)

#define XITERATOR_HAS_NEXT(iterator)\
    iterator->has_next(iterator)

#define XITERATOR_NEXT(iterator)\
    iterator->next(iterator)

CESTER_TEST(test_stack, _, {
    Iterator *iterator = init_iterator();
    while (iterator->has_next(iterator)) {
        printf("Number %d\n", iterator->next(iterator));
    }
    index = 50;
    while (XITERATOR_HAS_NEXT(iterator)) {
        printf("Number %d\n", XITERATOR_NEXT(iterator));
    }
    iterator->destroy(iterator);
})

