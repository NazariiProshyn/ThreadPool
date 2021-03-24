cmake_minimum_required(VERSION 3.16.3)
project(ThreadPool)

set(CMAKE_CXX_STANDART 17)

add_executable(threadPool main.cpp threadsafeQueue.h threadsafeQueue.cpp)
