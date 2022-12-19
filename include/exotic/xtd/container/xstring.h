
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

#include <exotic/xtd/xcommon.h>
#include "xvector.h"

#ifdef __cplusplus
#if !defined(ALLOW_XTD_TYPES_WITH_ALTERNATIVES_IN_CPP) && __cplusplus >= 201103L
    #warning Do not use this type in C++ 03 and above, use the std::string class instead
#endif
#endif


/*

*/
static size_t xstring_cstr_length_1(char char_array[]) {
    size_t length = 0;
    if (char_array == NULL) { return length; }
    while(char_array[length] != '\0') {
        length++;
    }
    return length;
}

/*

*/
#define xstring_cstr_length xstring_cstr_length_1

/*

*/
static size_t xstring_cstr_length_2(char char_array[]) {
    size_t length = 0;
    if (char_array == NULL) { return length; }
    for (; char_array[length] != '\0'; length++);
    return length;
}

/*

*/
static size_t xstring_cstr_length_3_internal__(char char_array[], size_t length) {
    if (char_array == NULL) { return length; }
    if (char_array[length] == '\0') {
        return length;
    }
    return xstring_cstr_length_3_internal__(char_array, ++length);
}

/*

*/
static bool xstring_cstr_length_3(char char_array[]) {
    return xstring_cstr_length_3_internal__(char_array, 0);
}

