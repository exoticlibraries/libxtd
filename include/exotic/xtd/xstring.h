
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 05 June 2021
    \file xstring.h
*/

#ifndef EXOTIC_XSTRING_H
#define EXOTIC_XSTRING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "xcommon.h"
#include "xvector.h"

#ifdef __cplusplus
#if !defined(ALLOW_XTD_TYPES_WITH_ALTERNATIVES_IN_CPP) && __cplusplus >= 201103L
    #warning Do not use this type in C++ 03 and above, use the std::string class instead
#endif
#endif


/*

*/
static size_t xstring_str_length_1(char char_array[]) {
    size_t length = 0;
    if (char_array == NULL) { return length; }
    while(char_array[length] != '\0') {
        length++;
    }
    return length;
}

/*

*/
#define xstring_str_length xstring_str_length_1

/*

*/
static size_t xstring_str_length_2(char char_array[]) {
    size_t length = 0;
    if (char_array == NULL) { return length; }
    for(; char_array[length] != '\0'; length++);
    return length;
}

/*

*/
static size_t xstring_str_length_3_internal__(char char_array[], size_t length) {
    if (char_array == NULL) { return length; }
    if (char_array[length] == '\0') {
        return length;
    }
    return xstring_str_length_3_internal__(char_array, ++length);
}

/*

*/
static bool xstring_str_length_3(char char_array[]) {
    return xstring_str_length_3_internal__(char_array, 0);
}

/*

*/
static bool xstring_str_equals_1(char *char_array1, char *char_array2) {
    size_t index = 0;
    if (char_array1 == XTD_NULL || char_array2 == XTD_NULL) {
        return char_array1 == char_array2;
    }
    while (TRUE) {
        if (char_array1[index] == '\0' && char_array2[index] == '\0') {
            break;
        }
        if (char_array1[index] != char_array2[index]) {
            return 0;
        }
        ++index;
    }
    return TRUE;
}

/*

*/
#define xstring_str_equals xstring_str_equals_1

/*

*/
static bool xstring_str_equals_2(char *char_array1, char *char_array2) {
    return char_array1 == char_array2;
}

/*

*/
static bool xstring_str_equals_3(char *char_array1, char *char_array2) {
    if (char_array1 == XTD_NULL || char_array2 == XTD_NULL) {
        return char_array1 == char_array2;
    }
    for(size_t index = 0; char_array1[index] != '\0' || char_array2[index] != '\0'; index++) {
        if(char_array1[index] != char_array2[index]) {
            return FALSE;
        }
    }
    return TRUE;
}

/*

*/
static bool xstring_str_equals_4(char *char_array1, char *char_array2) {
    if (char_array1 == XTD_NULL || char_array2 == XTD_NULL) {
        return char_array1 == char_array2;
    }
    while((*char_array1 && *char_array2)) {
        if (*char_array1 != *char_array2) {
            return FALSE;
        }
        char_array1++; char_array2++; 
    }
    return (!*char_array1 && !*char_array2);
}

/*

*/
static bool xstring_str_equals_ignore_case_1(char *char_array1, char *char_array2) {
    if (char_array1 == XTD_NULL || char_array2 == XTD_NULL) {
        return char_array1 == char_array2;
    }
    while((*char_array1 && *char_array2)) {
        if (((*char_array1 >= 65) && (*char_array1 <= 90) ? *char_array1 + 32 : *char_array1) != 
            ((*char_array2 >= 65) && (*char_array2 <= 90) ? *char_array2 + 32 : *char_array2)) {
            return FALSE;
        }
        char_array1++; char_array2++; 
    }
    return (!*char_array1 && !*char_array2);
}

/*

*/
#define xstring_str_equals_ignore_case xstring_str_equals_ignore_case_1

/*
    Compares two strings lexicographically.
*/
static size_t xstring_str_compare_1(char *char_array1, char *char_array2) {
    size_t index = 0;
    if (char_array1 == XTD_NULL || char_array2 == XTD_NULL) {
        return char_array1 == char_array2;
    }
    while(char_array1[index] == char_array2[index]) {
        if(char_array1[index] == '\0' && char_array2[index] == '\0') {
            break;
        }
        index++;
    }
    return char_array1[index] - char_array2[index];
}

/*
    
*/
#define xstring_str_compare xstring_str_compare_1

