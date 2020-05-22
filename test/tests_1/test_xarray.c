/*! g++ {0} -I../../include/ ../../src/xarray.c -o out.exe; ./out.exe */


#include <exotic/cester.h>
#include <exotic/xarray.h>

CESTER_COMMENT(

)

CESTER_BEFORE_ALL(inst,
    
)

CESTER_TEST(test_xarray_init, inst, 
    XArray* array;
    enum xtypes_stat status = xarray_new(&array);
    cester_assert_uint_eq(status, X_OK);
)

CESTER_TODO_TEST(test_xarray_add, inst, 
    cester_assert_nothing();
)

CESTER_OPTIONS(
    CESTER_VERBOSE();
    CESTER_MINIMAL();
)