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
	//!						   blocks access to the queue
	//! \param [in] value      New item for push 
	//! \return 
	void push(const std::function<void()>& value);

	//! \brief                     Assigns first element of queue to the variable
	//!                            blocks access to the queue
	//! \param [in,out] value      function performed in the thread 
	//! \return                    returns result of deleting first element
	std::function<void()> pop();

	size_t size() { return dataQueue.size(); }


private:
	//Allows you to work with the 
	//queue in multithreaded mode safely
	mutable std::mutex mut;

	//Contains items about functions that 
	//are in runtime and that will be executed
	std::queue<std::function<void()>> dataQueue;

	//notifies that an item has been added to the queue
	std::condition_variable dataCondition;
};

