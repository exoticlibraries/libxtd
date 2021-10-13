
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 10 October 2021
    \file xpair.h
*/

#ifndef EXOTIC_XPAIR_H
#define EXOTIC_XPAIR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "xcommon.h"

#ifdef __cplusplus
#if !defined(ALLOW_XTD_TYPES_WITH_ALTERNATIVES_IN_CPP) && __cplusplus >= 201103L
    #warning Do not use this type in C++ 11 and above, use the std::pair class instead
#endif
#endif

/*
    
*/
#define SETUP_XPAIR_FOR(T1, T2) typedef struct xpair_##T1##_##T2##_s { \
    T1 key;\
    T2 value;\
} xpair_##T1##_##T2;\
\
\
\

/*
    
*/
#define SETUP_XPAIR_FOR_WITH_HASH_AND_NEXT(T1, T2)\
\
typedef struct xpair_##T1##_##T2##_s xpair_##T1##_##T2;\
\
struct xpair_##T1##_##T2##_s { \
    T1 key;\
    T2 value;\
    size_t hash;\
    xpair_##T1##_##T2 *next;\
};\
\
\
\


/**

*/
#define xpair(T1, T2) xpair_##T1##_##T2 

/**

*/
#define xpair_new(key_entry, value_entry) { .key = key_entry, .value = value_entry }

/**

*/
#define xpair_new_with_hash(key_entry, value_entry, hash_entry) { .key = key_entry, .value = value_entry, .hash = hash_entry }

/**

*/
#define xpair_new_with_next(key_entry, value_entry, next_entry) { .key = key_entry, .value = value_entry, .next = next_entry }

/**

*/
#define xpair_new_with_hash_and_next(key_entry, value_entry, hash_entry, next_entry) { .key = key_entry, .value = value_entry, .hash = hash_entry, .next = next_entry }

/**

*/
#define xpair_key(pair) pair.key

/**

*/
#define xpair_set_key(pair, key_entry) { pair.key = key_entry; }

/**

*/
#define xpair_value(pair) pair.value

/**

*/
#define xpair_set_value(pair, value_entry) { pair.value = value_entry; }

/**

*/
#define xpair_hash(pair) pair.hash

/**

*/
#define xpair_set_hash(pair, hash_entry) { pair.hash = hash_entry; }

/**

*/
#define xpair_next(pair) (*pair.next)

/**

*/
#define xpair_set_next(pair, next_entry) { pair.next = next_entry; }

#ifdef __cplusplus
}
#endif

#endif