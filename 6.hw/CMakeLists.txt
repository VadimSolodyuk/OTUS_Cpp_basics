cmake_minimum_required(VERSION 3.5)

project(06.homework)

add_executable (containers src/main.cpp)

target_include_directories(containers PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(containers
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(containers PRIVATE 
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(containers PRIVATE
        /EHsc
        /W4
        /WX
    )
endif()


