
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 19 June 2021
    \file xset.h
*/

#ifndef EXOTIC_XSET_H
#define EXOTIC_XSET_H

#ifdef __cplusplus
extern "C" {
#endif

#include "xcommon.h"
#include "xiterator.h"

#ifdef __cplusplus
#if !defined(ALLOW_XTD_TYPES_WITH_ALTERNATIVES_IN_CPP) && __cplusplus >= 201103L
    #warning Do not use this type in C++ 11 and above, use the std::set class instead
#endif
#endif

/*
    
*/
#define SETUP_XSET_ONLY_FOR(T) typedef struct xset_##T##_s { \
    size_t capacity;\
    size_t expansion_rate;\
    size_t size;\
    size_t max_size;\
    T *buffer;\
    bool (*element_equals)  (T first, T second);\
    bool (*element_greater_than)  (T first, T second);\
    void *(*memory_malloc)  (size_t size);\
    void *(*memory_calloc) (size_t blocks, size_t size);\
    void  (*memory_free)   (void *block);\
} xset_##T;\
\
static enum x_stat xset_##T##_new(xset_##T **out, bool (*xset_element_equals)  (T,T), bool (*xset_element_greater_than)  (T,T));\
static enum x_stat xset_##T##_new_config(struct xcontainer_config * const config, xset_##T **out, bool (*xset_element_equals)  (T,T), bool (*xset_element_greater_than)  (T,T));\
static enum x_stat xset_##T##_get_at(xset_##T *container, size_t index, T *out);\
static enum x_stat xset_##T##_get_front(xset_##T *container, T *out);\
static enum x_stat xset_##T##_get_back(xset_##T *container, T *out);\
static enum x_stat xset_##T##_add(xset_##T *container, T element);\
static enum x_stat xset_##T##_index_of(xset_##T *container, T element, size_t *out);\
static enum x_stat xset_##T##_expand_capacity(xset_##T *container);\
\
static enum x_stat xset_##T##_new(xset_##T **out, bool (*xset_element_equals)  (T,T), bool (*xset_element_greater_than)  (T,T)) \
{\
    struct xcontainer_config config;\
    init_xcontainer_config(&config);\
    return xset_##T##_new_config(&config, out, xset_element_equals, xset_element_greater_than);\
}\
\
static enum x_stat xset_##T##_new_max_size(xset_##T **out, size_t max_size, bool (*xset_element_equals)  (T,T), bool (*xset_element_greater_than)  (T,T)) \
{\
    struct xcontainer_config config;\
    init_xcontainer_config_max_size(&config, max_size);\
    return xset_##T##_new_config(&config, out, xset_element_equals, xset_element_greater_than);\
}\
\
static enum x_stat xset_##T##_new_config(struct xcontainer_config * const config, xset_##T **out, bool (*xset_element_equals)  (T,T), bool (*xset_element_greater_than)  (T,T)) \
{\
    size_t expansion_rate;\
    xset_##T *container;\
    T *buffer;\
    if (config->expansion_rate <= 1) {\
        expansion_rate = XDEFAULT_CONTAINER_EXPANSION_RATE;\
    } else {\
        expansion_rate = config->expansion_rate;\
    }\
    if ((!config->capacity || expansion_rate >= (config->max_size / config->capacity)) && (config->max_size < config->capacity)) {\
        return XTD_INVALID_CAPACITY_ERR;\
    }\
    container = (xset_##T *) config->allocator.memory_calloc(1, sizeof(xset_##T));\
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
    container->element_equals       = xset_element_equals;\
    container->element_greater_than = xset_element_greater_than;\
    container->memory_malloc        = config->allocator.memory_malloc;\
    container->memory_calloc        = config->allocator.memory_calloc;\
    container->memory_free          = config->allocator.memory_free;\
    container->buffer               = buffer;\
    *out = container;\
    return XTD_OK;\
}\
\
static enum x_stat xset_##T##_add_at(xset_##T *container, T element, size_t index);\
\
static enum x_stat xset_##T##_add(xset_##T *container, T element)\
{\
    T last_element;\
    size_t index;\
    enum x_stat status;\
    if (container->size >= container->max_size) {\
        return XTD_MAX_SIZE_ERR;\
    }\
    if (xset_##T##_index_of(container, element, &index) == XTD_OK) {\
        return XTD_ALREADY_IN_CONTAINER_ERR;\
    }\
    if (container->size >= container->capacity) {\
        status = xset_##T##_expand_capacity(container);\
        if (status != XTD_OK) {\
            return status;\
        }\
    }\
    if (container->element_greater_than != XTD_NULL) {\
        for (index = 0; index < container->size; ++index) {\
            if (xset_##T##_get_at(container, index, &last_element) == XTD_OK) {\
                int is_greater = container->element_greater_than(last_element, element);\
                if (is_greater) {\
                    container->buffer[index] = element;\
                    element = last_element;\
                    xset_##T##_add_at(container, last_element, index+1);\
                    return XTD_OK;\
                }\
            }\
        }\
    }\
    container->buffer[container->size] = element;\
    ++container->size;\
    return XTD_OK;\
}\
\
static enum x_stat xset_##T##_add_at(xset_##T *container, T element, size_t index) \
{\
    size_t ele_pos;\
    size_t num;\
    enum x_stat status;\
    if (index == container->size) {\
        return xset_##T##_add(container, element);\
    }\
    if ((container->size == 0 && index != 0) || index > (container->size - 1)) {\
        return XTD_INDEX_OUT_OF_RANGE_ERR;\
    }\
    if (container->size >= container->max_size) {\
        return XTD_MAX_SIZE_ERR;\
    }\
    if (xset_##T##_index_of(container, element, &ele_pos) == XTD_OK) {\
        return XTD_ALREADY_IN_CONTAINER_ERR;\
    }\
    if (container->size >= container->capacity) {\
        status = xset_##T##_expand_capacity(container);\
        if (status != XTD_OK) {\
            return status;\
        }\
    }\
    num = (container->size - index) * sizeof(void*);\
    memmove(&(container->buffer[index + 1]),\
            &(container->buffer[index]),\
            num);\
    container->buffer[index] = element;\
    ++container->size;\
    return XTD_OK;\
}\
\
static enum x_stat xset_##T##_index_of(xset_##T *container, T element, size_t *out)\
{\
    int index;\
    if (!out) {\
        return XTD_OUT_PARAM_NULL_ERR;\
    }\
    for (index = 0; index < container->size; index++) {\
        if (container->element_equals(container->buffer[index], element)) {\
            *out = index;\
            return XTD_OK;\
        }\
    }\
    return XTD_OUT_OF_RANGE_ERR;\
}\
\
static bool xset_##T##_contains(xset_##T *container, T element)\
{\
    size_t iter_index;\
    for (iter_index = 0; iter_index < container->size; iter_index++) {\
        if (container->buffer[iter_index] == element) {\
            return TRUE;\
        }\
    }\
    return FALSE;\
}\
\
static size_t xset_##T##_element_count(xset_##T *container, T element)\
{\
    size_t iter_index;\
    size_t occurence_count = 0;\
    for (iter_index = 0; iter_index < container->size; iter_index++) {\
        if (container->buffer[iter_index] == element) occurence_count++;\
    }\
    return occurence_count;\
}\
\
static enum x_stat xset_##T##_get_at(xset_##T *container, size_t index, T *out)\
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
static enum x_stat xset_##T##_get_front(xset_##T *container, T *out)\
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
static enum x_stat xset_##T##_get_back(xset_##T *container, T *out)\
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
static enum x_stat xset_##T##_replace_at(xset_##T *container, size_t index, T element, T *out)\
{\
    if (index >= container->size) {\
        return XTD_INDEX_OUT_OF_RANGE_ERR;\
    }\
    if (out) {\
        *out = container->buffer[index];\
    }\
    container->buffer[index] = element;\
    return XTD_OK;\
}\
\
static enum x_stat xset_##T##_remove_at(xset_##T *container, size_t index, T *out)\
{\
    size_t mem_size;\
    if (index < 0 || index >= container->size) {\
        return XTD_INDEX_OUT_OF_RANGE_ERR;\
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
static enum x_stat xset_##T##_remove_front(xset_##T *container, T *out)\
{\
    return xset_##T##_remove_at(container, 0, out);\
}\
\
static enum x_stat xset_##T##_remove_back(xset_##T *container, T *out)\
{\
    return xset_##T##_remove_at(container, container->size-1, out);\
}\
\
static enum x_stat xset_##T##_clear(xset_##T *container)\
{\
    enum x_stat status;\
    while (container->size > 0) {\
        status = xset_##T##_remove_at(container, (container->size)-1, XTD_NULL);\
        if (status != XTD_OK) {\
            return status;\
        }\
    }\
    return XTD_OK;\
}\
\
static enum x_stat xset_##T##_shrink_to_fit(xset_##T *container)\
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
static enum x_stat xset_##T##_expand_capacity(xset_##T *container)\
{\
    size_t tmp_capacity;\
    T *new_buffer;\
    if (container->capacity >= XTD_CONTAINER_MAX_CAPACITY) {\
        return XTD_MAX_CAPACITY_ERR;\
    }\
    tmp_capacity = container->capacity * container->expansion_rate;\
    if (tmp_capacity <= container->capacity) {\
        container->capacity = container->max_size;\
    } else {\
        container->capacity = tmp_capacity;\
    }\
    new_buffer = (T *) container->memory_malloc(tmp_capacity * sizeof(T));\
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
\

/*
    
*/
#define SETUP_ITERATOR_FOR_XSET(T) \
\
static void xset_iterator_##T##_reset_forward(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    iterator->forward_index = 0;\
}\
\
static void xset_iterator_##T##_reset_backward(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    iterator->backward_index = ((xset_##T *) iterator->container)->size-1;\
}\
\
static void xset_iterator_##T##_reset(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    iterator->forward_index = 0;\
    iterator->backward_index = ((xset_##T *) iterator->container)->size-1;\
}\
\
static void xset_iterator_##T##_destroy(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    if (iterator == XTD_NULL) {\
        return;\
    }\
    if (iterator->container != XTD_NULL) {\
        ((xset_##T *) iterator->container)->memory_free(iterator);\
        return;\
    }\
    x_free(iterator);\
}\
\
static void xset_iterator_##T##_advance_by(void *iterator_, size_t distance) {\
    XIterator *iterator = (XIterator *) iterator_;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    iterator->forward_index += distance;\
}\
\
static void xset_iterator_##T##_decrement(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    iterator->forward_index--;\
}\
\
static void xset_iterator_##T##_increment(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    iterator->forward_index++;\
}\
\
static bool xset_iterator_##T##_has_next(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xset_##T *container;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return FALSE;\
    }\
    container = (xset_##T *) iterator->container;\
    return (container != XTD_NULL && iterator->forward_index < container->size);\
}\
\
static void *xset_iterator_##T##_next(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xset_##T *container;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return XTD_NULL;\
    }\
    container = (xset_##T *) iterator->container;\
    return (void *) container->buffer[iterator->forward_index++];\
}\
\
static bool xset_iterator_##T##_has_prev(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xset_##T *container;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return FALSE;\
    }\
    container = (xset_##T *) iterator->container;\
    return (container != XTD_NULL && iterator->backward_index != -1 && ((iterator->backward_index <= container->size) || (iterator->backward_index = container->size-1) > 0));\
}\
\
static void *xset_iterator_##T##_prev(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xset_##T *container;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return XTD_NULL;\
    }\
    container = (xset_##T *) iterator->container;\
    return (void *) container->buffer[iterator->backward_index--];\
}\
\
static XIterator *xiterator_init_xset_##T(xset_##T *container) \
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
    iterator->has_next = xset_iterator_##T##_has_next;\
    iterator->next = xset_iterator_##T##_next;\
    iterator->has_prev = xset_iterator_##T##_has_prev;\
    iterator->prev = xset_iterator_##T##_prev;\
    iterator->reset_forward = xset_iterator_##T##_reset_forward;\
    iterator->reset_backward = xset_iterator_##T##_reset_backward;\
    iterator->reset = xset_iterator_##T##_reset;\
    iterator->destroy = xset_iterator_##T##_destroy;\
    iterator->advance_by = xset_iterator_##T##_advance_by;\
    iterator->increment = xset_iterator_##T##_increment;\
    iterator->decrement = xset_iterator_##T##_decrement;\
    iterator->container = container;\
    return iterator;\
}\
\
\
\

