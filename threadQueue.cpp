#include "threadQueue.h"


void ThreadQueue::push(std::function<void()> value)
{
	std::lock_guard<std::mutex> lock(mut);
	dataQueue.push(std::move(value));
	dataCondition.notify_one();
}

std::shared_ptr<std::function<void()>> ThreadQueue::Pop()
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

