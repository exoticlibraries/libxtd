/*! g++ {0} -I../include/ ../src/array.c -o out.exe; ./out.exe */

#include <stdio.h>
#include <stdlib.h>
#include <exotic/array.h>
#include <exotic/cester.h>

#include <iostream>
#include <vector>

/*#define GenerateArray(T) typedef struct array_struct_##T {\
    size_t capacity; \
    size_t size;  \
    T *buffer;\
} Array_##T;\
\
int array_new_##T(Array_##T **out){\
    Array_##T *arr;\
    arr = calloc(1, sizeof(Array_##T));\
    arr->buffer = malloc(3 * sizeof(T*));\
    arr->size = 0;\
    if (!arr->buffer) {\
        return 0;\
    }\
    *out = arr;\
    return 1;\
}\
\
void array_add_##T(Array_##T *arr, T element) \
{\
    arr->buffer[arr->size] = element;\
    ++arr->size;\
}\
\
T array_get_at_##T(Array_##T *arr, size_t index) {\
    return arr->buffer[index];\
}\

#define Array(T) Array_##T
#define array_new(T) array_new_##T
#define array_add(T) array_add_##T
#define array_get_at(T) array_get_at_##T

typedef void* x_void_pointer;
typedef char* cstring;

GenerateArray(x_void_pointer);
GenerateArray(int);
GenerateArray(cstring);

#define array_add_p(x,y) x[0] = y;

int main(int argc, char **argv) 
{
    /*Array(int) *array;
    Array(cstring) *array2;
    int status = array_new(int)(&array);
    status = array_new(cstring)(&array2);
    array_add(int)(array, 65656650);
    array_add(int)(array, 2898392);
    array_add(cstring)(array, "Adewale");
    
    printf("At 0 = %d\n", array_get_at(int)(array, 0));
    printf("At 1 = %d\n", array_get_at(int)(array, 1));
    printf("At 0 = %c\n", array_get_at(int)(array2, 0));*
    
    int *array;
    array_add_p(array, 2932309)
    
}*/

CESTER_SKIP_TEST(xtypes_array, inst, 
    Array *array;
    long long i = 999999999999;
    
    array_new(&array);
    while(i-->0) {
        array_add(array, &i);
    }
)

CESTER_SKIP_TEST(cpp_vector, inst, 
    std::vector<int> array;
    long long i = 999999999999;
    
    while(i-->0) {
        array.push_back(i);
    }
)

/* http://www.cplusplus.com/reference/vector/vector/push_back/ */





