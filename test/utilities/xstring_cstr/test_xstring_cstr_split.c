/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I.-I../include/  -I../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/xstring.h>
#include <exotic/xtd/xiterator.h>

#define cester_assert_str_equal_(x,y) cester_assert_true(xstring_cstr_equals(x,y))

#ifdef __XTD_STDC_VERSION__
#define TEST_CASE_CHAR_ARRAY_HELLO_WORLD {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'}
#define TEST_CASE_CHAR_ARRAY_HELLO_WORLD2 {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', 'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'}
#else
#define TEST_CASE_CHAR_ARRAY_HELLO_WORLD "Hello world"
#define TEST_CASE_CHAR_ARRAY_HELLO_WORLD2 "Hello world Hello world"
#endif

CESTER_TEST(xstring_cstr_split_with_length, _, {
    XAllocator allocator;
    char **splited1;
    char **splited2;
    char **splited3;
    char *text1 = "libxtd xstring length and string for xstring";
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD;
    size_t text1_length = xstring_cstr_length(text1);
    size_t text2_length = xstring_cstr_length(text2);
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    cester_assert_ptr_equal(xstring_cstr_split_with_length(allocator, text1_length, text1, XTD_NULL), XTD_NULL);
    cester_assert_ptr_equal(xstring_cstr_split_with_length(allocator, text1_length, XTD_NULL, XTD_NULL), XTD_NULL);
    splited1 = xstring_cstr_split_with_length(allocator, text1_length, text1, " ");
    /*cester_assert_ptr_not_equal(splited1, XTD_NULL);*/
    cester_assert_int_eq(xptp_array_size((void **)splited1), 7);
    cester_assert_str_equal_(splited1[0], "libxtd");
    cester_assert_str_equal_(splited1[2], "length");
    cester_assert_str_equal_(splited1[3], "and");
    cester_assert_str_equal_(splited1[6], "xstring");
    splited2 = xstring_cstr_split_with_length(allocator, text2_length, text2, "o w");
    /*cester_assert_ptr_not_equal(splited2, XTD_NULL);*/
    cester_assert_int_eq(xptp_array_size((void **)splited2), 2);
    cester_assert_str_equal_(splited2[0], "Hell");
    cester_assert_str_equal_(splited2[1], "orld");
    splited3 = xstring_cstr_split_with_length(allocator, 17, "Whole cake island", "");
    /*cester_assert_ptr_not_equal(splited3, XTD_NULL);*/
    cester_assert_int_eq(xptp_array_size((void **)splited3), 1);
    cester_assert_str_equal_(splited3[0], "Whole cake island");
    /*cester_assert_ptr_equal(splited3[1], XTD_NULL);*/

    xfreep2p(allocator, (void **)splited1);
    xfreep2p(allocator, (void **)splited2);
    xfreep2p(allocator, (void **)splited3);
})

CESTER_TEST(xstring_cstr_split, _, {
    XAllocator allocator;
    char **splited1;
    char **splited2;
    char **splited3;
    char **splited4;
    char **splited5;
    char *text1 = "libxtd xstring length and string for xstring";
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD;
    char *text3 = "libxtd xstring \nlength \nand \nstring for xstring\n\n\n\n\n\n\n\n";
    char text4[40] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD2;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    cester_assert_ptr_equal(xstring_cstr_split(allocator, text1, XTD_NULL), XTD_NULL);
    cester_assert_ptr_equal(xstring_cstr_split(allocator, XTD_NULL, XTD_NULL), XTD_NULL);
    splited1 = xstring_cstr_split(allocator, text1, " ");
    cester_assert_ptr_not_equal(splited1, XTD_NULL);
    cester_assert_int_eq(xptp_array_size((void **)splited1), 7);
    cester_assert_str_equal_(splited1[0], "libxtd");
    cester_assert_str_equal_(splited1[2], "length");
    cester_assert_str_equal_(splited1[3], "and");
    cester_assert_str_equal_(splited1[6], "xstring");
    splited2 = xstring_cstr_split(allocator, text2, "o w");
    cester_assert_ptr_not_equal(splited2, XTD_NULL);
    cester_assert_int_eq(xptp_array_size((void **)splited2), 2);
    cester_assert_str_equal_(splited2[0], "Hell");
    cester_assert_str_equal(splited2[1], "orld");
    splited3 = xstring_cstr_split(allocator, "Whole cake island", "");
    cester_assert_ptr_not_equal(splited3, XTD_NULL);
    cester_assert_int_eq(xptp_array_size((void **)splited3), 1);
    cester_assert_str_equal_(splited3[0], "Whole cake island");
    cester_assert_ptr_equal(splited3[1], XTD_NULL);
    splited4 = xstring_cstr_split(allocator, text3, "\n");
    cester_assert_ptr_not_equal(splited4, XTD_NULL);
    cester_assert_int_eq(xptp_array_size((void **)splited4), 12);
    splited5 = xstring_cstr_split(allocator, text4, "o w");
    cester_assert_ptr_not_equal(splited5, XTD_NULL);
    cester_assert_int_eq(xptp_array_size((void **)splited5), 3);
    cester_assert_str_equal_(splited5[0], "Hell");
    cester_assert_str_equal(splited5[1], "orldHell");
    cester_assert_str_equal(splited5[2], "orld");
    size_t index = 0;
    for (; splited5[index] != XTD_NULL; index++) printf("::::::::::::::::::::::::::::::::::::::::%s\n", splited5[index]);
    return;

    xfreep2p(allocator, (void **)splited1);
    xfreep2p(allocator, (void **)splited2);
    xfreep2p(allocator, (void **)splited3);
    xfreep2p(allocator, (void **)splited4);
    xfreep2p(allocator, (void **)splited5);
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)

