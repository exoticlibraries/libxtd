/*! gcc -ansi -pedantic-errors {0} -I../../../include/ ../../../src/array.c -o out; ./out */

#define XTYPES_DONT_USE_BUILTIN
#include <exotic/cester.h>
#include <exotic/array.h>

CESTER_COMMENT(
    Test the Array data type. 
    Create as many test as posible 
    also try to simulate failures.
)

CESTER_BODY(
typedef struct a_struct__ {
    int index ;
    char* value;
} AStruct;

void* failing_malloc(size_t size) {
    return NULL;
}

bool if_between_2_and_6(const void* item) {
    int num;
    
    num = *((int*)item);
    return num > 2 && num < 6;
}

bool remove_free_if_predicate(const void* item) {
    AStruct *a_struct;
    
    a_struct = (AStruct *) item;
    return a_struct->index == 1 || 
           cester_string_starts_with(a_struct->value, "second");
}

void* test_copy_function(void* item) {
    AStruct *a_struct = (AStruct *) item;
    AStruct *new_a_struct =  (AStruct *) malloc(sizeof(AStruct));
    
    new_a_struct->value = a_struct->value;
    new_a_struct->index = a_struct->index;
    return new_a_struct;
}

void validate_between_2_and_6(void* item) {
    int num;
    
    num = *((int*)item);
    cester_assert_true(num > 2 && num < 6);
}

void add_int_values(void* item, void* result) {
    int num;
    
    num = *((int*)item);
    *((int*)result) += + num;
}

void flatten_array_fn(void* item, void* result) {
    Array *arr = (Array*) item;
    Array *result_array = (Array*) result;
    
    array_add_all(result_array, arr);
}

int cpm_int_for_sort_asc(const void *item1, const void *item2) {
    int num1;
    int num2;
    
    num1 = *(*((int**) item1));
    num2 = *(*((int**) item2));
    return num1 - num2;
}

int cpm_int_for_sort_dsc(const void *item1, const void *item2) {
    int num1;
    int num2;
    
    num1 = *(*((int**) item1));
    num2 = *(*((int**) item2));
    return num2 - num1;
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

CESTER_TEST(test_array_remove, _, 
    Array *array;
    enum x_stat status;
    char* name;
    char* license;
    char* reason;
    char* language;
    
    reason = "for fltk IDE";
    status = array_new(&array);
    cester_assert_int_eq(status, X_OK);
    array_add(array, "libxtypes");
    array_add(array, "MIT License");
    array_add(array, "for fltk IDE");
    array_add(array, "Adewale Azeez");
    array_add(array, "Open Source");
    array_add(array, "C");
    cester_assert_int_eq(6, array_size(array));
    
    array_remove_last(array, (void*)&language);
    cester_assert_str_equal("C", language);
    cester_assert_int_eq(5, array_size(array));
    
    array_remove(array, reason);
    cester_assert_int_eq(4, array_size(array));
    
    array_remove_at(array, 0, (void*)&name);
    cester_assert_str_equal("libxtypes", name);
    cester_assert_int_eq(3, array_size(array));
    
    status = array_remove_all(array);
    cester_assert_int_eq(status, X_OK);
    cester_assert_int_eq(0, array_size(array));
    
    array_destroy(array);
)

CESTER_TEST(test_array_remove_if, _, 
    Array *array;
    enum x_stat status;
    int one;
    int two;
    int three;
    int four;
    int five;
    int six;
    int seven;
    
    one = 1;
    two = 2;
    three = 3;
    four = 4;
    five = 5;
    six = 6;
    seven = 7;
    status = array_new(&array);
    cester_assert_int_eq(status, X_OK);
    array_add(array, &one);
    array_add(array, &two);
    array_add(array, &three);
    array_add(array, &four);
    array_add(array, &five);
    array_add(array, &six);
    array_add(array, &seven);
    
    cester_assert_int_eq(7, array_size(array));
    array_remove_if(array, if_between_2_and_6);
    cester_assert_int_eq(4, array_size(array));    
    
    status = array_remove_range(array, 1, 3);
    cester_assert_int_eq(status, X_OK);
    cester_assert_int_eq(1, array_size(array));   
    
    array_destroy(array);
)

CESTER_TEST(test_array_remove_free, _, 
    Array *array;
    enum x_stat status;
    AStruct *a_struct1;
    AStruct *a_struct2;
    AStruct *a_struct3;
    AStruct *a_struct4;
    
    a_struct1 =  (AStruct *) malloc(sizeof(AStruct));
    a_struct2 =  (AStruct *) malloc(sizeof(AStruct));
    a_struct3 =  (AStruct *) malloc(sizeof(AStruct));
    a_struct1->index = 1;
    a_struct2->value = "second struct";
    a_struct3->value = "third struct";
    
    status = array_new(&array);
    cester_assert_int_eq(status, X_OK);
    array_add(array, a_struct1);
    array_add(array, a_struct2);
    array_add(array, a_struct3);
    cester_assert_str_equal("second struct", a_struct2->value);

    cester_assert_int_eq(3, array_size(array));
    array_free_element_if(array, remove_free_if_predicate);
    cester_assert_int_eq(1, array_size(array));
    a_struct4 =  (AStruct *) malloc(10000);
    array_add(array, a_struct4);
    
    array_free_all_elements(array);
    cester_assert_int_eq(0, array_size(array));
    
    array_destroy(array);
)

CESTER_TEST(test_array_get, _,
    Array *array;
    AStruct *a_struct;
    AStruct *nu_struct;
    char* name;
    int num;
    int* nu_num;
    enum x_stat status;
    
    a_struct = (AStruct *) malloc(sizeof(AStruct));
    num = 212122323;
    status = array_new(&array);
    cester_assert_int_eq(status, X_OK);
    status = array_add(array, a_struct);
    cester_assert_int_eq(status, X_OK);
    status = array_add(array, "libxtypes");
    cester_assert_int_eq(status, X_OK);
    status = array_add(array, &num);
    cester_assert_int_eq(status, X_OK);
    
    cester_assert_str_not_equal(name, "libxtypes");
    status = array_get_at(array, 1, (void*)&name);
    cester_assert_int_eq(status, X_OK);
    cester_assert_str_equal(name, "libxtypes");
    
    status = array_get_last(array, (void*)&nu_num);
    cester_assert_int_eq(status, X_OK);
    cester_assert_int_eq(*nu_num, num);
    
    cester_assert_ptr_not_equal(nu_struct, a_struct);
    status = array_get_at(array, 0, (void*)&nu_struct);
    cester_assert_int_eq(status, X_OK);
    cester_assert_ptr_equal(nu_struct, a_struct);
    
    free(a_struct);
    array_destroy(array);
)

CESTER_TEST(test_array_index_of, _,
    Array *array;
    enum x_stat status;
    int num1 = 20;
    int num2 = 30;
    int num3 = 40;
    int num4 = 50;
    int num5 = 60;
    size_t index;
    
    status = array_new(&array);
    cester_assert_int_eq(X_OK, status);
    array_add(array, &num1);
    array_add(array, &num2);
    array_add(array, &num3);
    array_add(array, &num4);
    array_add(array, &num5);
    
    status = array_index_of(array, &num3, &index);
    cester_assert_int_eq(X_OK, status);
    cester_assert_int_eq(2, index);
    
    status = array_index_of(array, &num5, &index);
    cester_assert_int_eq(X_OK, status);
    cester_assert_int_eq(4, index);
    
    status = array_index_of_from(array, &num3, &index, 2);
    cester_assert_int_eq(X_OK, status);
    cester_assert_int_eq(0, index);
    
    status = array_index_of_from(array, &num4, &index, 2);
    cester_assert_int_eq(X_OK, status);
    cester_assert_int_eq(1, index);
    
    status = array_index_of_in_range(array, &num4, &index, 0, 3);
    cester_assert_int_eq(X_OK, status);
    cester_assert_int_eq(3, index);
    
    status = array_index_of_in_range(array, &num5, &index, 2, array_size(array));
    cester_assert_int_eq(X_OK, status);
    cester_assert_int_eq(2, index);
    
    status = array_index_of_in_range(array, &num3, &index, 2, 4);
    cester_assert_int_eq(X_OK, status);
    cester_assert_int_eq(0, index);
    
    index = -1;
    status = array_index_of_from(array, &num1, &index, 3);
    cester_assert_int_eq(X_OUT_OF_RANGE_ERR, status);
    cester_assert_int_eq(-1, index);
    
    status = array_index_of_in_range(array, &num4, &index, 20, array_size(array));
    cester_assert_int_eq(X_INDEXES_OVERLAP_ERR, status);
    
    array_destroy(array);
)

CESTER_TEST(test_array_last_index_of, _,
    Array *array;
    enum x_stat status;
    int num1 = 20;
    int num2 = 40;
    size_t index;
    
    status = array_new(&array);
    cester_assert_int_eq(X_OK, status);
    array_add(array, &num1);
    array_add(array, &num1);
    array_add(array, &num2);
    array_add(array, &num1);
    array_add(array, &num1);
    
    status = array_last_index_of(array, &num2, &index);
    cester_assert_int_eq(X_OK, status);
    cester_assert_int_eq(2, index);
    
    status = array_last_index_of(array, &num1, &index);
    cester_assert_int_eq(X_OK, status);
    cester_assert_int_eq(4, index);
    
    status = array_last_index_of_from(array, &num1, &index, 2);
    cester_assert_int_eq(X_OK, status);
    cester_assert_int_eq(4, index);
    
    status = array_last_index_of_in_range(array, &num1, &index, 0, 2);
    cester_assert_int_eq(X_OK, status);
    cester_assert_int_eq(1, index);
    
    status = array_last_index_of_in_range(array, &num1, &index, 0, 4);
    cester_assert_int_eq(X_OK, status);
    cester_assert_int_eq(4, index);
    
    array_destroy(array);
)

CESTER_TEST(test_array_copy_fn, _, 
    Array *array1;
    Array *array2;
    AStruct *a_struct;
    AStruct *get_a_struct1;
    AStruct *get_a_struct2;
    enum x_stat status;
    
    status = array_new(&array1);
    cester_assert_int_eq(X_OK, status);
    status = array_new(&array2);
    cester_assert_int_eq(X_OK, status);    
    a_struct =  (AStruct *) malloc(sizeof(AStruct));
    a_struct->value = "Testing 1234 !@##$$";
    
    array_add(array1, (void*) a_struct);    
    status = array_copy_fn(array1, test_copy_function, &array2);
    cester_assert_int_eq(X_OK, status);
    
    array_get_at(array1, 0, (void*)&(get_a_struct1));
    array_get_at(array2, 0, (void*)&(get_a_struct2));
    cester_assert_str_equal(get_a_struct1->value, get_a_struct2->value);
    cester_assert_ptr_not_equal(get_a_struct1, get_a_struct2);
    
    array_destroy(array1);
    array_destroy(array2);
)

CESTER_TEST(test_array_shallow_copy, _, 
    Array *array1;
    Array *array2;
    char *value1;
    char *value2;
    enum x_stat status;
    
    status = array_new(&array1);
    cester_assert_int_eq(X_OK, status);
    status = array_new(&array2);
    cester_assert_int_eq(X_OK, status);
    
    array_add(array1, (void*) "One");
    array_add(array1, (void*) "Two");
    array_add(array1, (void*) "Three");
    
    array_get_at(array1, 0, (void*)&(value1));
    cester_assert_str_equal(value1, "One");
    array_get_at(array1, 2, (void*)&(value1));
    cester_assert_str_not_equal(value1, "Two");
    cester_assert_str_equal(value1, "Three");
    
    status = array_shallow_copy(array1, &array2);
    cester_assert_int_eq(X_OK, status);
    
    array_get_at(array1, 0, (void*)&(value1));
    array_get_at(array2, 0, (void*)&(value2));
    cester_assert_str_equal(value1, value2);
    cester_assert_ptr_equal(value1, value2);
    
    array_get_at(array1, 1, (void*)&(value1));
    array_get_at(array2, 1, (void*)&(value2));
    cester_assert_str_equal(value1, value2);
    cester_assert_ptr_equal(value1, value2);
    
    array_get_at(array1, 2, (void*)&(value1));
    array_get_at(array2, 2, (void*)&(value2));
    cester_assert_str_equal(value1, value2);
    cester_assert_ptr_equal(value1, value2);
    
    array_destroy(array1);
    array_destroy(array2);
)

CESTER_TEST(test_array_shallow_copy_2, _, 
    Array *array1;
    Array *array2;
    AStruct *a_struct;
    AStruct *get_a_struct1;
    AStruct *get_a_struct2;
    enum x_stat status;
    
    status = array_new(&array1);
    cester_assert_int_eq(X_OK, status);
    status = array_new(&array2);
    cester_assert_int_eq(X_OK, status);    
    a_struct =  (AStruct *) malloc(sizeof(AStruct));
    a_struct->value = "Testing 1234 !@##$$";
    
    array_add(array1, (void*) a_struct);    
    status = array_shallow_copy(array1, &array2);
    cester_assert_int_eq(X_OK, status);
    
    array_get_at(array1, 0, (void*)&(get_a_struct1));
    array_get_at(array2, 0, (void*)&(get_a_struct2));
    cester_assert_str_equal(get_a_struct1->value, get_a_struct2->value);
    cester_assert_ptr_equal(get_a_struct1, get_a_struct2);
    
    array_destroy(array1);
    array_destroy(array2);
)

CESTER_TEST(test_array_map, _, 
    Array *array; 
    enum x_stat status;
    int three;
    int four;
    int five;
   
    three = 3;
    four = 4;
    five = 5; 
    status = array_new(&array);
    cester_assert_int_eq(X_OK, status);
    array_add(array, &three);
    array_add(array, &four);
    array_add(array, &five);
    
    cester_assert_int_eq(3, array_size(array));
    array_map(array, validate_between_2_and_6);
    
    array_destroy(array);
)

CESTER_TEST(test_array_reduce, _, 
    Array *array; 
    enum x_stat status;
    int var1;
    int var2;
    int var3;
    int result;
   
    var1 = 5;
    var2 = 10;
    var3 = 15; 
    result = 0;
    status = array_new(&array);
    cester_assert_int_eq(X_OK, status);
    array_add(array, &var1);
    array_add(array, &var2);
    array_add(array, &var3);
    
    cester_assert_int_eq(3, array_size(array));
    array_reduce(array, add_int_values, &result);
    cester_assert_int_eq(result, 30);
    
    array_destroy(array);
)

CESTER_TEST(test_array_reduce_2_flatten_array, _,
    Array *array; 
    Array *array1;
    Array *array2;
    Array *array3;
    enum x_stat status;
    int initial_size;
    
    status = array_new(&array);
    cester_assert_int_eq(X_OK, status);
    status = array_new(&array1);
    cester_assert_int_eq(X_OK, status);
    status = array_new(&array2);
    cester_assert_int_eq(X_OK, status);
    status = array_new(&array3);
    cester_assert_int_eq(X_OK, status);
    
    array_add(array, (void*) array1);
    array_add(array, (void*) array2);
    array_add(array, (void*) array3);
    
    array_add(array1, "one");
    array_add(array1, "two");
    array_add(array1, "three");
    
    array_add(array2, "four");
    array_add(array2, "five");
    array_add(array2, "six");
    
    array_add(array3, "seven");
    array_add(array3, "eight");
    array_add(array3, "nine");
    array_add(array3, "ten");
    
    initial_size = array_size(array);
    array_reduce(array, flatten_array_fn, (void*) array);
    cester_assert_int_eq(array_size(array), initial_size + 
                                            array_size(array1) + 
                                            array_size(array2) + 
                                            array_size(array3));
    
    array_destroy(array);
    array_destroy(array1);
    array_destroy(array2);
    array_destroy(array3);
)

CESTER_TEST(test_array_filter, _, 
    Array *array; 
    Array *filtered_out;
    enum x_stat status;
    int one;
    int two;
    int three;
    int four;
    int five;
    int six;
    int seven;
    
    one = 1;
    two = 2;
    three = 3;
    four = 4;
    five = 5;
    six = 6;
    seven = 7;    
    status = array_new(&array);
    cester_assert_int_eq(X_OK, status);
    array_add(array, &one);
    array_add(array, &two);
    array_add(array, &three);
    array_add(array, &four);
    array_add(array, &five);
    array_add(array, &six);
    array_add(array, &seven);
    
    status = array_filter(array, if_between_2_and_6, &filtered_out);
    cester_assert_int_eq(X_OK, status);
    cester_assert_int_ne(0, array_size(filtered_out));
    cester_assert_int_ne(array_size(array), array_size(filtered_out));
    array_map(filtered_out, validate_between_2_and_6);
    
    array_destroy(array);
    array_destroy(filtered_out);
)

CESTER_TEST(test_array_reverse, _, 
    Array *array; 
    enum x_stat status;
    int one;
    int two;
    int three;
    int four;
    int five;
    int six;
    int seven;
    size_t i;
    void* get_value;
    int num1;
    int num2;
    
    one = 1;
    two = 2;
    three = 3;
    four = 4;
    five = 5;
    six = 6;
    seven = 7;    
    status = array_new(&array);
    cester_assert_int_eq(X_OK, status);
    array_add(array, &one);
    array_add(array, &two);
    array_add(array, &three);
    array_add(array, &four);
    array_add(array, &five);
    array_add(array, &six);
    array_add(array, &seven);
    
    for (i = 0; i < array_size(array) -1; ++i) {
        array_get_at(array, i, (void*) &get_value);
        num1 = *((int*)get_value);
        array_get_at(array, i+1, (void*) &get_value);
        num2 = *((int*)get_value);
        
        cester_assert_int_lt(num1, num2);
    }
    array_reverse(array);    
    for (i = 0; i < array_size(array) - 1; ++i) {
        array_get_at(array, i, (void*) &get_value);
        num1 = *((int*)get_value);
        array_get_at(array, i+1, (void*) &get_value);
        num2 = *((int*)get_value);
        
        cester_assert_int_gt(num1, num2);
    }
    
    array_destroy(array);
)

CESTER_TEST(test_array_contains, _, 
    Array *array;
    enum x_stat status;
    
    status = array_new(&array);
    cester_assert_int_eq(X_OK, status);
    array_add(array, "Adewale");
    array_add(array, "Exotic Libraries");
    
    cester_assert_true(array_contains(array, "Exotic Libraries"));
    cester_assert_true(array_contains(array, "Adewale"));
    cester_assert_false(array_contains(array, "libxtypes"));
    
    array_destroy(array);
)

CESTER_TEST(test_array_element_count, _, 
    Array *array;
    enum x_stat status;
    
    status = array_new(&array);
    cester_assert_int_eq(X_OK, status);
    array_add(array, "Adewale");
    array_add(array, "Exotic Libraries");
    array_add(array, "Exotic Libraries");
    array_add(array, "libxtypes");
    array_add(array, "Adewale");
    array_add(array, "Exotic Libraries");
    array_add(array, "libxtypes");
    array_add(array, "libxtypes");
    array_add(array, "libxtypes");
    array_add(array, "Adewale");
    array_add(array, "Exotic Libraries");
    array_add(array, "Exotic Libraries");
    array_add(array, "libxtypes");
    array_add(array, "libxtypes");
    array_add(array, "libxtypes");
    
    cester_assert_int_eq(3, array_element_count(array, "Adewale"));
    cester_assert_int_eq(5, array_element_count(array, "Exotic Libraries"));
    cester_assert_int_eq(7, array_element_count(array, "libxtypes"));
    
    array_destroy(array);
)

CESTER_TEST(test_array_sort, _, 
    Array *array; 
    enum x_stat status;
    size_t i;
    int one;
    int two;
    int three;
    int four;
    int five;
    void* get_value;
    int num1;
    int num2;
   
    one = 1;
    two = 2;
    three = 3;
    four = 4;
    five = 5; 
    status = array_new(&array);
    cester_assert_int_eq(X_OK, status);
    array_add(array, &two);
    array_add(array, &one);
    array_add(array, &five);
    array_add(array, &four);
    array_add(array, &three);
    
    array_sort(array, cpm_int_for_sort_asc);
    for (i = 0; i < array_size(array) - 1; ++i) {
        array_get_at(array, i, (void*) &get_value);
        num1 = *((int*)get_value);
        array_get_at(array, i+1, (void*) &get_value);
        num2 = *((int*)get_value);
        
        cester_assert_int_lt(num1, num2);
    }
    array_sort(array, cpm_int_for_sort_dsc);
    for (i = 0; i < array_size(array) - 1; ++i) {
        array_get_at(array, i, (void*) &get_value);
        num1 = *((int*)get_value);
        array_get_at(array, i+1, (void*) &get_value);
        num2 = *((int*)get_value);
        
        cester_assert_int_gt(num1, num2);
    }
    
    array_destroy(array);
)

CESTER_TEST(test_array_size_and_capacity_trim_is_empty, _, 
    Array *array; 
    enum x_stat status;
    int one;
    int two;
    int three;
    int four;
    
    one = 1;
    two = 2;
    three = 3;
    four = 4;  
    status = array_new(&array);
    cester_assert_int_eq(X_OK, status);
    cester_assert_true(array_is_empty(array));
    array_add(array, &one);
    array_add(array, &two);
    array_add(array, &three);
    array_add(array, &four);
    array_add(array, &four);
    
    cester_assert_false(array_is_empty(array));
    cester_assert_int_eq(5, array_size(array));
    cester_assert_int_ne(array_capacity(array), array_size(array));
    cester_assert_int_gt(array_capacity(array), 4);
    status = array_trim_to_size(array);
    cester_assert_int_eq(X_OK, status);
    cester_assert_int_eq(array_capacity(array), array_size(array));
    
    array_destroy(array);
)

CESTER_TEST(test_array_iterator_raw, _,
    Array *array;
    enum x_stat status;
    int i;
    void *value;
    
    status = array_new(&array);
    cester_assert_int_eq(X_OK, status); 
    array_add(array, "Hello");
    array_add(array, "World");
    array_add(array, "This");
    array_add(array, "is libxtypes");
    
    i = 0;
    cester_assert_false(array_contains(array, "Whole"));
    cester_assert_true(array_contains(array, "is libxtypes"));
    while (ITERATOR_HAS_NEXT(array)) {
        value = ITERATOR_NEXT(array);
        if (array->iter->index == 0) {
            array_add(array, "Whole");
            array_add(array, "Wide");
        }
        if (cester_string_starts_with(value, "This")) {
            array_remove(array, "is libxtypes");
        }
        if (array->iter->index > 2) {
            array_remove(array, "Wide");
        }
        ++i;
        ++array->iter->index;
    }
    cester_assert_true(array_contains(array, "Whole"));
    cester_assert_false(array_contains(array, "is libxtypes"));
    cester_assert_int_eq(i, array_size(array));
    
    array_destroy(array);
)

CESTER_TEST(test_array_iterator, _,
    Array *array;
    enum x_stat status;
    size_t i;
    
    status = array_new(&array);
    cester_assert_int_eq(X_OK, status); 
    array_add(array, "Hello");
    array_add(array, "World");
    array_add(array, "This");
    array_add(array, "is libxtypes");
    
    i = 0;
    FOREACH(array, element, {
        ++i;
    })
    cester_assert_int_eq(i, array_size(array));
    
    array_destroy(array);
)

CESTER_TEST(test_array_iterator_with_index, _,
    Array *array;
    enum x_stat status;
    int i;
    
    status = array_new(&array);
    cester_assert_int_eq(X_OK, status); 
    array_add(array, "Hello");
    array_add(array, "World");
    array_add(array, "This");
    array_add(array, "is libxtypes");
    
    i = 0;
    cester_assert_false(array_contains(array, "Whole"));
    cester_assert_true(array_contains(array, "is libxtypes"));
    FOREACH_INDEX(array, index, element, {
        if (index == 0) {
            array_add(array, "Whole");
            array_add(array, "Wide");
        }
        if (cester_string_starts_with(element, "This")) {
            array_remove(array, "is libxtypes");
        }
        if (index > 2) {
            array_remove(array, "Wide");
        }
        ++i;
    })
    cester_assert_true(array_contains(array, "Whole"));
    cester_assert_false(array_contains(array, "is libxtypes"));
    cester_assert_int_eq(i, array_size(array));
    
    array_destroy(array);
)

CESTER_OPTIONS(
    CESTER_NO_MEMTEST();
    CESTER_MINIMAL();
)

