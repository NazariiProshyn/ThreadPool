#include "threadPool.h"
#include "windows.h"

void foo1() {
    std::cout << "One\n";
}

void foo2() {
    std::cout << "Two\n" ;
}

void foo3() {
    std::cout << "Three\n" ;
}

int main()
{
    ThreadPool threadpool(4);
    std::function<void()> f1 = foo1;
    std::function<void()> f2 = foo2;
    std::function<void()> f3 = foo3;

    for (size_t i = 0; i < 3; ++i) 
    { 
        threadpool.submit(f1);
        threadpool.submit(f2);
        threadpool.submit(f3);
        Sleep(2000);
    }
    return 0;
}

