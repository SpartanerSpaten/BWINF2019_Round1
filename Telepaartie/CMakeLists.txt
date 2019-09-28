cmake_minimum_required(VERSION 3.13)
project(Telepaartie)

set(CMAKE_CXX_STANDARD 14)

add_executable(Telepaartie main.cpp src/container.h src/container.cpp src/treenode.h src/treenode.cpp)