
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
#include "xvector.h"

#ifdef __cplusplus
#if !defined(ALLOW_X_TYPES_WITH_ALTERNATIVES_IN_CPP) && __cplusplus >= 201103L
    #warning Do not use this type in C++ 03 and above, use the std::vector class instead
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
    xvector_##T *xinternal_e7884708734_xvector;\
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
    xvector_##T *xinternal_vector;\
    xstack_##T *container;\
    container = (xstack_##T *) config->memory_calloc(1, sizeof(xstack_##T));\
    if (!container) {\
        return X_ALLOC_ERR;\
    }\
    xinternal_vector_status = xvector_##T##_new_config(config, &xinternal_vector);\
    if (xinternal_vector_status != X_OK) {\
        config->memory_free(container);\
        return xinternal_vector_status;\
    }\
    container->capacity         = config->capacity;\
    container->max_size         = config->max_size;\
    container->size             = 0;\
    container->xinternal_e7884708734_xvector = xinternal_vector;\
    container->buffer           = xinternal_vector->buffer;\
    container->iter             = xinternal_vector->iter;\
    container->memory_alloc     = config->memory_alloc;\
    container->memory_calloc    = config->memory_calloc;\
    container->memory_free      = config->memory_free;\
    *out = container;\
    return X_OK;\
}\
\
enum x_stat xstack_##T##_push(xstack_##T *container, T element)\
{\
    enum x_stat status;\
    if (container->size >= container->max_size) {\
        return X_STACK_OVERFLOW_ERR;\
    }\
    status = xvector_##T##_add(container->xinternal_e7884708734_xvector, element);\
    if (status == X_OK) {\
        container->capacity = container->xinternal_e7884708734_xvector->capacity;\
        container->size = container->xinternal_e7884708734_xvector->size;\
    }\
    return status;\
}\
\
enum x_stat xstack_##T##_peek(xstack_##T *container, T *element)\
{\
    return xvector_##T##_get_back(container->xinternal_e7884708734_xvector, element);\
}\
\
enum x_stat xstack_##T##_pop(xstack_##T *container, T *element)\
{\
    enum x_stat status;\
    if (container->size == 0) {\
        return X_STACK_UNDERFLOW_ERR;\
    }\
    status = xvector_##T##_remove_at(container->xinternal_e7884708734_xvector, container->xinternal_e7884708734_xvector->size-1, element);\
    if (status == X_OK) {\
        container->capacity = container->xinternal_e7884708734_xvector->capacity;\
        container->size = container->xinternal_e7884708734_xvector->size;\
    }\
    return status;\
}\
\

/**

*/
#define SETUP_XSTACK_FOR(T) SETUP_XVECTOR_FOR(T) SETUP_ONLY_XSTACK_FOR(T)

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
        container->memory_free(container->xinternal_e7884708734_xvector->buffer); \
        container->memory_free(container->xinternal_e7884708734_xvector->iter); \
        container->memory_free(container->xinternal_e7884708734_xvector); \
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