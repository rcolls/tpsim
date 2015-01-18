#pragma once
#include <memory>
#include <vector>

#include "MemModel.h"

class Core;
class Thread;
class OutputResults;


class MemModelDemo: public MemModel
{
private:
	int rows;
	int cols;
	std::vector<std::shared_ptr<Core> > cores;
	std::vector<std::shared_ptr<Core> >::iterator iter;

	void CreateCores();
	void CalculateRowAndColumn(std::shared_ptr<Core> pCore, int &row, int &col);
public:
	MemModelDemo(int noOfRows, int noOfCols);
	~MemModelDemo(void);
	void GetSize(int &noOfRows, int &noOfCols);
	void IteratorReset();
	std::shared_ptr<Core> IteratorNext();
	std::shared_ptr<Core> IteratorFirst();
	bool IteratorComplete();
	void UpdateCores(double increment);
	double GetMemoryFactor(std::shared_ptr<Core> pSlaveCore, std::shared_ptr<Core> pMasterCore);
	void FindNearestCores(std::list<std::shared_ptr<Core> > &coreList, std::shared_ptr<Core> pCore, int level);
	void OutputThreadCount(OutputResults &res, double time);
};

