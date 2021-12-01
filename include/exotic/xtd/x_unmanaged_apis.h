
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <iamthecarisma@gmail.com>
    \date 07 April 2020
    \file xconf.h
*/

#ifndef EXOTIC_UNMANAGED_APIS_H
#define EXOTIC_UNMANAGED_APIS_H

#ifdef __cplusplus
extern "C" {
#endif

/*

*/
#define array_add(ptr_array, element) 

/*

*/
#define array_add_at(ptr_array, index, element) (ptr_array[index] = element)

/*

*/
#define array_get(ptr_array, index) (ptr_array[index])

/*

*/
#define array_get_or(ptr_array, index, default)

#ifdef __cplusplus
}
#endif

#endif
