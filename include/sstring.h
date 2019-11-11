

#ifndef S_STRING_H
#define S_STRING_H

#include <stddef.h>
#include "sct_common.h"

typedef struct sstring {
	char *value  ;
	size_t size  ;
} sstring;

SCT_API enum sct_stat		sstring_new(sstring **out, char* chars);
SCT_API enum sct_stat		sstring_new_len(sstring **out, char* chars, size_t str_size);

SCT_API size_t 				sstring_length(sstring *str);

SCT_API enum sct_stat		sstring_concat(sstring *str, char* chars);
SCT_API enum sct_stat		sstring_set_value(sstring *str, char* chars);
SCT_API enum sct_bool		sstring_is_empty(sstring *str);
SCT_API enum sct_bool		sstring_equals(sstring *str1, sstring *str2);
SCT_API enum sct_bool		sstring_equals_no_case(sstring *str1, sstring *str2);
SCT_API enum sct_bool		sstring_starts_with_from(sstring *str, char* chars, size_t from);
SCT_API enum sct_bool		sstring_starts_with(sstring *str, char* chars);
SCT_API enum sct_bool		sstring_ends_with(sstring *str, char* chars);
SCT_API enum sct_bool		sstring_index_of_from(sstring *str, char char_, size_t from);
SCT_API enum sct_bool		sstring_index_of(sstring *str, char char_);
SCT_API enum sct_bool		sstring_last_index_of_from(sstring *str, char char_, size_t from);
SCT_API enum sct_bool		sstring_last_index_of(sstring *str, char char_);
SCT_API enum sct_bool		sstring_contains(sstring *str1, char *chars);

SCT_API void 				sstring_lower(sstring *str);
SCT_API void 				sstring_upper(sstring *str);
SCT_API void 				sstring_trim(sstring *str);
SCT_API void 				sstring_sub_string(sstring *str, size_t from, size_t to, sstring *str1);
SCT_API void 				sstring_replace(sstring *str, char *in);
//SCT_API void 				sstring_split(List *out, sstring *str, char* chars);
SCT_API void 				sstring_format(sstring *str, char *in, ...);
SCT_API void 				sstring_destroy(sstring *str);

SCT_API char				sstring_chat_at(sstring *str, size_t index, char** out);
SCT_API char*				sstring_get_value(sstring *str);

#endif
