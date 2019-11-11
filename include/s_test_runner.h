
/*P
	:copyright: 2019, Azeez Adewale
	:license: GNU Lesser General Public License v3.0 Copyright (c) 
	:author: Azeez Adewale <azeezadewale98@gmail.com>
	:date: 10 November 2019
	:filename: s_test_runner.h
*/


#ifndef S_TEST_RUNNER_H
#define S_TEST_RUNNER_H

#include <stdio.h>
#include "s_common.h"
#include "sstring.h"
#include "sbool.h"

#define s_assert_null(x) s_assert(x==NULL)
#define s_assert_not_null(x) s_assert(x!=NULL)
#define s_assert_true(x) s_assert(x)
#define s_assert_false(x) s_assert(!x)

int TEST_COUNT = 0;
int PASSED_TEST_COUNT = 0;
int FAILED_TEST_COUNT = 0;

S_API inline void s_assert(int x) {
	TEST_COUNT++;
	if (x == 1) {
		PASSED_TEST_COUNT++;
		fprintf(stdout, "Test %i: Assertion Passed \n", TEST_COUNT);
	} else {
		FAILED_TEST_COUNT++;
		fprintf(stderr, "Test %i: Assertion Failed \n", TEST_COUNT);
	}
}

S_API inline void s_test_runner_analyse() {
	fprintf(stdout, "Synthesis: Tested: %i | Passing: %i | Failing: %i \n", 
								TEST_COUNT, PASSED_TEST_COUNT, FAILED_TEST_COUNT);
}

#endif