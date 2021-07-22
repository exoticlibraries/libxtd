/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I.-I../include/  -I../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/xstring.h>
#include <exotic/xtd/xiterator.h>

#define cester_assert_str_equal_(x,y) cester_assert_true(xstring_cstr_equals(x,y))

CESTER_TEST(xstring_cstr_split_with_length, _, {
    XAllocator allocator;
    char **splited1;
    char **splited2;
    char **splited3;
    char *text1 = "libxtd xstring length and string for xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    size_t text1_length = xstring_cstr_length(text1);
    size_t text2_length = xstring_cstr_length(text2);
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    cester_assert_ptr_equal(xstring_cstr_split_with_length(text1_length, text1, XTD_NULL, allocator), XTD_NULL);
    cester_assert_ptr_equal(xstring_cstr_split_with_length(text1_length, XTD_NULL, XTD_NULL, allocator), XTD_NULL);
    splited1 = xstring_cstr_split_with_length(text1_length, text1, " ", allocator);
    /*cester_assert_ptr_not_equal(splited1, XTD_NULL);*/
    cester_assert_int_eq(xptp_array_size((void **)splited1), 7);
    cester_assert_str_equal_(splited1[0], "libxtd");
    cester_assert_str_equal_(splited1[2], "length");
    cester_assert_str_equal_(splited1[3], "and");
    cester_assert_str_equal_(splited1[6], "xstring");
    splited2 = xstring_cstr_split_with_length(text2_length, text2, "o w", allocator);
    /*cester_assert_ptr_not_equal(splited2, XTD_NULL);*/
    cester_assert_int_eq(xptp_array_size((void **)splited2), 2);
    cester_assert_str_equal_(splited2[0], "Hell");
    cester_assert_str_equal_(splited2[1], "orld");
    splited3 = xstring_cstr_split_with_length(17, "Whole cake island", "", allocator);
    /*cester_assert_ptr_not_equal(splited3, XTD_NULL);*/
    cester_assert_int_eq(xptp_array_size((void **)splited3), 1);
    cester_assert_str_equal_(splited3[0], "Whole cake island");
    /*cester_assert_ptr_equal(splited3[1], XTD_NULL);*/

    xfreep2p((void **)splited1, allocator);
    xfreep2p((void **)splited2, allocator);
    xfreep2p((void **)splited3, allocator);
})

CESTER_TEST(xstring_cstr_split, _, {
    XAllocator allocator;
    char **splited1;
    char **splited2;
    char **splited3;
    char **splited4;
    char **splited5;
    char *text1 = "libxtd xstring length and string for xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "libxtd xstring \nlength \nand \nstring for xstring\n\n\n\n\n\n\n\n";
    char text4[40] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', 'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    cester_assert_ptr_equal(xstring_cstr_split(text1, XTD_NULL, allocator), XTD_NULL);
    cester_assert_ptr_equal(xstring_cstr_split(XTD_NULL, XTD_NULL, allocator), XTD_NULL);
    splited1 = xstring_cstr_split(text1, " ", allocator);
    cester_assert_ptr_not_equal(splited1, XTD_NULL);
    cester_assert_int_eq(xptp_array_size((void **)splited1), 7);
    cester_assert_str_equal_(splited1[0], "libxtd");
    cester_assert_str_equal_(splited1[2], "length");
    cester_assert_str_equal_(splited1[3], "and");
    cester_assert_str_equal_(splited1[6], "xstring");
    splited2 = xstring_cstr_split(text2, "o w", allocator);
    cester_assert_ptr_not_equal(splited2, XTD_NULL);
    cester_assert_int_eq(xptp_array_size((void **)splited2), 2);
    cester_assert_str_equal_(splited2[0], "Hell");
    cester_assert_str_equal(splited2[1], "orld");
    splited3 = xstring_cstr_split("Whole cake island", "", allocator);
    cester_assert_ptr_not_equal(splited3, XTD_NULL);
    cester_assert_int_eq(xptp_array_size((void **)splited3), 1);
    cester_assert_str_equal_(splited3[0], "Whole cake island");
    cester_assert_ptr_equal(splited3[1], XTD_NULL);
    splited4 = xstring_cstr_split(text3, "\n", allocator);
    cester_assert_ptr_not_equal(splited4, XTD_NULL);
    cester_assert_int_eq(xptp_array_size((void **)splited4), 12);
    splited5 = xstring_cstr_split(text4, "o w", allocator);
    cester_assert_ptr_not_equal(splited5, XTD_NULL);
    cester_assert_int_eq(xptp_array_size((void **)splited5), 3);
    cester_assert_str_equal_(splited5[0], "Hell");
    cester_assert_str_equal(splited5[1], "orldHell");
    cester_assert_str_equal(splited5[2], "orld");
    size_t index = 0;
    for (; splited5[index] != XTD_NULL; index++) printf("::::::::::::::::::::::::::::::::::::::::%s\n", splited5[index]);
    return;

    xfreep2p((void **)splited1, allocator);
    xfreep2p((void **)splited2, allocator);
    xfreep2p((void **)splited3, allocator);
    xfreep2p((void **)splited4, allocator);
    xfreep2p((void **)splited5, allocator);
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)

