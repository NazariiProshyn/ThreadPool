cmake_minimum_required(VERSION 3.16.3)
project(ThreadPool)

set(CMAKE_CXX_STANDART 17)

add_compile_options(-Wall)

add_executable(threadPool main.cpp threadSafeQueue.h threadSafeQueue.cpp)
