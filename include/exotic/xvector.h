
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 20 December 2020
    \file xvector.h
*/

#ifndef EXOTIC_XVECTOR_H
#define EXOTIC_XVECTOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "xcommon.h"
#include "xiterator.h"

#ifdef __cplusplus
#if !defined(ALLOW_XTD_TYPES_WITH_ALTERNATIVES_IN_CPP) && __cplusplus >= 201103L
    #warning Do not use this type in C++ 11 and above, use the std::vector class instead
#endif
#define NULL 0
#endif

/*
    
*/
#define SETUP_XVECTOR_FOR(T) typedef struct xvector_##T##_s { \
    size_t capacity;\
    size_t expansion_rate;\
    size_t size;\
    size_t max_size;\
    T *buffer;\
    XIterator *iter;\
    void *(*memory_alloc)  (size_t size);\
    void *(*memory_calloc) (size_t blocks, size_t size);\
    void  (*memory_free)   (void *block);\
} xvector_##T;\
\
enum x_stat xvector_##T##_new(xvector_##T **out);\
enum x_stat xvector_##T##_new_config(struct xcontainer_config * const config, xvector_##T **out);\
enum x_stat xvector_##T##_add(xvector_##T *container, T element);\
static enum x_stat xvector_##T##_expand_capacity(xvector_##T *container);\
\
enum x_stat xvector_##T##_new(xvector_##T **out) \
{\
    struct xcontainer_config config;\
    init_xcontainer_config(&config);\
    return xvector_##T##_new_config(&config, out);\
}\
\
enum x_stat xvector_##T##_new_max_size(xvector_##T **out, size_t max_size) \
{\
    struct xcontainer_config config;\
    init_xcontainer_config_max_size(&config, max_size);\
    return xvector_##T##_new_config(&config, out);\
}\
\
enum x_stat xvector_##T##_new_config(struct xcontainer_config * const config, xvector_##T **out) \
{\
    size_t expansion_rate;\
    xvector_##T *container;\
    T *buffer;\
    XIterator *iter;\
    if (config->expansion_rate <= 1) {\
        expansion_rate = XDEFAULT_CONTAINER_EXPANSION_RATE;\
    } else {\
        expansion_rate = config->expansion_rate;\
    }\
    if ((!config->capacity || expansion_rate >= (config->max_size / config->capacity)) && (config->max_size < config->capacity)) {\
        return XTD_INVALID_CAPACITY_ERR;\
    }\
    container = (xvector_##T *) config->memory_calloc(1, sizeof(xvector_##T));\
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
    container->buffer               = buffer;\
    container->iter                 = iter;\
    container->iter->index          = 0;\
    container->iter->backward_index = 0;\
    *out = container;\
    return XTD_OK;\
}\
\
enum x_stat xvector_##T##_add(xvector_##T *container, T element)\
{\
    enum x_stat status;\
    if (container->size >= container->max_size) {\
        return XTD_MAXTD_SIZE_ERR;\
    }\
    if (container->size >= container->capacity) {\
        status = xvector_##T##_expand_capacity(container);\
        if (status != XTD_OK) {\
            return status;\
        }\
    }\
    container->buffer[container->size] = element;\
    ++container->size;\
    return XTD_OK;\
}\
\
enum x_stat xvector_##T##_add_at(xvector_##T *container, T item, size_t index) \
{\
    size_t num;\
    enum x_stat status;\
    if (index == container->size) {\
        return xvector_##T##_add(container, item);\
    }\
    if ((container->size == 0 && index != 0) || index > (container->size - 1)) {\
        return XTD_INDEXTD_OUT_OF_RANGE_ERR;\
    }\
    if (container->size >= container->max_size) {\
        return XTD_MAXTD_SIZE_ERR;\
    }\
    if (container->size >= container->capacity) {\
        status = xvector_##T##_expand_capacity(container);\
        if (status != XTD_OK) {\
            return status;\
        }\
    }\
    num = (container->size - index) * sizeof(void*);\
    memmove(&(container->buffer[index + 1]),\
            &(container->buffer[index]),\
            num);\
    container->buffer[index] = item;\
    ++container->size;\
    return XTD_OK;\
}\
\
enum x_stat xvector_##T##_get_at(xvector_##T *container, int index, T *out)\
{\
    if (!out) {\
        return XTD_OUT_PARAM_NULL_ERR;\
    }\
    if (index >= container->size) {\
        return XTD_INDEXTD_OUT_OF_RANGE_ERR;\
    }\
    *out = container->buffer[index];\
    return XTD_OK;\
}\
\
enum x_stat xvector_##T##_get_front(xvector_##T *container, T *out)\
{\
    if (!out) {\
        return XTD_OUT_PARAM_NULL_ERR;\
    }\
    if (container->size == 0) {\
        return XTD_EMPTY_CONTAINER_ERR;\
    }\
    *out = container->buffer[0];\
    return XTD_OK;\
}\
\
enum x_stat xvector_##T##_get_back(xvector_##T *container, T *out)\
{\
    if (!out) {\
        return XTD_OUT_PARAM_NULL_ERR;\
    }\
    if (container->size == 0) {\
        return XTD_EMPTY_CONTAINER_ERR;\
    }\
    *out = container->buffer[container->size-1];\
    return XTD_OK;\
}\
\
enum x_stat xvector_##T##_replace_at(xvector_##T *container, size_t index, T element, T *out)\
{\
    if (index >= container->size) {\
        return XTD_INDEXTD_OUT_OF_RANGE_ERR;\
    }\
    if (out) {\
        *out = container->buffer[index];\
    }\
    container->buffer[index] = element;\
    return XTD_OK;\
}\
\
enum x_stat xvector_##T##_remove_at(xvector_##T *container, size_t index, T *out)\
{\
    size_t mem_size;\
    if (index < 0 || index >= container->size) {\
        return XTD_INDEXTD_OUT_OF_RANGE_ERR;\
    }\
    if (out) {\
        *out = container->buffer[index];\
    }\
    if (index != container->size) {\
        mem_size = (container->size - 1 - index) * sizeof(T);\
        memmove(&(container->buffer[index]), &(container->buffer[index + 1]), mem_size);\
    }\
    --container->size;\
    return XTD_OK;\
}\
\
enum x_stat xvector_##T##_remove_front(xvector_##T *container, T *out)\
{\
    return xvector_##T##_remove_at(container, 0, out);\
}\
\
enum x_stat xvector_##T##_remove_back(xvector_##T *container, T *out)\
{\
    return xvector_##T##_remove_at(container, container->size-1, out);\
}\
\
enum x_stat xvector_##T##_clear(xvector_##T *container)\
{\
    enum x_stat status;\
    while (container->size > 0) {\
        status = xvector_##T##_remove_at(container, (container->size)-1, NULL);\
        if (status != XTD_OK) {\
            return status;\
        }\
    }\
    return XTD_OK;\
}\
\
static enum x_stat xvector_##T##_shrink_to_fit(xvector_##T *container)\
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
static enum x_stat xvector_##T##_expand_capacity(xvector_##T *container)\
{\
    size_t tmp_capacity;\
    T *new_buffer;\
    if (container->capacity >= XTD_CONTAINER_MAXTD_CAPACITY) {\
        return XTD_MAXTD_CAPACITY_ERR;\
    }\
    tmp_capacity = container->capacity * container->expansion_rate;\
    if (tmp_capacity <= container->capacity) {\
        container->capacity = container->max_size;\
    } else {\
        container->capacity = tmp_capacity;\
    }\
    new_buffer = (T *) container->memory_alloc(tmp_capacity * sizeof(T));\
    if (!new_buffer) {\
        return XTD_ALLOC_ERR;\
    }\
    memcpy(new_buffer, container->buffer, container->size * sizeof(T));\
    container->memory_free(container->buffer);\
    container->buffer = new_buffer;\
    return XTD_OK;\
}\
\
\

/**

*/
#define xvector(T) xvector_##T

/**

*/
#define xvector_new(T) xvector_##T##_new

/**

*/
#define xvector_new_max_size(T) xvector_##T##_new_max_size

/**

*/
#define xvector_new_config(T) xvector_##T##_new_config

/**

*/
#define xvector_add(T) xvector_##T##_add

/**

*/
#define xvector_add_at(T) xvector_##T##_add_at

/**

*/
#define xvector_get_at(T) xvector_##T##_get_at

/**

*/
#define xvector_get_front(T) xvector_##T##_get_front

/**

*/
#define xvector_get_back(T) xvector_##T##_get_back

/**

*/
#define xvector_replace_at(T) xvector_##T##_replace_at

/**

*/
#define xvector_remove_front(T) xvector_##T##_remove_front

/**

*/
#define xvector_remove_back(T) xvector_##T##_remove_back

/**

*/
#define xvector_remove_at(T) xvector_##T##_remove_at

/**

*/
#define xvector_clear(T) xvector_##T##_clear

/**

*/
#define xvector_shrink_to_fit(T) xvector_##T##_shrink_to_fit

/**

*/
#define xvector_destroy(container) { \
        container->memory_free(container->buffer); \
        container->memory_free(container->iter); \
        container->memory_free(container); \
    }

/*

*/
#define xvector_capacity xcapacity

/*

*/
#define xvector_size xsize

/*

*/
#define xvector_max_size xmax_size

/*

*/
#define xvector_is_empty xis_empty


#ifdef __cplusplus
}
#endif

#endif
