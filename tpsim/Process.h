#pragma once
#include "process.h"
#include "SimProbabilities.h"

#include <memory>
#include <vector>
#include <map>

class OS;
class Thread;
class SimProbabilities;
class OutputResults;
class TPStrategy;
class MemModel;

class Process
{
private:
	std::vector<std::shared_ptr<Thread> > AllThreads;
	std::map<std::pair<Thread*,Thread*>, double> coupling;

	void CreateThread(int threadNo, double duration);
	void CreateCouplingMatrix(std::vector<std::vector<double> > &couplingMatrix, int size);
	void AddCoupling(std::shared_ptr<Thread> slave, std::shared_ptr<Thread> master, double couplingRatio);
	void SetPenalty(std::shared_ptr<MemModel> pMemModel, std::shared_ptr<Thread> slaveThread);
public:
	Process(void);
	Process(int noOfThreads, std::shared_ptr<MemModel> pMemModel, std::shared_ptr<TPStrategy> pTPStrategy, SimProbabilities &simProbs, OS *os);
	~Process(void);
	typedef std::vector<std::shared_ptr<Thread> >::iterator iterator;
    iterator begin() { return AllThreads.begin(); }
    iterator end() { return AllThreads.end(); }

	int GetNoOfThreads();
	bool IsComplete();
	void UpdatePenalties(std::shared_ptr<MemModel> pMemModel);
	double GetCoupling(std::shared_ptr<Thread> slaveThread, std::shared_ptr<Thread> masterThread);
	void OutputProcessInfo(OutputResults &res);
};

