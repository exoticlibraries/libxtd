
#include "../../include/lbool.h"
#include "../../src/lstring.c"
#include "../../include/l_test_runner.h"
#include <stdio.h>

int main(int argc, char **argv) 
{
    lbool bool1 = SFALSE;
    lbool bool2 = STRUE;
    lbool bool3 = FALSE;
    lbool bool4 = FALSE;
    lbool bool5 = TRUE;

    l_assert_false(bool1);
    l_assert_true(bool2);
    l_assert_false(bool3);
    l_assert_false(bool4);
    l_assert_true(bool5);
    l_assert_equal(bool1, bool4);
    l_assert_not_equal(bool1, bool2);

    l_test_runner_analyse();
    return 0;
}