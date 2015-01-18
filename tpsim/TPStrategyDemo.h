#pragma once
#include "TPStrategy.h"


class Process;
class MemModel;
class OS;

class TPStrategyDemo : public TPStrategy
{
private:
	std::shared_ptr<MemModel> pMemModel;
	bool migOn;
	void AllocateThreadToIdlestCore(std::shared_ptr<Thread> pThread);
public:
	TPStrategyDemo(std::shared_ptr<MemModel> pMemModel, bool migrationOn);
	~TPStrategyDemo(void);
	void AllocateThreadToCore(Process *process,std::shared_ptr<Thread> pThread, OS *os);
	void MigrateThreads(Process *process, OS *os);
};

