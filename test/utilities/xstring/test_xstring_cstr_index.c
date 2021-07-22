/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I.-I../include/  -I../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/xstring.h>
#include <exotic/xtd/xiterator.h>

#define cester_assert_str_equal_(x,y) cester_assert_true(xstring_cstr_equals(x,y))

CESTER_TEST(xstring_cstr_index_of_from_pos_with_length, _, {
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "string";
    size_t text1_length = xstring_cstr_length(text1);
    size_t text2_length = xstring_cstr_length(text2);

    cester_assert_int_eq(xstring_cstr_index_of_from_pos_with_length(text1_length, text1, "xtd", 0), 3);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos_with_length(text1_length, text1, "libxtd xstring length and longer", 0), -1);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos_with_length(text1_length, text1, "libxtd xstring length xstring", 0), 0);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos_with_length(text1_length, text1, text1, 0), 0);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos_with_length(text1_length, text1, "i", 0), 1);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos_with_length(text1_length, text1, "i", 4), 11);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos_with_length(text1_length, text1, "xstring", 0), 7);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos_with_length(text1_length, text1, "xstring", 10), 22);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos_with_length(text1_length, text1, text2, 0), -1);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos_with_length(text1_length, text1, text3, 0), 8);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos_with_length(text1_length, text1, text3, 10), 23);
})

CESTER_TEST(xstring_cstr_index_of_from_pos, _, {
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "string";

    cester_assert_int_eq(xstring_cstr_index_of_from_pos(text1, "xtd", 0), 3);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos(text1, "libxtd xstring length and longer", 0), -1);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos(text1, "libxtd xstring length xstring", 0), 0);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos(text1, text1, 0), 0);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos(text1, "i", 0), 1);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos(text1, "i", 4), 11);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos(text1, "xstring", 0), 7);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos(text1, "xstring", 10), 22);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos(text1, text2, 0), -1);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos(text1, text3, 0), 8);
    cester_assert_int_eq(xstring_cstr_index_of_from_pos(text1, text3, 10), 23);
})

CESTER_TEST(xstring_cstr_index_of, _, {
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "string";

    cester_assert_int_eq(xstring_cstr_index_of(text1, "xtd"), 3);
    cester_assert_int_eq(xstring_cstr_index_of(text1, "libxtd xstring length and longer"), -1);
    cester_assert_int_eq(xstring_cstr_index_of(text1, "libxtd xstring length xstring"), 0);
    cester_assert_int_eq(xstring_cstr_index_of(text1, text1), 0);
    cester_assert_int_eq(xstring_cstr_index_of(text1, "i"), 1);
    cester_assert_int_eq(xstring_cstr_index_of(text1, "xstring"), 7);
    cester_assert_int_eq(xstring_cstr_index_of(text1, text2), -1);
    cester_assert_int_eq(xstring_cstr_index_of(text1, text3), 8);
})

CESTER_TEST(xstring_cstr_last_index_of_from_pos_with_length, _, {
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "string";
    size_t text1_length = xstring_cstr_length(text1);
    size_t text2_length = xstring_cstr_length(text2);

    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos_with_length(text1_length, text1, "xtd", 0), 3);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos_with_length(text1_length, text1, "libxtd xstring length and longer", 0), -1);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos_with_length(text1_length, text1, "libxtd xstring length xstring", 0), 0);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos_with_length(text1_length, text1, text1, 0), 0);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos_with_length(text1_length, text1, "i", 0), 26);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos_with_length(text1_length, text1, "i", 4), 11);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos_with_length(text1_length, text1, "xstring", 0), 22);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos_with_length(text1_length, text1, "xstring", 10), 7);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos_with_length(text1_length, text1, text2, 0), -1);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos_with_length(text1_length, text1, text3, 0), 23);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos_with_length(text1_length, text1, text3, 10), 8);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos_with_length(text2_length, text2, "o", 0), 7);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos_with_length(text2_length, text2, "o", 4), 4);
})

CESTER_TEST(xstring_cstr_last_index_of_from_pos, _, {
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "string";

    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos(text1, "xtd", 0), 3);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos(text1, "libxtd xstring length and longer", 0), -1);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos(text1, "libxtd xstring length xstring", 0), 0);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos(text1, text1, 0), 0);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos(text1, "i", 0), 26);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos(text1, "i", 4), 11);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos(text1, "xstring", 0), 22);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos(text1, "xstring", 10), 7);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos(text1, text2, 0), -1);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos(text1, text3, 0), 23);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos(text1, text3, 10), 8);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos(text2, "o", 0), 7);
    cester_assert_int_eq(xstring_cstr_last_index_of_from_pos(text2, "o", 4), 4);
})

