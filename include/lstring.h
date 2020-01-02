

#ifndef LIBO_STRING_H
#define LIBO_STRING_H

#include <stddef.h>
#include "l_common.h"

typedef struct lstring {
    char *value  ;
    size_t size  ;
} lstring;

LIBO_API libo_stat       lstring_new(lstring **out, char* chars);
LIBO_API libo_stat       lstring_new_len(lstring **out, char* chars, size_t str_size);
LIBO_API libo_stat       lstring_concat(lstring *str, char* chars);
LIBO_API libo_stat       lstring_concat_char(lstring *str, char char_);
LIBO_API libo_stat       lstring_set_value(lstring *str, char* chars);
LIBO_API libo_stat       lstring_substring_to(lstring *str1, size_t begin, size_t end, lstring **out);
LIBO_API libo_stat       lstring_substring(lstring *str1, size_t begin, lstring **out);
LIBO_API libo_stat       lstring_reverse(lstring *str1, lstring **out);

LIBO_API size_t       l_utf8len(char *chars);
LIBO_API size_t       lstring_length(lstring *str);
LIBO_API size_t       lstring_index_of_from(lstring *str, char* chars, size_t from);
LIBO_API size_t       lstring_index_of(lstring *str, char* chars);
LIBO_API size_t       lstring_last_index_of_from(lstring *str, char* chars, size_t from);
LIBO_API size_t       lstring_last_index_of(lstring *str, char* chars);

LIBO_API lbool        lstring_is_empty(lstring *str);
LIBO_API lbool        lstring_equals(lstring *str1, lstring *str2);
LIBO_API lbool        lstring_equals_no_case(lstring *str1, lstring *str2);
LIBO_API lbool        lstring_starts_with_from(lstring *str, char* chars, size_t from);
LIBO_API lbool        lstring_starts_with(lstring *str, char* chars);
LIBO_API lbool        lstring_ends_with(lstring *str, char* chars);
LIBO_API lbool        lstring_contains(lstring *str1, char *chars);

LIBO_API void          lstring_lower(lstring *str);
LIBO_API void          lstring_upper(lstring *str);
LIBO_API void          lstring_trim(lstring *str);
LIBO_API void          lstring_sub_string(lstring *str, size_t from, size_t to, lstring *str1);
LIBO_API void          lstring_replace(lstring *str, char *in);
//LIBO_API void          lstring_split(lstring *str, char* chars, List **out);
LIBO_API void          lstring_format(lstring *str, char *in, ...);
LIBO_API void          lstring_destroy(lstring *str);

LIBO_API char*         lstring_chars_at(lstring *str, size_t index);
LIBO_API char*         lstring_get_value(lstring *str);

#endif
