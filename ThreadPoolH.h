#pragma once

#include <vector>
#include <queue>
#include <functional> //bind
#include <mutex>
#include <condition_variable>
#include <type_traits> //invoke_result
#include <thread>
#include <future> //packaged_task

#include "ThreadQueue.h"

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
	ThreadQueue<std::function<void()>> workQueue;
};


