
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 21 December 2020
    \file xstack.h
*/

#ifndef EXOTIC_XSTACK_H
#define EXOTIC_XSTACK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "xcommon.h"
#include "xiterator.h"
#include "xdeque.h"

#ifdef __cplusplus
#if !defined(ALLOW_XTD_TYPES_WITH_ALTERNATIVES_IN_CPP) && __cplusplus >= 201103L
    #warning Do not use this type in C++ 03 and above, use the std::stack class instead
#endif
#define NULL 0
#endif

/**
    NEVER EVER SWAP BUFFER OF XSTACK to prevent dangling pointers, 
    except your swap function will take care of the internal 
    impl container
*/
#define SETUP_ONLY_XSTACK_FOR(T)  typedef struct xstack_##T##_s { \
    size_t capacity;\
    size_t size;\
    size_t max_size;\
    T *buffer;\
    XIterator *iter;\
    void *(*memory_alloc)  (size_t size);\
    void *(*memory_calloc) (size_t blocks, size_t size);\
    void  (*memory_free)   (void *block);\
    \
    xdeque_##T *xinternal_e7884708734_ximpl;\
} xstack_##T;\
\
enum x_stat xstack_##T##_new_config(struct xcontainer_config * const config, xstack_##T **out);\
\
enum x_stat xstack_##T##_new(xstack_##T **out) \
{\
    struct xcontainer_config config;\
    init_xcontainer_config(&config);\
    return xstack_##T##_new_config(&config, out);\
}\
\
enum x_stat xstack_##T##_new_max_size(xstack_##T **out, size_t max_size) \
{\
    struct xcontainer_config config;\
    init_xcontainer_config_max_size(&config, max_size);\
    return xstack_##T##_new_config(&config, out);\
}\
\
enum x_stat xstack_##T##_new_config(struct xcontainer_config * const config, xstack_##T **out) \
{\
    enum x_stat xinternal_vector_status;\
    xdeque_##T *xinternal_vector;\
    xstack_##T *container;\
    container = (xstack_##T *) config->memory_calloc(1, sizeof(xstack_##T));\
    if (!container) {\
        return XTD_ALLOC_ERR;\
    }\
    xinternal_vector_status = xdeque_##T##_new_config(config, &xinternal_vector);\
    if (xinternal_vector_status != XTD_OK) {\
        config->memory_free(container);\
        return xinternal_vector_status;\
    }\
    container->capacity         = config->capacity;\
    container->max_size         = config->max_size;\
    container->size             = 0;\
    container->xinternal_e7884708734_ximpl = xinternal_vector;\
    container->buffer           = xinternal_vector->buffer;\
    container->iter             = xinternal_vector->iter;\
    container->memory_alloc     = config->memory_alloc;\
    container->memory_calloc    = config->memory_calloc;\
    container->memory_free      = config->memory_free;\
    *out = container;\
    return XTD_OK;\
}\
\
enum x_stat xstack_##T##_push(xstack_##T *container, T element)\
{\
    enum x_stat status;\
    if (container->size >= container->max_size) {\
        return XTD_STACK_OVERFLOW_ERR;\
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
enum x_stat xstack_##T##_peek(xstack_##T *container, T *element)\
{\
    return xdeque_##T##_get_back(container->xinternal_e7884708734_ximpl, element);\
}\
\
enum x_stat xstack_##T##_pop(xstack_##T *container, T *element)\
{\
    enum x_stat status;\
    if (container->size == 0) {\
        return XTD_STACK_UNDERFLOW_ERR;\
    }\
    status = xdeque_##T##_remove_back(container->xinternal_e7884708734_ximpl, element);\
    if (status == XTD_OK) {\
        container->buffer = container->xinternal_e7884708734_ximpl->buffer;\
        container->capacity = container->xinternal_e7884708734_ximpl->capacity;\
        container->size = container->xinternal_e7884708734_ximpl->size;\
    }\
    return status;\
}\
\

/**

*/
#define SETUP_XSTACK_FOR(T) SETUP_XDEQUE_FOR(T) SETUP_ONLY_XSTACK_FOR(T)

/**

*/
#define xstack(T) xstack_##T

/**

*/
#define xstack_new(T) xstack_##T##_new

/**

*/
#define xstack_new_max_size(T) xstack_##T##_new_max_size

/**

*/
#define xstack_new_config(T) xstack_##T##_new_config

/**

*/
#define xstack_push(T) xstack_##T##_push

/**

*/
#define xstack_peek(T) xstack_##T##_peek

/**

*/
#define xstack_pop(T) xstack_##T##_pop

/**

*/
#define xstack_destroy(container) { \
        container->memory_free(container->xinternal_e7884708734_ximpl->buffer); \
        container->memory_free(container->xinternal_e7884708734_ximpl->iter); \
        container->memory_free(container->xinternal_e7884708734_ximpl); \
        container->memory_free(container); \
    }

/*

*/
#define xstack_capacity xcapacity

/*

*/
#define xstack_size xsize

/*

*/
#define xstack_max_size xmax_size

/*

*/
#define xstack_is_empty xis_empty
    


#ifdef __cplusplus
}
#endif

#endif
