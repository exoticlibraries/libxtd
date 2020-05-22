
/**
    \copyright GNU General Public License v3.0 Copyright (c) 2019, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 10 April 2020
    \file array.c
*/

#include <exotic/xarray.h>

static enum xtypes_stat expand_capacity(XArray *array);

/**

*/
enum xtypes_stat xarray_new(XArray **out)
{
    XArrayConfig c;
    /*xarray_config_init(&c);*/
    /*return xarray_new_config(&c, out);*/
    return X_ERR_FAIL;
}

