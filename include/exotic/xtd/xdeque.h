
/**
    \copyright MIT License Copyright (xcapacity) 2020, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 21 December 2020
    \file xdeque.h
*/

#ifndef EXOTIC_XDEQUE_H
#define EXOTIC_XDEQUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "xmath.h"
#include "xiterator.h"

#ifdef __cplusplus
#if !defined(ALLOW_XTD_TYPES_WITH_ALTERNATIVES_IN_CPP) && __cplusplus >= 201103L
    #warning Do not use this type in C++ 03 and above, use the std::deque class instead
#endif
#endif

#define SETUP_XDEQUE_ONLY_FOR(T) typedef struct xdeque_##T##_s { \
    size_t capacity;\
    size_t expansion_rate;\
    size_t size;\
    size_t max_size;\
    size_t first;\
    size_t last;\
    T *buffer;\
    void *(*memory_malloc)  (size_t size);\
    void *(*memory_calloc) (size_t blocks, size_t size);\
    void  (*memory_free)   (void *block);\
} xdeque_##T;\
\
enum x_stat xdeque_##T##_new(xdeque_##T **out);\
enum x_stat xdeque_##T##_new_config(struct xcontainer_config * const config, xdeque_##T **out);\
enum x_stat xdeque_##T##_add(xdeque_##T *container, T element);\
static enum x_stat xdeque_##T##_expand_capacity(xdeque_##T *container);\
\
enum x_stat xdeque_##T##_new(xdeque_##T **out) \
{\
    struct xcontainer_config config;\
    init_xcontainer_config(&config);\
    return xdeque_##T##_new_config(&config, out);\
}\
\
enum x_stat xdeque_##T##_new_max_size(xdeque_##T **out, size_t max_size) \
{\
    struct xcontainer_config config;\
    init_xcontainer_config_max_size(&config, max_size);\
    return xdeque_##T##_new_config(&config, out);\
}\
\
enum x_stat xdeque_##T##_new_config(struct xcontainer_config * const config, xdeque_##T **out) \
{\
    size_t expansion_rate;\
    xdeque_##T *container;\
    T *buffer;\
    if (config->expansion_rate <= 1) {\
        expansion_rate = XDEFAULT_CONTAINER_EXPANSION_RATE;\
    } else {\
        expansion_rate = config->expansion_rate;\
    }\
    if ((!config->capacity || expansion_rate >= (config->max_size / config->capacity)) && (config->max_size < config->capacity)) {\
        return XTD_INVALID_CAPACITY_ERR;\
    }\
    container = (xdeque_##T *) config->allocator.memory_calloc(1, sizeof(xdeque_##T));\
    if (!container) {\
        return XTD_ALLOC_ERR;\
    }\
    buffer = (T *) config->allocator.memory_malloc(config->capacity * sizeof(T));\
    if (!buffer) {\
        config->allocator.memory_free(container);\
        return XTD_ALLOC_ERR;\
    }\
    container->capacity             = xmath_round_power_of_two(config->capacity);\
    container->expansion_rate       = config->expansion_rate;\
    container->max_size             = config->max_size;\
    container->size                 = 0;\
    container->first                = 0;\
    container->last                 = 0;\
    container->memory_malloc         = config->allocator.memory_malloc;\
    container->memory_calloc        = config->allocator.memory_calloc;\
    container->memory_free          = config->allocator.memory_free;\
    container->buffer               = buffer;\
    *out = container;\
    return XTD_OK;\
}\
\
enum x_stat xdeque_##T##_add_front(xdeque_##T *container, T element)\
{\
    if (container->size >= container->max_size) {\
        return XTD_MAX_SIZE_ERR;\
    }\
    if (container->size >= container->capacity && xdeque_##T##_expand_capacity(container) != XTD_OK) {\
        return XTD_ALLOC_ERR;\
    }\
    container->first = (container->first - 1) & (container->capacity - 1);\
    container->buffer[container->first] = element;\
    container->size++;\
    return XTD_OK;\
}\
\
enum x_stat xdeque_##T##_add_back(xdeque_##T *container, T element)\
{\
    if (container->size >= container->max_size) {\
        return XTD_MAX_SIZE_ERR;\
    }\
    if (container->capacity == container->size && xdeque_##T##_expand_capacity(container) != XTD_OK) {\
        return XTD_ALLOC_ERR;\
    }\
    container->buffer[container->last] = element;\
    container->last = (container->last + 1) & (container->capacity - 1);\
    container->size++;\
    return XTD_OK;\
}\
\
enum x_stat xdeque_##T##_add(xdeque_##T *container, T element)\
{\
    return xdeque_##T##_add_back(container, element);\
}\
\
enum x_stat xdeque_##T##_add_at(xdeque_##T *container, T element, size_t index)\
{\
    size_t xcapacity;\
    size_t xlast;\
    size_t xfirst;\
    size_t xpos;\
    if (index > container->size) {\
        return XTD_INDEX_OUT_OF_RANGE_ERR;\
    }\
    if (index == container->size) {\
        return xdeque_##T##_add_back(container, element);\
    }\
    if (container->size >= container->max_size) {\
        return XTD_MAX_SIZE_ERR;\
    }\
    if (container->capacity == container->size && xdeque_##T##_expand_capacity(container) != XTD_OK) {\
        return XTD_ALLOC_ERR;\
    }\
    xcapacity = container->capacity - 1;\
    xlast = container->last & xcapacity;\
    xfirst = container->first & xcapacity;\
    xpos = (container->first + index) & xcapacity;\
    if (index == 0) {\
        return xdeque_##T##_add_front(container, element);\
    }\
    if (index == xcapacity) {\
        return xdeque_##T##_add_back(container, element);\
    }\
    if (index <= (container->size / 2) - 1) {\
        if (xpos < xfirst || xfirst == 0) {\
            const size_t r_move = (xfirst != 0) ? xcapacity - xfirst + 1 : 0;\
            const size_t l_move = xpos;\
            T e_first = container->buffer[0];\
            if (xfirst != 0) {\
                memmove(&(container->buffer[xfirst - 1]),\
                        &(container->buffer[xfirst]),\
                        r_move * sizeof(T));\
            }\
            if (xpos != 0) {\
                memmove(&(container->buffer[0]),\
                        &(container->buffer[1]),\
                        l_move * sizeof(T));\
            }\
            container->buffer[xcapacity] = e_first;\
        } else {\
            memmove(&(container->buffer[xfirst - 1]),\
                    &(container->buffer[xfirst]),\
                    index * sizeof(T));\
        }\
        container->first = (container->first - 1) & xcapacity;\
    } else {\
        if (xpos > xlast || xlast == xcapacity) {\
            T e_last = container->buffer[0];\
            if (xpos != xcapacity) {\
                memmove(&(container->buffer[xpos + 1]),\
                        &(container->buffer[xpos]),\
                        (xcapacity - xpos) * sizeof(T));\
            }\
            if (xlast != xcapacity) {\
                memmove(&(container->buffer[1]),\
                        &(container->buffer[0]),\
                        (xlast + 1) * sizeof(T));\
            }\
            container->buffer[0] = e_last;\
        } else {\
            memmove(&(container->buffer[xpos + 1]),\
                    &(container->buffer[xpos]),\
                    (container->size - index) * sizeof(T));\
        }\
        container->last = (container->last + 1) & xcapacity;\
    }\
    container->buffer[xpos] = element;\
    container->size++;\
    return XTD_OK;\
}\
\
enum x_stat xdeque_##T##_get_at(xdeque_##T *container, size_t index, T *out)\
{\
    size_t actual_index;\
    if (!out) {\
        return XTD_OUT_PARAM_NULL_ERR;\
    }\
    if (index >= container->size) {\
        return XTD_INDEX_OUT_OF_RANGE_ERR;\
    }\
    actual_index = (container->first + index) & (container->capacity - 1);\
    *out = container->buffer[actual_index];\
    return XTD_OK;\
}\
\
enum x_stat xdeque_##T##_get_front(xdeque_##T *container, T *out)\
{\
    if (!out) {\
        return XTD_OUT_PARAM_NULL_ERR;\
    }\
    if (container->size == 0) {\
        return XTD_EMPTY_CONTAINER_ERR;\
    }\
    *out = container->buffer[container->first];\
    return XTD_OK;\
}\
\
enum x_stat xdeque_##T##_get_back(xdeque_##T *container, T *out)\
{\
    size_t last;\
    if (!out) {\
        return XTD_OUT_PARAM_NULL_ERR;\
    }\
    if (container->size == 0) {\
        return XTD_EMPTY_CONTAINER_ERR;\
    }\
    last = (container->last - 1) & (container->capacity - 1);\
    *out = container->buffer[last];\
    return XTD_OK;\
}\
\
enum x_stat xdeque_##T##_replace_at(xdeque_##T *container, size_t index, T element, T *out)\
{\
    size_t actual_index;\
    if (index >= container->size) {\
        return XTD_INDEX_OUT_OF_RANGE_ERR;\
    }\
    actual_index = (container->first + index) & (container->capacity - 1);\
    if (out) {\
        *out = container->buffer[actual_index];\
    }\
    container->buffer[actual_index] = element;\
    return XTD_OK;\
}\
\
enum x_stat xdeque_##T##_remove_front(xdeque_##T *container, T *out)\
{\
    T element;\
    if (container->size == 0) {\
        return XTD_INDEX_OUT_OF_RANGE_ERR;\
    }\
    element = container->buffer[container->first];\
    container->first = (container->first + 1) & (container->capacity - 1);\
    container->size--;\
    if (out) {\
        *out = element;\
    }\
    return XTD_OK;\
}\
\
enum x_stat xdeque_##T##_remove_back(xdeque_##T *container, T *out)\
{\
    size_t last;\
    T element;\
    if (container->size == 0) {\
        return XTD_INDEX_OUT_OF_RANGE_ERR;\
    }\
    last = (container->last - 1) & (container->capacity - 1);\
    element = container->buffer[last];\
    container->last = last;\
    container->size--;\
    if (out) {\
        *out = element;\
    }\
    return XTD_OK;\
}\
\
enum x_stat xdeque_##T##_remove_at(xdeque_##T *container, size_t index, T *out)\
{\
    size_t xcapacity;\
    size_t xlast;\
    size_t xfirst;\
    size_t xpos;\
   T removed;\
    if (index < 0 || index >= container->size) {\
        return XTD_INDEX_OUT_OF_RANGE_ERR;\
    }\
    xcapacity = container->capacity - 1;\
    xlast = container->last & xcapacity;\
    xfirst = container->first & xcapacity;\
    xpos = (container->first + index) & xcapacity;\
    removed = container->buffer[index];\
    if (index == 0) {\
        return xdeque_##T##_remove_front(container, out);\
    }\
    if (index == xcapacity) {\
        return xdeque_##T##_remove_back(container, out);\
    }\
    if (index <= (container->size / 2) - 1) {\
        if (xpos < xfirst) {\
            T e = container->buffer[xcapacity];\
            if (xfirst != xcapacity) {\
                memmove(&(container->buffer[xfirst + 1]),\
                        &(container->buffer[xfirst]),\
                        (xcapacity - xfirst) * sizeof(T));\
            }\
            if (xpos != 0) {\
                memmove(&(container->buffer[1]),\
                        &(container->buffer[0]),\
                        xpos * sizeof(T));\
            }\
            container->buffer[0] = e;\
        } else {\
            memmove(&(container->buffer[xfirst + 1]),\
                    &(container->buffer[xfirst]),\
                    index * sizeof(T));\
        }\
        container->first = (container->first + 1) & xcapacity;\
    } else {\
        if (xpos > xlast) {\
            T e = container->buffer[0];\
            if (xpos != xcapacity) {\
                memmove(&(container->buffer[xpos]),\
                        &(container->buffer[xpos + 1]),\
                        (xcapacity - xpos) * sizeof(T));\
            }\
            if (xpos != 0) {\
                memmove(&(container->buffer[1]),\
                        &(container->buffer[0]),\
                        xlast * sizeof(T));\
            }\
            container->buffer[xcapacity] = e;\
        } else {\
            memmove(&(container->buffer[xpos]),\
                    &(container->buffer[xpos + 1]),\
                    (xlast - xpos) * sizeof(T));\
        }\
        container->last = (container->last- 1) & xcapacity;\
    }\
    container->size--;\
    if (out)\
        *out = removed;\
    return XTD_OK;\
}\
\
enum x_stat xdeque_##T##_clear(xdeque_##T *container)\
{\
    enum x_stat status;\
    while (container->size > 0) {\
        status = xdeque_##T##_remove_at(container, (container->size)-1, XTD_NULL);\
        if (status != XTD_OK) {\
            return status;\
        }\
    }\
    return XTD_OK;\
}\
\
static void xdeque_##T##_copy_buffer(xdeque_##T const * const container, T *buffer, T (*callback) (T))\
{\
    if (callback == XTD_NULL) {\
        if (container->last > container->first) {\
            memcpy(buffer,\
                   &(container->buffer[container->first]),\
                   container->size * sizeof(void*));\
        } else {\
            size_t l = container->last;\
            size_t e = container->capacity - container->first;\
            memcpy(buffer,\
                   &(container->buffer[container->first]),\
                   e * sizeof(void*));\
            memcpy(&(buffer[e]),\
                   container->buffer,\
                   l * sizeof(void*));\
        }\
    } else {\
        size_t i;\
        for (i = 0; i < container->size; i++) {\
            size_t p = (container->first + i) & (container->capacity - 1);\
            buffer[i] = callback(container->buffer[p]);\
        }\
    }\
}\
\
static enum x_stat xdeque_##T##_shrink_to_fit(xdeque_##T *container)\
{\
    size_t new_size;\
    T *new_buffer;\
    if (container->capacity == container->size) {\
        return XTD_OK;\
    }\
    new_size = xmath_round_power_of_two(container->size);\
    if (new_size == container->capacity) {\
        return XTD_OK;\
    }\
    new_buffer = (T *) container->memory_malloc(sizeof(T) * new_size);\
    if (!new_buffer) {\
        return XTD_ALLOC_ERR;\
    }\
    xdeque_##T##_copy_buffer(container, new_buffer, XTD_NULL);\
    container->memory_free(container->buffer);\
    container->buffer   = new_buffer;\
    container->first    = 0;\
    container->last     = container->size;\
    container->capacity = new_size;\
    return XTD_OK;\
}\
\
static enum x_stat xdeque_##T##_expand_capacity(xdeque_##T *container)\
{\
    size_t new_capacity;\
    T *new_buffer;\
    if (container->capacity == XTD_MATH_MAX_POW_TWO) {\
        return XTD_MAX_CAPACITY_ERR;\
    }\
    new_capacity = container->capacity << 1;\
    new_buffer = (T *) container->memory_calloc(new_capacity, sizeof(T));\
    if (!new_buffer) {\
        return XTD_ALLOC_ERR;\
    }\
    xdeque_##T##_copy_buffer(container, new_buffer, XTD_NULL);\
    container->memory_free(container->buffer);\
    container->first      = 0;\
    container->last       = container->size;\
    container->capacity   = new_capacity;\
    container->buffer     = new_buffer;\
    return XTD_OK;\
}\
\
\
\

/*
    
*/
#define SETUP_ITERATOR_FOR_XDEQUE(T) \
\
void xdeque_iterator_##T##_reset_forward(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    iterator->forward_index = 0;\
}\
\
void xdeque_iterator_##T##_reset_backward(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    iterator->backward_index = ((xdeque_##T *) iterator->container)->size-1;\
}\
\
void xdeque_iterator_##T##_reset(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    iterator->forward_index = 0;\
    iterator->backward_index = ((xdeque_##T *) iterator->container)->size-1;\
}\
\
void xdeque_iterator_##T##_destroy(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    if (iterator == XTD_NULL) {\
        return;\
    }\
    if (iterator->container != XTD_NULL) {\
        ((xdeque_##T *) iterator->container)->memory_free(iterator);\
        return;\
    }\
    x_free(iterator);\
}\
\
void xdeque_iterator_##T##_advance_by(void *iterator_, size_t distance) {\
    XIterator *iterator = (XIterator *) iterator_;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    iterator->forward_index += distance;\
}\
\
void xdeque_iterator_##T##_decrement(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    iterator->forward_index--;\
}\
\
void xdeque_iterator_##T##_increment(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    iterator->forward_index++;\
}\
\
bool xdeque_iterator_##T##_has_next(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xdeque_##T *container;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return FALSE;\
    }\
    container = (xdeque_##T *) iterator->container;\
    return (container != XTD_NULL && iterator->forward_index < container->size);\
}\
\
void *xdeque_iterator_##T##_next(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xdeque_##T *container;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return XTD_NULL;\
    }\
    container = (xdeque_##T *) iterator->container;\
    return (void *) container->buffer[iterator->forward_index++];\
}\
\
bool xdeque_iterator_##T##_has_prev(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xdeque_##T *container;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return FALSE;\
    }\
    container = (xdeque_##T *) iterator->container;\
    return (container != XTD_NULL && iterator->backward_index != -1 && ((iterator->backward_index <= container->size) || (iterator->backward_index = container->size-1) > 0));\
}\
\
void *xdeque_iterator_##T##_prev(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xdeque_##T *container;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return XTD_NULL;\
    }\
    container = (xdeque_##T *) iterator->container;\
    return (void *) container->buffer[iterator->backward_index--];\
}\
\
static XIterator *xiterator_init_xdeque_##T(xdeque_##T *container) \
{\
    XIterator *iterator;\
    if (container == XTD_NULL) {\
        return XTD_NULL;\
    }\
    iterator = (XIterator *) container->memory_malloc(sizeof(XIterator));\
    if (iterator == XTD_NULL) {\
        return XTD_NULL;\
    }\
    iterator->forward_index = 0;\
    iterator->backward_index = container->size-1;\
    iterator->has_next = xdeque_iterator_##T##_has_next;\
    iterator->next = xdeque_iterator_##T##_next;\
    iterator->has_prev = xdeque_iterator_##T##_has_prev;\
    iterator->prev = xdeque_iterator_##T##_prev;\
    iterator->reset_forward = xdeque_iterator_##T##_reset_forward;\
    iterator->reset_backward = xdeque_iterator_##T##_reset_backward;\
    iterator->reset = xdeque_iterator_##T##_reset;\
    iterator->destroy = xdeque_iterator_##T##_destroy;\
    iterator->advance_by = xdeque_iterator_##T##_advance_by;\
    iterator->increment = xdeque_iterator_##T##_increment;\
    iterator->decrement = xdeque_iterator_##T##_decrement;\
    iterator->container = container;\
    return iterator;\
}\
\
\
\

