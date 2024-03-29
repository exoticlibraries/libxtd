#!cmake CMakeLists.txt -G"Unix Makefiles"; make
cmake_minimum_required(VERSION 3.17)
project(libxtd_tests VERSION 1.0)

set(FILE_EXT "")
set(INCLUDE_PATHS -I${PWD}/../../include/ -I${PWD}/../include/ -I../../include/ -I../include/)
include_directories(${PWD}/../../include/ ${PWD}/../include/ ../../include/ ../include/)
add_executable(cester_test ./empty_c_file.c)
set_target_properties(cester_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ./build/ )
set(echo_var "")

IF (WIN32)
    set(FILE_EXT ".exe")
ENDIF()

# build and run the tests
file(GLOB files "./*/test_*.c" "./*/*/test_*.c")
foreach(filepath ${files})
    message(STATUS "FilePath: " ${filepath}  )
    get_filename_component(filename ${filepath} NAME)
    get_filename_component(filenameonly ${filepath} NAME_WLE)
    if("${filepath}" MATCHES "test_xstring_escape_sequence")
        set(echo_var "echo")
    endif()
    
    add_custom_target(${filenameonly}__
        
        COMMAND echo -------------------------------------------
        COMMAND echo Compiling ${filenameonly} 
        COMMAND echo -------------------------------------------
        
        # clang 
        COMMAND ${echo_var} clang -I. ${INCLUDE_PATHS} ${filepath} -o ./build/${filenameonly}_clang${FILE_EXT}
        COMMAND ${echo_var} clang -ansi -pedantic-errors -I. ${INCLUDE_PATHS} ${filepath} -o ./build/${filenameonly}_clang_ansi${FILE_EXT}
        #COMMAND ${echo_var} clang++ -I. ${INCLUDE_PATHS} ${filepath} -o ./build/${filenameonly}_clang_cpp${FILE_EXT}
    
        # gcc
        COMMAND ${echo_var} gcc -I. ${INCLUDE_PATHS} ${filepath} -o ./build/${filenameonly}_gcc${FILE_EXT}
        COMMAND ${echo_var} gcc -ansi -pedantic-errors -I. ${INCLUDE_PATHS} ${filepath} -o ./build/${filenameonly}_gcc_ansi${FILE_EXT}
        #COMMAND ${echo_var} g++ -I. ${INCLUDE_PATHS} ${filepath} -o ./build/${filenameonly}_gcc_cpp${FILE_EXT}
    )
    
    add_custom_command(TARGET cester_test
        POST_BUILD
        
        COMMAND echo -------------------------------------------
        COMMAND echo Running ${filenameonly} 
        COMMAND echo -------------------------------------------
        
        # clang
        COMMAND ${echo_var} ./build/${filenameonly}_clang${FILE_EXT}
        COMMAND ${echo_var} ./build/${filenameonly}_clang_ansi${FILE_EXT} --cester-output=junitxml
        #COMMAND ${echo_var} ./build/${filenameonly}_clang_cpp${FILE_EXT} --cester-output=tap
        
        # gcc
        COMMAND ${echo_var} ./build/${filenameonly}_gcc${FILE_EXT}
        COMMAND ${echo_var} ./build/${filenameonly}_gcc_ansi${FILE_EXT} --cester-output=junitxml
        #COMMAND ${echo_var} ./build/${filenameonly}_gcc_cpp${FILE_EXT} --cester-output=tapV13
    )
    
    add_dependencies(cester_test ${filenameonly}__)
endforeach()

