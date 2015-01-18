#include "stdafx.h"
#include "SimProbabilities.h"
#include "ProbDist.h"

#include <memory>
#include <string>

using std::shared_ptr;


SimProbabilities::SimProbabilities(shared_ptr<ProbDist> pdur, shared_ptr<ProbDist> pthread, shared_ptr<ProbDist> pProc, shared_ptr<ProbDist> pNew):
	threadDurationDistribution(pdur),noOfThreadsDistribution(pthread),noOfProcessesDistribution(pProc),newProcessCreationDistribution(pNew)
{
}


SimProbabilities::~SimProbabilities(void)
{
}


// Thread length will be [double] and > 0
double SimProbabilities::GetThreadLength()
{
	return threadDurationDistribution->GetNextDoubleGTZero();
}


// No of threads created will be [int] and > 0
int SimProbabilities::GetNoOfThreads()
{
	return noOfThreadsDistribution->GetNextIntGTZero();
}


// No of processes created will be [int] and > 0
int SimProbabilities::GetNoOfProcesses()
{
	return noOfProcessesDistribution->GetNextIntGTZero();
}


// Process decision will be [int] and >= 0
int SimProbabilities::GetNewProcessDecision()
{
	return newProcessCreationDistribution->GetNextIntGEZero();
}
