
#include "../../src/sstring.c"
#include "../../include/s_test_runner.h"
#include <stdio.h>

int main(int argc, char **argv) 
{
    sstring *str;
    if (sstring_new(&str, "") != LIBO_OK) {
        printf("Init failed\n");
        return 1;
    }
    s_assert_not_null(str);
    s_assert_true(sstring_is_empty(str));

    sstring_set_value(str, "Hello World");
    s_assert_chars_equal(sstring_get_value(str), "Hello World");
    s_assert_equal(sstring_length(str), 11);

    sstring_concat(str, " From Adewale Azeez");
    sstring_concat(str, " through super-c-types");
    s_assert_chars_equal(sstring_get_value(str), "Hello World From Adewale Azeez through super-c-types");
    s_assert_not_equal(sstring_length(str), 50);

    s_test_runner_analyse();
    sstring_destroy(str);
    return 0;
}