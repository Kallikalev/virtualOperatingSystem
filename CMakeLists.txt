cmake_minimum_required(VERSION 3.23)
project(virtualOperatingSystem)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(virtualOperatingSystem
        main.cpp
        Memory.h
        Memory.cpp utils.cpp)
