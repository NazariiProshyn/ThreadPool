/**
 * @file      threadSafeQueue.cpp
 *
 * @brief     Realization of Thread-safe
 *            structure <queue> 
 *
 * @author    Proshyn Nazarii
 * Contact:   nazariyproshyn@gmail.com
 *
 */

#include "threadSafeQueue.h"


void ThreadSafeQueue::push(std::function<void()> funct)
{
	std::lock_guard<std::mutex> lock(mut);
	dataQueue.push(std::move(funct));
	condVar.notify_one();
}

std::function<void()> ThreadSafeQueue::pop()
{
	std::unique_lock<std::mutex> lock(mut);
	condVar.wait(lock, [this] {return !dataQueue.empty(); });

	std::function<void()> value = std::move(dataQueue.front());
	dataQueue.pop();
	return value;
}

size_t ThreadSafeQueue::size() const
{
	std::lock_guard<std::mutex> lock(mut);
	return dataQueue.size();
}
