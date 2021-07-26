/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I.-I../include/  -I../../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../include/ -I../../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/xstring.h>
#include <exotic/xtd/xiterator.h>

#define cester_assert_str_equal_(x,y) cester_assert_true(xstring_cstr_equals(x,y))

CESTER_TEST(xstring_cstr_escape_sequences, _, {
    char *value;
    size_t err_pos;
    char *cstr1 = "Hello\tWorld";
    char *cstr2 = "Hello\\tWorld";
    char *cstr3 = "Hello\\qWorld";
    char *cstr4 = "Tab\t\tNew Line\tCariage \rAlert beep\aBackspacee\bEscape char\eFormfeed PageBreak\fVertical tab \vBackslash\\Apostle\'Double quote\"Question Mark \?";
    char *cstr5 = "Tab\\t\\tNew Line\\tCariage \\rAlert beep\\aBackspacee\\bEscape char\\eFormfeed PageBreak\\fVertical tab \\vBackslash\\\\Apostle\\'Double quote\\\"Question Mark \\?";
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    cester_assert_str_equal(cstr1, "Hello\tWorld");
    cester_assert_str_not_equal(cstr2, "Hello\tWorld");
    cester_assert_uint_eq(xstring_cstr_escape_sequences(cstr2, allocator, &value, XTD_NULL), XTD_OK);
    cester_assert_str_equal(value, cstr1);
    cester_assert_str_equal(value, "Hello\tWorld");
    cester_assert_uint_ne(xstring_cstr_escape_sequences(cstr3, allocator, &value, XTD_NULL), XTD_OK);
    cester_assert_uint_eq(xstring_cstr_escape_sequences(cstr3, allocator, &value, &err_pos), XTD_PARSING_ERR);
    cester_assert_int_eq(err_pos, 6);
    cester_assert_char_eq(cstr3[err_pos], 'q');
    cester_assert_str_equal(cstr4, "Tab\t\tNew Line\tCariage \rAlert beep\aBackspacee\bEscape char\eFormfeed PageBreak\fVertical tab \vBackslash\\Apostle\'Double quote\"Question Mark \?");
    cester_assert_str_not_equal(cstr5, cstr4);
    cester_assert_uint_eq(xstring_cstr_escape_sequences(cstr5, allocator, &value, &err_pos), XTD_OK);
    cester_assert_str_equal(value, cstr4);
    cester_assert_str_equal(value, "Tab\t\tNew Line\tCariage \rAlert beep\aBackspacee\bEscape char\eFormfeed PageBreak\fVertical tab \vBackslash\\Apostle\'Double quote\"Question Mark \?");
})

CESTER_TEST(xstring_cstr_unescape_sequences, _, {
    char *value;
    size_t err_pos;
    char *cstr1 = "Hello\tWorld";
    char *cstr2 = "Hello\\tWorld";
    char *cstr3 = "Hello\\qWorld";
    char *cstr4 = "Tab\t\tNew Line\tCariage \rAlert beep\aBackspacee\bEscape char\eFormfeed PageBreak\fVertical tab \vBackslash\\Apostle\'Double quote\"Question Mark \?";
    char *cstr5 = "Tab\\t\\tNew Line\\tCariage \\rAlert beep\\aBackspacee\\bEscape char\\eFormfeed PageBreak\\fVertical tab \\vBackslash\\\\Apostle\\'Double quote\\\"Question Mark \\?";
    XAllocator allocator;
    allocator.memory_malloc = malloc;
    allocator.memory_calloc = calloc;
    allocator.memory_realloc = realloc;
    allocator.memory_free = free;

    cester_assert_str_equal(cstr2, "Hello\\tWorld");
    cester_assert_str_not_equal(cstr2, "Hello\tWorld");
    cester_assert_uint_eq(xstring_cstr_unescape_sequences(cstr1, allocator, &value, XTD_NULL), XTD_OK);
    cester_assert_str_equal(value, cstr2);
    cester_assert_str_equal(value, "Hello\\tWorld");
    cester_assert_str_equal(cstr5, "Tab\\t\\tNew Line\\tCariage \\rAlert beep\\aBackspacee\\bEscape char\\eFormfeed PageBreak\\fVertical tab \\vBackslash\\\\Apostle\\'Double quote\\\"Question Mark \\?");
    cester_assert_str_not_equal(cstr5, cstr4);
    cester_assert_uint_eq(xstring_cstr_unescape_sequences(cstr4, allocator, &value, &err_pos), XTD_OK);
    cester_assert_str_equal(value, cstr5);
    cester_assert_str_equal(value, "Tab\\t\\tNew Line\\tCariage \\rAlert beep\\aBackspacee\\bEscape char\\eFormfeed PageBreak\\fVertical tab \\vBackslash\\\\Apostle\\'Double quote\\\"Question Mark \\?");
})

CESTER_TODO_TEST(xstring_cstr_escape_sequences_extended, _, {
    char *cstr1 = "Hello\tWorld";

    cester_assert_str_equal_(cstr1, "Hello\tWorld");
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)

