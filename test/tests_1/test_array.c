/*! gcc -ansi -pedantic-errors {0} -I../../include/ ../../src/array.c -o out.exe; ./out.exe */
/*! gcc {0} -I../../include/ ../../src/array.c -o out.exe; ./out.exe */

#define XTYPES_DONT_USE_BUILTIN
#include <exotic/cester.h>
#include <exotic/array.h>

CESTER_COMMENT(
    Test the Array data type. 
    Create as many test as posible 
    also try to simulate failures.
)

CESTER_BODY(
void *failing_malloc(size_t size) {
    return NULL;
}
)

CESTER_TEST(test_array_init, _, 
    Array *array1;
    Array *array2;
    Array *array3;
    ArrayConfig c;
    enum x_stat status1;
    enum x_stat status2;
    enum x_stat status3;
    
    status1 = array_new(&array1);
    cester_assert_uint_eq(X_OK, status1);
    
    array_config_init(&c);
    c.expand_rate = X_ARRAY_MAX_CAPACITY;
    status2 = array_new_config(&c, &array2);
    cester_assert_uint_eq(X_INVALID_CAPACITY_ERR, status2);
    
    c.expand_rate = 2;
    c.memory_alloc = failing_malloc;
    status3 = array_new_config(&c, &array3);
    cester_assert_uint_eq(X_ALLOC_ERR, status3);
    
    array_destroy(array1);
)

CESTER_TEST(test_array_init_custom_conf, _, 
    Array *array;
    ArrayConfig conf;
    enum x_stat status;
    
    conf.memory_alloc  = malloc;
    conf.memory_calloc = calloc;
    conf.memory_free   = free;
    conf.expand_rate   = 5;
    conf.capacity      = 20;
    status = array_new_config(&conf, &array);
    cester_assert_uint_eq(X_OK, status);
    
    array_destroy(array);
)

CESTER_TEST(test_array_new_from, _, 
    Array *array1;
    Array *array2;
    enum x_stat status1;
    enum x_stat status2;
    int num1 = 20;
    int num2 = 30;
    int num3 = 40;
    int num4 = 50;
    int num5 = 60;
    
    
    status1 = array_new(&array1);
    cester_assert_uint_eq(X_OK, status1);
    array_add(array1, &num1);
    array_add(array1, &num2);
    
    status2 = array_new_from(&array2, array1);
    cester_assert_uint_eq(X_OK, status2);
    
    cester_assert_int_eq(array_size(array1), array_size(array2));
    array_add(array2, &num3);
    array_add(array2, &num4);
    cester_assert_int_gt(array_size(array2), array_size(array1));
    
    array_add(array1, &num5);
    cester_assert_int_eq(array_size(array1), 3);
    cester_assert_int_eq(array_size(array2), 4);
    
    array_destroy(array1);
    array_destroy(array2);
)

CESTER_TEST(test_array_add, _, 
    Array *array;
    enum x_stat status;
    int num1 = 1;
    int num2 = 2;
    int num3 = 3;
    int num4 = 4;
    int num5 = 5;
    
    status = array_new(&array);
    cester_assert_int_eq(status, X_OK);
    cester_assert_int_eq(array_size(array), 0);
    
    status = array_add(array, &num1);
    cester_assert_int_eq(status, X_OK);
    cester_assert_int_eq(array_size(array), 1);
    
    status = array_add(array, &num2);
    cester_assert_int_eq(status, X_OK);
    
    status = array_add(array, &num3);
    cester_assert_int_eq(status, X_OK);
    cester_assert_int_eq(array_size(array), 3);
    
    status = array_add_at(array, &num4, 1);
    cester_assert_int_eq(status, X_OK);
    cester_assert_int_eq(array_size(array), 4);
    
    status = array_add_at(array, &num5, 3);
    cester_assert_int_eq(status, X_OK);
    cester_assert_int_eq(array_size(array), 5);
    
    array_destroy(array);
)

CESTER_TEST(test_array_add_all, _, 
    Array *array1;
    Array *array2;
    Array *array3;
    enum x_stat status1;
    enum x_stat status2;
    enum x_stat status3;
    enum x_stat status;
    int num1 = 1;
    int num2 = 2;
    int num3 = 3;
    int num4 = 4;
    int num5 = 5;
    
    status1 = array_new(&array1);
    status2 = array_new(&array2);
    status3 = array_new(&array3);
    cester_assert_int_eq(status1, X_OK);
    cester_assert_int_eq(status2, X_OK);
    cester_assert_int_eq(status3, X_OK);
    
    status = array_add(array1, &num1);
    cester_assert_int_eq(status, X_OK);
    
    status = array_add(array1, &num2);
    cester_assert_int_eq(status, X_OK);
    cester_assert_int_eq(array_size(array1), 2);
    cester_assert_int_eq(array_size(array2), 0);
    
    status = array_add_all(array2, array1);
    cester_assert_int_eq(status, X_OK);
    cester_assert_int_eq(array_size(array2), 2);
    
    status = array_add_at(array3, &num3, 0);
    cester_assert_int_eq(status, X_OK);
    
    status = array_add_at(array3, &num4, 1);
    cester_assert_int_eq(status, X_OK);
    
    status = array_add_at(array3, &num5, 2);
    cester_assert_int_eq(status, X_OK);
    
    status = array_add_all_at(array2, array3, 0);
    cester_assert_int_eq(status, X_OK);
    cester_assert_int_eq(array_size(array2), 5);
    
    array_destroy(array1);
    array_destroy(array2);
    array_destroy(array3);
)

CESTER_TODO_TEST(test_array_remove, _, 
    
)

CESTER_TODO_TEST(test_array_remove_two, _, 
    
)

CESTER_TODO_TEST(test_array_size_and_capacity, _, 
    
)

CESTER_TODO_TEST(test_array_iterator, _, 
    
)

CESTER_TODO_TEST(test_array_deep_copy, _, 
    
)

CESTER_TODO_TEST(test_array_shallow_copy, _, 
    
)

CESTER_TODO_TEST(test_array_add_get, _, 
    /* test add_at and get and get_at */
    /* see test_array_add_all and test get_at */
)

CESTER_OPTIONS(
    /* CESTER_VERBOSE(); */
    CESTER_MINIMAL();
)