/*
    Compares two strings lexicographically. using pointer
*/
static size_t xstring_str_compare_2(char *char_array1, char *char_array2) {
    if (char_array1 == XTD_NULL || char_array2 == XTD_NULL) {
        return char_array1 == char_array2;
    }
    while((*char_array1 && *char_array2) && (*char_array1 == *char_array2)) {
        char_array1++; char_array2++;
    }
    return *char_array1 - *char_array2;
}

/*
    
*/
static size_t xstring_str_compare_ignore_case_1(char *char_array1, char *char_array2) {
    char char1;
    char char2;
    if (char_array1 == XTD_NULL || char_array2 == XTD_NULL) {
        return char_array1 == char_array2;
    }
    while((*char_array1 && *char_array2) && 
            (((*char_array1 >= 65) && (*char_array1 <= 90) ? *char_array1 + 32 : *char_array1) == 
            ((*char_array2 >= 65) && (*char_array2 <= 90) ? *char_array2 + 32 : *char_array2))) {
        char_array1++; char_array2++;
    }
    char1 = ((*char_array1 >= 65) && (*char_array1 <= 90) ? *char_array1 + 32 : *char_array1);
    char2 = ((*char_array2 >= 65) && (*char_array2 <= 90) ? *char_array2 + 32 : *char_array2);
    return char1 - char2;
}

/*

*/
#define xstring_str_compare_ignore_case xstring_str_compare_ignore_case_1

/*

*/
static bool xstring_str_is_empty_1(char char_array[]) {
    return xstring_str_length(char_array) == 0;
}

/*
    
*/
#define xstring_str_is_empty xstring_str_is_empty_1

/*
    Does not check if char_array is NULL
*/
static int xstring_str_index_of_from_pos_with_length_1(size_t char_array_length, char *char_array, char *str_to_check, size_t from) {
    size_t primary_index;
    size_t secondary_index;
    size_t str_to_check_length = xstring_str_length(str_to_check);
    if ((char_array_length <= 0 || str_to_check_length <= 0) || (str_to_check_length > (char_array_length - from))) {
        return -1;
    }
    if (from < 0) { from = 0; }
    /*if (char_array_length == str_to_check_length) {
        return (xstring_str_equals(char_array, str_to_check) ? 0 : -1);
    }*/
    for (; from < char_array_length; ++from) {
        if (char_array[from] == str_to_check[0]) {
            if (str_to_check_length == 1) { return from; }
            {
                primary_index = from;
                secondary_index = 0;
                while (char_array[primary_index] != '\0' && char_array[++primary_index] == str_to_check[++secondary_index]);
                if (str_to_check_length == secondary_index) { return from; }
            }
        }
    }
    return -1;
}

/*
    
*/
#define xstring_str_index_of_from_pos_with_length xstring_str_index_of_from_pos_with_length_1

/*
    
*/
static int xstring_str_index_of_from_pos_1(char *char_array, char *str_to_check, size_t from) {
    return xstring_str_index_of_from_pos_with_length_1(xstring_str_length(char_array), char_array, str_to_check, from);
}

/*
    
*/
#define xstring_str_index_of_from_pos xstring_str_index_of_from_pos_1

/*
    
*/
static int xstring_str_index_of_1(char *char_array, char *str_to_check) {
    return xstring_str_index_of_from_pos_with_length_1(xstring_str_length(char_array), char_array, str_to_check, 0);
}

/*
    
*/
#define xstring_str_index_of xstring_str_index_of_1

/*
    Does not check if char_array is NULL, pos is from the backend
*/
static int xstring_str_last_index_of_from_pos_with_length_1(size_t char_array_length, char *char_array, char *str_to_check, size_t from) {
    int right_most;
    size_t primary_index;
    size_t secondary_index;
    size_t str_to_check_length = xstring_str_length(str_to_check);
    if ((char_array_length <= 0 || str_to_check_length <= 0) || (str_to_check_length > (char_array_length - from))) {
        return -1;
    }
    if (from < 0) { from = 0; }
    /*if (char_array_length == str_to_check_length) {
        return (xstring_str_equals(char_array, str_to_check) ? 0 : -1);
    }*/
    right_most = (char_array_length-1) - from;
    for (; right_most > -1 ; --right_most) {
        if (char_array[right_most] == str_to_check[0]) {
            if (str_to_check_length == 1) { return right_most; }
            primary_index = right_most;
            secondary_index = 0;
            while (char_array[primary_index] != '\0' && char_array[++primary_index] == str_to_check[++secondary_index]);
            if (str_to_check_length == secondary_index) { return right_most; }
        }
    }
    return -1;
}

