
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 07 April 2020
    \file array.h
*/


#ifndef EXOTIC_ARRAY_H
#define EXOTIC_ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "xconf.h"

#define DEFAULT_ARRAY_CAPACITY 4
#define DEFAULT_ARRAY_EXPANSION_RATE 2

/**
    The array configuration structure to initialize a new array with 
    specific fields and memory allocation funtions. 
*/
typedef struct array_config {
    size_t capacity;                                        /**<  the default capacity of the array */
    size_t expand_rate;                                     /**<  the rate at which the array buffer expands (capacity * expand_rate) */
    void *(*memory_alloc)  (size_t size);                   /**<  memory allocator used to allocate the array and it buffer. malloc */
    void *(*memory_calloc) (size_t blocks, size_t size);    /**<  memory allocator used to allocate the array and it buffer. calloc */
    void  (*memory_free)   (void *block);                   /**<  the free funtion to release the memory of the array and it buffer */
} ArrayConfig;

/**
    A dynamic array that expands automatically as new items are 
    added to it. The array supports constant time insertion 
    and removal of elements at any index of the array, as well as
    constant time access.
    
    When a new item is to be added if the size of array is greater 
    than or equal to the capacity the array capacity is expanded 
    using by multiplying the array config capacity by the array conf 
    expand_rate (conf->capacity * conf->expand_rate). 
*/
typedef struct array_struct {
    size_t capacity;                                        /**<  the default capacity of the array */
    size_t expand_rate;                                     /**<  the rate at which the array buffer expands (capacity * expand_rate) */
    size_t size;                                            /**<  the number of items in the array */
    void *(*memory_alloc)  (size_t size);                   /**<  memory allocator used to allocate the array and it buffer. malloc */
    void *(*memory_calloc) (size_t blocks, size_t size);    /**<  memory allocator used to allocate the array and it buffer. calloc */
    void  (*memory_free)   (void *block);                   /**<  the free funtion to release the memory of the array and it buffer */
    void **buffer;                                          /**<  the pointer to the items in the array */
} Array;


/**
    Array iterator structure. Use to iterate the items in the array 
    in the specified ::iterator_order. The default order #X_ITERATOR_ASC.
    
*/
typedef struct array_iterator_struct {
    Array *array;               /**<  the array associated with this iterator */
    size_t index;               /**<  the current position of the iterator */
    bool last_item_removed;     /**<  if the last item returned by the iterator is remove it return true */
    /*enum order;               /**<  the order to iterate over the items in the array */
} ArrayIterator;


enum x_stat    array_new                     (Array **out);
enum x_stat    array_new_from                (Array **out, Array *arr);
void           array_config_init             (ArrayConfig* conf);
enum x_stat    array_new_config              (ArrayConfig* const conf, Array **out);

void           array_destroy                 (Array *arr);
void           array_destroy_fn              (Array *arr, void (*fn) (void*));

enum x_stat    array_add                     (Array *arr, void *item);
enum x_stat    array_add_at                  (Array *arr, void *item, size_t index);
enum x_stat    array_add_all                 (Array *arr, Array *from_arr);
enum x_stat    array_add_all_at              (Array *arr, Array *from_arr, size_t index);

enum x_stat    array_remove                  (Array *arr, void *item);
enum x_stat    array_remove_at               (Array *arr, size_t index, void **out);
enum x_stat    array_remove_last             (Array *arr, void **out);
enum x_stat    array_remove_all              (Array *arr);
void           array_remove_if               (Array *arr, bool (*predicate) (const void*));
enum x_stat    array_remove_range            (Array *arr, size_t from_index, size_t to_index);
void           array_free_element_if         (Array *arr, bool (*predicate) (const void*));
void           array_free_all_elements       (Array *arr);

enum x_stat    array_get_at                  (Array *arr, size_t index, void **out);
enum x_stat    array_get_last                (Array *arr, void **out);

enum x_stat    array_slice                   (Array *arr, size_t from_index, size_t to_index, Array **out);
enum x_stat    array_shallow_copy            (Array *arr, Array **out);
enum x_stat    array_shallow_copy_in_range   (Array *arr, size_t from_index, size_t to_index, Array **out);
enum x_stat    array_deep_copy               (Array *arr, void *(*cpy) (void*), Array **out);
enum x_stat    array_deep_copy_in_range      (Array *arr, size_t from_index, size_t to_index, void *(*cpy) (void*), Array **out);

enum x_stat    array_trim_to_size            (Array *arr);
void           array_reverse                 (Array *arr);
void           array_reverse_in_range        (Array *arr, size_t from_index, size_t to_index);
bool           array_contains                (Array *arr, void *item);
size_t         array_element_count           (Array *arr, void *item);
void           array_sort                    (Array *arr, int (*cmp) (const void*, const void*));

enum x_stat    array_index_of                (Array *arr, void *item, size_t *index);
enum x_stat    array_index_of_from           (Array *arr, void *item, size_t *index, size_t from_index);
enum x_stat    array_index_of_in_range       (Array *arr, void *item, size_t *index, size_t from_index, size_t to_index);
enum x_stat    array_last_index_of           (Array *arr, void *item, size_t *index);
enum x_stat    array_last_index_of_from      (Array *arr, void *item, size_t *index, size_t from_index);
enum x_stat    array_last_index_of_in_range  (Array *arr, void *item, size_t *index, size_t from_index, size_t to_index);

size_t         array_size                    (Array *arr);
bool           array_is_empty                (Array *arr);
size_t         array_capacity                (Array *arr);

void           array_map                     (Array *arr, void (*fn) (void*));
enum x_stat    array_filter                  (Array *arr, bool (*predicate) (const void*));
enum x_stat    array_filter_out              (Array *arr, bool (*predicate) (const void*), Array **out);
char*          array_to_string               (Array *arr);

#ifdef __cplusplus
}
#endif


#endif