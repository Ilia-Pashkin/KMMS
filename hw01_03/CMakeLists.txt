cmake_minimum_required(VERSION 3.19)
project(hw01_03)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")
include_directories(/usr/include/mpi/)
add_executable(hw01_03 main.cpp)