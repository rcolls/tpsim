#include "stdafx.h"
#include "TPStrategyDemo.h"
#include "Process.h"
#include "MemModel.h"
#include "Thread.h"
#include "Core.h"

#include <map>
#include <climits>


using std::shared_ptr;
using std::vector;
using std::list;
using std::map;


TPStrategyDemo::TPStrategyDemo(std::shared_ptr<MemModel> pMemModel, bool migrationOn):pMemModel(pMemModel),migOn(migrationOn)
{
}


TPStrategyDemo::~TPStrategyDemo(void)
{
}


// Find a core for a new thread.
// If the thread is not coupled to any other thread in its process then allocated it to the 'idlest' core (see AllocateThreadToIdlestCore).
// If the thread is coupled find the thread it is most dependent upon and determine its core. Then search in the vicinity of this core
// (level1 and sometimes level2 from the MemModel) for the lowest loaded core. If there are multiple cores with the same low load then the first
// one returned by the MemModel is chosen
void TPStrategyDemo::AllocateThreadToCore(Process *process, shared_ptr<Thread> pThread, OS *os)
{
	double coupling = process->GetCoupling(pThread,pThread);
	// If coupling to itself is 1 then use the 'idlest' core. Otherwise find 'master' core
	if(coupling == 1)
	{
		AllocateThreadToIdlestCore(pThread);
	}
	else
	{
		// Find the thread to which pThread is most highly coupled (excluding itself)
		// If this thread does not have a core yet then ignore it.
		shared_ptr<Thread> masterThread = pThread;
		double highestCoupling = 0;
		for(Process::iterator iter = process->begin(); iter != process->end(); ++iter)
		{
			coupling = process->GetCoupling(pThread,*iter);
			if((*iter != pThread) && (coupling > highestCoupling))
			{
				if((*iter)->GetCore())
				{
					masterThread = *iter;
					highestCoupling = coupling;
				}
			}
		}

		// Find the cores 1 level away from the master core
		shared_ptr<Core> masterCore = masterThread->GetCore();
		list<shared_ptr<Core> > cores;
		pMemModel->FindNearestCores(cores,masterCore,1);

		// If the process has more threads than there are level 1 cores then extend the search to level 2
		if(process->GetNoOfThreads() > cores.size())
		{
			list<shared_ptr<Core> > extraCores;
			pMemModel->FindNearestCores(extraCores,masterCore,2);
			cores.splice(cores.end(),extraCores);
		}

		std::shared_ptr<Core> pCore = cores.front();
		double minLoad = pCore->GetActivityLevel();
		double load = 0;
		// Iterate through the level1 (and maybe level2) cores to find the one with lowest load
		for (list<shared_ptr<Core> >::iterator iter = cores.begin(); iter != cores.end(); ++iter)
		{
			load = (*iter)->GetActivityLevel();
			if(load < minLoad)
			{
				pCore = (*iter);
				minLoad = load;
			}
		}

		// If the thread is already on a core then remove it
		if(pThread->GetCore())
		{
			pThread->GetCore()->RemoveThread(pThread);
		}
		pCore->AddThread(pThread,pCore);
	}
}



// Move threads that have already been placed on a core.
// THIS IS A DELIBERATELY DEMENTED IMPLEMENTATION!
// In this implementation the first thread of the process is moved if is adjudged too close
// to another thread in the process i.e. the memory factor for the two cores >= 0.5
// For MemModelDemo this corresponds to the cores being adjacent.
// The thread will be moved to the core with the lowest load. If there are multiple cores
// with the same low load then the last one returned by the MemModel iterator is chosen
// (i.e. the one NEAREST THE END)
void TPStrategyDemo::MigrateThreads(Process *process, OS *os)
{
	// Check that migration is activated and that the process has active threads
	if(migOn && !(process->IsComplete()))
	{
		Process::iterator firstThread = process->begin();
		// Strategy only activates if first thread is active and there are other threads
		if(!((*firstThread)->IsComplete()) && (process->GetNoOfThreads() > 1))
		{
			shared_ptr<Core> firstCore = (*firstThread)->GetCore();
			shared_ptr<Core> secondCore;
			bool tooClose = false;
			Process::iterator nextThread = process->begin() + 1;
			// If the memoryFactor between the first and any other thread is >=0.5 then they are tooClose
			while(!tooClose && nextThread != process->end())
			{
				if(!(*nextThread)->IsComplete())
				{
					secondCore = (*nextThread)->GetCore();
					if(pMemModel->GetMemoryFactor(firstCore,secondCore) >= 0.5)
					{
						tooClose = true;
					}
				}
				nextThread++;
			}

			if(tooClose)
			{
				shared_ptr<Core> bestCore = pMemModel->IteratorFirst();
				double minLoad = (pMemModel->IteratorFirst())->GetActivityLevel();
				shared_ptr<Core> nextCore;

				bool found = false;
				pMemModel->IteratorReset();
				// Iterate through all cores and find the latest one with low load
				while(!pMemModel->IteratorComplete())
				{
					nextCore = pMemModel->IteratorNext();
					double load = nextCore->GetActivityLevel();
					if(load <= minLoad)
					{
						bestCore = nextCore;
						minLoad = load;
					}
				}

				// Move the thread and update the memory penalties
				firstCore->RemoveThread(*firstThread);
				bestCore->AddThread(*firstThread,bestCore);
				process->UpdatePenalties(pMemModel);
			}
		}
	}
}



// Idlest core is defined as:
// 1. No core has a lower load, and
// 2. No core has a lower combined load on its adjacent cores (level1)
// If a core is found that has zero load on itself and its level1 cores the search is stopped 
void TPStrategyDemo::AllocateThreadToIdlestCore(std::shared_ptr<Thread> pThread)
{
	double minFirstLoad = (pMemModel->IteratorFirst())->GetActivityLevel() + 1;
	double minTotalLoad  = std::numeric_limits<double>::max();
	shared_ptr<Core> nextCore;
	shared_ptr<Core> bestCore = pMemModel->IteratorFirst();
	bool found = false;
	pMemModel->IteratorReset();
	// Iterate through cores
	while(!found && !pMemModel->IteratorComplete())
	{
		nextCore = pMemModel->IteratorNext();
		double firstLoad = nextCore->GetActivityLevel();
		double totalLoad = 0;
		// If the load on this core is equal to the minimum then examine the level1 cores
		if(firstLoad <= minFirstLoad)
		{
			list<shared_ptr<Core> > adjacentCores;
			pMemModel->FindNearestCores(adjacentCores,nextCore,1);
			for(list<shared_ptr<Core> >::iterator adjCoreIter = adjacentCores.begin(); adjCoreIter != adjacentCores.end(); ++adjCoreIter)
			{
				totalLoad = totalLoad + (*adjCoreIter)->GetActivityLevel();
			}
		}
		bool betterFirstLoad = (firstLoad < minFirstLoad) ? true:false;
		bool betterTotalLoad = (totalLoad < minTotalLoad) ? true:false;
		// If current load is better OR current load is equal and surrounding load is better 
		if(betterFirstLoad || ((firstLoad == minFirstLoad) && betterTotalLoad))
		{
			bestCore = nextCore;
			minFirstLoad = firstLoad;
			minTotalLoad = totalLoad;
		}

		// If first core and adjacent cores are empty stop searching
		if((minFirstLoad == 0) && (minTotalLoad == 0))
		{
			found = true;
		}
	}

	// If the thread is already on a core then remove it
	if(pThread->GetCore())
	{
		pThread->GetCore()->RemoveThread(pThread);
	}
	// Allocate thread to best core
	bestCore->AddThread(pThread,bestCore);
}