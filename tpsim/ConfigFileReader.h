#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>

class MemModel;
class ProbDist;
class OutputResults;
class TPStrategy;

class ConfigFileReader
{
private:
	std::map<std::string,std::vector<std::string> > input;
	bool validStream;
public:
	ConfigFileReader(std::string fileName);
	~ConfigFileReader(void);
	bool StreamValid();
	void OutputParameters(std::string id, OutputResults &results);
	bool ExtractParameters(std::string id, std::vector<std::string> &params);
	bool AssignParameter(std::string id, int &intVal, std::string &errMessage);
	bool AssignParameter(std::string id, double &doubleVal, std::string &errMessage);
	bool AssignParameter(std::string id, std::shared_ptr<MemModel> &pMemModel, std::string &errMessage);
	bool AssignParameter(std::string id, std::shared_ptr<ProbDist> &pDistribution, std::string &errMessage);
	bool AssignParameter(std::string id, std::shared_ptr<TPStrategy> &pTPStrategy, std::shared_ptr<MemModel> pMemModel,std::string &errMessage);
	bool AssignParameter(OutputResults &output, std::string &errMessage);
};

