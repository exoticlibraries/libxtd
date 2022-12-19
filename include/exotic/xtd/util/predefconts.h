
/*!
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <iamthecarisma@gmail.com>
    \date 01 April 2022
    \file predefconts.h
*/

#ifndef EXOTIC_XPRE_DEFINED_CONTAINERS_H
#define EXOTIC_XPRE_DEFINED_CONTAINERS_H

#ifdef __cplusplus
extern "C" {
#endif

// declare type e.g.
typedef char* xstr;
typedef char** xchar_array;

#define xstrarray xchar_array;

SETUP_XCIRCULAR_BUFFER_FOR(xstr);
SETUP_XCIRCULAR_BUFFER_FOR(xstr);

#ifdef __cplusplus
}
#endif

#endif