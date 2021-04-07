
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 20 December 2020
    \file xvector.h
*/

#ifndef EXOTIC_XVECTOR_H
#define EXOTIC_XVECTOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "xcommon.h"

/*
    
*/
#define SETUP_XSINGLE_NODE_FOR(T) typedef struct T##_xsingle_node_s { \
    T data;\
    struct T##_xsingle_node_s *next;\
} T##_XSingle_Node;\
\

/*
    
*/
#define SETUP_XSINGLE_NODE_WITH_ITER_FOR(T) typedef struct T##_xsingle_node_s { \
    T data;\
    struct T##_xsingle_node_s *next;\
    struct T##_xsingle_node_s *iter;\
} T##_XSingle_Node;\
\
void xiterator_reset_xsingle_node_##T(T##_XSingle_Node *node)\
{\
    node->iter = node;\
}\
\
unsigned int xiterator_has_next_xsingle_node_##T(T##_XSingle_Node *node)\
{\
    if (node->iter == XTD_NULL) {\
        node->iter = node;\
    }\
    return xnode_has_next(node->iter);\
}\
\
int xiterator_next_xsingle_node_##T(T##_XSingle_Node *node)\
{\
    T value = xnode_get_next_data(node->iter);\
    node->iter = xnode_get_next(node->iter);\
    return value;\
}\
\
\

/*
    
*/
#define SETUP_XNODE_FOR(T) typedef struct T##_xnode_s { \
    T data;\
    struct T##_xnode_s *next;\
    struct T##_xnode_s *prev;\
} T##_XNode;\
\

/**

*/
#define SETUP_XNODE_WITH_ITER_FOR(T) typedef struct T##_xnode_s { \
    T data;\
    struct T##_xnode_s *next;\
    struct T##_xnode_s *prev;\
    struct T##_xnode_s *iter;\
} T##_XNode;\
\
void xiterator_reset_xnode_##T(T##_XNode *node)\
{\
    node->iter = node;\
}\
\
unsigned int xiterator_has_next_xnode_##T(T##_XNode *node)\
{\
    if (node->iter == XTD_NULL) {\
        node->iter = node;\
    }\
    return xnode_has_next(node->iter);\
}\
\
int xiterator_next_xnode_##T(T##_XNode *node)\
{\
    T value = xnode_get_next_data(node->iter);\
    node->iter = xnode_get_next(node->iter);\
    return value;\
}\
\
unsigned int xiterator_has_prev_xnode_##T(T##_XNode *node)\
{\
    if (node->iter == XTD_NULL) {\
        node->iter = node;\
    }\
    return xnode_has_prev(node->iter);\
}\
\
int xiterator_prev_xnode_##T(T##_XNode *node)\
{\
    T value = xnode_get_prev_data(node->iter);\
    node->iter = xnode_get_prev(node->iter);\
    return value;\
}\
\
\

/**

*/
#define xsingle_node(T) T##_XSingle_Node

/**

*/
#define xnode(T) T##_XNode

/**

*/
#define xnode_get_data(node) (node->data)

/**

*/
#define xnode_set_data(node, value) {node->data = value;}

/**

*/
#define xnode_has_prev(node) (node->prev != XTD_NULL)

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
#define xnode_has_next(node) (node->next != XTD_NULL)

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


#ifdef __cplusplus
}
#endif

#endif

