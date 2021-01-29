
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 07 April 2020
    \file xconf.h
*/

#ifndef EXOTIC_XCOMMON_H
#define EXOTIC_XCOMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#ifndef XTYPES_DONT_USE_BUILTIN
    #include <string.h>
    #define xtd_qsort qsort
#else
    #include "__xsupplement.h" /* define the builtin functions manually */
#endif


/** 
    The inline keyword to optimize the function. In 
    C89 and C90 the inline keyword semantic is 
    different from current C standard semantic hence 
    for compilation targeting C89 or C99 the inline 
    keyword is ommited.
*/
#ifdef __STDC_VERSION__
    #define __X_STDC_VERSION__ __STDC_VERSION__
#else
    #ifdef __cplusplus
        #if __cplusplus > 199711L
            #define __X_STDC_VERSION__ __cplusplus
        #endif
    #endif
#endif
#ifndef __X_STDC_VERSION__
    #define __X_INLINE__ 
    #define __X_LONG_LONG__ long
    #define __FUNCTION__ "<unknown>"
#else 
    #define __X_INLINE__ inline
    #define __X_LONG_LONG__ long long
    #define __FUNCTION__ __func__
#endif

#ifdef _WIN32
/*
**  Windows 
**  Support Windows XP 
**  To avoid error message : procedure entry point **  InitializeConditionVariable could not be located **  in Kernel32.dll 
*/
#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif
#define _WIN32_WINNT 0x502
#define EXOTICTYPES_WINDLLEXPORT 1
/* Linux */
#else
#define EXOTICTYPES_WINDLLEXPORT 0
#endif
#ifndef __cplusplus
    #if EXOTICTYPES_WINDLLEXPORT
        #define EXOTIC_API __declspec(dllexport) /**< the platform is windows use windows export keyword __declspec(dllexport) */ 
    #else
        #define EXOTIC_API extern                /**< Keyword to export the functions to allow ussage dynamically. NOT USED. IGNORED  */
    #endif
#else
    #define EXOTIC_API
#endif

#define x_free(x) free(x); x = NULL;

/**
    Define bool to be unsigned
*/
#ifndef bool 
#define bool unsigned
#endif
#ifndef FALSE
    #define FALSE 0
#endif
#ifndef TRUE
    #define TRUE !FALSE
#endif
#ifndef false
    #define false 0
#endif
#ifndef true
    #define true !false
#endif
/**
    The status codes for operation in the x-types 
    library.
*/
EXOTIC_API enum x_stat {
    X_OK = 0,                       /**< the operation successful */
    X_ALLOC_ERR,                    /**< unable to allocate memory for a pointer */
    X_INVALID_CAPACITY_ERR,         /**< the capacity is more than available for the data type */
    X_INDEX_OUT_OF_RANGE_ERR,       /**< the index is equal or more than the size of the container elements */
    X_INDEX_LESS_THAN_ZERO_ERR,
    X_EMPTY_CONTAINER_ERR,
    X_MAX_SIZE_ERR,
    X_OUT_OF_RANGE_ERR,
    X_OUT_PARAM_NULL_ERR,
    X_STACK_OVERFLOW_ERR,
    X_STACK_UNDERFLOW_ERR,
    X_MAX_CAPACITY_ERR,             /**< the data type is full */
    X_VALUE_NOT_FOUND_ERR,          /**< the data type is full */  
    X_FAILED_TO_CLEANUP_ERR,        /**< the data type is full */    
    X_INDEXES_OVERLAP_ERR,          /**< Two index value overlap each other */
    X_CRITICAL_ERR,                 /**< An error impossible to recover from occur. The program should terminate immediately if encountered */
    X_NO_OP,                        /**< No operation caried out */
    X_ITER_END,                     /**< The loop has reached the end of the iteration */
    X_INVALID_PARAMETER,
    X_ERR                           /**< An operation fails */

};

#ifdef ARCH_64
    #define X_MAX_POW_TWO (((size_t) 1) << 63)
#else
    #define X_MAX_POW_TWO (((size_t) 1) << 31)
#endif /* ARCH_64 */

#define XDEFAULT_CONTAINER_CAPACITY 4
#define XDEFAULT_CONTAINER_EXPANSION_RATE 2

#define X_CONTAINER_MAX_CAPACITY ((size_t) - 1)

/**
    The container configuration structure to initialize a new container with 
    specific fields and memory allocation funtions. 
*/
EXOTIC_API struct xcontainer_config {
    size_t capacity;                                        /**<  the default capacity of the array */
    size_t expansion_rate;                                  /**<  the rate at which the array buffer expands (capacity * expand_rate) */
    size_t max_size;                                        /**<  the max size of the container */
    void *(*memory_alloc)  (size_t size);                   /**<  memory allocator used to allocate the array and it buffer. malloc */
    void *(*memory_calloc) (size_t blocks, size_t size);    /**<  memory allocator used to allocate the array and it buffer. calloc */
    void  (*memory_free)   (void *block);                   /**<  the free funtion to release the memory of the array and it buffer */
};

typedef struct xcontainer_config XConfig;

void init_xcontainer_config(struct xcontainer_config *config) {
    config->expansion_rate = XDEFAULT_CONTAINER_EXPANSION_RATE;
    config->capacity       = XDEFAULT_CONTAINER_CAPACITY;
    config->max_size       = X_CONTAINER_MAX_CAPACITY;
    config->memory_alloc   = malloc;
    config->memory_calloc  = calloc;
    config->memory_free    = free;
}

void init_xcontainer_config_max_size(struct xcontainer_config *config, size_t max_size) {
    config->expansion_rate = XDEFAULT_CONTAINER_CAPACITY > max_size ? 0 : XDEFAULT_CONTAINER_EXPANSION_RATE;
    config->capacity       = XDEFAULT_CONTAINER_CAPACITY > max_size ? max_size : XDEFAULT_CONTAINER_CAPACITY;
    config->max_size       = max_size;
    config->memory_alloc   = malloc;
    config->memory_calloc  = calloc;
    config->memory_free    = free;
}

/* General container functions */

/**

*/
#define xcapacity(container) (container->capacity)

/**

*/
#define xsize(container) (container->size)

/**

*/
#define xmax_size(container) (container->max_size)

/**

*/
#define xis_empty(container) (container->size == 0)

/**

*/
#define xget_buffer(container) (container->buffer)

/**

*/
#define xget_internal_impl(container) (container->xinternal_e7884708734_ximpl)

/**

*/
#define xget_at(container, index) (container->buffer[index])

/**

*/
#define xget_front(container) (container->size > 0 ? xget_at(container, 0) : NULL)

/**

*/
#define xget_back(container) (container->size > 0 ? xget_at(container, container->size-1) : NULL)

/**

*/
static __X_INLINE__ size_t x_upper_pow_two(size_t n)
{
    if (n >= X_MAX_POW_TWO) {
        return X_MAX_POW_TWO;
    }
    if (n == 0) {
        return 2;
    }
    /**
     * taken from:
     * http://graphics.stanford.edu/~seander/
     * bithacks.html#RoundUpPowerOf2Float
     */
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;

    return n;
}

#ifdef __cplusplus
}
#endif

#endif