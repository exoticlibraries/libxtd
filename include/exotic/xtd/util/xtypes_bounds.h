
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <iamthecarisma@gmail.com>
    \date 12 July 2021
    \file xtypes_bounds.h
*/

#ifndef EXOTIC_XTYPED_BOUNDS_H
#define EXOTIC_XTYPED_BOUNDS_H

#ifdef __cplusplus
extern "C" {
#endif

/* TODO IMPLEMENTS THE LIMIT MANUALLY */
#include <limits.h>
#include <exotic/xtd/container/xstring.h>

#define XTD_INT_MAX INT_MAX
#define XTD_LONG_MAX LONG_MAX

#define XTD_INT_MIN INT_MIN
#define XTD_LONG_MIN LONG_MIN

/* char bound checks*/

/*!

*/
#define xbound_char_is_uppercase(ch) (ch >= 'A' && ch <= 'Z')

/*!

*/
#define xbound_char_is_lowercase(ch) (ch >= 'a' && ch <= 'z')

/*!

*/
#define xbound_char_is_alpha(ch) (xbound_char_is_lowercase(ch) || xbound_char_is_uppercase(ch))

/*!

*/
#define xbound_char_is_digit(ch) (ch >= '0' && ch <= '9')

/*!

*/
#define xbound_char_is_alphanum(ch) (xbound_char_is_alpha(ch) || xbound_char_is_digit(ch))

/*!

*/
#define xbound_char_is_white_space(ch) (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\v' || ch == '\f' || ch == '\r')

/*!

*/
#define xbound_char_is_cntrl(ch) ((ch >= 0 && ch <= 31) || ch == 127)

/*!

*/
#define xbound_char_is_printable(ch) (!xbound_char_is_cntrl(ch))

/*!

*/
#define xbound_char_is_graphical(ch) (ch >= 33 && ch <= 126)

/* cstr bound checks*/

/*!

*/
static bool xbound_cstr_is_uppercase(char *char_array) {
    size_t length = 0;
    if (char_array == NULL) { return FALSE; }
    for (; char_array[length] != '\0'; length++) {
        if (!xbound_char_is_uppercase(char_array[length])) return FALSE;
    }
    return length > 0;
}

/*!

*/
static bool xbound_cstr_is_lowercase(char *char_array) {
    size_t length = 0;
    if (char_array == NULL) { return FALSE; }
    for (; char_array[length] != '\0'; length++) {
        if (!xbound_char_is_lowercase(char_array[length])) return FALSE;
    }
    return length > 0;
}

/*!

*/
static bool xbound_cstr_is_mixed_case(char *char_array) {
    size_t length = 0;
    char has_lower = 0;
    char has_upper = 0;
    if (char_array == NULL) { return FALSE; }
    for (; char_array[length] != '\0'; length++) {
        has_lower = has_lower || xbound_char_is_lowercase(char_array[length]);
        has_upper = has_upper || xbound_char_is_uppercase(char_array[length]);
        if (has_lower && has_upper) return TRUE;
    }
    return FALSE;
}

/*!

*/
static bool xbound_cstr_is_sentence_case(char *char_array) {
    size_t length = 0;
    if (char_array == NULL) { return FALSE; }
    if (!xbound_char_is_uppercase(char_array[length])) { return FALSE; }
    for (; char_array[++length] != '\0';) {
        if (xbound_char_is_alpha(char_array[length]) && !xbound_char_is_lowercase(char_array[length])) return FALSE;
    }
    return TRUE;
}

/*!

*/
static bool xbound_cstr_is_title_case(char *char_array) {
    size_t length = 0;
    if (char_array == NULL) { return FALSE; }
    if (!xbound_char_is_uppercase(char_array[length])) { return FALSE; }
    for (; char_array[++length] != '\0';) {
        if (xbound_char_is_white_space(char_array[length-1]) && 
            (xbound_char_is_alpha(char_array[length]) && 
                !xbound_char_is_uppercase(char_array[length]))) return FALSE;
    }
    return TRUE;
}

/*!

*/
static bool xbound_cstr_is_alpha(char *char_array) {
    size_t length = 0;
    if (char_array == NULL) { return FALSE; }
    for (; char_array[length] != '\0'; length++) {
        if (!xbound_char_is_alpha(char_array[length])) return FALSE;
    }
    return length > 0;
}

/*!

*/
static bool xbound_cstr_is_digit(char *char_array) {
    size_t length = 0;
    if (char_array == NULL) { return FALSE; }
    for (; char_array[length] != '\0'; length++) {
        if (!xbound_char_is_digit(char_array[length])) return FALSE;
    }
    return length > 0;
}

/*!

*/
static bool xbound_cstr_is_alphanum(char *char_array) {
    size_t length = 0;
    if (char_array == NULL) { return FALSE; }
    for (; char_array[length] != '\0'; length++) {
        if (!xbound_char_is_alphanum(char_array[length])) return FALSE;
    }
    return length > 0;
}

/*!

*/
static bool xbound_cstr_is_white_space(char *char_array) {
    size_t length = 0;
    if (char_array == NULL) { return FALSE; }
    for (; char_array[length] != '\0'; length++) {
        if (!xbound_char_is_white_space(char_array[length])) return FALSE;
    }
    return length > 0;
}

/*!

*/
static bool xbound_cstr_is_cntrl(char *char_array) {
    size_t length = 0;
    if (char_array == NULL) { return FALSE; }
    for (; char_array[length] != '\0'; length++) {
        if (!xbound_char_is_cntrl(char_array[length])) return FALSE;
    }
    return length > 0;
}

/*!

*/
static bool xbound_cstr_is_printable(char *char_array) {
    size_t length = 0;
    if (char_array == NULL) { return FALSE; }
    for (; char_array[length] != '\0'; length++) {
        if (xbound_char_is_printable(char_array[length])) return TRUE;
    }
    return FALSE;
}

/*!

*/
static bool xbound_cstr_is_graphical(char *char_array) {
    size_t length = 0;
    if (char_array == NULL) { return FALSE; }
    for (; char_array[length] != '\0'; length++) {
        if (xbound_char_is_graphical(char_array[length])) return TRUE;
    }
    return FALSE;
}

/*!

*/
static bool xbound_cstr_is_decimal_with_seperator(char *char_array, char seperator) {
    size_t index = 0;
    bool found_e = FALSE;
    bool found_dot = FALSE;
    size_t length = xstring_cstr_length(char_array);

    if (length == 1 && !xbound_char_is_digit(char_array[index])) return FALSE;
    if (!xbound_char_is_digit(char_array[index]) && char_array[0] != '.' && 
        char_array[index] != '+' && char_array[index] != '-') return FALSE;
    for (; index < length; index++) {
        if (!xbound_char_is_digit(char_array[index]) && char_array[index] != 'e' &&
            char_array[index] != 'E' && char_array[index] != '.' && char_array[index] != '+' && 
            char_array[index] != '-' && (seperator == '\0' || char_array[index] != seperator)) {
                return FALSE;
        };
        if (char_array[index] == '+' || char_array[index] == '-') {
            if (char_array[index+1] == '+' || char_array[index+1] == '-') return FALSE;

        } else if (char_array[index] == '.' && seperator != '.') {
            if (found_e == TRUE || found_dot == TRUE) return FALSE;
            found_dot = TRUE;

        } else if (char_array[index] == 'e' || char_array[index] == 'E') {
            if (found_e || (index >= length-1) || !xbound_char_is_digit(char_array[index-1])) return FALSE;
            if (!xbound_char_is_digit(char_array[index+1]) && char_array[index+1] != '+' && 
                char_array[index+1] != '-') return FALSE;
            found_e = TRUE;

        } else if (seperator != '\0' && char_array[index] == seperator) {
            if (!xbound_char_is_digit(char_array[index-1]) || 
                !xbound_char_is_digit(char_array[index+1])) return FALSE;
        }
    }
    
    return TRUE;
}

/*!

*/
#define xbound_cstr_is_decimal(char_array) xbound_cstr_is_decimal_with_seperator(char_array, '\0')

/*!

*/
static bool xbound_cstr_is_hex_with_prefix(char *char_array, char *prefix) {
    size_t length = xstring_cstr_length(char_array);
    size_t index = (prefix == XTD_NULL ? 0 : xstring_cstr_length(prefix));

    if (prefix != XTD_NULL && !xstring_cstr_starts_with(char_array, prefix)) return FALSE;
    for (; index < length; index++) {
        if (!xbound_char_is_digit(char_array[index]) && !(char_array[index] >= 'a' && char_array[index] <= 'f') && 
            !(char_array[index] >= 'A' && char_array[index] <= 'F')) return FALSE;
    }

    return TRUE;
}

/*!

*/
#define xbound_cstr_is_hex(char_array) xbound_cstr_is_hex_with_prefix(char_array, XTD_NULL)

/*!

*/
static bool xbound_cstr_is_octal_with_prefix(char *char_array, char *prefix) {
    size_t length = xstring_cstr_length(char_array);
    size_t index = (prefix == XTD_NULL ? 0 : xstring_cstr_length(prefix));

    if (prefix != XTD_NULL && !xstring_cstr_starts_with(char_array, prefix)) return FALSE;
    for (; index < length; index++) {
        if (!(char_array[index] >= '0' && char_array[index] <= '7')) return FALSE;
    }

    return TRUE;
}

/*!

*/
#define xbound_cstr_is_octal(char_array) xbound_cstr_is_octal_with_prefix(char_array, XTD_NULL)

/*!

*/
static bool xbound_cstr_is_binary_with_prefix_and_seperator(char *char_array, char *prefix, char seperator) {
    size_t length = xstring_cstr_length(char_array);
    size_t index = (prefix == XTD_NULL ? 0 : xstring_cstr_length(prefix));

    if (prefix != XTD_NULL && !xstring_cstr_starts_with(char_array, prefix)) return FALSE;
    for (; index < length; index++) {
        if (char_array[index] != '0' && char_array[index] != '1' && 
            (seperator == '\0' || (char_array[index] != seperator))) return FALSE;
        if (seperator != '\0' && char_array[index] == seperator) {
            if (!xbound_char_is_digit(char_array[index-1]) || 
                !xbound_char_is_digit(char_array[index+1])) return FALSE;
        }
    }

    return TRUE;
}

/*!

*/
#define xbound_cstr_is_binary_with_prefix(char_array, prefix) xbound_cstr_is_binary_with_prefix_and_seperator(char_array, prefix, '\0')

/*!

*/
#define xbound_cstr_is_binary(char_array) xbound_cstr_is_binary_with_prefix(char_array, XTD_NULL)

/*xbound_cstr_is_number*/

/* TODO add int, long e.t.c. min max, bounds e.t.c*/

#ifdef __cplusplus
}
#endif

#endif
