#include "threadQueue.h"


void ThreadQueue::push(std::function<void()> value)
{
	std::lock_guard<std::mutex> lock(mut);
	dataQueue.push(std::move(value));
	dataCondition.notify_one();
}


std::shared_ptr<std::function<void()>> ThreadQueue::waitAndPop()
{
	std::unique_lock<std::mutex> lock(mut);
	dataCondition.wait(lock, [this] {return !dataQueue.empty(); });
	std::shared_ptr<std::function<void()>> res(
		std::make_shared<std::function<void()>>(std::move(dataQueue.front())));
	dataQueue.pop();
	return res;
}


std::shared_ptr<std::function<void()>> ThreadQueue::tryPop()
{
	std::lock_guard<std::mutex> lock(mut);
	if (dataQueue.empty()) {
		return std::shared_ptr<std::function<void()>>();
	}
	std::shared_ptr<std::function<void()>> res(
		std::make_shared<std::function<void()>>(std::move(dataQueue.front())));
	dataQueue.pop();
	return res;
}


bool ThreadQueue::empty() const
{
	std::lock_guard<std::mutex> lock(mut);
	return dataQueue.empty();
}

/*
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
void ThreadQueue<T>::waitAndPop(T& value)
{
	std::unique_lock<std::mutex> lock(mut);
	dataCondition.wait(lock, [this] { return !dataQueue.empty(); });
	value = std::move(dataQueue.front());
	dataQueue.pop();
}
*/
