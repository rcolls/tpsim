#pragma once
#pragma warning(disable : 4996)

#include <fstream>
#include <vector>

class SimProbabilities;

class OutputResults
{
private:
	std::vector<std::string> outputOptions;
	std::ofstream coreInfoStream;
	std::ofstream threadInfoStream;
	int coreOutputInterval;

	bool OpenStream(std::ofstream &stream, std::string filename);
	void CloseStream(std::ofstream &stream);
	bool TestStream(std::ofstream &stream);
public:
	OutputResults();
	~OutputResults(void);
	std::vector<std::string> GetOutputOptions();
	bool ActivateCoreInfoOption(std::string filename, int interval);
	bool ActivateThreadInfoOption(std::string filename);
	void Close();
	void CloseCoreStream();
	void CloseThreadStream();
	void WriteCoreInfo(std::string output);
	void WriteCoreInfo(int output);
	void WriteCoreInfo(double output);
	void WriteThreadInfo(std::string output);
	void WriteThreadInfo(int output);
	void WriteThreadInfo(double output);
	int GetCoreOutputInterval();
	bool CoreInfoIsActive();
	bool ThreadInfoIsActive();
	void WriteDateTimeInfo();
};

