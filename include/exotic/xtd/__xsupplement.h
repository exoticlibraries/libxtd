
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <iamthecarisma@gmail.com>
    \date 24 May 2020
    \file __xsupplement.h
*/

#ifndef EXOTIC_XSUPPLEMENT_H
#define EXOTIC_XSUPPLEMENT_H

#ifdef __cplusplus
extern "C" {
#endif

static void *memcpy(void *dst, void const *src, size_t len) {
    char* pDst = (char *) dst;
    char const * pSrc = (char const *) src;

    while(len--){
        *pDst++ = *pSrc++;
    }
    return (dst);
}

#ifdef __cplusplus
}
#endif

#endif
