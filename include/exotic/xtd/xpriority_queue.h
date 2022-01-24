
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <iamthecarisma@gmail.com>
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
#endif

#define XPRIORITY_QUEUE_PARENT(x)  ((x - 1) / 2)
#define XPRIORITY_QUEUE_LEFT(x)    ((2 * x) + 1)
#define XPRIORITY_QUEUE_RIGHT(x)   ((2 * x) + 2)

/*
    
*/
#define SETUP_XPRIORITY_QUEUE_ONLY_FOR(T) typedef struct xpriority_queue_##T##_s { \
    size_t capacity;\
    size_t expansion_rate;\
    size_t size;\
    size_t max_size;\
    T *buffer;\
    void *(*memory_malloc)  (size_t size);\
    void *(*memory_calloc) (size_t blocks, size_t size);\
    void  (*memory_free)   (void *block);\
    bool  (*cmp) (const T a, const T b);\
} xpriority_queue_##T;\
\
static enum x_stat xpriority_queue_##T##_new(xpriority_queue_##T **out, bool  (*cmp) (const T a, const T b));\
static enum x_stat xpriority_queue_##T##_new_config(struct xcontainer_config * const config, xpriority_queue_##T **out, bool  (*cmp) (const T a, const T b));\
static enum x_stat xpriority_queue_##T##_expand_capacity(xpriority_queue_##T *container);\
static void xpriority_queue_##T##_heapify(xpriority_queue_##T *container, size_t index);\
\
static enum x_stat xpriority_queue_##T##_new(xpriority_queue_##T **out, bool  (*cmp) (const T a, const T b)) \
{\
    struct xcontainer_config config;\
    init_xcontainer_config(&config);\
    return xpriority_queue_##T##_new_config(&config, out, cmp);\
}\
\
static enum x_stat xpriority_queue_##T##_new_max_size(xpriority_queue_##T **out, size_t max_size, bool  (*cmp) (const T a, const T b)) \
{\
    struct xcontainer_config config;\
    init_xcontainer_config_max_size(&config, max_size);\
    return xpriority_queue_##T##_new_config(&config, out, cmp);\
}\
\
static enum x_stat xpriority_queue_##T##_new_config(struct xcontainer_config * const config, xpriority_queue_##T **out, bool  (*cmp) (const T a, const T b)) \
{\
    size_t expansion_rate;\
    xpriority_queue_##T *container;\
    T *buffer;\
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
    container = (xpriority_queue_##T *) config->allocator.memory_calloc(1, sizeof(xpriority_queue_##T));\
    if (!container) {\
        return XTD_ALLOC_ERR;\
    }\
    buffer = (T *) config->allocator.memory_malloc(config->capacity * sizeof(T));\
    if (!buffer) {\
        config->allocator.memory_free(container);\
        return XTD_ALLOC_ERR;\
    }\
    container->capacity             = config->capacity;\
    container->expansion_rate       = config->expansion_rate;\
    container->max_size             = config->max_size;\
    container->size                 = 0;\
    container->memory_malloc         = config->allocator.memory_malloc;\
    container->memory_calloc        = config->allocator.memory_calloc;\
    container->memory_free          = config->allocator.memory_free;\
    container->cmp                  = cmp;\
    container->buffer               = buffer;\
    *out = container;\
    return XTD_OK;\
}\
\
static enum x_stat xpriority_queue_##T##_push(xpriority_queue_##T *container, T element)\
{\
    enum x_stat status;\
    size_t container_size;\
    T child;\
    T parent;\
    container_size = container->size;\
    if (container->size >= container->max_size) {\
        return XTD_MAX_SIZE_ERR;\
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
static enum x_stat xpriority_queue_##T##_peek(xpriority_queue_##T *container, T *out)\
{\
    if (container->size == 0) {\
        return XTD_OUT_OF_RANGE_ERR;\
    }\
    *out = container->buffer[0];\
    return XTD_OK;\
}\
\
static enum x_stat xpriority_queue_##T##_pop(xpriority_queue_##T *container, T *out)\
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
        return XTD_MAX_CAPACITY_ERR;\
    }\
    temp_capacity = container->capacity * container->expansion_rate;\
    if (temp_capacity <= container->capacity) {\
        container->capacity = container->max_size;\
    } else {\
        container->capacity = temp_capacity;\
    }\
    new_buffer = (T *) container->memory_malloc(temp_capacity * sizeof(T));\
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
\

/*
    
*/
#define SETUP_ITERATOR_FOR_XPRIORITY_QUEUE(T) \
\
static void xpriority_queue_iterator_##T##_reset_forward(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    iterator->forward_index = 0;\
}\
\
static void xpriority_queue_iterator_##T##_reset_backward(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    iterator->backward_index = ((xpriority_queue_##T *) iterator->container)->size-1;\
}\
\
static void xpriority_queue_iterator_##T##_reset(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    iterator->forward_index = 0;\
    iterator->backward_index = ((xpriority_queue_##T *) iterator->container)->size-1;\
}\
\
static void xpriority_queue_iterator_##T##_destroy(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xpriority_queue_##T *container;\
    if (iterator == XTD_NULL) {\
        return;\
    }\
    if (iterator->container != XTD_NULL) {\
        ((xpriority_queue_##T *) iterator->container)->memory_free(iterator);\
        return;\
    }\
    x_free(iterator);\
}\
\
static void xpriority_queue_iterator_##T##_advance_by(void *iterator_, size_t distance) {\
    XIterator *iterator = (XIterator *) iterator_;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    iterator->forward_index += distance;\
}\
\
static void xpriority_queue_iterator_##T##_decrement(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    iterator->forward_index--;\
}\
\
static void xpriority_queue_iterator_##T##_increment(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    iterator->forward_index++;\
}\
\
static bool xpriority_queue_iterator_##T##_has_next(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xpriority_queue_##T *container;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return FALSE;\
    }\
    container = (xpriority_queue_##T *) iterator->container;\
    return (iterator->forward_index < container->size);\
}\
\
static T xpriority_queue_iterator_##T##_next(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xpriority_queue_##T *container;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return XTD_NULL;\
    }\
    container = (xpriority_queue_##T *) iterator->container;\
    return container->buffer[iterator->forward_index++];\
}\
\
static bool xpriority_queue_iterator_##T##_has_prev(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xpriority_queue_##T *container;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return FALSE;\
    }\
    container = (xpriority_queue_##T *) iterator->container;\
    return (iterator->backward_index != -1 && ((iterator->backward_index <= container->size) || (iterator->backward_index = container->size-1) > 0));\
}\
\
static T xpriority_queue_iterator_##T##_prev(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xpriority_queue_##T *container;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return XTD_NULL;\
    }\
    container = (xpriority_queue_##T *) iterator->container;\
    return container->buffer[iterator->backward_index--];\
}\
\
static XIterator *xiterator_init_xpriority_queue_##T(xpriority_queue_##T *container) \
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
    iterator->has_next = xpriority_queue_iterator_##T##_has_next;\
    iterator->next = (xiterator_next) xpriority_queue_iterator_##T##_next;\
    iterator->has_prev = xpriority_queue_iterator_##T##_has_prev;\
    iterator->prev = (xiterator_prev) xpriority_queue_iterator_##T##_prev;\
    iterator->reset_forward = xpriority_queue_iterator_##T##_reset_forward;\
    iterator->reset_backward = xpriority_queue_iterator_##T##_reset_backward;\
    iterator->reset = xpriority_queue_iterator_##T##_reset;\
    iterator->destroy = xpriority_queue_iterator_##T##_destroy;\
    iterator->advance_by = xpriority_queue_iterator_##T##_advance_by;\
    iterator->increment = xpriority_queue_iterator_##T##_increment;\
    iterator->decrement = xpriority_queue_iterator_##T##_decrement;\
    iterator->container = container;\
    return iterator;\
}\
\
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
        container->memory_free((void *)container); \
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

/*
    
*/
#define SETUP_XPRIORITY_QUEUE_FOR(T) SETUP_XPRIORITY_QUEUE_ONLY_FOR(T) SETUP_ITERATOR_FOR_XPRIORITY_QUEUE(T)


#ifdef __cplusplus
}
#endif

#endif
