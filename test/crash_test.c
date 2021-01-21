/*! gcc -ansi -pedantic-errors {0} -I../include/ -I../../libmetaref/include/ -o out.exe; ./out.exe */

#include <exotic/cester.h>
#include <exotic/xvector.h>

#ifndef SETUP_XSTACK_FOR

#define SETUP_XSTACK_FOR(T) typedef struct xstacks {\
\
    xvector_##T *internal_array;\
} Stack;\
    

#endif

CESTER_BODY(
    typedef char* str;
    SETUP_XVECTOR_FOR(str)
    SETUP_XSTACK_FOR(str)
    
)


CESTER_TEST(test_stack, _, {
    
})







