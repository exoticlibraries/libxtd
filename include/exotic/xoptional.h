
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 13 December 2020
    \file xoptional.h
*/

#ifndef EXOTIC_XOPTIONAL_H
#define EXOTIC_XOPTIONAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "xcommon.h"

#ifdef __cplusplus
#if !defined(ALLOW_X_TYPES_WITH_ALTERNATIVES_IN_CPP) && __cplusplus >= 201103L
    #warning Do not use this type in C++ 11 and above, use the std::optional class instead
#endif
#define NULL 0
#endif


/**

*/
#define SETUP_XOPTIONAL_FOR(T)  typedef struct xoptional_##T##_s { \
    bool is_present ;\
    T value;\
} xoptional_##T;\
\
xoptional_##T xoptional_##T##_new(T value) {\
    xoptional_##T _x_gen_optional;\
    if (value == NULL) {\
        _x_gen_optional.is_present = FALSE;\
    } else {\
        _x_gen_optional.is_present = TRUE;\
        _x_gen_optional.value = value;\
    }\
    return _x_gen_optional;\
}\
\
xoptional_##T xoptional_##T##_new_empty() {\
    xoptional_##T _x_gen_optional;\
    _x_gen_optional.is_present = FALSE;\
    return _x_gen_optional;\
}\
\
void xoptional_##T##_if_present(xoptional_##T optional, \
        void (*xoption_if_##T##_present_func_ptr) (T const value)) {\
    if (xoptional_is_present(optional))  { \
        xoption_if_##T##_present_func_ptr(optional.value); \
    }\
}\
\
bool xoptional_##T##_filter_is_present(xoptional_##T optional, \
        bool (*xoption_filter_if_##T##_present_func_ptr) (T const value)) {\
    return (xoptional_is_present(optional) && xoption_filter_if_##T##_present_func_ptr(optional.value));\
}\
\
void xoptional_##T##_swap(xoptional_##T *optional1, xoptional_##T *optional2) {\
    xoptional_##T _x_gen_optional_x;\
    _x_gen_optional_x.value = optional1->value;\
    _x_gen_optional_x.is_present = optional1->is_present;\
    optional1->value = optional2->value;\
    optional1->is_present = optional2->is_present;\
    optional2->value = _x_gen_optional_x.value;\
    optional2->is_present = _x_gen_optional_x.is_present;\
}\
\


/**

*/
#define xoptional(T) xoptional_##T 

/**

*/
#define xoptional_new(T) xoptional_##T##_new 

/**

*/
#define xoptional_new_empty(T) xoptional_##T##_new_empty

/**

*/
#define xoptional_is_present(optional) (optional.is_present == TRUE && optional.value != NULL)

/**

*/
#define xoptional_is_empty(optional) (optional.is_present == FALSE || optional.value == NULL)

/**

*/
#define xoptional_value(optional) (optional.value)

/**

*/
#define xoptional_value_or(optional, fallback_value) ((optional.is_present == TRUE) ? optional.value : fallback_value)

/**

*/
#define xoptional_if_present(T) xoptional_##T##_if_present

/**

*/
#define xoptional_filter_is_present(T) xoptional_##T##_filter_is_present

/**

*/
#define xoptional_swap(T) xoptional_##T##_swap 

/**

*/
#define xoptional_reset(optional) { optional.is_present = FALSE; optional.value = NULL; }

#ifdef __cplusplus
}
#endif

#endif