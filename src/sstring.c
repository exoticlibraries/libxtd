
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
SCT_API enum sct_stat string_new(sstring **out, char* chars) 
{
    string_new_len(out, chars, strlen(chars));
}

/*

*/
SCT_API enum sct_stat string_new_len(sstring **out, char* chars, size_t str_size)
{
    sstring *str;
    int x ;

    str = (struct sstring*) malloc(sizeof(struct sstring));
    if (!str) {
        return SCC_ERR_ALLOC;
    }
    str->value = (char*) malloc(str_size + 1);
    if (!str->value) {
        free((void*)str);
        return SCC_ERR_ALLOC;
    }

    for ( x = 0 ; x < str_size ; x++ ) {
        str->value[x] = chars[x] ;
	}
    str->size = str_size;

    *out = str;
}

/*
 
 */
SCT_API void string_destroy(sstring *str)
{
    str->size = 0;
    free(str->value);
    free(str);
}

/*

*/
SCT_API size_t string_length(sstring *str)
{
    return str->size;
}

/*

*/
SCT_API enum sct_stat string_concat(sstring **out, char* chars)
{
    
}

/*

*/
SCT_API enum sct_stat string_set_value(sstring **out, char* chars)
{

}

/*

*/
SCT_API enum sct_bool string_is_empty(sstring *str)
{

}

/*

*/
SCT_API enum sct_bool string_equals(sstring *str1, sstring *str2)
{

}

/*

*/
SCT_API enum sct_bool string_equals_no_case(sstring *str1, sstring *str2)
{

}

/*

*/
SCT_API enum sct_bool string_starts_with_from(sstring *str, char* chars, size_t from)
{

}

/*

*/
SCT_API enum sct_bool string_starts_with(sstring *str, char* chars)
{

}

/*

*/
SCT_API enum sct_bool string_ends_with(sstring *str, char* chars)
{

}

/*

*/
SCT_API enum sct_bool string_index_of_from(sstring *str, char char_, size_t from)
{

}

/*

*/
SCT_API enum sct_bool string_index_of(sstring *str, char char_)
{

}

/*

*/
SCT_API enum sct_bool string_last_index_of_from(sstring *str, char char_, size_t from)
{

}

/*

*/
SCT_API enum sct_bool string_last_index_of(sstring *str, char char_)
{

}

/*

*/
SCT_API enum sct_bool string_contains(sstring *str1, char *chars)
{

}

/*

*/

SCT_API void string_lower(sstring **out)
{

}

/*

*/
SCT_API void string_upper(sstring **out)
{

}

/*

*/
SCT_API void string_trim(sstring **out)
{

}

/*

*/
SCT_API void string_sub_string(sstring *str, size_t from, size_t to, sstring **out)
{

}

/*

*/
SCT_API void string_replace(sstring **out, char *in)
{

}

/*

*/
//SCT_API void string_split(List **out, sstring *str, char* chars);

/*

*/
SCT_API void string_format(sstring **out, char *in, ...)
{

}

/*

*/

SCT_API char  string_chat_at(sstring *str, size_t index, char** out)
{

}

/*

*/
SCT_API char*  string_get_value(sstring *str)
{
    return str->value;
}

/*

*/