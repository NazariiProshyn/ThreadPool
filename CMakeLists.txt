cmake_minimum_required(VERSION 3.16.3)
project(ThreadPoolC17)

set(CMAKE_CXX_STANDART 17)

add_executable(ThreadPoolC17 Main.cpp ThreadPoolH.cpp  ThreadPoolH.h)