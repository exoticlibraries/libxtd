
/*P
	:copyright: 2019, Azeez Adewale
	:license: GNU Lesser General Public License v3.0 Copyright (c) 
	:author: Azeez Adewale <azeezadewale98@gmail.com>
	:date: 10 November 2019
	:filename: s_math.c
*/

#include "../include/s_math.h"

/*
	Get the minimum number between two size_t 
	number 
*/
S_API size_t s_min(size_t num1, size_t num2) {
	return ((num1) < (num2) ? (num1) : (num2));
}

/*
	Get the maximum number between two size_t 
	number 
*/
S_API size_t s_max(size_t num1, size_t num2) {
	return ((num1) > (num2) ? (num1) : (num2));
}