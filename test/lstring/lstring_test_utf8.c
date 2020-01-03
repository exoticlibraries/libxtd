
#include "../../lrc/lstring.c"
#include "../../include/l_test_runner.h"
#include <stdio.h>

int main(int argc, char **argv) 
{
    lstring *str;
    if (lstring_new(&str, "x好āaas好And你们x好āax好āa") != L_OK) {
        printf("Init failed\n");
        return 1;
    }
    //l_assert_not_null(str);
    //l_assert_equal(5, lstring_length(str));
    
    //lstring_set_value(str, "");
    //lstring_concat(str, "好");
    //lstring_concat(str, "And");
    //lstring_concat(str, "你们好āa");
    //l_assert_charl_equal(lstring_get_value(str), "好And你们好āa");
    //l_assert_equal(9, lstring_length(str));
    //l_assert_true(lstring_startl_with(str, "好"));
    //l_assert_true(lstring_endl_with(str, "好āa"));
    //l_assert_equal(lstring_index_of(str, "们"), 5);
    //l_assert_equal(lstring_index_of(str, "好"), 0);
    //l_assert_equal(lstring_index_of_from(str, "好", 2), 4);
    printf("::%i\n", lstring_last_index_of(str, "x好āa"));
    printf("%s\n", lstring_charl_at(str, 16));
    //l_assert_equal(lstring_last_index_of_from(str, "like", 18), 0);
    
    //l_test_runner_analyse();
    lstring_destroy(str);
    return 0;
}