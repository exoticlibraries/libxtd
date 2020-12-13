/*! g++ {0} -I../include/ -I../../libmetaref/include/ -o out.exe; ./out.exe */

#include <stdio.h>
#include <stdlib.h>
#include <exotic/cester.h>

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

#ifndef INC_1
#define INC_1
#include <exotic/metaref.h>
//#include <exotic/xoptional.h>

#define SETUP_OPTIONAL_FOR(type)  typedef struct xoptional_##type##_s { \
    bool is_present ;\
    type value;\
} xoptional_##type;\
\
xoptional_##type xoptional_##type##_new(type value) {\
    xoptional_##type _x_gen_optional;\
    if (value == NULL) {\
        _x_gen_optional.is_present = FALSE;\
    } else {\
        _x_gen_optional.is_present = TRUE;\
         _x_gen_optional.value = value;\
    }\
    return _x_gen_optional;\
}\
\
void (*xoption_if_##type##_present_func_ptr) (type value);\
\
void xoptional_##type##_if_present(xoptional_##type optional, \
        void (*xoption_if_##type##_present_func_ptr) (type value)) {\
    if (xoptional_is_present(optional))  { \
        xoption_if_##type##_present_func_ptr(optional.value); \
    }\
}\


#define xoptional(type) xoptional_##type 

#define xoptional_new(type) xoptional_##type##_new 

#define xoptional_is_present(optional) (optional.is_present == TRUE)

#define xoptional_is_empty(optional) (optional.is_present == FALSE)

#define xoptional_get(optional) (optional.value)

#define xoptional_if_present(type) xoptional_##type##_if_present

SETUP_OPTIONAL_FOR(int)

void printer(int value) {
    
}

void myptr(int value) {
    printf("The value In: %d\n", value);
}

#endif

CESTER_TEST(crash_code, inst,
    xoptional(int) num = xoptional_new(int)(2021);
    /*if (xoptional_is_present(num)) {
        myptr(xoptional_get(num));
    }*/
    xoptional_if_present(int)(num, myptr);
)


/* http://www.cplusplus.com/reference/vector/vector/push_back/ */





