#pragma once
//	$Header$

//	********************************************************
//	File Name:			threadQueue.h        
//	Date:               3/19/2021
//	Author:             Proshyn Nazarii
//	Description:        thread-safe structure <queue> with 
//                      the ability to simultaneously write
//                      from multiple threads
//	********************************************************

#include <mutex>
#include <memory>
#include <condition_variable>
#include <queue>
#include <functional>

class ThreadQueue
{
public:

	ThreadQueue() = default;

	//! \brief                 Inserts a new element at the end of the queue
	//! \param [in] value      New item for push 
	//! \return 
	void push(std::function<void()> value);

	//! \brief                     Assigns first element of queue to the variable
	//! \param [in,out] value      function performed in the thread 
	//! \return                    returns result of deleting first element
	std::function<void()> pop();

	//! \brief                 Check queue for items     
	//! \return                Result of checking (true if number of items>0)
	bool empty() const;



private:
	//Allows you to work with the 
	//queue in multithreaded mode safely
	mutable std::mutex mut;

	//Contains items about functions that 
	//are in runtime and that will be executed
	std::queue<std::function<void()>> dataQueue;

	std::condition_variable dataCondition;
};

