#include "threadPool.h"


void foo1() {
    std::cout << "One" << std::endl;
}

void foo2() {
    std::cout << "Two" << std::endl;
}

void foo3() {
    std::cout << "Three" << std::endl;
}

int main()
{
    ThreadPool threadpool(4);
    std::function<void()> f1 = foo1;
    for (size_t i = 0; i < 3; ++i) 
    { 
        threadpool.submit(f1);
    }

}

