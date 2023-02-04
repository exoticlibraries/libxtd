/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I.-I../include/  -I../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/container/xstring.h>
#include <exotic/xtd/xiterator.h>

#ifdef __XTD_STDC_VERSION__
#define TEST_CASE_CHAR_ARRAY_HELLO_WORLD {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'}
#else
#define TEST_CASE_CHAR_ARRAY_HELLO_WORLD "Hello world"
#endif

CESTER_TODO_TEST(xstring_cstr_trim_front, _, {
    
})

CESTER_TODO_TEST(xstring_cstr_trim_back, _, {
    
})

CESTER_TODO_TEST(xstring_cstr_trim, _, {
    
})

CESTER_TODO_TEST(xstring_cstr_trim_char, _, {
    remove a dupplicate char in successon
})

CESTER_TODO_TEST(xstring_cstr_trim_white_space, _, {
    
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)


