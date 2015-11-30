cmake_minimum_required(VERSION 3.3)
project(sec_hw4)

set(CMAKE_C_COMPILER "/usr/bin/gcc")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_executable(attack01 attack01.c)
add_executable(attack02 attack02.c)
add_executable(attack04 attack04.c)
add_executable(login01 login01.c)
add_executable(login03 login03.c)
target_link_libraries(attack02 crypto)
target_link_libraries(login01 crypto)
