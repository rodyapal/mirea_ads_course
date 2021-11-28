cmake_minimum_required(VERSION 3.20)
project(Encoding)

set(CMAKE_CXX_STANDARD 20)

add_executable(Encoding main.cpp HuffmanCoder.h utils.h ShennonFanoCoder.h)
