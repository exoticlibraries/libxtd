
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 21 June 2021
    \file xhashtable.h
*/

#ifndef EXOTIC_XHASHTABLE_H
#define EXOTIC_XHASHTABLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "xmath.h"
#include "xvector.h"

#ifdef __cplusplus
#if !defined(ALLOW_XTD_TYPES_WITH_ALTERNATIVES_IN_CPP) && __cplusplus >= 201103L
    #warning Do not use this type in C++ 11 and above, use the std::map class instead
#endif
#endif

/*
    
*/
#define SETUP_XHASHTABLE_ENTRY_ONLY_FOR(T1, T2) typedef struct xhashtable_entry_##T1##_##T2##_s { \
    T1 key;\
    T2 value;\
    size_t hash;\
    struct xhashtable_entry_##T1##_##T2##_s *next;\
} xhashtable_entry_##T1##_##T2;\
\
\
\

/*
    
*/
#define SETUP_XHASHTABLE_ONLY_FOR(T1, T2) typedef struct xhashtable_##T1##_##T2##_s { \
    size_t capacity;\
    size_t size;\
    size_t max_size;\
    size_t threshold;\
    uint32_t hash_seed;\
    int key_length;\
    float load_factor;\
    xhashtable_entry_##T1##_##T2 **buffer;\
    bool (*compare_key)(const T1 key1, const T1 key2);\
    size_t (*hash_key)(const T1 key, int length, uint32_t seed);\
    void *(*memory_malloc)  (size_t size);\
    void *(*memory_calloc) (size_t blocks, size_t size);\
    void  (*memory_free)   (void *block);\
} xhashtable_##T1##_##T2;\
\
enum x_stat xhashtable_##T1##_##T2##_new_config(struct xcontainer_config * const config, xhashtable_##T1##_##T2 **out, bool (*compare_key)(const T1, const T1), size_t (*hash_key)(const T1, int, uint32_t));\
static enum x_stat xhashtable_##T1##_##T2##_resize(xhashtable_##T1##_##T2 *container, size_t new_capacity);\
static __XTD_INLINE__ size_t xhashtable_##T1##_##T2##_get_entry_index(xhashtable_##T1##_##T2 *container, T1 key);\
\
enum x_stat xhashtable_##T1##_##T2##_new(xhashtable_##T1##_##T2 **out, bool (*compare_key)(const T1, const T1), size_t (*hash_key)(const T1, int, uint32_t)) \
{\
    struct xcontainer_config config;\
    init_xcontainer_config(&config);\
    return xhashtable_##T1##_##T2##_new_config(&config, out, compare_key, hash_key);\
}\
\
enum x_stat xhashtable_##T1##_##T2##_new_max_size(xhashtable_##T1##_##T2 **out, size_t max_size, bool (*compare_key)(const T1, const T1), size_t (*hash_key)(const T1, int, uint32_t)) \
{\
    struct xcontainer_config config;\
    init_xcontainer_config_max_size(&config, max_size);\
    return xhashtable_##T1##_##T2##_new_config(&config, out, compare_key, hash_key);\
}\
\
enum x_stat xhashtable_##T1##_##T2##_new_config(struct xcontainer_config * const config, xhashtable_##T1##_##T2 **out, bool (*compare_key)(const T1, const T1), size_t (*hash_key)(const T1, int, uint32_t)) \
{\
\
    xhashtable_##T1##_##T2 *container = (xhashtable_##T1##_##T2 *) config->allocator.memory_calloc(1, sizeof(xhashtable_##T1##_##T2));\
    if (!container) {\
        return XTD_ALLOC_ERR;\
    }\
    container->capacity = xmath_round_power_of_two(config->capacity);\
    container->buffer  = (xhashtable_entry_##T1##_##T2 **) config->allocator.memory_calloc(container->capacity, sizeof(xhashtable_entry_##T1##_##T2 *));\
    if (!container->buffer) {\
        config->allocator.memory_free(container);\
        return XTD_ALLOC_ERR;\
    }\
    container->hash_key      = hash_key;\
    container->compare_key   = compare_key;\
    container->load_factor   = config->load_factor;\
    container->hash_seed     = config->hash_seed;\
    container->key_length    = config->key_length;\
    container->size          = 0;\
    container->memory_malloc = config->allocator.memory_malloc;\
    container->memory_calloc = config->allocator.memory_calloc;\
    container->memory_free   = config->allocator.memory_free;\
    container->threshold     = container->capacity * container->load_factor;\
    *out = container;\
    return XTD_OK;\
}\
\
void xhashtable_##T1##_##T2##_destroy(xhashtable_##T1##_##T2 *container) {\
    size_t index;\
    for (index = 0; index < container->capacity; index++) {\
        xhashtable_entry_##T1##_##T2 *current_entry = container->buffer[index];\
        while (current_entry) {\
            xhashtable_entry_##T1##_##T2 *tmp_entry = current_entry->next;\
            container->memory_free(current_entry);\
            current_entry = tmp_entry;\
        }\
    }\
    container->memory_free(container->buffer);\
    container->memory_free(container);\
}\
\
static enum x_stat xhashtable_##T1##_##T2##_put_null_key(xhashtable_##T1##_##T2 *container, T2 value) {\
    xhashtable_entry_##T1##_##T2 *new_entry;\
    xhashtable_entry_##T1##_##T2 *existing_entry = container->buffer[0];\
    while (existing_entry) {\
        if (!existing_entry->key) {\
            existing_entry->value = value;\
            return XTD_OK;\
        }\
        existing_entry = existing_entry->next;\
    }\
    new_entry = container->memory_malloc(sizeof(xhashtable_entry_##T1##_##T2));\
    if (!new_entry) {\
        return XTD_ALLOC_ERR;\
    }\
    new_entry->key   = XTD_NULL;\
    new_entry->value = value;\
    new_entry->hash  = 0;\
    new_entry->next  = container->buffer[0];\
    container->buffer[0] = new_entry;\
    container->size++;\
    return XTD_OK;\
}\
\
enum x_stat xhashtable_##T1##_##T2##_put(xhashtable_##T1##_##T2 *container, T1 key, T2 value) {\
    enum x_stat status;\
    xhashtable_entry_##T1##_##T2 *existing_entry;\
    xhashtable_entry_##T1##_##T2 *new_entry;\
    if (container->size >= container->threshold) {\
        if ((status = xhashtable_##T1##_##T2##_resize(container, container->capacity << 1)) != XTD_OK) {\
            return status;\
        }\
    }\
    if (key == XTD_NULL) {\
        return xhashtable_##T1##_##T2##_put_null_key(container, value);\
    }\
    {\
        const size_t hash = container->hash_key(key, container->key_length, container->hash_seed);\
        const size_t index = hash & (container->capacity - 1);\
        existing_entry = container->buffer[index];\
        while (existing_entry) {\
            T1 existing_entry_key = existing_entry->key;\
            if (existing_entry_key != XTD_NULL && container->compare_key(existing_entry_key, key)) {\
                existing_entry->value = value;\
                return XTD_OK;\
            }\
            existing_entry = existing_entry->next;\
        }\
        new_entry = container->memory_malloc(sizeof(xhashtable_entry_##T1##_##T2));\
        if (!new_entry) {\
            return XTD_ALLOC_ERR;\
        }\
        new_entry->key   = key;\
        new_entry->value = value;\
        new_entry->hash  = hash;\
        new_entry->next  = container->buffer[index];\
        container->buffer[index] = new_entry;\
        container->size++;\
    }\
    return XTD_OK;\
}\
\
static enum x_stat xhashtable_##T1##_##T2##_get_null_key(xhashtable_##T1##_##T2 *container, T2 *out) {\
    xhashtable_entry_##T1##_##T2 *entry = container->buffer[0];\
    while (entry) {\
        if (entry->key == XTD_NULL) {\
            *out = entry->value;\
            return XTD_OK;\
        }\
        entry = entry->next;\
    }\
    return XTD_KEY_NOT_FOUND_ERR;\
}\
\
enum x_stat xhashtable_##T1##_##T2##_get(xhashtable_##T1##_##T2 *container, T1 key, T2 *out) {\
    size_t index;\
    xhashtable_entry_##T1##_##T2 *entry;\
    if (key == XTD_NULL) {\
        return xhashtable_##T1##_##T2##_get_null_key(container, out);\
    }\
    index = xhashtable_##T1##_##T2##_get_entry_index(container, key);\
    entry = container->buffer[index];\
    while (entry) {\
        if (entry->key != XTD_NULL && container->compare_key(entry->key, key)) {\
            *out = entry->value;\
            return XTD_OK;\
        }\
        entry = entry->next;\
    }\
    return XTD_KEY_NOT_FOUND_ERR;\
}\
\
enum x_stat xhashtable_##T1##_##T2##_remove_null_key(xhashtable_##T1##_##T2 *container, T2 *out) {\
    xhashtable_entry_##T1##_##T2 *entry = container->buffer[0];\
    xhashtable_entry_##T1##_##T2 *prev_entry = XTD_NULL;\
    xhashtable_entry_##T1##_##T2 *next_entry = XTD_NULL;\
    while (entry) {\
        next_entry = entry->next;\
        if (entry->key == XTD_NULL) {\
            T2 value = entry->value;\
            if (!prev_entry) {\
                container->buffer[0] = next_entry;\
            } else {\
                prev_entry->next = next_entry;\
            }\
            container->memory_free(entry);\
            container->size--;\
            if (out) {\
                *out = value;\
            }\
            return XTD_OK;\
        }\
        prev_entry = entry;\
        entry = next_entry;\
    }\
    return XTD_KEY_NOT_FOUND_ERR;\
}\
\
enum x_stat xhashtable_##T1##_##T2##_remove(xhashtable_##T1##_##T2 *container, T1 key, T2 *out) {\
    if (key == XTD_NULL) {\
        return xhashtable_##T1##_##T2##_remove_null_key(container, out);\
    }\
    {\
        const size_t index = xhashtable_##T1##_##T2##_get_entry_index(container, key);\
        xhashtable_entry_##T1##_##T2 *entry = container->buffer[index];\
        xhashtable_entry_##T1##_##T2 *prev_entry = XTD_NULL;\
        xhashtable_entry_##T1##_##T2 *next_entry = XTD_NULL;\
        while (entry) {\
            next_entry = entry->next;\
            if (entry->key != XTD_NULL && container->compare_key(key, entry->key)) {\
                T2 value = entry->value;\
                if (!prev_entry) {\
                    container->buffer[index] = next_entry;\
                } else {\
                    prev_entry->next = next_entry;\
                }\
                container->memory_free(entry);\
                container->size--;\
                if (out) {\
                    *out = value;\
                }\
                return XTD_OK;\
            }\
            prev_entry = entry;\
            entry = next_entry;\
        }\
    }\
    return XTD_KEY_NOT_FOUND_ERR;\
}\
\
void xhashtable_##T1##_##T2##_remove_all(xhashtable_##T1##_##T2 *container) {\
    size_t index;\
    for (index = 0; index < container->capacity; index++) {\
        xhashtable_entry_##T1##_##T2 *entry = container->buffer[index];\
        while (entry) {\
            xhashtable_entry_##T1##_##T2 *next = entry->next;\
            container->memory_free(entry);\
            container->size--;\
            entry = next;\
        }\
        container->buffer[index] = XTD_NULL;\
    }\
}\
\
bool xhashtable_##T1##_##T2##_contains_key(xhashtable_##T1##_##T2 *container, T1 key) {\
    xhashtable_entry_##T1##_##T2 *entry = container->buffer[xhashtable_##T1##_##T2##_get_entry_index(container, key)];\
    while (entry) {\
        if (container->compare_key(key, entry->key)) {\
            return TRUE;\
        }\
        entry = entry->next;\
    }\
    return FALSE;\
}\
\
static __XTD_INLINE__ size_t xhashtable_##T1##_##T2##_get_entry_index(xhashtable_##T1##_##T2 *container, T1 key) {\
    size_t hash = container->hash_key(key, container->key_length, container->hash_seed);\
    return hash & (container->capacity - 1);\
}\
\
static __XTD_INLINE__ void xhashtable_##T1##_##T2##_move_buffer(xhashtable_entry_##T1##_##T2 **src_buffer, xhashtable_entry_##T1##_##T2 **dest_buffer, size_t src_size, size_t dest_size) {\
    size_t pos;\
    for (pos = 0; pos < src_size; pos++) {\
        xhashtable_entry_##T1##_##T2 *entry = src_buffer[pos];\
        while (entry) {\
            xhashtable_entry_##T1##_##T2 *next  = entry->next;\
            size_t index = entry->hash & (dest_size - 1);\
            entry->next = dest_buffer[index];\
            dest_buffer[index] = entry;\
            entry = next;\
        }\
    }\
}\
\
static enum x_stat xhashtable_##T1##_##T2##_resize(xhashtable_##T1##_##T2 *container, size_t new_capacity)\
{\
    xhashtable_entry_##T1##_##T2 **new_buffer;\
    xhashtable_entry_##T1##_##T2 **old_buffer;\
    if (container->capacity == XTD_MATH_MAX_POW_TWO) {\
        return XTD_MAX_CAPACITY_ERR;\
    }\
    new_buffer = container->memory_calloc(new_capacity, sizeof(xhashtable_entry_##T1##_##T2));\
    if (!new_buffer) {\
        return XTD_ALLOC_ERR;\
    }\
    old_buffer = container->buffer;\
    xhashtable_##T1##_##T2##_move_buffer(old_buffer, new_buffer, container->capacity, new_capacity);\
    container->buffer   = new_buffer;\
    container->capacity  = new_capacity;\
    container->threshold = container->load_factor * new_capacity;\
    container->memory_free(old_buffer);\
    return XTD_OK;\
}\
\
\
\

/*
    
*/
#define SETUP_GET_KEYS_VALUES_XVECTOR_FOR_XHASHTABLE(T1, T2)\
\
enum x_stat xhashtable_##T1##_##T2##_get_keys(xhashtable_##T1##_##T2 *container, xvector(T1) **out) {\
    size_t index;\
    enum x_stat status;\
    xvector(T1) *keys;\
    struct xcontainer_config config;\
    init_xcontainer_config_max_size(&config, container->size);\
    config.capacity = container->size;\
    config.allocator.memory_malloc = container->memory_malloc;\
    config.allocator.memory_calloc = container->memory_calloc;\
    config.allocator.memory_free   = container->memory_free;\
    status = xvector_new_config(T1)(&config, &keys);\
    if (status != XTD_OK) {\
        return status;\
    }\
    for (index = 0; index < container->capacity; index++) {\
        xhashtable_entry_##T1##_##T2 *entry = container->buffer[index];\
        while (entry) {\
            if ((status = xvector_add(T1)(keys, entry->key)) == XTD_OK) {\
                entry = entry->next;\
            } else {\
                xvector_destroy(keys);\
                return status;\
            }\
        }\
    }\
    *out = keys;\
    return XTD_OK;\
}\
\
enum x_stat xhashtable_##T1##_##T2##_get_values(xhashtable_##T1##_##T2 *container, xvector(T2) **out) {\
    size_t index;\
    enum x_stat status;\
    xvector(T2) *values;\
    struct xcontainer_config config;\
    init_xcontainer_config_max_size(&config, container->size);\
    config.capacity = container->size;\
    config.allocator.memory_malloc = container->memory_malloc;\
    config.allocator.memory_calloc = container->memory_calloc;\
    config.allocator.memory_free   = container->memory_free;\
    status = xvector_new_config(T2)(&config, &values);\
    if (status != XTD_OK) {\
        return status;\
    }\
    for (index = 0; index < container->capacity; index++) {\
        xhashtable_entry_##T1##_##T2 *entry = container->buffer[index];\
        while (entry) {\
            if ((status = xvector_add(T2)(values, entry->value)) == XTD_OK) {\
                entry = entry->next;\
            } else {\
                xvector_destroy(values);\
                return status;\
            }\
        }\
    }\
    *out = values;\
    return XTD_OK;\
}\
\
\
\

