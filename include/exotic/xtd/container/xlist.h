
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <iamthecarisma@gmail.com>
    \date 16 April 2021
    \file xlist.h
*/

#ifndef EXOTIC_XLIST_H
#define EXOTIC_XLIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <exotic/xtd/container/xnode.h>

#ifdef __cplusplus
#if !defined(ALLOW_XTD_TYPES_WITH_ALTERNATIVES_IN_CPP) && __cplusplus >= 201103L
    #warning Do not use this type in C++ 11 and above, use the std::list class instead
#endif
#endif

/*
    
*/
#define SETUP_XLIST_ONLY_NO_NODE_FOR(T) typedef struct xlist_##T##_s { \
    size_t size;\
    size_t max_size;\
    xnode_##T *head;\
    xnode_##T *tail;\
    void *(*memory_malloc)  (size_t size);\
    void *(*memory_calloc) (size_t blocks, size_t size);\
    void  (*memory_free)   (void *block);\
} xlist_##T;\
\
static enum x_stat xlist_##T##_new(xlist_##T **out);\
static enum x_stat xlist_##T##_new_config(struct xcontainer_config * const config, xlist_##T **out);\
static T xlist_##T##_unlink(xlist_##T *container, xnode_##T *node);\
static bool xlist_##T##_unlink_all(xlist_##T *container, void (*cb) (T));\
static enum x_stat xlist_##T##_get_node_at(xlist_##T *container, size_t index, xnode_##T **out);\
static xnode_##T *xlist_##T##_get_node(xlist_##T *container, T element);\
\
static enum x_stat xlist_##T##_new(xlist_##T **out) \
{\
    struct xcontainer_config config;\
    init_xcontainer_config(&config);\
    return xlist_##T##_new_config(&config, out);\
}\
\
static enum x_stat xlist_##T##_new_max_size(xlist_##T **out, size_t max_size) \
{\
    struct xcontainer_config config;\
    init_xcontainer_config_max_size(&config, max_size);\
    return xlist_##T##_new_config(&config, out);\
}\
\
static enum x_stat xlist_##T##_new_config(struct xcontainer_config * const config, xlist_##T **out) \
{\
    xlist_##T *container = (xlist_##T *) config->allocator.memory_calloc(1, sizeof(xlist_##T));\
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
static enum x_stat xlist_##T##_destroy(xlist_##T *container) \
{\
    container->memory_free((void *)container);\
    return XTD_OK;\
}\
\
static enum x_stat xlist_##T##_add_front(xlist_##T *container, T element)\
{\
    xnode_##T *node;\
    if (container->size >= container->max_size) {\
        return XTD_MAX_SIZE_ERR;\
    }\
    node = container->memory_calloc(1, sizeof(xnode_##T));\
    if (!node) {\
        return XTD_ALLOC_ERR;\
    }\
    node->data = element;\
    if (container->size == 0) {\
        container->head = node;\
        container->tail = node;\
    } else {\
        node->next = container->head;\
        container->head->prev = node;\
        container->head = node;\
    }\
    container->size++;\
    return XTD_OK;\
}\
\
static enum x_stat xlist_##T##_add_back(xlist_##T *container, T element)\
{\
    xnode_##T *node;\
    if (container->size >= container->max_size) {\
        return XTD_MAX_SIZE_ERR;\
    }\
    node = container->memory_calloc(1, sizeof(xnode_##T));\
    if (!node) {\
        return XTD_ALLOC_ERR;\
    }\
    node->data = element;\
    if (container->size == 0) {\
        container->head = node;\
        container->tail = node;\
    } else {\
        node->prev = container->tail;\
        container->tail->next = node;\
        container->tail = node;\
    }\
    container->size++;\
    return XTD_OK;\
}\
\
static enum x_stat xlist_##T##_add(xlist_##T *container, T element)\
{\
    return xlist_##T##_add_back(container, element);\
}\
\
static enum x_stat xlist_##T##_add_at(xlist_##T *container, T element, size_t index)\
{\
    xnode_##T *new_node;\
    xnode_##T *last_node;\
    enum x_stat status;\
    if (index == container->size) {\
        return xlist_##T##_add(container, element);\
    }\
    status = xlist_##T##_get_node_at(container, index, &last_node);\
    if (status != XTD_OK) {\
        return status;\
    }\
    if (container->size >= container->max_size) {\
        return XTD_MAX_SIZE_ERR;\
    }\
    new_node = container->memory_calloc(1, sizeof(xnode_##T));\
    if (!new_node) {\
        return XTD_ALLOC_ERR;\
    }\
    new_node->data = element;\
    xnode_link_at_back(last_node, new_node);\
    if (index == 0) {\
        container->head = new_node;\
    }\
    container->size++;\
    return XTD_OK;\
}\
\
static enum x_stat xlist_##T##_get_at(xlist_##T *container, size_t index, T *out)\
{\
    enum x_stat status;\
    xnode_##T *node;\
    if (!out) {\
        return XTD_OUT_PARAM_NULL_ERR;\
    }\
    if (index >= container->size) {\
        return XTD_INDEX_OUT_OF_RANGE_ERR;\
    }\
    status = xlist_##T##_get_node_at(container, index, &node);\
    if (status == XTD_OK) {\
        *out = node->data;\
    }\
    return status;\
}\
\
static enum x_stat xlist_##T##_get_front(xlist_##T *container, T *out)\
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
static enum x_stat xlist_##T##_get_back(xlist_##T *container, T *out)\
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
static enum x_stat xlist_##T##_replace_at(xlist_##T *container, size_t index, T element, T *out)\
{\
    enum x_stat status;\
    xnode_##T *node;\
    T old_data;\
    if (index >= container->size) {\
        return XTD_INDEX_OUT_OF_RANGE_ERR;\
    }\
    status = xlist_##T##_get_node_at(container, index, &node);\
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
static enum x_stat xlist_##T##_remove(xlist_##T *container, T element, T *out)\
{\
    xnode_##T *node = xlist_##T##_get_node(container, element);\
    if (!node) {\
        return XTD_VALUE_NOT_FOUND_ERR;\
    }\
    if (out) {\
        *out = node->data;\
    }\
    xlist_##T##_unlink(container, node);\
    return XTD_OK;\
}\
\
static enum x_stat xlist_##T##_remove_at(xlist_##T *container, size_t index, T *out)\
{\
    xnode_##T *node;\
    enum x_stat status = xlist_##T##_get_node_at(container, index, &node);\
    if (status != XTD_OK) {\
        return status;\
    }\
    if (out) {\
        *out = node->data;\
    }\
    xlist_##T##_unlink(container, node);\
    return XTD_OK;\
}\
\
static enum x_stat xlist_##T##_remove_front(xlist_##T *container, T *out)\
{\
    T element;\
    if (container->size == 0) {\
        return XTD_EMPTY_CONTAINER_ERR;\
    }\
    element = xlist_##T##_unlink(container, container->head);\
    if (out) {\
        *out = element;\
    }\
    return XTD_OK;\
}\
\
static enum x_stat xlist_##T##_remove_back(xlist_##T *container, T *out)\
{\
    T element;\
    if (container->size == 0) {\
        return XTD_EMPTY_CONTAINER_ERR;\
    }\
    element = xlist_##T##_unlink(container, container->tail);\
    if (out) {\
        *out = element;\
    }\
    return XTD_OK;\
}\
\
static enum x_stat xlist_##T##_clear(xlist_##T *container)\
{\
    bool unlinked_all = xlist_##T##_unlink_all(container, NULL);\
    if (unlinked_all) {\
        container->head = NULL;\
        container->tail = NULL;\
        return XTD_OK;\
    }\
    return XTD_EMPTY_CONTAINER_ERR;\
}\
\
static T xlist_##T##_unlink(xlist_##T *container, xnode_##T *node)\
{\
    T data = node->data;\
    if (node->prev != NULL) {\
        node->prev->next = node->next;\
    }\
    if (node->prev == NULL) {\
        container->head = node->next;\
    }\
    if (node->next == NULL) {\
        container->tail = node->prev;\
    }\
    if (node->next != NULL) {\
        node->next->prev = node->prev;\
    }\
    container->memory_free(node);\
    container->size--;\
    return data;\
}\
\
static bool xlist_##T##_unlink_all(xlist_##T *container, void (*cb) (T))\
{\
    xnode_##T *node;\
    if (container->size == 0) {\
        return false;\
    }\
    node = container->head;\
    while (node) {\
        xnode_##T *tmp = node->next;\
        if (cb) {\
            cb(node->data);\
        }\
        xlist_##T##_unlink(container, node);\
        node = tmp;\
    }\
    return true;\
}\
\
static enum x_stat xlist_##T##_get_node_at(xlist_##T *container, size_t index, xnode_##T **out)\
{\
    size_t position_index;\
    xnode_##T *node = XTD_NULL;\
    if (!out) {\
        return XTD_OUT_PARAM_NULL_ERR;\
    }\
    if (container == XTD_NULL || index >= container->size) {\
        return XTD_INDEX_OUT_OF_RANGE_ERR;\
    }\
    if (index < container->size / 2) {\
        node = container->head;\
        for (position_index =  0; position_index < index; position_index++) {\
            node = node->next;\
        }\
    } else {\
        node = container->tail;\
        for (position_index = container->size - 1; position_index > index; position_index--) {\
            node = node->prev;\
        }\
    }\
    *out = node;\
    return XTD_OK;\
}\
\
static xnode_##T *xlist_##T##_get_node(xlist_##T *container, T element)\
{\
    xnode_##T *node = container->head;\
    while (node) {\
        if (node->data == element)\
            return node;\
        node = node->next;\
    }\
    return NULL;\
}\
\
static enum x_stat xlist_##T##_index_of(xlist_##T *container, T element, size_t *index)\
{\
    size_t iter_index = 0;\
    xnode_##T *node = container->head;\
    while (node) {\
        if (node->data == element) {\
            *index = iter_index;\
            return XTD_OK;\
        }\
        node = node->next;\
        iter_index++;\
    }\
    return XTD_OUT_OF_RANGE_ERR;\
}\
\
static bool xlist_##T##_contains(xlist_##T *container, T element)\
{\
    size_t iter_index = 0;\
    xnode_##T *node = container->head;\
    while (node) {\
        if (node->data == element) return TRUE;\
        node = node->next;\
        iter_index++;\
    }\
    return FALSE;\
}\
\
static size_t xlist_##T##_element_count(xlist_##T *container, T element)\
{\
    size_t iter_index;\
    size_t occurence_count = 0;\
    xnode_##T *node = container->head;\
    while (node) {\
        if (node->data == element) {\
            occurence_count++;\
        }\
        node = node->next;\
        iter_index++;\
    }\
    return occurence_count;\
}\
\
\
\

/*
    
*/
#define SETUP_ITERATOR_FOR_XLIST(T) typedef struct xlist_iterator_##T##_s { \
    xnode_##T *forward_iter;\
    xnode_##T *backward_iter;\
    xlist_##T *container;\
} xlist_iterator_##T;\
\
static void xlist_iterator_##T##_reset_forward(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xlist_iterator_##T *xlist_iterator;\
    xlist_##T *container;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    xlist_iterator = ((xlist_iterator_##T *) iterator->container);\
    container = xlist_iterator->container;\
    xlist_iterator->forward_iter = container->head;\
    iterator->forward_index = 0;\
}\
\
static void xlist_iterator_##T##_reset_backward(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xlist_iterator_##T *xlist_iterator;\
    xlist_##T *container;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    xlist_iterator = ((xlist_iterator_##T *) iterator->container);\
    container = xlist_iterator->container;\
    xlist_iterator->backward_iter = container->tail;\
    iterator->backward_index = container->size-1;\
}\
\
static void xlist_iterator_##T##_reset(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xlist_iterator_##T *xlist_iterator;\
    xlist_##T *container;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    xlist_iterator = ((xlist_iterator_##T *) iterator->container);\
    container = xlist_iterator->container;\
    xlist_iterator->forward_iter = container->head;\
    xlist_iterator->backward_iter = container->tail;\
    iterator->forward_index = 0;\
    iterator->backward_index = container->size-1;\
}\
\
static void xlist_iterator_##T##_destroy(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xlist_iterator_##T *xlist_iterator;\
    xlist_##T *container;\
    if (iterator == XTD_NULL) {\
        return;\
    }\
    if (iterator->container == XTD_NULL) {\
        x_free(iterator);\
        return;\
    }\
    xlist_iterator = ((xlist_iterator_##T *) iterator->container);\
    container = xlist_iterator->container;\
    container->memory_free(xlist_iterator);\
    container->memory_free(iterator);\
}\
\
static void xlist_iterator_##T##_advance_by(void *iterator_, size_t distance) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xlist_iterator_##T *xlist_iterator;\
    xlist_##T *container;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    xlist_iterator = ((xlist_iterator_##T *) iterator->container);\
    container = xlist_iterator->container;\
    while (distance-- > 0 && xlist_iterator->forward_iter != XTD_NULL) {\
        xlist_iterator->forward_iter = xnode_get_next(xlist_iterator->forward_iter);\
        iterator->forward_index++;\
    }\
}\
\
static void xlist_iterator_##T##_decrement(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xlist_iterator_##T *xlist_iterator;\
    xlist_##T *container;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    xlist_iterator = ((xlist_iterator_##T *) iterator->container);\
    container = xlist_iterator->container;\
    if (xlist_iterator->forward_iter != XTD_NULL) {\
        xlist_iterator->forward_iter = xnode_get_prev(xlist_iterator->forward_iter);\
        iterator->forward_index--;\
    }\
    if (xlist_iterator->forward_iter == XTD_NULL) {\
        xlist_iterator->forward_iter = container->tail;\
    }\
}\
\
static void xlist_iterator_##T##_increment(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xlist_iterator_##T *xlist_iterator;\
    xlist_##T *container;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    xlist_iterator = ((xlist_iterator_##T *) iterator->container);\
    container = xlist_iterator->container;\
    if (xlist_iterator->forward_iter != XTD_NULL) {\
        xlist_iterator->forward_iter = xnode_get_next(xlist_iterator->forward_iter);\
        iterator->forward_index++;\
    }\
    if (xlist_iterator->forward_iter == XTD_NULL) {\
        xlist_iterator->forward_iter = container->head;\
    }\
}\
\
static bool xlist_iterator_##T##_has_next(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xlist_iterator_##T *xlist_iterator;\
    xlist_##T *container;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return FALSE;\
    }\
    xlist_iterator = ((xlist_iterator_##T *) iterator->container);\
    container = xlist_iterator->container;\
    return (container != XTD_NULL && xlist_iterator->forward_iter != XTD_NULL && xnode_has_data(xlist_iterator->forward_iter));\
}\
\
static T xlist_iterator_##T##_next(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xlist_iterator_##T *xlist_iterator;\
    xlist_##T *container;\
    T value;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return XTD_NULL;\
    }\
    xlist_iterator = ((xlist_iterator_##T *) iterator->container);\
    container = xlist_iterator->container;\
    value = xnode_get_data(xlist_iterator->forward_iter);\
    xlist_iterator->forward_iter = xnode_get_next(xlist_iterator->forward_iter);\
    iterator->forward_index++;\
    return value;\
}\
\
static bool xlist_iterator_##T##_has_prev(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xlist_iterator_##T *xlist_iterator;\
    xlist_##T *container;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return FALSE;\
    }\
    xlist_iterator = ((xlist_iterator_##T *) iterator->container);\
    container = xlist_iterator->container;\
    return (container != XTD_NULL && xlist_iterator->backward_iter != XTD_NULL && xnode_has_data(xlist_iterator->backward_iter));\
}\
\
static T xlist_iterator_##T##_prev(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    xlist_iterator_##T *xlist_iterator;\
    xlist_##T *container;\
    T value;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return XTD_NULL;\
    }\
    xlist_iterator = ((xlist_iterator_##T *) iterator->container);\
    container = xlist_iterator->container;\
    value = xnode_get_data(xlist_iterator->backward_iter);\
    xlist_iterator->backward_iter = xnode_get_prev(xlist_iterator->backward_iter);\
    iterator->backward_index++;\
    return value;\
}\
\
static XIterator *xiterator_init_xlist_##T(xlist_##T *container) \
{\
    XIterator *iterator;\
    xlist_iterator_##T *xlist_iterator;\
    if (container == XTD_NULL) {\
        return XTD_NULL;\
    }\
    iterator = (XIterator *) container->memory_malloc(sizeof(XIterator));\
    if (iterator == XTD_NULL) {\
        return XTD_NULL;\
    }\
    xlist_iterator = (xlist_iterator_##T *) container->memory_malloc(sizeof(xlist_iterator_##T));\
    if (xlist_iterator == XTD_NULL) {\
        container->memory_free(iterator);\
        return XTD_NULL;\
    }\
    xlist_iterator->container = container;\
    xlist_iterator->forward_iter = container->head;\
    xlist_iterator->backward_iter = container->tail;\
    iterator->forward_index = 0;\
    iterator->backward_index = container->size-1;\
    iterator->has_next = xlist_iterator_##T##_has_next;\
    iterator->next = (xiterator_next) xlist_iterator_##T##_next;\
    iterator->has_prev = xlist_iterator_##T##_has_prev;\
    iterator->prev = (xiterator_prev) xlist_iterator_##T##_prev;\
    iterator->reset_forward = xlist_iterator_##T##_reset_forward;\
    iterator->reset_backward = xlist_iterator_##T##_reset_backward;\
    iterator->reset = xlist_iterator_##T##_reset;\
    iterator->destroy = xlist_iterator_##T##_destroy;\
    iterator->advance_by = xlist_iterator_##T##_advance_by;\
    iterator->increment = xlist_iterator_##T##_increment;\
    iterator->decrement = xlist_iterator_##T##_decrement;\
    iterator->container = xlist_iterator;\
    return iterator;\
}\
\
\
\

/**

*/
#define xlist(T) xlist_##T

/**

*/
#define xlist_new(T) xlist_##T##_new

/**

*/
#define xlist_new_max_size(T) xlist_##T##_new_max_size

/**

*/
#define xlist_new_config(T) xlist_##T##_new_config

/**

*/
#define xlist_index_of(T) xlist_##T##_index_of

/**

*/
#define xlist_contains(T) xlist_##T##_contains

/**

*/
#define xlist_element_count(T) xlist_##T##_element_count

/**

*/
#define xlist_destroy(T) xlist_##T##_destroy

/**

*/
#define xlist_add_front(T) xlist_##T##_add_front

/**

*/
#define xlist_add_back(T) xlist_##T##_add_back

/**

*/
#define xlist_add(T) xlist_##T##_add

/**

*/
#define xlist_add_at(T) xlist_##T##_add_at

/**

*/
#define xlist_get_at(T) xlist_##T##_get_at

/**

*/
#define xlist_get_front(T) xlist_##T##_get_front

/**

*/
#define xlist_get_back(T) xlist_##T##_get_back

/**

*/
#define xlist_replace_at(T) xlist_##T##_replace_at

/**

*/
#define xlist_remove(T) xlist_##T##_remove

/**

*/
#define xlist_remove_at(T) xlist_##T##_remove_at

/**

*/
#define xlist_remove_front(T) xlist_##T##_remove_front

/**

*/
#define xlist_remove_back(T) xlist_##T##_remove_back

/**

*/
#define xlist_clear(T) xlist_##T##_clear

/**

*/
#define xlist_get_node_at(T) xlist_##T##_get_node_at

/**

*/
#define xlist_get_node(T) xlist_##T##_get_node

/*

*/
#define xlist_capacity xcapacity

/*

*/
#define xlist_size xsize

/*

*/
#define xlist_max_size xmax_size

/*

*/
#define xlist_is_empty xis_empty

/**

*/
#define xlist_iterator(T) xlist_iterator_##T

/*

*/
#define SETUP_XLIST_ONLY_FOR(T) SETUP_XNODE_FOR(T) SETUP_XLIST_ONLY_NO_NODE_FOR(T)

/*

*/
#define SETUP_XLIST_FOR(T) SETUP_XLIST_ONLY_FOR(T) SETUP_ITERATOR_FOR_XLIST(T)



#ifdef __cplusplus
}
#endif

#endif
