/*!gcc -ansi -pedantic-errors {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/xiterator.h>

CESTER_BEFORE_ALL(test_instance, {
    
})

CESTER_TEST(iterate_raw_array_of_pointers, _, {
    char **fruits = (char **) calloc(3, sizeof(char *));
    char **address = fruits;
    int count = 0;

    fruits[0] = "Apple";
    fruits[1] = "Banana";
    while (*fruits != NULL) {
        printf("Fruit %s\n", (*fruits++));
        count++;
    }
    cester_assert_int_eq(count, 2);
    free(address);
})

CESTER_TEST(iterate_raw_array_of_pointers_next, _, {
    char **fruits = (char **) calloc(3, sizeof(char *));
    char **address = fruits;
    int count = 0;

    fruits[0] = "Apple";
    fruits[1] = "Banana";
    while (XITERATOR_RPTR_HAS_NEXT(fruits)) {
        printf("Fruit %s\n", XITERATOR_RPTR_NEXT(fruits));
        count++;
    }
    cester_assert_int_eq(count, 2);
    free(address);
})

CESTER_TEST(iterate_raw_array_of_pointers_foreach, _, {
    char **fruits = (char **) calloc(3, sizeof(char *));
    char **address = fruits;
    int count = 0;

    fruits[0] = "Apple";
    fruits[1] = "Banana";
    XFOREACH_RPTR(char *fruit, fruits, {
        printf("Fruit %s\n", fruit);
        count++;
    })
    cester_assert_int_eq(count, 2);
    free(address);
})


