#pragma once
#include "ProbDist.h"

#include <random>

class ProbDistBernoulli: public ProbDist
{
private:
	std::bernoulli_distribution dist;
	std::default_random_engine generator;
public:
	ProbDistBernoulli(double prob, unsigned int seedVal);
	~ProbDistBernoulli(void);
	int GetNextInt();
	double GetNextDouble();
	int GetNextIntGEZero();
	double GetNextDoubleGEZero();
	int GetNextIntGTZero();
	double GetNextDoubleGTZero();
};

