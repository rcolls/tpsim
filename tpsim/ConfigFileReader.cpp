#include "stdafx.h"
#include "ConfigFileReader.h"
#include "FactoryMemModel.h"
#include "FactoryProbDist.h"
#include "OutputResults.h"
#include "FactoryTPStrategy.h"

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

using std::stringstream;
using std::vector;
using std::string;
using std::shared_ptr;

// Opens the specified file and stores all data in a map structure.
// Map key is first string on the line. Map value is all other strings on the line
// stored as a vector of the separated strings
ConfigFileReader::ConfigFileReader(string fileName):validStream(false)
{
	// Open file
	std::ifstream config(fileName); 

	if(!config.fail())
	{
		validStream = true;
		
		string line = "";
		string key = "";
		string word = "";

		// Loop until EOF. Read up to carriage return and store in 'line'
		while ( getline(config,line) )
		{
			// Convert string to stringstream and read the first word
			stringstream iss(line);
			iss >> key;
			// Ignore blank lines and those starting with double slash
			if (iss && (key.compare("//") != 0))
			{
				// Temp vector for this line
				vector<string> temp;
				iss >> word;
				// Add last read word to temp and try to read the next 
				while(iss)
				{
					temp.push_back(word);
					iss >> word;
				}
				// Add temp to map, using the first word on the line as a key
				input[key] = temp;
			}
		}

		// Close config file
		config.close();
	}
}


ConfigFileReader::~ConfigFileReader(void)
{
}


// Config file was opened
bool ConfigFileReader::StreamValid()
{
	return validStream;
}


// Searches map for key 'id'. If found return true and set 'params' to corresponding map entry
// If not found return false and set 'params' to an TPSIM_ERROR message 
bool ConfigFileReader::ExtractParameters(string id, vector<string> &params)
{
	params.clear();
	bool found = false;

	// If iterator reaches .end() then no match found
	std::map<string,vector<string> >::iterator it = input.find(id);
    if (it == input.end())
	{
		found = false;
		params.push_back("TPSIM_ERROR: could not find identifier " + id + " in config file.\n");
	}
    else
	{ 	
		found = true;
		params = it->second;
	}

	return found;
}


// Write data matching 'id' to file via OutputResults object
void ConfigFileReader::OutputParameters(string id, OutputResults &results)
{
	string outString = "// " + id + " ";
	vector<string> params;
	ExtractParameters(id,params);
	for(unsigned int i = 0; i < params.size(); i++)
	{
		outString = outString + " " + params[i];
	}
	outString = outString + "\n";

	if(results.CoreInfoIsActive())
	{
		results.WriteCoreInfo(outString);
	}
	if(results.ThreadInfoIsActive())
	{
		results.WriteThreadInfo(outString);
	}

}


// Search for key 'id' and try to parse entry to integer (return by reference: default to zero); returns any TPSIM_ERROR messages by reference
bool ConfigFileReader::AssignParameter(string id, int &intVal, string &errMessage)
{
	vector<string> params;
	bool valid = true;
	intVal = 0;

	bool found = ExtractParameters(id, params);
	if(found)
	{
		try
		{
			intVal = std::stoi(params.at(0));
		}
		catch(...)
		{
			errMessage = errMessage + "TPSIM_ERROR: could not convert parameter associated with " + id + " to an integer.\n";
			valid = false;
		}
	}
	else
	{
		errMessage = errMessage + "TPSIM_ERROR: could not find identifier " + id + " in config file.\n";
		valid = false;
	}

	return valid;
}


// Search for key 'id' and try to parse entry to double (return by reference: default to zero); returns any TPSIM_ERROR messages by reference
bool ConfigFileReader::AssignParameter(string id, double &doubleVal, string &errMessage)
{
	vector<string> params;
	bool valid = true;
	doubleVal = 0;

	bool found = ExtractParameters(id, params);
	if(found)
	{
		try
		{
			doubleVal = std::stod(params.at(0));
		}
		catch(...)
		{
			errMessage = errMessage + "TPSIM_ERROR: could not convert parameter associated with " + id + " to a double.\n";
			valid = false;
		}
	}
	else
	{
		errMessage = errMessage + "TPSIM_ERROR: could not find identifier " + id + " in config file.\n";
		valid = false;
	}

	return valid;
}


