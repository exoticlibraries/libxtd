
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 24 June 2020
    \file iterator.h
*/

#ifndef EXOTIC_XOPTIONAL_H
#define EXOTIC_XOPTIONAL_H

#include "xconf.h"

#ifdef __cplusplus
#if !defined(ALLOW_X_TYPES_WITH_ALTERNATIVES_IN_CPP) && __cplusplus >= 201103L
    #warning Do not use this type in C++ 11 and above, use the std::optional class instead
#endif
#define NULL 0
#endif


/**

*/
#define SETUP_OPTIONAL_FOR(type)  typedef struct xoptional_##type##_s { \
    bool is_present ;\
    type value;\
} xoptional_##type;\
\
xoptional_##type xoptional_##type##_new(type value) {\
    xoptional_##type _x_gen_optional;\
    if (value == NULL) {\
        _x_gen_optional.is_present = FALSE;\
    } else {\
        _x_gen_optional.is_present = TRUE;\
        _x_gen_optional.value = value;\
    }\
    return _x_gen_optional;\
}\
\
xoptional_##type xoptional_##type##_new_empty() {\
    xoptional_##type _x_gen_optional;\
    _x_gen_optional.is_present = FALSE;\
    return _x_gen_optional;\
}\
\
void xoptional_##type##_if_present(xoptional_##type optional, \
        void (*xoption_if_##type##_present_func_ptr) (type const value)) {\
    if (xoptional_is_present(optional))  { \
        xoption_if_##type##_present_func_ptr(optional.value); \
    }\
}\
\
bool xoptional_##type##_filter_is_present(xoptional_##type optional, \
        bool (*xoption_filter_if_##type##_present_func_ptr) (type const value)) {\
    return (xoptional_is_present(optional) && xoption_filter_if_##type##_present_func_ptr(optional.value));\
}\
\
void xoptional_##type##_swap(xoptional_##type *optional1, xoptional_##type *optional2) {\
    xoptional_##type _x_gen_optional_x;\
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
#define xoptional(type) xoptional_##type 

/**

*/
#define xoptional_new(type) xoptional_##type##_new 

/**

*/
#define xoptional_new_empty(type) xoptional_##type##_new_empty

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
#define xoptional_if_present(type) xoptional_##type##_if_present

/**

*/
#define xoptional_filter_is_present(type) xoptional_##type##_filter_is_present

/**

*/
#define xoptional_swap__internal(optionalRef, optional1, optional2) { optional2 = optional1; optional2 = optional1; }

/**

*/
#define xoptional_swap(type) xoptional_##type##_swap 

/**

*/
#define xoptional_reset(optional) { optional.is_present = FALSE; optional.value = NULL; }

#endif