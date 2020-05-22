
/**
    \copyright GNU General Public License v3.0 Copyright (c) 2019, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 07 April 2020
    \file array.h
*/


#ifndef EXOTICPEN_ARRAY_H
#define EXOTICPEN_ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <exotic/xconf.h>

#define DEFAULT_ARRAY_CAPACITY 4
#define DEFAULT_ARRAY_EXPANSION_RATE 2

/**
    The array configuration structure to initialize a new array with 
    specific fields and memory allocation funtions. 
*/
typedef struct xxarray_config {
    size_t capacity;                                        /**<  the default capacity of the array */
    size_t expand_rate;                                     /**<  the rate at which the array buffer expands (capacity * expand_rate) */
    void *(*memory_alloc)  (size_t size);                   /**<  memory allocator used to allocate the array and it buffer. malloc */
    void *(*memory_calloc) (size_t blocks, size_t size);    /**<  memory allocator used to allocate the array and it buffer. calloc */
    void  (*memory_free)   (void *block);                   /**<  the free funtion to release the memory of the array and it buffer */
} XArrayConfig;

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
typedef struct xarray_struct {
    size_t size;             /**<  the number of items in the array */
    void **buffer;           /**<  the pointer to the items in the array */
    XArrayConfig* conf;       /**<  the XArrayConfig struct used to manage the array  */
} XArray;


/**
    XArray iterator structure. Use to iterate the items in the array 
    in the specified ::iterator_order. The default order #X_ITERATOR_ASC.
    
*/
typedef struct xarray_iterator_struct {
    XArray* array;            /**<  the array associated with this iterator */
    size_t index;            /**<  the current position of the iterator */
    bool last_item_removed;  /**<  if the last item returned by the iterator is remove it return true */
    /*enum order;              /**<  the order to iterate over the items in the array */
} XArrayIterator;


enum xtypes_stat    xarray_new            (XArray **out);
enum xtypes_stat    xarray_new_config     (XArrayConfig const * const conf, XArray **out);
void                 xarray_config_init    (XArrayConfig *conf);

void                 xarray_destroy        (XArray *ar);
void                 xarray_destroy_cb     (XArray *ar, void (*cb) (void*));

#ifdef __cplusplus
}
#endif


#endif