/**

*/
#define xset(T) xset_##T

/**

*/
#define xset_new(T) xset_##T##_new

/**

*/
#define xset_new_max_size(T) xset_##T##_new_max_size

/**

*/
#define xset_new_config(T) xset_##T##_new_config

/**

*/
#define xset_index_of(T) xset_##T##_index_of

/**

*/
#define xset_contains(T) xset_##T##_contains

/**

*/
#define xset_element_count(T) xset_##T##_element_count

/**

*/
#define xset_add(T) xset_##T##_add

/**

*/
#define xset_add_at(T) xset_##T##_add_at

/**

*/
#define xset_get_at(T) xset_##T##_get_at

/**

*/
#define xset_get_front(T) xset_##T##_get_front

/**

*/
#define xset_get_back(T) xset_##T##_get_back

/**

*/
#define xset_replace_at(T) xset_##T##_replace_at

/**

*/
#define xset_remove_front(T) xset_##T##_remove_front

/**

*/
#define xset_remove_back(T) xset_##T##_remove_back

/**

*/
#define xset_remove_at(T) xset_##T##_remove_at

/**

*/
#define xset_clear(T) xset_##T##_clear

/**

*/
#define xset_shrink_to_fit(T) xset_##T##_shrink_to_fit

/**

*/
#define xset_destroy(container) { \
        container->memory_free(container->buffer); \
        container->memory_free((void *)container); \
    }

/**

*/
#define xiterator_init_xset(T) xiterator_init_xset_##T

/*

*/
#define xset_capacity xcapacity

/*

*/
#define xset_size xsize

/*

*/
#define xset_max_size xmax_size

/*

*/
#define xset_is_empty xis_empty

/*

*/
#define SETUP_XSET_FOR(T) SETUP_XSET_ONLY_FOR(T) SETUP_ITERATOR_FOR_XSET(T)


#ifdef __cplusplus
}
#endif

#endif
