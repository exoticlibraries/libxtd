
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 24 June 2020
    \file iterator.h
*/

#ifndef EXOTIC_ITERATOR_H
#define EXOTIC_ITERATOR_H

#ifdef __cplusplus
extern "C" {
#endif

/**

*/
typedef void (*xiterator_destroy)(void*);

/**

*/
typedef void (*xiterator_reset)(void*);

/**

*/
typedef void (*xiterator_reset_forward)(void*);
/**

*/
typedef void (*xiterator_reset_backward)(void*);

/**

*/
typedef unsigned (*xiterator_has_next)(void*);


/**

*/
typedef void* (*xiterator_next)(void*);

/**

*/
typedef unsigned (*xiterator_has_prev)(void*);

/**

*/
typedef void* (*xiterator_prev)(void*);


/**

*/
typedef void (*xiterator_advance_by)(void*, size_t distance);

/**

*/
typedef void (*xiterator_increment)(void*);

/**

*/
typedef void (*xiterator_decrement)(void*);

/**

*/
struct xiterator_s {
    size_t forward_index;                     /**< the current element index in the parent containerect */
    size_t backward_index;                    /**< the current element index in the parent containerect */
    xiterator_has_next has_next;              /**< ... */
    xiterator_next next;                      /**< ... */
    xiterator_has_next has_prev;              /**< ... */
    xiterator_next prev;                      /**< ... */
    xiterator_reset reset;                    /**< ... */
    xiterator_destroy destroy;                /**< ... */
    xiterator_advance_by advance_by;          /**< ... */
    xiterator_increment increment;            /**< ... */
    xiterator_decrement decrement;            /**< ... */
    xiterator_reset_forward reset_forward;    /**< ... */
    xiterator_reset_backward reset_backward;  /**< ... */
    void *container;                          /**< ... */
};

/**

*/
typedef struct xiterator_s XIterator;

/**

*/
#define XITERATOR_INIT(xtype, T, container) xiterator_init_##xtype##_##T(container)

/**

*/
#define XITERATOR_RESET(iterator) iterator->reset(iterator)

/**

*/
#define XITERATOR_RESET_FORWARD(iterator) iterator->reset_forward(iterator)

/**

*/
#define XITERATOR_RESET_BACKWARD(iterator) iterator->reset_backward(iterator)

/**

*/
#define XITERATOR_RESET(iterator) iterator->reset(iterator)

/**

*/
#define XITERATOR_HAS_NEXT(iterator) iterator->has_next(iterator)

/**

*/
#define XITERATOR_NEXT(iterator) iterator->next(iterator)

/**

*/
#define XITERATOR_HAS_PREV(iterator) iterator->has_prev(iterator)

/**

*/
#define XITERATOR_PREV(iterator) iterator->prev(iterator)

/**

*/
#define XITERATOR_ADVANCE_BY(iterator, distance) iterator->advance_by(iterator, distance)
#define XITERATOR_ADVANCE_BY_TMP(container, distance) {container->iter->index += distance;}

/**

*/
#define XITERATOR_INCREMENT(iterator) iterator->increment(iterator)
#define XITERATOR_INCREMENT_TMP(container) {container->iter->index++;}

/**

*/
#define XITERATOR_DECREMENT(iterator) iterator->decrement(iterator)
#define XITERATOR_DECREMENT_TMP(container) {container->iter->inde--;}

/**

*/
#define x_internal_foreach(value, iterator, body) XITERATOR_RESET_FORWARD(iterator); \
                                  while (XITERATOR_HAS_NEXT(iterator)) { \
                                        value = XITERATOR_NEXT(container);\
                                        body\
                                  }

/**

*/
#define x_internal_foreach_typed(type, name, iterator, body) XITERATOR_RESET_FORWARD(iterator); \
                                  while (XITERATOR_HAS_NEXT(iterator)) { \
                                        type name = (type) XITERATOR_NEXT(container);\
                                        body\
                                  }

/**

*/
#define XFOREACH(value, iterator, body) x_internal_foreach(value, iterator, body)

/**

*/
#define XFOREACH_TYPED(type, name, iterator, body) x_internal_foreach_typed(type, name, iterator, body)

/**

*/
#define XFOREACH_INDEX(index_, value, container, body) XITERATOR_RESET_FORWARD(iterator);\
                                  while (XITERATOR_HAS_NEXT(iterator)) {\
                                        index_ = iterator->forward_index;\
                                        value = XITERATOR_NEXT(iterator);\
                                        body\
                                  }

/**

*/
#define XFOREACH_INDEX_TYPED(index_, type, name, container, body) XITERATOR_RESET_FORWARD(iterator);\
                                  while (XITERATOR_HAS_NEXT(iterator)) {\
                                        index_ = iterator->forward_index;\
                                        type name = (type) XITERATOR_NEXT(iterator);\
                                        body\
                                  }

/**

*/
#define x_internal_foreach_reverse(value, iterator, body) XITERATOR_RESET_BACKWARD(iterator);\
                                  while (XITERATOR_HAS_PREV(iterator)) {\
                                        value = XITERATOR_PREV(iterator);\
                                        body\
                                  }

/**

*/
#define x_internal_foreach_reverse_typed(type, name, iterator, body) XITERATOR_RESET_BACKWARD(iterator);\
                                  while (XITERATOR_HAS_PREV(iterator)) {\
                                        type name = (type) XITERATOR_PREV(iterator);\
                                        body\
                                  }

/**

*/
#define XFOREACH_REVERSE(value, iterator, body) x_internal_foreach_reverse(value, iterator, body)

/**

*/
#define XFOREACH_REVERSE_TYPED(type, name, iterator, body) x_internal_foreach_reverse_typed(type, name, iterator, body)

/**

*/
#define XFOREACH_REVERSE_INDEX(index_, value, iterator, body) XITERATOR_RESET_BACKWARD(iterator);\
                                  while (XITERATOR_HAS_PREV(iterator)) {\
                                        index_ = iterator->backward_index;\
                                        value = XITERATOR_PREV(iterator);\
                                        body\
                                  }

/**

*/
#define XFOREACH_REVERSE_INDEX_TYPED(index_, type, name, container, body) XITERATOR_RESET_BACKWARD(iterator);\
                                  while (XITERATOR_HAS_PREV(iterator)) {\
                                        index_ = iterator->backward_index;\
                                        type name = (type) = XITERATOR_PREV(iterator);\
                                        body\
                                  }


#define XITERATOR_RPTR_HAS_NEXT(ptr_array) (*(ptr_array) != NULL)

#define XITERATOR_RPTR_NEXT(ptr_array) (*(ptr_array)++)

#define XFOREACH_RPTR(value, ptr_array, body) \
            while (XITERATOR_RPTR_HAS_NEXT(ptr_array)) {\
                  value = XITERATOR_RPTR_NEXT(ptr_array);\
                  body\
            }

/* iterator for custom types */

/**

*/
#define XITERATOR_UD_INIT(T) xiterator_init_##T

/**

*/
#define XITERATOR_UD_DESTROY(T) xiterator_destroy_##T

/**

*/
#define XITERATOR_UD_RESET(T) xiterator_reset_##T

/**

*/
#define XITERATOR_UD_HAS_NEXT(T) xiterator_has_next_##T

/**

*/
#define XITERATOR_UD_NEXT(T) xiterator_next_##T

/**

*/
#define XITERATOR_UD_HAS_PREV(T) xiterator_has_prev_##T

/**

*/
#define XITERATOR_UD_PREV(T) xiterator_prev_##T

/**

*/
#define XITERATOR_UD_ADVANCE_BY(T) xiterator_advance_by_##T

/**

*/
#define XITERATOR_UD_INCREMENT(T) xiterator_increment_##T

/**

*/
#define XITERATOR_UD_DECREMENT(T) xiterator_decrement_##T

/**

*/
#define XFOREACH_UD(T, value, object, body) xiterator_reset_##T(object); \
                                  while (xiterator_has_next_##T(object)) { \
                                        value = xiterator_next_##T(object);\
                                        body\
                                  }\

/**

*/
#define XFOREACH_UD_REVERSE(T, value, object, body) xiterator_reset_##T(object); \
                                  while (xiterator_has_prev_##T(object)) { \
                                        value = xiterator_prev_##T(object);\
                                        body\
                                  }\


#ifdef __cplusplus
}
#endif

#endif


