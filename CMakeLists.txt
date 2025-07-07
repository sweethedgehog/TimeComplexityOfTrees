cmake_minimum_required(VERSION 3.29)
project(Last_stand_2025)

set(CMAKE_CXX_STANDARD 20)

add_executable(Last_stand_2025 src/Tester.cpp
        src/BTree.cpp
        src/BTree.h
        src/Generator.cpp
        src/Generator.h)
