//	$Header$

//	********************************************************
//	File Name:			threadPoll.h        
//	Date:               3/19/2021
//	Author:             Proshyn Nazarii
//	Description:        simple example of Thread Pool
//	********************************************************


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
#include "joinThread.h"

class ThreadPool
{
public:
	//! \brief       Determines the possible number 
	//!              of threads and creates them
	//! \return 
	ThreadPool();

	~ThreadPool();

	//Thread not copiable
	ThreadPool(const ThreadPool&) = delete;
	ThreadPool& operator = (const ThreadPool&) = delete;

	//! \brief                 Add function to the queue for execution
	//! \param [in] funct      Function performed in the thread 
	//! \return                   
	void submit(std::function<void()> funct);

private:
	//Vector of working threads
	std::vector<std::thread> threads;

	//Indicates the possibility threads to work
	std::atomic_bool done;

	//Queue of functions to be performed
	ThreadQueue workQueue;

	//Ensures the connection of all threads
	JoinThread joiner;

	void workThread();
};


