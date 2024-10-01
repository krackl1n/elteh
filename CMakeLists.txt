cmake_minimum_required(VERSION 3.29)
project(elteh)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(elteh
    Core.cpp
    Core.h
    elteh.cpp)

