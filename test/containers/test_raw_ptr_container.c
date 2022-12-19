/*!gcc {0} -I. -I../../include/ -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I. -I../../include/ -o out; ./out */
/*!gcc {0} -I. -I../../include/ -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../../include/ -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/util/x_unmanaged_apis.h>
#include <exotic/xtd/xiterator.h>

CESTER_TEST(manage_raw_ptr_array_add, _, {
    char **fruits = (char **) malloc(10 * sizeof(char *));
    
    array_add_at(fruits, 0, "Apple");
    array_add_at(fruits, 1, "Banana");
    cester_assert_str_equal(array_get(fruits, 1), "Banana");

    free(fruits);
})
