/*! gcc -ansi -pedantic-errors {0} -I../include/ -I../../libmetaref/include/ -o out.exe; ./out.exe */

#include <exotic/cester.h>
#include <exotic/xtd/xcommon.h>

CESTER_BODY(


)

CESTER_TEST(test_stack, _, {
    int number = 20;
    void *num_ptr= (void *) (number);
    printf("Number %d\n", number);
    printf("Number %d\n", num_ptr);
})

