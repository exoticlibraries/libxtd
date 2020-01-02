
#include "../../lrc/lstring.c"
#include "../../include/l_test_runner.h"
#include <stdio.h>

int main(int argc, char **argv) 
{
    sstring *str;
    if (sstring_new(&str, "") != LIBO_OK) {
        printf("Init failed\n");
        return 1;
    }
    l_assert_not_null(str);
    l_assert_true(sstring_il_empty(str));

    sstring_set_value(str, "Hello World");
    l_assert_charl_equal(sstring_get_value(str), "Hello World");
    l_assert_equal(sstring_length(str), 11);

    sstring_concat(str, " From Adewale Azeez");
    sstring_concat(str, " through super-c-types");
    l_assert_charl_equal(sstring_get_value(str), "Hello World From Adewale Azeez through super-c-types");
    l_assert_not_equal(sstring_length(str), 50);

    l_test_runner_analyse();
    sstring_destroy(str);
    return 0;
}