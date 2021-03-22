#include "joinThread.h"

JoinThread::~JoinThread()
{
	for (size_t i = 0; i < threads.size(); ++i) 
	{
		if (threads[i].joinable()) 
		{
			threads[i].join();
		}
	}
}
