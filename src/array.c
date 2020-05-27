
/**
    \copyright GNU General Public License v3.0 Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 10 April 2020
    \file array.c
*/

#include <exotic/array.h>

static enum x_stat expand_capacity(Array *arr);

/**
    
*/
enum x_stat array_new(Array **out) {
    ArrayConfig c;
    array_config_init(&c);
    return array_new_config(&c, out);
}

/**

*/
enum x_stat array_new_from(Array **out, Array *arr) {
    ArrayConfig c;
    enum x_stat status;
    enum x_stat add_status;
    array_config_init(&c);
    status = array_new_config(&c, out);
    if (status != X_OK) {
        return status;
    }
    add_status = array_add_all(*out, arr);

    return add_status;
}

/**

*/
void array_config_init(ArrayConfig* conf) {
    conf->expand_rate   = DEFAULT_ARRAY_EXPANSION_RATE;
    conf->capacity      = DEFAULT_ARRAY_CAPACITY;
    conf->memory_alloc  = malloc;
    conf->memory_calloc = calloc;
    conf->memory_free   = free;
}

/**

*/
enum x_stat array_new_config(ArrayConfig* const conf, Array **out) {
    size_t exp_rate;
    Array *arr;
    void **buffer;

    if (conf->expand_rate <= 1) {
        exp_rate = DEFAULT_ARRAY_EXPANSION_RATE;
    } else {
        exp_rate = conf->expand_rate;
    }

    if (!conf->capacity || exp_rate >= (X_ARRAY_MAX_CAPACITY / conf->capacity)) { /* see */
        return X_INVALID_CAPACITY_ERR;
    }

    arr = conf->memory_calloc(1, sizeof(Array));

    if (!arr) {
        return X_ALLOC_ERR;
    }

    buffer = conf->memory_alloc(conf->capacity * sizeof(void*));

    if (!buffer) {
        conf->memory_free(arr);
        return X_ALLOC_ERR;
    }

    arr->capacity        = conf->capacity;
    arr->expand_rate     = conf->expand_rate;
    arr->size            = 0;
    arr->memory_alloc    = conf->memory_alloc;
    arr->memory_calloc   = conf->memory_calloc;
    arr->memory_free     = conf->memory_free;
    arr->buffer          = buffer;
    *out = arr;
    
    return X_OK;
}

/**

*/
void array_destroy(Array *arr) {
    arr->memory_free(arr->buffer);
    arr->memory_free(arr);
}

/**

*/
void array_destroy_fn(Array *arr, void (*fn) (void*)) {
    size_t i;
    
    for (i = 0; i < arr->size; ++i) {
        fn(arr->buffer[i]);
    }
    array_destroy(arr);
}

/**

*/
enum x_stat array_add(Array *arr, void *item) {
    enum x_stat status;
    
    if (arr->size >= arr->capacity) {
        status = expand_capacity(arr);
        if (status != X_OK)
            return status;
    }
    arr->buffer[arr->size] = item;
    ++arr->size;
    
    return X_OK;
}

/**

*/
enum x_stat array_add_at(Array *arr, void *item, size_t index) {
    size_t num;
    enum x_stat status;
    
    if (index == arr->size) {
        return array_add(arr, item);
    }
    if ((arr->size == 0 && index != 0) || index > (arr->size - 1))
        return X_OUT_OF_RANGE_ERR;

    if (arr->size >= arr->capacity) {
        status = expand_capacity(arr);
        if (status != X_OK)
            return status;
    }
    num = (arr->size - index) * sizeof(void*);
    memmove(&(arr->buffer[index + 1]),
            &(arr->buffer[index]),
            num);

    arr->buffer[index] = item;
    ++arr->size;
    
    return X_OK;
}

/**
    If at least one failed to be added, all the other element that has 
    been added will be removed
*/
enum x_stat array_add_all(Array *arr, Array *from_arr) {
    size_t i, y, size;
    enum x_stat status;
    
    y = arr->size;
    for (i = 0; i < from_arr->size; ++i) {
        status = array_add(arr, from_arr->buffer[i]);
        if (status != X_OK) {
            size = arr->size;
            for (i = y; i < size; ++i) {
                status = array_remove_last(arr, NULL);
                if (status != X_OK) {
                    return X_FAILED_TO_CLEANUP_ERR;
                }
            } 
            return status;
        }
    }
    
