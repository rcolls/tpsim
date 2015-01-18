#include "stdafx.h"
#include "Core.h"
#include "Thread.h"

using std::list;
using std::shared_ptr;


Core::Core(int index): coreNo(index)
{
}


// Need default constructor to create vector
Core::Core(void)
{
}

Core::~Core(void)
{
}


int Core::GetCoreNo()
{
	return coreNo;
}


// Number of threads left on the core
int Core::GetNoOfThreads()
{
	return threads.size();
}


// Returns a measure of how busy the core is.
double Core::GetActivityLevel()
{
	// Returns the number of threads.
	return (double)GetNoOfThreads();
}


// Add a thread to the core
void Core::AddThread(shared_ptr<Thread> pThread, shared_ptr<Core> pCore)
{
	threads.push_front(pThread);
	pThread->SetCore(pCore);
}



// Remove a thread from the core
void Core::RemoveThread(std::shared_ptr<Thread> oldThread)
{
	threads.remove(oldThread);
}



// Update the status of the threads on the core.
void Core::UpdateCore(double increment)
{
	// Core time is shared evenly between all threads on the core.
	double coreTime = (GetNoOfThreads() > 0) ? increment/GetNoOfThreads() : 0;
	double prevCoreTime = 0;
	double leftoverTime = coreTime;
	while(leftoverTime > 0 && GetNoOfThreads() > 0)
	{
		leftoverTime = 0;
		// Loop through all threads, removing them if they are complete	
		for(list<shared_ptr<Thread> >::iterator thread = threads.begin(); thread != threads.end();)
		{
			// If the thread completed this step, capture the unused increment time
			leftoverTime = leftoverTime + (*thread)->UpdateThread(coreTime,prevCoreTime,increment);
			if((*thread)->IsComplete())
			{
				shared_ptr<Thread> deadThread = *thread;
				++thread;
				RemoveThread(deadThread);
			}
			else
			{
				++thread;
			}
		}
		// Loop again if there was unused time
		if((leftoverTime > 0) && (GetNoOfThreads() > 0))
		{
			prevCoreTime = coreTime;
			coreTime = coreTime + (leftoverTime/GetNoOfThreads());
		}
	}
}


