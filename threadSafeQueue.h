#pragma once

/**
 * @file      threadSafeQueue.h
 *
 * @brief     Thread-safe structure <queue> 
 *
 * @author    Proshyn Nazarii
 * Contact:   nazariyproshyn@gmail.com
 *
 */

#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>

/**
 * @class     ThreadSafeQueue
 * 
 * @brief     A wrapper of std::queue<std::function<void()>> 
 *            that provides thread safe operations
 *
 */
class ThreadSafeQueue final
{
public:

	ThreadSafeQueue() = default;

    // ThreadSafeQueue is not copyable
    // ThreadSafeQueue is not movable
    ThreadSafeQueue(const ThreadSafeQueue&) = delete;

    ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;

    ThreadSafeQueue(ThreadSafeQueue&&) = delete;

    ThreadSafeQueue& operator=(ThreadSafeQueue&&) = delete;

    /**
     * @brief           Tread safe insert into the queue
     * 
     * @param funct     New item for push 
     */
	void push(std::function<void()> funct);

    /**
     * @brief     Delete first item from
     *            the queue and return it
     * 
     * @return    First item in the queue
     */
	std::function<void()> pop();

    /**
     * @brief             Returns the number of 
     *                    elements in the queue. 
     * 
     * @return            The number of elements 
     *                    in the queue.
     */
    size_t size() const;

private:
	
    // Sync access to the queue,
    // Prevents data race
    mutable std::mutex mut;

    // Queue of functions
    std::queue<std::function<void()>> dataQueue;

    // Notifies that an item has been added to the queue
    std::condition_variable condVar;
};
