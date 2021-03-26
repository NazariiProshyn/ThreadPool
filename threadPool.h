#pragma once

/**
 * @file      threadPool.h
 *
 * @brief     simple example of Thread Pool
 *
 * @author    Proshyn Nazarii
 * Contact:   nazariyproshyn@gmail.com
 *
 */

#include <vector>
#include <functional> 
#include <thread>
#include <queue>
#include <atomic>

#include "threadSafeQueue.h"

class ThreadPool
{
public:
	//! \brief       Determines the possible number 
	//!              of threads and creates them
	ThreadPool(const size_t thread_count);

	~ThreadPool();

	//Thread not copiable
	ThreadPool(const ThreadPool&) = delete;
	ThreadPool& operator=(const ThreadPool&) = delete;

	//! \brief                 Add function to the execution queue  
	//! \param [in] funct      New item for push         
	void submit(const std::function<void()> funct);

private:
	//Vector of working threads
	std::vector<std::thread> threads;

	//Indicates the possibility threads to work
	std::atomic_bool run{true};

	//Synchronized access to the task queue
	ThreadSafeQueue workQueue;

	void workThread();
};


