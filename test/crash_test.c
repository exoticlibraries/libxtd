/*! gcc -ansi -pedantic-errors {0} -I../include/ ../src/array.c -o out.exe; ./out.exe */

CESTER_TEST(crash_test, _, 
    Array *array;
    Array *array_tmp;
    enum x_stat status;
    int num1 = 1;
    int num2 = 2;
    int num3 = 3;
    int num4 = 4;
    int num5 = 5;
    int num60 = 60;
    int num70 = 70;
    int num80 = 80;
    
    int* n1;
    int* n2;
    int* n3;
    
    status = array_new(&array);
    status = array_new(&array_tmp);
    array_add(array, &num1);
    array_add(array, &num2);
    array_add(array, &num3);
    array_add(array, &num4);
    array_add(array, &num5);
    
    array_add(array_tmp, &num60);
    array_add(array_tmp, &num70);
    array_add(array_tmp, &num80);
    
    array_get_at(array_tmp, 0, (void*)&n1);
    array_get_at(array_tmp, 1, (void*)&n2);
    array_get_at(array_tmp, 2, (void*)&n3);
    printf("Size=%d,At0=%d,At1=%d,At2=%d\n", array_size(array_tmp), *n1, *n2, *n3);
    status = array_add_all_at(array_tmp, array, 1);
    /* cester_assert_int_eq(status, X_OK); */
    
    array_get_at(array_tmp, 0, (void*)&n1);
    array_get_at(array_tmp, 1, (void*)&n2);
    array_get_at(array_tmp, 2, (void*)&n3);
    printf("Size=%d,At0=%d,At1=%d,At2=%d\n", array_size(array_tmp), *n1, *n2, *n3);
    
    array_destroy(array);
    array_destroy(array_tmp);
)