#include "threadPool.h"


ThreadPool::ThreadPool():
	done(false), joiner(threads)
{
	unsigned const thread_count =
		std::thread::hardware_concurrency();
	try 
	{
		for (unsigned i = 0; i < thread_count; i++)
		{
			threads.push_back(
				std::thread(&ThreadPool::workThread, this));
		}
	}
	catch (...)
	{
		done = true;
		throw;
	}
}

ThreadPool::~ThreadPool()
{
	done = true;
}

void ThreadPool::submit(std::function<void()> funct)
{
	workQueue.push(funct);
}

void ThreadPool::workThread()
{
	while (!done)
	{
		std::function<void()> task;
		if (workQueue.Pop(task))
		{
			task();
		}
		else
		{
			std::this_thread::yield();
		}
	}
}
