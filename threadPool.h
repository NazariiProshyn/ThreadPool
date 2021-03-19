#pragma once

#include <vector>
#include <queue>
#include <functional> 
#include <mutex>
#include <condition_variable>
#include <type_traits> 
#include <thread>
#include <future> 

#include "threadQueue.h"

class ThreadPool
{
public:
	ThreadPool(size_t NumOfThreads);
	~ThreadPool();

	//thread not copiable
	ThreadPool (const ThreadPool&) = delete;
	ThreadPool& operator = (const ThreadPool&) = delete;

private:
	std::vector<std::thread> threads;
	std::atomic_bool done;
	ThreadQueue workQueue;
};


