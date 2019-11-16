
#include "../../src/sstring.c"
#include "../../include/s_test_runner.h"
#include <stdio.h>

int main(int argc, char **argv) 
{
    sstring *str;

    if (sstring_new(&str, "Do you slide to all your Night like this") != S_OK) {
        printf("Init failed\n");
        return 1;
    }
    //s_assert_not_null(str);
    printf(">>%i\n", sstring_last_index_of(str, "li"));
    //s_assert_equal(sstring_last_index_of(str, "The Best Life and Day of my Life,"), -1);
    //s_assert_equal(sstring_last_index_of(str, "Life"), 28);

    s_test_runner_analyse();
    sstring_destroy(str);
    return 0;
}