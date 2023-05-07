cmake_minimum_required(VERSION 3.5)

project(03.homework)

add_executable(
	3.homework
	3.homework.cpp
    function.cpp
)

set_target_properties(3.homework PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
    )