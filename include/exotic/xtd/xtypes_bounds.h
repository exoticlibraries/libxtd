
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
#define xbounds_char_is_uppercase(ch) (ch >= 'A' && ch <= 'Z')

/*!

*/
#define xbounds_char_is_lowercase(ch) (ch >= 'a' && ch <= 'z')

/*!

*/
#define xbounds_char_is_alpha(ch) (xbounds_char_is_lowercase(ch) || xbounds_char_is_uppercase(ch))

/*!

*/
#define xbounds_char_is_digit(ch) (ch >= '0' && ch <= '9')

/*!

*/
#define xbounds_char_is_alphanum(ch) (xbounds_char_is_alpha(ch) || xbounds_char_is_digit(ch))

/*!

*/
#define xbounds_char_is_white_space(ch) (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\v' || ch == '\f' || ch == '\r')

/*!

*/
#define xbounds_char_is_cntrl(ch) ((ch >= 0 && ch <= 31) || ch == 127)

/*!

*/
#define xbounds_char_is_printable(ch) (!xbounds_char_is_cntrl(ch))

/*!

*/
#define xbounds_char_is_graphical(ch) (ch >= 33 && ch <= 126)


//TODO add the char bound for cstr (char array too)
// TODO add int, long e.t.c. min max, bounds e.t.c

#ifdef __cplusplus
}
#endif

#endif