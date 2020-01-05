
/*P
	:copyright: 2019, Adewale Azeez
	:license: GNU Lesser General Public License v3.0 Copyright (c) 
	:author: Adewale Azeez <azeezadewale98@gmail.com>
	:date: 10 November 2019
	:filename: l_common.h
*/

#ifndef LIBO_COMMON_H
#define LIBO_COMMON_H

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
#define LIBO_API __declspec(dllexport)
#else
#define LIBO_API extern
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lbool.h"

#define l_free(x) free(x); x = NULL;

typedef enum l_stat {

    L_OK                   = 0,
	L_ERR_ALLOC            = 1,
	L_ERR_FAIL             = 2

} l_stat;

#endif