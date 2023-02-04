/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I.-I../include/  -I../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/container/xstring.h>
#include <exotic/xtd/xiterator.h>

CESTER_TODO_TEST(xstring_cstr_replace, _, {
    
})

CESTER_TODO_TEST(xstring_cstr_replace_first, _, {
    
})

CESTER_TODO_TEST(xstring_cstr_replace_last, _, {
    
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)

