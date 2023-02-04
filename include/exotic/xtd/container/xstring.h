
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <iamthecarisma@gmail.com>
    \date 05 June 2021
    \file xstring.h
*/

#ifndef EXOTIC_XSTRING_H
#define EXOTIC_XSTRING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "xvector.h"
#include "xhashtable.h"

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
static enum x_stat xstring_cstr_sub_string_in_range_with_length_1(XAllocator allocator, size_t char_array_length, char *char_array, size_t begin_index, size_t end_index, char **out) {
    char *result;
    size_t str_index = 0;
    if (begin_index < 0 || begin_index > char_array_length || end_index > char_array_length) {
        return XTD_OUT_OF_RANGE_ERR;
    }
    if (out == XTD_NULL) {
        return XTD_PARAM_NULL_ERR;
    }
    result = (char *) allocator.memory_calloc((end_index - begin_index), sizeof(char));
    if (!result) return XTD_ALLOC_ERR;
    for (; begin_index < end_index; ++begin_index) {
        result[str_index++] = char_array[begin_index];
    }
    *out = result;
    return XTD_OK;
}

/*
    
*/
#define xstring_cstr_sub_string_in_range_with_length xstring_cstr_sub_string_in_range_with_length_1

/*
    
*/
static enum x_stat xstring_cstr_sub_string_in_range_1(XAllocator allocator, char *char_array, size_t begin_index, size_t end_index, char **out) {
    return xstring_cstr_sub_string_in_range_with_length_1(allocator, xstring_cstr_length(char_array), char_array, begin_index, end_index, out);
}

/*
    
*/
#define xstring_cstr_sub_string_in_range xstring_cstr_sub_string_in_range_1

