
/**
    \copyright GNU General Public License v3.0 Copyright (c) 2019, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 07 April 2020
    \file typeconf.h
*/

#ifndef LIBOPEN_TYPECONF_H
#define LIBOPEN_TYPECONF_H

#ifdef __cplusplus
extern "C" {
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
#define LIBOTYPES_WINDLLEXPORT 1
/* Linux */
#else
#define LIBOTYPES_WINDLLEXPORT 0
#endif
#if LIBOTYPES_WINDLLEXPORT
#define LIBOPEN_API __declspec(dllexport)
#else
#define LIBOPEN_API extern
#endif

#define l_free(x) free(x); x = NULL;

/**
    The status codes for operation in the libopen-types 
    library.
*/
LIBOPEN_API enum libopen_stat {

    L_OK                   = 0, ///< the operation successful
    L_ERR_ALLOC            = 1, ///< unable to allocate memory for a pointer
    L_ERR_FAIL             = 2  ///< an operation fails

};

/**
    The order in which to sort datas or to order iterate over 
    a collection.
*/
LIBOPEN_API enum iterator_order {
    L_ITERATOR_ASC        = 0, ///< ascending order
    L_ITERATOR_DESC       = 1  ///< descending order
};

#define LIBOPEN_ARRAY_MAX_CAPACITY ((size_t) - 1)

#ifdef __cplusplus
}
#endif

#endif