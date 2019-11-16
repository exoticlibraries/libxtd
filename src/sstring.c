
/**P
	:copyright: 2019, Azeez Adewale
	:license: GNU Lesser General Public License v3.0 Copyright (c)
	:author: Azeez Adewale <azeezadewale98@gmail.com>
	:date: 10 November 2019
	:filename: sstring.h
**/

#include "../include/sstring.h"

/*
    Get the correct length of any character array including 
    characters encoded with utf8. The *strlen* in the `<string.h`> 
    gives the full length of char array including utf8 
    continuation characters.

    The correct length is claculated by only counting characters 
    that it top two bits is not set to 10 i.e characters less than 
    `0x80` or greater than `0xbf`, and ignoring the continuation 
    characters.

    A temporary char array is created for effective and quick loop 
    and to prevent destruction of the char array on returning from 
    the function. 

    **Parameters**:	
		chars : char*
            the character array to find it length
	
	**return**:
		the correct length of character arrays in any encoding
*/
S_API size_t s_utf8len(char *chars)
{
    char *tmp_chars;
    size_t len ;

    tmp_chars = chars;
    len = 0;
    for (; *tmp_chars; ++tmp_chars) if ((*tmp_chars & 0xC0) != 0x80) ++len;
    tmp_chars = NULL;
    s_free(tmp_chars);
    return len;
}

/*

*/
S_API s_stat sstring_new(sstring **out, char* chars) 
{
    return sstring_new_len(out, chars, strlen(chars));
}

/*

*/
S_API s_stat sstring_new_len(sstring **out, char* chars, size_t str_size)
{
    sstring *str;
    int x ;

    str = (struct sstring*) malloc(sizeof(struct sstring));
    if (!str) {
        return S_ERR_ALLOC;
    }
    str->value = (char*) malloc(str_size + 1);
    if (!str->value) {
        free((void*)str);
        return S_ERR_ALLOC;
    }

    for ( x = 0 ; x < str_size ; x++ ) {
        str->value[x] = chars[x] ;
    }
    str->value[str_size] = '\0' ;
    str->size = s_utf8len(str->value);

    *out = str;
    return S_OK;
}

/*
 
 */
S_API void sstring_destroy(sstring *str)
{
    free(str->value);
    str->value = NULL;
    free(str);
    str = NULL;
}

/*

*/
S_API size_t sstring_length(sstring *str)
{
    return str->size;
}

/*

*/
S_API s_stat sstring_concat(sstring *str, char* chars)
{
    char* concat_value;
    size_t str_size;
    
    str_size = strlen(chars) + strlen(str->value);
    concat_value = malloc(str_size+1);
    strcpy(concat_value, str->value);
    strcat(concat_value, chars);

    s_stat status = sstring_set_value(str, concat_value);
    s_free(concat_value);
    return status;
}

/*

*/
S_API s_stat sstring_set_value(sstring *str, char* chars)
{
    int x ;
    int str_size;

    str_size = strlen(chars);
    free(str->value);
    str->value = (char*) malloc(str_size + 1);
    if (!str->value) {
        return S_ERR_ALLOC;
    }

    for ( x = 0 ; x < str_size ; x++ ) {
        str->value[x] = chars[x] ;
	}
    str->value[str_size] = '\0' ;
    str->size = s_utf8len(str->value);
    return S_OK;
}

/*

*/
S_API sbool sstring_is_empty(sstring *str)
{
    if (str->size == 0) {
        return STRUE;
    }
    return SFALSE;
}

/*

*/
S_API sbool sstring_equals(sstring *str1, sstring *str2)
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
S_API sbool sstring_equals_no_case(sstring *str1, sstring *str2)
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
        if (((str1->value[i] >= 65) && (str1->value[i] <= 90) ? str1->value[i] + 32 : str1->value[i]) != 
        ((str2->value[i] >= 65) && (str2->value[i] <= 90) ? str2->value[i] + 32 : str2->value[i])) {
            return SFALSE;
        }
        i++;
    }
    return STRUE;
}

/*

*/
S_API sbool sstring_starts_with_from(sstring *str, char* chars, size_t from)
{
    int i, j;
    size_t str_len;
    size_t chars_len;

    if (str == NULL) {
        return SFALSE;
    }
    str_len = strlen(str->value);
    chars_len = strlen(chars);
    j = chars_len+from;
    if (chars_len > str_len) {
        return SFALSE;
    }
    for (i=from; i < j; i++) {
        if (str->value[i] != chars[i-from]) {
            return SFALSE;
        }
    }
    return STRUE;    
}