    return X_OK;
}

/**
    If at least one failed to be added, all the other element that has 
    been added will be removed
*/
enum x_stat array_add_all_at(Array *arr, Array *from_arr, size_t index) {
    size_t i, y, size, new_index;
    enum x_stat status;
    
    y = arr->size;
    for (i = 0, new_index = index; i < from_arr->size; ++i, ++new_index) {
        status = array_add_at(arr, from_arr->buffer[i], new_index);
        if (status != X_OK) {
            size = arr->size;
            for (i = y; i < size; ++i) {
                status = array_remove_at(arr, index, NULL);
                if (status != X_OK) {
                    return X_FAILED_TO_CLEANUP_ERR;
                }
            }
            return status;
        }
    }
    
    return X_OK;
}

/**

*/
enum x_stat array_remove(Array *arr, void *item) {
    size_t index;
    size_t size;
    enum x_stat status;

    status = array_index_of(arr, item, &index);
    if (status == X_OUT_OF_RANGE_ERR) {
        return X_VALUE_NOT_FOUND_ERR;
    }

    return array_remove_at(arr, index, NULL);
}

/**

*/
enum x_stat array_remove_at(Array *arr, size_t index, void **out) {
    size_t size;
    
    if (index >= arr->size)
        return X_OUT_OF_RANGE_ERR;

    if (out) {
        *out = arr->buffer[index];
    }

    if (index != arr->size - 1) {
        size = (arr->size - 1 - index) * sizeof(void*);
        memmove(&(arr->buffer[index]),
                &(arr->buffer[index + 1]),
                size);
    }
    --arr->size;

    return X_OK;
}

/**

*/
enum x_stat array_remove_last(Array *arr, void **out) {
    return array_remove_at(arr, arr->size - 1, out);
}

/**

*/
void array_remove_all(Array *arr) {
    
}

/**

*/
void array_remove_if(Array *arr, bool (*predicate) (const void*)) {
    
}

/**

*/
void array_remove_range(Array *arr, size_t from_index, size_t to_index) {
    
}

/**

*/
void array_free_element_if(Array *arr, bool (*predicate) (const void*)) {
    
}

/**

*/
enum x_stat array_get_at(Array *arr, size_t index, void **out) {
    if (index >= arr->size) {
        return X_OUT_OF_RANGE_ERR;
    }

    *out = arr->buffer[index];
    return X_OK;
}

/**

*/
enum x_stat array_get_last(Array *arr, void **out) {
    if (arr->size == 0) {
        return X_VALUE_NOT_FOUND_ERR;
    }

    return array_get_at(arr, arr->size - 1, out);
}

/**

*/
void array_free_all_elements(Array *arr) {
    
}

enum x_stat array_index_of(Array *arr, void *item, size_t *index) {
    size_t i;
    
    for (i = 0; i < arr->size; ++i) {
        if (arr->buffer[i] == item) {
            *index = i;
            return X_OK;
        }
    }
    return X_OUT_OF_RANGE_ERR;
}

/**

*/
size_t array_size(Array *arr){
    return arr->size;
}

/**

*/
bool array_is_empty(Array *arr){
    return arr->size == 0;
}

/**

*/
size_t array_capacity(Array *arr){
    return arr->capacity;
}

/**

*/
static enum x_stat expand_capacity(Array *arr) {
    size_t tmp_capacity;
    void **new_buffer;
    
    if (arr->capacity == X_ARRAY_MAX_CAPACITY) {
        return X_MAX_CAPACITY_ERR;
    }
    tmp_capacity = arr->capacity * arr->expand_rate;
    if (tmp_capacity <= arr->capacity) {
        arr->capacity = X_ARRAY_MAX_CAPACITY;
    } else {
        arr->capacity = tmp_capacity;
    }
    new_buffer = arr->memory_alloc(tmp_capacity * sizeof(void*));
    if (!new_buffer) {
        return X_ALLOC_ERR;
    }

    memcpy(new_buffer, arr->buffer, arr->size * sizeof(void*));

    arr->memory_free(arr->buffer);
    arr->buffer = new_buffer;

    return X_OK;
}



