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
	ThreadQueue();
	~ThreadQueue();
	void push(T value);
	void waitAndPop(T& value);
	std::shared_ptr<T> waitAndPop();
	bool tryPop(T& value);
	std::shared_ptr<T> tryPop();
	bool empty() const;

private:
	mutable std::mutex mut;
	std::queue<T> dataQueue;
	std::condition_variable dataCondition;
};