/*
    
*/
static enum x_stat xstring_cstr_sub_string_1(XAllocator allocator, char *char_array, size_t begin_index, char **out) {
    size_t char_array_length = xstring_cstr_length(char_array);
    return xstring_cstr_sub_string_in_range_with_length_1(allocator, char_array_length, char_array, begin_index, char_array_length, out);
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
                if (allocated_value_size == 1) {
                    value = (char *) allocator.memory_malloc(allocated_value_size * sizeof(char));
                    value[0] = '\0';
                } else {
                    if (xstring_cstr_sub_string_in_range_1(allocator, char_array, last_seperator_position, str_index_cache, &value) != XTD_OK) {
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
        if (allocated_value_size == 1) {
            value = (char *) allocator.memory_malloc(allocated_value_size * sizeof(char));
            value[0] = '\0';
        } else {
            if (xstring_cstr_sub_string_in_range_1(allocator, char_array, (last_seperator_position-(seperator_length == 1 && found_words_counts-1 == 0 ? 1 : 0)), str_index_cache, &value) != XTD_OK) {
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
                if (allocated_value_size == 0) {
				    value = (char *) allocator.memory_malloc(allocated_value_size+1 * sizeof(char));
                    value[0] = '\0';
                } else {
                    if (xstring_cstr_sub_string_in_range_1(allocator, char_array, last_seperator_position, str_index_cache, &value) != XTD_OK) {
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

#ifdef _MSC_VER
#define xstring_sprintf(x,y,z,a,b,c) sprintf_s(x, y, z, a, b, c);
#define xstring_sprintf1(x,y,z,a) xstring_sprintf(x,y,z,a,"","")
#define xstring_sprintf2(x,y,z,a,b) xstring_sprintf(x,y,z,a,b,"")
#define xstring_sprintf3(x,y,z,a,b,c) xstring_sprintf(x,y,z,a,b,c)
#else
#define xstring_sprintf(x,y,z,a,b) sprintf(x, z, a, b);
#define xstring_sprintf1(x,y,z,a) sprintf(x, z, a)
#define xstring_sprintf2(x,y,z,a,b) sprintf(x, z, a, b)
#define xstring_sprintf3(x,y,z,a,b,c) sprintf(x, z, a, b, c)
#endif

/*!
    The default size of the pointer string value in memory
*/
#ifndef XTD_XSTRING_POINTER_STR_SIZE
#define XTD_XSTRING_POINTER_STR_SIZE 15
#endif

/*!
    Get the string value of a pointer
    \code{.c}
    char *value = xstring_cstr_pointer_value(xallocator, NULL);
    //value == "(null)"
    \endcode

    The returned value needs to be freed as it is allocated with 
    \struct XAllocator.memory_calloc

    \param allocator the memory allocation manager
    \param value the pointer to get it string value

    \return the pointer string value
*/
static const char *xstring_cstr_pointer_value(XAllocator allocator, void *value) {
    char *cstr = (char *) allocator.memory_calloc(XTD_XSTRING_POINTER_STR_SIZE, sizeof(char));
    xstring_sprintf1(cstr, XTD_XSTRING_POINTER_STR_SIZE, "%p", value);
#ifndef XTD_DONT_TRIM_MANAGED_CSTRING
    cstr = xstring_cstr_trim_memory_to_size(allocator, cstr);
#endif
    return cstr;
}

/*!
    Get a pointer string value using the c lib sprintf_s|sprintf
*/
#define xstring_cstr_pointer_value_snprintf xstring_cstr_pointer_value

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
    if (dest != XTD_NULL) allocator.memory_free(dest);
    return cstr;
}

/*!
    
*/
static char *xstring_cstr_concat_char(XAllocator allocator, char *dest, char value) {
    char *to_concat = (char *) xstring_cstr_char_value(allocator, value);
    char *result = xstring_cstr_concat_cstr(allocator, dest, to_concat);
    allocator.memory_free(to_concat);
    return result;
}

/*!
    
*/
static char *xstring_cstr_concat_char_free_old(XAllocator allocator, char *dest, char value) {
    char *cstr = xstring_cstr_concat_char(allocator, dest, value);
    if (dest != XTD_NULL) allocator.memory_free(dest);
    return cstr;
}

/*!
    
*/
static char *xstring_cstr_concat_int(XAllocator allocator, char *dest, int value) {
    char *to_concat = (char *) xstring_cstr_int_value(allocator, value);
    char *result = xstring_cstr_concat_cstr(allocator, dest, to_concat);
    allocator.memory_free(to_concat);
    return result;
}

/*!
    
*/
static char *xstring_cstr_concat_int_free_old(XAllocator allocator, char *dest, int value) {
    char *cstr = xstring_cstr_concat_int(allocator, dest, value);
    if (dest != XTD_NULL) allocator.memory_free(dest);
    return cstr;
}

/*!
    
*/
static char *xstring_cstr_concat_long(XAllocator allocator, char *dest, long value) {
    char *to_concat = (char *) xstring_cstr_long_value(allocator, value);
    char *result = xstring_cstr_concat_cstr(allocator, dest, to_concat);
    allocator.memory_free(to_concat);
    return result;
}

/*!
    
*/
static char *xstring_cstr_concat_long_free_old(XAllocator allocator, char *dest, long value) {
    char *cstr = xstring_cstr_concat_long(allocator, dest, value);
    if (dest != XTD_NULL) allocator.memory_free(dest);
    return cstr;
}

/*!
    
*/
static char *xstring_cstr_concat_double(XAllocator allocator, char *dest, double value) {
    char *to_concat = (char *) xstring_cstr_double_value(allocator, value, 2);
    char *result = xstring_cstr_concat_cstr(allocator, dest, to_concat);
    allocator.memory_free(to_concat);
    return result;
}

/*!
    
*/
static char *xstring_cstr_concat_double_free_old(XAllocator allocator, char *dest, double value) {
    char *cstr = xstring_cstr_concat_double(allocator, dest, value);
    if (dest != XTD_NULL) allocator.memory_free(dest);
    return cstr;
}

/*!
    
*/
static char *xstring_cstr_concat_float(XAllocator allocator, char *dest, float value) {
    char *to_concat = (char *) xstring_cstr_float_value(allocator, value, 2);
    char *result = xstring_cstr_concat_cstr(allocator, dest, to_concat);
    allocator.memory_free(to_concat);
    return result;
}

/*!
    
*/
static char *xstring_cstr_concat_float_free_old(XAllocator allocator, char *dest, float value) {
    char *cstr = xstring_cstr_concat_float(allocator, dest, value);
    if (dest != XTD_NULL) allocator.memory_free(dest);
    return cstr;
}

/*!
    Concatenate a pointer value to a string, a new allocated string value is 
    returned which must be freed after use.

    \param allocator the memory allocation manager
    \param dest left operand string to add the pointer value to
    \param value pointer to concat to the dest param

    \return the resulting string value
*/
static char *xstring_cstr_concat_pointer(XAllocator allocator, char *dest, void *value) {
    char *to_concat = (char *) xstring_cstr_pointer_value(allocator, value);
    char *result = xstring_cstr_concat_cstr(allocator, dest, to_concat);
    allocator.memory_free(to_concat);
    return result;
}

/*!
    Concatenate a pointer value to a string, a new allocated string value is 
    returned which must be freed after use. The left most operand (dest) 
    which must be an allocated string on heap will be freed on behalf of the 
    caller.

    \param allocator the memory allocation manager
    \param dest left operand string which must be allocated on heap
    \param value pointer to concat to the dest param

    \return the resulting string value
*/
static char *xstring_cstr_concat_pointer_free_old(XAllocator allocator, char *dest, void *value) {
    char *cstr = xstring_cstr_concat_pointer(allocator, dest, value);
    if (dest != XTD_NULL) allocator.memory_free(dest);
    return cstr;
}

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
    if (dest != XTD_NULL) allocator.memory_free(dest);
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
    if (dest != XTD_NULL) allocator.memory_free(dest);
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
    if (dest != XTD_NULL) allocator.memory_free(dest);
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
    if (dest != XTD_NULL) allocator.memory_free(dest);
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
    if (dest != XTD_NULL) allocator.memory_free(dest);
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
    if (dest != XTD_NULL) allocator.memory_free(dest);
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
    if (dest != XTD_NULL) allocator.memory_free(dest);
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
    if (length == 0 || out == XTD_NULL) return XTD_NO_OP_ERR;
    changed_case = (char *) allocator.memory_calloc(length, sizeof(char));
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
static char *xstring_cstr_to_lower_case_mut(char *char_array) {
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
    if (length == 0 || out == XTD_NULL) return XTD_NO_OP_ERR;
    changed_case = (char *) allocator.memory_calloc(length, sizeof(char));
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
static char *xstring_cstr_to_upper_case_mut(char *char_array) {
    size_t length = 0;
    for (; char_array[length] != '\0';) {
        xstring_cstr_char_to_upper_ref(char_array[length]);
        length++;
    }
    return char_array;
}

/*!
    Return a copy of then string with the first character capitilized. 
    The out value is allocated using calloc so it is required to free to 
    properly destriyed it.

    \param allocator the memory allocation manager
    \param char_array the string to capitilize it first character
    \param out the allocated result output variable

    \return ::x_stat
*/
static enum x_stat xstring_cstr_to_sentence_case(XAllocator allocator, char *char_array, char **out) {
    size_t index;
    size_t length;
    char *changed_case;
    
    length = xstring_cstr_length(char_array);
    if (length == 0 || out == XTD_NULL) return XTD_NO_OP_ERR;
    changed_case = (char *) allocator.memory_calloc(length, sizeof(char));
    if (!changed_case) return XTD_ALLOC_ERR;
    changed_case[0] = xstring_cstr_char_to_upper(char_array[0]);
    for (index = 1; index < length; index++) {
        changed_case[index] = xstring_cstr_char_to_lower(char_array[index]);
    }
    changed_case[length] = '\0';
    *out = changed_case;

    return XTD_OK;
}

/*!
    Convert the string first character to capital letter. 
    The passed string parameter is modified but no extra allocation is done.

    \param char_array the string to capitilize it first character

    \return the modified string
*/
static char *xstring_cstr_to_sentence_case_mut(char *char_array) {
    size_t length = 0;
    xstring_cstr_char_to_upper_ref(char_array[length]);
    for (; char_array[++length] != '\0';) {
        xstring_cstr_char_to_lower_ref(char_array[length]);
    }
    return char_array;
}

/*!
    Check whether the character is whitespace character, in-file impl.
*/
#define XTD__INTERNAL__XSTRING_IS_WHITE_SPACE(ch) (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\v' || ch == '\f' || ch == '\r')

/*!
    Return a copy of then string with the first character of every word capitilized. 
    The out value is allocated using calloc so it is required to free to 
    properly destriyed it.

    \param allocator the memory allocation manager
    \param char_array the string to capitilize each word first character
    \param out the allocated result output variable

    \return ::x_stat
*/
static enum x_stat xstring_cstr_to_title_case(XAllocator allocator, char *char_array, char **out) {
    size_t index;
    size_t length;
    char *changed_case;
    
    length = xstring_cstr_length(char_array);
    if (length == 0 || out == XTD_NULL) return XTD_NO_OP_ERR;
    changed_case = (char *) allocator.memory_calloc(length, sizeof(char));
    if (!changed_case) return XTD_ALLOC_ERR;
    changed_case[0] = xstring_cstr_char_to_upper(char_array[0]);
    for (index = 1; index < length; index++) {
        changed_case[index] = (XTD__INTERNAL__XSTRING_IS_WHITE_SPACE(char_array[index-1])
            ? xstring_cstr_char_to_upper(char_array[index])
            : xstring_cstr_char_to_lower(char_array[index]));
    }
    changed_case[length] = '\0';
    *out = changed_case;

    return XTD_OK;
}

/*!
    Convert the string words first character to capital letter. 
    The passed string parameter is modified but no extra allocation is done.

    \param char_array the string to capitilize each word first character

    \return the modified string
*/
static char *xstring_cstr_to_title_case_mut(char *char_array) {
    size_t length = 0;
    xstring_cstr_char_to_upper_ref(char_array[length]);
    for (; char_array[++length] != '\0';) {
        if (XTD__INTERNAL__XSTRING_IS_WHITE_SPACE(char_array[length-1])) {
            xstring_cstr_char_to_upper_ref(char_array[length]);
        } else {
            xstring_cstr_char_to_lower_ref(char_array[length]);
        }
    }
    return char_array;
}

/*!
    Check whether the character is upper case. in-file impl.
*/
#define XTD__INTERNAL__XSTRING_IS_UPPER_CASE(ch) (ch >= 'A' && ch <= 'Z')

/*!
    Return a copy of the string with the characters cases inverted. 
    The out value is allocated using calloc so it is required to free to 
    properly destriyed it.

    \param allocator the memory allocation manager
    \param char_array the string to invert the case
    \param out the allocated result output variable

    \return ::x_stat
*/
static enum x_stat xstring_cstr_invert_case(XAllocator allocator, char *char_array, char **out) {
    size_t index;
    size_t length;
    char *changed_case;
    
    length = xstring_cstr_length(char_array);
    if (length == 0 || out == XTD_NULL) return XTD_NO_OP_ERR;
    changed_case = (char *) allocator.memory_calloc(length, sizeof(char));
    if (!changed_case) return XTD_ALLOC_ERR;
    for (index = 0; index < length; index++) {
        changed_case[index] = (!XTD__INTERNAL__XSTRING_IS_UPPER_CASE(char_array[index])
            ? xstring_cstr_char_to_upper(char_array[index])
            : xstring_cstr_char_to_lower(char_array[index]));
    }
    changed_case[length] = '\0';
    *out = changed_case;

    return XTD_OK;
}

/*!
    Convert the string words first character to capital letter. 
    The passed string parameter is modified but no extra allocation is done.

    \param char_array the string to capitilize each word first character
*/
static char *xstring_cstr_invert_case_mut(char *char_array) {
    size_t length = 0;
    for (; char_array[length] != '\0'; length++) {
        if (!XTD__INTERNAL__XSTRING_IS_UPPER_CASE(char_array[length])) {
            xstring_cstr_char_to_upper_ref(char_array[length]);
        } else {
            xstring_cstr_char_to_lower_ref(char_array[length]);
        }
    }
    return char_array;
}

/*!
    Remove some part of a string from the start value and replace 
    with a new string value if specified. The original string char_array is 
    not modified. A new value containing the modified value is returned. 

    \note The returned value must be freed after use 

    \param allocator the memory allocation manager
    \param char_array the string to invert the case
    \param start Zero-based index at which to start changing the char_array.
        - Negative index counts back from the end of the char_array — if start < 0, start + char_array.length is used.
        - If start < -char_array.length or start is omitted, 0 is used.
        - If start >= char_array.length, no element will be deleted, but the method will behave as an adding function, adding as many elements as provided.
    \param delete_count An integer indicating the number of elements in the char_array to remove from start.
        - If its value is greater than or equal to the number of elements after the position specified by start, then all the elements from start to the end of the char_array will be deleted. 
        - if value is less than 0 it gets converted to 0.
        - If delete_count is 0 or negative, no elements are removed.
    \param item the string to insert in place of the deleted values
    \param out the allocated result output variable

    \return ::x_stat
        - ::XTD_NO_OP_ERR if the char_array length is 0 or out is null
        - ::XTD_ALLOC_ERR if the allocator failed to allocate the result string
        - ::XTD_OK if all the operation completes successfully
*/
static enum x_stat xstring_cstr_splice(XAllocator allocator, char *char_array, signed long start, signed long delete_count, char *item, char **out) {
    size_t index;
    size_t length;
    size_t counter;
    size_t item_length;
    char *result;

    counter = 0;
    item_length = 0;
    length = xstring_cstr_length(char_array);
    if (length == 0 || !out) return XTD_NO_OP_ERR;
    if (item) { item_length = xstring_cstr_length(item); }
    if (start < 0) start += length;
    if (start > length) start = length;
    if (delete_count < 0) delete_count = 0;
    if (delete_count > (length-start)) delete_count = (length-start);
    result = (char *) allocator.memory_calloc(((length-delete_count) + item_length)+1, sizeof(char));
    if (!result) return XTD_ALLOC_ERR;
    for (index = 0; index < start; index++) {
        result[counter++] = char_array[index];
    }
    for (index = 0; (index < item_length && item); index++) {
        result[counter++] = item[index];
    }
    for (index = (start+delete_count); index < length; index++) {
        result[counter++] = char_array[index];
    }
    result[counter] = '\0';
    *out = result;

    return XTD_OK;
}

/*!
    Insert a string value at a specified index of a string.
*/
#define xstring_cstr_insert_at(allocator, char_array, index, value, out) xstring_cstr_splice(allocator, char_array, index, 0, value, out)

/*!
    Insert a string value at the end of a string.
*/
#define xstring_cstr_insert(allocator, char_array, value, out) xstring_cstr_insert_at(allocator, char_array, xstring_cstr_length(char_array), value, out)

/*!
    Extract a section of a string from index start to index end. 
    The original string char_array is not modified. A new value 
    containing the modified value is returned.
    
    - if char_array length is 0 no operation is performed
    - if index_start is less than 0 no operation is performed
    - if index_end is less than 0 the exract occur from the end
    - if the out parameter is not set no operation is performed
    - if index_end is same as the value of index_start no operation is perfromed
    - if \code index_end - index_start \endcode is equal to 0 no operation is performed
    - if index_start is greater or equal to the length of char_array no operation is perfromed
    - if index_end is greater than the char_array length index_end value is set to the char_array length

    \note The returned value must be freed after use 

    \param allocator the memory allocation manager
    \param char_array the string to invert the case
    \param index_start Zero-based index at which to start extract the char_array.
    \param index_end An integer indicating the number of characters in the char_array to extract from index_start
    \param item the string to insert in place of the deleted values
    \param out the allocated result output variable

    \return ::x_stat
        - ::XTD_NO_OP_ERR if the char_array length is 0 or out is null
        - ::XTD_ALLOC_ERR if the allocator failed to allocate the result string
        - ::XTD_OK if all the operation completes successfully
*/
static enum x_stat xstring_cstr_slice(XAllocator allocator, char *char_array, signed long index_start, signed long index_end, char **out) {
    size_t index;
    size_t length;
    size_t counter;
    char *result;

    counter = 0;
    length = xstring_cstr_length(char_array);
    if (length == 0 || index_start < 0 || ((index_end - index_start) == 0) || 
        index_start >= length || !out) return XTD_NO_OP_ERR;
    if (index_end < 0) index_end = length - (-index_end);
    if (index_end > length) index_end = length;
    result = (char *) allocator.memory_calloc((index_end - index_start)+1, sizeof(char));
    if (!result) return XTD_ALLOC_ERR;
    for (index = index_start; index < index_end; index++) {
        result[counter++] = char_array[index];
    }
    result[counter] = '\0';
    *out = result;

    return XTD_OK;
}

/*!
    Get a section of a string from a specific index
*/
#define xstring_cstr_extract_from(allocator, char_array, start, out) xstring_cstr_slice(allocator, char_array, start, xstring_cstr_length(char_array), out)

/* TODO */
#define xstring_cstr_replace
#define xstring_cstr_replace_first
#define xstring_cstr_replace_last
#define xstring_cstr_trim

#include "../util/xtypes_bounds.h"
#include "../typesys/xnumber.h"

/*!
    xstring format char pointer non symbol type def
*/
typedef char* XSTRH_CHAR_PTR;

/*!
    xstring format void pointer non symbol type def
*/
typedef void* XSTRH_VOID_PTR;

/*!
    
*/
SETUP_XHASHTABLE_FOR(XSTRH_CHAR_PTR, XSTRH_VOID_PTR)

/*!
    djb2 string hash but only hash the string part before '~' 
    to allow get hash for key that starts with instead of full key hash 
    for the xstring_cstr_format xhashtable key value lookup

    \param key string to be hashed
    \param len length of the string
    \param seed crypto seed for the hash algorithm

    \return the hashed value of the key
*/
static size_t xstring_cstr_format_hash_string__internal(char * const key, int len, uint32_t seed) {
    int c;
    const char *str = key;
    register size_t hash = seed + 5381 + len + 1;
    while ((c = *str++)) {
        if (c == '~') break;
        hash = ((hash << 5) + hash) ^ c;
    }
    return hash;
}

/*!
    
*/
static enum x_stat xstring_cstr_format__internal(XAllocator allocator, char *str, xhashtable(XSTRH_CHAR_PTR, XSTRH_VOID_PTR) *data_map, char **out) {
    char ch;
    enum x_stat return_status;
    bool is_parsing_placeholder;
    size_t index;
    size_t length;
    size_t counter;
    size_t auto_key_index;
    size_t placeholder_index;
    long format_number_value[2];
    void *data_map_value;
    char *result;
    char *placeholder;
    char *format_specifier;
    char *placeholder_value_key;
    char *format_specifier_param;

    auto_key_index = 0;
    placeholder = XTD_NULL;
    data_map_value = XTD_NULL;
    format_specifier = XTD_NULL;
    is_parsing_placeholder = FALSE;
    placeholder_value_key = XTD_NULL;
    length = xstring_cstr_length(str);
    if (!data_map) return XTD_NO_OP_ERR;
    return_status = XTD_KEY_NOT_FOUND_ERR;
    if (!out) return XTD_OUT_PARAM_NULL_ERR;
    result = (char *) allocator.memory_calloc(1, sizeof(char));
    if (!result) return XTD_ALLOC_ERR;

    for (counter = 0; counter < length; counter++) {
        ch = str[counter];
        if (ch != '{') {
            result = xstring_cstr_concat_char_free_old(allocator, result, str[counter]);
            continue;
        }
        
        placeholder_index = counter;
        while ((ch = str[++counter]) != '}') {
            placeholder = xstring_cstr_concat_char_free_old(allocator, placeholder, ch);
        }
        if (placeholder == XTD_NULL) {
            placeholder = xstring_cstr_concat_int_free_old(allocator, placeholder, auto_key_index++);
        } else if (placeholder != XTD_NULL && auto_key_index > 0) {
            return_status = XTD_KEY_SWITCH_FROM_AUTO_ERR;
            goto clean_up_and_return_placeholder_error;
        }
        if (xstring_cstr_contains(placeholder, ":") && 
            xstring_cstr_sub_string(allocator, placeholder, xstring_cstr_index_of(placeholder, ":")+1, &format_specifier) != XTD_OK) {
            return_status = XTD_PARSING_ERR;
            goto clean_up_and_return_placeholder_error;
        }

        if (format_specifier != XTD_NULL) {
            /* kinda using data_map_value for cache. which is not the intended */
            data_map_value = placeholder;
            if (xstring_cstr_sub_string_in_range(allocator, placeholder, 0, xstring_cstr_index_of(placeholder, ":"), &placeholder) != XTD_OK) {
                return_status = XTD_PARSING_ERR;
                goto clean_up_and_return_placeholder_error;
            }
            allocator.memory_free(data_map_value);
            data_map_value = XTD_NULL;
        }
        if (xhashtable_get_with_key(XSTRH_CHAR_PTR, XSTRH_VOID_PTR)(data_map, placeholder, &data_map_value, &placeholder_value_key) != XTD_OK || 
            xstring_cstr_sub_string(allocator, placeholder_value_key, xstring_cstr_index_of(placeholder_value_key, "~")+1, &placeholder_value_key) != XTD_OK) {
            goto clean_up_and_return_placeholder_error;
        }

        if (xstring_cstr_equals(placeholder_value_key, "int")) {
            data_map_value = (char *) xstring_cstr_int_value(allocator, (int) (size_t) data_map_value);
        } else if (xstring_cstr_equals(placeholder_value_key, "long")) {
            data_map_value = (char *) xstring_cstr_long_value(allocator, (long) data_map_value);
        } else if (xstring_cstr_equals(placeholder_value_key, "float")) {
            data_map_value = (char *) xstring_cstr_float_value(allocator, *((float *) data_map_value), 2);
        } else if (xstring_cstr_equals(placeholder_value_key, "double")) {
            data_map_value = (char *) xstring_cstr_double_value(allocator, *((double *) data_map_value), 2);
        } else if (xstring_cstr_equals(placeholder_value_key, "char")) {
            data_map_value = (char *) xstring_cstr_char_value(allocator, (char) (size_t) data_map_value);
        } else if (xstring_cstr_equals(placeholder_value_key, "pointer")) {
            data_map_value = (char *) xstring_cstr_pointer_value(allocator, (void *) data_map_value);
        }
        result = xstring_cstr_concat_cstr_free_old(allocator, result, (char *) data_map_value);
        if (format_specifier != XTD_NULL) {
            /* using ch for purpose not intended. (re use) */
            ch = format_specifier[0];
            if ((return_status = xstring_cstr_extract_from(allocator, format_specifier, 1, &format_specifier_param)) != XTD_OK) {
                goto clean_up_and_return_placeholder_error;
            }
            allocator.memory_free(format_specifier);
            return_status = XTD_UNKNOWN_FORMAT_VALUE_ERR;
            if (ch == '<' || ch == '>' || ch == '^') {
                if (xnumber_str2int_strtol(format_specifier_param, 10, (long *) &format_number_value) != XTD_OK) {
                    goto clean_up_and_return_placeholder_error;
                }
                format_number_value[0] -= xstring_cstr_length((char *) data_map_value);
                format_number_value[1] = format_number_value[0];
                format_number_value[0] = ch == '^' ? format_number_value[0] / 2 : format_number_value[0];
                for (index = 0; index < format_number_value[0]; index++) {
                    if (ch == '<' || ch == '^') {
                        result = xstring_cstr_concat_char_free_old(allocator, result, ' ');
                    }
                    if (ch == '>' || ch == '^') {
                        format_specifier = result;
                        xstring_cstr_insert_at(allocator, format_specifier, placeholder_index, " ", &result);
                        allocator.memory_free(format_specifier);
                    }
                }
                if (ch == '^') {
                    format_number_value[1] = format_number_value[1]%2;
                    for (index = 0; index < format_number_value[1]; index++) {
                        result = xstring_cstr_concat_char_free_old(allocator, result, ' ');
                    }
                }
            } else {
                return_status = XTD_UNKNOWN_FORMAT_CODE_ERR;
                goto clean_up_and_return_placeholder_error;
            }
            allocator.memory_free(format_specifier_param);
            format_specifier_param = XTD_NULL;
        }
        allocator.memory_free(placeholder);
        if (!xstring_cstr_equals(placeholder_value_key, "string") && 
            placeholder_value_key != XTD_NULL) {
            allocator.memory_free(data_map_value);
            allocator.memory_free(placeholder_value_key);
        }
        placeholder = XTD_NULL;
        data_map_value = XTD_NULL;
        format_specifier = XTD_NULL;
    }
    
    clean_up_and_return_result:
        #ifndef XTD_DONT_TRIM_MANAGED_CSTRING
            result = xstring_cstr_trim_memory_to_size(allocator, result);
        #endif
        *out = result;
        return XTD_OK;
    
    clean_up_and_return_placeholder_error:
        allocator.memory_free(result);
        allocator.memory_free(placeholder);
        if (!xstring_cstr_equals(placeholder_value_key, "string") && 
            placeholder_value_key != XTD_NULL) {
            allocator.memory_free(data_map_value);
            allocator.memory_free(placeholder_value_key);
        }
        if (format_specifier_param != XTD_NULL) {
            allocator.memory_free(format_specifier_param);
        }
        return return_status;
}

/*!
    
*/
#define xstring_cstr_format xstring_cstr_format__internal

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
