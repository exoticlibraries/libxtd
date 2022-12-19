/*!gcc -ansi -pedantic-errors {0} -I. -I../../include/ -I../include/  -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I. -I../../include/ -I../include -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../../include/ -I../include -I../../../libcester/include -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../../include/ -I../include -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/util/xtypes_bounds.h>

CESTER_TEST(xbound_char_is_uppercase, _, {
    cester_assert_true(xbound_char_is_uppercase('A'));
    cester_assert_true(xbound_char_is_uppercase('B'));
    cester_assert_true(xbound_char_is_uppercase('C'));
    cester_assert_true(xbound_char_is_uppercase('D'));
    cester_assert_true(xbound_char_is_uppercase('E'));
    cester_assert_true(xbound_char_is_uppercase('F'));
    cester_assert_true(xbound_char_is_uppercase('G'));
    cester_assert_true(xbound_char_is_uppercase('H'));
    cester_assert_true(xbound_char_is_uppercase('I'));
    cester_assert_true(xbound_char_is_uppercase('J'));
    cester_assert_true(xbound_char_is_uppercase('K'));
    cester_assert_true(xbound_char_is_uppercase('L'));
    cester_assert_true(xbound_char_is_uppercase('M'));
    cester_assert_true(xbound_char_is_uppercase('N'));
    cester_assert_true(xbound_char_is_uppercase('O'));
    cester_assert_true(xbound_char_is_uppercase('P'));
    cester_assert_true(xbound_char_is_uppercase('Q'));
    cester_assert_true(xbound_char_is_uppercase('R'));
    cester_assert_true(xbound_char_is_uppercase('S'));
    cester_assert_true(xbound_char_is_uppercase('T'));
    cester_assert_true(xbound_char_is_uppercase('U'));
    cester_assert_true(xbound_char_is_uppercase('V'));
    cester_assert_true(xbound_char_is_uppercase('W'));
    cester_assert_true(xbound_char_is_uppercase('X'));
    cester_assert_true(xbound_char_is_uppercase('Y'));
    cester_assert_true(xbound_char_is_uppercase('Z'));
    cester_assert_false(xbound_char_is_uppercase('a'));
    cester_assert_false(xbound_char_is_uppercase('b'));
    cester_assert_false(xbound_char_is_uppercase('c'));
    cester_assert_false(xbound_char_is_uppercase('d'));
    cester_assert_false(xbound_char_is_uppercase('e'));
    cester_assert_false(xbound_char_is_uppercase('f'));
    cester_assert_false(xbound_char_is_uppercase('g'));
    cester_assert_false(xbound_char_is_uppercase('h'));
    cester_assert_false(xbound_char_is_uppercase('i'));
    cester_assert_false(xbound_char_is_uppercase('j'));
    cester_assert_false(xbound_char_is_uppercase('k'));
    cester_assert_false(xbound_char_is_uppercase('l'));
    cester_assert_false(xbound_char_is_uppercase('m'));
    cester_assert_false(xbound_char_is_uppercase('n'));
    cester_assert_false(xbound_char_is_uppercase('o'));
    cester_assert_false(xbound_char_is_uppercase('p'));
    cester_assert_false(xbound_char_is_uppercase('q'));
    cester_assert_false(xbound_char_is_uppercase('r'));
    cester_assert_false(xbound_char_is_uppercase('s'));
    cester_assert_false(xbound_char_is_uppercase('t'));
    cester_assert_false(xbound_char_is_uppercase('u'));
    cester_assert_false(xbound_char_is_uppercase('v'));
    cester_assert_false(xbound_char_is_uppercase('w'));
    cester_assert_false(xbound_char_is_uppercase('x'));
    cester_assert_false(xbound_char_is_uppercase('y'));
    cester_assert_false(xbound_char_is_uppercase('z'));
})

CESTER_TEST(xbound_char_is_lowercase, _, {
    cester_assert_true(xbound_char_is_lowercase('a'));
    cester_assert_true(xbound_char_is_lowercase('b'));
    cester_assert_true(xbound_char_is_lowercase('c'));
    cester_assert_true(xbound_char_is_lowercase('d'));
    cester_assert_true(xbound_char_is_lowercase('e'));
    cester_assert_true(xbound_char_is_lowercase('f'));
    cester_assert_true(xbound_char_is_lowercase('g'));
    cester_assert_true(xbound_char_is_lowercase('h'));
    cester_assert_true(xbound_char_is_lowercase('i'));
    cester_assert_true(xbound_char_is_lowercase('j'));
    cester_assert_true(xbound_char_is_lowercase('k'));
    cester_assert_true(xbound_char_is_lowercase('l'));
    cester_assert_true(xbound_char_is_lowercase('m'));
    cester_assert_true(xbound_char_is_lowercase('n'));
    cester_assert_true(xbound_char_is_lowercase('o'));
    cester_assert_true(xbound_char_is_lowercase('p'));
    cester_assert_true(xbound_char_is_lowercase('q'));
    cester_assert_true(xbound_char_is_lowercase('r'));
    cester_assert_true(xbound_char_is_lowercase('s'));
    cester_assert_true(xbound_char_is_lowercase('t'));
    cester_assert_true(xbound_char_is_lowercase('u'));
    cester_assert_true(xbound_char_is_lowercase('v'));
    cester_assert_true(xbound_char_is_lowercase('w'));
    cester_assert_true(xbound_char_is_lowercase('x'));
    cester_assert_true(xbound_char_is_lowercase('y'));
    cester_assert_true(xbound_char_is_lowercase('z'));
    cester_assert_false(xbound_char_is_lowercase('A'));
    cester_assert_false(xbound_char_is_lowercase('B'));
    cester_assert_false(xbound_char_is_lowercase('C'));
    cester_assert_false(xbound_char_is_lowercase('D'));
    cester_assert_false(xbound_char_is_lowercase('E'));
    cester_assert_false(xbound_char_is_lowercase('F'));
    cester_assert_false(xbound_char_is_lowercase('G'));
    cester_assert_false(xbound_char_is_lowercase('H'));
    cester_assert_false(xbound_char_is_lowercase('I'));
    cester_assert_false(xbound_char_is_lowercase('J'));
    cester_assert_false(xbound_char_is_lowercase('K'));
    cester_assert_false(xbound_char_is_lowercase('L'));
    cester_assert_false(xbound_char_is_lowercase('M'));
    cester_assert_false(xbound_char_is_lowercase('N'));
    cester_assert_false(xbound_char_is_lowercase('O'));
    cester_assert_false(xbound_char_is_lowercase('P'));
    cester_assert_false(xbound_char_is_lowercase('Q'));
    cester_assert_false(xbound_char_is_lowercase('R'));
    cester_assert_false(xbound_char_is_lowercase('S'));
    cester_assert_false(xbound_char_is_lowercase('T'));
    cester_assert_false(xbound_char_is_lowercase('U'));
    cester_assert_false(xbound_char_is_lowercase('V'));
    cester_assert_false(xbound_char_is_lowercase('W'));
    cester_assert_false(xbound_char_is_lowercase('X'));
    cester_assert_false(xbound_char_is_lowercase('Y'));
    cester_assert_false(xbound_char_is_lowercase('Z'));
})

CESTER_TEST(xbound_char_is_alpha, _, {
    cester_assert_true(xbound_char_is_alpha('a'));
    cester_assert_true(xbound_char_is_alpha('b'));
    cester_assert_true(xbound_char_is_alpha('c'));
    cester_assert_true(xbound_char_is_alpha('A'));
    cester_assert_true(xbound_char_is_alpha('B'));
    cester_assert_true(xbound_char_is_alpha('C'));
})

CESTER_TEST(xbound_char_is_digit, _, {
    cester_assert_false(xbound_char_is_digit('a'));
    cester_assert_false(xbound_char_is_digit('A'));
    cester_assert_true(xbound_char_is_digit('0'));
    cester_assert_true(xbound_char_is_digit('1'));
    cester_assert_true(xbound_char_is_digit('2'));
    cester_assert_true(xbound_char_is_digit('3'));
    cester_assert_true(xbound_char_is_digit('4'));
    cester_assert_true(xbound_char_is_digit('5'));
    cester_assert_true(xbound_char_is_digit('6'));
    cester_assert_true(xbound_char_is_digit('7'));
    cester_assert_true(xbound_char_is_digit('8'));
    cester_assert_true(xbound_char_is_digit('9'));
})

CESTER_TEST(xbound_char_is_alphanum, _, {
    cester_assert_true(xbound_char_is_alphanum('a'));
    cester_assert_true(xbound_char_is_alphanum('b'));
    cester_assert_true(xbound_char_is_alphanum('c'));
    cester_assert_true(xbound_char_is_alphanum('A'));
    cester_assert_true(xbound_char_is_alphanum('B'));
    cester_assert_true(xbound_char_is_alphanum('C'));
    cester_assert_true(xbound_char_is_alphanum('1'));
    cester_assert_true(xbound_char_is_alphanum('2'));
    cester_assert_true(xbound_char_is_alphanum('8'));
    cester_assert_true(xbound_char_is_alphanum('9'));
})

CESTER_TEST(xbound_char_is_white_space, _, {
    cester_assert_false(xbound_char_is_white_space('a'));
    cester_assert_false(xbound_char_is_white_space('A'));
    cester_assert_false(xbound_char_is_white_space('>'));
    cester_assert_false(xbound_char_is_white_space('!'));
    cester_assert_true(xbound_char_is_white_space(' '));
    cester_assert_true(xbound_char_is_white_space('\n'));
    cester_assert_true(xbound_char_is_white_space('\t'));
    cester_assert_true(xbound_char_is_white_space('\v'));
    cester_assert_true(xbound_char_is_white_space('\f'));
    cester_assert_true(xbound_char_is_white_space('\r'));
})

CESTER_TEST(xbound_char_is_cntrl, _, {
    cester_assert_false(xbound_char_is_cntrl('a'));
    cester_assert_false(xbound_char_is_cntrl('A'));
    cester_assert_false(xbound_char_is_cntrl('>'));
    cester_assert_false(xbound_char_is_cntrl('!'));
    cester_assert_true(xbound_char_is_cntrl('\n'));
    cester_assert_true(xbound_char_is_cntrl('\b'));
    cester_assert_true(xbound_char_is_cntrl('\v'));
    cester_assert_true(xbound_char_is_cntrl('\r'));
})

CESTER_TEST(xbound_char_is_printable, _, {
    cester_assert_true(xbound_char_is_printable('a'));
    cester_assert_true(xbound_char_is_printable('A'));
    cester_assert_true(xbound_char_is_printable('>'));
    cester_assert_true(xbound_char_is_printable('!'));
    cester_assert_false(xbound_char_is_printable('\n'));
    cester_assert_false(xbound_char_is_printable('\b'));
    cester_assert_false(xbound_char_is_printable('\v'));
    cester_assert_false(xbound_char_is_printable('\r'));
})

CESTER_TEST(xbound_char_is_graphical, _, {
    int index;
    cester_assert_true(xbound_char_is_graphical('a'));
    cester_assert_true(xbound_char_is_graphical('A'));
    cester_assert_true(xbound_char_is_graphical('>'));
    cester_assert_true(xbound_char_is_graphical('!'));
    cester_assert_false(xbound_char_is_graphical('\n'));
    cester_assert_false(xbound_char_is_graphical('\b'));
    cester_assert_false(xbound_char_is_graphical('\v'));
    cester_assert_false(xbound_char_is_graphical('\r'));
    for (index = 33; index < 127; index++) {
        cester_assert_true(xbound_char_is_graphical(index));
    }
})




