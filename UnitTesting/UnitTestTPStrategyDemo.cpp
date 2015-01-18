#include "stdafx.h"
#include "CppUnitTest.h"
#include "TPStrategyDemo.cpp"
#include "MemModelDemo.h"
#include "ProbDistConstant.h"
#include "OS.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(UnitTestTPStrategyDemo)
	{
	public:
		
		TEST_METHOD(TPStrategyDemoAllocateThreadToCore1)
		{
			MemModel *memModel = new MemModelDemo(5,7);
			std::shared_ptr<MemModel> pMemModel(memModel);
			TPStrategy* tpstrat = new TPStrategyDemo(pMemModel,false);
			shared_ptr<TPStrategy> pTPStrat(tpstrat);
			ProbDist* probDist = new ProbDistConstant(1);
			shared_ptr<ProbDist> pDist(probDist);
			SimProbabilities simProbs(pDist,pDist,pDist,pDist);
			OS *os = new OS(pMemModel,pTPStrat,100);

			Process *proc = new Process(17,pMemModel,pTPStrat,simProbs,os);

			vector<int> coreNos;
			for(Process::iterator iter = proc->begin(); iter != proc->end(); ++iter)
			{
				coreNos.push_back((*iter)->GetCore()->GetCoreNo());
			}

			Assert::IsTrue((coreNos[0] == 1)
				        && (coreNos[1] == 2)  && (coreNos[6]  == 2)  && (coreNos[11] == 2) && (coreNos[16] == 2)
						&& (coreNos[2] == 8)  && (coreNos[7]  == 8)  && (coreNos[12] == 8)
						&& (coreNos[3] == 3)  && (coreNos[8]  == 3)  && (coreNos[13] == 3)
						&& (coreNos[4] == 9)  && (coreNos[9]  == 9)  && (coreNos[14] == 9)
						&& (coreNos[5] == 15) && (coreNos[10] == 15) && (coreNos[15] == 15));
		}

		TEST_METHOD(TPStrategyDemoAllocateThreadToCore2)
		{
			MemModel *memModel = new MemModelDemo(5,7);
			std::shared_ptr<MemModel> pMemModel(memModel);
			TPStrategy* tpstrat = new TPStrategyDemo(pMemModel,false);
			shared_ptr<TPStrategy> pTPStrat(tpstrat);
			ProbDist* probDist = new ProbDistConstant(1);
			shared_ptr<ProbDist> pDist(probDist);
			SimProbabilities simProbs(pDist,pDist,pDist,pDist);
			OS *os = new OS(pMemModel,pTPStrat,100);

			Process *proc = new Process(3,pMemModel,pTPStrat,simProbs,os);

			Process *proc2 = new Process(14,pMemModel,pTPStrat,simProbs,os);

			vector<int> coreNos;
			for(Process::iterator iter = proc2->begin(); iter != proc2->end(); ++iter)
			{
				coreNos.push_back((*iter)->GetCore()->GetCoreNo());
			}

			Assert::IsTrue((coreNos[0]  == 4)
				        && (coreNos[1]  == 3)  && (coreNos[8]  == 3)
						&& (coreNos[2]  == 5)  && (coreNos[9]  == 5) 
						&& (coreNos[3]  == 11) && (coreNos[10] == 11)  
						&&                        (coreNos[11] == 2) 
						&& (coreNos[4]  == 6)  && (coreNos[12] == 6)
						&& (coreNos[5]  == 10) && (coreNos[13] == 10)
						&& (coreNos[6]  == 12)
						&& (coreNos[7]  == 18));
		}

		TEST_METHOD(TPStrategyDemoAllocateThreadToCore3)
		{
			MemModel *memModel = new MemModelDemo(5,7);
			std::shared_ptr<MemModel> pMemModel(memModel);
			TPStrategy* tpstrat = new TPStrategyDemo(pMemModel,false);
			shared_ptr<TPStrategy> pTPStrat(tpstrat);
			ProbDist* probDist = new ProbDistConstant(1);
			shared_ptr<ProbDist> pDist(probDist);
			SimProbabilities simProbs(pDist,pDist,pDist,pDist);
			OS *os = new OS(pMemModel,pTPStrat,100);

			Process *proc1 = new Process(3,pMemModel,pTPStrat,simProbs,os);
			Process *proc2 = new Process(4,pMemModel,pTPStrat,simProbs,os);

			Process *proc = new Process(13,pMemModel,pTPStrat,simProbs,os);

			vector<int> coreNos;
			for(Process::iterator iter = proc->begin(); iter != proc->end(); ++iter)
			{
				coreNos.push_back((*iter)->GetCore()->GetCoreNo());
			}

			Assert::IsTrue((coreNos[0]  == 7)
				        && (coreNos[1]  == 6)  && (coreNos[5]  == 6)   && (coreNos[10]  == 6)
						&& (coreNos[2]  == 14) && (coreNos[6]  == 14)  && (coreNos[11]  == 14) 
						&&                        (coreNos[7]  == 5)   && (coreNos[12]  == 5)
						&& (coreNos[3] == 13)  && (coreNos[8]  == 13) 
						&& (coreNos[4] == 21)  && (coreNos[9]  == 21));
		}

		TEST_METHOD(TPStrategyDemoAllocateThreadToCore4)
		{
			MemModel *memModel = new MemModelDemo(5,7);
			std::shared_ptr<MemModel> pMemModel(memModel);
			TPStrategy* tpstrat = new TPStrategyDemo(pMemModel,false);
			shared_ptr<TPStrategy> pTPStrat(tpstrat);
			ProbDist* probDist = new ProbDistConstant(1);
			shared_ptr<ProbDist> pDist(probDist);
			SimProbabilities simProbs(pDist,pDist,pDist,pDist);
			OS *os = new OS(pMemModel,pTPStrat,100);

			Process *proc1 = new Process(6,pMemModel,pTPStrat,simProbs,os);
			Process *proc2 = new Process(8,pMemModel,pTPStrat,simProbs,os);

			Process *proc = new Process(23,pMemModel,pTPStrat,simProbs,os);

			vector<int> coreNos;
			for(Process::iterator iter = proc->begin(); iter != proc->end(); ++iter)
			{
				coreNos.push_back((*iter)->GetCore()->GetCoreNo());
			}

			Assert::IsTrue((coreNos[0]  == 17)
				        && (coreNos[1]  == 10)  && (coreNos[8]   == 10)  && (coreNos[20]  == 10)
						&& (coreNos[2]  == 16)  && (coreNos[9]   == 16)   && (coreNos[21]  == 16) 
						&& (coreNos[3]  == 18)  && (coreNos[10]  == 18)  && (coreNos[22]  == 18) 
						&& (coreNos[4]  == 24)  && (coreNos[11]  == 24)
						&&                         (coreNos[12]  ==  3)
						&&                         (coreNos[13]  ==  9)
						&&                         (coreNos[14]  == 11)
						&&                         (coreNos[15]  == 15)
						&&                         (coreNos[16]  == 19)
						&& (coreNos[5]  == 23)  && (coreNos[17]  == 23)
						&& (coreNos[6]  == 25)  && (coreNos[18]  == 25)
						&& (coreNos[7]  == 31)  && (coreNos[19]  == 31));
		}

		TEST_METHOD(TPStrategyDemoAllocateThreadToCore5)
		{
			MemModel *memModel = new MemModelDemo(5,7);
			std::shared_ptr<MemModel> pMemModel(memModel);
			TPStrategy* tpstrat = new TPStrategyDemo(pMemModel,false);
			shared_ptr<TPStrategy> pTPStrat(tpstrat);
			ProbDist* probDist = new ProbDistConstant(1);
			shared_ptr<ProbDist> pDist(probDist);
			SimProbabilities simProbs(pDist,pDist,pDist,pDist);
			OS *os = new OS(pMemModel,pTPStrat,100);

			Process *proc1 = new Process(6,pMemModel,pTPStrat,simProbs,os);
			Process *proc2 = new Process(8,pMemModel,pTPStrat,simProbs,os);
			Process *proc3 = new Process(4,pMemModel,pTPStrat,simProbs,os);
			Process *proc4 = new Process(3,pMemModel,pTPStrat,simProbs,os);
			Process *proc5 = new Process(5,pMemModel,pTPStrat,simProbs,os);
			Process *proc6 = new Process(1,pMemModel,pTPStrat,simProbs,os);

			Process *proc = new Process(6,pMemModel,pTPStrat,simProbs,os);

			vector<int> coreNos;
			for(Process::iterator iter = proc->begin(); iter != proc->end(); ++iter)
			{
				coreNos.push_back((*iter)->GetCore()->GetCoreNo());
			}

			Assert::IsTrue((coreNos[0]  == 35)
				        && (coreNos[1]  == 28)  && (coreNos[4]   == 28)
						&& (coreNos[2]  == 34)  && (coreNos[5]   == 34)
						&& (coreNos[3]  == 27));
		}

		TEST_METHOD(TPStrategyDemoAllocateThreadToCore6)
		{
			MemModel *memModel = new MemModelDemo(5,7);
			std::shared_ptr<MemModel> pMemModel(memModel);
			TPStrategy* tpstrat = new TPStrategyDemo(pMemModel,false);
			shared_ptr<TPStrategy> pTPStrat(tpstrat);
			ProbDist* probDist = new ProbDistConstant(1);
			shared_ptr<ProbDist> pDist(probDist);
			SimProbabilities simProbs(pDist,pDist,pDist,pDist);
			OS *os = new OS(pMemModel,pTPStrat,100);

			for(int i = 0; i < 35; i++)
			{
				Process *proc1 = new Process(1,pMemModel,pTPStrat,simProbs,os);
			}

			Process *proc = new Process(11,pMemModel,pTPStrat,simProbs,os);

			vector<int> coreNos;
			for(Process::iterator iter = proc->begin(); iter != proc->end(); ++iter)
			{
				coreNos.push_back((*iter)->GetCore()->GetCoreNo());
			}

			Assert::IsTrue((coreNos[0]  == 1)
				        && (coreNos[1]  == 2)  && (coreNos[6]   == 2)
						&& (coreNos[2]  == 8)  && (coreNos[7]   == 8)
						&& (coreNos[3]  == 3)  && (coreNos[8]   == 3)
						&& (coreNos[4]  == 9)  && (coreNos[9]   == 9)
						&& (coreNos[5]  == 15) && (coreNos[10]  == 15));
		}

		TEST_METHOD(TPStrategyDemoAllocateThreadToCore7)
		{
			MemModel *memModel = new MemModelDemo(5,7);
			std::shared_ptr<MemModel> pMemModel(memModel);
			TPStrategy* tpstrat = new TPStrategyDemo(pMemModel,false);
			shared_ptr<TPStrategy> pTPStrat(tpstrat);
			ProbDist* probDist = new ProbDistConstant(1);
			shared_ptr<ProbDist> pDist(probDist);
			SimProbabilities simProbs(pDist,pDist,pDist,pDist);
			OS *os = new OS(pMemModel,pTPStrat,100);

			Process *proc = new Process(3,pMemModel,pTPStrat,simProbs,os);

			tpstrat->MigrateThreads(proc,os);

			vector<int> coreNos;
			for(Process::iterator iter = proc->begin(); iter != proc->end(); ++iter)
			{
				coreNos.push_back((*iter)->GetCore()->GetCoreNo());
			}

			Assert::IsTrue((coreNos[0]  == 1) && (coreNos[1]  == 2) && (coreNos[2]  == 8));
		}

		TEST_METHOD(TPStrategyDemoAllocateThreadToCore8)
		{
			MemModel *memModel = new MemModelDemo(5,7);
			std::shared_ptr<MemModel> pMemModel(memModel);
			TPStrategy* tpstrat = new TPStrategyDemo(pMemModel,true);
			shared_ptr<TPStrategy> pTPStrat(tpstrat);
			ProbDist* probDist = new ProbDistConstant(1);
			shared_ptr<ProbDist> pDist(probDist);
			SimProbabilities simProbs(pDist,pDist,pDist,pDist);
			OS *os = new OS(pMemModel,pTPStrat,100);

			Process *proc = new Process(3,pMemModel,pTPStrat,simProbs,os);

			tpstrat->MigrateThreads(proc,os);

			vector<int> coreNos;
			for(Process::iterator iter = proc->begin(); iter != proc->end(); ++iter)
			{
				coreNos.push_back((*iter)->GetCore()->GetCoreNo());
			}

			Assert::IsTrue((coreNos[0]  == 35) && (coreNos[1]  == 2) && (coreNos[2]  == 8));
		}

		TEST_METHOD(TPStrategyDemoAllocateThreadToCore9)
		{
			MemModel *memModel = new MemModelDemo(5,7);
			std::shared_ptr<MemModel> pMemModel(memModel);
			TPStrategy* tpstrat = new TPStrategyDemo(pMemModel,true);
			shared_ptr<TPStrategy> pTPStrat(tpstrat);
			ProbDist* probDist = new ProbDistConstant(10);
			shared_ptr<ProbDist> pDist(probDist);
			SimProbabilities simProbs(pDist,pDist,pDist,pDist);
			OS *os = new OS(pMemModel,pTPStrat,100);

			Process *proc = new Process(3,pMemModel,pTPStrat,simProbs,os);

			vector<int> coreNos;
			coreNos.push_back((*proc->begin())->GetCore()->GetCoreNo());
			tpstrat->MigrateThreads(proc,os);
			coreNos.push_back((*proc->begin())->GetCore()->GetCoreNo());
			tpstrat->MigrateThreads(proc,os);
			coreNos.push_back((*proc->begin())->GetCore()->GetCoreNo());
			tpstrat->MigrateThreads(proc,os);
			coreNos.push_back((*proc->begin())->GetCore()->GetCoreNo());
			tpstrat->MigrateThreads(proc,os);
			coreNos.push_back((*proc->begin())->GetCore()->GetCoreNo());

			Assert::IsTrue((coreNos[0]  == 1) && (coreNos[1]  == 35) && (coreNos[2]  == 35) && (coreNos[3]  == 35) && (coreNos[4]  == 35));
		}

		TEST_METHOD(TPStrategyDemoAllocateThreadToCore10)
		{
			MemModel *memModel = new MemModelDemo(5,7);
			std::shared_ptr<MemModel> pMemModel(memModel);
			TPStrategy* tpstrat = new TPStrategyDemo(pMemModel,true);
			shared_ptr<TPStrategy> pTPStrat(tpstrat);
			ProbDist* probDist = new ProbDistConstant(1);
			shared_ptr<ProbDist> pDist(probDist);
			SimProbabilities simProbs(pDist,pDist,pDist,pDist);
			OS *os = new OS(pMemModel,pTPStrat,100);
			
			vector<Process*> processes;
			for(int i = 0; i < 5; i++)
			{
				Process *proc = new Process(4,pMemModel,pTPStrat,simProbs,os);
				processes.push_back(proc);
			}

			tpstrat->MigrateThreads(processes[0],os);
			tpstrat->MigrateThreads(processes[1],os);
			tpstrat->MigrateThreads(processes[4],os);
			tpstrat->MigrateThreads(processes[2],os);
			tpstrat->MigrateThreads(processes[3],os);

			vector<int> coreNos;
			for(vector<Process*>::iterator iter = (processes).begin(); iter != (processes).end(); ++iter)
			{
				Process *p = (*iter);
				shared_ptr<Thread> t = *(p->begin());
				coreNos.push_back(t->GetCore()->GetCoreNo());
			}

			Assert::IsTrue((coreNos[0]  == 35) && (coreNos[1]  == 34)  && (coreNos[4] == 33) && (coreNos[2]  == 32)  && (coreNos[3]   == 31));
		}

		TEST_METHOD(TPStrategyDemoAllocateThreadToCore11)
		{
			MemModel *memModel = new MemModelDemo(5,7);
			std::shared_ptr<MemModel> pMemModel(memModel);
			TPStrategy* tpstrat = new TPStrategyDemo(pMemModel,true);
			shared_ptr<TPStrategy> pTPStrat(tpstrat);
			ProbDist* probDist = new ProbDistConstant(1);
			shared_ptr<ProbDist> pDist(probDist);
			SimProbabilities simProbs(pDist,pDist,pDist,pDist);
			OS *os = new OS(pMemModel,pTPStrat,100);
			
			Process *proc = new Process(3,pMemModel,pTPStrat,simProbs,os);
			
			for(int i = 0; i < 32; i++)
			{
				Process *proc = new Process(1,pMemModel,pTPStrat,simProbs,os);
			}

			tpstrat->MigrateThreads(proc,os);

			Assert::IsTrue((*proc->begin())->GetCore()->GetCoreNo()  == 35);
		}
	};
}