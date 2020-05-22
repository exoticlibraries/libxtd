
/**
    \copyright GNU General Public License v3.0 Copyright (c) 2019, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 07 April 2020
    \file typeconf.h
*/

#ifndef EXOTICPEN_TYPECONF_H
#define EXOTICPEN_TYPECONF_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

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
#if EXOTICTYPES_WINDLLEXPORT
#define EXOTICPEN_API __declspec(dllexport)
#else
#define EXOTICPEN_API extern
#endif

#define x_free(x) free(x); x = NULL;

/**
    Define bool to be unsigned
*/
typedef unsigned bool;

/**
    The status codes for operation in the xtypes-types 
    library.
*/
EXOTICPEN_API enum xtypes_stat {

    X_OK                   = 0, ///< the operation successful
    X_ERR_ALLOC            = 1, ///< unable to allocate memory for a pointer
    X_ERR_FAIL             = 2  ///< an operation fails

};

/**
    The order in which to sort datas or to order iterate over 
    a collection.
*/
EXOTICPEN_API enum iterator_order {
    X_ITERATOR_ASC        = 0, ///< ascending order
    X_ITERATOR_DESC       = 1  ///< descending order
};

#define EXOTICPEN_ARRAY_MAX_CAPACITY ((size_t) - 1)

#ifdef __cplusplus
}
#endif

#endif