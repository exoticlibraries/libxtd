
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
#define SIMPLE_WINDLLEXPORT 1
/* Linux */
#else
#define SIMPLE_WINDLLEXPORT 0
#endif
#if SIMPLE_WINDLLEXPORT
#define LIBO_API __declspec(dllexport)
#else
#define LIBO_API extern
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sbool.h"

#define l_free(x) free(x); x = NULL;

typedef enum libo_stat {

    LIBO_OK                   = 0,
	LIBO_ERR_ALLOC            = 1,
	LIBO_ERR_FAIL             = 2

} libo_stat;

#endif