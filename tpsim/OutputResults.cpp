#include "stdafx.h"
#include "OutputResults.h"
#include "SimProbabilities.h"

#include <fstream>
#include <string>
#include <ctime>
#include <chrono>
#include <iomanip>

using std::string;
using std::vector;

OutputResults::OutputResults()
{
	// These are the strings the ConfigFileReader object will try to match
	outputOptions.push_back("outputCoreLoad");
	outputOptions.push_back("outputRunTimes");
}

OutputResults::~OutputResults(void)
{
	Close();
}

// Returns strings for matching
vector<string> OutputResults::GetOutputOptions()
{
	return outputOptions;
}


// Open stream for saving core load information
bool OutputResults::ActivateCoreInfoOption(string filename, int interval)
{
	coreOutputInterval = interval;
	return OpenStream(coreInfoStream,filename);
}


// Open stream for saving thread runtime information
bool OutputResults::ActivateThreadInfoOption(string filename)
{
	return OpenStream(threadInfoStream,filename);
}


// Close all open streams
void OutputResults::Close(void)
{
	CloseStream(coreInfoStream);
	CloseStream(threadInfoStream);
}


// Close core output stream only
void OutputResults::CloseCoreStream()
{
	CloseStream(coreInfoStream);
}


// Close thread output stream only
void OutputResults::CloseThreadStream()
{
	CloseStream(threadInfoStream);
}



void OutputResults::WriteCoreInfo(string output)
{
		coreInfoStream << output;
}

void OutputResults::WriteCoreInfo(int output)
{
		coreInfoStream << output;
}

void OutputResults::WriteCoreInfo(double output)
{
		coreInfoStream << output;
}

void OutputResults::WriteThreadInfo(string output)
{
		threadInfoStream << output;
}

void OutputResults::WriteThreadInfo(int output)
{
		threadInfoStream << output;
}

void OutputResults::WriteThreadInfo(double output)
{
		threadInfoStream << output;
}


// coreOutputInterval specifies how often (in timesteps) core load data should be written to file
int OutputResults::GetCoreOutputInterval()
{
	return coreOutputInterval;
}


// Check if the core load stream is active
bool OutputResults::CoreInfoIsActive()
{
	return TestStream(coreInfoStream);
}


// Check if the thread runtime stream is active
bool OutputResults::ThreadInfoIsActive()
{
	return TestStream(threadInfoStream);

}


// Write time and date info to file
// This function requires the pragma warning disable set in the header file
void OutputResults::WriteDateTimeInfo()
{
	// current date/time based on current system
	time_t now = time(0); 
	// convert now to string form
	char* dt = ctime(&now);

	if(TestStream(coreInfoStream))
	{
		coreInfoStream << "// Date and Time: " << dt;
	}
	if(TestStream(threadInfoStream))
	{
		threadInfoStream << "// Date and Time: " << dt;
	}
}



void OutputResults::CloseStream(std::ofstream &stream)
{
	if(TestStream(stream))
	{
		stream.close();
	}
}


bool OutputResults::OpenStream(std::ofstream &stream, string filename)
{
	try
	{
		stream.open(filename);
	}
	catch(...)
	{
	}

	return TestStream(stream);
}


bool OutputResults::TestStream(std::ofstream &stream)
{
	if(stream.is_open())
	{
		return true;
	}
	else
	{
		return false;
	}
}