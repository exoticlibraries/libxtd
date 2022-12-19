
/**
    \copyright MIT License Copyright (c) 2022, Adewale Azeez 
    \author Adewale Azeez <iamthecarisma@gmail.com>
    \date 01 April 2022
    \file xring.c
*/

#ifndef EXOTIC_XRING_H
#define EXOTIC_XRING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "xcircular_buffer.h"
#include <exotic/xtd/xiterator.h>

/**

*/
#define SETUP_XRING_ONLY_FOR SETUP_XCIRCULAR_BUFFER_ONLY_FOR

/**

*/
#define SETUP_ITERATOR_FOR_XRING(T) SETUP_ITERATOR_FOR_XCIRCULAR_BUFFER(T) \
\
static void xring_iterator_##T##_reset_forward(void *iterator_) {\
    xcircular_buffer_iterator_##T##_reset_forward(iterator_);\
}\
\
static void xring_iterator_##T##_reset_backward(void *iterator_) {\
    xcircular_buffer_iterator_##T##_reset_backward(iterator_);\
}\
\
static void xring_iterator_##T##_reset(void *iterator_) {\
    xcircular_buffer_iterator_##T##_reset(iterator_);\
}\
\
static void xring_iterator_##T##_destroy(void *iterator_) {\
    xcircular_buffer_iterator_##T##_destroy(iterator_);\
}\
\
static void xring_iterator_##T##_advance_by(void *iterator_, size_t distance) {\
    xcircular_buffer_iterator_##T##_advance_by(iterator_, distance);\
}\
\
static void xring_iterator_##T##_decrement(void *iterator_) {\
    xcircular_buffer_iterator_##T##_decrement(iterator_);\
}\
\
static void xring_iterator_##T##_increment(void *iterator_) {\
    xcircular_buffer_iterator_##T##_increment(iterator_);\
}\
\
static bool xring_iterator_##T##_has_next(void *iterator_) {\
    return xcircular_buffer_iterator_##T##_has_next(iterator_);\
}\
\
static T xring_iterator_##T##_next(void *iterator_) {\
    return xcircular_buffer_iterator_##T##_next(iterator_);\
}\
\
static bool xring_iterator_##T##_has_prev(void *iterator_) {\
    return xcircular_buffer_iterator_##T##_has_prev(iterator_);\
}\
\
static T xring_iterator_##T##_prev(void *iterator_) {\
    return xcircular_buffer_iterator_##T##_prev(iterator_);\
}\
\
static XIterator *xiterator_init_xring_##T(xcircular_buffer_##T *container) \
{\
    return xiterator_init_xcircular_buffer_##T(container);\
}\
\
\

/**

*/
#define xring xcircular_buffer


/**

*/
#define xring_new xcircular_buffer_new

/**

*/
#define xring_new_config xcircular_buffer_new_config

/**

*/
#define xring_add xcircular_buffer_add

/**

*/
#define xring_enqueue xcircular_buffer_enqueue

/**

*/
#define xring_enqueue_cb xcircular_buffer_enqueue_cb

/**

*/
#define xring_enqueue_is_full xcircular_buffer_enqueue_is_full

/**

*/
#define xring_enqueue_is_empty xcircular_buffer_enqueue_is_empty

/**

*/
#define xring_get_at xcircular_buffer_get_at

/**

*/
#define xring_get xcircular_buffer_get

/**

*/
#define xring_dequeue_at xcircular_buffer_dequeue_at

/**

*/
#define xring_dequeue xcircular_buffer_dequeue

/**

*/
#define xring_destroy xcircular_buffer_destroy

/**

*/
#define xiterator_init_xring xiterator_init_xcircular_buffer

/*

*/
#define xring_capacity xcapacity

/*

*/
#define xring_size xsize

/*

*/
#define xring_max_size xmax_size

/*

*/
#define xring_is_empty xis_empty

/**

*/
#define SETUP_XRING_FOR(T) SETUP_XRING_ONLY_FOR(T) SETUP_ITERATOR_FOR_XRING(T)

#ifdef __cplusplus
}
#endif

#endif
