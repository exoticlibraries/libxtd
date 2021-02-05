/*!gcc -ansi -pedantic-errors {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xoptional.h>

CESTER_BODY(
struct point_s {
    int x;
    int y;
};
typedef char* str;
typedef struct point_s* Point;

SETUP_XOPTIONAL_FOR(int)
SETUP_XOPTIONAL_FOR(str)
SETUP_XOPTIONAL_FOR(Point)


bool int_is_less_than_zero(int value)
{
    return value == -1;
}

)

CESTER_TEST(xoptional_initialization_str, _, {
    xoptional(str) emptyOpt = xoptional_new_empty(str)();
    xoptional(str) fillOpt = xoptional_new(str)("exoticlibraries");
    xoptional(str) nullOpt = xoptional_new(str)(NULL);
    
    cester_assert_false(xoptional_is_present(emptyOpt));
    cester_assert_true(xoptional_is_present(fillOpt));
    cester_assert_false(xoptional_is_present(nullOpt));
})

CESTER_TEST(xoptional_initialization_int, _, {
    xoptional(int) emptyOpt = xoptional_new_empty(int)();
    xoptional(int) fillOpt = xoptional_new_with_cmp(int)(2020, int_is_less_than_zero);
    
    cester_assert_false(xoptional_is_present(emptyOpt));
    cester_assert_true(xoptional_is_present(fillOpt));
})

CESTER_TEST(xoptional_initialization_Point, _, {
    struct point_s *point = (struct point_s *) malloc(sizeof(Point));
    xoptional(Point) emptyOpt = xoptional_new_empty(Point)();
    xoptional(Point) fillOpt = xoptional_new(Point)(point);
    xoptional(Point) nullOpt = xoptional_new(Point)(NULL);
    
    cester_assert_false(xoptional_is_present(emptyOpt));
    cester_assert_true(xoptional_is_present(fillOpt));
    cester_assert_false(xoptional_is_present(nullOpt));

    free(point);
})

CESTER_TEST(xoptional_is_present_is_empty, _, {
    xoptional(str) fillOpt = xoptional_new(str)("exoticlibraries");
    xoptional(str) nullOpt = xoptional_new(str)(NULL);
    
    cester_assert_true(xoptional_is_present(fillOpt));
    cester_assert_false(xoptional_is_present(nullOpt));
    cester_assert_false(xoptional_is_empty(fillOpt));
    cester_assert_true(xoptional_is_empty(nullOpt));
})

CESTER_BODY(
    void str_present_1(char * const value) {
        cester_assert_str_equal(value, "exoticlibraries");
    }
)

CESTER_TEST(xoptional_conditional_if_present, _, {
    xoptional(str) fillOpt = xoptional_new(str)("exoticlibraries");

    xoptional_if_present(str)(fillOpt, str_present_1);
})

CESTER_TEST(xoptional_value, _, {
    struct point_s *point = (struct point_s *) malloc(sizeof(Point));
    xoptional(str) fillOptStr = xoptional_new(str)("exoticlibraries");
    xoptional(int) fillOptInt = xoptional_new(int)(2020);
    xoptional(Point) fillOptPoint;
    point->x = 20; 
    point->y = 40;
    fillOptPoint = xoptional_new(Point)(point);

    cester_assert_str_equal(xoptional_value(fillOptStr), "exoticlibraries");
    cester_assert_int_eq(xoptional_value(fillOptInt), 2020);
    cester_assert_int_eq(xoptional_value(fillOptPoint)->x, 20);
    cester_assert_int_eq(xoptional_value(fillOptPoint)->y, 40);

    free(point);
})

CESTER_TEST(xoptional_value_or, _, {
    xoptional(int) fillOptInt = xoptional_new(int)(2000);
    xoptional(str) fillOptStr = xoptional_new(str)(NULL);
    xoptional(str) fillOptStr2 = xoptional_new(str)("libxtypes");
    xoptional(Point) fillOptPoint = xoptional_new(Point)(NULL);
    struct point_s *point = (struct point_s *) malloc(sizeof(Point));
    point->x = 20; 
    point->y = 40;

    cester_assert_str_equal(xoptional_value_or(fillOptStr, "exoticlibraries"), "exoticlibraries");
    cester_assert_str_equal(xoptional_value_or(fillOptStr2, "libxtd"), "libxtypes");
    cester_assert_int_ne(xoptional_value_or(fillOptInt, 2021), 2021);
    cester_assert_int_eq(xoptional_value_or(fillOptPoint, point)->x, 20);
    cester_assert_int_eq(xoptional_value_or(fillOptPoint, point)->y, 40);

    free(point);
})

CESTER_BODY(
    bool filter_greater_than_2002(int const value) {
        return value > 2002;
    }
)

CESTER_TEST(xoptional_conditional_filter, _, {
    xoptional(int) fillOptInt0 = xoptional_new(int)(2000);
    xoptional(int) fillOptInt1 = xoptional_new(int)(2001);
    xoptional(int) fillOptInt2 = xoptional_new(int)(2002);
    xoptional(int) fillOptInt3 = xoptional_new(int)(2003);
    xoptional(int) fillOptInt4 = xoptional_new(int)(2004);

    cester_assert_false(xoptional_filter_is_present(int)(fillOptInt0, filter_greater_than_2002));
    cester_assert_false(xoptional_filter_is_present(int)(fillOptInt1, filter_greater_than_2002));
    cester_assert_false(xoptional_filter_is_present(int)(fillOptInt2, filter_greater_than_2002));
    cester_assert_true(xoptional_filter_is_present(int)(fillOptInt3, filter_greater_than_2002));
    cester_assert_true(xoptional_filter_is_present(int)(fillOptInt4, filter_greater_than_2002));
})

CESTER_TEST(xoptional_swap_reset, _, {
    xoptional(str) optCester = xoptional_new(str)("1. libcester");
    xoptional(str) optMetaref = xoptional_new(str)("2. libmtaref");
    xoptional(str) *postSwap1 = &optCester;
    xoptional(str) *postSwap2 = &optMetaref;

    cester_assert_str_equal(xoptional_value(optCester), "1. libcester");
    cester_assert_str_equal(xoptional_value(optMetaref), "2. libmtaref");
    cester_assert_ptr_equal(postSwap1, &optCester);
    cester_assert_ptr_equal(postSwap2, &optMetaref);

    xoptional_swap(str)(&optCester, &optMetaref);

    cester_assert_ptr_equal(postSwap1, &optCester);
    cester_assert_ptr_equal(postSwap2, &optMetaref);
    cester_assert_str_not_equal(xoptional_value(optCester), "1. libcester");
    cester_assert_str_not_equal(xoptional_value(optMetaref), "2. libmtaref");
    cester_assert_str_equal(xoptional_value(optCester), "2. libmtaref");
    cester_assert_str_equal(xoptional_value(optMetaref), "1. libcester");
    cester_assert_false(xoptional_is_empty(optCester));
    cester_assert_false(xoptional_is_empty(optMetaref));

    xoptional_reset(optCester);
    xoptional_reset(optMetaref);
    
    cester_assert_true(xoptional_is_empty(optCester));
    cester_assert_true(xoptional_is_empty(optMetaref));
    cester_assert_null(xoptional_value(optCester));
    cester_assert_null(xoptional_value(optMetaref));
})

CESTER_OPTIONS(
    CESTER_DEBUG_LEVEL(3);
)
