

#ifndef LIBO_STRING_H
#define LIBO_STRING_H

#include <stddef.h>
#include "l_common.h"

typedef struct sstring {
    char *value  ;
    size_t size  ;
} sstring;

LIBO_API libo_stat       sstring_new(sstring **out, char* chars);
LIBO_API libo_stat       sstring_new_len(sstring **out, char* chars, size_t str_size);
LIBO_API libo_stat       sstring_concat(sstring *str, char* chars);
LIBO_API libo_stat       sstring_concat_char(sstring *str, char char_);
LIBO_API libo_stat       sstring_set_value(sstring *str, char* chars);
LIBO_API libo_stat       sstring_substring_to(sstring *str1, size_t begin, size_t end, sstring **out);
LIBO_API libo_stat       sstring_substring(sstring *str1, size_t begin, sstring **out);
LIBO_API libo_stat       sstring_reverse(sstring *str1, sstring **out);

LIBO_API size_t       l_utf8len(char *chars);
LIBO_API size_t       sstring_length(sstring *str);
LIBO_API size_t       sstring_index_of_from(sstring *str, char* chars, size_t from);
LIBO_API size_t       sstring_index_of(sstring *str, char* chars);
LIBO_API size_t       sstring_last_index_of_from(sstring *str, char* chars, size_t from);
LIBO_API size_t       sstring_last_index_of(sstring *str, char* chars);

LIBO_API sbool        sstring_il_empty(sstring *str);
LIBO_API sbool        sstring_equals(sstring *str1, sstring *str2);
LIBO_API sbool        sstring_equall_no_case(sstring *str1, sstring *str2);
LIBO_API sbool        sstring_startl_with_from(sstring *str, char* chars, size_t from);
LIBO_API sbool        sstring_startl_with(sstring *str, char* chars);
LIBO_API sbool        sstring_endl_with(sstring *str, char* chars);
LIBO_API sbool        sstring_contains(sstring *str1, char *chars);

LIBO_API void          sstring_lower(sstring *str);
LIBO_API void          sstring_upper(sstring *str);
LIBO_API void          sstring_trim(sstring *str);
LIBO_API void          sstring_sub_string(sstring *str, size_t from, size_t to, sstring *str1);
LIBO_API void          sstring_replace(sstring *str, char *in);
//LIBO_API void          sstring_split(sstring *str, char* chars, List **out);
LIBO_API void          sstring_format(sstring *str, char *in, ...);
LIBO_API void          sstring_destroy(sstring *str);

LIBO_API char*         sstring_charl_at(sstring *str, size_t index);
LIBO_API char*         sstring_get_value(sstring *str);

#endif
