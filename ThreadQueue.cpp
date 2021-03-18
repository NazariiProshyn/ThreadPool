#include "ThreadQueue.h"

ThreadQueue::ThreadQueue()
{
}

ThreadQueue::~ThreadQueue()
{
}

template<typename T>
void ThreadQueue<T>::push(T value)
{
	std::lock_guard<std::mutex> lock(mut);
	dataQueue.push(std::move(value));
	dataCondition.notify_one();
}

template<typename T>
void ThreadQueue<T>::waitAndPop(T& value)
{
	std::unique_lock<std::mutex> lock(mut);
}

template<typename T>
std::shared_ptr<T> ThreadQueue<T>::waitAndPop()
{
	return std::shared_ptr<T>();
}

template<typename T>
bool ThreadQueue<T>::tryPop(T& value)
{
	return false;
}

template<typename T>
std::shared_ptr<T> ThreadQueue<T>::tryPop()
{
	return std::shared_ptr<T>();
}

template<typename T>
bool ThreadQueue<T>::empty() const
{
	return false;
}
