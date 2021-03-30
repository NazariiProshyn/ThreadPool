cmake_minimum_required(VERSION 3.16.3)
project(ThreadPool)

set(CMAKE_CXX_STANDART 17)

find_package( Threads )

# We define WIN32_WINNT to specify the minimum 
# operating system version my code supports
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/WX /W3 -D_WIN32_WINNT=0x0501)
else()
    add_compile_options(-g2 -Werror -Wall -Wpedantic -Weffc++)
endif()

add_executable(threadPool main.cpp threadSafeQueue.h threadSafeQueue.cpp threadPool.h threadPool.cpp)

target_link_libraries( threadPool ${CMAKE_THREAD_LIBS_INIT} )
