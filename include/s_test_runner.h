
/*P
	:copyright: 2019, Adewale Azeez
	:license: GNU Lesser General Public License v3.0 Copyright (c) 
	:author: Adewale Azeez <azeezadewale98@gmail.com>
	:date: 10 November 2019
	:filename: s_test_runner.h
*/


#ifndef LIBO_TEST_RUNNER_H
#define LIBO_TEST_RUNNER_H

#include <stdio.h>
#include "s_common.h"
#include "sstring.h"
#include "sbool.h"

#define s_assert_null(x) s_assert(x==NULL)
#define s_assert_not_null(x) s_assert(x!=NULL)
#define s_assert_true(x) s_assert(x)
#define s_assert_false(x) s_assert(!x)
#define s_assert_equal(x,y) s_assert(x==y)
#define s_assert_not_equal(x,y) s_assert(x!=y)

int test_count = 0;
int passed_test_count = 0;
int failed_test_count = 0;

LIBO_API inline void s_assert(int x) 
{
	test_count++;
	if (x == 1) {
		passed_test_count++;
		fprintf(stdout, "Test %i: Assertion Passed \n", test_count);
	} else {
		failed_test_count++;
		fprintf(stderr, "Test %i: Assertion Failed \n", test_count);
	}
}

LIBO_API inline void s_test_runner_analyse() 
{
	fprintf(stdout, "Synthesis: Tested: %i | Passing: %i | Failing: %i \n", 
								test_count, passed_test_count, failed_test_count);
}

LIBO_API inline void s_assert_chars_equal(char* chars1, char* chars2)
{
	sstring *str1;
	sstring *str2;

    if (sstring_new(&str1, chars1) != LIBO_OK || sstring_new(&str2, chars2) != LIBO_OK) {
        s_assert_true(SFALSE);
        return;
    }
	s_assert(sstring_equals(str1, str2));
	sstring_destroy(str1);
	sstring_destroy(str2);
}

#endif