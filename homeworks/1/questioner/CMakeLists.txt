cmake_minimum_required(VERSION 2.8)
project(questioneer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES main.cpp)
add_executable(questioneer_exe ${SOURCE_FILES})