
#include "../../lrc/lstring.c"
#include "../../include/l_test_runner.h"
#include <stdio.h>

int main(int argc, char **argv) 
{
    sstring *str;
    if (sstring_new(&str, "x好āaas好And你们x好āax好āa") != LIBO_OK) {
        printf("Init failed\n");
        return 1;
    }
    //l_assert_not_null(str);
    //l_assert_equal(5, sstring_length(str));
    
    //lstring_set_value(str, "");
    //lstring_concat(str, "好");
    //lstring_concat(str, "And");
    //lstring_concat(str, "你们好āa");
    //l_assert_charl_equal(sstring_get_value(str), "好And你们好āa");
    //l_assert_equal(9, sstring_length(str));
    //l_assert_true(sstring_startl_with(str, "好"));
    //l_assert_true(sstring_endl_with(str, "好āa"));
    //l_assert_equal(sstring_index_of(str, "们"), 5);
    //l_assert_equal(sstring_index_of(str, "好"), 0);
    //l_assert_equal(sstring_index_of_from(str, "好", 2), 4);
    printf("::%i\n", sstring_last_index_of(str, "x好āa"));
    printf("%s\n", sstring_charl_at(str, 16));
    //l_assert_equal(sstring_last_index_of_from(str, "like", 18), 0);
    
    //l_test_runner_analyse();
    sstring_destroy(str);
    return 0;
}