/*
    
*/
#define SETUP_ITERATOR_FOR_XHASHTABLE(T1, T2) typedef struct xhashtable_iterator_##T1##_##T2##_s { \
    xhashtable_entry_##T1##_##T2 *forward_iter;\
    xhashtable_entry_##T1##_##T2 *backward_iter;\
    xhashtable_entry_##T1##_##T2 *last_forward_value;\
    size_t buffer_index;\
    size_t buffer_reverse_index;\
    xhashtable_##T1##_##T2 *container;\
} xhashtable_iterator_##T1##_##T2;\
\
void xhashtable_iterator_##T1##_##T2##_reset_forward(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    iterator->forward_index = 0;\
}\
\
void xhashtable_iterator_##T1##_##T2##_reset_backward(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    iterator->backward_index = ((xhashtable_##T1##_##T2 *) iterator->container)->size-1;\
}\
\
void xhashtable_iterator_##T1##_##T2##_reset(void *iterator_) {\
    size_t index, reverse_index;\
    xhashtable_iterator_##T1##_##T2 *xhashtable_iterator;\
    xhashtable_##T1##_##T2 *container;\
    XIterator *iterator = (XIterator *) iterator_;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    xhashtable_iterator = ((xhashtable_iterator_##T1##_##T2 *) iterator->container);\
    container = xhashtable_iterator->container;\
    iterator->forward_index = 0;\
    iterator->backward_index = container->size-1;\
    xhashtable_iterator->buffer_index = 0;\
    xhashtable_iterator->buffer_reverse_index = 0;\
    xhashtable_iterator->forward_iter = XTD_NULL;\
    xhashtable_iterator->backward_iter = XTD_NULL;\
    for (index = 0, reverse_index = container->capacity-1; index < container->capacity, reverse_index >= 0; index++, reverse_index--) {\
        if (xhashtable_iterator->forward_iter == XTD_NULL) {\
            xhashtable_entry_##T1##_##T2 *entry = container->buffer[index];\
            if (entry) {\
                xhashtable_iterator->buffer_index = index;\
                xhashtable_iterator->forward_iter = entry;\
                if (xhashtable_iterator->backward_iter != XTD_NULL) {\
                    break;\
                }\
            }\
        }\
        if (xhashtable_iterator->backward_iter == XTD_NULL) {\
            xhashtable_entry_##T1##_##T2 *reverse_entry = container->buffer[reverse_index];\
            if (reverse_entry) {\
                xhashtable_iterator->buffer_reverse_index = reverse_index;\
                xhashtable_iterator->backward_iter = reverse_entry;\
                if (xhashtable_iterator->forward_iter != XTD_NULL) {\
                    break;\
                }\
            }\
        }\
    }\
}\
\
void xhashtable_iterator_##T1##_##T2##_destroy(void *iterator_) {\
    xhashtable_iterator_##T1##_##T2 *xhashtable_iterator;\
    XIterator *iterator = (XIterator *) iterator_;\
    if (iterator == XTD_NULL) {\
        return;\
    }\
    if (iterator->container != XTD_NULL) {\
        xhashtable_iterator = ((xhashtable_iterator_##T1##_##T2 *) iterator->container);\
        xhashtable_iterator->container->memory_free(xhashtable_iterator);\
        xhashtable_iterator->container->memory_free(iterator);\
        return;\
    }\
    x_free(iterator);\
}\
\
bool xhashtable_iterator_##T1##_##T2##_has_next(void *iterator_) {\
    xhashtable_##T1##_##T2 *container;\
    xhashtable_iterator_##T1##_##T2 *xhashtable_iterator;\
    XIterator *iterator = (XIterator *) iterator_;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return FALSE;\
    }\
    xhashtable_iterator = ((xhashtable_iterator_##T1##_##T2 *) iterator->container);\
    container = xhashtable_iterator->container;\
    return container->size > 0 && xhashtable_iterator->forward_iter != XTD_NULL;\
}\
\
void *xhashtable_iterator_##T1##_##T2##_next(void *iterator_) {\
    size_t index;\
    xhashtable_##T1##_##T2 *container;\
    xhashtable_iterator_##T1##_##T2 *xhashtable_iterator;\
    XIterator *iterator = (XIterator *) iterator_;\
    xhashtable_entry_##T1##_##T2 *entry;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return XTD_NULL;\
    }\
    xhashtable_iterator = ((xhashtable_iterator_##T1##_##T2 *) iterator->container);\
    container = xhashtable_iterator->container;\
    entry = xhashtable_iterator->forward_iter;\
    xhashtable_iterator->last_forward_value = entry;\
    xhashtable_iterator->forward_iter = entry->next;\
    iterator->forward_index++;\
    if (xhashtable_iterator->forward_iter == XTD_NULL) {\
        for (index = xhashtable_iterator->buffer_index + 1; index < xhashtable_iterator->container->capacity; index++) {\
            xhashtable_iterator->forward_iter = xhashtable_iterator->container->buffer[index];\
            if (xhashtable_iterator->forward_iter) {\
                xhashtable_iterator->buffer_index = index;\
                break;\
            }\
        }\
    }\
    return (void *) entry;\
}\
\
bool xhashtable_iterator_##T1##_##T2##_has_prev(void *iterator_) {\
    xhashtable_##T1##_##T2 *container;\
    xhashtable_iterator_##T1##_##T2 *xhashtable_iterator;\
    XIterator *iterator = (XIterator *) iterator_;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return FALSE;\
    }\
    xhashtable_iterator = ((xhashtable_iterator_##T1##_##T2 *) iterator->container);\
    container = xhashtable_iterator->container;\
    return container->size > 0 && xhashtable_iterator->backward_iter != XTD_NULL;\
}\
\
void *xhashtable_iterator_##T1##_##T2##_prev(void *iterator_) {\
    size_t index;\
    xhashtable_##T1##_##T2 *container;\
    xhashtable_iterator_##T1##_##T2 *xhashtable_iterator;\
    XIterator *iterator = (XIterator *) iterator_;\
    xhashtable_entry_##T1##_##T2 *entry;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return XTD_NULL;\
    }\
    xhashtable_iterator = ((xhashtable_iterator_##T1##_##T2 *) iterator->container);\
    container = xhashtable_iterator->container;\
    entry = xhashtable_iterator->backward_iter;\
    xhashtable_iterator->backward_iter = entry->next;\
    iterator->backward_index++;\
    if (xhashtable_iterator->backward_iter == XTD_NULL) {\
        for (index = xhashtable_iterator->buffer_reverse_index-1; index > 0; index--) {\
            xhashtable_iterator->backward_iter = xhashtable_iterator->container->buffer[index];\
            if (xhashtable_iterator->backward_iter) {\
                xhashtable_iterator->buffer_reverse_index = index;\
                break;\
            }\
        }\
    }\
    return (void *) entry;\
}\
\
void xhashtable_iterator_##T1##_##T2##_advance_by(void *iterator_, size_t distance) {\
    xhashtable_iterator_##T1##_##T2 *xhashtable_iterator;\
    XIterator *iterator = (XIterator *) iterator_;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    xhashtable_iterator = ((xhashtable_iterator_##T1##_##T2 *) iterator->container);\
    iterator->forward_index += distance;\
    while (xhashtable_iterator->forward_iter != XTD_NULL && distance-- > 0) {\
        xhashtable_iterator_##T1##_##T2##_next(iterator_);\
    }\
}\
\
void xhashtable_iterator_##T1##_##T2##_decrement(void *iterator_) {\
    size_t index;\
    size_t cached_buffer_reverse_index;\
    xhashtable_entry_##T1##_##T2 *cached_entry;\
    xhashtable_iterator_##T1##_##T2 *xhashtable_iterator;\
    XIterator *iterator = (XIterator *) iterator_;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    xhashtable_iterator = ((xhashtable_iterator_##T1##_##T2 *) iterator->container);\
    if (iterator->forward_index > 0) {\
        for (index = 0; index < xhashtable_iterator->container->capacity; index++) {\
            if (xhashtable_iterator->last_forward_value == xhashtable_iterator->container->buffer[index]) {\
                break;\
            }\
            xhashtable_iterator->forward_iter = xhashtable_iterator->container->buffer[index];\
            if (xhashtable_iterator->forward_iter) {\
                xhashtable_iterator->buffer_index = index;\
                break;\
            }\
        }\
    }\
    iterator->forward_index--;\
}\
\
void xhashtable_iterator_##T1##_##T2##_increment(void *iterator_) {\
    XIterator *iterator = (XIterator *) iterator_;\
    if (iterator == XTD_NULL || iterator->container == XTD_NULL) {\
        return;\
    }\
    xhashtable_iterator_##T1##_##T2##_advance_by(iterator_, 1);\
}\
\
static XIterator *xiterator_init_xhashtable_##T1##_##T2(xhashtable_##T1##_##T2 *container) {\
    XIterator *iterator;\
    xhashtable_iterator_##T1##_##T2 *xhashtable_iterator;\
    if (container == XTD_NULL) {\
        return XTD_NULL;\
    }\
    iterator = (XIterator *) container->memory_malloc(sizeof(XIterator));\
    if (iterator == XTD_NULL) {\
        return XTD_NULL;\
    }\
    xhashtable_iterator = (xhashtable_iterator_##T1##_##T2 *) container->memory_malloc(sizeof(xhashtable_iterator_##T1##_##T2));\
    if (xhashtable_iterator == XTD_NULL) {\
        container->memory_free(iterator);\
        return XTD_NULL;\
    }\
    xhashtable_iterator->container = container;\
    iterator->forward_index = 0;\
    iterator->backward_index = container->size-1;\
    iterator->has_next = xhashtable_iterator_##T1##_##T2##_has_next;\
    iterator->next = xhashtable_iterator_##T1##_##T2##_next;\
    iterator->has_prev = xhashtable_iterator_##T1##_##T2##_has_prev;\
    iterator->prev = xhashtable_iterator_##T1##_##T2##_prev;\
    iterator->reset_forward = xhashtable_iterator_##T1##_##T2##_reset_forward;\
    iterator->reset_backward = xhashtable_iterator_##T1##_##T2##_reset_backward;\
    iterator->reset = xhashtable_iterator_##T1##_##T2##_reset;\
    iterator->destroy = xhashtable_iterator_##T1##_##T2##_destroy;\
    iterator->advance_by = xhashtable_iterator_##T1##_##T2##_advance_by;\
    iterator->increment = xhashtable_iterator_##T1##_##T2##_increment;\
    iterator->decrement = xhashtable_iterator_##T1##_##T2##_decrement;\
    iterator->container = xhashtable_iterator;\
    iterator->reset(iterator);\
    return iterator;\
}\
\
\
\

/**

*/
#define xhashtable_entry(T1, T2) xhashtable_entry_##T1##_##T2

/**

*/
#define xhashtable(T1, T2) xhashtable_##T1##_##T2

/**

*/
#define xhashtable_new(T1, T2) xhashtable_##T1##_##T2##_new

/**

*/
#define xhashtable_new_max_size(T1, T2) xhashtable_##T1##_##T2##_new_max_size

/**

*/
#define xhashtable_new_config(T1, T2) xhashtable_##T1##_##T2##_new_config

/**

*/
#define xhashtable_destroy(T1, T2) xhashtable_##T1##_##T2##_destroy

/**

*/
#define xhashtable_put(T1, T2) xhashtable_##T1##_##T2##_put

/**

*/
#define xhashtable_put_null_key(T1, T2) xhashtable_##T1##_##T2##_put_null_key

/**

*/
#define xhashtable_get(T1, T2) xhashtable_##T1##_##T2##_get

/**

*/
#define xhashtable_get_null_key(T1, T2) xhashtable_##T1##_##T2##_get_null_key

/**

*/
#define xhashtable_remove(T1, T2) xhashtable_##T1##_##T2##_remove

/**

*/
#define xhashtable_remove_null_key(T1, T2) xhashtable_##T1##_##T2##_remove_null_key

/**

*/
#define xhashtable_remove_all(T1, T2) xhashtable_##T1##_##T2##_remove_all

/**

*/
#define xhashtable_contains_key(T1, T2) xhashtable_##T1##_##T2##_contains_key

/**

*/
#define xhashtable_get_keys(T1, T2) xhashtable_##T1##_##T2##_get_keys

/**

*/
#define xhashtable_get_values(T1, T2) xhashtable_##T1##_##T2##_get_values

/**

*/
#define xhashtable_resize(T1, T2) xhashtable_##T1##_##T2##_resize

/*

*/
#define xhashtable_capacity xcapacity

/*

*/
#define xhashtable_size xsize

/*

*/
#define xhashtable_max_size xmax_size

/*

*/
#define xhashtable_is_empty xis_empty

/*

*/
#define SETUP_XHASHTABLE_FOR(T1, T2) SETUP_XHASHTABLE_ENTRY_ONLY_FOR(T1, T2) SETUP_XHASHTABLE_ONLY_FOR(T1, T2) SETUP_ITERATOR_FOR_XHASHTABLE(T1, T2)


#ifdef __cplusplus
}
#endif

#endif