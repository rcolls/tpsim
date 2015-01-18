#pragma once
#include <vector>
#include <string>
#include <memory>

class MemModel;

class FactoryMemModel
{
public:
	FactoryMemModel(void);
	~FactoryMemModel(void);
	static bool CreateMemModel(std::vector<std::string> parameters,std::shared_ptr<MemModel> &pMemModel,std::string &errMessage);
};

