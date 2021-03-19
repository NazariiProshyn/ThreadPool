#pragma once

#include <mutex>
#include <memory>
#include <thread>
#include <condition_variable>
#include <queue>
#include <utility>

template<typename T>
class ThreadQueue
{
public:
	
	ThreadQueue() = default;
	
	void push(T value);
	std::shared_ptr<T> waitAndPop();
	std::shared_ptr<T> tryPop();
	bool empty() const;

	// void waitAndPop(T& value);
	// bool tryPop(T& value);

private:
	mutable std::mutex mut;
	std::queue<T> dataQueue;
	std::condition_variable dataCondition;
};
