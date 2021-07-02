
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 17 April 2021
    \file xslist.h
*/

#ifndef EXOTIC_XSLIST_H
#define EXOTIC_XSLIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "xnode.h"

/*#ifdef __cplusplus
#if !defined(ALLOW_XTD_TYPES_WITH_ALTERNATIVES_IN_CPP) && __cplusplus >= 201103L
    #warning Do not use this type in C++ 11 and above, use the std::list class instead
#endif
#endif*/

/*
    
*/
#define SETUP_XSLIST_ONLY_NO_NODE_FOR(T) typedef struct xslist_##T##_s { \
    size_t size;\
    size_t max_size;\
    xsingle_node_##T *head;\
    xsingle_node_##T *tail;\
    void *(*memory_malloc)  (size_t size);\
    void *(*memory_calloc) (size_t blocks, size_t size);\
    void  (*memory_free)   (void *block);\
} xslist_##T;\
\
enum x_stat xslist_##T##_new(xslist_##T **out);\
enum x_stat xslist_##T##_new_config(struct xcontainer_config * const config, xslist_##T **out);\
static T xslist_##T##_unlink(xslist_##T *container, xsingle_node_##T *node, xsingle_node_##T *prev);\
static bool xslist_##T##_unlink_all(xslist_##T *container, void (*cb) (T));\
static enum x_stat xslist_##T##_get_node_at(xslist_##T *container, size_t index, xsingle_node_##T **out, xsingle_node_##T **prev);\
static enum x_stat xslist_##T##_get_node(xslist_##T *container, T element, xsingle_node_##T **node, xsingle_node_##T **prev);\
\
enum x_stat xslist_##T##_new(xslist_##T **out) \
{\
    struct xcontainer_config config;\
    init_xcontainer_config(&config);\
    return xslist_##T##_new_config(&config, out);\
}\
\
enum x_stat xslist_##T##_new_max_size(xslist_##T **out, size_t max_size) \
{\
    struct xcontainer_config config;\
    init_xcontainer_config_max_size(&config, max_size);\
    return xslist_##T##_new_config(&config, out);\
}\
\
enum x_stat xslist_##T##_new_config(struct xcontainer_config * const config, xslist_##T **out) \
{\
    xslist_##T *container = (xslist_##T *) config->allocator.memory_calloc(1, sizeof(xslist_##T));\
    if (!container) {\
        return XTD_ALLOC_ERR;\
    }\
    container->size          = 0;\
    container->max_size      = config->max_size;\
    container->memory_malloc  = config->allocator.memory_malloc;\
    container->memory_calloc = config->allocator.memory_calloc;\
    container->memory_free   = config->allocator.memory_free;\
    *out = container;\
    return XTD_OK;\
}\
\
enum x_stat xslist_##T##_destroy(xslist_##T *container) \
{\
    container->memory_free((void *)container);\
    return XTD_OK;\
}\
\
enum x_stat xslist_##T##_add_front(xslist_##T *container, T element)\
{\
    xsingle_node_##T *node;\
    if (container->size >= container->max_size) {\
        return XTD_MAX_SIZE_ERR;\
    }\
    node = container->memory_calloc(1, sizeof(xsingle_node_##T));\
    if (!node) {\
        return XTD_ALLOC_ERR;\
    }\
    node->data = element;\
    if (container->size == 0) {\
        container->head = node;\
        container->tail = node;\
    } else {\
        node->next = container->head;\
        container->head = node;\
    }\
    container->size++;\
    return XTD_OK;\
}\
\
enum x_stat xslist_##T##_add_back(xslist_##T *container, T element)\
{\
    xsingle_node_##T *node;\
    if (container->size >= container->max_size) {\
        return XTD_MAX_SIZE_ERR;\
    }\
    node = container->memory_calloc(1, sizeof(xsingle_node_##T));\
    if (!node) {\
        return XTD_ALLOC_ERR;\
    }\
    node->data = element;\
    if (container->size == 0) {\
        container->head = node;\
        container->tail = node;\
    } else {\
        container->tail->next = node;\
        container->tail = node;\
    }\
    container->size++;\
    return XTD_OK;\
}\
\
enum x_stat xslist_##T##_add(xslist_##T *container, T element)\
{\
    return xslist_##T##_add_back(container, element);\
}\
\
enum x_stat xslist_##T##_add_at(xslist_##T *container, T element, size_t index)\
{\
    xsingle_node_##T *new_node;\
    xsingle_node_##T *prev_node;\
    xsingle_node_##T *last_node;\
    enum x_stat status;\
    if (index == container->size) {\
        return xslist_##T##_add(container, element);\
    }\
    status = xslist_##T##_get_node_at(container, index, &last_node, &prev_node);\
    if (status != XTD_OK) {\
        return status;\
    }\
    if (container->size >= container->max_size) {\
        return XTD_MAX_SIZE_ERR;\
    }\
    new_node = container->memory_calloc(1, sizeof(xsingle_node_##T));\
    if (!new_node) {\
        return XTD_ALLOC_ERR;\
    }\
    new_node->data = element;\
    if (!prev_node) {\
        new_node->next  = container->head;\
        container->head = new_node;\
    } else {\
        xsingle_node_##T *tmp = prev_node->next;\
        prev_node->next = new_node;\
        new_node->next  = tmp;\
    }\
    if (index == 0) {\
        container->head = new_node;\
    }\
    container->size++;\
    return XTD_OK;\
}\
\
enum x_stat xslist_##T##_get_at(xslist_##T *container, size_t index, T *out)\
{\
    enum x_stat status;\
    xsingle_node_##T *node;\
    xsingle_node_##T *prev;\
    if (!out) {\
        return XTD_OUT_PARAM_NULL_ERR;\
    }\
    if (index >= container->size) {\
        return XTD_INDEX_OUT_OF_RANGE_ERR;\
    }\
    status = xslist_##T##_get_node_at(container, index, &node, &prev);\
    if (status == XTD_OK) {\
        *out = node->data;\
    }\
    return status;\
}\
\
enum x_stat xslist_##T##_get_front(xslist_##T *container, T *out)\
{\
    if (!out) {\
        return XTD_OUT_PARAM_NULL_ERR;\
    }\
    if (container->size == 0) {\
        return XTD_EMPTY_CONTAINER_ERR;\
    }\
    *out = container->head->data;\
    return XTD_OK;\
}\
\
enum x_stat xslist_##T##_get_back(xslist_##T *container, T *out)\
{\
    size_t last;\
    if (!out) {\
        return XTD_OUT_PARAM_NULL_ERR;\
    }\
    if (container->size == 0) {\
        return XTD_EMPTY_CONTAINER_ERR;\
    }\
    *out = container->tail->data;\
    return XTD_OK;\
}\
\
enum x_stat xslist_##T##_replace_at(xslist_##T *container, size_t index, T element, T *out)\
{\
    enum x_stat status;\
    xsingle_node_##T *node;\
    xsingle_node_##T *prev;\
    T old_data;\
    if (index >= container->size) {\
        return XTD_INDEX_OUT_OF_RANGE_ERR;\
    }\
    status = xslist_##T##_get_node_at(container, index, &node, &prev);\
    if (status == XTD_OK) {\
        old_data = node->data;\
        node->data = element;\
        if (out) {\
            *out = old_data;\
        }\
    }\
    return XTD_OK;\
}\
\
enum x_stat xslist_##T##_remove(xslist_##T *container, T element, T *out)\
{\
    enum x_stat status;\
    xsingle_node_##T *node;\
    xsingle_node_##T *prev;\
    T old_data;\
    status = xslist_##T##_get_node(container, element, &node, &prev);\
    if (status != XTD_OK) {\
        return status;\
    }\
    old_data = xslist_##T##_unlink(container, node, prev);\
    if (out) {\
        *out = old_data;\
    }\
    return XTD_OK;\
}\
\
enum x_stat xslist_##T##_remove_at(xslist_##T *container, size_t index, T *out)\
{\
    xsingle_node_##T *node;\
    xsingle_node_##T *prev;\
    T old_data;\
    enum x_stat status = xslist_##T##_get_node_at(container, index, &node, &prev);\
    if (status != XTD_OK) {\
        return status;\
    }\
    old_data = xslist_##T##_unlink(container, node, prev);\
    if (out) {\
        *out = old_data;\
    }\
    return XTD_OK;\
}\
\
enum x_stat xslist_##T##_remove_front(xslist_##T *container, T *out)\
{\
    T element;\
    if (container->size == 0) {\
        return XTD_EMPTY_CONTAINER_ERR;\
    }\
    element = xslist_##T##_unlink(container, container->head, XTD_NULL);\
    if (out) {\
        *out = element;\
    }\
    return XTD_OK;\
}\
\
enum x_stat xslist_##T##_remove_back(xslist_##T *container, T *out)\
{\
    T element;\
    enum x_stat status;\
    xsingle_node_##T *node;\
    xsingle_node_##T *prev;\
    if (container->size == 0) {\
        return XTD_EMPTY_CONTAINER_ERR;\
    }\
    status = xslist_##T##_get_node_at(container, container->size - 1, &node, &prev);\
    if (status != XTD_OK) {\
        return status;\
    }\
    element = xslist_##T##_unlink(container, node, prev);\
    if (out) {\
        *out = element;\
    }\
    return XTD_OK;\
}\
\
enum x_stat xslist_##T##_clear(xslist_##T *container)\
{\
    bool unlinked_all = xslist_##T##_unlink_all(container, XTD_NULL);\
    if (unlinked_all) {\
        container->head = XTD_NULL;\
        container->tail = XTD_NULL;\
        return XTD_OK;\
    }\
    return XTD_EMPTY_CONTAINER_ERR;\
}\
\
xsingle_node_##T *xslist_##T##_find_previous_node(xslist_##T *container, xsingle_node_##T *node)\
{\
    xsingle_node_##T *current_node = container->head;\
    while (current_node->next != XTD_NULL) {\
        if (current_node->next == node) {\
            return current_node;\
        } else {\
            current_node = current_node->next;\
        }\
    }\
    return XTD_NULL;\
}\
\
static T xslist_##T##_unlink(xslist_##T *container, xsingle_node_##T *node, xsingle_node_##T *prev)\
{\
    T data = node->data;\
    if (prev != XTD_NULL) {\
        prev->next = node->next;\
    } else {\
        container->head = node->next;\
    }\
    if (node->next == XTD_NULL) {\
        container->tail = prev;\
    }\
    container->memory_free(node);\
    container->size--;\
    return data;\
}\
\
static bool xslist_##T##_unlink_all(xslist_##T *container, void (*cb) (T))\
{\
    xsingle_node_##T *node;\
    if (container->size == 0) {\
        return FALSE;\
    }\
    node = container->head;\
    while (node) {\
        xsingle_node_##T *tmp = node->next;\
        if (cb) {\
            cb(node->data);\
        }\
        container->memory_free(node);\
        node = tmp;\
        container->size--;\
    }\
    return TRUE;\
}\
\
static enum x_stat xslist_##T##_get_node_at(xslist_##T *container, size_t index, xsingle_node_##T **out, xsingle_node_##T **prev)\
{\
    size_t position_index;\
    xsingle_node_##T *node = XTD_NULL;\
    if (!out) {\
        return XTD_OUT_PARAM_NULL_ERR;\
    }\
    if (!prev) {\
        return XTD_OUT_PARAM_NULL_ERR;\
    }\
    if (container == XTD_NULL || index >= container->size) {\
        return XTD_INDEX_OUT_OF_RANGE_ERR;\
    }\
    *out = container->head;\
    *prev = XTD_NULL;\
    for (position_index = 0; position_index < index; position_index++) {\
        *prev = *out;\
        *out = (*out)->next;\
    }\
    return XTD_OK;\
}\
\
static enum x_stat xslist_##T##_get_node(xslist_##T *container, T element, xsingle_node_##T **node, xsingle_node_##T **prev)\
{\
    if (!node) {\
        return XTD_OUT_PARAM_NULL_ERR;\
    }\
    if (!prev) {\
        return XTD_OUT_PARAM_NULL_ERR;\
    }\
    *node = container->head;\
    *prev = XTD_NULL;\
    while (*node) {\
        if ((*node)->data == element)\
            return XTD_OK;\
        *prev = *node;\
        *node = (*node)->next;\
    }\
    return XTD_VALUE_NOT_FOUND_ERR;\
}\
\
\
\

/*
    
*/
#define SETUP_ITERATOR_FOR_XSLIST(T) typedef struct xslist_iterator_##T##_s { \
    xsingle_node_##T *forward_iter;\
    xsingle_node_##T *backward_iter;\
    xslist_##T *container;\
} xslist_iterator_##T;\
\
void xslist_iterator_##T##_reset_forward(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xslist_iterator_##T *xslist_iterator;\
    xslist_##T *container;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    xslist_iterator = ((xslist_iterator_##T *) iterator->container);\
    container = xslist_iterator->container;\
    xslist_iterator->forward_iter = container->head;\
    iterator->forward_index = 0;\
}\
\
void xslist_iterator_##T##_reset_backward(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xslist_iterator_##T *xslist_iterator;\
    xslist_##T *container;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    xslist_iterator = ((xslist_iterator_##T *) iterator->container);\
    container = xslist_iterator->container;\
    xslist_iterator->backward_iter = container->tail;\
    iterator->backward_index = container->size-1;\
}\
\
void xslist_iterator_##T##_reset(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xslist_iterator_##T *xslist_iterator;\
    xslist_##T *container;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    xslist_iterator = ((xslist_iterator_##T *) iterator->container);\
    container = xslist_iterator->container;\
    xslist_iterator->forward_iter = container->head;\
    xslist_iterator->backward_iter = container->tail;\
    iterator->forward_index = 0;\
    iterator->backward_index = container->size-1;\
}\
\
void xslist_iterator_##T##_destroy(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xslist_iterator_##T *xslist_iterator;\
    xslist_##T *container;\
    if (iterator == XTD_NULL) {\
        return;\
    }\
    if (iterator->container == XTD_NULL) {\
        x_free(iterator);\
        return;\
    }\
    xslist_iterator = ((xslist_iterator_##T *) iterator->container);\
    container = xslist_iterator->container;\
    container->memory_free(xslist_iterator);\
    container->memory_free(iterator);\
}\
\
void xslist_iterator_##T##_advance_by(void *iterator_, size_t distance) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xslist_iterator_##T *xslist_iterator;\
    xslist_##T *container;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    xslist_iterator = ((xslist_iterator_##T *) iterator->container);\
    container = xslist_iterator->container;\
    while (distance-- > 0 && xslist_iterator->forward_iter != XTD_NULL) {\
        xslist_iterator->forward_iter = xsingle_node_get_next(xslist_iterator->forward_iter);\
        iterator->forward_index++;\
    }\
}\
\
void xslist_iterator_##T##_decrement(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xslist_iterator_##T *xslist_iterator;\
    xslist_##T *container;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    xslist_iterator = ((xslist_iterator_##T *) iterator->container);\
    container = xslist_iterator->container;\
    if (xslist_iterator->forward_iter != XTD_NULL) {\
        xslist_iterator->forward_iter = xslist_##T##_find_previous_node(container, xslist_iterator->forward_iter);\
        iterator->forward_index--;\
    }\
    if (xslist_iterator->forward_iter == XTD_NULL) {\
        xslist_iterator->forward_iter = container->tail;\
    }\
}\
\
void xslist_iterator_##T##_increment(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xslist_iterator_##T *xslist_iterator;\
    xslist_##T *container;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    xslist_iterator = ((xslist_iterator_##T *) iterator->container);\
    container = xslist_iterator->container;\
    if (xslist_iterator->forward_iter != XTD_NULL) {\
        xslist_iterator->forward_iter = xsingle_node_get_next(xslist_iterator->forward_iter);\
        iterator->forward_index++;\
    }\
    if (xslist_iterator->forward_iter == XTD_NULL) {\
        xslist_iterator->forward_iter = container->head;\
    }\
}\
\
bool xslist_iterator_##T##_has_next(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xslist_iterator_##T *xslist_iterator;\
    xslist_##T *container;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return FALSE;\
    }\
    xslist_iterator = ((xslist_iterator_##T *) iterator->container);\
    container = xslist_iterator->container;\
    return (container != XTD_NULL && xslist_iterator->forward_iter != XTD_NULL && xsingle_node_has_data(xslist_iterator->forward_iter));\
}\
\
void *xslist_iterator_##T##_next(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xslist_iterator_##T *xslist_iterator;\
    xslist_##T *container;\
    T value;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return XTD_NULL;\
    }\
    xslist_iterator = ((xslist_iterator_##T *) iterator->container);\
    container = xslist_iterator->container;\
    value = xsingle_node_get_data(xslist_iterator->forward_iter);\
    xslist_iterator->forward_iter = xsingle_node_get_next(xslist_iterator->forward_iter);\
    iterator->forward_index++;\
    return (void *) value;\
}\
\
bool xslist_iterator_##T##_has_prev(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xslist_iterator_##T *xslist_iterator;\
    xslist_##T *container;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return FALSE;\
    }\
    xslist_iterator = ((xslist_iterator_##T *) iterator->container);\
    container = xslist_iterator->container;\
    return (container != XTD_NULL && xslist_iterator->backward_iter != XTD_NULL && xsingle_node_has_data(xslist_iterator->backward_iter));\
}\
\
void *xslist_iterator_##T##_prev(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xslist_iterator_##T *xslist_iterator;\
    xslist_##T *container;\
    T value;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return XTD_NULL;\
    }\
    xslist_iterator = ((xslist_iterator_##T *) iterator->container);\
    container = xslist_iterator->container;\
    value = xsingle_node_get_data(xslist_iterator->backward_iter);\
    xslist_iterator->backward_iter = xslist_##T##_find_previous_node(container, xslist_iterator->backward_iter);\
    iterator->backward_index++;\
    return (void *) value;\
}\
\
static XIterator *xiterator_init_xslist_##T(xslist_##T *container) \
{\
    XIterator *iterator;\
    xslist_iterator_##T *xslist_iterator;\
    if (container == XTD_NULL) {\
        return XTD_NULL;\
    }\
    iterator = (XIterator *) container->memory_malloc(sizeof(XIterator));\
    if (iterator == XTD_NULL) {\
        return XTD_NULL;\
    }\
    xslist_iterator = (xslist_iterator_##T *) container->memory_malloc(sizeof(xslist_iterator_##T));\
    if (xslist_iterator == XTD_NULL) {\
        container->memory_free(iterator);\
        return XTD_NULL;\
    }\
    xslist_iterator->container = container;\
    xslist_iterator->forward_iter = container->head;\
    xslist_iterator->backward_iter = container->tail;\
    iterator->forward_index = 0;\
    iterator->backward_index = container->size-1;\
    iterator->has_next = xslist_iterator_##T##_has_next;\
    iterator->next = xslist_iterator_##T##_next;\
    iterator->has_prev = xslist_iterator_##T##_has_prev;\
    iterator->prev = xslist_iterator_##T##_prev;\
    iterator->reset_forward = xslist_iterator_##T##_reset_forward;\
    iterator->reset_backward = xslist_iterator_##T##_reset_backward;\
    iterator->reset = xslist_iterator_##T##_reset;\
    iterator->destroy = xslist_iterator_##T##_destroy;\
    iterator->advance_by = xslist_iterator_##T##_advance_by;\
    iterator->increment = xslist_iterator_##T##_increment;\
    iterator->decrement = xslist_iterator_##T##_decrement;\
    iterator->container = xslist_iterator;\
    return iterator;\
}\
\
\
\

/**

*/
#define xslist(T) xslist_##T

/**

*/
#define xslist_new(T) xslist_##T##_new

/**

*/
#define xslist_new_max_size(T) xslist_##T##_new_max_size

/**

*/
#define xslist_new_config(T) xslist_##T##_new_config

/**

*/
#define xslist_destroy(T) xslist_##T##_destroy

/**

*/
#define xslist_add_front(T) xslist_##T##_add_front

/**

*/
#define xslist_add_back(T) xslist_##T##_add_back

/**

*/
#define xslist_add(T) xslist_##T##_add

/**

*/
#define xslist_add_at(T) xslist_##T##_add_at

/**

*/
#define xslist_get_at(T) xslist_##T##_get_at

/**

*/
#define xslist_get_front(T) xslist_##T##_get_front

/**

*/
#define xslist_get_back(T) xslist_##T##_get_back

/**

*/
#define xslist_replace_at(T) xslist_##T##_replace_at

/**

*/
#define xslist_remove(T) xslist_##T##_remove

/**

*/
#define xslist_remove_at(T) xslist_##T##_remove_at

/**

*/
#define xslist_remove_front(T) xslist_##T##_remove_front

/**

*/
#define xslist_remove_back(T) xslist_##T##_remove_back

/**

*/
#define xslist_clear(T) xslist_##T##_clear

/**

*/
#define xslist_previous_node(T) xslist_##T##_find_previous_node

/**

*/
#define xslist_get_node_at(T) xslist_##T##_get_node_at

/**

*/
#define xslist_get_node(T) xslist_##T##_get_node

/*

*/
#define xslist_capacity xcapacity

/*

*/
#define xslist_size xsize

/*

*/
#define xslist_max_size xmax_size

/*

*/
#define xslist_is_empty xis_empty

/**

*/
#define xslist_iterator(T) xslist_iterator_##T

/*

*/
#define SETUP_XSLIST_ONLY_FOR(T) SETUP_XSINGLE_NODE_FOR(T) SETUP_XSLIST_ONLY_NO_NODE_FOR(T)

/*

*/
#define SETUP_XSLIST_FOR(T) SETUP_XSLIST_ONLY_FOR(T) SETUP_ITERATOR_FOR_XSLIST(T)



#ifdef __cplusplus
}
#endif

#endif