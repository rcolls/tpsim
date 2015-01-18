#include "stdafx.h"
#include "ProbDistNormal.h"

#include <math.h>
#include <string>


ProbDistNormal::ProbDistNormal(double mean, double stDev, unsigned int seedVal):dist(mean,stDev)
{
	generator.seed(seedVal);
}


ProbDistNormal::~ProbDistNormal(void)
{
}


// Rounding function inherited from base class
int ProbDistNormal::GetNextInt()
{
	double next = GetNextDouble();
	return RounddoubleToInt(next);
}


double ProbDistNormal::GetNextDouble()
{
	return dist(generator);
}


int ProbDistNormal::GetNextIntGEZero()
{
	return RounddoubleToInt(GetNextDoubleGEZero());
}


// Keep trying until a valid value is obtained (no maximum loop limit)
double ProbDistNormal::GetNextDoubleGEZero()
{
	double nonNeg = GetNextDouble();
	while(nonNeg < 0.0)
	{
		nonNeg = GetNextDouble();
	}

	return nonNeg;
}


int ProbDistNormal::GetNextIntGTZero()
{
	int nonZero = RounddoubleToInt(GetNextDoubleGTZero());
	while(nonZero == 0)
	{
		nonZero = RounddoubleToInt(GetNextDoubleGTZero());;
	}

	return nonZero;
}


// Keep trying until a valid value is obtained (no maximum loop limit)
double ProbDistNormal::GetNextDoubleGTZero()
{
	double nonZero = GetNextDouble();
	while(nonZero <= 0)
	{
		nonZero = GetNextDouble();
	}

	return nonZero;
}

