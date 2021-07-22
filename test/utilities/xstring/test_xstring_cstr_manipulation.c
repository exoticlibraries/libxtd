/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I.-I../include/  -I../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/xstring.h>
#include <exotic/xtd/xiterator.h>

#define cester_assert_str_equal_(x,y) cester_assert_true(xstring_cstr_equals(x,y))

CESTER_TODO_TEST(xstring_cstr_to_lower_case, _, {
    
})

CESTER_TODO_TEST(xstring_cstr_to_upper_case, _, {
    
})

CESTER_TODO_TEST(xstring_cstr_trim, _, {
    
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)

