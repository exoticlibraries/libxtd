/*!g++ -ansi -pedantic-errors {0} -I. -I../../include/ -I../include -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../../include/ -I../include/  -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../../include/ -I../include -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../../include/ -I../include -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/container/xpair.h>

CESTER_BODY(
typedef struct point_s {
    int x;
    int y;
} Point;

typedef char* str;

SETUP_XPAIR_FOR(int, int)
SETUP_XPAIR_FOR(str, str)
SETUP_XPAIR_FOR(str, int)
SETUP_XPAIR_FOR(str, Point)
SETUP_XPAIR_FOR_WITH_HASH_AND_NEXT(str, char)


bool int_is_less_than_zero(int value)
{
    return value == -1;
}

)

#ifdef __STDC_VERSION__

CESTER_TEST(xpair_initialization_str, _, {
    xpair(int, int) pair_int_int = xpair_new(1, 10);
    xpair(str, str) pair_str_str = xpair_new("name", "exoticlibraries");
    xpair(str, int) pair_str_int = xpair_new("string", 9000);
    xpair(str, Point) pair_str_point = xpair_new("ptr", {});
})

CESTER_TEST(xpair_key_value, _, {
	Point point = { .x = 90, .y = 120 };
    xpair(int, int) pair_int_int = xpair_new(1, 10);
    xpair(str, str) pair_str_str = xpair_new("name", "exoticlibraries");
    xpair(str, int) pair_str_int = xpair_new("string", 9000);
    xpair(str, Point) pair_str_point = xpair_new("ptr", point);
    
	cester_assert_int_eq(xpair_key(pair_int_int), 1);
	cester_assert_str_equal(xpair_key(pair_str_str), "name");
	cester_assert_str_equal(xpair_key(pair_str_int), "string");
	cester_assert_str_equal(xpair_key(pair_str_point), "ptr");
    
	cester_assert_int_eq(xpair_value(pair_int_int), 10);
	cester_assert_str_equal(xpair_value(pair_str_str), "exoticlibraries");
	cester_assert_int_eq(xpair_value(pair_str_int), 9000);
	cester_assert_int_eq(xpair_value(pair_str_point).x, 90);
	cester_assert_int_eq(xpair_value(pair_str_point).y, 120);
})

CESTER_TEST(xpair_set_key_value, _, {
    Point point = { .x = 90, .y = 120 };
    Point monster_point = { .x = 56000, .y = 90828678 };
    xpair(int, int) pair_int_int = xpair_new(1, 10);
    xpair(str, str) pair_str_str = xpair_new("name", "exoticlibraries");
    xpair(str, int) pair_str_int = xpair_new("string", 9000);
    xpair(str, Point) pair_str_point = xpair_new("ptr", point);
    
	cester_assert_int_eq(xpair_key(pair_int_int), 1);
	cester_assert_str_equal(xpair_key(pair_str_str), "name");
	cester_assert_str_equal(xpair_key(pair_str_int), "string");
	cester_assert_str_equal(xpair_key(pair_str_point), "ptr");
    
	cester_assert_int_eq(xpair_value(pair_int_int), 10);
	cester_assert_str_equal(xpair_value(pair_str_str), "exoticlibraries");
	cester_assert_int_eq(xpair_value(pair_str_int), 9000);
	cester_assert_int_eq(xpair_value(pair_str_point).x, 90);
	cester_assert_int_eq(xpair_value(pair_str_point).y, 120);

	xpair_set_value(pair_int_int, 230);
	xpair_set_value(pair_str_str, "libxtd");
	xpair_set_value(pair_str_int, -121);
	xpair_set_value(pair_str_point, monster_point);
    
	cester_assert_int_ne(xpair_value(pair_int_int), 10);
	cester_assert_str_not_equal(xpair_value(pair_str_str), "exoticlibraries");
	cester_assert_int_ne(xpair_value(pair_str_int), 9000);
	cester_assert_int_ne(xpair_value(pair_str_point).x, 90);
	cester_assert_int_ne(xpair_value(pair_str_point).y, 120);

	cester_assert_int_eq(xpair_value(pair_int_int), 230);
	cester_assert_str_equal(xpair_value(pair_str_str), "libxtd");
	cester_assert_int_eq(xpair_value(pair_str_int), -121);
	cester_assert_int_eq(xpair_value(pair_str_point).x, 56000);
	cester_assert_int_eq(xpair_value(pair_str_point).y, 90828678);
})

CESTER_TEST(xpair_with_hash_and_next, _, {
    xpair(str, char) xpair_a = xpair_new("Hay", 'a');
    xpair(str, char) xpair_b = xpair_new_with_hash("Bee", 'b', 231);
    xpair(str, char) xpair_c = xpair_new_with_next("Cee", 'c', &xpair_b);
    xpair(str, char) xpair_d = xpair_new_with_hash_and_next("Dee", 'd', 98724001, &xpair_c);
    
	cester_assert_str_equal(xpair_key(xpair_a), "Hay");
	cester_assert_str_equal(xpair_key(xpair_b), "Bee");
	cester_assert_str_equal(xpair_key(xpair_c), "Cee");
	cester_assert_str_equal(xpair_key(xpair_d), "Dee");

	cester_assert_char_eq(xpair_value(xpair_a), 'a');
	cester_assert_char_eq(xpair_value(xpair_b), 'b');
	cester_assert_char_eq(xpair_value(xpair_c), 'c');
	cester_assert_char_eq(xpair_value(xpair_d), 'd');

	cester_assert_int_eq(xpair_hash(xpair_a), 0);
	cester_assert_int_eq(xpair_hash(xpair_b), 231);
	cester_assert_int_eq(xpair_hash(xpair_c), 0);
	cester_assert_int_eq(xpair_hash(xpair_d), 98724001);

	cester_assert_ptr_equal(xpair_c.next, &xpair_b);
	cester_assert_ptr_equal(xpair_d.next, &xpair_c);
	cester_assert_ptr_equal(&xpair_next(xpair_c), &xpair_b);
	cester_assert_ptr_equal(&xpair_next(xpair_d), &xpair_c);

	cester_assert_char_eq(xpair_value(xpair_next(xpair_c)), 'b');
	cester_assert_char_eq(xpair_value(xpair_next(xpair_d)), 'c');
})

#else

CESTER_TODO_TEST(xpair_initialization_str, _, {
	XINIT_STRUCT_WITH_FIELDS2(Point, point, x = 90, y = 120);
	XINIT_STRUCT_WITH_FIELDS2(xpair(int, int), pair_int_int, key = 1, value = 10);
	XINIT_STRUCT_WITH_FIELDS2(xpair(str, str), pair_str_str, key = "name", value = "exoticlibraries");
	XINIT_STRUCT_WITH_FIELDS2(xpair(str, int), pair_str_int, key = "string", value = 9000);
	XINIT_STRUCT_WITH_FIELDS2(xpair(str, Point), pair_str_point, key = "ptr", value = point);
    
	cester_assert_int_eq(xpair_key(pair_int_int), 1);
	cester_assert_str_equal(xpair_key(pair_str_str), "name");
	cester_assert_str_equal(xpair_key(pair_str_int), "string");
	cester_assert_str_equal(xpair_key(pair_str_point), "ptr");
    
	cester_assert_int_eq(xpair_value(pair_int_int), 10);
	cester_assert_str_equal(xpair_value(pair_str_str), "exoticlibraries");
	cester_assert_int_eq(xpair_value(pair_str_int), 9000);
	cester_assert_int_eq(xpair_value(pair_str_point).x, 90);
	cester_assert_int_eq(xpair_value(pair_str_point).y, 120);
})

#endif

CESTER_OPTIONS(
    CESTER_DEBUG_LEVEL(3);
)

