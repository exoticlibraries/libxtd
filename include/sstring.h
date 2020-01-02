

#ifndef S_STRING_H
#define S_STRING_H

#include <stddef.h>
#include "s_common.h"

typedef struct sstring {
    char *value  ;
    size_t size  ;
} sstring;

S_API libo_stat       sstring_new(sstring **out, char* chars);
S_API libo_stat       sstring_new_len(sstring **out, char* chars, size_t str_size);
S_API libo_stat       sstring_concat(sstring *str, char* chars);
S_API libo_stat       sstring_concat_char(sstring *str, char char_);
S_API libo_stat       sstring_set_value(sstring *str, char* chars);
S_API libo_stat       sstring_substring_to(sstring *str1, size_t begin, size_t end, sstring **out);
S_API libo_stat       sstring_substring(sstring *str1, size_t begin, sstring **out);
S_API libo_stat       sstring_reverse(sstring *str1, sstring **out);

S_API size_t       s_utf8len(char *chars);
S_API size_t       sstring_length(sstring *str);
S_API size_t       sstring_index_of_from(sstring *str, char* chars, size_t from);
S_API size_t       sstring_index_of(sstring *str, char* chars);
S_API size_t       sstring_last_index_of_from(sstring *str, char* chars, size_t from);
S_API size_t       sstring_last_index_of(sstring *str, char* chars);

S_API sbool        sstring_is_empty(sstring *str);
S_API sbool        sstring_equals(sstring *str1, sstring *str2);
S_API sbool        sstring_equals_no_case(sstring *str1, sstring *str2);
S_API sbool        sstring_starts_with_from(sstring *str, char* chars, size_t from);
S_API sbool        sstring_starts_with(sstring *str, char* chars);
S_API sbool        sstring_ends_with(sstring *str, char* chars);
S_API sbool        sstring_contains(sstring *str1, char *chars);

S_API void          sstring_lower(sstring *str);
S_API void          sstring_upper(sstring *str);
S_API void          sstring_trim(sstring *str);
S_API void          sstring_sub_string(sstring *str, size_t from, size_t to, sstring *str1);
S_API void          sstring_replace(sstring *str, char *in);
//S_API void          sstring_split(sstring *str, char* chars, List **out);
S_API void          sstring_format(sstring *str, char *in, ...);
S_API void          sstring_destroy(sstring *str);

S_API char*         sstring_chars_at(sstring *str, size_t index);
S_API char*         sstring_get_value(sstring *str);

#endif
