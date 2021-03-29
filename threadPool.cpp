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
		stopvector();
		throw ex;
	}
}

ThreadPool::~ThreadPool()
{
    while(workQueue.size()>0){}
    stopvector();
}

void ThreadPool::submit(const std::function<void()> funct)
{
	workQueue.push(funct);
}

void ThreadPool::workThread()
{
	while (run)
	{
		std::function<void()> task = workQueue.pop();
		task();
	}
}

void ThreadPool::stopvector()
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