/*

*/
static bool xstring_cstr_equals_1(const char *char_array1, const char *char_array2) {
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
#define xstring_cstr_equals xstring_cstr_equals_1

/*

*/
static bool xstring_cstr_equals_2(char *char_array1, char *char_array2) {
    return char_array1 == char_array2;
}

/*

*/
static bool xstring_cstr_equals_3(char *char_array1, char *char_array2) {
    size_t index;
    if (char_array1 == XTD_NULL || char_array2 == XTD_NULL) {
        return char_array1 == char_array2;
    }
    for(index = 0; char_array1[index] != '\0' || char_array2[index] != '\0'; index++) {
        if(char_array1[index] != char_array2[index]) {
            return FALSE;
        }
    }
    return TRUE;
}

/*

*/
static bool xstring_cstr_equals_4(char *char_array1, char *char_array2) {
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
static bool xstring_cstr_equals_ignore_case_1(char *char_array1, char *char_array2) {
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
#define xstring_cstr_equals_ignore_case xstring_cstr_equals_ignore_case_1

/*
    Compares two strings lexicographically.
*/
static size_t xstring_cstr_compare_1(char *char_array1, char *char_array2) {
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
#define xstring_cstr_compare xstring_cstr_compare_1

/*
    Compares two strings lexicographically. using pointer
*/
static size_t xstring_cstr_compare_2(char *char_array1, char *char_array2) {
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
static size_t xstring_cstr_compare_ignore_case_1(char *char_array1, char *char_array2) {
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
#define xstring_cstr_compare_ignore_case xstring_cstr_compare_ignore_case_1

/*

*/
static bool xstring_cstr_is_empty_1(char char_array[]) {
    return xstring_cstr_length(char_array) == 0;
}

/*
    
*/
#define xstring_cstr_is_empty xstring_cstr_is_empty_1

/*
    Does not check if char_array is NULL
*/
static int xstring_cstr_index_of_from_pos_with_length_1(size_t char_array_length, char *char_array, char *str_to_check, size_t from) {
    size_t primary_index;
    size_t secondary_index;
    size_t str_to_check_length = xstring_cstr_length(str_to_check);
    if ((char_array_length <= 0 || str_to_check_length <= 0) || (str_to_check_length > (char_array_length - from))) {
        return -1;
    }
    if (from < 0) { from = 0; }
    /*if (char_array_length == str_to_check_length) {
        return (xstring_cstr_equals(char_array, str_to_check) ? 0 : -1);
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
#define xstring_cstr_index_of_from_pos_with_length xstring_cstr_index_of_from_pos_with_length_1

/*
    
*/
static int xstring_cstr_index_of_from_pos_1(char *char_array, char *str_to_check, size_t from) {
    return xstring_cstr_index_of_from_pos_with_length_1(xstring_cstr_length(char_array), char_array, str_to_check, from);
}

/*
    
*/
#define xstring_cstr_index_of_from_pos xstring_cstr_index_of_from_pos_1

/*
    
*/
static int xstring_cstr_index_of_1(char *char_array, char *str_to_check) {
    return xstring_cstr_index_of_from_pos_with_length_1(xstring_cstr_length(char_array), char_array, str_to_check, 0);
}

/*
    
*/
#define xstring_cstr_index_of xstring_cstr_index_of_1

/*
    Does not check if char_array is NULL, pos is from the backend
*/
static int xstring_cstr_last_index_of_from_pos_with_length_1(size_t char_array_length, char *char_array, char *str_to_check, size_t from) {
    int right_most;
    size_t primary_index;
    size_t secondary_index;
    size_t str_to_check_length = xstring_cstr_length(str_to_check);
    if ((char_array_length <= 0 || str_to_check_length <= 0) || (str_to_check_length > (char_array_length - from))) {
        return -1;
    }
    if (from < 0) { from = 0; }
    /*if (char_array_length == str_to_check_length) {
        return (xstring_cstr_equals(char_array, str_to_check) ? 0 : -1);
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
#define xstring_cstr_last_index_of_from_pos_with_length xstring_cstr_last_index_of_from_pos_with_length_1

/*
    
*/
static int xstring_cstr_last_index_of_from_pos_1(char *char_array, char *str_to_check, size_t from) {
    return xstring_cstr_last_index_of_from_pos_with_length_1(xstring_cstr_length(char_array), char_array, str_to_check, from);
}

/*
    
*/
#define xstring_cstr_last_index_of_from_pos xstring_cstr_last_index_of_from_pos_1

/*
    
*/
static int xstring_cstr_last_index_of_1(char *char_array, char *str_to_check) {
    return xstring_cstr_last_index_of_from_pos_with_length_1(xstring_cstr_length(char_array), char_array, str_to_check, 0);
}

/*
    
*/
#define xstring_cstr_last_index_of xstring_cstr_last_index_of_1

/*
    
*/
static bool xstring_cstr_contains_1(char *char_array, char *str_to_check) {
    return xstring_cstr_index_of(char_array, str_to_check) > -1;
}

/*
    
*/
#define xstring_cstr_contains xstring_cstr_contains_1

/*
    
*/
static bool xstring_cstr_ends_with_1(char *char_array, char *str_to_check) {
    size_t char_array_length = xstring_cstr_length(char_array);
    size_t str_to_check_length = xstring_cstr_length(str_to_check);
    return xstring_cstr_index_of_from_pos_1(char_array, str_to_check, (char_array_length - str_to_check_length)) > -1;
}

/*
    
*/
#define xstring_cstr_ends_with xstring_cstr_ends_with_1

/*
    
*/
static bool xstring_cstr_starts_with_1(char *char_array, char *str_to_check) {
    size_t char_array_length = xstring_cstr_length(char_array);
    size_t str_to_check_length = xstring_cstr_length(str_to_check);
    if (str_to_check_length > char_array_length) {
        return FALSE;
    }
    return xstring_cstr_index_of_from_pos_with_length_1(str_to_check_length, char_array, str_to_check, 0) == 0;
}

/*
    
*/
#define xstring_cstr_starts_with xstring_cstr_starts_with_1

/*
    
*/
static enum x_stat xstring_cstr_sub_string_in_range_with_length_1(size_t char_array_length, char *char_array, size_t begin_index, size_t end_index, char *out) {
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
#define xstring_cstr_sub_string_in_range_with_length xstring_cstr_sub_string_in_range_with_length_1

/*
    
*/
static enum x_stat xstring_cstr_sub_string_in_range_1(char *char_array, size_t begin_index, size_t end_index, char *out) {
    return xstring_cstr_sub_string_in_range_with_length_1(xstring_cstr_length(char_array), char_array, begin_index, end_index, out);
}

/*
    
*/
#define xstring_cstr_sub_string_in_range xstring_cstr_sub_string_in_range_1

/*
    
*/
static enum x_stat xstring_cstr_sub_string_1(char *char_array, size_t begin_index, char *out) {
    size_t char_array_length = xstring_cstr_length(char_array);
    return xstring_cstr_sub_string_in_range_with_length_1(char_array_length, char_array, begin_index, char_array_length, out);
}

/*
    
*/
#define xstring_cstr_sub_string xstring_cstr_sub_string_1

/*
    
*/
#define xstring_cstr_char_at(char_array, index) char_array[index]

/*
    
*/
/* valgrind the shit out of this function, I suspect lot of mem leaks */
static char **xstring_cstr_split_with_length_1_(XAllocator allocator, size_t char_array_length, char *char_array, char *seperator) {
    char **out;
    char *value;
    char **tmp_out;
    size_t str_index;
    size_t tmp_out_index;
    size_t str_index_cache;
    size_t secondary_index;
    size_t seperator_length;
    size_t found_words_counts;
    size_t allocated_value_size;
    size_t last_seperator_position;
    found_words_counts = 0;
    if (char_array == XTD_NULL || seperator == XTD_NULL) {
        goto xstring_cstr_split_with_length_1_release_and_return_null;
    }
    out = XTD_NULL;
    str_index = 0;
    tmp_out_index = 0;
    str_index_cache = 0;
    secondary_index = 0;
    seperator_length = xstring_cstr_length(seperator);
    found_words_counts = 0;
    allocated_value_size = 0;
    last_seperator_position = 0;
    for (; str_index < char_array_length; ++str_index, allocated_value_size++, str_index_cache = str_index) {
        if (char_array[str_index] == seperator[0]) {
            secondary_index = 0;
            while (char_array[str_index] != '\0' && char_array[++str_index] == seperator[++secondary_index]);
            if (seperator_length == secondary_index) {
                value = (char *) allocator.memory_malloc(allocated_value_size+2 * sizeof(char));
                if (allocated_value_size == 1) {
                    value[0] = '\0';
                } else {
                    if (xstring_cstr_sub_string_in_range_1(char_array, last_seperator_position, str_index_cache, value) != XTD_OK) {
                        allocator.memory_free(value);
                        goto xstring_cstr_split_with_length_1_release_and_return_null;
                    }
                }
                found_words_counts++;
                tmp_out = (char **) allocator.memory_realloc(out, found_words_counts * sizeof(char *));
                if (!tmp_out) {
                    goto xstring_cstr_split_with_length_1_release_and_return_null;
                }
                out = tmp_out;
                out[found_words_counts-1] = value;
            }
            str_index--;
            allocated_value_size = 0;
            last_seperator_position = str_index + (seperator_length == 1 ? 1 : 0);
        }
    }
    if (str_index_cache > 0) {
        value = (char *) allocator.memory_malloc(allocated_value_size+2 * sizeof(char));
        if (allocated_value_size == 1) {
            value[0] = '\0';
        } else {
            if (xstring_cstr_sub_string_in_range_1(char_array, (last_seperator_position-(seperator_length == 1 && found_words_counts-1 == 0 ? 1 : 0)), str_index_cache, value) != XTD_OK) {
                allocator.memory_free(value);
                goto xstring_cstr_split_with_length_1_release_and_return_null;
            }
        }
        found_words_counts++;
        tmp_out = (char **) allocator.memory_realloc(out, found_words_counts * sizeof(char *));
        if (!tmp_out) {
            goto xstring_cstr_split_with_length_1_release_and_return_null;
        }
        out = tmp_out;
        out[found_words_counts-1] = value;
    }
    out[found_words_counts] = XTD_NULL;
    return out;
    xstring_cstr_split_with_length_1_release_and_return_null:
        if (found_words_counts > 0) {
            for (secondary_index = 0; secondary_index < found_words_counts-1; secondary_index++) {
                allocator.memory_free(out[secondary_index]);
            }
            allocator.memory_free(out);
        }
        return XTD_NULL;
}
static size_t xstring_cstr_split_with_length_1(XAllocator allocator, size_t char_array_length, char *char_array, char *seperator, char ***out) {
    char *value;
	bool is_eos;
    char **tmp_out;
    size_t str_index;
    size_t str_index_cache;
    size_t secondary_index;
    size_t seperator_length;
    size_t allocated_value_size;
    size_t last_seperator_position;
    size_t found_words_counts = 0;

	if (char_array == XTD_NULL || seperator == XTD_NULL || out == XTD_NULL) {
        goto xstring_cstr_split_with_length_1_release_and_return_null;
    }
    (*out) = XTD_NULL;
    str_index = 0;
	is_eos = FALSE;
    str_index_cache = 0;
    found_words_counts = 0;
	allocated_value_size = 0;
    last_seperator_position = 0;
    seperator_length = xstring_cstr_length(seperator);
	if (char_array_length == seperator_length && xstring_cstr_equals(char_array, seperator)) return 0;
	for (; str_index <= char_array_length; str_index++, str_index_cache = str_index, is_eos = (str_index == char_array_length)) {
		if (char_array[str_index] == seperator[0] || seperator_length == 0 || is_eos) {
			secondary_index = 0;
			if (seperator_length != 0) while (char_array[str_index] != '\0' && char_array[++str_index] == seperator[++secondary_index]);
			if (seperator_length == secondary_index || is_eos) {
				if (seperator_length == 0) str_index_cache++;
				if (!is_eos && str_index == char_array_length-1 && seperator_length == 0) {
					is_eos = TRUE;
				}
				if (is_eos || seperator_length == 0) {
					allocated_value_size++;
				}
				/*printf("is_eos=%d,%d,%d ---", is_eos, str_index, char_array_length);
				printf("%c-%d-%d-%d-%d-%d\n", char_array[str_index_cache], str_index_cache, str_index, secondary_index, allocated_value_size, last_seperator_position);*/
				value = (char *) allocator.memory_malloc(allocated_value_size+1 * sizeof(char));
                if (allocated_value_size == 0) {
                    value[0] = '\0';
                } else {
                    if (xstring_cstr_sub_string_in_range_1(char_array, last_seperator_position, str_index_cache, value) != XTD_OK) {
                        allocator.memory_free(value);
                        goto xstring_cstr_split_with_length_1_release_and_return_null;
                    }
                }
				found_words_counts++;
                tmp_out = (char **) allocator.memory_realloc((*out), found_words_counts * sizeof(char *));
                (*out) = tmp_out;
                if (!out) {
                    goto xstring_cstr_split_with_length_1_release_and_return_null;
                }
                (*out)[found_words_counts-1] = value;
				/*printf("AT::%d::%s::\n", found_words_counts, value);*/
				if (seperator_length == 0) {
					str_index_cache--;
				} else {
					str_index--;
				}
				allocated_value_size = 0;
				last_seperator_position = str_index + (seperator_length >= 1 || seperator_length == 0 ? 1 : 0);
				if (is_eos) break;
				continue;
			} else {
				allocated_value_size++;
			}
		}
		allocated_value_size++;
	}
	/*if (found_words_counts > 0) {
		out[found_words_counts] = XTD_NULL;
	}*/
	return found_words_counts;
	
	xstring_cstr_split_with_length_1_release_and_return_null:
		if (found_words_counts > 0) {
            for (secondary_index = 0; secondary_index < found_words_counts-1; secondary_index++) {
                allocator.memory_free(out[secondary_index]);
            }
			if ((*out) != XTD_NULL) {
				allocator.memory_free(out);
			}
        }
        return 0;
}

/*
    
*/
#define xstring_cstr_split_with_length xstring_cstr_split_with_length_1

/*
    
*/
static size_t xstring_cstr_split_1(XAllocator allocator, char *char_array, char *seperator, char ***out) {
    return xstring_cstr_split_with_length_1(allocator, xstring_cstr_length(char_array), char_array, seperator, out);
}

/*
    
*/
#define xstring_cstr_split xstring_cstr_split_1

/*!
    
*/
static void xstring_cstr_copy(char *src, char *dest, size_t len) {
    char* pDst = (char *) dest;
    char const * pSrc = (char const *) src;
    while(len--){
        *pDst++ = *pSrc++;
    }
}

/*!
    
*/
static char *xstring_cstr_trim_memory_to_size(XAllocator allocator, char *mem_allocated_chars) {
    size_t length = xstring_cstr_length(mem_allocated_chars);
    char *copy = (char *) allocator.memory_malloc(length+1);
    xstring_cstr_copy(mem_allocated_chars, copy, length);
    copy[length] = '\0';
    allocator.memory_free(mem_allocated_chars);
    return copy;
}

/*!
    
*/
static const char *xstring_cstr_char_value(XAllocator allocator, char ch) {
    char *cstr = (char *) allocator.memory_malloc(2 * sizeof(char));
    cstr[0] = ch;
    cstr[1] = '\0';
    return cstr;
}

/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.
 */
static char* itoa_by_lukas(long value, char* result, int base) {
    /* check that the base if valid*/
    char *ptr, *ptr1, tmp_char;
    long tmp_value;
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    ptr = result, ptr1 = result;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    /* Apply negative sign*/
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

/*!
    
*/
#define XTD_FLOAT_PRECISION_STR_SIZE 21

/*!
    TODO: update to show all floating values
*/
static char *xstring_float_to_cstr_internal(double value, char *result, int decimal_places) {
    uint16_t decimals;
    long units;
    long index;
    char *cstr = result + (XTD_FLOAT_PRECISION_STR_SIZE+decimal_places);

    if (value < 0) {
        decimals = (long)(value * -100) % 100;
        units = (long)(-1 * value);
    } else {
        decimals = (long)(value * 100) % 100;
        units = (long)value;
    }
    index = 0;
    *--cstr = '\0';
    while (decimal_places-- > 0) {
        *--cstr = (decimals % 10) + '0';
        decimals /= 10;
    }
    *--cstr = '.';
    do {
        *--cstr = (units % 10) + '0';
        units /= 10;
    } while (units > 0);
    if (value < 0) result[index++] = '-';
    while(*cstr != '\0') {
        result[index++] = *cstr++;
    }
    result[index] = '\0';

    return result;
}

/*!
    
*/
static const char *xstring_cstr_int_value(XAllocator allocator, int value) {
    char *cstr = (char *) allocator.memory_malloc(12 * sizeof(char));
    cstr = itoa_by_lukas(value, cstr, 10);
#ifndef XTD_DONT_TRIM_MANAGED_CSTRING
    cstr = xstring_cstr_trim_memory_to_size(allocator, cstr);
#endif
    return cstr;
}

/*!
    
*/
static const char *xstring_cstr_long_value(XAllocator allocator, long value) {
    char *cstr = (char *) allocator.memory_malloc(12 * sizeof(char));
    cstr = itoa_by_lukas(value, cstr, 10);
#ifndef XTD_DONT_TRIM_MANAGED_CSTRING
    cstr = xstring_cstr_trim_memory_to_size(allocator, cstr);
#endif
    return cstr;
}

/*!
    
*/
static const char *xstring_cstr_float_value(XAllocator allocator, float value, int decimal_places) {
    char *cstr = (char *) allocator.memory_malloc(XTD_FLOAT_PRECISION_STR_SIZE+decimal_places * sizeof(char));
    cstr = xstring_float_to_cstr_internal(value, cstr, decimal_places);
#ifndef XTD_DONT_TRIM_MANAGED_CSTRING
    cstr = xstring_cstr_trim_memory_to_size(allocator, cstr);
#endif
    return cstr;
}

/*!
    
*/
static const char *xstring_cstr_double_value(XAllocator allocator, double value, int decimal_places) {
    char *cstr = (char *) allocator.memory_malloc(XTD_FLOAT_PRECISION_STR_SIZE+decimal_places * sizeof(char));
    cstr = xstring_float_to_cstr_internal(value, cstr, decimal_places);
#ifndef XTD_DONT_TRIM_MANAGED_CSTRING
    cstr = xstring_cstr_trim_memory_to_size(allocator, cstr);
#endif
    return cstr;
}

/*!
    
*/
#define xstring_cstr_pointer_value

/*!
    
*/
static char *xstring_cstr_concat_cstr(XAllocator allocator, char *dest, char *to_concat) {
    size_t index;
    size_t dest_length = xstring_cstr_length(dest);
    size_t to_concat_length = xstring_cstr_length(to_concat);
    char *cstr = (char *) allocator.memory_malloc(sizeof(char) * dest_length + to_concat_length + 1);
    for (index = 0; index < dest_length; index++) {
        cstr[index] = dest[index];
    }
    for (; index < to_concat_length+dest_length; index++) {
        cstr[index] = to_concat[index-dest_length];
    }
    cstr[index] = '\0';
    return cstr;
}

/*!
    
*/
static char *xstring_cstr_concat_cstr_free_old(XAllocator allocator, char *dest, char *to_concat) {
    char *cstr = xstring_cstr_concat_cstr(allocator, dest, to_concat);
    allocator.memory_free(dest);
    return cstr;
}

/*!
    
*/
static char *xstring_cstr_concat_char(XAllocator allocator, char *dest, char value) {
    size_t index;
    char *to_concat = (char *) xstring_cstr_char_value(allocator, value);
    size_t dest_length = xstring_cstr_length(dest);
    size_t to_concat_length = xstring_cstr_length(to_concat);
    char *cstr = (char *) allocator.memory_malloc(sizeof(char) * dest_length + to_concat_length + 1);
    for (index = 0; index < dest_length; index++) {
        cstr[index] = dest[index];
    }
    for (; index < to_concat_length+dest_length; index++) {
        cstr[index] = to_concat[index-dest_length];
    }
    cstr[index] = '\0';
    allocator.memory_free(to_concat);
    return cstr;
}

/*!
    
*/
static char *xstring_cstr_concat_char_free_old(XAllocator allocator, char *dest, char value) {
    char *cstr = xstring_cstr_concat_char(allocator, dest, value);
    allocator.memory_free(dest);
    return cstr;
}

/*!
    
*/
static char *xstring_cstr_concat_int(XAllocator allocator, char *dest, int value) {
    size_t index;
    char *to_concat = (char *) xstring_cstr_int_value(allocator, value);
    size_t dest_length = xstring_cstr_length(dest);
    size_t to_concat_length = xstring_cstr_length(to_concat);
    char *cstr = (char *) allocator.memory_malloc(sizeof(char) * dest_length + to_concat_length + 1);
    for (index = 0; index < dest_length; index++) {
        cstr[index] = dest[index];
    }
    for (; index < to_concat_length+dest_length; index++) {
        cstr[index] = to_concat[index-dest_length];
    }
    cstr[index] = '\0';
    allocator.memory_free(to_concat);
    return cstr;
}

/*!
    
*/
static char *xstring_cstr_concat_int_free_old(XAllocator allocator, char *dest, int value) {
    char *cstr = xstring_cstr_concat_int(allocator, dest, value);
    allocator.memory_free(dest);
    return cstr;
}

/*!
    
*/
static char *xstring_cstr_concat_long(XAllocator allocator, char *dest, long value) {
    size_t index;
    char *to_concat = (char *) xstring_cstr_long_value(allocator, value);
    size_t dest_length = xstring_cstr_length(dest);
    size_t to_concat_length = xstring_cstr_length(to_concat);
    char *cstr = (char *) allocator.memory_malloc(sizeof(char) * dest_length + to_concat_length + 1);
    for (index = 0; index < dest_length; index++) {
        cstr[index] = dest[index];
    }
    for (; index < to_concat_length+dest_length; index++) {
        cstr[index] = to_concat[index-dest_length];
    }
    cstr[index] = '\0';
    allocator.memory_free(to_concat);
    return cstr;
}

/*!
    
*/
static char *xstring_cstr_concat_long_free_old(XAllocator allocator, char *dest, long value) {
    char *cstr = xstring_cstr_concat_long(allocator, dest, value);
    allocator.memory_free(dest);
    return cstr;
}

/*!
    
*/
static char *xstring_cstr_concat_double(XAllocator allocator, char *dest, double value) {
    size_t index;
    char *to_concat = (char *) xstring_cstr_double_value(allocator, value, 2);
    size_t dest_length = xstring_cstr_length(dest);
    size_t to_concat_length = xstring_cstr_length(to_concat);
    char *cstr = (char *) allocator.memory_malloc(sizeof(char) * dest_length + to_concat_length + 1);
    for (index = 0; index < dest_length; index++) {
        cstr[index] = dest[index];
    }
    for (; index < to_concat_length+dest_length; index++) {
        cstr[index] = to_concat[index-dest_length];
    }
    cstr[index] = '\0';
    allocator.memory_free(to_concat);
    return cstr;
}

/*!
    
*/
static char *xstring_cstr_concat_double_free_old(XAllocator allocator, char *dest, double value) {
    char *cstr = xstring_cstr_concat_double(allocator, dest, value);
    allocator.memory_free(dest);
    return cstr;
}

/*!
    
*/
static char *xstring_cstr_concat_float(XAllocator allocator, char *dest, float value) {
    size_t index;
    char *to_concat = (char *) xstring_cstr_float_value(allocator, value, 2);
    size_t dest_length = xstring_cstr_length(dest);
    size_t to_concat_length = xstring_cstr_length(to_concat);
    char *cstr = (char *) allocator.memory_malloc(sizeof(char) * dest_length + to_concat_length + 1);
    for (index = 0; index < dest_length; index++) {
        cstr[index] = dest[index];
    }
    for (; index < to_concat_length+dest_length; index++) {
        cstr[index] = to_concat[index-dest_length];
    }
    cstr[index] = '\0';
    allocator.memory_free(to_concat);
    return cstr;
}

/*!
    
*/
static char *xstring_cstr_concat_float_free_old(XAllocator allocator, char *dest, float value) {
    char *cstr = xstring_cstr_concat_float(allocator, dest, value);
    allocator.memory_free(dest);
    return cstr;
}

/*!
    
*/
#define xstring_cstr_concat_pointer

/*!
    
*/
#define xstring_cstr_concat_pointer_free_old

/*!
    
*/
static char *xstring_cstr_append_cstr(XAllocator allocator, char *dest, char *to_append, size_t pos) {
    char *cstr;
    size_t index;
    size_t sub_index;
    size_t dest_index;
    size_t dest_length;
    size_t to_append_length;
    size_t new_value_length;

    index = 0;
    sub_index = 0;
    dest_index = 0;
    dest_length = xstring_cstr_length(dest);
    to_append_length = xstring_cstr_length(to_append);
    if (pos < 0 || pos > dest_length) return XTD_NULL;
    new_value_length = dest_length + to_append_length + 1;
    cstr = (char *) allocator.memory_malloc(sizeof(char) * new_value_length);
    xstring_cstr_append_cstr_copy_cstr:
        for (; index < new_value_length-1; index++, dest_index++) {
            cstr[index] = dest[dest_index];
            if (index == pos) goto xstring_cstr_append_cstr_copy_to_append;
        }
        cstr[index] = '\0';

    return cstr;
    xstring_cstr_append_cstr_copy_to_append:
        for (; sub_index < to_append_length; sub_index++, index++) {
            cstr[index] = to_append[sub_index];
        }
        goto xstring_cstr_append_cstr_copy_cstr;
}

/*!
    
*/
static char *xstring_cstr_append_cstr_free_old(XAllocator allocator, char *dest, char *to_append, size_t pos) {
    char *cstr = xstring_cstr_append_cstr(allocator, dest, to_append, pos);
    allocator.memory_free(dest);
    return cstr;
}

/*

*/
#define xstring_cstr_append_cstr_prefix(allocator, dest, to_append) xstring_cstr_append_cstr(allocator, dest, to_append, 0)

/*

*/
#define xstring_cstr_append_cstr_suffix(allocator, dest, to_append) xstring_cstr_append_cstr(allocator, dest, to_append, xstring_cstr_length(dest))

/*

*/
#define xstring_cstr_append_cstr_prefix_free_old(allocator, dest, to_append) xstring_cstr_append_cstr_free_old(allocator, dest, to_append, 0)

/*

*/
#define xstring_cstr_append_cstr_suffix_free_old(allocator, dest, to_append) xstring_cstr_append_cstr_free_old(allocator, dest, to_append, xstring_cstr_length(dest))

/*!
    
*/
static char *xstring_cstr_append_char(XAllocator allocator, char *dest, char value, size_t pos) {
    char *to_concat = (char *) xstring_cstr_char_value(allocator, value);
    return xstring_cstr_append_cstr(allocator, dest, to_concat, pos);
}

/*!
    
*/
static char *xstring_cstr_append_char_free_old(XAllocator allocator, char *dest, char value, size_t pos) {
    char *cstr = xstring_cstr_append_char(allocator, dest, value, pos);
    allocator.memory_free(dest);
    return cstr;
}

/*

*/
#define xstring_cstr_append_char_prefix(allocator, dest, value) xstring_cstr_append_char(allocator, dest, value, 0)

/*

*/
#define xstring_cstr_append_char_suffix(allocator, dest, value) xstring_cstr_append_char(allocator, dest, value, xstring_cstr_length(dest))

/*

*/
#define xstring_cstr_append_char_prefix_free_old(allocator, dest, value) xstring_cstr_append_char_free_old(allocator, dest, value, 0)

/*

*/
#define xstring_cstr_append_char_suffix_free_old(allocator, dest, value) xstring_cstr_append_char_free_old(allocator, dest, value, xstring_cstr_length(dest))

/*!
    
*/
static char *xstring_cstr_append_int(XAllocator allocator, char *dest, int value, size_t pos) {
    char *to_concat = (char *) xstring_cstr_int_value(allocator, value);
    return xstring_cstr_append_cstr(allocator, dest, to_concat, pos);
}

/*!
    
*/
static char *xstring_cstr_append_int_free_old(XAllocator allocator, char *dest, int value, size_t pos) {
    char *cstr = xstring_cstr_append_int(allocator, dest, value, pos);
    allocator.memory_free(dest);
    return cstr;
}

/*

*/
#define xstring_cstr_append_int_prefix(allocator, dest, value) xstring_cstr_append_int(allocator, dest, value, 0)

/*

*/
#define xstring_cstr_append_int_suffix(allocator, dest, value) xstring_cstr_append_int(allocator, dest, value, xstring_cstr_length(dest))

/*

*/
#define xstring_cstr_append_int_prefix_free_old(allocator, dest, value) xstring_cstr_append_int_free_old(allocator, dest, value, 0)

/*

*/
#define xstring_cstr_append_int_suffix_free_old(allocator, dest, value) xstring_cstr_append_int_free_old(allocator, dest, value, xstring_cstr_length(dest))

/*!
    
*/
static char *xstring_cstr_append_long(XAllocator allocator, char *dest, long value, size_t pos) {
    char *to_concat = (char *) xstring_cstr_long_value(allocator, value);
    return xstring_cstr_append_cstr(allocator, dest, to_concat, pos);
}

/*!
    
*/
static char *xstring_cstr_append_long_free_old(XAllocator allocator, char *dest, long value, size_t pos) {
    char *cstr = xstring_cstr_append_long(allocator, dest, value, pos);
    allocator.memory_free(dest);
    return cstr;
}

/*

*/
#define xstring_cstr_append_long_prefix(allocator, dest, value) xstring_cstr_append_long(allocator, dest, value, 0)

/*

*/
#define xstring_cstr_append_long_suffix(allocator, dest, value) xstring_cstr_append_long(allocator, dest, value, xstring_cstr_length(dest))

/*

*/
#define xstring_cstr_append_long_prefix_free_old(allocator, dest, value) xstring_cstr_append_long_free_old(allocator, dest, value, 0)

/*

*/
#define xstring_cstr_append_long_suffix_free_old(allocator, dest, value) xstring_cstr_append_long_free_old(allocator, dest, value, xstring_cstr_length(dest))

/*!
    
*/
static char *xstring_cstr_append_double(XAllocator allocator, char *dest, double value, size_t pos) {
    char *to_concat = (char *) xstring_cstr_double_value(allocator, value, 2);
    return xstring_cstr_append_cstr(allocator, dest, to_concat, pos);
}

/*!
    
*/
static char *xstring_cstr_append_double_free_old(XAllocator allocator, char *dest, double value, size_t pos) {
    char *cstr = xstring_cstr_append_double(allocator, dest, value, pos);
    allocator.memory_free(dest);
    return cstr;
}

/*

*/
#define xstring_cstr_append_double_prefix(allocator, dest, value) xstring_cstr_append_double(allocator, dest, value, 0)

/*

*/
#define xstring_cstr_append_double_suffix(allocator, dest, value) xstring_cstr_append_double(allocator, dest, value, xstring_cstr_length(dest))

/*

*/
#define xstring_cstr_append_double_prefix_free_old(allocator, dest, value) xstring_cstr_append_double_free_old(allocator, dest, value, 0)

/*

*/
#define xstring_cstr_append_double_suffix_free_old(allocator, dest, value) xstring_cstr_append_double_free_old(allocator, dest, value, xstring_cstr_length(dest))

/*!
    
*/
static char *xstring_cstr_append_float(XAllocator allocator, char *dest, float value, size_t pos) {
    char *to_concat = (char *) xstring_cstr_float_value(allocator, value, 2);
    return xstring_cstr_append_cstr(allocator, dest, to_concat, pos);
}

/*!
    
*/
static char *xstring_cstr_append_float_free_old(XAllocator allocator, char *dest, float value, size_t pos) {
    char *cstr = xstring_cstr_append_float(allocator, dest, value, pos);
    allocator.memory_free(dest);
    return cstr;
}

/*

*/
#define xstring_cstr_append_float_prefix(allocator, dest, value) xstring_cstr_append_float(allocator, dest, value, 0)

/*

*/
#define xstring_cstr_append_float_suffix(allocator, dest, value) xstring_cstr_append_float(allocator, dest, value, xstring_cstr_length(dest))

/*

*/
#define xstring_cstr_append_float_prefix_free_old(allocator, dest, value) xstring_cstr_append_float_free_old(allocator, dest, value, 0)

/*

*/
#define xstring_cstr_append_float_suffix_free_old(allocator, dest, value) xstring_cstr_append_float_free_old(allocator, dest, value, xstring_cstr_length(dest))

/*!
    
*/
static char *xstring_cstr_append_pointer(XAllocator allocator, char *dest, void *value, size_t pos) {
    char *to_concat = (char *) xstring_cstr_pointer_value(allocator, value);
    return xstring_cstr_append_cstr(allocator, dest, to_concat, pos);
}

/*!
    
*/
static char *xstring_cstr_append_pointer_free_old(XAllocator allocator, char *dest, void *value, size_t pos) {
    char *cstr = xstring_cstr_append_pointer(allocator, dest, value, pos);
    allocator.memory_free(dest);
    return cstr;
}

/*

*/
#define xstring_cstr_append_pointer_prefix(allocator, dest, value) xstring_cstr_append_float(allocator, dest, value, 0)

/*

*/
#define xstring_cstr_append_pointer_suffix(allocator, dest, value) xstring_cstr_append_float(allocator, dest, value, xstring_cstr_length(dest))

/*

*/
#define xstring_cstr_append_pointer_prefix_free_old(allocator, dest, value) xstring_cstr_append_float_free_old(allocator, dest, value, 0)

/*

*/
#define xstring_cstr_append_pointer_suffix_free_old(allocator, dest, value) xstring_cstr_append_float_free_old(allocator, dest, value, xstring_cstr_length(dest))


/*!
    
*/
#include <stdarg.h>
/*static char *xstring_cstr_format_1(XAllocator allocator, const char *str, ...) {
    va_list ap;
    unsigned argscount;
    char *version_text = (char *) allocator.memory_malloc(2000 * sizeof(char));
    va_start(ap, argscount);
    va_end(ap);
    return version_text;
}*/

/*!
    
*/
/*#define xstring_cstr_format xstring_cstr_format_1*/

/*!

*/
#define XTD__INTERNAL__XSTRING_CONCAT_ESCAPE_SEQ(case_char, ch) case case_char:\
    value = xstring_cstr_concat_char_free_old(allocator, value, ch);\
    break

/*!
    /see https://en.wikipedia.org/wiki/Escape_sequences_in_C#Table_of_escape_sequences
*/
/* treat octaland hexadecimal, unicode u and U*/
static enum x_stat xstring_cstr_escape_sequences(XAllocator allocator, char *unescape_cstr, char **out, size_t *err_pos_out) {
    size_t index;
    char *value = xstring_cstr_concat_cstr(allocator, XTD_NULL, "");
    size_t unescape_cstr_length = xstring_cstr_length(unescape_cstr);

    for (index = 0; index < unescape_cstr_length; index++) {
        if (unescape_cstr[index] == '\\') {
            index++;
            switch (unescape_cstr[index]) {
                XTD__INTERNAL__XSTRING_CONCAT_ESCAPE_SEQ('a', '\a');
                XTD__INTERNAL__XSTRING_CONCAT_ESCAPE_SEQ('b', '\b');
                /*XTD__INTERNAL__XSTRING_CONCAT_ESCAPE_SEQ('e', '\e');*/
                XTD__INTERNAL__XSTRING_CONCAT_ESCAPE_SEQ('f', '\f');
                XTD__INTERNAL__XSTRING_CONCAT_ESCAPE_SEQ('n', '\n');
                XTD__INTERNAL__XSTRING_CONCAT_ESCAPE_SEQ('r', '\r');
                XTD__INTERNAL__XSTRING_CONCAT_ESCAPE_SEQ('t', '\t');
                XTD__INTERNAL__XSTRING_CONCAT_ESCAPE_SEQ('v', '\v');
                XTD__INTERNAL__XSTRING_CONCAT_ESCAPE_SEQ('\\', '\\');
                XTD__INTERNAL__XSTRING_CONCAT_ESCAPE_SEQ('\'', '\'');
                XTD__INTERNAL__XSTRING_CONCAT_ESCAPE_SEQ('\"', '\"');
                XTD__INTERNAL__XSTRING_CONCAT_ESCAPE_SEQ('?', '\?');
                default:
                    if (out != XTD_NULL) *out = XTD_NULL;
                    if (err_pos_out != XTD_NULL) *err_pos_out = index;
                    allocator.memory_free(value);
                    return XTD_PARSING_ERR;
            }
        } else {
            value = xstring_cstr_concat_char_free_old(allocator, value, unescape_cstr[index]);
        }
    }
    if (out != XTD_NULL) *out = value;

    return XTD_OK;
}

/*!

*/
#define XTD__INTERNAL__XSTRING_CONCAT_UNESCAPE_SEQ(case_char, cstr) case case_char:\
    value = xstring_cstr_concat_cstr_free_old(allocator, value, cstr);\
    break

/*!

*/
static enum x_stat xstring_cstr_unescape_sequences(XAllocator allocator, char *escaped_cstr, char **out, size_t *err_pos_out) {
    size_t index;
    char *value = xstring_cstr_concat_cstr(allocator, XTD_NULL, "");
    size_t escaped_cstr_length = xstring_cstr_length(escaped_cstr);

    for (index = 0; index < escaped_cstr_length; index++) {
        switch (escaped_cstr[index]) {
            XTD__INTERNAL__XSTRING_CONCAT_UNESCAPE_SEQ('\a', "\\a");
            XTD__INTERNAL__XSTRING_CONCAT_UNESCAPE_SEQ('\b', "\\b");
            /*XTD__INTERNAL__XSTRING_CONCAT_UNESCAPE_SEQ('\e', "\\e");*/
            XTD__INTERNAL__XSTRING_CONCAT_UNESCAPE_SEQ('\f', "\\f");
            XTD__INTERNAL__XSTRING_CONCAT_UNESCAPE_SEQ('\n', "\\n");
            XTD__INTERNAL__XSTRING_CONCAT_UNESCAPE_SEQ('\r', "\\r");
            XTD__INTERNAL__XSTRING_CONCAT_UNESCAPE_SEQ('\t', "\\t");
            XTD__INTERNAL__XSTRING_CONCAT_UNESCAPE_SEQ('\v', "\\v");
            XTD__INTERNAL__XSTRING_CONCAT_UNESCAPE_SEQ('\\', "\\\\");
            XTD__INTERNAL__XSTRING_CONCAT_UNESCAPE_SEQ('\'', "\\'");
            XTD__INTERNAL__XSTRING_CONCAT_UNESCAPE_SEQ('\"', "\\\"");
            XTD__INTERNAL__XSTRING_CONCAT_UNESCAPE_SEQ('\?', "\\?");
            default:
                value = xstring_cstr_concat_char_free_old(allocator, value, escaped_cstr[index]);
        }
    }
    if (out != XTD_NULL) *out = value;

    return XTD_OK;
}

/*!

*/
#define xstring_cstr_char_to_lower(ch) ((ch >= 'A' && ch <= 'Z') ? ch - 'A' + 'a' : ch)

/*!

*/
#define xstring_cstr_char_to_lower_ref(ch) ((ch >= 'A' && ch <= 'Z') ? ch += 32 : ch)

/*!

*/
#define xstring_cstr_char_to_upper(ch) ((ch >= 'a' && ch <= 'z') ? ch - 'a' + 'A' : ch)

/*!

*/
#define xstring_cstr_char_to_upper_ref(ch) ((ch >= 'a' && ch <= 'z') ? ch -= 32 : ch)

/*!

*/
static enum x_stat xstring_cstr_to_lower_case(XAllocator allocator, char *char_array, char **out) {
    size_t index;
    size_t length;
    char *changed_case;
    
    length = xstring_cstr_length(char_array);
    if (length == 0 || out == XTD_NULL) return XTD_NO_OP;
    changed_case = (char *) allocator.memory_calloc(length+1, sizeof(char));
    if (!changed_case) return XTD_ALLOC_ERR;
    for (index = 0; index < length; index++) {
        changed_case[index] = xstring_cstr_char_to_lower(char_array[index]);
    }
    changed_case[length] = '\0';
    *out = changed_case;

    return XTD_OK;
}

/*!

*/
static char *xstring_cstr_to_lower_case_ref(char *char_array) {
    size_t length = 0;
    for (; char_array[length] != '\0';) {
        xstring_cstr_char_to_lower_ref(char_array[length]);
        length++;
    }
    return char_array;
}

/*!

*/
static enum x_stat xstring_cstr_to_upper_case(XAllocator allocator, char *char_array, char **out) {
    size_t index;
    size_t length;
    char *changed_case;
    
    length = xstring_cstr_length(char_array);
    if (length == 0 || out == XTD_NULL) return XTD_NO_OP;
    changed_case = (char *) allocator.memory_calloc(length+1, sizeof(char));
    if (!changed_case) return XTD_ALLOC_ERR;
    for (index = 0; index < length; index++) {
        changed_case[index] = xstring_cstr_char_to_upper(char_array[index]);
    }
    changed_case[length] = '\0';
    *out = changed_case;

    return XTD_OK;
}

/*!

*/
static char *xstring_cstr_to_upper_case_ref(char *char_array) {
    size_t length = 0;
    for (; char_array[length] != '\0';) {
        xstring_cstr_char_to_upper_ref(char_array[length]);
        length++;
    }
    return char_array;
}

/* TODO */
#define xstring_cstr_hash
#define xstring_cstr_replace
#define xstring_cstr_replace_first
#define xstring_cstr_replace_last
#define xstring_cstr_trim

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
    for (index = 0; char_array[index] != '\0'; index++) {
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
