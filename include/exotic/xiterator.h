
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
struct xiterator_s {
    size_t index;               /**< the current element index in the parent containerect */
    size_t backward_index;      /**< the current element index in the parent containerect */
};

/**

*/
typedef struct xiterator_s XIterator;

/**

*/
#define XITERATOR_RESET(container) {container->iter->index = 0; container->iter->backward_index = container->size-1;}

/**

*/
#define XITERATOR_HAS_NEXT(container) (container->iter->index < container->size)

/**

*/
#define XITERATOR_NEXT(container) container->buffer[container->iter->index++]

/**

*/
#define XITERATOR_HAS_PREV(container) (container->iter->backward_index != -1 && ((container->iter->backward_index <= container->size) || (container->iter->backward_index = container->size-1) > 0))

/**

*/
#define XITERATOR_PREV(container) container->buffer[container->iter->backward_index--]

/**

*/
#define XITERATOR_ADVANCE_BY(container, distance) {container->iter->index += distance;}

/**

*/
#define XITERATOR_INCREMENT(container) {container->iter->index++;}

/**

*/
#define XITERATOR_DECREMENT(container) {container->iter->inde--;}

/**

*/
#define x_internal_foreach(value, container, body) container->iter->index = 0; \
                                  while (XITERATOR_HAS_NEXT(container)) { \
                                        value = XITERATOR_NEXT(container);\
                                        body\
                                  }\

/**

*/
#define XFOREACH(value, container, body) x_internal_foreach(value, container, body)

/**

*/
#define XFOREACH_UNSAFE(value, container, body) x_internal_foreach(void * value, container, body)

/**

*/
#define XFOREACH_INDEX(index_, value, container, body) container->iter->index = 0;\
                                  while (XITERATOR_HAS_NEXT(container)) {\
                                        index_ = container->iter->index;\
                                        value = XITERATOR_NEXT(container);\
                                        body\
                                  }\

/**

*/
#define XFOREACH_INDEX_UNSAFE(index, value, container, body) \
                                XFOREACH_INDEX(unsigned int index, void *value, container, body)

/**

*/
#define x_internal_foreach_reverse(value, container, body) container->iter->backward_index = container->size-1;\
                                  while (XITERATOR_HAS_PREV(container)) {\
                                        value = XITERATOR_PREV(container);\
                                        body\
                                  }\

/**

*/
#define XFOREACH_REVERSE(value, container, body) x_internal_foreach_reverse(value, container, body)

/**

*/
#define XFOREACH_REVERSE_UNSAFE(value, container, body) x_internal_foreach_reverse(void * value, container, body)

/**

*/
#define XFOREACH_REVERSE_INDEX(index_, value, container, body) container->iter->backward_index = container->size-1;\
                                  while (XITERATOR_HAS_PREV(container)) {\
                                        index_ = container->iter->backward_index;\
                                        value = XITERATOR_PREV(container);\
                                        body\
                                  }\

/**

*/
#define XFOREACH_REVERSE_INDEX_UNSAFE(index, value, container, body) \
                                XFOREACH_REVERSE_INDEX(unsigned int index, void *value, container, body)


#define XITERATOR_RPTR_HAS_NEXT(ptr_array) (*(ptr_array) != NULL)

#define XITERATOR_RPTR_NEXT(ptr_array) (*(ptr_array)++)

#define XFOREACH_RPTR(value, ptr_array, body) \
            while (XITERATOR_RPTR_HAS_NEXT(ptr_array)) {\
                  value = XITERATOR_RPTR_NEXT(ptr_array);\
                  body\
            }\

/* iterator for custom types */

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