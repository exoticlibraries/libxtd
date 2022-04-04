/*!gcc {0} -I. -I../../include/ -I../../libxtd/include/ -I../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I. -I../../include/ -I../../../libxtd/include/ -I../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../../include/ -I../../../libcester/include -I../include/ -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/io/fs.h>


#ifdef _WIN32
#define OPTIONAL_ASSERTION_1 cester_assert_false(xio_create_file("/folder/dami.txt"));
#define OPTIONAL_ASSERTION_2 cester_assert_false(xio_create_file("dami.$#&$*$*($)$)!@#$%%^&^*&*(()"));
#else
#define OPTIONAL_ASSERTION_1 cester_assert_false(xio_create_file("C:/folder/dami.txt"));
#define OPTIONAL_ASSERTION_2 cester_assert_false(xio_create_file("C:/dami.$#&$*$*($)$)!@#$%%^&^*&*(()"));
#endif

CESTER_BODY(

char *file_content = "";
size_t file_index = 0;

bool log_file(char c) {
    file_content[file_index++] = c;
    return TRUE;
}

)

CESTER_BEFORE_ALL(test_inst, {
    file_content = (char *) malloc(100 * sizeof(char));
    test_inst->arg = (void *) file_content;
})

CESTER_TEST(xio_create_file, test_inst, {
    cester_assert_true(xio_create_file("dami.txt"));
    OPTIONAL_ASSERTION_1
    OPTIONAL_ASSERTION_2
})

CESTER_TEST(xio_file_exists, test_inst, {
    cester_assert_false(xio_file_exists("new-file.txt"));
    cester_assert_true(xio_file_exists("dami.txt"));
})

CESTER_TEST(xio_read_file_chars_cb, test_inst, {
    FILE *my_file = fopen("dami.txt", "a");

    fprintf(my_file, "Hello World"); fclose(my_file);
    my_file = fopen("dami.txt", "r");
    cester_assert_int_eq(xio_read_file_chars_cb(my_file, XTD_NULL), XTD_PARAM_NULL_ERR);
    cester_assert_int_eq(xio_read_file_chars_cb(XTD_NULL, log_file), XTD_PARAM_NULL_ERR);
    cester_assert_int_eq(xio_read_file_chars_cb(my_file, log_file), XTD_OK);
    cester_assert_str_equal(file_content, "Hello World");

    file_index = 0;
    fclose(my_file);
})

CESTER_TEST(xio_read_file_chars_cb_from_path, test_inst, {
    cester_assert_int_eq(xio_read_file_chars_cb_from_path("dami.txt", log_file), XTD_OK);
    cester_assert_str_equal(file_content, "Hello World");
})

CESTER_TEST(xio_read_all_file_content, test_inst, {
    char content[15];
    FILE *my_file = fopen("dami.txt", "r");

    cester_assert_int_eq(xio_read_file_chars_cb(my_file, XTD_NULL), XTD_PARAM_NULL_ERR);
    cester_assert_int_eq(xio_read_file_chars_cb(XTD_NULL, log_file), XTD_PARAM_NULL_ERR);
    cester_assert_int_eq(xio_read_all_file_content(my_file, content), XTD_OK);
    cester_assert_str_equal(content, "Hello World");

    fclose(my_file);
})

CESTER_TEST(xio_read_all_file_content_from_path, test_inst, {
    char content[15];
    cester_assert_int_eq(xio_read_all_file_content_from_path("dami.txt", content), XTD_OK);
    cester_assert_str_equal(content, "Hello World");
})

CESTER_TEST(xio_delete_file, test_inst, {
    cester_assert_true(xio_delete_file("dami.txt"));
    cester_assert_false(xio_delete_file("dami.txt"));
})

CESTER_AFTER_ALL(test_inst, {
    free(test_inst->arg);
})

