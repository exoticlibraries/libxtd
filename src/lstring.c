
/**P
	:copyright: 2019, Adewale Azeez
	:license: GNU Lesser General Public License v3.0 Copyright (c)
	:author: Adewale Azeez <azeezadewale98@gmail.com>
	:date: 10 November 2019
	:filename: sstring.h
**/

#include "../include/lstring.h"

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
LIBO_API size_t s_utf8len(char *chars)
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
LIBO_API libo_stat sstring_new(sstring **out, char* chars) 
{
    return sstring_new_len(out, chars, strlen(chars));
}

/*

*/
LIBO_API libo_stat sstring_new_len(sstring **out, char* chars, size_t str_size)
{
    sstring *str;
    int x ;

    str = (struct sstring*) malloc(sizeof(struct sstring));
    if (!str) {
        return LIBO_ERR_ALLOC;
    }
    str->value = (char*) malloc(str_size + 1);
    if (!str->value) {
        free((void*)str);
        return LIBO_ERR_ALLOC;
    }

    for ( x = 0 ; x < str_size ; x++ ) {
        str->value[x] = chars[x] ;
    }
    str->value[str_size] = '\0' ;
    str->size = s_utf8len(str->value);

    *out = str;
    return LIBO_OK;
}

/*
 
 */
LIBO_API void sstring_destroy(sstring *str)
{
    free(str->value);
    str->value = NULL;
    free(str);
    str = NULL;
}

/*

*/
LIBO_API size_t sstring_length(sstring *str)
{
    return str->size;
}

/*

*/
LIBO_API libo_stat sstring_concat(sstring *str, char* chars)
{
    char* concat_value;
    size_t str_size;
    
    str_size = strlen(chars) + strlen(str->value);
    concat_value = malloc(str_size+1);
    strcpy(concat_value, str->value);
    strcat(concat_value, chars);

    libo_stat status = sstring_set_value(str, concat_value);
    s_free(concat_value);
    return status;
}

/*

*/
LIBO_API libo_stat sstring_concat_char(sstring *str, char char_) 
{
    int len = strlen(str->value);
    str->value[len] = char_;
    str->value[len+1] = '\0';
    return LIBO_OK;
}

/*

*/
LIBO_API libo_stat sstring_set_value(sstring *str, char* chars)
{
    int x ;
    int str_size;

    str_size = strlen(chars);
    free(str->value);
    str->value = (char*) malloc(str_size + 1);
    if (!str->value) {
        return LIBO_ERR_ALLOC;
    }

    for ( x = 0 ; x < str_size ; x++ ) {
        str->value[x] = chars[x] ;
	}
    str->value[str_size] = '\0' ;
    str->size = s_utf8len(str->value);
    return LIBO_OK;
}

/*

*/
LIBO_API sbool sstring_is_empty(sstring *str)
{
    if (str->size == 0) {
        return STRUE;
    }
    return SFALSE;
}

/*

*/
LIBO_API sbool sstring_equals(sstring *str1, sstring *str2)
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
LIBO_API sbool sstring_equals_no_case(sstring *str1, sstring *str2)
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
LIBO_API sbool sstring_starts_with_from(sstring *str, char* chars, size_t from)
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
LIBO_API sbool sstring_starts_with(sstring *str, char* chars)
{
    return sstring_starts_with_from(str, chars, 0);
}

/*

*/
LIBO_API sbool sstring_ends_with(sstring *str, char* chars)
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
LIBO_API size_t sstring_index_of_from(sstring *str, char* chars, size_t from)
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
        if (sstring_new_len(&str1, chars, chars_len) != LIBO_OK) {
            return -1;
        }
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
            if (chars_len == 1) return l;
            j = 0; k = i;
            while (chars[++j] == str->value[++k]) {}
            if (chars_len==j) return l-from;
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
LIBO_API size_t sstring_index_of(sstring *str, char* chars)
{
    return sstring_index_of_from(str, chars, 0);
}

/*
    

*/
LIBO_API size_t sstring_last_index_of_from(sstring *str, char* chars, size_t from)
{
    int i, j, k, l, m, right_most;
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
    right_most = str->size - from;
    if (chars_len == 0) {
        return from;
    }
    printf("$%i,%i,%i,%i\n", chars_len, str_len, from, right_most);
    if (chars_len > from) {
        return -1;
    } 
    for (i=right_most, l=-1, m=0; i > -1 ; --i,++m) {
        //printf("%c", str->value[i]);
        if ((str->value[i] & 0xC0) != 0x80) { ++l; }
        printf("%c,%c,%i,%i,%i\n", str->value[i],chars[chars_len-1],m,l,from);
        //if (l < from-m) { continue; } 
        if (str->value[i] == chars[chars_len-1]) {
            if (chars_len == 1) return from-s_utf8len(chars);
            j = chars_len-1; k = i;
            while (str->value[--k] == chars[--j]) {
                //printf("%c,%c\n", str->value[k], chars[j]);
            }
            printf("::%i,%i,%i,%i,%i,%i,%i,%i,%i\n",str->size,i,chars_len,s_utf8len(chars),from,j,k,l,m);
            if (j==-1) return str->size - s_utf8len(chars) - m;
        }
    }
    return -1;
}

/*

*/
LIBO_API size_t sstring_last_index_of(sstring *str, char* chars)
{
    return sstring_last_index_of_from(str, chars, strlen(str->value));
}

/*

*/
LIBO_API sbool sstring_contains(sstring *str1, char *chars)
{

}

/*

*/
LIBO_API libo_stat sstring_substring_to(sstring *str1, size_t begin, size_t end, sstring **out)
{

}

/*

*/
LIBO_API libo_stat sstring_substring(sstring *str1, size_t begin, sstring **out)
{

}

/*

*/
LIBO_API libo_stat sstring_reverse(sstring *str1, sstring **out)
{

}

/*

*/

LIBO_API void sstring_lower(sstring *str)
{

}

/*

*/
LIBO_API void sstring_upper(sstring *str)
{

}

/*

*/
LIBO_API void sstring_trim(sstring *str)
{

}

/*

*/
LIBO_API void sstring_sub_string(sstring *str, size_t from, size_t to, sstring *str1)
{

}

/*

*/
LIBO_API void sstring_replace(sstring *str, char *in)
{

}

/*

*/
//LIBO_API void sstring_split(List *out, sstring *str, char* chars);

/*

*/
LIBO_API void sstring_format(sstring *str, char *in, ...)
{

}

/*
    //use for substring
*/
LIBO_API char* sstring_chars_at(sstring *str, size_t index)
{
    int i,j,l;
    size_t str_len;
    sstring* str1;
    char* value ;

    if (sstring_new_len(&str1, "", 0) != LIBO_OK) {
        return "";
    }
    if (str == NULL) {
        goto return_label;
    }
    str_len = strlen(str->value);
    if (index >= str_len) {
        goto return_label;
    }
    for (i=0, l=-1; i < str_len; i++) {
        if ((str->value[i] & 0xC0) != 0x80) { ++l; }
        if (l==index) {
            j = i;
            sstring_concat_char(str1, str->value[i]); 
            for (++j; j < str_len; j++) {
                if ((str->value[j] & 0xC0) != 0x80) { break; }
                sstring_concat_char(str1, str->value[j]); 
            }
            goto return_label;
        }
    }
    return_label:
        value = malloc(strlen(str1->value));
        strcpy(value,str1->value);
        sstring_destroy(str1);
        return value;
}

/*

*/
LIBO_API char*  sstring_get_value(sstring *str)
{
    return str->value;
}

/*

*/