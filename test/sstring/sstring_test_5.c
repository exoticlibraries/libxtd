
#include "../../src/sstring.c"
#include "../../include/s_test_runner.h"
#include <stdio.h>

int main(int argc, char **argv) 
{
    sstring *str;

    if (sstring_new(&str, "The Best day of my Life") != LIBO_OK) {
        printf("Init failed\n");
        return 1;
    }
    s_assert_not_null(str);
    s_assert_equal(sstring_index_of(str, "The Best day of my Life"), 0);
    s_assert_not_equal(sstring_index_of_from(str, "The", 22), 2);
    s_assert_equal(sstring_index_of(str, "Best"), 4);
    s_assert_equal(sstring_index_of(str, "Best day o"), 4);
    s_assert_not_equal(sstring_index_of(str, "Bwee "), 4);
    s_assert_equal(sstring_index_of_from(str, "e", 3), 5);
    s_assert_not_equal(sstring_index_of_from(str, "e", 10), 10);
    s_assert_equal(sstring_index_of(str, "f"), 14);
    s_assert_equal(sstring_index_of(str, "q"), -1);
    s_assert_not_equal(sstring_index_of_from(str, "q", 10), 10);

    s_test_runner_analyse();
    sstring_destroy(str);
    return 0;
}