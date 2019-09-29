cmake_minimum_required(VERSION 3.13)
project(Telepaartie)

set(CMAKE_CXX_STANDARD 14)

add_executable(Telepaartie main.cpp src/treenode.h src/treenode.cpp src/functions.cpp src/functions.h)