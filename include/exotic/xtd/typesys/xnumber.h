
/**
    \copyright MIT License Copyright (c) 2023, Adewale Azeez 
    \author Adewale Azeez <iamthecarisma@gmail.com>
    \date 22 January 2023
    \file xnumber.h
*/

#ifndef EXOTIC_XNUMBER_H
#define EXOTIC_XNUMBER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <errno.h>
#include <stdlib.h>
#include "../xcommon.h"
#include "../container/xstring.h"

/*!
    
*/
static enum x_stat xnumber_str2int_strtol(char *cstr, int base, long *out) {
    char *end;
    long result;

    errno = 0;
    if (!cstr || !out || cstr[0] == '\0' || xbound_char_is_white_space(cstr[0])) {
        return XTD_INCONVERTIBLE_ERR;
    }
    result = strtol(cstr, &end, base);
    if (result > XTD_INT_MAX || (errno == ERANGE && result == XTD_LONG_MAX)) {
        return XTD_NUMBER_TYPE_OVERFLOW_ERR;
    }
    if (result < XTD_INT_MIN || (errno == ERANGE && result == XTD_LONG_MIN)) {
        return XTD_NUMBER_TYPE_UNDERFLOW_ERR;
    }
    if (*end != '\0') { return XTD_INCONVERTIBLE_ERR; }

    *out = result;
    return XTD_OK;
}

/*!
    
*/
static enum x_stat xnumber_str2int() {
    return XTD_NOT_IMPLEMENTED_ERR;
}


#ifdef __cplusplus
}
#endif

#endif
