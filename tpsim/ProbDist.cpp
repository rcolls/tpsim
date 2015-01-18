#include "stdafx.h"
#include "ProbDist.h"


ProbDist::ProbDist()
{
}


ProbDist::~ProbDist(void)
{
}


// Visual Studio 2012 does not provide a function to directly round double to int
// The following is suggested on	http://stackoverflow.com/questions/485525/round-for-double-in-c
int ProbDist::RounddoubleToInt(double f)
{
	int tmp = static_cast<int> (f);
	tmp += (f-tmp >= 0.5) - (f-tmp <= -0.5);
	return tmp;
}
