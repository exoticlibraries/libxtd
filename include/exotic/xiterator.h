
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
typedef struct iterator_s {
    size_t index;               /**< the current element index in the parent object */
} Iterator;

/**

*/
#define ITERATOR_HAS_NEXT(obj) (obj->iter->index < obj->size)

/**

*/
#define ITERATOR_NEXT(obj) obj->buffer[obj->iter->index++]

/**

*/
#define x_internal_foreach(obj, value, body) obj->iter->index = 0;                     \
                                  while (ITERATOR_HAS_NEXT(obj)) {          \
                                        value = ITERATOR_NEXT(obj);   \
                                        body                                \
                                  }                                         \

/**

*/
#define FOREACH(obj, value, body) x_internal_foreach(obj, value, body)

/**

*/
#define FOREACH_UNSAFE(obj, value, body) x_internal_foreach(obj, void * value, body)

/**

*/
#define FOREACH_INDEX(obj, index_, value, body) obj->iter->index = 0;        \
                                  while (ITERATOR_HAS_NEXT(obj)) {          \
                                        index_ = obj->iter->index;           \
                                        value = ITERATOR_NEXT(obj);         \
                                        body                                \
                                  }                                         \

/**

*/
#define FOREACH_INDEX_UNSAFE(obj, index, value, body) \
                                FOREACH_INDEX(obj, size_t index, void *value, body)

#ifdef __cplusplus
}
#endif

#endif