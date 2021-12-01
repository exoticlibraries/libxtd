
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <iamthecarisma@gmail.com>
    \date 23 January 2021
    \file xqueue.h
*/

#ifndef EXOTIC_XQUEUE_H
#define EXOTIC_XQUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "xcommon.h"
#include "xiterator.h"
#include "xdeque.h"

#ifdef __cplusplus
#if !defined(ALLOW_XTD_TYPES_WITH_ALTERNATIVES_IN_CPP) && __cplusplus >= 201103L
    #warning Do not use this type in C++ 03 and above, use the std::queue class instead
#endif
#endif

/**
    NEVER EVER SWAP BUFFER OF XQUEUE to prevent dangling pointers, 
    except your swap function will take care of the internal 
    impl container
*/
#define SETUP_ONLY_XQUEUE_FOR(T)  typedef struct xqueue_##T##_s { \
    size_t capacity;\
    size_t size;\
    size_t max_size;\
    T *buffer;\
    void *(*memory_malloc)  (size_t size);\
    void *(*memory_calloc) (size_t blocks, size_t size);\
    void  (*memory_free)   (void *block);\
    \
    xdeque(T) *xinternal_e7884708734_ximpl;\
} xqueue_##T;\
\
static enum x_stat xqueue_##T##_new_config(struct xcontainer_config * const config, xqueue_##T **out);\
\
static enum x_stat xqueue_##T##_new(xqueue_##T **out) \
{\
    struct xcontainer_config config;\
    init_xcontainer_config(&config);\
    return xqueue_##T##_new_config(&config, out);\
}\
\
static enum x_stat xqueue_##T##_new_max_size(xqueue_##T **out, size_t max_size) \
{\
    struct xcontainer_config config;\
    init_xcontainer_config_max_size(&config, max_size);\
    return xqueue_##T##_new_config(&config, out);\
}\
\
static enum x_stat xqueue_##T##_new_config(struct xcontainer_config * const config, xqueue_##T **out) \
{\
    enum x_stat xinternal_vector_status;\
    xdeque_##T *xinternal_vector;\
    xqueue_##T *container;\
    container = (xqueue_##T *) config->allocator.memory_calloc(1, sizeof(xqueue_##T));\
    if (!container) {\
        return XTD_ALLOC_ERR;\
    }\
    xinternal_vector_status = xdeque_##T##_new_config(config, &xinternal_vector);\
    if (xinternal_vector_status != XTD_OK) {\
        config->allocator.memory_free(container);\
        return xinternal_vector_status;\
    }\
    container->capacity         = config->capacity;\
    container->max_size         = config->max_size;\
    container->size             = 0;\
    container->xinternal_e7884708734_ximpl = xinternal_vector;\
    container->buffer           = xinternal_vector->buffer;\
    container->memory_malloc     = config->allocator.memory_malloc;\
    container->memory_calloc    = config->allocator.memory_calloc;\
    container->memory_free      = config->allocator.memory_free;\
    *out = container;\
    return XTD_OK;\
}\
\
static enum x_stat xqueue_##T##_push(xqueue_##T *container, T element)\
{\
    enum x_stat status;\
    if (container->size >= container->max_size) {\
        return XTD_MAX_SIZE_ERR;\
    }\
    status = xdeque_##T##_add_back(container->xinternal_e7884708734_ximpl, element);\
    if (status == XTD_OK) {\
        container->buffer = container->xinternal_e7884708734_ximpl->buffer;\
        container->capacity = container->xinternal_e7884708734_ximpl->capacity;\
        container->size = container->xinternal_e7884708734_ximpl->size;\
    }\
    return status;\
}\
\
static enum x_stat xqueue_##T##_peek(xqueue_##T *container, T *element)\
{\
    return xdeque_##T##_get_front(container->xinternal_e7884708734_ximpl, element);\
}\
\
static enum x_stat xqueue_##T##_pop(xqueue_##T *container, T *element)\
{\
    enum x_stat status;\
    if (container->size == 0) {\
        return XTD_EMPTY_CONTAINER_ERR;\
    }\
    status = xdeque_##T##_remove_front(container->xinternal_e7884708734_ximpl, element);\
    if (status == XTD_OK) {\
        container->buffer = container->xinternal_e7884708734_ximpl->buffer;\
        container->capacity = container->xinternal_e7884708734_ximpl->capacity;\
        container->size = container->xinternal_e7884708734_ximpl->size;\
    }\
    return status;\
}\
\
\
\

/*
    
*/
#define SETUP_ITERATOR_FOR_XQUEUE(T) SETUP_ITERATOR_FOR_XDEQUE(T) \
\
static XIterator *xiterator_init_xqueue_##T(xqueue_##T *container) \
{\
    return xiterator_init_xdeque_##T(container->xinternal_e7884708734_ximpl);\
}\
\
\
\

/**

*/
#define xqueue(T) xqueue_##T

/**

*/
#define xqueue_new(T) xqueue_##T##_new

/**

*/
#define xqueue_new_max_size(T) xqueue_##T##_new_max_size

/**

*/
#define xqueue_new_config(T) xqueue_##T##_new_config

/**

*/
#define xqueue_push(T) xqueue_##T##_push

/**

*/
#define xqueue_enqueue xqueue_push

/**

*/
#define xqueue_peek(T) xqueue_##T##_peek

/**

*/
#define xqueue_pop(T) xqueue_##T##_pop

/**

*/
#define xqueue_dequeue xqueue_pop

/**

*/
#define xqueue_destroy(container) { \
        container->memory_free(container->xinternal_e7884708734_ximpl->buffer); \
        container->memory_free(container->xinternal_e7884708734_ximpl); \
        container->memory_free((void *)container); \
    }

/*

*/
#define xqueue_capacity xcapacity

/*

*/
#define xqueue_size xsize

/*

*/
#define xqueue_max_size xmax_size

/*

*/
#define xqueue_is_empty xis_empty

/**

*/
#define SETUP_XQUEUE_FOR(T) SETUP_XDEQUE_ONLY_FOR(T) SETUP_ONLY_XQUEUE_FOR(T) SETUP_ITERATOR_FOR_XQUEUE(T)
    


#ifdef __cplusplus
}
#endif

#endif
