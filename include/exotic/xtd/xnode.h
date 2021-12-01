
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <iamthecarisma@gmail.com>
    \date 1 April 2021
    \file xnode.h
*/

#ifndef EXOTIC_XNODE_H
#define EXOTIC_XNODE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "xcommon.h"

/*
    
*/
#define SETUP_XSINGLE_NODE_FOR(T) typedef struct xsingle_node_##T##_s { \
    T data;\
    struct xsingle_node_##T##_s *next;\
} xsingle_node_##T;\
\

/*
    
*/
#define SETUP_XSINGLE_NODE_WITH_ITER_FOR(T) typedef struct xsingle_node_##T##_s { \
    T data;\
    struct xsingle_node_##T##_s *next;\
    struct xsingle_node_##T##_s *iter;\
} xsingle_node_##T;\
\
static void xiterator_reset_xsingle_node_##T(xsingle_node_##T *node)\
{\
    node->iter = node;\
}\
\
static unsigned int xiterator_has_next_xsingle_node_##T(xsingle_node_##T *node)\
{\
    if (node->iter == XTD_NULL) {\
        node->iter = node;\
    }\
    return xnode_has_next(node->iter);\
}\
\
static int xiterator_next_xsingle_node_##T(xsingle_node_##T *node)\
{\
    T value = xnode_get_next_data(node->iter);\
    node->iter = xnode_get_next(node->iter);\
    return value;\
}\
\
\

/*
    
*/
#define SETUP_XNODE_FOR(T) typedef struct xnode_##T##_s { \
    T data;\
    struct xnode_##T##_s *next;\
    struct xnode_##T##_s *prev;\
} xnode_##T;\
\

/**

*/
#define SETUP_XNODE_WITH_ITER_FOR(T) typedef struct xnode_##T##_s { \
    T data;\
    struct xnode_##T##_s *next;\
    struct xnode_##T##_s *prev;\
    struct xnode_##T##_s *iter;\
} xnode_##T;\
\
static void xiterator_reset_xnode_##T(xnode_##T *node)\
{\
    node->iter = node;\
}\
\
static unsigned int xiterator_has_next_xnode_##T(xnode_##T *node)\
{\
    if (node->iter == XTD_NULL) {\
        node->iter = node;\
    }\
    return xnode_has_next(node->iter);\
}\
\
static T xiterator_next_xnode_##T(xnode_##T *node)\
{\
    T value = xnode_get_next_data(node->iter);\
    node->iter = xnode_get_next(node->iter);\
    return value;\
}\
\
static unsigned int xiterator_has_prev_xnode_##T(xnode_##T *node)\
{\
    if (node->iter == XTD_NULL) {\
        node->iter = node;\
    }\
    return xnode_has_prev(node->iter);\
}\
\
static T xiterator_prev_xnode_##T(xnode_##T *node)\
{\
    T value = xnode_get_prev_data(node->iter);\
    node->iter = xnode_get_prev(node->iter);\
    return value;\
}\
\
\

/**

*/
#define xsingle_node(T) xsingle_node_##T

/**

*/
#define xnode(T) xnode_##T

/**

*/
#define xnode_has_data(node) (node != XTD_NULL && node->data != XTD_NULL)

/**

*/
#define xnode_get_data(node) (node ? node->data : XTD_NULL)

/**

*/
#define xnode_set_data(node, value) {node->data = value;}

/**

*/
#define xnode_has_prev(node) (node != XTD_NULL && node->prev != XTD_NULL)

/**

*/
#define xnode_get_prev(node) (node->prev)

/**

*/
#define xnode_link_prev(node, value) {node->prev = value;}

/**

*/
#define xnode_get_prev_data(node) (node->prev->data)

/**

*/
#define xnode_set_prev_data(node, value) {if (node->prev != XTD_NULL) { node->prev->data = value; }}

/**

*/
#define xnode_has_next(node) (node != XTD_NULL && node->next != XTD_NULL)

/**

*/
#define xnode_get_next(node) (node->next)

/**

*/
#define xnode_link_next(node, value) {node->next = value;}

/**

*/
#define xnode_get_next_data(node) (node->next->data)

/**

*/
#define xnode_set_next_data(node, value) {if (node->next != XTD_NULL) { node->next->data = value; }}

/* FIllers */

/**

*/
#define xsingle_node_has_data xnode_has_data

/**

*/
#define xsingle_node_get_data xnode_get_data

/**

*/
#define xsingle_node_set_data xnode_set_data

/**

*/
#define xsingle_node_has_prev xnode_has_prev

/**

*/
#define xsingle_node_get_prev xnode_get_prev

/**

*/
#define xsingle_node_link_prev xnode_link_prev

/**

*/
#define xsingle_node_get_prev_data xnode_get_prev_data

/**

*/
#define xsingle_node_set_prev_data xnode_set_prev_data

/**

*/
#define xsingle_node_has_next xnode_has_next

/**

*/
#define xsingle_node_get_next xnode_get_next

/**

*/
#define xsingle_node_link_next xnode_link_next

/**

*/
#define xsingle_node_get_next_data xnode_get_next_data

/**

*/
#define xsingle_node_set_next_data xnode_set_next_data

/**

*/
#define xnode_link_at_back(base_node, child_node) {\
        if (child_node->next != XTD_NULL) {\
            child_node->next->prev = child_node->prev;\
        }\
        if (child_node->prev != XTD_NULL) {\
            child_node->prev->next = child_node->next;\
        }\
        if (base_node->prev == XTD_NULL) {\
            child_node->prev = XTD_NULL;\
            child_node->next = base_node;\
            base_node->prev  = child_node;\
        } else {\
            child_node->prev = base_node->prev;\
            child_node->prev->next = child_node;\
            child_node->next  = base_node;\
            base_node->prev  = child_node;\
        }\
    }

/**

*/
#define xnode_link_at_front(base_node, child_node) {\
        if (child_node->next != XTD_NULL) {\
            child_node->next->prev = child_node->prev;\
        }\
        if (child_node->prev != XTD_NULL) {\
            child_node->prev->next = child_node->next;\
        }\
        if (base_node->prev == XTD_NULL) {\
            child_node->prev = base_node;\
            base_node->next = child_node;\
            child_node->next  = XTD_NULL;\
        } else {\
            child_node->next = base_node->next;\
            child_node->next->prev = child_node;\
            child_node->prev  = base_node;\
            base_node->next  = child_node;\
        }\
    }


#ifdef __cplusplus
}
#endif

#endif

