#include "stdafx.h"
#include "FactoryMemModel.h"
#include "MemModel.h"
#include "MemModelDemo.h"

#include <vector>
#include <string>
#include <memory>

using std::string;
using std::vector;
using std::shared_ptr;
using std::stoi;

FactoryMemModel::FactoryMemModel(void)
{
}


FactoryMemModel::~FactoryMemModel(void)
{
}

// Create a new MemModel object according to spec contained in 'parameters' (return pointer by reference: default to null).
// TPSIM_ERROR messages are appended and returned by reference
bool FactoryMemModel::CreateMemModel(vector<string> parameters,shared_ptr<MemModel> &pMemModel,string &errMessage)
{
	bool valid = false;
	pMemModel = nullptr;

	// Catch empty vector case
	if(parameters.size() == 0)
	{
		errMessage = errMessage + "TPSIM_ERROR: MemModel has no associated parameters.\n";
		return false;
	}

	// Model name will be first vector element
	string model = parameters[0];
	// MemModelDemo constructor expects 2 integer inputs
	if(model.compare("MemModelDemo") == 0)
	{
		try
		{
			int noOfRows = stoi(parameters.at(1));
			int noOfCols = stoi(parameters.at(2));

			pMemModel.reset(new MemModelDemo(noOfRows,noOfCols));
			valid = true;
		}
		catch(...)
		{
			errMessage = errMessage + "TPSIM_ERROR: FactoryMemModel cannot construct " + model + ". Expecting [int] [int] after model name.\n";
			valid = false;
		}
	}
	// No matching model name.
	else
	{
		errMessage = errMessage + "TPSIM_ERROR: FactoryMemModel does not recognize " + model + ".\n";
		valid = false;
	}

	return valid;
}