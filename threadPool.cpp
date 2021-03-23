#include "threadPool.h"


ThreadPool::ThreadPool(size_t thread_count)
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
	catch (std::exception& e)
	{
		run = true;
		std::cout << e.what() << std::endl;
		throw;
	}
}

ThreadPool::~ThreadPool()
{
	//while (workQueue.size() > 0) {}
	run = true;
	for (size_t i = 0; i < threads.size(); ++i)
	{
		if (threads[i].joinable())
		{
			threads[i].join();
		}
	}
}

void ThreadPool::submit(std::function<void()> funct)
{
	workQueue.push(funct);
}

void ThreadPool::workThread()
{
	while (!run)
	{
		std::function<void()> task = workQueue.pop();
		task();
	}
}
