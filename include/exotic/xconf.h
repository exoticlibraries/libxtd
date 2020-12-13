
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 07 April 2020
    \file xconf.h
*/

#ifndef EXOTIC_TYPECONF_H
#define EXOTIC_TYPECONF_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#ifndef XTYPES_DONT_USE_BUILTIN
    #include <string.h>
    #define xtypes_qsort qsort
#else
    #include "__xsupplement.h" /* define the builtin functions manually */
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
    X_OUT_OF_RANGE_ERR,             /**< unable to allocate memory for a pointer */
    X_MAX_CAPACITY_ERR,             /**< the data type is full */
    X_VALUE_NOT_FOUND_ERR,          /**< the data type is full */  
    X_FAILED_TO_CLEANUP_ERR,        /**< the data type is full */    
    X_INDEXES_OVERLAP_ERR,          /**< Two index value overlap each other */
    X_CRITICAL_ERR,                 /**< An error impossible to recover from occur. The program should terminate immediately if encountered */
    X_NO_OP,                        /**< No operation caried out */
    X_ITER_END,                     /**< The loop has reached the end of the iteration */
    X_ERR                           /**< An operation fails */

};

/**
    The order in which to sort datas or to order iterate over 
    a collection.
*/
EXOTIC_API enum iterator_order {
    X_ITERATOR_ASC        = 0, /**< ascending order */
    X_ITERATOR_DESC       = 1  /**< descending order */
};

#define X_ARRAY_MAX_CAPACITY ((size_t) - 1)

#ifdef __cplusplus
}
#endif

#endif