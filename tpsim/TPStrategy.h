#pragma once
#include <memory>

class MemModel;
class Process;
class Thread;
class OS;

class TPStrategy
{
public:
	TPStrategy();
	virtual ~TPStrategy(void);
	virtual void AllocateThreadToCore(Process *process,std::shared_ptr<Thread> pThread, OS *os) = 0;
	virtual void MigrateThreads(Process *process, OS *os) = 0;
};

