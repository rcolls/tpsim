#include "stdafx.h"
#include "Thread.h"
#include "Core.h"
#include "Process.h"
#include "OutputResults.h"

#include <string>

using std::to_string;


Thread::Thread(double duration):minimumDuration(duration),remainingDuration(duration),runTime(0),memoryFactor(1)
{
}

// Default constructor (required to create vector).
Thread::Thread(void):minimumDuration(0),remainingDuration(0),runTime(0)
{
}

Thread::~Thread(void)
{
}


double Thread::GetMinimumDuration()
{
	return minimumDuration;
}


double Thread::GetRemainingDuration()
{
	return remainingDuration;
}


double Thread::GetRunTime()
{
	return runTime;
}


// Update remaining thread life
double Thread::UpdateThread(double cpuTime, double prevCpuTime, double timeStep)
{
	// Reduce coreTime in accordance with memory penalty of thread
	double processTime = cpuTime*memoryFactor;
	double leftoverTime = 0;

	// if prevCpuTime > 0 need to correct values from previous visit
	if(prevCpuTime > 0)
	{
		runTime = runTime - timeStep;
		remainingDuration= remainingDuration + prevCpuTime*memoryFactor;
	}

	// Check if thread finishes in this visit. If so, rescale the increment
	if(remainingDuration > processTime)
	{
		runTime = runTime + timeStep;
		leftoverTime = 0;
		remainingDuration = remainingDuration - processTime;
	}
	else
	{
		runTime = runTime + (remainingDuration/memoryFactor);
		leftoverTime = cpuTime - (remainingDuration/memoryFactor);
		remainingDuration = 0;
	}

	// If thread finished return leftover cpu time
	return leftoverTime;
}


// Returns true if thread life is <= 0
bool Thread::IsComplete()
{
	if(remainingDuration > 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}



void Thread::SetCore(std::shared_ptr<Core> core)
{
	pCore = core;
}



std::shared_ptr<Core> Thread::GetCore()
{
	return pCore;
}


void Thread::SetMemoryFactor(double factor)
{
	memoryFactor = factor;
}


double Thread::GetMemoryFactor()
{
	return memoryFactor;
}



// Outputs minimumDuration and runtime to file via OutputResults object.
// If thread is incomplete print runtime as -ve
void Thread::OutputThreadInfo(OutputResults &res)
{
	std::string finalTime = "";
	if(IsComplete())
	{
		finalTime = to_string(runTime);
	}
	else
	{
		finalTime =  to_string(-runTime);
	}

	res.WriteThreadInfo(to_string(minimumDuration));
	res.WriteThreadInfo(" ");
	res.WriteThreadInfo(finalTime);
}


