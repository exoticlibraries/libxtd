
#include "../../src/sstring.c"
#include "../../include/s_test_runner.h"
#include <stdio.h>

int main(int argc, char **argv) 
{
    sstring *str;

    if (sstring_new(&str, "like do you slide to all your Night like this, like this") != S_OK) {
        printf("Init failed\n");
        return 1;
    }
    s_assert_not_null(str);
    s_assert_equal(sstring_last_index_of(str, sstring_get_value(str)), 0);
    s_assert_equal(sstring_last_index_of(str, "like"), 47);
    s_assert_equal(sstring_last_index_of_from(str, "like", 9), 36);
    s_assert_equal(sstring_last_index_of_from(str, "like", 18), 0);

    s_test_runner_analyse();
    sstring_destroy(str);
    return 0;
}