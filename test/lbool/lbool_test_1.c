
#include "../../include/lbool.h"
#include "../../lrc/lstring.c"
#include "../../include/l_test_runner.h"
#include <stdio.h>

int main(int argc, char **argv) 
{
    sbool bool1 = SFALSE;
    sbool bool2 = STRUE;
    sbool bool3 = FALSE;
    sbool bool4 = FALSE;
    sbool bool5 = TRUE;

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