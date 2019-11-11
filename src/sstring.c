
/**P
	:copyright: 2019, Azeez Adewale
	:license: GNU Lesser General Public License v3.0 Copyright (c)
	:author: Azeez Adewale <azeezadewale98@gmail.com>
	:date: 10 November 2019
	:filename: string.h
**/

#include "../include/sstring.h"

/*

*/
SCT_API enum sct_stat sstring_new(sstring **out, char* chars) 
{
    return sstring_new_len(out, chars, strlen(chars));
}

/*

*/
SCT_API enum sct_stat sstring_new_len(sstring **out, char* chars, size_t str_size)
{
    sstring *str;
    int x ;

    str = (struct sstring*) malloc(sizeof(struct sstring));
    if (!str) {
        return SCT_ERR_ALLOC;
    }
    str->value = (char*) malloc(str_size + 1);
    if (!str->value) {
        free((void*)str);
        return SCT_ERR_ALLOC;
    }

    for ( x = 0 ; x < str_size ; x++ ) {
        str->value[x] = chars[x] ;
	}
    str->value[str_size] = '\0' ;
    str->size = str_size;

    *out = str;
    return SCT_OK;
}

/*
 
 */
SCT_API void sstring_destroy(sstring *str)
{
    free(str->value);
    str->value = NULL;
    free(str);
    str = NULL;
}

/*

*/
SCT_API size_t sstring_length(sstring *str)
{
    return str->size;
}

/*

*/
SCT_API enum sct_stat sstring_concat(sstring *str, char* chars)
{
    char* concat_value;
    size_t str_size;
    
    str_size = strlen(chars) + strlen(str->value);
    concat_value = malloc(str_size+1);
    strcpy(concat_value, str->value);
    strcat(concat_value, chars);

    enum sct_stat status = sstring_set_value(str, concat_value);
    sct_free(concat_value);
    return status;
}

/*

*/
SCT_API enum sct_stat sstring_set_value(sstring *str, char* chars)
{
    int x ;
    int str_size;

    str_size = strlen(chars);
    free(str->value);
    str->value = (char*) malloc(str_size + 1);
    if (!str->value) {
        return SCT_ERR_ALLOC;
    }

    for ( x = 0 ; x < str_size ; x++ ) {
        str->value[x] = chars[x] ;
	}
    str->value[str_size] = '\0' ;
    str->size = str_size;
    return SCT_OK;
}

/*

*/
SCT_API enum sbool sstring_is_empty(sstring *str)
{
    if (str->size == 0) {
        return STRUE;
    }
    return SFALSE;
}

/*

*/
SCT_API enum sbool sstring_equals(sstring *str1, sstring *str2)
{
    int i;

    i = 0;
    if (str1 == NULL || str2 == NULL) {
        return SFALSE;
    }
    if (str1->size != str2->size) {
        return SFALSE;
    }
    while (str1->value[i] != '\0') {
        if (str1->value[i] != str2->value[i]) {
            return SFALSE;
        }
        i++;
    }
    return STRUE;
}

/*

*/
SCT_API enum sbool sstring_equals_no_case(sstring *str1, sstring *str2)
{
    int i;

    i = 0;
    if (str1 == NULL || str2 == NULL) {
        return SFALSE;
    }
    if (str1->size != str2->size) {
        return SFALSE;
    }
    while (str1->value[i] != '\0') {
        if (str1->value[i] != str2->value[i]) {
            return SFALSE;
        }
        i++;
    }
    return STRUE;
}

/*

*/
SCT_API enum sbool sstring_starts_with_from(sstring *str, char* chars, size_t from)
{

}

/*

*/
SCT_API enum sbool sstring_starts_with(sstring *str, char* chars)
{

}

/*

*/
SCT_API enum sbool sstring_ends_with(sstring *str, char* chars)
{

}

/*

*/
SCT_API enum sbool sstring_index_of_from(sstring *str, char char_, size_t from)
{

}

/*

*/
SCT_API enum sbool sstring_index_of(sstring *str, char char_)
{

}

/*

*/
SCT_API enum sbool sstring_last_index_of_from(sstring *str, char char_, size_t from)
{

}

/*

*/
SCT_API enum sbool sstring_last_index_of(sstring *str, char char_)
{

}

/*

*/
SCT_API enum sbool sstring_contains(sstring *str1, char *chars)
{

}

/*

*/

SCT_API void sstring_lower(sstring *str)
{

}

/*

*/
SCT_API void sstring_upper(sstring *str)
{

}

/*

*/
SCT_API void sstring_trim(sstring *str)
{

}

/*

*/
SCT_API void sstring_sub_string(sstring *str, size_t from, size_t to, sstring *str1)
{

}

/*

*/
SCT_API void sstring_replace(sstring *str, char *in)
{

}

/*

*/
//SCT_API void sstring_split(List *out, sstring *str, char* chars);

/*

*/
SCT_API void sstring_format(sstring *str, char *in, ...)
{

}

/*

*/

SCT_API char  sstring_chat_at(sstring *str, size_t index, char** out)
{

}

/*

*/
SCT_API char*  sstring_get_value(sstring *str)
{
    return str->value;
}

/*

*/