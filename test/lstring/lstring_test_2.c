
#include "../../src/lstring.c"
#include "../../include/l_test_runner.h"
#include <stdio.h>

int main(int argc, char **argv) 
{
    lstring *str;
    if (lstring_new(&str, "") != L_OK) {
        printf("Init failed\n");
        return 1;
    }
    l_assert_not_null(str);
    l_assert_true(lstring_il_empty(str));

    lstring_set_value(str, "Hello World");
    l_assert_charl_equal(lstring_get_value(str), "Hello World");
    l_assert_equal(lstring_length(str), 11);

    lstring_concat(str, " From Adewale Azeez");
    lstring_concat(str, " through super-c-types");
    l_assert_charl_equal(lstring_get_value(str), "Hello World From Adewale Azeez through super-c-types");
    l_assert_not_equal(lstring_length(str), 50);

    l_test_runner_analyse();
    lstring_destroy(str);
    return 0;
}