#pragma once
#include "ProbDist.h"

#include <random>

class ProbDistPoisson: public ProbDist
{
private:
	std::poisson_distribution<int> dist;
	std::default_random_engine generator;
public:
	ProbDistPoisson(double mean, unsigned int seedVal);
	~ProbDistPoisson(void);
	int GetNextInt();
	double GetNextDouble();
	int GetNextIntGEZero();
	double GetNextDoubleGEZero();
	int GetNextIntGTZero();
	double GetNextDoubleGTZero();
};

