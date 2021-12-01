
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <iamthecarisma@gmail.com>
    \date 21 June 2021
    \file xmath.h
*/

#ifndef EXOTIC_XMATH_H
#define EXOTIC_XMATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "xcommon.h"

/*!

*/
#define XMATH_MAX(num1, num2) (((num1) >= (num2)) ? (num1) : (num2))
#define XMATH_MIN(num1, num2) (((num1) <= (num2)) ? (num1) : (num2))

/*
    \see http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2Float
*/
static __XTD_INLINE__ size_t xmath_round_power_of_two(size_t num)
{
    if (num >= XTD_MATH_MAX_POW_TWO) {
        return XTD_MATH_MAX_POW_TWO;
    }
    if (num == 0) {
        return 2;
    }
    num--;
    num |= num >> 1;
    num |= num >> 2;
    num |= num >> 4;
    num |= num >> 8;
    num |= num >> 16;
    num++;

    return num;
}


#ifdef __cplusplus
}
#endif

#endif
