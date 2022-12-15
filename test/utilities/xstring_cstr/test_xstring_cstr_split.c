/*!gcc {0} -I. -I../include/ -I../../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I.-I../include/  -I../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/container/xstring.h>
#include <exotic/xtd/xiterator.h>

#ifdef __XTD_STDC_VERSION__
#define TEST_CASE_CHAR_ARRAY_HELLO_WORLD {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'}
#define TEST_CASE_CHAR_ARRAY_HELLO_WORLD2 {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'}
#else
#define TEST_CASE_CHAR_ARRAY_HELLO_WORLD "Hello world"
#define TEST_CASE_CHAR_ARRAY_HELLO_WORLD2 "Hello world Hello world"
#endif


/* function to convert char ** to xvector(cstr) */
CESTER_TEST(xstring_cstr_split_quick_test, _, {
	XAllocator allocator;
    char **splited1;
    char **splited2;
    char *text1 = "aaa";
	char *text2 = "Hello world";
    size_t text1_length = xstring_cstr_length(text1);
    size_t text2_length = xstring_cstr_length(text2);
    size_t splitted1_count;
    size_t splitted2_count;
	allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;
	
    /*splitted1_count = xstring_cstr_split_with_length(allocator, text1_length, text1, " ", &splited1);
	cester_assert_int_eq(splitted1_count, 11);*/
    /*splitted1_count = xstring_cstr_split_with_length(allocator, text1_length, text1, "", &splited1);
	printf("Splitted Count = %d\n", splitted1_count);
	
	for (size_t index = 0; index < splitted1_count; index++) {
    	printf("Splitted[%d] = '%s'\n", index, splited1[index]);
	}*/
	/*printf("Splitted[1] = '%s'\n", splited2[1]);*/
})

CESTER_TEST(xstring_cstr_split_with_length, _, {
    XAllocator allocator;
    char **splited1;
    char **splited2;
    char **splited3;
    size_t index;
    size_t splited1_length;
    size_t splited2_length;
    size_t splited3_length;
    char *text1 = "libxtd xstring length and string for xstring";
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD;
    size_t text1_length = xstring_cstr_length(text1);
    size_t text2_length = xstring_cstr_length(text2);
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    cester_assert_int_eq(xstring_cstr_split_with_length(allocator, text1_length, text1, " ", XTD_NULL), 0);
    cester_assert_int_eq(xstring_cstr_split_with_length(allocator, text1_length, text1, XTD_NULL, XTD_NULL), 0);
    cester_assert_int_eq(xstring_cstr_split_with_length(allocator, text1_length, XTD_NULL, XTD_NULL, XTD_NULL), 0);
	
    splited1_length = xstring_cstr_split_with_length(allocator, text1_length, text1, "trtrtjujuyjiuiui", &splited1);
    cester_assert_int_eq(splited1_length, 1);
    cester_assert_str_eq(splited1[0], text1);
	xfreep2p_wl(allocator, (void **)splited1, splited1_length);
	
    splited1_length = xstring_cstr_split_with_length(allocator, text1_length, text1, text1, &splited1);
    cester_assert_int_eq(splited1_length, 0);

    splited1_length = xstring_cstr_split_with_length(allocator, text1_length, text1, " ", &splited1);
    cester_assert_ptr_ne(splited1, XTD_NULL);
    cester_assert_int_eq(splited1_length, 7);
    cester_assert_str_eq(splited1[0], "libxtd");
    cester_assert_str_eq(splited1[2], "length");
    cester_assert_str_eq(splited1[3], "and");
    cester_assert_str_eq(splited1[6], "xstring");
    xfreep2p_wl(allocator, (void **)splited1, splited1_length);

    splited2_length = xstring_cstr_split_with_length(allocator, text2_length, text2, "o w", &splited2);
    cester_assert_ptr_ne(splited2, XTD_NULL);
    cester_assert_int_eq(splited2_length, 2);
    cester_assert_str_eq(splited2[0], "Hell");
	cester_assert_str_eq(splited2[1], "orld");
    xfreep2p_wl(allocator, (void **)splited2, splited2_length);

    splited3_length = xstring_cstr_split_with_length(allocator, 17, "Whole cake island", "", &splited3);
    cester_assert_ptr_not_equal(splited3, XTD_NULL);
    cester_assert_int_eq(splited3_length, 17);
	cester_assert_str_eq(splited3[0], "W");
	cester_assert_str_eq(splited3[splited3_length-1], "d");
	for (index = 0; index < splited3_length; index++) {
    	cester_assert_char_eq(splited3[index][0], ((char *) "Whole cake island")[index]);
	}
    xfreep2p_wl(allocator, (void **)splited3, splited3_length);
})

