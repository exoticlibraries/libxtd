
#include "../../lrc/lstring.c"
#include "../../include/l_test_runner.h"
#include <stdio.h>

int main(int argc, char **argv) 
{
    lstring *str;
    if (lstring_new(&str, "Hello World") != LIBO_OK) {
        printf("Init failed\n");
        return 1;
    }
    l_assert_not_null(str);
    l_assert_equal(11, lstring_length(str));
    l_assert_charl_equal(lstring_get_value(str), "Hello World");
    
    l_test_runner_analyse();
    lstring_destroy(str);
    return 0;
}