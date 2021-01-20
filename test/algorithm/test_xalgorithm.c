/*!gcc {0} -I. -I../../include/ -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I. -I../../include/ -o out; ./out */
/*!gcc {0} -I. -I../../include/ -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../../include/ -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xalgorithm.h>

CESTER_BODY(
    typedef long long llong;
    SETUP_XALGORITHM_FOR(int);
    SETUP_XALGORITHM_FOR(llong);
)

CESTER_TEST(xlinear_search_6, _, {
    int numbers[6] = {1, 2, 3, 4, 5, 6};
    
    cester_assert_int_eq(xliner_search(int)(numbers, 6, 1), 0);
    cester_assert_int_eq(xliner_search(int)(numbers, 6, 2), 1);
    cester_assert_int_eq(xliner_search(int)(numbers, 6, 3), 2);
    cester_assert_int_eq(xliner_search(int)(numbers, 6, 4), 3);
    cester_assert_int_eq(xliner_search(int)(numbers, 6, 5), 4);
    cester_assert_int_eq(xliner_search(int)(numbers, 6, 6), 5);
})

CESTER_TEST(xlinear_search_999999999, _, {
    size_t index = 0;
    long long size = 999999999;
    long long *numbers = calloc(size, sizeof(long long));

    for (; index < size; index++) {
        numbers[index] = (index + 2);
    }
    
    cester_assert_int_eq(xliner_search(llong)(numbers, size, 2), 0);
    cester_assert_int_eq(xliner_search(llong)(numbers, size, 3), 1);
    cester_assert_int_eq(xliner_search(llong)(numbers, size, 5), 3);
    cester_assert_int_eq(xliner_search(llong)(numbers, size, 7), 5);
    cester_assert_int_eq(xliner_search(llong)(numbers, size, 9), 7);
    cester_assert_int_eq(xliner_search(llong)(numbers, size, 10), 8);
    cester_assert_int_eq(xliner_search(llong)(numbers, size, 1001), 999);
    cester_assert_int_eq(xliner_search(llong)(numbers, size, 10001), 9999);
    cester_assert_int_eq(xliner_search(llong)(numbers, size, 100001), 99999);

    free(numbers);
})

CESTER_TEST(xbinary_search_6, _, {
    int numbers[6] = {1, 2, 3, 4, 5, 6};
    
    cester_assert_int_eq(xbinary_search(int)(numbers, 6, 1), 0);
    cester_assert_int_eq(xbinary_search(int)(numbers, 6, 2), 1);
    cester_assert_int_eq(xbinary_search(int)(numbers, 6, 3), 2);
    cester_assert_int_eq(xbinary_search(int)(numbers, 6, 4), 3);
    cester_assert_int_eq(xbinary_search(int)(numbers, 6, 5), 4);
    cester_assert_int_eq(xbinary_search(int)(numbers, 6, 6), 5);
})

CESTER_TEST(xbinary_search_999999999, _, {
    size_t index = 0;
    long long size = 999999999;
    long long *numbers = calloc(size, sizeof(long long));

    for (; index < size; index++) {
        numbers[index] = (index + 2);
    }
    
    cester_assert_int_eq(xbinary_search(llong)(numbers, size, 2), 0);
    cester_assert_int_eq(xbinary_search(llong)(numbers, size, 3), 1);
    cester_assert_int_eq(xbinary_search(llong)(numbers, size, 5), 3);
    cester_assert_int_eq(xbinary_search(llong)(numbers, size, 7), 5);
    cester_assert_int_eq(xbinary_search(llong)(numbers, size, 9), 7);
    cester_assert_int_eq(xbinary_search(llong)(numbers, size, 10), 8);
    cester_assert_int_eq(xbinary_search(llong)(numbers, size, 1001), 999);
    cester_assert_int_eq(xbinary_search(llong)(numbers, size, 10001), 9999);
    cester_assert_int_eq(xbinary_search(llong)(numbers, size, 100001), 99999);

    free(numbers);
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(0);
)