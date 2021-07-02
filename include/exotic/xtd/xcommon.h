
/*!
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


/*! 
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
        #define EXOTIC_API __declspec(dllexport) /*!< the platform is windows use windows export keyword __declspec(dllexport) */ 
    #else
        #define EXOTIC_API extern                /*!< Keyword to export the functions to allow ussage dynamically. NOT USED. IGNORED  */
    #endif
#else
    #define EXOTIC_API
#endif

#define x_free(x) free(x); x = XTD_NULL;

/*!
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

/*
    Neccessary fillers
*/
#ifndef uint32_t
typedef unsigned int uint32_t;
#endif
#ifndef uint32_t
typedef unsigned short uint16_t;
#endif

/*!
    The status codes for operation in the x-types 
    library.
*/
enum x_stat {
    XTD_OK = 0,                       /*!< the operation successful */
    XTD_ERR,                           /*!< An operation fails */
    XTD_ALLOC_ERR,                    /*!< unable to allocate memory for a pointer */
    XTD_INVALID_CAPACITY_ERR,         /*!< the capacity is more than available for the data type */
    XTD_INDEX_OUT_OF_RANGE_ERR,       /*!< the index is equal or more than the size of the container elements */
    XTD_INDEX_LESS_THAN_ZERO_ERR,
    XTD_EMPTY_CONTAINER_ERR,
    XTD_MAX_SIZE_ERR,
    XTD_OUT_OF_RANGE_ERR,
    XTD_PARAM_NULL_ERR,
    XTD_OUT_PARAM_NULL_ERR,
    XTD_STACK_OVERFLOW_ERR,
    XTD_STACK_UNDERFLOW_ERR,
    XTD_ALREADY_IN_CONTAINER_ERR,
    XTD_MAX_CAPACITY_ERR,             /*!< the data type is full */
    XTD_VALUE_NOT_FOUND_ERR,          /*!< the data type is full */  
    XTD_KEY_NOT_FOUND_ERR,
    XTD_FAILED_TO_CLEANUP_ERR,        /*!< the data type is full */    
    XTD_INDEXES_OVERLAP_ERR,          /*!< Two index value overlap each other */
    XTD_CRITICAL_ERR,                 /*!< An error impossible to recover from occur. The program should terminate immediately if encountered */
    XTD_NO_OP,                        /*!< No operation caried out */
    XTD_ITER_END,                     /*!< The loop has reached the end of the iteration */
    XTD_INVALID_PARAMETER,
    XTD_DUPLICATE_ERR,
    XTD_NOT_FOUND_ERR,
    XTD_INVALID_PARAMETER_FOUND_ERR,
    XTD_MISSING_PARAM_ERR
};

/*!
    
*/
#define XTD_INVALID_OPTION_ERR XTD_INVALID_PARAMETER_ERR

/*!
    
*/
#define XTD_INVALID_ARGUMENT_ERR XTD_INVALID_PARAMETER_ERR

/*!
    
*/
#define XTD_VALUE_NOT_IN_OPTION_ERR XTD_KEY_NOT_FOUND_ERR

#ifdef ARCH_64
    #define XTD_MATH_MAX_POW_TWO (((size_t) 1) << 63)
#else
    #define XTD_MATH_MAX_POW_TWO (((size_t) 1) << 31)
#endif /* ARCH_64 */

#define XDEFAULT_CONTAINER_CAPACITY 4
#define XDEFAULT_CONTAINER_EXPANSION_RATE 2
#define XTD_CONTAINER_MAX_CAPACITY ((size_t) - 1)
#define XHASHTABLE_KEY_LENGTH_VARIABLE  -1
#define XDEFAULT_XHASHTABLE_DEFAULT_CAPACITY 16
#define XDEFAULT_XHASHTABLE_LOAD_FACTOR 0.75f

