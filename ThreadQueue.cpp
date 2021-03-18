#include "ThreadQueue.h"


template<typename T>
ThreadQueue<T>::ThreadQueue(T value)
{
	std::lock_guard<std::mutex> lock(mut);
	dataQueue.push(std::move(value));
	dataCondition.notify_one();
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
	dataCondition.wait(lock, [this] { return !dataQueue.empty(); });
	value = std::move(dataQueue.front());
	dataQueue.pop();
}

template<typename T>
std::shared_ptr<T> ThreadQueue<T>::waitAndPop()
{
	std::unique_lock<std::mutex> lock(mut);
	dataCondition.wait(lock, [this] {return !dataQueue.empty(); });
	std::shared_ptr<T> res(
		std::make_shared<T>(std::move(dataQueue.front())));
	dataQueue.pop();
	return res;
}

template<typename T>
bool ThreadQueue<T>::tryPop(T& value)
{
	std::lock_guard<std::mutex> lock(mut);
	if (dataQueue.empty()) {
		return false;
	}
	value = std::move(dataQueue.front());
	dataQueue.pop();
	return true;
}

template<typename T>
std::shared_ptr<T> ThreadQueue<T>::tryPop()
{
	std::lock_guard<std::mutex> lock(mut);
	if (dataQueue.empty()) {
		return std::shared_ptr<T>();
	}
	std::shared_ptr<T> res(
		std::make_shared<T>(std::move(dataQueue.front())));
	dataQueue.pop();
	return res;
}

template<typename T>
bool ThreadQueue<T>::empty() const
{
	std::lock_guard<std::mutex> lock(mut);
	return dataQueue.empty();
}
