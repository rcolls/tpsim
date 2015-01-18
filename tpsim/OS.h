#pragma once
#include <vector>
#include <memory>
#include <random>

#include "MemModelDemo.h"

class Process;
class Thread;
class Core;
class SimProbabilities;
class OutputResults;
class TPStrategy;

class OS
{
private:
    std::vector<Process> processes;
	std::shared_ptr<MemModel> pMemModel;
	std::shared_ptr<TPStrategy> pTPStrategy;
	int noCreatedProcesses;
	double time;
	bool threadsComplete;

	void CreateProcess(SimProbabilities &simProbs);
	bool IsComplete(double maxTime);
public:
	OS(std::shared_ptr<MemModel> memModel, std::shared_ptr<TPStrategy> pTPStrat,int maxProc);
	~OS(void);
	void Run(double increment, double maxRuntime, SimProbabilities &probDist, OutputResults &outOpts);
};

