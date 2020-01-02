
/**P
	:copyright: 2019, Adewale Azeez
	:license: GNU Lesser General Public License v3.0 Copyright (c)
	:author: Adewale Azeez <azeezadewale98@gmail.com>
	:date: 10 November 2019
	:filename: lstring.h
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
LIBO_API size_t l_utf8len(char *chars)
{
    char *tmp_chars;
    size_t len ;

    tmp_chars = chars;
    len = 0;
    for (; *tmp_chars; ++tmp_chars) if ((*tmp_chars & 0xC0) != 0x80) ++len;
    tmp_chars = NULL;
    l_free(tmp_chars);
    return len;
}

/*

*/
LIBO_API l_stat lstring_new(lstring **out, char* chars) 
{
    return lstring_new_len(out, chars, strlen(chars));
}

/*

*/
LIBO_API l_stat lstring_new_len(lstring **out, char* chars, size_t str_size)
{
    lstring *str;
    int x ;

    str = (struct lstring*) malloc(sizeof(struct lstring));
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
    str->size = l_utf8len(str->value);

    *out = str;
    return LIBO_OK;
}

/*
 
 */
LIBO_API void lstring_destroy(lstring *str)
{
    free(str->value);
    str->value = NULL;
    free(str);
    str = NULL;
}

/*

*/
LIBO_API size_t lstring_length(lstring *str)
{
    return str->size;
}

/*

*/
LIBO_API l_stat lstring_concat(lstring *str, char* chars)
{
    char* concat_value;
    size_t str_size;
    
    str_size = strlen(chars) + strlen(str->value);
    concat_value = malloc(str_size+1);
    strcpy(concat_value, str->value);
    strcat(concat_value, chars);

    l_stat status = lstring_set_value(str, concat_value);
    l_free(concat_value);
    return status;
}

/*

*/
LIBO_API l_stat lstring_concat_char(lstring *str, char char_) 
{
    int len = strlen(str->value);
    str->value[len] = char_;
    str->value[len+1] = '\0';
    return LIBO_OK;
}

/*

*/
LIBO_API l_stat lstring_set_value(lstring *str, char* chars)
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
    str->size = l_utf8len(str->value);
    return LIBO_OK;
}

/*

*/
LIBO_API lbool lstring_il_empty(lstring *str)
{
    if (str->size == 0) {
        return STRUE;
    }
    return SFALSE;
}

