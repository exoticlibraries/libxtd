
#include "../../include/sbool.h"
#include "../../src/sstring.c"
#include "../../include/s_test_runner.h"
#include <stdio.h>

int main(int argc, char **argv) 
{
    enum sbool bool1 = SFALSE;
    enum sbool bool2 = STRUE;
    enum sbool bool3 = FALSE;
    enum sbool bool4 = FALSE;
    enum sbool bool5 = TRUE;

    s_assert_false(bool1);
    s_assert_true(bool2);
    s_assert_false(bool3);
    s_assert_false(bool4);
    s_assert_true(bool5);
    s_assert_equal(bool1, bool4);
    s_assert_not_equal(bool1, bool2);

    s_test_runner_analyse();
    return 0;
}