#include "stdafx.h"
#include "ProbDistConstant.h"

#include <limits>


ProbDistConstant::ProbDistConstant(double constIn):constVal(constIn)
{
}


ProbDistConstant::~ProbDistConstant(void)
{
}


// Rounding function inherited from base class
int ProbDistConstant::GetNextInt()
{
	return RounddoubleToInt(constVal);
}


double ProbDistConstant::GetNextDouble()
{
	return constVal;
}

// If const value < 0 then return 0 by default
int ProbDistConstant::GetNextIntGEZero()
{
	if(constVal >= 0)
	{
		return GetNextInt();
	}
	else
	{
		return 0;
	}
}

// If const value < 0 then return 0 by default
double ProbDistConstant::GetNextDoubleGEZero()
{
	if(constVal >= 0)
	{
		return GetNextDouble();
	}
	else
	{
		return 0;
	}
}

// If const value !> 0 then return 1 by default
int ProbDistConstant::GetNextIntGTZero()
{
	if(constVal > 0)
	{
		return GetNextInt();
	}
	else
	{
		return 1;
	}
}

// If const value !> 0 then return smallest value of double by default
double ProbDistConstant::GetNextDoubleGTZero()
{
	if(constVal > 0)
	{
		return GetNextDouble();
	}
	else
	{
		return std::numeric_limits<double>::epsilon();
	}
}