/*

*/
LIBO_API lbool lstring_equals(lstring *str1, lstring *str2)
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
LIBO_API lbool lstring_equall_no_case(lstring *str1, lstring *str2)
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
LIBO_API lbool lstring_startl_with_from(lstring *str, char* chars, size_t from)
{
    int i, j;
    size_t str_len;
    size_t charl_len;

    if (str == NULL) {
        return SFALSE;
    }
    str_len = strlen(str->value);
    charl_len = strlen(chars);
    j = charl_len+from;
    if (charl_len > str_len) {
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
LIBO_API lbool lstring_startl_with(lstring *str, char* chars)
{
    return lstring_startl_with_from(str, chars, 0);
}

/*

*/
LIBO_API lbool lstring_endl_with(lstring *str, char* chars)
{
    return lstring_startl_with_from(str, chars, strlen(str->value) - strlen(chars));
}

/*
    Get the index within the character array the occurence of 
    the specified character if no occurence after start from 
    value -1 is returned. 

    The function work fine with utf8 encoded character sets.

    **Parameters**:	
		str : lstring*
            the pointer to the lstring struct
		char_ : char
            a character to find it index
		from : size_t
            the index to start the search from
	
	**return**:
		the index of the first occurence after the from index in 
        the characters array.
*/
LIBO_API size_t lstring_index_of_from(lstring *str, char* chars, size_t from)
{
    int i, j, k, l;
    size_t str_len;
    size_t charl_len;
    lstring *str1;

    if (str == NULL) {
        return -1;
    }
    if (from < 0) {
        from = 0;
    }
    str_len = strlen(str->value);
    charl_len = strlen(chars);
    if (charl_len > str_len-from) {
        return -1;
    } else if (charl_len == str_len-from) {
        if (lstring_new_len(&str1, chars, charl_len) != LIBO_OK) {
            return -1;
        }
        if (lstring_equals(str, str1) == STRUE) {
            lstring_destroy(str1);
            return 0;
        }
        lstring_destroy(str1);
        return -1;
    }
    for (i=0, l=-1; i < str_len; i++) {
        if ((str->value[i] & 0xC0) != 0x80) { ++l; } 
        if (l < from) { continue; } 
        if (str->value[i] == chars[0]) {
            if (charl_len == 1) return l;
            j = 0; k = i;
            while (chars[++j] == str->value[++k]) {}
            if (charl_len==j) return l-from;
        }
    }
    return -1;
}

/*
    Get the index within the character array the first occurence 
    of the specified character if no occurence -1 is returned.

    **Parameters**:	
		str : lstring*
            the pointer to the lstring struct
		chars : char*
            a character to find it index
	
	**return**:
		the index of the first occurence in the characters array.
*/
LIBO_API size_t lstring_index_of(lstring *str, char* chars)
{
    return lstring_index_of_from(str, chars, 0);
}

/*
    

*/
LIBO_API size_t lstring_last_index_of_from(lstring *str, char* chars, size_t from)
{
    int i, j, k, l, m, right_most;
    size_t str_len;
    size_t charl_len;
    lstring *str1;

    if (str == NULL) {
        return -1;
    }
    if (from < 0) {
        return -1;
    }
    str_len = strlen(str->value);
    charl_len = strlen(chars);
    right_most = str->size - from;
    if (charl_len == 0) {
        return from;
    }
    printf("$%i,%i,%i,%i\n", charl_len, str_len, from, right_most);
    if (charl_len > from) {
        return -1;
    } 
    for (i=right_most, l=-1, m=0; i > -1 ; --i,++m) {
        //printf("%c", str->value[i]);
        if ((str->value[i] & 0xC0) != 0x80) { ++l; }
        printf("%c,%c,%i,%i,%i\n", str->value[i],chars[charl_len-1],m,l,from);
        //if (l < from-m) { continue; } 
        if (str->value[i] == chars[charl_len-1]) {
            if (charl_len == 1) return from-l_utf8len(chars);
            j = charl_len-1; k = i;
            while (str->value[--k] == chars[--j]) {
                //printf("%c,%c\n", str->value[k], chars[j]);
            }
            printf("::%i,%i,%i,%i,%i,%i,%i,%i,%i\n",str->size,i,charl_len,l_utf8len(chars),from,j,k,l,m);
            if (j==-1) return str->size - l_utf8len(chars) - m;
        }
    }
    return -1;
}

/*

*/
LIBO_API size_t lstring_last_index_of(lstring *str, char* chars)
{
    return lstring_last_index_of_from(str, chars, strlen(str->value));
}

/*

*/
LIBO_API lbool lstring_contains(lstring *str1, char *chars)
{

}

/*

*/
LIBO_API l_stat lstring_substring_to(lstring *str1, size_t begin, size_t end, lstring **out)
{

}

/*

*/
LIBO_API l_stat lstring_substring(lstring *str1, size_t begin, lstring **out)
{

}

/*

*/
LIBO_API l_stat lstring_reverse(lstring *str1, lstring **out)
{

}

/*

*/

LIBO_API void lstring_lower(lstring *str)
{

}

/*

*/
LIBO_API void lstring_upper(lstring *str)
{

}

/*

*/
LIBO_API void lstring_trim(lstring *str)
{

}

/*

*/
LIBO_API void lstring_sub_string(lstring *str, size_t from, size_t to, lstring *str1)
{

}

/*

*/
LIBO_API void lstring_replace(lstring *str, char *in)
{

}

/*

*/
//LIBO_API void lstring_split(List *out, lstring *str, char* chars);

/*

*/
LIBO_API void lstring_format(lstring *str, char *in, ...)
{

}

/*
    //use for substring
*/
LIBO_API char* lstring_charl_at(lstring *str, size_t index)
{
    int i,j,l;
    size_t str_len;
    lstring* str1;
    char* value ;

    if (lstring_new_len(&str1, "", 0) != LIBO_OK) {
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
            lstring_concat_char(str1, str->value[i]); 
            for (++j; j < str_len; j++) {
                if ((str->value[j] & 0xC0) != 0x80) { break; }
                lstring_concat_char(str1, str->value[j]); 
            }
            goto return_label;
        }
    }
    return_label:
        value = malloc(strlen(str1->value));
        strcpy(value,str1->value);
        lstring_destroy(str1);
        return value;
}

/*

*/
LIBO_API char*  lstring_get_value(lstring *str)
{
    return str->value;
}

/*

*/