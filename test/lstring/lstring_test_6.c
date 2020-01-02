
#include "../../lrc/lstring.c"
#include "../../include/l_test_runner.h"
#include <stdio.h>

int main(int argc, char **argv) 
{
    sstring *str;

    if (sstring_new(&str, "like do you slide to all your Night like this, like this") != LIBO_OK) {
        printf("Init failed\n");
        return 1;
    }
    //l_assert_not_null(str);
    //l_assert_equal(sstring_last_index_of(str, sstring_get_value(str)), 0);
    //l_assert_equal(sstring_last_index_of(str, "like"), 47);
    l_assert_equal(sstring_last_index_of_from(str, "like", 9), 36);
    //l_assert_equal(sstring_last_index_of_from(str, "like", 18), 0);

    l_test_runner_analyse();
    sstring_destroy(str);
    return 0;
}