/*!gcc -ansi -pedantic-errors {0} -I. -I../../include/ -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I. -I../../include/ -o out; ./out */
/*!gcc {0} -I. -I../../include/ -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../../include/ -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xiterator.h>

CESTER_BEFORE_ALL(test_instance, {
    
})

CESTER_TEST(iterate_raw_array_of_pointers, _, {
    char* numbers = calloc(2, sizeof(char));
    int count = 0;

    numbers[0] = 'A';
    numbers[1] = 'B';    
    while (*numbers != '\0') {
        printf("Number %c\n", (*numbers++));
        count++;
    }
    cester_assert_int_eq(count, 2);
})

CESTER_TEST(iterate_raw_array_of_pointers_next, _, {
    char* numbers = calloc(2, sizeof(char));
    int count = 0;

    numbers[0] = 'A';
    numbers[1] = 'B';    
    while (XITERATOR_RPTR_HAS_NEXT(numbers)) {
        printf("Number %c\n", XITERATOR_RPTR_NEXT(numbers));
        count++;
    }
    cester_assert_int_eq(count, 2);
})

CESTER_TEST(iterate_raw_array_of_pointers_foreach, _, {
    char* numbers = calloc(2, sizeof(char));
    int count = 0;

    numbers[0] = 'A';
    numbers[1] = 'B';
    XFOREACH_RPTR(char number, numbers, {
        printf("Number %c\n", number);
        count++;
    })
    cester_assert_int_eq(count, 2);
})