/**

*/
#define xdeque(T) xdeque_##T

/**

*/
#define xdeque_new(T) xdeque_##T##_new

/**

*/
#define xdeque_new_max_size(T) xdeque_##T##_new_max_size

/**

*/
#define xdeque_new_config(T) xdeque_##T##_new_config

/**

*/
#define xdeque_add_front(T) xdeque_##T##_add_front

/**

*/
#define xdeque_add_back(T) xdeque_##T##_add_back

/**

*/
#define xdeque_add(T) xdeque_##T##_add

/**

*/
#define xdeque_add_at(T) xdeque_##T##_add_at

/**

*/
#define xdeque_get_at(T) xdeque_##T##_get_at

/**

*/
#define xdeque_get_front(T) xdeque_##T##_get_front

/**

*/
#define xdeque_get_back(T) xdeque_##T##_get_back

/**

*/
#define xdeque_replace_at(T) xdeque_##T##_replace_at

/**

*/
#define xdeque_remove_front(T) xdeque_##T##_remove_front

/**

*/
#define xdeque_remove_back(T) xdeque_##T##_remove_back

/**

*/
#define xdeque_remove_at(T) xdeque_##T##_remove_at

/**

*/
#define xdeque_clear(T) xdeque_##T##_clear

/**

*/
#define xdeque_shrink_to_fit(T) xdeque_##T##_shrink_to_fit

/**

*/
#define xdeque_destroy(container) { \
        container->memory_free(container->buffer); \
        container->memory_free((void *)container); \
    }

/*

*/
#define xdeque_capacity xcapacity

/*

*/
#define xdeque_size xsize

/*

*/
#define xdeque_max_size xmax_size

/*

*/
#define xdeque_is_empty xis_empty

/*

*/
#define SETUP_XDEQUE_FOR(T) SETUP_XDEQUE_ONLY_FOR(T) SETUP_ITERATOR_FOR_XDEQUE(T)


#ifdef __cplusplus
}
#endif

#endif
