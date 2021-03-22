//	$Header$

//	********************************************************
//	File Name:			joinThread.h        
//	Date:               3/22/2021
//	Author:             Proshyn Nazarii
//	Description:        ensures the connection of all  
//                      threads, regardless of how the 
//                      processing of the block is completed
//	********************************************************

#pragma once

#include<vector>
#include <thread>

class JoinThread
{
public:
	explicit JoinThread(std::vector<std::thread>& thread) :
		threads(thread)
	{};
	~JoinThread();

private:
	std::vector<std::thread>& threads;
};

