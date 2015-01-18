#pragma once
#include <vector>
#include <memory>
#include <string>

class TPStrategy;
class MemModel;

class FactoryTPStrategy
{
public:
	FactoryTPStrategy(void);
	~FactoryTPStrategy(void);
	static bool CreateTPStrategy(std::vector<std::string> parameters,std::shared_ptr<TPStrategy> &pTPStrategy,std::shared_ptr<MemModel> pMemModel,std::string &errMessage);
};

