
/*P
	:copyright: 2019, Azeez Adewale
	:license: GNU Lesser General Public License v3.0 Copyright (c) 
	:author: Azeez Adewale <azeezadewale98@gmail.com>
	:date: 10 November 2019
	:filename: s_test_runner.h
*/


#ifndef S_TEST_RUNNER_H
#define S_TEST_RUNNER_H

#define s_assert(x)
#define s_assert_true(x) if (x == 1) \
							fprintf(stdout, "Assertion Passed\n"); \
							else 								\
							fprintf(stderr, "Assertion Failed\n");

#define s_assert_false(x) s_assert_true(!x)

#endif