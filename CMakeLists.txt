cmake_minimum_required(VERSION 3.29)
project(Last_stand_2025)

set(CMAKE_CXX_STANDARD 20)

add_executable(Last_stand_2025 src/Tester.cpp
        src/Treap.cpp
        src/Treap.h
        src/Generator.cpp
        src/Generator.h
        src/CoolTreap.h
        src/BTree.cpp
        src/CoolBTree.h)
