
#include "../../lrc/lstring.c"
#include "../../include/l_test_runner.h"
#include <stdio.h>

int main(int argc, char **argv) 
{
    lstring *str;
    lstring *str1;
    lstring *str2;
    lstring *str3;

    if (lstring_new(&str, "Terry A Davis") != LIBO_OK || lstring_new(&str1, "The Programmer") != LIBO_OK 
        || lstring_new(&str2, "Terry A Davis") != LIBO_OK || lstring_new(&str3, "terry a davis") != LIBO_OK) {
        printf("Init failed\n");
        return 1;
    }
    l_assert_not_null(str);
    l_assert_false(lstring_equals(str, str1));
    l_assert_true(lstring_equals(str, str2));
    l_assert_false(lstring_equals(str2, str3));
    l_assert_true(lstring_equall_no_case(str2, str3));

    l_test_runner_analyse();
    lstring_destroy(str);
    lstring_destroy(str1);
    lstring_destroy(str2);
    lstring_destroy(str3);
    return 0;
}