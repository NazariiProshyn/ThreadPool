#include "threadPool.h"
#include <iostream>

void foo1() {
    std::cout << "One\n";
}

void foo2() {
    std::cout << "Two\n";
}

void foo3() {
    std::cout << "Three\n";
}

int main()
{
    ThreadPool threadpool(4);

    for (size_t i = 0; i < 3; ++i)
    {
        threadpool.submit(foo1);
        threadpool.submit(foo2);
        threadpool.submit(foo3);
    }

    return 0;
}

