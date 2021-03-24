#pragma once

//	********************************************************
//	File Name:			threadQueue.h        
//	Date:               3/19/2021
//	Author:             Proshyn Nazarii
//	Description:        thread-safe structure <queue> with 
//                      the ability to simultaneously write
//                      from multiple threads
//	********************************************************

#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>

class ThreadQueue
{
public:

	ThreadQueue() = default;

	//! \brief                 Inserts a new element at the end of the queue
	//!                        sync access to the queue, prevent data race
	//! \param [in] funct      New item for push 
	//! \return 
	void push(std::function<void()> funct);

	//! \brief                 Delete first element in the queue 
	//!                        sync access to the queue, prevent data race
	//! \return                First function in the queue
	std::function<void()> pop();

	size_t size() const;


private:
	
	//Sync access to the queue,
	//prevent data race
	mutable std::mutex mut;

	//Queue of functions wich will be
	//executed in thread pool
	std::queue<std::function<void()>> dataQueue;

	//notifies that an item has been added to the queue
	std::condition_variable dataCondition;
};

