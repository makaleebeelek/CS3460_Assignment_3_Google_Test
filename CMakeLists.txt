cmake_minimum_required(VERSION 3.12)
project(RandDistributions)

# specify all the source files

set(HEADER_FILES
    distributions.hpp)

set(SOURCE_FILES
    distributions.cpp)

# This is the main target
add_executable(RandDistributions ${HEADER_FILES} ${SOURCE_FILES} main.cpp)


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