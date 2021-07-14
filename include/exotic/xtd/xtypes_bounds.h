
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 12 July 2021
    \file xtypes_bounds.h
*/

#ifndef EXOTIC_XTYPED_BOUNDS_H
#define EXOTIC_XTYPED_BOUNDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "xcommon.h"

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
    return TRUE;
}

/*!

*/
static bool xbound_cstr_is_lowercase(char *char_array) {
    size_t length = 0;
    if (char_array == NULL) { return FALSE; }
    for (; char_array[length] != '\0'; length++) {
        if (!xbound_char_is_lowercase(char_array[length])) return FALSE;
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
    return TRUE;
}

/*!

*/
static bool xbound_cstr_is_digit(char *char_array) {
    size_t length = 0;
    if (char_array == NULL) { return FALSE; }
    for (; char_array[length] != '\0'; length++) {
        if (!xbound_char_is_digit(char_array[length])) return FALSE;
    }
    return TRUE;
}

/*!

*/
static bool xbound_cstr_is_alphanum(char *char_array) {
    size_t length = 0;
    if (char_array == NULL) { return FALSE; }
    for (; char_array[length] != '\0'; length++) {
        if (!xbound_char_is_alphanum(char_array[length])) return FALSE;
    }
    return TRUE;
}

/*!

*/
static bool xbound_cstr_is_white_space(char *char_array) {
    size_t length = 0;
    if (char_array == NULL) { return FALSE; }
    for (; char_array[length] != '\0'; length++) {
        if (!xbound_char_is_white_space(char_array[length])) return FALSE;
    }
    return TRUE;
}

/*!

*/
static bool xbound_cstr_is_cntrl(char *char_array) {
    size_t length = 0;
    if (char_array == NULL) { return FALSE; }
    for (; char_array[length] != '\0'; length++) {
        if (!xbound_char_is_cntrl(char_array[length])) return FALSE;
    }
    return TRUE;
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
static bool xbound_cstr_is_mixed_case(char *char_array) {
    size_t length = 0;
    char has_lower = 0;
    char has_upper = 0;
    if (char_array == NULL) { return FALSE; }
    for (; char_array[length] != '\0'; length++) {
        has_lower = has_lower || xbound_char_is_lowercase(char_array[length]);
        has_upper = has_upper || xbound_char_is_uppercase(char_array[length]);
        if (has_lower && has_upper) break;
    }
    return (has_lower && has_upper);
}

/*!

*/
static bool xbound_cstr_is_sentence_case(char *char_array) {
    size_t length = 0;
    if (char_array == NULL) { return FALSE; }
    return xbound_char_is_uppercase(char_array[0]);
}

/*!

*/
static bool xbound_cstr_is_number(char *char_array) {
    size_t length = 0;
    if (char_array == NULL) { return FALSE; }
    for (; char_array[length] != '\0'; length++) {
        if (!xbound_char_is_digit(char_array[length])) {
            return FALSE;
        };
    }
    return TRUE;
}

// TODO add int, long e.t.c. min max, bounds e.t.c

#ifdef __cplusplus
}
#endif

#endif