CESTER_TEST(xstring_cstr_last_index_of, _, {
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "string";

    cester_assert_int_eq(xstring_cstr_last_index_of(text1, "xtd"), 3);
    cester_assert_int_eq(xstring_cstr_last_index_of(text1, "libxtd xstring length and longer"), -1);
    cester_assert_int_eq(xstring_cstr_last_index_of(text1, "libxtd xstring length xstring"), 0);
    cester_assert_int_eq(xstring_cstr_last_index_of(text1, text1), 0);
    cester_assert_int_eq(xstring_cstr_last_index_of(text1, "i"), 26);
    cester_assert_int_eq(xstring_cstr_last_index_of(text1, "xstring"), 22);
    cester_assert_int_eq(xstring_cstr_last_index_of(text1, text2), -1);
    cester_assert_int_eq(xstring_cstr_last_index_of(text1, text3), 23);
    cester_assert_int_eq(xstring_cstr_last_index_of("test_xstring_utils.h", "."), 18);
})

CESTER_TEST(xstring_cstr_contains, _, {
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "string";

    cester_assert_true(xstring_cstr_contains(text1, "xtd"));
    cester_assert_false(xstring_cstr_contains(text1, "libxtd xstring length and longer"));
    cester_assert_true(xstring_cstr_contains(text1, "libxtd xstring length xstring"));
    cester_assert_true(xstring_cstr_contains(text1, text1));
    cester_assert_true(xstring_cstr_contains(text1, "i"));
    cester_assert_true(xstring_cstr_contains(text1, "xstring"));
    cester_assert_false(xstring_cstr_contains(text1, text2));
    cester_assert_true(xstring_cstr_contains(text1, text3));
    cester_assert_true(xstring_cstr_contains("test_xstring_utils.h", "."));
    cester_assert_true(xstring_cstr_contains(text2, "Hello"));
    cester_assert_false(xstring_cstr_contains(text2, "hello"));
    cester_assert_false(xstring_cstr_contains(text2, "World"));
    cester_assert_true(xstring_cstr_contains(text2, "world"));
    cester_assert_true(xstring_cstr_contains(text2, "Hello world"));
})

CESTER_TEST(xstring_cstr_ends_with, _, {
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "string";

    cester_assert_false(xstring_cstr_ends_with(text1, "xtd"));
    cester_assert_false(xstring_cstr_ends_with(text1, "libxtd xstring length and longer"));
    cester_assert_true(xstring_cstr_ends_with(text1, "libxtd xstring length xstring"));
    cester_assert_true(xstring_cstr_ends_with(text1, text1));
    cester_assert_false(xstring_cstr_ends_with(text1, "i"));
    cester_assert_true(xstring_cstr_ends_with(text1, "g"));
    cester_assert_false(xstring_cstr_ends_with(text1, "libxtd"));
    cester_assert_true(xstring_cstr_ends_with(text1, "xstring"));
    cester_assert_true(xstring_cstr_ends_with("test_xstring_utils.h", ".h"));
    cester_assert_true(xstring_cstr_ends_with("test_xstring_utils.h", "h"));
    cester_assert_false(xstring_cstr_ends_with(text2, "Hello"));
    cester_assert_true(xstring_cstr_ends_with(text2, "world"));
    cester_assert_false(xstring_cstr_ends_with(text1, text2));
    cester_assert_true(xstring_cstr_ends_with(text1, text3));
    cester_assert_true(xstring_cstr_ends_with(text2, "Hello world"));
})

CESTER_TEST(xstring_cstr_starts_with, _, {
    char *text1 = "libxtd xstring length xstring";
    char text2[20] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char *text3 = "string";

    cester_assert_false(xstring_cstr_starts_with(text1, "xtd"));
    cester_assert_false(xstring_cstr_starts_with(text1, "libxtd xstring length and longer"));
    cester_assert_true(xstring_cstr_starts_with(text1, "libxtd xstring length xstring"));
    cester_assert_true(xstring_cstr_starts_with(text1, text1));
    cester_assert_false(xstring_cstr_starts_with(text1, "i"));
    cester_assert_true(xstring_cstr_starts_with(text1, "l"));
    cester_assert_true(xstring_cstr_starts_with(text1, "libxtd"));
    cester_assert_false(xstring_cstr_starts_with(text1, "xstring"));
    cester_assert_false(xstring_cstr_starts_with("test_xstring_utils.h", ".h"));
    cester_assert_true(xstring_cstr_starts_with("test_xstring_utils.h", "test_"));
    cester_assert_true(xstring_cstr_starts_with(text2, "Hello"));
    cester_assert_false(xstring_cstr_starts_with(text2, "world"));
    cester_assert_false(xstring_cstr_starts_with(text1, text2));
    cester_assert_false(xstring_cstr_starts_with(text1, text3));
    cester_assert_true(xstring_cstr_starts_with(text2, "Hello world"));
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)

