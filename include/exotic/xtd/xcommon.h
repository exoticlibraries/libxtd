
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
    #define __XTD_STDC_VERSION__ __STDC_VERSION__
#else
    #ifdef __cplusplus
        #if __cplusplus > 199711L
            #define __XTD_STDC_VERSION__ __cplusplus
        #endif
    #endif
#endif
#ifndef __XTD_STDC_VERSION__
    #define __XTD_INLINE__ 
    #define __XTD_LONG_LONG__ long
    #ifdef __FUNCTION__ 
        #define __XTD_FUNCTION__ __FUNCTION__
    #else
        #define __XTD_FUNCTION__ "<unknown>"
    #endif
    #define XTD_NULL 0L
#else 
    #define __XTD_INLINE__ inline
    #define __XTD_LONG_LONG__ long long
    #define __XTD_FUNCTION__ __func__
    #define XTD_NULL NULL
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

#define x_free(x) free(x); x = XTD_NULL;

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
enum x_stat {
    XTD_OK = 0,                       /**< the operation successful */
    XTD_ALLOC_ERR,                    /**< unable to allocate memory for a pointer */
    XTD_INVALID_CAPACITY_ERR,         /**< the capacity is more than available for the data type */
    XTD_INDEX_OUT_OF_RANGE_ERR,       /**< the index is equal or more than the size of the container elements */
    XTD_INDEX_LESS_THAN_ZERO_ERR,
    XTD_EMPTY_CONTAINER_ERR,
    XTD_MAX_SIZE_ERR,
    XTD_OUT_OF_RANGE_ERR,
    XTD_PARAM_NULL_ERR,
    XTD_OUT_PARAM_NULL_ERR,
    XTD_STACK_OVERFLOW_ERR,
    XTD_STACK_UNDERFLOW_ERR,
    XTD_MAX_CAPACITY_ERR,             /**< the data type is full */
    XTD_VALUE_NOT_FOUND_ERR,          /**< the data type is full */  
    XTD_FAILED_TO_CLEANUP_ERR,        /**< the data type is full */    
    XTD_INDEXES_OVERLAP_ERR,          /**< Two index value overlap each other */
    XTD_CRITICAL_ERR,                 /**< An error impossible to recover from occur. The program should terminate immediately if encountered */
    XTD_NO_OP,                        /**< No operation caried out */
    XTD_ITER_END,                     /**< The loop has reached the end of the iteration */
    XTD_INVALID_PARAMETER,
    XTD_ERR                           /**< An operation fails */

};

#ifdef ARCH_64
    #define XTD_MAX_POW_TWO (((size_t) 1) << 63)
#else
    #define XTD_MAX_POW_TWO (((size_t) 1) << 31)
#endif /* ARCH_64 */

#define XDEFAULT_CONTAINER_CAPACITY 4
#define XDEFAULT_CONTAINER_EXPANSION_RATE 2

#define XTD_CONTAINER_MAX_CAPACITY ((size_t) - 1)

/**
    The container configuration structure to initialize a new container with 
    specific fields and memory allocation funtions. 
*/
struct xcontainer_config {
    size_t capacity;                                        /**<  the default capacity of the array */
    size_t expansion_rate;                                  /**<  the rate at which the array buffer expands (capacity * expand_rate) */
    size_t max_size;                                        /**<  the max size of the container */
    void *(*memory_alloc)  (size_t size);                   /**<  memory allocator used to allocate the array and it buffer. malloc */
    void *(*memory_calloc) (size_t blocks, size_t size);    /**<  memory allocator used to allocate the array and it buffer. calloc */
    void  (*memory_free)   (void *block);                   /**<  the free funtion to release the memory of the array and it buffer */
};

typedef struct xcontainer_config XConfig;

static void init_xcontainer_config(struct xcontainer_config *config) {
    config->expansion_rate = XDEFAULT_CONTAINER_EXPANSION_RATE;
    config->capacity       = XDEFAULT_CONTAINER_CAPACITY;
    config->max_size       = XTD_CONTAINER_MAX_CAPACITY;
#if defined(_STDIO_H_) || defined(_INC_STDLIB) || defined(_STDLIB_H) || defined(_TR1_STDLIB_H)
    config->memory_alloc   = malloc;
    config->memory_calloc  = calloc;
    config->memory_free    = free;
#endif
}

static void init_xcontainer_config_max_size(struct xcontainer_config *config, size_t max_size) {
    config->expansion_rate = XDEFAULT_CONTAINER_CAPACITY > max_size ? 0 : XDEFAULT_CONTAINER_EXPANSION_RATE;
    config->capacity       = XDEFAULT_CONTAINER_CAPACITY > max_size ? max_size : XDEFAULT_CONTAINER_CAPACITY;
    config->max_size       = max_size;
#if defined(_STDIO_H_) || defined(_INC_STDLIB) || defined(_STDLIB_H) || defined(_TR1_STDLIB_H)
    config->memory_alloc   = malloc;
    config->memory_calloc  = calloc;
    config->memory_free    = free;
#endif
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
#define xget_front(container) (container->size > 0 ? xget_at(container, 0) : XTD_NULL)

/**

*/
#define xget_back(container) (container->size > 0 ? xget_at(container, container->size-1) : XTD_NULL)

/**

*/
static __XTD_INLINE__ size_t x_upper_pow_two(size_t n)
{
    if (n >= XTD_MAX_POW_TWO) {
        return XTD_MAX_POW_TWO;
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
