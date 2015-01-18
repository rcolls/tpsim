#pragma once

#include <memory>

class OutputResults;
class Core;

class Thread
{
private:
	double minimumDuration;
	double remainingDuration;
	double runTime;
	double memoryFactor;
	std::shared_ptr<Core> pCore;
public:
	Thread(void);
	Thread(double duration);
	~Thread(void);
	double GetMinimumDuration();
	double GetRemainingDuration();
	double GetRunTime();
	double UpdateThread(double cpuTime, double lastCpuTime, double timeStep);
	bool IsComplete();
	void SetCore(std::shared_ptr<Core> core);
	std::shared_ptr<Core> GetCore();
	void SetMemoryFactor(double factor);
	double GetMemoryFactor();
	void OutputThreadInfo(OutputResults &res);
};

