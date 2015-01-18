#include "stdafx.h"
#include <vector>
#include <random>
#include "OS.h"
#include "Process.h"
#include "Thread.h"
#include "SimProbabilities.h"
#include "OutputResults.h"
#include "TPStrategy.h"

using std::shared_ptr;
using std::vector;
using std::pair;
using std::map;


Process::Process(int maxThreads, shared_ptr<MemModel> pMemModel, shared_ptr<TPStrategy> pTPStrategy, SimProbabilities &simProbs, OS *os):AllThreads(maxThreads)
{
	// Create a matrix of doubles to capture how much each thread's runtime is dependent on the other threads in the process
	vector<vector<double> > couplingMatrix;
	CreateCouplingMatrix(couplingMatrix,maxThreads);

	// Create the specified number of threads.
	// 'Ideal' thread duration is generated probabilistically by the simProbs object. 
	double duration = 0;
	for(int thread = 0; thread < maxThreads; thread++)
	{
		duration = simProbs.GetThreadLength();
		CreateThread(thread, duration);
	}

	// Match the value in the coupling matrix to the thread pairing. Only non-zero values are captured
	// The ordering of the ratios is taken as the order in which the threads were created.
	double factor = 0;
	for(int slave = 0; slave < maxThreads; slave++)
	{
		for(int master = 0; master < maxThreads; master++)
		{
			factor = couplingMatrix[slave][master];
			if(factor > 0)
			{
				AddCoupling(AllThreads[slave],AllThreads[master],factor);
			}
		}
	}

	// Now that the coupling information is known allocate the threads to cores via the TPStrategy object
	for (vector<shared_ptr<Thread> >::iterator iter = AllThreads.begin(); iter != AllThreads.end(); ++iter)
	{
		pTPStrategy->AllocateThreadToCore(this,*iter,os);
	}

	// Calculate the memory penalty for each thread based on its coupling ratios and the core locations
	for (vector<shared_ptr<Thread> >::iterator iter = AllThreads.begin(); iter != AllThreads.end(); ++iter)
	{
		SetPenalty(pMemModel,*iter);
	}
}

// Default constructor (required to create Vector).
Process::Process(void)
{
}

Process::~Process(void)
{
}


int Process::GetNoOfThreads()
{
	return AllThreads.size();
}


// Process is complete when all associated threads are complete
bool Process::IsComplete()
{
	for(vector<shared_ptr<Thread> >::iterator it = AllThreads.begin(); it != AllThreads.begin() + GetNoOfThreads(); ++it)
	{
		if(!(*it)->IsComplete())
		{
			return false;
		}
	}
	
	return true;
}


// Create a new thread with specified duration on the heap
void Process::CreateThread(int threadNo, double duration)
{
	shared_ptr<Thread> ptr(new Thread(duration));
	AllThreads[threadNo] = ptr;
}


// Coupling ratios between threads. Ratios represent the proportion of access required to other
// threads in the process. Ratios add to 1 for each thread (including a value for coupling to itself).
// In this implementation the first thread is not coupled to any others.
// All other threads have a 0.5 coupling to the first thread (the other 0.5 being to itself).
void Process::CreateCouplingMatrix(vector<vector<double> > &couplingMatrix, int size)
{
	double factor;
	for(int i = 0; i < size; i++)
	{
		vector<double> temp;
		for(int j = 0; j < size; j++)
		{
			if(j == 0 || j == i)
			{
				factor = 0.5;
			}
			else
			{
				factor = 0;
			}
			temp.push_back(factor);
		}
		couplingMatrix.push_back(temp);
	}
	vector<double> temp = couplingMatrix[0];
	temp[0] = 1;
	couplingMatrix[0] = temp;
}


// Store the coupling ratio between slave and master threads.
void Process::AddCoupling(shared_ptr<Thread> slave, shared_ptr<Thread> master, double couplingRatio)
{
	pair<Thread*,Thread*> key(slave.get(),master.get());
	coupling[key] = couplingRatio;
}


// Determine the penalty incurred by the distance of coupled threads
// Penalty factor = SUM(couplingRatio*memoryPenalty)
// memoryPenalty is obtained from MemoryModel object
void Process::SetPenalty(shared_ptr<MemModel> pMemModel, shared_ptr<Thread> pSlaveThread)
{
	double avgFactor = 0;
	for(vector<shared_ptr<Thread> >::iterator iterMaster = AllThreads.begin(); iterMaster != AllThreads.end(); ++iterMaster)
	{
		double ratio = GetCoupling(pSlaveThread,*iterMaster);
		if(ratio > 0)
		{
			shared_ptr<Core> pSlaveCore = pSlaveThread->GetCore();
			shared_ptr<Core> pMasterCore = (*iterMaster)->GetCore();
			double factor = pMemModel->GetMemoryFactor(pSlaveCore,pMasterCore);
			avgFactor = avgFactor + ratio*factor;
		}
	}
	pSlaveThread->SetMemoryFactor(avgFactor);
}


// Update penalty values (e.g. after a thread has been moved)
void Process::UpdatePenalties(shared_ptr<MemModel> pMemModel)
{
	for(vector<shared_ptr<Thread> >::iterator iterSlave = AllThreads.begin(); iterSlave != AllThreads.end(); ++iterSlave)
	{
		SetPenalty(pMemModel,(*iterSlave));
	}
}


// Returns coupling ratio between slave and master threads. Returns zero if no match is found.
double Process::GetCoupling(shared_ptr<Thread> slaveThread, shared_ptr<Thread> masterThread)
{
	pair<Thread*,Thread*> key(slaveThread.get(),masterThread.get());
	map<pair<Thread*,Thread*>,double>::iterator it = coupling.find(key);
	if(it != coupling.end())
	{
		return it->second;
	}
	else
	{
		return 0;
	}
}


// Outputs process information to file via OutputResults object.
void Process::OutputProcessInfo(OutputResults &res)
{	
	for (vector<shared_ptr<Thread> >::iterator iter = AllThreads.begin(); iter != AllThreads.end(); ++iter)
	{
		(*iter)->OutputThreadInfo(res);
		res.WriteThreadInfo("\n");
	}
}

