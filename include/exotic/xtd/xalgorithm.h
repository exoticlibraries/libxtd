
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 21 December 2020
    \file xalgorithm.h
*/

#ifndef EXOTIC_XALGORITHM_H
#define EXOTIC_XALGORITHM_H

#ifdef __cplusplus
extern "C" {
#endif

/**

*/
#define SETUP_XALGORITHM_FOR(T)\
size_t xliner_search_##T(T *array_of_t, size_t array_of_t_size, T t)\
{\
    size_t index = 0;\
    for (; index < array_of_t_size; index++) {\
        if (array_of_t[index] == t) {\
            return index;\
        }\
    }\
    return -1;\
}\
\
size_t xbinary_search_in_range_##T(T *array_of_t, size_t begin, size_t end, T t)\
{\
    if (begin <= end) {\
        size_t middle = (begin + end) / 2;\
        if (array_of_t[middle] == t) {\
            return middle;\
        }\
        if (array_of_t[middle] > t) {\
            return xbinary_search_in_range_##T(array_of_t, begin, middle-1, t);\
        }\
        if (array_of_t[middle] < t) {\
            return xbinary_search_in_range_##T(array_of_t, middle+1, end, t);\
        }\
    }\
    return -1;\
}\
\
size_t xbinary_search_##T(T *array_of_t, size_t array_of_t_size, T t)\
{\
    return xbinary_search_in_range_##T(array_of_t, 0, array_of_t_size-1, t);\
}\

/**

*/
#define SETUP_XALGORITHM_SWAP_FOR(T)\
void xswap_##T(T *ptr1, T *ptr2)\
{\
    T tmp = *ptr1;\
    *ptr1 = *ptr2;\
    *ptr2 = tmp;\
}\

/**

*/
#define xliner_search(T) xliner_search_##T

/**

*/
#define xbinary_search_in_range(T) xbinary_search_in_range_##T

/**

*/
#define xbinary_search(T) xbinary_search_##T

/**

*/
#define xswap(T) xswap_##T

#ifdef __cplusplus
}
#endif

#endif
