
#include "../../src/sstring.c"
#include "../../include/s_test_runner.h"
#include <stdio.h>

int main(int argc, char **argv) 
{
    sstring *str;
    sstring *str1;
    sstring *str2;
    sstring *str3;

    if (sstring_new(&str, "Terry A Davis") != S_OK || sstring_new(&str1, "The Programmer") != S_OK 
        || sstring_new(&str2, "Terry A Davis") != S_OK || sstring_new(&str3, "terry a davis") != S_OK) {
        printf("Init failed\n");
        return 1;
    }
    s_assert_not_null(str);
    s_assert_false(sstring_equals(str, str1));
    s_assert_true(sstring_equals(str, str2));
    s_assert_false(sstring_equals(str2, str3));
    s_assert_true(sstring_equals_no_case(str2, str3));

    s_test_runner_analyse();
    sstring_destroy(str);
    sstring_destroy(str1);
    sstring_destroy(str2);
    sstring_destroy(str3);
    return 0;
}