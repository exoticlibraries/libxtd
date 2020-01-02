
#include "../../src/sstring.c"
#include "../../include/s_test_runner.h"
#include <stdio.h>

int main(int argc, char **argv) 
{
    sstring *str;

    if (sstring_new(&str, "Terry A Davis") != LIBO_OK) {
        printf("Init failed\n");
        return 1;
    }
    s_assert_not_null(str);
    s_assert_true(sstring_starts_with(str, "Terry"));
    s_assert_true(sstring_starts_with_from(str, "A Davis", 6));
    s_assert_true(sstring_ends_with(str, "Davis"));
    s_assert_false(sstring_ends_with(str, "A Dav"));

    sstring_concat(str, " created TempleOS");
    s_assert_true(sstring_ends_with(str, "TempleOS"));

    s_test_runner_analyse();
    sstring_destroy(str);
    return 0;
}