/*

*/
#define xstring_str_last_index_of_from_pos_with_length xstring_str_last_index_of_from_pos_with_length_1

/*
    
*/
static int xstring_str_last_index_of_from_pos_1(char *char_array, char *str_to_check, size_t from) {
    return xstring_str_last_index_of_from_pos_with_length_1(xstring_str_length(char_array), char_array, str_to_check, from);
}

/*
    
*/
#define xstring_str_last_index_of_from_pos xstring_str_last_index_of_from_pos_1

/*
    
*/
static int xstring_str_last_index_of_1(char *char_array, char *str_to_check) {
    return xstring_str_last_index_of_from_pos_with_length_1(xstring_str_length(char_array), char_array, str_to_check, 0);
}

/*
    
*/
#define xstring_str_last_index_of xstring_str_last_index_of_1

/*
    
*/
static bool xstring_str_contains_1(char *char_array, char *str_to_check) {
    return xstring_str_index_of(char_array, str_to_check) > -1;
}

/*
    
*/
#define xstring_str_contains xstring_str_contains_1

/*
    
*/
static bool xstring_str_ends_with_1(char *char_array, char *str_to_check) {
    size_t char_array_length = xstring_str_length(char_array);
    size_t str_to_check_length = xstring_str_length(str_to_check);
    return xstring_str_index_of_from_pos_1(char_array, str_to_check, (char_array_length - str_to_check_length)) > -1;
}

/*
    
*/
#define xstring_str_ends_with xstring_str_ends_with_1

/*
    
*/
static bool xstring_str_starts_with_1(char *char_array, char *str_to_check) {
    size_t char_array_length = xstring_str_length(char_array);
    size_t str_to_check_length = xstring_str_length(str_to_check);
    if (str_to_check_length > char_array_length) {
        return FALSE;
    }
    return xstring_str_index_of_from_pos_with_length_1(str_to_check_length, char_array, str_to_check, 0) == 0;
}

/*
    
*/
#define xstring_str_starts_with xstring_str_starts_with_1

/*
    
*/
static enum x_stat xstring_str_sub_string_in_range_with_length_1(size_t char_array_length, char *char_array, size_t begin_index, size_t end_index, char *out) {
    size_t str_index = 0;
    if (begin_index < 0 || begin_index > char_array_length || end_index > char_array_length) {
        return XTD_OUT_OF_RANGE_ERR;
    }
    if (out == XTD_NULL) {
        return XTD_PARAM_NULL_ERR;
    }
    for (; begin_index < end_index; ++begin_index) {
        out[str_index++] = char_array[begin_index];
    }
    out[str_index] = '\0';
    return XTD_OK;
}

/*
    
*/
#define xstring_str_sub_string_in_range_with_length xstring_str_sub_string_in_range_with_length_1

/*
    
*/
static enum x_stat xstring_str_sub_string_in_range_1(char *char_array, size_t begin_index, size_t end_index, char *out) {
    return xstring_str_sub_string_in_range_with_length_1(xstring_str_length(char_array), char_array, begin_index, end_index, out);
}

/*
    
*/
#define xstring_str_sub_string_in_range xstring_str_sub_string_in_range_1

/*
    
*/
static enum x_stat xstring_str_sub_string_1(char *char_array, size_t begin_index, char *out) {
    size_t char_array_length = xstring_str_length(char_array);
    return xstring_str_sub_string_in_range_with_length_1(char_array_length, char_array, begin_index, char_array_length, out);
}

/*
    
*/
#define xstring_str_sub_string xstring_str_sub_string_1

/*
    
*/
#define xstring_str_char_at(char_array, index) char_array[index]

