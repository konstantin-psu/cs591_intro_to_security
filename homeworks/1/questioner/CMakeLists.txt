cmake_minimum_required(VERSION 2.8)
project(questioneer)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(SOURCE_FILES questioner.c)
add_executable(app_exe ${SOURCE_FILES})