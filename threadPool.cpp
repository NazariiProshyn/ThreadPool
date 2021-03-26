#include <iostream>
#include <iterator>
#include "threadPool.h"


ThreadPool::ThreadPool(const size_t thread_count)
{
	threads.reserve(thread_count);
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
		run = false;
		std::cout << ex.what() << std::endl;

		while(threads.size()>0)
		{
			threads.pop_back();
		}

		throw;
	}
}

ThreadPool::~ThreadPool()
{	
	for (auto &iter : threads)
	{
		if (iter.joinable())
		{
			iter.join();
		}
	}
	run = false;
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
