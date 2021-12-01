
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <iamthecarisma@gmail.com>
    \date 21 June 2021
    \file xcrypto.h
*/

#ifndef EXOTIC_XCRYPTO_H
#define EXOTIC_XCRYPTO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "xcommon.h"

/**
    djb2 string hash
*/
static size_t xcrypto_hash_string(char * const key, int len, uint32_t seed) {
    int c;
    const char *str = key;
    register size_t hash = seed + 5381 + len + 1;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) ^ c;
    }
    return hash;
}


#ifdef __cplusplus
}
#endif

#endif