/*
    
*/
static char **xstring_str_split_with_length_1(size_t char_array_length, char *char_array, char *seperator, XAllocator allocator) {
    char **out;
    char *value;
    char **tmp_out;
    size_t str_index;
    size_t tmp_out_index;
    size_t str_index_cache;
    size_t secondary_index;
    size_t seperator_length;
    size_t found_words_counts;
    size_t last_seperator_position;
    found_words_counts = 0;
    if (char_array == XTD_NULL || seperator == XTD_NULL) {
        goto xstring_str_split_with_length_1_release_and_return_null;
    }
    out = XTD_NULL;
    last_seperator_position = 0;
    seperator_length = xstring_str_length(seperator);
    for (str_index = 0; str_index < char_array_length; ++str_index, str_index_cache = str_index) {
        if (char_array[str_index] == seperator[0]) {
            secondary_index = 0;
            while (char_array[str_index] != '\0' && char_array[++str_index] == seperator[++secondary_index]);
            if (seperator_length == secondary_index) {
                value = (char *) allocator.memory_malloc((str_index_cache - last_seperator_position) * sizeof(char));
                if (xstring_str_sub_string_in_range_1(char_array, last_seperator_position, str_index_cache, value) != XTD_OK) {
                    allocator.memory_free(value);
                    goto xstring_str_split_with_length_1_release_and_return_null;
                }
                found_words_counts++;
                tmp_out = (char **) allocator.memory_realloc(out, found_words_counts * sizeof(char *));
                if (!tmp_out) {
                    goto xstring_str_split_with_length_1_release_and_return_null;
                }
                out = tmp_out;
                out[found_words_counts-1] = value;
            } else {
                str_index = str_index_cache;
            }
            last_seperator_position = str_index;
        }
    }
    if ((str_index_cache - last_seperator_position) > 1) {
        value = (char *) allocator.memory_malloc((str_index_cache - last_seperator_position) * sizeof(char));
        if (xstring_str_sub_string_in_range_1(char_array, last_seperator_position, str_index_cache, value) != XTD_OK) {
            allocator.memory_free(value);
            goto xstring_str_split_with_length_1_release_and_return_null;
        }
        found_words_counts++;
        tmp_out = (char **) allocator.memory_realloc(out, found_words_counts * sizeof(char *));
        if (!tmp_out) {
            goto xstring_str_split_with_length_1_release_and_return_null;
        }
        out = tmp_out;
        out[found_words_counts-1] = value;
    }
    out[found_words_counts] = XTD_NULL;
    return out;
    xstring_str_split_with_length_1_release_and_return_null:
        if (found_words_counts > 0) {
            for (secondary_index = 0; secondary_index < found_words_counts-1; secondary_index++) {
                allocator.memory_free(out[secondary_index]);
            }
            allocator.memory_free(out);
        }
        return XTD_NULL;
}

/*
    
*/
#define xstring_str_split_with_length xstring_str_split_with_length_1

/*
    
*/
static char **xstring_str_split_1(char *char_array, char *seperator, XAllocator allocator) {
    return xstring_str_split_with_length_1(xstring_str_length(char_array), char_array, seperator, allocator);
}

/*
    
*/
#define xstring_str_split xstring_str_split_1

/* TODO */
#define xstring_str_char_value
#define xstring_str_int_value
#define xstring_str_long_value
#define xstring_str_double_value
#define xstring_str_float_value
#define xstring_str_pointer_value
#define xstring_str_concat_str
#define xstring_str_concat_char
#define xstring_str_concat_int
#define xstring_str_concat_long
#define xstring_str_concat_double
#define xstring_str_concat_float
#define xstring_str_concat_pointer
#define xstring_str_format
#define xstring_str_hashcode
#define xstring_str_replace
#define xstring_str_replace_first
#define xstring_str_replace_last
#define xstring_str_to_lower_case
#define xstring_str_to_upper_case
#define xstring_str_trim

/*

*/
typedef char xchar_internal__;
SETUP_XVECTOR_FOR(xchar_internal__)

/*

*/
#define xstring xvector_xchar_internal__

/*

*/
static const xstring *xstring_new(char *char_array) {
    size_t index;
    xstring *xstring_internal__;
    if (xvector_new(xchar_internal__)(&xstring_internal__) != XTD_OK) {
        return XTD_NULL;
    }
    for(index = 0; char_array[index] != '\0'; index++) {
        xvector_add(xchar_internal__)(xstring_internal__, char_array[index]);
    }
    xvector_add(xchar_internal__)(xstring_internal__, '\0');
    return xstring_internal__;
}

/*

*/
static void xstring_destroy(const xstring *container) {
    if (container != XTD_NULL) {
        xvector_destroy(container);
    }
}

/*

*/
#define xstring_get_cstr(container) container->buffer


#ifdef __cplusplus
}
#endif

#endif