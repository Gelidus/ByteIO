cmake_minimum_required(VERSION 3.1)
project(ByteIO)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    ByteStream.h
    ByteStream.cpp
)

add_library(ByteIO ${SOURCE_FILES})