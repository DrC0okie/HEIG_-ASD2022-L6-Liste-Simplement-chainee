cmake_minimum_required(VERSION 3.15)
project(ASD2022_L6)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wsign-conversion -pedantic")

add_executable(L7d-Splice main.cpp util.cpp)