#pragma once

//  ********************************************************
//  File Name:          threadSafeQueue.h        
//  Date:               3/19/2021
//  Author:             Proshyn Nazarii
//  Description:        thread-safe structure <queue> with 
//                      the ability to simultaneously write
//                      from multiple threads
//  ********************************************************

#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>

class ThreadSafeQueue final
{
public:

	ThreadSafeQueue() = default;

	//! \brief                 Tread safe insert into the queue
	//! \param [in] funct      New item for push 
	void push(std::function<void()> funct);

	//! \brief                 Delete first function
	//!                        from the queue and return it
	//! \return                First function in the queue
	std::function<void()> pop();

	//! \brief                 Returns the number of 
	//!                        elements in the queue. 
	//! \return                The number of 
	//!                        elements in the queue.
	size_t size() const;


private:
	
	// Sync access to the queue,
	// prevents data race
	mutable std::mutex mut;

	// Queue of functions
	std::queue<std::function<void()>> dataQueue;

	// Notifies that an item has been added to the queue
	std::condition_variable condVar;
};
