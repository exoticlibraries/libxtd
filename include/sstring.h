

#ifndef S_STRING_H
#define S_STRING_H

#include <stddef.h>
#include "sct_common.h"

typedef struct sstring {
	char *value  ;
	size_t size  ;
} sstring;

SCT_API enum sct_stat		string_new(sstring **out, char* chars);
SCT_API enum sct_stat		string_new_len(sstring **out, char* chars, size_t str_size);

SCT_API size_t 				string_length(sstring *str);

SCT_API enum sct_stat		string_concat(sstring **out, char* chars);
SCT_API enum sct_stat		string_set_value(sstring **out, char* chars);
SCT_API enum sct_bool		string_is_empty(sstring *str);
SCT_API enum sct_bool		string_equals(sstring *str1, sstring *str2);
SCT_API enum sct_bool		string_equals_no_case(sstring *str1, sstring *str2);
SCT_API enum sct_bool		string_starts_with_from(sstring *str, char* chars, size_t from);
SCT_API enum sct_bool		string_starts_with(sstring *str, char* chars);
SCT_API enum sct_bool		string_ends_with(sstring *str, char* chars);
SCT_API enum sct_bool		string_index_of_from(sstring *str, char char_, size_t from);
SCT_API enum sct_bool		string_index_of(sstring *str, char char_);
SCT_API enum sct_bool		string_last_index_of_from(sstring *str, char char_, size_t from);
SCT_API enum sct_bool		string_last_index_of(sstring *str, char char_);
SCT_API enum sct_bool		string_contains(sstring *str1, char *chars);

SCT_API void 				string_lower(sstring **out);
SCT_API void 				string_upper(sstring **out);
SCT_API void 				string_trim(sstring **out);
SCT_API void 				string_sub_string(sstring *str, size_t from, size_t to, sstring **out);
SCT_API void 				string_replace(sstring **out, char *in);
//SCT_API void 				string_split(List **out, sstring *str, char* chars);
SCT_API void 				string_format(sstring **out, char *in, ...);
SCT_API void 				string_destroy(sstring *str);

SCT_API char				string_chat_at(sstring *str, size_t index, char** out);
SCT_API char*				string_get_value(sstring *str);

#endif