/*

*/
S_API sbool sstring_starts_with(sstring *str, char* chars)
{
    return sstring_starts_with_from(str, chars, 0);
}

/*

*/
S_API sbool sstring_ends_with(sstring *str, char* chars)
{
    return sstring_starts_with_from(str, chars, strlen(str->value) - strlen(chars));
}

/*
    Get the index within the character array the occurence of 
    the specified character if no occurence after start from 
    value -1 is returned. 

    The function work fine with utf8 encoded character sets.

    **Parameters**:	
		str : sstring*
            the pointer to the sstring struct
		char_ : char
            a character to find it index
		from : size_t
            the index to start the search from
	
	**return**:
		the index of the first occurence after the from index in 
        the characters array.
*/
S_API size_t sstring_index_of_from(sstring *str, char* chars, size_t from)
{
    int i, j, k, l;
    size_t str_len;
    size_t chars_len;
    sstring *str1;

    if (str == NULL) {
        return -1;
    }
    if (from < 0) {
        from = 0;
    }
    str_len = strlen(str->value);
    chars_len = strlen(chars);
    if (chars_len > str_len-from) {
        return -1;
    } else if (chars_len == str_len-from) {
        sstring_new_len(&str1, chars, chars_len);
        if (sstring_equals(str, str1) == STRUE) {
            sstring_destroy(str1);
            return 0;
        }
        sstring_destroy(str1);
        return -1;
    }
    for (i=0, l=-1; i < str_len; i++) {
        if ((str->value[i] & 0xC0) != 0x80) { ++l; } 
        if (l < from) { continue; } 
        if (str->value[i] == chars[0]) {
            if (chars_len == 1) return i;
            j = 0; k = i;
            while (chars[++j] == str->value[++k]) {}
            if (chars_len+from==j+from) return l-from;
        }
    }
    return -1;
}

/*
    Get the index within the character array the first occurence 
    of the specified character if no occurence -1 is returned.

    **Parameters**:	
		str : sstring*
            the pointer to the sstring struct
		chars : char*
            a character to find it index
	
	**return**:
		the index of the first occurence in the characters array.
*/
S_API size_t sstring_index_of(sstring *str, char* chars)
{
    return sstring_index_of_from(str, chars, 0);
}

/*
    

*/
S_API size_t sstring_last_index_of_from(sstring *str, char* chars, size_t from)
{
    int i, j, k, l, right_most;
    size_t str_len;
    size_t chars_len;
    sstring *str1;

    if (str == NULL) {
        return -1;
    }
    if (from < 0) {
        return -1;
    }
    str_len = strlen(str->value);
    chars_len = strlen(chars);
    right_most = str_len - chars_len;
    if (chars_len == 0) {
        return from;
    }
    if (from > right_most) {
        from = right_most;
    }
    if (chars_len > str_len-from) {
        return -1;
    } else if (chars_len == str_len-from) {
        sstring_new_len(&str1, chars, chars_len);
        if (sstring_equals(str, str1) == STRUE) {
            sstring_destroy(str1);
            return 0;
        }
        sstring_destroy(str1);
        return -1;
    }
    printf("'");
    for (i=str_len-1, l=-1; i > -1 ; i--) {
        printf("%c", str->value[i]);
    }
    printf("'\n");
    return -1;
}

/*

*/
S_API size_t sstring_last_index_of(sstring *str, char* chars)
{
    return sstring_last_index_of_from(str, chars, strlen(chars));
}

/*

*/
S_API sbool sstring_contains(sstring *str1, char *chars)
{

}

/*

*/

S_API void sstring_lower(sstring *str)
{

}

/*

*/
S_API void sstring_upper(sstring *str)
{

}

/*

*/
S_API void sstring_trim(sstring *str)
{

}

/*

*/
S_API void sstring_sub_string(sstring *str, size_t from, size_t to, sstring *str1)
{

}

/*

*/
S_API void sstring_replace(sstring *str, char *in)
{

}

/*

*/
//S_API void sstring_split(List *out, sstring *str, char* chars);

/*

*/
S_API void sstring_format(sstring *str, char *in, ...)
{

}

/*

*/

S_API char  sstring_chat_at(sstring *str, size_t index, char** out)
{

}

/*

*/
S_API char*  sstring_get_value(sstring *str)
{
    return str->value;
}

/*

*/