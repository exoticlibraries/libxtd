
#include "../../include/stypes.h"
#include "../../include/s_test_runner.h"
#include <stdio.h>

int main(int argc, char **argv) 
{
    sint a = 1;
    suint b = 86766;
	
	s_assert_not_equal(a, b);
	s_assert_equal(a, 1);
	printf("%u\n", b);

    s_test_runner_analyse();
    return 0;
}