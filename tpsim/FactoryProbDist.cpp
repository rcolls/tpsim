#include "stdafx.h"
#include "FactoryProbDist.h"
#include "ProbDist.h"
#include "ProbDistPoisson.h"
#include "ProbDistNormal.h"
#include "ProbDistBernoulli.h"
#include "ProbDistConstant.h"

#include <string>
#include <random>

using std::vector;
using std::string;
using std::shared_ptr;


FactoryProbDist::FactoryProbDist(void)
{
}


FactoryProbDist::~FactoryProbDist(void)
{
}


// Create a new ProbDist object according to spec contained in 'parameters' (return pointer by reference: default to null).
// If 'parameters' contains an entry directing the distribution to generate a random seed ('random') this will be replaced
// in 'parameters' by a string representation of the seed
// TPSIM_ERROR messages are appended and returned by reference
bool FactoryProbDist::CreateNew(vector<string> &parameters,shared_ptr<ProbDist> &pDistribution,string &errMessage)
{
	bool valid = false;
	pDistribution = nullptr;

	// Catch empty vector case
	if(parameters.size() == 0)
	{
		errMessage = errMessage + "TPSIM_ERROR: probability distribution has no associated parameters.\n";
		return false;
	}

	// Distribution name will be first vector element
	string dist = parameters[0];

	// Poisson distribution expects 1 double input
	if(dist.compare("Poisson") == 0)
	{
		try
		{
			double lambda = stod(parameters.at(1));
			if(lambda > 0)
			{
				unsigned int seedVal = 0;
				valid = GetSeed(parameters.at(2),seedVal,errMessage);
				if(valid)
				{
					pDistribution.reset(new ProbDistPoisson(lambda,seedVal));
					parameters[2] =  std::to_string(seedVal);
					valid = true;
				}
				else
				{
					errMessage = errMessage + "TPSIM_ERROR: FactoryProbDist cannot construct " + dist + ". Possibly seed option is invalid.\n";
				}
			}
			else
			{
				errMessage = errMessage + "TPSIM_ERROR: FactoryProbDist cannot construct " + dist + ". Input parameter must be greater than zero.\n";
			}
		}
		catch(...)
		{
			errMessage = errMessage + "TPSIM_ERROR: FactoryProbDist cannot construct " + dist + ". Expecting [double] ['random' or uint] after distribution name.\n";
		}
	}
	// Normal distribution expects 2 double inputs
	else if(dist.compare("Normal") == 0)
	{
		try
		{
			double mean = stod(parameters.at(1));
			double stDev = stod(parameters.at(2));
			if(stDev > 0)
			{
				unsigned int seedVal = 0;
				valid = GetSeed(parameters.at(3),seedVal,errMessage);
				if(valid)
				{
					pDistribution.reset(new ProbDistNormal(mean,stDev,seedVal));
					parameters[3] =  std::to_string(seedVal);
					valid = true;
				}
				else
				{
					errMessage = errMessage + "TPSIM_ERROR: FactoryProbDist cannot construct " + dist + ". Possibly seed option is invalid.\n";
				}
			}
			else
			{
				errMessage = errMessage + "TPSIM_ERROR: Normal distribution stDev must be greater than zero.\n";
			}
		}
		catch(...)
		{
			errMessage = errMessage + "TPSIM_ERROR: FactoryProbDist cannot construct " + dist + ". Expecting [double] [double] ['random' or uint] after distribution name.\n";
		}
	}
	// Bernoulli distribution expects 1 double input
	else if(dist.compare("Bernoulli") == 0)
	{
		try
		{
			double prob = stod(parameters.at(1));
			if(prob < 0 || prob > 1)
			{
				errMessage = errMessage + "TPSIM_ERROR: Bernoulli distribution parameter must be 0<=p<=1.\n";
				valid = false;
			}
			else
			{
				unsigned int seedVal = 0;
				valid = GetSeed(parameters.at(2),seedVal,errMessage);
				if(valid)
				{
					pDistribution.reset(new ProbDistBernoulli(prob,seedVal));
					parameters[2] =  std::to_string(seedVal);
					valid = true;
				}
				else
				{
					errMessage = errMessage + "TPSIM_ERROR: FactoryProbDist cannot construct " + dist + ". Possibly seed option is invalid.\n";
				}
			}
		}
		catch(...)
		{
			errMessage = errMessage + "TPSIM_ERROR: FactoryProbDist cannot construct " + dist + ". Expecting [double] ['random' or uint] after distribution name.\n";
		}
	}
	// Constant distribution expects 1 double input
	else if(dist.compare("Constant") == 0)
	{
		try
		{
			double constVal = stod(parameters.at(1));
			pDistribution.reset(new ProbDistConstant(constVal));
			valid = true;
		}
		catch(...)
		{
			errMessage = errMessage + "TPSIM_ERROR: FactoryProbDist cannot construct " + dist + ". Expecting [double] after distribution name.\n";
		}
	}
	// No matching distribution name.
	else
	{
		errMessage = errMessage + "TPSIM_ERROR: FactoryProbDist does not recognize " + dist + ".\n";
		valid = false;
	}

	return valid;
}


// If seedString is 'random' then generate a random number using the default system device.
// Otherwise try to parse it to an unsigned integer. Return by reference in both cases (default to zero). 
bool FactoryProbDist::GetSeed(string seedString, unsigned int &seedVal, string &errMessage)
{
	seedVal = 0;
	if(seedString.compare("random") == 0)
	{
		std::random_device rd;
		seedVal = rd();
		return true;
	}
	else
	{
		try
		{
			seedVal = stoul(seedString);
			return true;
		}
		catch(...)
		{
			errMessage = errMessage + "TPSIM_ERROR: Cannot parse " + seedString + " to a uint.\n";
			return false;
		}
	}
}