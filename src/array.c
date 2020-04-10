
/**
    \copyright GNU General Public License v3.0 Copyright (c) 2019, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 10 April 2020
    \file array.c
*/

#include <libopen/array.h>

static enum libopen_stat expand_capacity(Array *array);

/**

*/
enum libopen_stat array_new(Array **out)
{
    ArrayConfig c;
    array_config_init(&c);
    return array_new_config(&c, out);
}

