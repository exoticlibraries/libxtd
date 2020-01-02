
#include "../../lrc/lstring.c"
#include "../../include/l_test_runner.h"
#include <stdio.h>

int main(int argc, char **argv) 
{
    lstring *str;

    if (lstring_new(&str, "Terry A Davis") != LIBO_OK) {
        printf("Init failed\n");
        return 1;
    }
    l_assert_not_null(str);
    l_assert_true(lstring_startl_with(str, "Terry"));
    l_assert_true(lstring_startl_with_from(str, "A Davis", 6));
    l_assert_true(lstring_endl_with(str, "Davis"));
    l_assert_false(lstring_endl_with(str, "A Dav"));

    lstring_concat(str, " created TempleOS");
    l_assert_true(lstring_endl_with(str, "TempleOS"));

    l_test_runner_analyse();
    lstring_destroy(str);
    return 0;
}