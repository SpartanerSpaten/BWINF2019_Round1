cmake_minimum_required(VERSION 3.13)
project(Telepaartie)

set(CMAKE_CXX_STANDARD 14)

add_executable(Telepaartie_1 src/main_tele1.cpp src/treenode.hpp src/treenode.cpp src/functions.cpp src/functions.hpp)

add_executable(Telepaartie_2 src/main_tele2.cpp src/functions.cpp src/functions.hpp src/treenode.hpp src/treenode.cpp)