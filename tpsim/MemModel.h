#pragma once
#include <memory>
#include <list>

class Thread;
class OutputResults;
class Core;

class MemModel
{
public:
	MemModel(void);
	virtual ~MemModel(void) = 0;
	virtual void GetSize(int &noOfRows, int &noOfCols) = 0;
	virtual void UpdateCores(double increment) = 0;
	virtual double GetMemoryFactor(std::shared_ptr<Core> pSlaveCore, std::shared_ptr<Core> pMasterCore) = 0;
	virtual	void FindNearestCores(std::list<std::shared_ptr<Core> > &coreList, std::shared_ptr<Core> pCore, int level) = 0;
	virtual void OutputThreadCount(OutputResults &res,double time) = 0;
	virtual void IteratorReset() = 0;
	virtual std::shared_ptr<Core> IteratorNext() = 0;
	virtual std::shared_ptr<Core> IteratorFirst() = 0;
	virtual bool IteratorComplete() = 0;
};

