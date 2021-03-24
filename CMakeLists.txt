cmake_minimum_required(VERSION 3.16.3)
project(ThreadPoolC17)

set(CMAKE_CXX_STANDART 17)

add_executable(threadPool main.cpp  threadPool.h threadPool.cpp  threadQueue.h threadQueue.cpp)
