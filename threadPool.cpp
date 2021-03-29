#include <iostream>
#include "threadPool.h"


ThreadPool::ThreadPool(const size_t thread_count)
{
	threads.reserve(thread_count);
	std::exception ex;
	try
	{
		for (size_t i = 0; i < thread_count; i++)
		{
			threads.push_back(
				std::thread(&ThreadPool::workThread, this));
		}
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
		stopThreads();
		throw ex;
	}
}

ThreadPool::~ThreadPool()
{
	//we need this loop to ensure 
	//that all functions are performed
    while( workQueue.size()>0 ) {}
    stopThreads();
}

void ThreadPool::submit(std::function<void()> funct)
{
	workQueue.push(std::move(funct));
}

void ThreadPool::workThread()
{
	while (run)
	{
		std::function<void()> task = workQueue.pop();
		task();
	}
}

void ThreadPool::stopThreads()
{
	run = false;
	for (auto& iter : threads)
	{
		if (iter.joinable())
		{
			iter.join();
		}
	}
}
