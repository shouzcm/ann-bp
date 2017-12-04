cmake_minimum_required(VERSION 3.9)
project(ann_bp)

set(CMAKE_CXX_STANDARD 11)

add_executable(ann_bp demo02/BpNet.h demo02/BpNet.cpp demo02/main.cpp)

#add_executable(ann_bp demo01/main.cpp demo01/Bp.h demo01/Bp.cpp)