// Search for key 'id' and pass entry to FactoryMemModel (return pointer by reference: default to null); TPSIM_ERROR messages are appended to
// any returned from the factory and returned by reference
bool ConfigFileReader::AssignParameter(string id, shared_ptr<MemModel> &pMemModel, string &errMessage)
{
	vector<string> params;
	pMemModel = nullptr;

	bool valid = ExtractParameters(id, params);
	if(valid)
	{
		valid = FactoryMemModel::CreateMemModel(params,pMemModel,errMessage);
		if(!valid)
		{
			errMessage = errMessage + "TPSIM_ERROR: could not create MemModel.\n";;
		}
	}
	else
	{
		errMessage = errMessage + "TPSIM_ERROR: could not find identifier " + id + " in config file.\n";
	}

	return valid;
}


// Search for key 'id' and pass entry to FactoryProbDist (return pointer by reference: default to null); TPSIM_ERROR messages are appended to
// any returned from the factory and returned by reference
bool ConfigFileReader::AssignParameter(string id, std::shared_ptr<ProbDist> &pDistribution, string &errMessage)
{
	vector<string> params;
	pDistribution = nullptr;

	bool valid = ExtractParameters(id, params);
	if(valid)
	{
		valid = FactoryProbDist::CreateNew(params, pDistribution, errMessage);
		input[id] = params;
		if(!valid)
		{
			errMessage = errMessage + "TPSIM_ERROR: could not create Probability Distribution " + id + ".\n";
		}
	}
	else
	{
		errMessage = errMessage + "TPSIM_ERROR: could not find identifier " + id + " in config file.\n";
	}

	return valid;
}


// Search for key 'id' and pass entry to FactoryTPStrategy (return pointer by reference: default to null); TPSIM_ERROR messages are appended to
// any returned from the factory and returned by reference
bool ConfigFileReader::AssignParameter(std::string id, std::shared_ptr<TPStrategy> &pTPStrategy, std::shared_ptr<MemModel> pMemModel,std::string &errMessage)
{
	vector<string> params;
	pTPStrategy = nullptr;

	bool valid = ExtractParameters(id, params);
	if(valid)
	{
		valid = FactoryTPStrategy::CreateTPStrategy(params, pTPStrategy, pMemModel,errMessage);
		if(!valid)
		{
			errMessage = errMessage + "TPSIM_ERROR: could not create Thread Placement Strategy.\n";
		}
	}
	else
	{
		errMessage = errMessage + "TPSIM_ERROR: could not find identifier " + id + " in config file.\n";
	}

	return valid;
}


// Loop through all output options in the OutputResults object and try to parse matching map entries.
// Matching data is set directly in the OutputResults object. TPSIM_ERROR messages are returned by reference
bool ConfigFileReader::AssignParameter(OutputResults &output, string &errMessage)
{
	vector<string> params;
	vector<string> outputOptions = output.GetOutputOptions();
	bool valid = true;

	// Loop through all options 
	for(vector<string>::iterator option = outputOptions.begin(); option != outputOptions.end(); ++option)
	{
		bool found = ExtractParameters(*option, params);
		if(found)
		{
			if(params.size() > 0)
			{
				// First entry after name should be either 'on' or 'off'
				if(params[0].compare("on") == 0)
				{
					// Output of no of threads on a core; should specify filename for output and number of steps between outputs
					if(option->compare("outputCoreLoad") == 0)
					{
						try
						{
							string coreLoadFilename = params.at(1);
							int coreLoadOutputInterval = std::stoi(params.at(2));
							output.ActivateCoreInfoOption(coreLoadFilename,coreLoadOutputInterval);
						}
						catch(...)
						{
							errMessage = errMessage + "TPSIM_ERROR: Cannot parse input for " + (*option) + ". Expecting [string] [int] after on/off option.\n";
							valid = false;
						}
					}
					// Output of thread runtimes; should specify filename for output
					else if(option->compare("outputRunTimes") == 0)
					{
						if(params.size() > 1)
						{
							string coreLoadFilename = params.at(1);
							output.ActivateThreadInfoOption(coreLoadFilename);
						}
						else
						{
							errMessage = errMessage + "TPSIM_ERROR: Cannot parse input for " + (*option) + ". Expecting [string] after on/off option.\n";
							valid = false;
						}
					}
					else
					{
						errMessage = errMessage + "TPSIM_ERROR: " + *option + " not a recognized output option\n";
						valid = false;
					}
				}
				else if(params[0].compare("off") != 0)
				{
					errMessage = errMessage + "TPSIM_ERROR: first option associated with " + *option + " should be 'on' or 'off'\n";
					valid = false;
				}
			}
			else
			{
				errMessage = errMessage + "TPSIM_ERROR: no options associated with " + *option + "\n";
				valid = false;
			}
		}
		else
		{
			errMessage = errMessage + "TPSIM_ERROR: could not find identifier " + *option + " in config file.\n";
			valid = false;
		}
	}

	return valid;
}