/*!
    
*/
struct xallocator_s {
    void *(*memory_realloc) (void* ptr, size_t size);      /*!<  memory allocator used to allocate the array and it buffer. realloc */
    void *(*memory_malloc)  (size_t size);                  /*!<  memory allocator used to allocate the array and it buffer. malloc */
    void *(*memory_calloc)  (size_t blocks, size_t size);   /*!<  memory allocator used to allocate the array and it buffer. calloc */
    void  (*memory_free)    (void *block);                  /*!<  the free funtion to release the memory of the array and it buffer */
};

/*!
    
*/
typedef struct xallocator_s XAllocator;

/*!
    
*/
static void init_xallocator(struct xallocator_s *allocator) {
#if defined(_STDIO_H_) || defined(_INC_STDLIB) || defined(_STDLIB_H) || defined(_TR1_STDLIB_H)
    allocator->memory_realloc   = realloc;
    allocator->memory_malloc   = malloc;
    allocator->memory_calloc  = calloc;
    allocator->memory_free    = free;
#endif
}

/*!
    The container configuration structure to initialize a new container with 
    specific fields and memory allocation funtions. 
*/
struct xcontainer_config {
    float load_factor;
    int key_length;
    uint32_t hash_seed;
    size_t capacity;                                        /*!<  the default capacity of the array */
    size_t expansion_rate;                                  /*!<  the rate at which the array buffer expands (capacity * expand_rate) */
    size_t max_size;                                        /*!<  the max size of the container */
    XAllocator allocator;                                   /*!<   */
};

/*!

*/
typedef struct xcontainer_config XConfig;

/*!

*/
static void init_xcontainer_config_max_size(struct xcontainer_config *config, size_t max_size) {
    XAllocator xallocator;
    config->expansion_rate = XDEFAULT_CONTAINER_CAPACITY > max_size ? 0 : XDEFAULT_CONTAINER_EXPANSION_RATE;
    config->capacity       = XDEFAULT_CONTAINER_CAPACITY > max_size ? max_size : XDEFAULT_CONTAINER_CAPACITY;
    config->max_size       = max_size;
    config->key_length     = XHASHTABLE_KEY_LENGTH_VARIABLE;
    config->load_factor    = XDEFAULT_XHASHTABLE_LOAD_FACTOR;
    config->hash_seed      = 0;
#if defined(_STDIO_H_) || defined(_INC_STDLIB) || defined(_STDLIB_H) || defined(_TR1_STDLIB_H)
    xallocator.memory_realloc   = realloc;
    xallocator.memory_malloc   = malloc;
    xallocator.memory_calloc  = calloc;
    xallocator.memory_free    = free;
#endif
    config->allocator   = xallocator;
}

/*!

*/
static void init_xcontainer_config(struct xcontainer_config *config) {
    init_xcontainer_config_max_size(config, XTD_CONTAINER_MAX_CAPACITY);
}

/* General container functions */

/*!

*/
#define xcapacity(container) (container->capacity)

/*!

*/
#define xsize(container) (container->size)

/*!

*/
#define xmax_size(container) (container->max_size)

/*!

*/
#define xis_empty(container) (container->size == 0)

/*!

*/
#define xget_buffer(container) (container->buffer)

/*!

*/
#define xget_internal_impl(container) (container->xinternal_e7884708734_ximpl)

/*!

*/
#define xget_at(container, index) (container->buffer[index])

/*!

*/
#define xget_front(container) (container->size > 0 ? xget_at(container, 0) : XTD_NULL)

/*!

*/
#define xget_back(container) (container->size > 0 ? xget_at(container, container->size-1) : XTD_NULL)

/*!

*/
static size_t xptp_array_size(void **p2p) {
    size_t index = 0;
    if (p2p == XTD_NULL) { return index; }
    for (; p2p[index] != XTD_NULL; index++);
    return index;
}

/*!

*/
static void xfreep2p(void **p2p, XAllocator allocator) {
    size_t index = 0;
    if (p2p == XTD_NULL) { return; }
    for (; p2p[index] != XTD_NULL; index++) {
        allocator.memory_free(p2p[index]);
    }
    allocator.memory_free(p2p);
}

/*!

*/
#define xptp_free xfreep2p

#ifdef __cplusplus
}
#endif

#endif
