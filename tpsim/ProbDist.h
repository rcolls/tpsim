#pragma once
#include <string>

class ProbDist
{
public:
	ProbDist();
	virtual ~ProbDist(void);
	virtual int GetNextInt() = 0;
	virtual double GetNextDouble() = 0;
	virtual int GetNextIntGEZero() = 0;
	virtual double GetNextDoubleGEZero() = 0;
	virtual int GetNextIntGTZero() = 0;
	virtual double GetNextDoubleGTZero() = 0;
	int ProbDist::RounddoubleToInt(double f);
};



