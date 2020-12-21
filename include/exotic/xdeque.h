
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 21 December 2020
    \file xdeque.h
*/

#ifndef EXOTIC_XDEQUE_H
#define EXOTIC_XDEQUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "xcommon.h"
#include "xiterator.h"

#ifdef __cplusplus
#if !defined(ALLOW_X_TYPES_WITH_ALTERNATIVES_IN_CPP) && __cplusplus >= 201103L
    #warning Do not use this type in C++ 03 and above, use the std::deque class instead
#endif
#define NULL 0
#endif

#define SETUP_ONLY_XDEQUE_FOR(T) "Not implemented yet"


#ifdef __cplusplus
}
#endif

#endif