
/**
    \copyright GNU General Public License v3.0 Copyright (c) 2019, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 07 April 2020
    \file array.h
*/


#ifndef LIBOPEN_ARRAY_H
#define LIBOPEN_ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#define DEFAULT_ARRAY_CAPACITY 4
#define DEFAULT_ARRAY_EXPANSION_RATE 2

/**
    The array configuration structure to initialize a new array with 
    specific fields and memory allocation funtions. 
*/
typedef struct array_config {
    size_t capacity;                                        ///< the default capacity of the array
    size_t expand_rate;                                     ///< the rate at which the array buffer expands (capacity * expand_rate)
    void *(*memory_alloc)  (size_t size);                   ///< memory allocator used to allocate the array and it buffer. malloc
    void *(*memory_calloc) (size_t blocks, size_t size);    ///< memory allocator used to allocate the array and it buffer. calloc
    void  (*memory_free)   (void *block);                   ///< the free funtion to release the memory of the array and it buffer
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
    size_t size;             ///< the number of items in the array
    void **buffer;           ///< the pointer to the items in the array
    ArrayConfig* conf;       ///< the ArrayConfig struct used to manage the array 
} Array;


/**
    Array iterator structure. Use to iterate the items in the array 
    in the specified ::iterator_order. The default order #L_ITERATOR_ASC.
    
*/
typedef struct array_iterator_struct {
    Array* array;            ///< the array associated with this iterator
    size_t index;            ///< the current position of the iterator
    bool last_item_removed;  ///< if the last item returned by the iterator is remove it return true
    enum order;              ///< the order to iterate over the items in the array
} ArrayIterator;


enum libopen_stat    array_new            (Array **out);
enum libopen_stat    array_new_config     (ArrayConfig const * const conf, Array **out);
void                 array_config_init    (ArrayConfig *conf);

void                 array_destroy        (Array *ar);
void                 array_destroy_cb     (Array *ar, void (*cb) (void*));

#ifdef __cplusplus
}
#endif


#endif