cmake_minimum_required( VERSION 3.0 )

project(adventofcode_project)

add_executable(adventofcode)

target_sources(adventofcode PUBLIC
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

set_property(TARGET adventofcode PROPERTY CXX_STANDARD 20)