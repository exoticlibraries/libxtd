
#include "../../lrc/lstring.c"
#include "../../include/l_test_runner.h"
#include <stdio.h>

int main(int argc, char **argv) 
{
    sstring *str;

    if (sstring_new(&str, "Terry A Davis") != LIBO_OK) {
        printf("Init failed\n");
        return 1;
    }
    l_assert_not_null(str);
    l_assert_true(sstring_startl_with(str, "Terry"));
    l_assert_true(sstring_startl_with_from(str, "A Davis", 6));
    l_assert_true(sstring_endl_with(str, "Davis"));
    l_assert_false(sstring_endl_with(str, "A Dav"));

    sstring_concat(str, " created TempleOS");
    l_assert_true(sstring_endl_with(str, "TempleOS"));

    l_test_runner_analyse();
    sstring_destroy(str);
    return 0;
}