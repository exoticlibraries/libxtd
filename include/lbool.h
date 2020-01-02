
/*P
	:copyright: 2019, Adewale Azeez
	:license: GNU Lesser General Public License v3.0 Copyright (c) 
	:author: Adewale Azeez <azeezadewale98@gmail.com>
	:date: 11 November 2019
	:filename: lbool.h
*/


#ifndef LIBO_BOOL_H
#define LIBO_BOOL_H

#ifndef FALSE
#define FALSE (0)
#endif
#ifndef TRUE
#define TRUE  (!FALSE)
#endif

#define SFALSE FALSE
#define STRUE  TRUE

typedef int lbool;

#endif