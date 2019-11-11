
/*P
	:copyright: 2019, Azeez Adewale
	:license: GNU Lesser General Public License v3.0 Copyright (c) 
	:author: Azeez Adewale <azeezadewale98@gmail.com>
	:date: 10 November 2019
	:filename: sct_common.h
*/

#ifndef SCT_COMMON_H
#define SCT_COMMON_H

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
#define SCT_API __declspec(dllexport)
#else
#define SCT_API extern
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define sct_free(x) free(x); x = NULL;

enum sct_stat {

    SCT_OK                   = 0,
	SCT_ERR_ALLOC            = 1,

};

/*

*/
enum sct_bool {

    SCT_TRUE                   = 1,
	SCT_FALSE	               = 0

};

#endif