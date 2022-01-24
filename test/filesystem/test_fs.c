/*!gcc {0} -I. -I../../include/ -I../../libxtd/include/ -I../include/ -I../../../libcester/include -o out; ./out */
/*!g++ -ansi -pedantic-errors {0} -I. -I../../include/ -I../../../libxtd/include/ -I../include/ -I../../../libcester/include -o out; ./out */
/*!gcc {0} -I. -I../../include/ -I../../../libcester/include -I../include/ -o out; ./out */
/*!g++ -std=c++11 {0} -I. -I../../include/ -I../include/ -I../../../libcester/include -o out; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/io/fs.h>

#ifdef _WIN32
#define TEST_ASSERTION_1 cester_assert_str_equal(full_file_path, "C:\\");
#endif
#ifdef _WIN32
#define TEST_ASSERTION_2 cester_assert_str_equal(full_file_path, "Y:\\..:\\Users\\thecarisma");
#endif


CESTER_TEST(xio_get_current_dir, test_inst, {
    XAllocator allocator;
    char *current_directory;
    
    init_xallocator(&allocator);
    cester_assert_uint_eq(xio_get_current_dir(allocator, XTD_NULL), XTD_PARAM_NULL_ERR);
    cester_assert_uint_eq(xio_get_current_dir(allocator, &current_directory), XTD_OK);
    cester_assert_str_not_equal(current_directory, XTD_NULL);
    printf("Current Folder: %s\n", current_directory);
    allocator.memory_free(current_directory);
})


CESTER_TEST(xio_absolute_path_name, test_inst, {
    char full_file_path[260];
    enum x_stat status;

    status = xio_absolute_path_name(test_inst->argv[0], full_file_path);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_not_equal(full_file_path, XTD_NULL);

    status = xio_absolute_path_name("C:../../.././../../../.././//.../../../.././../../", full_file_path);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_not_equal(full_file_path, XTD_NULL);
    TEST_ASSERTION_1

    status = xio_absolute_path_name("Y:..:/Users/thecarisma", full_file_path);
    cester_assert_uint_eq(status, XTD_OK);
    cester_assert_str_not_equal(full_file_path, XTD_NULL);
    TEST_ASSERTION_2
})

/* TODO treat relative to file in another parent folder, not just starts with*/
CESTER_TEST(xio_relative_path_name, test_inst, {
    char *value;
    XAllocator allocator;
    char *file_name1 = "C:/";
    char *file_name2 = "C:\\Users\\name\\";
    char *file_name3 = "C:\\Users\\name\\Documents\\home.blade.php";
    char *file_name4 = "/usr/lib/";
    char *file_name5 = "/usr/lib/exotic/cester.h";

    init_xallocator(&allocator);
    cester_assert_uint_eq(xio_relative_path_name(allocator, XTD_NULL, XTD_NULL, '/', XTD_NULL), XTD_PARAM_NULL_ERR);
    cester_assert_uint_eq(xio_relative_path_name(allocator, file_name1, file_name2, '/', XTD_NULL), XTD_PARAM_NULL_ERR);
    cester_assert_uint_eq(xio_relative_path_name(allocator, file_name1, file_name2, '/', &value), XTD_OK);
    cester_assert_str_equal(value, "Users/name/"); allocator.memory_free(value);
    cester_assert_uint_eq(xio_relative_path_name(allocator, file_name1, file_name2, '\\', &value), XTD_OK);
    cester_assert_str_equal(value, "Users\\name\\"); allocator.memory_free(value);
    cester_assert_uint_eq(xio_relative_path_name(allocator, file_name2, file_name3, '\\', &value), XTD_OK);
    cester_assert_str_equal(value, "Documents\\home.blade.php"); allocator.memory_free(value);
    cester_assert_uint_eq(xio_relative_path_name(allocator, file_name2, file_name3, '/', &value), XTD_OK);
    cester_assert_str_equal(value, "Documents/home.blade.php"); allocator.memory_free(value);
    cester_assert_uint_eq(xio_relative_path_name(allocator, file_name4, file_name5, '/', &value), XTD_OK);
    cester_assert_str_equal(value, "exotic/cester.h"); allocator.memory_free(value);
})

CESTER_TEST(xio_file_name_from_path, test_inst, {
    char *file_name1 = "./../../test_fs.c";
    char *file_name2 = "C:\\Users\\name\\Documents\\home.blade.php";
    char *file_name3 = "/tmp\\noextension";
    char *file_name4 = "nofilename";
    char file_name_only[20];

    cester_assert_uint_eq(xio_file_name_from_path(XTD_NULL, file_name_only), XTD_PARAM_NULL_ERR);
    cester_assert_uint_eq(xio_file_name_from_path(file_name1, XTD_NULL), XTD_PARAM_NULL_ERR);
    cester_assert_uint_eq(xio_file_name_from_path(XTD_NULL, XTD_NULL), XTD_PARAM_NULL_ERR);
    cester_assert_uint_eq(xio_file_name_from_path(file_name1, file_name_only), XTD_OK);
    cester_assert_str_equal(file_name_only, "test_fs.c");
    cester_assert_uint_eq(xio_file_name_from_path(file_name2, file_name_only), XTD_OK);
    cester_assert_str_equal(file_name_only, "home.blade.php");
    cester_assert_uint_eq(xio_file_name_from_path(file_name3, file_name_only), XTD_OK);
    cester_assert_str_equal(file_name_only, "noextension");
    cester_assert_uint_eq(xio_file_name_from_path(file_name4, file_name_only), XTD_OK);
    cester_assert_str_equal(file_name_only, "nofilename");
})

