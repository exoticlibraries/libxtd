
/*P
	:copyright: 2019, Adewale Azeez
	:license: GNU Lesser General Public License v3.0 Copyright (c) 
	:author: Adewale Azeez <azeezadewale98@gmail.com>
	:date: 10 November 2019
	:filename: l_math.c
*/

#include "../include/l_math.h"

/*
	Get the minimum number between two size_t 
	number 
*/
LIBO_API size_t l_min(size_t num1, size_t num2) {
	return ((num1) < (num2) ? (num1) : (num2));
}

/*
	Get the maximum number between two size_t 
	number 
*/
LIBO_API size_t l_max(size_t num1, size_t num2) {
	return ((num1) > (num2) ? (num1) : (num2));
}