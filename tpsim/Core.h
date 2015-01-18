#pragma once
#include<list>
#include <memory>

class Thread;

class Core
{
private:
	int coreNo;
	std::list<std::shared_ptr<Thread> > threads;
public:
	Core(int coreNo);
	Core(void);
	~Core(void);
	int GetCoreNo();
	int GetNoOfThreads();
	double GetActivityLevel();
	void AddThread(std::shared_ptr<Thread> pthread, std::shared_ptr<Core> pCore);
	void RemoveThread(std::shared_ptr<Thread> oldThread);
	void UpdateCore(double coreTime);
};

