cmake_minimum_required(VERSION 2.8)
project(questioneer)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")


add_executable(attack01 attack01.c)
add_executable(attack02 attack02.c)
add_executable(attack04 attack04.c)
add_executable(login01 login01.c)
add_executable(login03 login03.c)
target_link_libraries(attack02 crypto)
target_link_libraries(login01 crypto)
