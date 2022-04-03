
/**
    \copyright MIT License Copyright (c) 2022, Adewale Azeez 
    \author Adewale Azeez <iamthecarisma@gmail.com>
    \date 27 March 2022
    \file xcircular_buffer.c
*/

#ifndef EXOTIC_XCIRCULAR_BUFFER_H
#define EXOTIC_XCIRCULAR_BUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "xcommon.h"
#include "xiterator.h"

/*
    
*/
#define SETUP_XCIRCULAR_BUFFER_ONLY_FOR(T) typedef struct xcircular_buffer_##T##_s { \
    size_t capacity;\
    size_t size;\
    size_t head_index;\
    size_t tail_index;\
    T *buffer;\
    void *(*memory_malloc)  (size_t size);\
    void *(*memory_calloc) (size_t blocks, size_t size);\
    void  (*memory_free)   (void *block);\
} xcircular_buffer_##T;\
\
static enum x_stat xcircular_buffer_##T##_new_config(struct xcontainer_config * const config, xcircular_buffer_##T **out);\
\
static enum x_stat xcircular_buffer_##T##_new(xcircular_buffer_##T **out, size_t capacity) \
{\
    struct xcontainer_config config;\
    init_xcontainer_config(&config);\
    config.capacity = capacity;\
    return xcircular_buffer_##T##_new_config(&config, out);\
}\
\
static enum x_stat xcircular_buffer_##T##_new_config(struct xcontainer_config * const config, xcircular_buffer_##T **out) \
{\
    size_t expansion_rate;\
    xcircular_buffer_##T *container;\
    T *buffer;\
    if (config->expansion_rate <= 1) {\
        expansion_rate = XDEFAULT_CONTAINER_EXPANSION_RATE;\
    } else {\
        expansion_rate = config->expansion_rate;\
    }\
    if ((!config->capacity || expansion_rate >= (config->max_size / config->capacity)) && (config->max_size < config->capacity)) {\
        return XTD_INVALID_CAPACITY_ERR;\
    }\
    container = (xcircular_buffer_##T *) config->allocator.memory_calloc(1, sizeof(xcircular_buffer_##T));\
    if (!container) {\
        return XTD_ALLOC_ERR;\
    }\
    buffer = (T *) config->allocator.memory_malloc(config->capacity * sizeof(T));\
    if (!buffer) {\
        config->allocator.memory_free(container);\
        return XTD_ALLOC_ERR;\
    }\
    container->capacity             = config->capacity;\
    container->size                 = 0;\
    container->head_index           = 0;\
    container->tail_index           = 0;\
    container->memory_malloc        = config->allocator.memory_malloc;\
    container->memory_calloc        = config->allocator.memory_calloc;\
    container->memory_free          = config->allocator.memory_free;\
    container->buffer               = buffer;\
    *out = container;\
    return XTD_OK;\
}\
\
static enum x_stat xcircular_buffer_##T##_add(xcircular_buffer_##T *container, T element) \
{\
    size_t num;\
    enum x_stat status;\
    if (container->size >= container->capacity) {\
        return XTD_MAX_CAPACITY_ERR;\
    }\
    container->tail_index = (container->tail_index) % container->capacity;\
    container->buffer[container->tail_index++] = element;\
    if (container->size < container->capacity) ++container->size;\
    return XTD_OK;\
}\
\
static enum x_stat xcircular_buffer_##T##_enqueue(xcircular_buffer_##T *container, T element) \
{\
    size_t num;\
    enum x_stat status;\
    container->tail_index = (container->tail_index) % container->capacity;\
    container->buffer[container->tail_index++] = element;\
    if (container->size < container->capacity) ++container->size;\
    return XTD_OK;\
}\
\
static enum x_stat xcircular_buffer_##T##_enqueue_cb(xcircular_buffer_##T *container, T element, void (*xcircular_buffer_enqueue_cb_fn)  (T)) \
{\
    size_t num;\
    enum x_stat status;\
    container->tail_index = (container->tail_index) % container->capacity;\
    if (xcircular_buffer_enqueue_cb_fn != XTD_NULL && container->size >= container->capacity) {\
        xcircular_buffer_enqueue_cb_fn(container->buffer[container->tail_index]);\
    }\
    container->buffer[container->tail_index++] = element;\
    if (container->size < container->capacity) ++container->size;\
    return XTD_OK;\
}\
\
static enum x_stat xcircular_buffer_##T##_get_at(xcircular_buffer_##T *container, size_t index, T *out) \
{\
    if (!out) {\
        return XTD_OUT_PARAM_NULL_ERR;\
    }\
    if (index >= container->size) {\
        return XTD_INDEX_OUT_OF_RANGE_ERR;\
    }\
    *out = container->buffer[index];\
    return XTD_OK;\
}\
\
static enum x_stat xcircular_buffer_##T##_get(xcircular_buffer_##T *container, T *out) \
{\
    return xcircular_buffer_##T##_get_at(container, container->head_index, out);\
}\
\
static enum x_stat xcircular_buffer_##T##_dequeue_at(xcircular_buffer_##T *container, size_t index, T *out) \
{\
    size_t mem_size;\
    if (index < 0 || index >= container->size) {\
        return XTD_INDEX_OUT_OF_RANGE_ERR;\
    }\
    if (!out) {\
        return XTD_OUT_PARAM_NULL_ERR;\
    }\
    container->head_index = (index) % container->capacity;\
    *out = container->buffer[container->head_index];\
    if (index != container->size) {\
        mem_size = (container->size - 1 - index) * sizeof(T);\
        memmove(&(container->buffer[index]), &(container->buffer[index + 1]), mem_size);\
    }\
    --container->size;\
    return XTD_OK;\
}\
\
static enum x_stat xcircular_buffer_##T##_dequeue(xcircular_buffer_##T *container, T *out) \
{\
    if (container->size == 0) {\
        return XTD_INDEX_OUT_OF_RANGE_ERR;\
    }\
    if (!out) {\
        return XTD_OUT_PARAM_NULL_ERR;\
    }\
    container->head_index = (container->head_index) % container->capacity;\
    *out = container->buffer[container->head_index++];\
    --container->size;\
    return XTD_OK;\
}\
\
\
\
// _should shift the others forward, and remove the last index;
// xcircular_buffer_add return the status XTD_MAX_CAPACITY_ERR if the buffer is full
// xcircular_buffer_enqueue simply replaces the oldest data in the queue
// _enqueue_cb report the removed element before replacing it
// _dequeue_at and _dequeue should invalidate the removed index or assign to NULL not just shift memory

/*
    
*/
#define SETUP_ITERATOR_FOR_XCIRCULAR_BUFFER(T) \
\
\
\

/**

*/
#define xcircular_buffer(T) xcircular_buffer_##T

/**

*/
#define xcircular_buffer_new(T) xcircular_buffer_##T##_new

/**

*/
#define xcircular_buffer_new_config(T) xcircular_buffer_##T##_new_config

/**

*/
#define xcircular_buffer_add(T) xcircular_buffer_##T##_add

/**

*/
#define xcircular_buffer_enqueue(T) xcircular_buffer_##T##_enqueue

/**

*/
#define xcircular_buffer_enqueue_cb(T) xcircular_buffer_##T##_enqueue_cb

/**

*/
#define xcircular_buffer_enqueue_is_full(container) (container->size == container->capacity)

/**

*/
#define xcircular_buffer_enqueue_is_empty(container) (!(xcircular_buffer_enqueue_is_full(container)))

/**

*/
#define xcircular_buffer_get_at(T) xcircular_buffer_##T##_get_at

/**

*/
#define xcircular_buffer_get(T) xcircular_buffer_##T##_get

/**

*/
#define xcircular_buffer_dequeue_at(T) xcircular_buffer_##T##_dequeue_at

/**

*/
#define xcircular_buffer_dequeue(T) xcircular_buffer_##T##_dequeue

/**

*/
#define xcircular_buffer_destroy(container) { \
        container->memory_free(container->buffer); \
        container->memory_free((void *)container); \
    }

/**

*/
#define xiterator_init_xcircular_buffer(T) xiterator_init_xcircular_buffer_##T

/*

*/
#define xcircular_buffer_capacity xcapacity

/*

*/
#define xcircular_buffer_size xsize

/*

*/
#define xcircular_buffer_max_size xmax_size

/*

*/
#define xcircular_buffer_is_empty xis_empty

/**

*/
#define SETUP_XCIRCULAR_BUFFER_FOR(T) SETUP_XCIRCULAR_BUFFER_ONLY_FOR(T) SETUP_ITERATOR_FOR_XCIRCULAR_BUFFER(T)
    


#ifdef __cplusplus
}
#endif

#endif
