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
	ThreadPool();
	~ThreadPool();

	//thread not copiable
	ThreadPool(const ThreadPool&) = delete;
	ThreadPool& operator = (const ThreadPool&) = delete;
	void submit(std::function<void()> funct);

private:
	std::vector<std::thread> threads;
	std::atomic_bool done;
	ThreadQueue workQueue;
	JoinThread joiner;

	void workThread();
};


