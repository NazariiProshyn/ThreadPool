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
		throw;
	}
}

ThreadPool::~ThreadPool()
{
	while (workQueue.size() > 0) {}
	run = false;
	for (std::vector<std::thread>::iterator iter = threads.begin(); iter < threads.end(); ++iter)
	{
		if ((*iter).joinable())
		{
			(*iter).join();
		}
	}
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
