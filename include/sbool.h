
/*P
	:copyright: 2019, Azeez Adewale
	:license: GNU Lesser General Public License v3.0 Copyright (c) 
	:author: Azeez Adewale <azeezadewale98@gmail.com>
	:date: 11 November 2019
	:filename: sbool.h
*/


#ifndef S_BOOL_H
#define S_BOOL_H

#ifndef FALSE
#define FALSE (0)
#endif
#ifndef TRUE
#define TRUE  (!FALSE)
#endif

#define SFALSE FALSE
#define STRUE  TRUE

typedef int sbool;

#endif