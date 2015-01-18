#pragma once

#include "ProbDist.h"

#include <memory>

class SimProbabilities
{
private:
	std::shared_ptr<ProbDist> threadDurationDistribution;
	std::shared_ptr<ProbDist> noOfThreadsDistribution;
	std::shared_ptr<ProbDist> noOfProcessesDistribution;
	std::shared_ptr<ProbDist> newProcessCreationDistribution;

public:
	SimProbabilities(std::shared_ptr<ProbDist> pdur, std::shared_ptr<ProbDist> pthread, std::shared_ptr<ProbDist> pProc, std::shared_ptr<ProbDist> pNew);
	~SimProbabilities(void);
	double GetThreadLength();
	int GetNoOfThreads();
	int GetNoOfProcesses();
	int GetNewProcessDecision();
};

