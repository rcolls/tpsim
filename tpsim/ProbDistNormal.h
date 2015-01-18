#pragma once
#include "ProbDist.h"

#include <random>

class ProbDistNormal: public ProbDist
{
private:
	std::normal_distribution<double> dist;
	std::default_random_engine generator;
public:
	ProbDistNormal(double mean, double stDev, unsigned int seedVal);
	~ProbDistNormal(void);
	int GetNextInt();
	double GetNextDouble();
	int GetNextIntGEZero();
	double GetNextDoubleGEZero();
	int GetNextIntGTZero();
	double GetNextDoubleGTZero();
};

