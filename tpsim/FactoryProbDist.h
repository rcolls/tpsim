#pragma once
#include <vector>
#include <memory>
#include <string>

class ProbDist;

class FactoryProbDist
{
public:
	FactoryProbDist(void);
	~FactoryProbDist(void);
	static bool GetSeed(std::string seedString, unsigned int &seedVal, std::string &errMessage);
	static bool CreateNew(std::vector<std::string> &parameters,std::shared_ptr<ProbDist> &pDistribution,std::string &errMessage);
};

