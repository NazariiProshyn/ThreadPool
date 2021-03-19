//	$Header$

//	********************************************************
//	File Name:			threadQueue.h        
//	Date:               3/19/2021
//	Author:             Proshyn Nazarii
//	Description:        thread-safe structure <queue> with 
//                      the ability to simultaneously write
//                      from multiple threads
//	********************************************************


#pragma once

#include <mutex>
#include <memory>
#include <thread>
#include <condition_variable>
#include <queue>
#include <utility>
#include <functional>

class ThreadQueue
{
public:
	
	ThreadQueue() = default;
	
	void push(std::function<void()> value);
	std::shared_ptr<std::function<void()>> waitAndPop();
	std::shared_ptr<std::function<void()>> tryPop();
	bool empty() const;

	// void waitAndPop(T& value);
	// bool tryPop(T& value);

private:
	mutable std::mutex mut;
	std::queue<std::function<void()>> dataQueue;
	std::condition_variable dataCondition;
};

