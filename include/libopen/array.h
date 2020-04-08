
/**
    \copyright GNU General Public License v3.0 Copyright (c) 2019, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 07 April 2020
    \file array.h
*/


#ifndef LIBOPEN_ARRAY_H
#define LIBOPEN_ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

/**

*/
typedef struct array_config {
    size_t capacity;
    size_t expand_rate;
    void *(*memory_alloc)  (size_t size);
    void *(*memory_calloc) (size_t blocks, size_t size);
    void  (*memory_free)   (void *block);
} ArrayConfig;

#ifdef __cplusplus
}
#endif


#endif