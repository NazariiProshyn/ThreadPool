cmake_minimum_required(VERSION 3.16.3)
project(ThreadPool)

set(CMAKE_CXX_STANDART 17)

find_package( Threads )

add_compile_options(-Wall -Wpedantic -Werror)

add_executable(threadPool main.cpp threadSafeQueue.h threadSafeQueue.cpp threadPool.h threadPool.cpp)

target_link_libraries( threadPool ${CMAKE_THREAD_LIBS_INIT} )