
/*P
	:copyright: 2019, Azeez Adewale
	:license: GNU Lesser General Public License v3.0 Copyright (c) 
	:author: Azeez Adewale <azeezadewale98@gmail.com>
	:date: 11 November 2019
	:filename: sbool.h
*/


#ifndef S_BOOL_H
#define S_BOOL_H

#define FALSE (0)
#define TRUE  (!FALSE)

/*

*/
typedef enum sbool {

	STRUE                   = 1,
	SFALSE	                = 0

} sbool;

#endif