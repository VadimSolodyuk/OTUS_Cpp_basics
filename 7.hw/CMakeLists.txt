cmake_minimum_required(VERSION 3.5)

project(07.homework)

find_package(GTest)

add_executable(containers  src/main.cpp)
add_executable(containers_tests
    test/test_vector.cpp
    test/test_list.cpp
) 

target_include_directories(containers PRIVATE   ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(containers_tests 
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(containers_tests PRIVATE   ${GTEST_BOTH_LIBRARIES})

set_target_properties(
    containers
    containers_tests
    PROPERTIES
        CXX_STANDARD 17 
        CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(
        containers PRIVATE
        /W4
    )
    target_compile_options(
        containers_tests PRIVATE
        /W4
    )
else ()
    target_compile_options(
        containers PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(
        containers_tests PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

