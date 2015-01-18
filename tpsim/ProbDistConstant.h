#pragma once
#include "ProbDist.h"
class ProbDistConstant :
	public ProbDist
{
private:
	double constVal;
public:
	ProbDistConstant(double constVal);
	~ProbDistConstant(void);
	int GetNextInt();
	double GetNextDouble();
	int GetNextIntGEZero();
	double GetNextDoubleGEZero();
	int GetNextIntGTZero();
	double GetNextDoubleGTZero();
};

