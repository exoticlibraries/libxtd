
#include "../../include/ltypes.h"
#include "../../src/lstring.c"
#include "../../include/l_test_runner.h"
#include <stdio.h>

int main(int argc, char **argv) 
{
    lint a = 1;
    luint b = 86766;
	
	l_assert_not_equal(a, b);
	l_assert_equal(a, 1);
	printf("%u\n", b);

    l_test_runner_analyse();
    return 0;
}