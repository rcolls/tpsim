#include "stdafx.h"
#include "ProbDistBernoulli.h"
#include "ProbDist.h"


ProbDistBernoulli::ProbDistBernoulli(double prob, unsigned int seedVal):dist(prob)
{
	generator.seed(seedVal);
}


ProbDistBernoulli::~ProbDistBernoulli(void)
{
}

// Parse bool to int
int ProbDistBernoulli::GetNextInt()
{
	return (int)dist(generator);
}


double ProbDistBernoulli::GetNextDouble()
{
	return (double)GetNextInt();
}

// Bernoulli returns either 0 or 1
int ProbDistBernoulli::GetNextIntGEZero()
{
	return GetNextInt();
}

// Bernoulli returns either 0 or 1
double ProbDistBernoulli::GetNextDoubleGEZero()
{
	return GetNextDouble();
}

// Bernoulli returns either 0 or 1
int ProbDistBernoulli::GetNextIntGTZero()
{
	return 1;
}

// Bernoulli returns either 0 or 1
double ProbDistBernoulli::GetNextDoubleGTZero()
{
	return 1.0;
}