#pragma once

//	********************************************************
//	File Name:          threadPoll.h        
//	Date:               3/19/2021
//	Author:             Proshyn Nazarii
//	Description:        simple example of Thread Pool
//	********************************************************


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
	//! \return 
	ThreadPool(const size_t thread_count);
	~ThreadPool();

	//Thread not copiable
	ThreadPool(const ThreadPool&) = delete;
	ThreadPool& operator=(const ThreadPool&) = delete;

	//! \brief                 Add function to the execution queue  
	//! \param [in] funct      Function that is added to the execution queue
	//! \return                   
	void submit(const std::function<void()> funct);

private:
	//Vector of working threads
	std::vector<std::thread> threads;

	//Indicates the possibility threads to work
	std::atomic_bool run{true};

	//Synchronized access to the task queue
	std::queue<std::function<void()>> workQueue;

	void workThread();
};


