# CS 3460 Assignment 3 CMake
# Makalee Beelek

cmake_minimum_required(VERSION 3.12)
project(RandDistributions)

# specify all the source files

set(HEADER_FILES
    distributions.hpp)

set(SOURCE_FILES
    distributions.cpp)

set(UNIT_TEST_FILES
    TestDistributions.cpp)

# This is the main target
add_executable(RandDistributions ${HEADER_FILES} ${SOURCE_FILES} main.cpp)
add_executable(UnitTestRunner  ${HEADER_FILES} ${SOURCE_FILES} ${UNIT_TEST_FILES})

# Make C++ 20 standard for the project
set_property(TARGET RandDistributions PROPERTY CXX_STANDARD 20)

# Show all warnings wether using MSVC or GNU
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(RandDistributions PRIVATE /W4 /permissive-)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(RandDistributions PRIVATE -Wall -Wextra -pedantic)
endif()

# run clang-format over all files
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    unset(SOURCE_FILES_PATHS)
    foreach(SOURCE_FILE ${HEADER_FILES} ${SOURCE_FILES} main.cpp)
        get_source_file_property(WHERE ${SOURCE_FILE} LOCATION)
        set(SOURCE_FILES_PATHS ${SOURCE_FILES_PATHS} ${WHERE})
    endforeach()

    add_custom_target(
        ClangFormat
        COMMAND ${CLANG_FORMAT}
        -i
        -style=file
        ${SOURCE_FILES_PATHS}
    )

    add_dependencies(RandDistributions ClangFormat)
else()
    message("Unable to find clang-format")
endif()

#
# Add GoogleTest
#
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# Now simply link against gtest or gtest_main as needed. Eg
target_link_libraries(UnitTestRunner gtest_main)