
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
#define ITERATOR_NEXT(obj) obj->buffer[obj->iter->index];

/**

*/
#define FOREACH(obj, value, body) obj->iter->index = 0;                     \
                                  while (ITERATOR_HAS_NEXT(obj)) {          \
                                        void *value = ITERATOR_NEXT(obj);   \
                                        body                                \
                                        ++obj->iter->index;                 \
                                  }                                         \

/**

*/
#define FOREACH_INDEX(obj, index, value, body) obj->iter->index = 0;        \
                                  while (ITERATOR_HAS_NEXT(obj)) {          \
                                        void *value;                        \
                                        size_t index;                       \
                                        index = obj->iter->index;           \
                                        value = ITERATOR_NEXT(obj);         \
                                        body                                \
                                        ++obj->iter->index;                 \
                                  }                                         \

#ifdef __cplusplus
}
#endif

#endif