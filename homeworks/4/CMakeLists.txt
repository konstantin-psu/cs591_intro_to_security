cmake_minimum_required(VERSION 3.3)
project(sec_hw4)

set(CMAKE_C_COMPILER "/usr/bin/gcc")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES main.c)
add_executable(sec_hw4 ${SOURCE_FILES})
target_link_libraries (sec_hw4 ssl crypto)
