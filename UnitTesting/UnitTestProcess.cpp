#include "stdafx.h"
#include "CppUnitTest.h"
#include "Process.h"
#include "Process.cpp"
#include "MemModel.h"
#include "MemModel.cpp"
#include "MemModelDemo.h"
#include "MemModelDemo.cpp"
#include "SimProbabilities.h"
#include "SimProbabilities.cpp"
#include "TPStrategy.h"
#include "TPStrategy.cpp"
#include "TPStrategyDemo.h"
#include "ProbDist.h"
#include "ProbDist.cpp"
#include "ProbDistConstant.h"
#include "ProbDistConstant.cpp"
#include "OS.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTesting
{
	TEST_CLASS(UnitTestProcess)
	{
	public:
		
		TEST_METHOD(ProcessGetNoOfThreads)
		{
			MemModelDemo* memModel = new MemModelDemo(5,5);
			std::shared_ptr<MemModel> pMemModel(memModel);
			TPStrategy* tpStrat = new TPStrategyDemo(pMemModel, false);
			std::shared_ptr<TPStrategy> pTPStrategy(tpStrat);
			ProbDist* dist5 = new ProbDistConstant(5);
			std::shared_ptr<ProbDist> pDist5(dist5);
			ProbDist* dist1 = new ProbDistConstant(1);
			std::shared_ptr<ProbDist> pDist1(dist1);
			SimProbabilities simProbs(pDist1,pDist5,pDist1,pDist1);
			OS *os = new OS(pMemModel,pTPStrategy,100);
			Process process(5, pMemModel, pTPStrategy, simProbs,os);

			int noOfThreads = process.GetNoOfThreads();

			Assert::AreEqual(noOfThreads,5);
		}


		TEST_METHOD(ProcessIsComplete1)
		{
			MemModelDemo* memModel = new MemModelDemo(9,17);
			std::shared_ptr<MemModel> pMemModel(memModel);
			TPStrategy* tpStrat = new TPStrategyDemo(pMemModel, false);
			std::shared_ptr<TPStrategy> pTPStrategy(tpStrat);
			ProbDist* dist6 = new ProbDistConstant(6);
			std::shared_ptr<ProbDist> pDist6(dist6);
			ProbDist* dist4 = new ProbDistConstant(4);
			std::shared_ptr<ProbDist> pDist4(dist4);
			SimProbabilities simProbs(pDist4,pDist6,pDist6,pDist6);
			OS *os = new OS(pMemModel,pTPStrategy,100);
			Process process(8, pMemModel, pTPStrategy, simProbs, os);

			for(Process::iterator iter = process.begin(); iter != process.end(); ++iter)
			{
				(*iter)->UpdateThread(1,0,1);
			}

			Assert::IsFalse(process.IsComplete());
		}

		TEST_METHOD(ProcessIsComplete2)
		{
			MemModelDemo* memModel = new MemModelDemo(2,2);
			std::shared_ptr<MemModel> pMemModel(memModel);
			TPStrategy* tpStrat = new TPStrategyDemo(pMemModel, false);
			std::shared_ptr<TPStrategy> pTPStrategy(tpStrat);
			ProbDist* dist8 = new ProbDistConstant(8);
			std::shared_ptr<ProbDist> pDist8(dist8);
			ProbDist* dist10 = new ProbDistConstant(10);
			std::shared_ptr<ProbDist> pDist10(dist10);
			SimProbabilities simProbs(pDist10,pDist8,pDist10,pDist10);
			OS *os = new OS(pMemModel,pTPStrategy,100);
			Process process(8, pMemModel, pTPStrategy, simProbs, os);

			for(Process::iterator iter = process.begin(); iter != process.end(); ++iter)
			{
				(*iter)->UpdateThread(1000,0,10);
			}

			Assert::IsTrue(process.IsComplete());
		}


		TEST_METHOD(ProcessUpdatePenalties)
		{
			MemModelDemo* memModel = new MemModelDemo(11,11);
			std::shared_ptr<MemModel> pMemModel(memModel);
			TPStrategy* tpStrat = new TPStrategyDemo(pMemModel, false);
			std::shared_ptr<TPStrategy> pTPStrategy(tpStrat);
			ProbDist* dist = new ProbDistConstant(25);
			std::shared_ptr<ProbDist> pDist(dist);
			SimProbabilities simProbs(pDist,pDist,pDist,pDist);
			OS *os = new OS(pMemModel,pTPStrategy,100);
			Process process(5, pMemModel, pTPStrategy, simProbs, os);

			shared_ptr<Core> core;
			memModel->IteratorReset();
			// Thread 2 to core 50
			for(int i = 1; i < 51; i++)
			{
				core = memModel->IteratorNext();
			}
			Process::iterator iter = process.begin() + 2;
			(*iter)->SetCore(core);

			// Thread 1 to core 60
			for(int i = 51; i < 61; i++)
			{
				core = memModel->IteratorNext();
			}
			iter = process.begin() + 1;
			(*iter)->SetCore(core);

			// Thread 4 to core 62
			core = memModel->IteratorNext();
			core = memModel->IteratorNext();
			iter = process.begin() + 4;
			(*iter)->SetCore(core);

			// Thread 3 to core 72
			for(int i = 63; i < 73; i++)
			{
				core = memModel->IteratorNext();
			}
			iter = process.begin() + 3;
			(*iter)->SetCore(core);

			// Thread 0 to core 108
			for(int i = 73; i < 109; i++)
			{
				core = memModel->IteratorNext();
			}
			iter = process.begin();
			(*iter)->SetCore(core);

			process.UpdatePenalties(pMemModel);

			iter = process.begin();
			double pen1 = (*iter)->GetMemoryFactor();
			iter = process.begin() + 1;
			double pen2 = (*iter)->GetMemoryFactor();
			iter = process.begin() + 2;
			double pen3 = (*iter)->GetMemoryFactor();
			iter = process.begin() + 3;
			double pen4 = (*iter)->GetMemoryFactor();
			iter = process.begin() + 4;
			double pen5 = (*iter)->GetMemoryFactor();

			Assert::IsTrue((pen1 == 1) && (pen2 == (0.5 + 0.5/9)) && (pen3 == (0.5 + 0.5/9)) && (pen4 == (0.5 + 0.5/7)) && (pen5 == (0.5 + 0.5/7)));
		}


		TEST_METHOD(ProcessGetCoupling)
		{
			MemModelDemo* memModel = new MemModelDemo(7,3);
			std::shared_ptr<MemModel> pMemModel(memModel);
			TPStrategy* tpStrat = new TPStrategyDemo(pMemModel, false);
			std::shared_ptr<TPStrategy> pTPStrategy(tpStrat);
			ProbDist* dist1 = new ProbDistConstant(4);
			std::shared_ptr<ProbDist> pDist1(dist1);
			SimProbabilities simProbs(pDist1,pDist1,pDist1,pDist1);
			OS *os = new OS(pMemModel,pTPStrategy,100);
			Process process(4, pMemModel, pTPStrategy, simProbs, os);

			vector<vector<double> > factors; 
			for(Process::iterator iter1 = process.begin(); iter1 != process.end(); ++iter1)
			{
				vector<double> temp;
				for(Process::iterator iter2 = process.begin(); iter2 != process.end(); ++iter2)
				{
					temp.push_back(process.GetCoupling((*iter1),(*iter2)));
				}
				factors.push_back(temp);
			}

			Assert::IsTrue((factors[0][0] == 1) && (factors[0][1] == 0) && (factors[0][2] == 0) && (factors[0][3] == 0) &&
				           (factors[1][0] == 0.5) && (factors[1][1] == 0.5) && (factors[1][2] == 0) && (factors[1][3] == 0) &&
						   (factors[2][0] == 0.5) && (factors[2][1] == 0) && (factors[2][2] == 0.5) && (factors[2][3] == 0) &&
						   (factors[3][0] == 0.5) && (factors[3][1] == 0) && (factors[3][2] == 0) && (factors[3][3] == 0.5));
		}



	};
}