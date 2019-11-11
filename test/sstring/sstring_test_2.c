
#include "../../src/sstring.c"
#include <stdio.h>

int main(int argc, char **argv) 
{
    sstring *str;
    if (sstring_new(&str, "") != S_OK) {
        printf("Init failed\n");
        return 1;
    }
    printf("sstring_is_empty : %i\n", sstring_is_empty(str));
    sstring_set_value(str, "Hello World");
    printf("sstring_is_empty: %i, length: %i\n", sstring_is_empty(str), sstring_length(str));
    sstring_set_value(str, "Hello World");
    sstring_concat(str, " From Azeez Adewale");
    sstring_concat(str, " through super-c-types");
    printf("%s\n", sstring_get_value(str));

    sstring_destroy(str);
    

    return 0;
}