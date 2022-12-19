
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <iamthecarisma@gmail.com>
    \date 19 June 2021
    \file xunordered_set.h
*/

#ifndef EXOTIC_XUNORDERED_SET_H
#define EXOTIC_XUNORDERED_SET_H

#ifdef __cplusplus
extern "C" {
#endif

#include "xset.h"

#ifdef __cplusplus
#if !defined(ALLOW_XTD_TYPES_WITH_ALTERNATIVES_IN_CPP) && __cplusplus >= 201103L
    #warning Do not use this type in C++ 11 and above, use the std::unordered_set class instead
#endif
#endif

/*
    
*/
#define SETUP_XUNORDERED_SET_ONLY_FOR_INTERNAL__(T) typedef xset_##T xunordered_set_##T; \
\
static enum x_stat xunordered_set_##T##_new_config(struct xcontainer_config * const config, xset_##T **out, bool (*xset_element_equals)  (T,T));\
\
static enum x_stat xunordered_set_##T##_new(xset_##T **out, bool (*xset_element_equals)  (T,T)) \
{\
    struct xcontainer_config config;\
    init_xcontainer_config(&config);\
    return xunordered_set_##T##_new_config(&config, out, xset_element_equals);\
}\
\
static enum x_stat xunordered_set_##T##_new_max_size(xset_##T **out, size_t max_size, bool (*xset_element_equals)  (T,T)) \
{\
    struct xcontainer_config config;\
    init_xcontainer_config_max_size(&config, max_size);\
    return xunordered_set_##T##_new_config(&config, out, xset_element_equals);\
}\
\
static enum x_stat xunordered_set_##T##_new_config(struct xcontainer_config * const config, xset_##T **out, bool (*xset_element_equals)  (T,T)) \
{\
    return xset_##T##_new_config(config, out, xset_element_equals, XTD_NULL);\
}\
\
\
\

/*

*/
#define SETUP_ITERATOR_FOR_XSET_INTERNAL__(T)\
\
static XIterator *xiterator_init_xunordered_set_##T(xset_##T *container) {\
    return xiterator_init_xset_##T(container);\
}\
\
\
\

/**

*/
#define xunordered_set(T) xset_##T

/**

*/
#define xunordered_set_new(T) xunordered_set_##T##_new

/**

*/
#define xunordered_set_new_max_size(T) xunordered_set_##T##_new_max_size

/**

*/
#define xunordered_set_new_config(T) xunordered_set_##T##_new_config

/**

*/
#define xunordered_set_index_of(T) xset_##T##_index_of

/**

*/
#define xunordered_set_contains(T) xset_##T##_contains

/**

*/
#define xunordered_set_element_count(T) xset_##T##_element_count

/**

*/
#define xunordered_set_add(T) xset_##T##_add

/**

*/
#define xunordered_set_add_at(T) xset_##T##_add_at

/**

*/
#define xunordered_set_get_at(T) xset_##T##_get_at

/**

*/
#define xunordered_set_get_front(T) xset_##T##_get_front

/**

*/
#define xunordered_set_get_back(T) xset_##T##_get_back

/**

*/
#define xunordered_set_replace_at(T) xset_##T##_replace_at

/**

*/
#define xunordered_set_remove_front(T) xset_##T##_remove_front

/**

*/
#define xunordered_set_remove_back(T) xset_##T##_remove_back

/**

*/
#define xunordered_set_remove_at(T) xset_##T##_remove_at

/**

*/
#define xunordered_set_clear(T) xset_##T##_clear

/**

*/
#define xunordered_set_shrink_to_fit(T) xset_##T##_shrink_to_fit

/**

*/
#define xunordered_set_destroy(container) xset_destroy(container)

/**

*/
#define xiterator_init_xunordered_set(T) xiterator_init_xset_##T

/*

*/
#define xunordered_set_capacity xcapacity

/*

*/
#define xunordered_set_size xsize

/*

*/
#define xunordered_set_max_size xmax_size

/*

*/
#define xunordered_set_is_empty xis_empty

/*
    
*/
#define SETUP_XUNORDERED_SET_ONLY_FOR(T) SETUP_XSET_ONLY_FOR(T) SETUP_XUNORDERED_SET_ONLY_FOR_INTERNAL__(T)

/*
    
*/
#define SETUP_ITERATOR_FOR_XUNORDERED_SET(T) SETUP_ITERATOR_FOR_XSET(T) SETUP_ITERATOR_FOR_XSET_INTERNAL__(T)

/*

*/
#define SETUP_XUNORDERED_SET_FOR(T) SETUP_XUNORDERED_SET_ONLY_FOR(T) SETUP_ITERATOR_FOR_XUNORDERED_SET(T)


#ifdef __cplusplus
}
#endif

#endif
