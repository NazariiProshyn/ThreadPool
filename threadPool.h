#pragma once

//	********************************************************
//	File Name:			threadPoll.h        
//	Date:               3/19/2021
//	Author:             Proshyn Nazarii
//	Description:        simple example of Thread Pool
//	********************************************************


#include <vector>
#include <queue>
#include <functional> 
#include <mutex>
#include <condition_variable>
#include <type_traits> 
#include <thread>
#include <future> 
#include <iostream>

#include "threadQueue.h"

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
	ThreadPool& operator= (const ThreadPool&) = delete;

	//! \brief                 Add function to the queue for execution
	//! \param [in] funct      Function performed in the thread 
	//! \return                   
	void submit(const std::function<void()> funct);

private:
	//Vector of working threads
	std::vector<std::thread> threads;

	//Indicates the possibility threads to work
	std::atomic_bool run{false};

	//Synchronized access to the task queue
	ThreadQueue workQueue;

	void workThread();
};


