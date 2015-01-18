#include "stdafx.h"
#include "MemModelDemo.h"
#include "Core.h"
#include "OutputResults.h"
#include "Thread.h"

#include <stdlib.h>
#include <string>

using std::string;
using std::shared_ptr;
using std::list;
using std::vector;
using std::pair;


MemModelDemo::MemModelDemo(int noOfRows, int noOfCols): rows(noOfRows),cols(noOfCols),cores(rows*cols)
{
	// Give each core an index number
	CreateCores();
}


MemModelDemo::~MemModelDemo(void)
{
}


// Returns number of rows and columns of cores
void MemModelDemo::GetSize(int &noOfRows, int &noOfCols)
{
	noOfRows = rows;
	noOfCols = cols;
}


// Point the iterator to the first core
void MemModelDemo::IteratorReset()
{
	iter = cores.begin();
}


// Return the core currently being pointed to then advance the iterator
shared_ptr<Core> MemModelDemo::IteratorNext()
{
	return *(iter++);
}


// Return the first core
shared_ptr<Core> MemModelDemo::IteratorFirst()
{
	return *(cores.begin());
}


// Terminator for the iterator
bool MemModelDemo::IteratorComplete()
{
	if(iter == cores.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}


// Apply the time step to the threads on each core
void MemModelDemo::UpdateCores(double increment)
{
	for (vector<shared_ptr<Core> >::iterator iter = cores.begin(); iter != cores.end(); ++iter)
	{
		if((*iter)->GetNoOfThreads() > 0)
		{
			(*iter)->UpdateCore(increment);
		}
	}
}


// Calculate memory penalty based on the distance between the cores
// For the Manhattan model the distance is (number of rows + number of columns) that separate the cores
// Memory penalty is a reciprocal function of this distance
double MemModelDemo::GetMemoryFactor(shared_ptr<Core> pSlaveCore, shared_ptr<Core> pMasterCore)
{
	int slaveRow;
	int slaveCol;
	CalculateRowAndColumn(pSlaveCore,slaveRow,slaveCol);

	int masterRow;
	int masterCol;
	CalculateRowAndColumn(pMasterCore,masterRow,masterCol);

	int dist = abs(slaveRow - masterRow) + abs(slaveCol - masterCol);

	return (double)1.0/(dist + 1);
}



// Return a list (by reference) of cores the specified distance away from the input core 
// If level < 0 return nothing
// If level = 0 return the input core
// If level = 1 return all cores EITHER 1 row OR 1 column away from the input core
// If level = 2 return all cores EITHER 2 rows OR 2 columns OR (1 row AND 1 column) away from the input core
// etc
// Order the cores are returned is as follows (if core exists):
// Same column as input;      'level' rows above the input
// One column left of input;  'level - 1' rows above input
// One column right of input; 'level - 1' rows above input
// Two columns left of input; 'level - 2' rows above input
// ...
// One column right of input; 'level - 1' rows below input
// Same column as input; 'level' rows below input
void MemModelDemo::FindNearestCores(list<std::shared_ptr<Core> > &coreList, std::shared_ptr<Core> pCore, int level)
{
	coreList.clear();
	
	if(level < 0 || level > ((rows-1) + (cols-1)))
	{
	}
	else if(level == 0)
	{
		coreList.push_front(pCore);
	}
	else
	{
		int row;
		int col;
		CalculateRowAndColumn(pCore,row,col);

		int colIndex = 0;
		int minRow = (row - level >= 0)   ? (row - level) : 0;
		int maxRow = (row + level < rows) ? (row + level) : rows - 1;
		// Iterate across all valid rows
		for(int rowIndex = minRow; rowIndex <= maxRow; rowIndex++)
		{
			// Try position to the left of the starting column
			colIndex = col - (level - abs(row - rowIndex));
			if(colIndex >= 0)
			{
				coreList.push_back(cores[rowIndex*cols + colIndex]);
			}
			// Now try position to the right. Ignore if it is the starting column (will be duplicate of above)
			colIndex = col + (level - abs(row - rowIndex));
			if((colIndex < cols) && (colIndex != col))
			{
				coreList.push_back(cores[rowIndex*cols + colIndex]);
			}
		}
	}
}


// Send core load information to output object
void MemModelDemo::OutputThreadCount(OutputResults &res, double time)
{
	res.WriteCoreInfo("t ");
	res.WriteCoreInfo(time);
	res.WriteCoreInfo("\n");
	for(int row = 0; row < rows; row++)
	{
		for(int col = 0; col < cols; col++)
		{
			res.WriteCoreInfo(cores[row*cols + col]->GetActivityLevel());
			res.WriteCoreInfo(" ");
		}
		res.WriteCoreInfo("\n");
	}
}


// Cores are numbered sequentially across rows starting at 1
void MemModelDemo::CreateCores()
{
	int coreNo = 1;
	for(vector<shared_ptr<Core> >::iterator iter = cores.begin(); iter != cores.end(); ++iter)
	{
		shared_ptr<Core> ptr(new Core(coreNo));
		(*iter) = ptr;
		coreNo = coreNo + 1;
	}
}


// Convert core number to row and column number
void MemModelDemo::CalculateRowAndColumn(std::shared_ptr<Core> pCore, int &pRow, int &pCol)
{
	int core = pCore->GetCoreNo();
	pRow = (core-1)/cols;
	pCol = (core-1)%cols;
}
