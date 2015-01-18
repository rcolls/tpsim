#include "stdafx.h"
#include "stdlib.h"
#include "OS.h"
#include "SimProbabilities.h"
#include "ConfigFileReader.h"
#include "OutputResults.h"
#include "TPStrategy.h"

#include <iostream>
#include <string>

using std::string;
using std::shared_ptr;
using std::vector;


int main()
{
	// Read config file
	ConfigFileReader config("config.txt");

	if(config.StreamValid())
	{
		string errMessage;
		bool valid = true;

		shared_ptr<MemModel> pMemModel;
		// Extract the row associated with the memory model
		if(!config.AssignParameter("MemModel",pMemModel,errMessage))
		{
			valid = false;
		}

		shared_ptr<TPStrategy> pTPStrategy;
		// Extract the row associated with the thread placement strategy
		if(!config.AssignParameter("TPStrategy",pTPStrategy,pMemModel,errMessage))
		{
			valid = false;
		}

		shared_ptr<ProbDist> pdurationDist;
		// Extract the row associated with the probability distribution for thread durations
		if(!config.AssignParameter("threadDurationDistribution",pdurationDist,errMessage))
		{
			valid = false;
		}
		shared_ptr<ProbDist> pnoThreadsDist;
		// Extract the row associated with the probability distribution for number of threads per process
		if(!config.AssignParameter("noOfThreadsDistribution",pnoThreadsDist,errMessage))
		{
			valid = false;
		}
		shared_ptr<ProbDist> pnoProcessDist;
		// Extract the row associated with the probability distribution for number of processes at a timestep
		if(!config.AssignParameter("noOfProcessesDistribution",pnoProcessDist,errMessage))
		{
			valid = false;
		}
		shared_ptr<ProbDist> pnewProcessDist;
			// Extract the row associated with the probability distribution for creating a new process at a timestep
		if(!config.AssignParameter("newProcessCreationDistribution",pnewProcessDist,errMessage))
		{
			valid = false;
		}

		// Bundle probability distributions
		SimProbabilities simProbs(pdurationDist,pnoThreadsDist,pnoProcessDist,pnewProcessDist);

		// Assign values to primitives used in the main function. 
		int maxProcesses = 0;
		if(!config.AssignParameter("maxProcesses", maxProcesses, errMessage))
		{
			valid = false;
		}

		double maxRuntime = 0;
		if(!config.AssignParameter("maxRuntime", maxRuntime, errMessage))
		{
			valid = false;
		}
	
		double stepSize = 0;
		if(!config.AssignParameter("stepSize", stepSize, errMessage))
		{
			valid = false;
		}

		if(maxProcesses <= 0 || maxRuntime <= 0 || stepSize <= 0)
		{
			errMessage = errMessage + "TPSIM_ERROR: maxProcesses, maxRuntime and stepSize must all be > 0\n";
			valid = false;
		}


		OutputResults output;
		if(!config.AssignParameter(output, errMessage))
		{
			valid = false;
		}


		if(valid)
		{
			// Operating system creates processes and threads and allocates them to cores
			OS os(pMemModel,pTPStrategy,maxProcesses);
			// Write config information to results files
			output.WriteDateTimeInfo();
			config.OutputParameters("maxProcesses",output);
			config.OutputParameters("maxRuntime",output);
			config.OutputParameters("stepSize",output);
			config.OutputParameters("MemModel",output);
			config.OutputParameters("TPStrategy",output);
			config.OutputParameters("threadDurationDistribution",output);
			config.OutputParameters("noOfThreadsDistribution", output);
			config.OutputParameters("noOfProcessesDistribution",output);
			config.OutputParameters("newProcessCreationDistribution",output);
			config.OutputParameters("outputCoreLoad",output);
			config.OutputParameters("outputRunTimes",output);
			if(output.CoreInfoIsActive())
			{
				output.WriteCoreInfo("\n\n\n");
			}
			if(output.CoreInfoIsActive())
			{
				output.WriteThreadInfo("\n\n\n");
			}


			// Start the simulation	
			os.Run(stepSize,maxRuntime,simProbs,output);

			// Close filestreams
			output.Close();

			std::cout << "tpsim complete.";
		}
		else
		{
			// Print TPSIM_ERROR messages to console
			std::cerr << errMessage;
		}
	}
	else
	{
		std::cout << "TPSIM_ERROR: failed to open config file.";
	}
	return 0;
}

