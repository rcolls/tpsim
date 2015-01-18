#include "stdafx.h"
#include "FactoryTPStrategy.h"
#include "TPStrategyDemo.h"

using std::vector;
using std::string;
using std::shared_ptr;


FactoryTPStrategy::FactoryTPStrategy(void)
{
}


FactoryTPStrategy::~FactoryTPStrategy(void)
{
}

// Create a new TPStrategy object according to spec contained in 'parameters' (return pointer by reference: default to null).
// TPSIM_ERROR messages are appended and returned by reference
bool FactoryTPStrategy::CreateTPStrategy(vector<string> parameters,shared_ptr<TPStrategy> &pTPStrategy,shared_ptr<MemModel> pMemModel,string &errMessage)
{
	bool valid = false;
	pTPStrategy = nullptr;

	// Catch empty vector case
	if(parameters.size() == 0)
	{
		errMessage = errMessage + "TPSIM_ERROR: TPStrategy has no associated parameters.\n";
		return false;
	}

	// Strategy name will be first vector element
	string strategy = parameters[0];
	// TPStrategyDemo constructor expects 1 string input
	if(strategy.compare("TPStrategyDemo") == 0)
	{
		try
		{
			bool migOn = false;
			if((parameters.at(1)).compare("migOn") == 0)
			{
				migOn = true;
			}
			pTPStrategy.reset(new TPStrategyDemo(pMemModel,migOn));
			valid = true;
		}
		catch(...)
		{
			errMessage = errMessage + "TPSIM_ERROR: FactoryTPStrategy cannot construct " + strategy + ". Expecting [string] after model name\n";
			valid = false;
		}
	}
	// No matching strategy name.
	else
	{
		errMessage = errMessage + "TPSIM_ERROR: FactoryMemModel does not recognize " + strategy + ".\n";
		valid = false;
	}

	return valid;
}