CESTER_TEST(xio_file_name_only, test_inst, {
    char *file_name1 = "test_fs.c";
    char *file_name2 = "home.blade.php";
    char *file_name3 = "noextension";
    char file_name_only[11];

    cester_assert_uint_eq(xio_file_name_only(XTD_NULL, file_name_only), XTD_PARAM_NULL_ERR);
    cester_assert_uint_eq(xio_file_name_only(file_name1, XTD_NULL), XTD_PARAM_NULL_ERR);
    cester_assert_uint_eq(xio_file_name_only(XTD_NULL, XTD_NULL), XTD_PARAM_NULL_ERR);
    cester_assert_uint_eq(xio_file_name_only(file_name1, file_name_only), XTD_OK);
    cester_assert_str_equal(file_name_only, "test_fs");
    cester_assert_uint_eq(xio_file_name_only(file_name2, file_name_only), XTD_OK);
    cester_assert_str_equal(file_name_only, "home.blade");
    cester_assert_uint_eq(xio_file_name_only(file_name3, file_name_only), XTD_OK);
    cester_assert_str_equal(file_name_only, "noextension");
})

CESTER_TEST(xio_file_extension, test_inst, {
    char *file_name1 = "test_fs.c";
    char *file_name2 = "home.blade.php";
    char *file_name3 = "noextension";
    char file_name_only[11];

    cester_assert_uint_eq(xio_file_extension(XTD_NULL, file_name_only), XTD_PARAM_NULL_ERR);
    cester_assert_uint_eq(xio_file_extension(file_name1, XTD_NULL), XTD_PARAM_NULL_ERR);
    cester_assert_uint_eq(xio_file_extension(XTD_NULL, XTD_NULL), XTD_PARAM_NULL_ERR);
    cester_assert_uint_eq(xio_file_extension(file_name1, file_name_only), XTD_OK);
    cester_assert_str_equal(file_name_only, ".c");
    cester_assert_uint_eq(xio_file_extension(file_name2, file_name_only), XTD_OK);
    cester_assert_str_equal(file_name_only, ".php");
    cester_assert_uint_eq(xio_file_extension(file_name3, file_name_only), XTD_OK);
    cester_assert_str_equal(file_name_only, "");
})

/* TODO normalize should normalize file in other parent other folder not just slash */
CESTER_TEST(xio_normalize_path, test_inst, {
    char *value;
    XAllocator allocator;
    char *file_name1 = "C:/User/thecarisma/text.txt";
    char *file_name2 = "C:\\/\\User/\\/thecarisma\\folder/text.txt";
    char *file_name3 = "/usr/dir/dist.zip.tmp";
    char *file_name4 = "\\/usr///////home/dir/\\dist.zip.tmp//\\//\\\\\\///\\\\////\\";

    init_xallocator(&allocator);
    cester_assert_uint_eq(xio_normalize_path(allocator, XTD_NULL, '\\', XTD_NULL), XTD_PARAM_NULL_ERR);
    cester_assert_uint_eq(xio_normalize_path(allocator, file_name1, '/', XTD_NULL), XTD_PARAM_NULL_ERR);
    cester_assert_uint_eq(xio_normalize_path(allocator, file_name1, '/', &value), XTD_OK);
    cester_assert_str_equal(value, "C:/User/thecarisma/text.txt"); allocator.memory_free(value);
    cester_assert_uint_eq(xio_normalize_path(allocator, file_name1, '\\', &value), XTD_OK);
    cester_assert_str_equal(value, "C:\\User\\thecarisma\\text.txt"); allocator.memory_free(value);
    cester_assert_uint_eq(xio_normalize_path(allocator, file_name2, '/', &value), XTD_OK);
    cester_assert_str_equal(value, "C:/User/thecarisma/folder/text.txt"); allocator.memory_free(value);
    cester_assert_uint_eq(xio_normalize_path(allocator, file_name2, '\\', &value), XTD_OK);
    cester_assert_str_equal(value, "C:\\User\\thecarisma\\folder\\text.txt"); allocator.memory_free(value);
    cester_assert_uint_eq(xio_normalize_path(allocator, file_name3, '\\', &value), XTD_OK);
    cester_assert_str_equal(value, "\\usr\\dir\\dist.zip.tmp"); allocator.memory_free(value);
    cester_assert_uint_eq(xio_normalize_path(allocator, file_name4, '\\', &value), XTD_OK);
    cester_assert_str_equal(value, "\\usr\\home\\dir\\dist.zip.tmp\\"); allocator.memory_free(value);
    cester_assert_uint_eq(xio_normalize_path(allocator, file_name4, '/', &value), XTD_OK);
    cester_assert_str_equal(value, "/usr/home/dir/dist.zip.tmp/"); allocator.memory_free(value);
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(3);
)

