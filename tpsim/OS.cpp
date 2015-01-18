#include "stdafx.h"
#include <vector>
#include <random>
#include <math.h>
#include "OS.h"
#include "Process.h"
#include "Thread.h"
#include "Core.h"
#include "SimProbabilities.h"
#include "OutputResults.h"
#include "TPStrategy.h"

#include <string>

using std::vector;
using std::shared_ptr;



OS::OS(std::shared_ptr<MemModel> memModel,std::shared_ptr<TPStrategy> pTPStrat, int maxProc):pMemModel(memModel),pTPStrategy(pTPStrat),processes(maxProc),time(0.0),noCreatedProcesses(0),threadsComplete(false)
{	
}


OS::~OS(void)
{
}


// Advance the simulation.
void OS::Run(double increment, double maxRuntime, SimProbabilities &simProbs, OutputResults &output)
{
	time = 0;
	// Track the number of steps as output of core information may not be required every time
	int stepCount = 1;

	while(!IsComplete(maxRuntime - increment))
	{
		time = time + increment;

		// Visit all cores and update threads appropriately.
		pMemModel->UpdateCores(increment);
		
		// Update all processes and check if they are complete.
		threadsComplete = true;
		for(int process = 0; process < noCreatedProcesses; process++)
		{
			pTPStrategy->MigrateThreads(&processes[process],this);
			// If ANY process is incomplete set member variable complete to FALSE
			if(!processes[process].IsComplete())
			{
				threadsComplete = false;
			}
		}

		// Consider creating new processes
		// Decision is decided probabilistically by the simProbs object.
		if(noCreatedProcesses < processes.size())
		{
			// Still room for more processes
			threadsComplete = false;

			if(simProbs.GetNewProcessDecision() > 0)
			{
				// Number of new processes at this timestep is generated probabilistically by the simProbs object.
				// Also ensure maximum is not exceeded.
				int noOfNewProcesses = std::min(simProbs.GetNoOfProcesses(),(int)(processes.size() - noCreatedProcesses));
				for(int i = 0; i < noOfNewProcesses; i++)
				{
					CreateProcess(simProbs);
				}
			}
		}

		// Print core load information to file (if required at this step)
		if((output.CoreInfoIsActive()) && (stepCount%output.GetCoreOutputInterval() == 0))
		{
			pMemModel->OutputThreadCount(output,time);
		}

		stepCount = stepCount + 1;
	}

	// Print thread information to file at the end of Run()
	if(output.ThreadInfoIsActive())
	{
		for (vector<Process>::iterator iter = processes.begin(); iter != processes.begin() + noCreatedProcesses; ++iter)
		{
			std::string incomplete = "";
			if(!iter->IsComplete())
			{
				incomplete = " (incomplete)";
			}
			output.WriteThreadInfo("Process" + incomplete + "\n");
			iter->OutputProcessInfo(output);
			output.WriteThreadInfo("\n");
		}
	}

	output.WriteDateTimeInfo();
}



// Return status of run
bool OS::IsComplete(double maxTime)
{
	if(threadsComplete || (time > maxTime))
	{
		return true;
	}
	else
	{
		return false;
	}
}




// Create a new process object and store it in Vector processes. Increase process count by 1.
// Number of threads associated with the process is generated probabilistically by the simProbs object.
void OS:: CreateProcess(SimProbabilities &simProbs)
{
	int noOfThreads = simProbs.GetNoOfThreads();
	processes[noCreatedProcesses] = Process(noOfThreads,pMemModel,pTPStrategy,simProbs,this);
	noCreatedProcesses = noCreatedProcesses + 1;
}

