cmake_minimum_required(VERSION 3.17)
project(6)

set(CMAKE_CXX_STANDARD 17)
include_directories(/usr/include/mpich-x86_64/)
SET(CMAKE_C_COMPILER mpicc)
SET(CMAKE_CXX_COMPILER mpicxx)

add_executable(6 main.cpp)