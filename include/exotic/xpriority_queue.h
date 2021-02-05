
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 23 January 2021
    \file xpriority_queue.h
*/
/* https://www.programiz.com/dsa/heap-data-structure */
/* https://github.com/srdja/Collections-C/blob/master/src/cc_pqueue.c */

#ifndef EXOTIC_XPRIORITY_QUEUE_H
#define EXOTIC_XPRIORITY_QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "xcommon.h"
#include "xiterator.h"

#ifdef __cplusplus
#if !defined(ALLOW_XTD_TYPES_WITH_ALTERNATIVES_IN_CPP) && __cplusplus >= 201103L
    #warning Do not use this type in C++ 11 and above, use the std::priority_queue class instead
#endif
#define NULL 0
#endif

#define XPRIORITY_QUEUE_PARENT(x)  ((x - 1) / 2)
#define XPRIORITY_QUEUE_LEFT(x)    ((2 * x) + 1)
#define XPRIORITY_QUEUE_RIGHT(x)   ((2 * x) + 2)

/*
    
*/
#define SETUP_XPRIORITY_QUEUE_FOR(T) typedef struct xpriority_queue_##T##_s { \
    size_t capacity;\
    size_t expansion_rate;\
    size_t size;\
    size_t max_size;\
    T *buffer;\
    XIterator *iter;\
    void *(*memory_alloc)  (size_t size);\
    void *(*memory_calloc) (size_t blocks, size_t size);\
    void  (*memory_free)   (void *block);\
    bool  (*cmp) (const T a, const T b);\
} xpriority_queue_##T;\
\
enum x_stat xpriority_queue_##T##_new(xpriority_queue_##T **out, bool  (*cmp) (const T a, const T b));\
enum x_stat xpriority_queue_##T##_new_config(struct xcontainer_config * const config, xpriority_queue_##T **out, bool  (*cmp) (const T a, const T b));\
static enum x_stat xpriority_queue_##T##_expand_capacity(xpriority_queue_##T *container);\
static void xpriority_queue_##T##_heapify(xpriority_queue_##T *container, size_t index);\
\
enum x_stat xpriority_queue_##T##_new(xpriority_queue_##T **out, bool  (*cmp) (const T a, const T b)) \
{\
    struct xcontainer_config config;\
    init_xcontainer_config(&config);\
    return xpriority_queue_##T##_new_config(&config, out, cmp);\
}\
\
enum x_stat xpriority_queue_##T##_new_max_size(xpriority_queue_##T **out, size_t max_size, bool  (*cmp) (const T a, const T b)) \
{\
    struct xcontainer_config config;\
    init_xcontainer_config_max_size(&config, max_size);\
    return xpriority_queue_##T##_new_config(&config, out, cmp);\
}\
\
enum x_stat xpriority_queue_##T##_new_config(struct xcontainer_config * const config, xpriority_queue_##T **out, bool  (*cmp) (const T a, const T b)) \
{\
    size_t expansion_rate;\
    xpriority_queue_##T *container;\
    T *buffer;\
    XIterator *iter;\
    if (!cmp) {\
        return XTD_INVALID_PARAMETER;\
    }\
    if (config->expansion_rate <= 1) {\
        expansion_rate = XDEFAULT_CONTAINER_EXPANSION_RATE;\
    } else {\
        expansion_rate = config->expansion_rate;\
    }\
    if ((!config->capacity || expansion_rate >= (config->max_size / config->capacity)) && (config->max_size < config->capacity)) {\
        return XTD_INVALID_CAPACITY_ERR;\
    }\
    container = (xpriority_queue_##T *) config->memory_calloc(1, sizeof(xpriority_queue_##T));\
    if (!container) {\
        return XTD_ALLOC_ERR;\
    }\
    buffer = (T *) config->memory_alloc(config->capacity * sizeof(T));\
    if (!buffer) {\
        config->memory_free(container);\
        return XTD_ALLOC_ERR;\
    }\
    iter = (XIterator *) config->memory_alloc(sizeof(XIterator));\
    if (!iter) {\
        config->memory_free(buffer);\
        config->memory_free(container);\
        return XTD_ALLOC_ERR;\
    }\
    container->capacity             = config->capacity;\
    container->expansion_rate       = config->expansion_rate;\
    container->max_size             = config->max_size;\
    container->size                 = 0;\
    container->memory_alloc         = config->memory_alloc;\
    container->memory_calloc        = config->memory_calloc;\
    container->memory_free          = config->memory_free;\
    container->cmp                  = cmp;\
    container->buffer               = buffer;\
    container->iter                 = iter;\
    container->iter->index          = 0;\
    container->iter->backward_index = 0;\
    *out = container;\
    return XTD_OK;\
}\
\
enum x_stat xpriority_queue_##T##_push(xpriority_queue_##T *container, T element)\
{\
    enum x_stat status;\
    size_t container_size;\
    T child;\
    T parent;\
    container_size = container->size;\
    if (container->size >= container->max_size) {\
        return XTD_MAXTD_SIZE_ERR;\
    }\
    if (container_size >= container->capacity) {\
        status = xpriority_queue_##T##_expand_capacity(container);\
        if (status != XTD_OK) {\
            return status;\
        }\
    }\
    container->buffer[container_size] = element;\
    container->size++;\
    if (container_size == 0) {\
        return XTD_OK;\
    }\
    child  = container->buffer[container_size];\
    parent = container->buffer[XPRIORITY_QUEUE_PARENT(container_size)];\
    while (container_size != 0 && container->cmp(child, parent) > 0) {\
        T temp = container->buffer[container_size];\
        container->buffer[container_size] = container->buffer[XPRIORITY_QUEUE_PARENT(container_size)];\
        container->buffer[XPRIORITY_QUEUE_PARENT(container_size)] = temp;\
        container_size = XPRIORITY_QUEUE_PARENT(container_size);\
        child  = container->buffer[container_size];\
        parent = container->buffer[XPRIORITY_QUEUE_PARENT(container_size)];\
    }\
    return XTD_OK;\
}\
\
enum x_stat xpriority_queue_##T##_peek(xpriority_queue_##T *container, T *out)\
{\
    if (container->size == 0) {\
        return XTD_OUT_OF_RANGE_ERR;\
    }\
    *out = container->buffer[0];\
    return XTD_OK;\
}\
\
enum x_stat xpriority_queue_##T##_pop(xpriority_queue_##T *container, T *out)\
{\
    T temp;\
    if (container->size == 0) {\
        return XTD_EMPTY_CONTAINER_ERR;\
    }\
    temp = container->buffer[0];\
    container->buffer[0] = container->buffer[container->size - 1];\
    container->buffer[container->size - 1] = temp;\
    temp = container->buffer[container->size - 1];\
    container->size--;\
    xpriority_queue_##T##_heapify(container, 0);\
    if (out) {\
        *out = temp;\
    }\
    return XTD_OK;\
}\
\
static enum x_stat xpriority_queue_##T##_shrink_to_fit(xpriority_queue_##T *container)\
{\
    T *new_buffer;\
    size_t size;\
    if (container->size == container->capacity) {\
        return XTD_OK;\
    }\
    new_buffer = (T *) container->memory_calloc(container->size, sizeof(T));\
    if (!new_buffer) {\
        return XTD_ALLOC_ERR;\
    }\
    size = container->size < 1 ? 1 : container->size;\
    memcpy(new_buffer, container->buffer, size * sizeof(T));\
    container->memory_free(container->buffer);\
    container->buffer   = new_buffer;\
    container->capacity = container->size;\
    return XTD_OK;\
}\
\
static enum x_stat xpriority_queue_##T##_expand_capacity(xpriority_queue_##T *container)\
{\
    size_t temp_capacity;\
    T *new_buffer;\
    if (container->capacity >= container->max_size) {\
        return XTD_MAXTD_CAPACITY_ERR;\
    }\
    temp_capacity = container->capacity * container->expansion_rate;\
    if (temp_capacity <= container->capacity) {\
        container->capacity = container->max_size;\
    } else {\
        container->capacity = temp_capacity;\
    }\
    new_buffer = (T *) container->memory_alloc(temp_capacity * sizeof(T));\
    if (!new_buffer) {\
        return XTD_ALLOC_ERR;\
    }\
    memcpy(new_buffer, container->buffer, container->size * sizeof(T));\
    container->memory_free(container->buffer);\
    container->buffer = new_buffer;\
    return XTD_OK;\
}\
\
static void xpriority_queue_##T##_heapify(xpriority_queue_##T *container, size_t index)\
{\
    size_t left_index;\
    size_t right_index;\
    size_t temp_index;\
    T left;\
    T right;\
    T index_value;\
    T swap_temp;\
    if (container->size <= 1) {\
        return;\
    }\
    left_index = XPRIORITY_QUEUE_LEFT(index);\
    right_index = XPRIORITY_QUEUE_RIGHT(index);\
    temp_index = index;\
    left = container->buffer[left_index];\
    right = container->buffer[right_index];\
    index_value = container->buffer[index];\
    if (left_index < container->size && container->cmp(index_value, left) < 0) {\
        index_value = left;\
        index = left_index;\
    }\
    if (right_index < container->size && container->cmp(index_value, right) < 0) {\
        index_value = right;\
        index = right_index;\
    }\
    if (index != temp_index) {\
        swap_temp = container->buffer[temp_index];\
        container->buffer[temp_index] = container->buffer[index];\
        container->buffer[index] = swap_temp;\
        xpriority_queue_##T##_heapify(container, index);\
    }\
}\
\
\

/**

*/
#define xpriority_queue(T) xpriority_queue_##T

/**

*/
#define xpriority_queue_new(T) xpriority_queue_##T##_new

/**

*/
#define xpriority_queue_new_max_size(T) xpriority_queue_##T##_new_max_size

/**

*/
#define xpriority_queue_new_config(T) xpriority_queue_##T##_new_config

/**

*/
#define xpriority_queue_push(T) xpriority_queue_##T##_push

/**

*/
#define xpriority_queue_enqueue xpriority_queue_push

/**

*/
#define xpriority_queue_peek(T) xpriority_queue_##T##_peek

/**

*/
#define xpriority_queue_pop(T) xpriority_queue_##T##_pop

/**

*/
#define xpriority_queue_dequeue xpriority_queue_pop

/**

*/
#define xpriority_queue_shrink_to_fit(T) xpriority_queue_##T##_shrink_to_fit

/**

*/
#define xpriority_queue_destroy(container) { \
        container->memory_free(container->buffer); \
        container->memory_free(container->iter); \
        container->memory_free(container); \
    }

/*

*/
#define xpriority_queue_capacity xcapacity

/*

*/
#define xpriority_queue_size xsize

/*

*/
#define xpriority_queue_max_size xmax_size

/*

*/
#define xpriority_queue_is_empty xis_empty


#ifdef __cplusplus
}
#endif

#endif