CESTER_TEST(xstring_cstr_split, _, {
    XAllocator allocator;
    char **splited1;
    char **splited2;
    char **splited3;
    char **splited4;
    char **splited5;
    size_t index;
    size_t splited1_length;
    size_t splited2_length;
    size_t splited3_length;
    size_t splited4_length;
    size_t splited5_length;
    char *text1 = "libxtd xstring length and string for xstring";
    char text2[20] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD;
    char *text3 = "libxtd xstring \nlength \nand \nstring for xstring\n\n\n\n\n\n\n\n";
    char text4[40] = TEST_CASE_CHAR_ARRAY_HELLO_WORLD2;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    cester_assert_int_eq(xstring_cstr_split(allocator, text1, "", XTD_NULL), 0);
    cester_assert_int_eq(xstring_cstr_split(allocator, text1, XTD_NULL, XTD_NULL), 0);
    cester_assert_int_eq(xstring_cstr_split(allocator, XTD_NULL, XTD_NULL, XTD_NULL), 0);

    splited1_length = xstring_cstr_split(allocator, text1, "trtrtjujuyjiuiui", &splited1);
    cester_assert_int_eq(splited1_length, 1);
    cester_assert_str_eq(splited1[0], text1);
	xfreep2p_wl(allocator, (void **)splited1, splited1_length);
	
    splited1_length = xstring_cstr_split(allocator, text1, text1, &splited1);
    cester_assert_int_eq(splited1_length, 0);

    splited1_length = xstring_cstr_split(allocator, text1, " ", &splited1);
    cester_assert_ptr_not_equal(splited1, XTD_NULL);
    cester_assert_int_eq(splited1_length, 7);
    cester_assert_str_eq(splited1[0], "libxtd");
    cester_assert_str_eq(splited1[2], "length");
    cester_assert_str_eq(splited1[3], "and");
    cester_assert_str_eq(splited1[6], "xstring");
    xfreep2p_wl(allocator, (void **)splited1, splited1_length);

    splited2_length = xstring_cstr_split(allocator, text2, "o w", &splited2);
    cester_assert_ptr_not_equal(splited2, XTD_NULL);
    cester_assert_int_eq(splited2_length, 2);
    cester_assert_str_eq(splited2[0], "Hell");
    cester_assert_str_equal(splited2[1], "orld");
    xfreep2p_wl(allocator, (void **)splited2, splited2_length);

    splited3_length = xstring_cstr_split(allocator, "Whole cake island", "ctrtryurt7tu", &splited3);
    cester_assert_ptr_not_equal(splited3, XTD_NULL);
    cester_assert_int_eq(splited3_length, 1);
    cester_assert_str_eq(splited3[0], "Whole cake island");
    xfreep2p_wl(allocator, (void **)splited3, splited3_length);

    splited3_length = xstring_cstr_split(allocator, "Whole cake island", "", &splited3);
    cester_assert_ptr_not_equal(splited3, XTD_NULL);
    cester_assert_int_eq(splited3_length, 17);
    cester_assert_str_eq(splited3[0], "W");
    cester_assert_str_eq(splited3[splited3_length-2], "n");
	for (index = 0; index < splited3_length; index++) {
    	cester_assert_char_eq(splited3[index][0], ((char *) "Whole cake island")[index]);
	}
    xfreep2p_wl(allocator, (void **)splited3, splited3_length);

    splited4_length = xstring_cstr_split(allocator, text3, "\n", &splited4);
    cester_assert_ptr_not_equal(splited4, XTD_NULL);
    cester_assert_int_eq(splited4_length, 12);
    xfreep2p_wl(allocator, (void **)splited4, splited4_length);

    splited5_length = xstring_cstr_split(allocator, text4, "o w", &splited5);
    cester_assert_ptr_not_equal(splited5, XTD_NULL);
    cester_assert_int_eq(splited5_length, 3);
    cester_assert_str_eq(splited5[0], "Hell");
    cester_assert_str_equal(splited5[1], "orld Hell");
    cester_assert_str_equal(splited5[2], "orld");
    xfreep2p_wl(allocator, (void **)splited5, splited5_length);
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)

