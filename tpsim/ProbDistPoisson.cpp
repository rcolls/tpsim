#include "stdafx.h"
#include "ProbDistPoisson.h"

#include <string>



ProbDistPoisson::ProbDistPoisson(double mean,unsigned int seedVal):dist(mean)
{
	generator.seed(seedVal);
}


ProbDistPoisson::~ProbDistPoisson(void)
{
}

int ProbDistPoisson::GetNextInt()
{
	return dist(generator);
}

double ProbDistPoisson::GetNextDouble()
{
	return (double)GetNextInt();
}

// All values generated by Poisson are >= 0
int ProbDistPoisson::GetNextIntGEZero()
{
	return GetNextInt();
}

double ProbDistPoisson::GetNextDoubleGEZero()
{
	return GetNextDouble();
}

// Keep trying until a valid value is obtained (no maximum loop limit)
int ProbDistPoisson::GetNextIntGTZero()
{
	int nonZero = GetNextInt();
	while(nonZero == 0)
	{
		nonZero = GetNextInt();
	}

	return nonZero;
}


double ProbDistPoisson::GetNextDoubleGTZero()
{
	return (double)GetNextIntGTZero();
}
