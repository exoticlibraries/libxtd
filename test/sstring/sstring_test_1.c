
#include "../../src/sstring.c"
#include "../../include/s_test_runner.h"
#include <stdio.h>

int main(int argc, char **argv) 
{
    sstring *str;
    if (sstring_new(&str, "Hello World") != S_OK) {
        printf("Init failed\n");
        return 1;
    }
    s_assert_not_null(str);
    s_assert_equal(11, sstring_length(str));
    s_assert_chars_equal(sstring_get_value(str), "Hello World");
    
    s_test_runner_analyse();
    sstring_destroy(str);
    return 0;
}