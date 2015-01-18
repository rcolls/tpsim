#include "stdafx.h"
#include "CppUnitTest.h"
#include "MemModelDemo.h"
#include "Core.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(UnitTestMemModelDemo)
	{
	public:
		
		TEST_METHOD(MemModelDemoGetSize)
		{
			MemModelDemo memModel(174,301);
			int rows = 0;
			int cols = 0;
			memModel.GetSize(rows,cols);

			Assert::IsTrue(rows == 174 && cols == 301);
		}

		TEST_METHOD(MemModelDemoIteratorReset)
		{
			MemModelDemo memModel(13,8);

			memModel.IteratorReset();
			Core *core1 = nullptr;
			shared_ptr<Core> pCore1(core1);
			for(int i = 0; i < 11; i++)
			{
				pCore1 = memModel.IteratorNext();
			}
			int core1No = pCore1->GetCoreNo();

			memModel.IteratorReset();
			Core *core2 = nullptr;
			shared_ptr<Core> pCore2(core2);
			pCore2 = memModel.IteratorNext();
			int core2No = pCore2->GetCoreNo();

			Assert::IsTrue((core2No == 1) && (core1No == 11));
		}

		TEST_METHOD(MemModelDemoIteratorNext)
		{
			MemModelDemo memModel(12,3);

			memModel.IteratorReset();
			Core *core = nullptr;
			shared_ptr<Core> pCore(core);

			pCore = memModel.IteratorNext();
			int core1No = pCore->GetCoreNo();

			pCore = memModel.IteratorNext();
			int core2No = pCore->GetCoreNo();

			pCore = memModel.IteratorNext();
			int core3No = pCore->GetCoreNo();

			pCore = memModel.IteratorNext();
			int core4No = pCore->GetCoreNo();

			pCore = memModel.IteratorNext();
			int core5No = pCore->GetCoreNo();

			Assert::IsTrue((core1No == 1) && (core2No == 2) && (core3No == 3) && (core4No == 4) && (core5No == 5));
		}

		TEST_METHOD(MemModelDemoIteratorFirst)
		{
			MemModelDemo memModel(74,8);

			int core1No = (memModel.IteratorFirst())->GetCoreNo();
			memModel.IteratorReset();
			Core *core = nullptr;
			shared_ptr<Core> pCore(core);

			pCore = memModel.IteratorNext();
			int core2No = (memModel.IteratorFirst())->GetCoreNo();

			Assert::IsTrue((core1No == 1) && (core2No == 1));
		}

		TEST_METHOD(MemModelDemoIteratorComplete)
		{
			MemModelDemo memModel(2,3);

			memModel.IteratorReset();
			Core *core = nullptr;
			shared_ptr<Core> pCore(core);

			pCore = memModel.IteratorNext();
			bool fin1 = memModel.IteratorComplete();

			pCore = memModel.IteratorNext();
			bool fin2 = memModel.IteratorComplete();

			pCore = memModel.IteratorNext();
			bool fin3 = memModel.IteratorComplete();

			pCore = memModel.IteratorNext();
			bool fin4 = memModel.IteratorComplete();

			pCore = memModel.IteratorNext();
			bool fin5 = memModel.IteratorComplete();

			pCore = memModel.IteratorNext();
			bool fin6 = memModel.IteratorComplete();

			Assert::IsTrue((fin1 == false) && (fin2 == false) && (fin3 == false) && (fin4 == false) && (fin5 == false) && (fin6 == true));
		}

		TEST_METHOD(MemModelDemoUpdateCores1)
		{
			MemModelDemo memModel(3,4);

			Thread *th1 = new Thread(5);
			th1->SetMemoryFactor(1);
			shared_ptr<Thread> pTh1(th1);
			Thread *th2 = new Thread(6);
			th2->SetMemoryFactor(1);
			shared_ptr<Thread> pTh2(th2);
			Thread *th3 = new Thread(7);
			th3->SetMemoryFactor(1);
			shared_ptr<Thread> pTh3(th3);
			Thread *th4 = new Thread(8);
			th4->SetMemoryFactor(1);
			shared_ptr<Thread> pTh4(th4);
			Thread *th5 = new Thread(9);
			th5->SetMemoryFactor(1);
			shared_ptr<Thread> pTh5(th5);
			Thread *th6 = new Thread(10);
			th6->SetMemoryFactor(1);
			shared_ptr<Thread> pTh6(th6);

			Core *core = nullptr;
			shared_ptr<Core> pCore(core);

			memModel.IteratorReset();
			pCore = memModel.IteratorNext();
			pCore->AddThread(pTh1,pCore);

			pCore = memModel.IteratorNext();
			pCore->AddThread(pTh2,pCore);

			pCore = memModel.IteratorNext();
			pCore = memModel.IteratorNext();
			pCore->AddThread(pTh3,pCore);

			pCore = memModel.IteratorNext();
			pCore = memModel.IteratorNext();
			pCore = memModel.IteratorNext();
			pCore->AddThread(pTh4,pCore);

			pCore = memModel.IteratorNext();
			pCore = memModel.IteratorNext();
			pCore = memModel.IteratorNext();
			pCore = memModel.IteratorNext();
			pCore = memModel.IteratorNext();
			pCore->AddThread(pTh5,pCore);
			pCore->AddThread(pTh6,pCore);

			memModel.UpdateCores(1.0);

			double time1 = pTh1->GetRemainingDuration();
			double time2 = pTh2->GetRemainingDuration();
			double time3 = pTh3->GetRemainingDuration();
			double time4 = pTh4->GetRemainingDuration();
			double time5 = pTh5->GetRemainingDuration();
			double time6 = pTh6->GetRemainingDuration();

			Assert::IsTrue((time1 == 4) && (time2 = 5) && (time3 == 6) && (time4 = 7) && (time5 == 8.5) && (time6 == 9.5));
		}

		TEST_METHOD(MemModelDemoUpdateCores2)
		{
			MemModelDemo memModel(5,2);

			Thread *th1 = new Thread(10);
			th1->SetMemoryFactor(1);
			shared_ptr<Thread> pTh1(th1);
			Thread *th2 = new Thread(9);
			th2->SetMemoryFactor(1);
			shared_ptr<Thread> pTh2(th2);
			Thread *th3 = new Thread(8);
			th3->SetMemoryFactor(1);
			shared_ptr<Thread> pTh3(th3);
			Thread *th4 = new Thread(7);
			th4->SetMemoryFactor(1);
			shared_ptr<Thread> pTh4(th4);
			Thread *th5 = new Thread(6);
			th5->SetMemoryFactor(1);
			shared_ptr<Thread> pTh5(th5);
			Thread *th6 = new Thread(5);
			th6->SetMemoryFactor(1);
			shared_ptr<Thread> pTh6(th6);

			Core *core = nullptr;
			shared_ptr<Core> pCore(core);

			memModel.IteratorReset();
			pCore = memModel.IteratorNext();
			pCore->AddThread(pTh1,pCore);

			pCore = memModel.IteratorNext();
			pCore->AddThread(pTh2,pCore);

			pCore = memModel.IteratorNext();
			pCore->AddThread(pTh3,pCore);
			pCore->AddThread(pTh4,pCore);

			pCore = memModel.IteratorNext();
			pCore = memModel.IteratorNext();
			pCore = memModel.IteratorNext();
			pCore->AddThread(pTh5,pCore);

			pCore = memModel.IteratorNext();
			pCore = memModel.IteratorNext();
			pCore = memModel.IteratorNext();
			pCore->AddThread(pTh6,pCore);

			memModel.UpdateCores(2.5);

			double time1 = pTh1->GetRemainingDuration();
			double time2 = pTh2->GetRemainingDuration();
			double time3 = pTh3->GetRemainingDuration();
			double time4 = pTh4->GetRemainingDuration();
			double time5 = pTh5->GetRemainingDuration();
			double time6 = pTh6->GetRemainingDuration();

			Assert::IsTrue((time1 ==7.5) && (time2 = 6.5) && (time3 == 6.75) && (time4 = 6.25) && (time5 == 3.5) && (time6 == 2.5));
		}

		TEST_METHOD(MemModelDemoGetMemoryFactor1)
		{
			MemModelDemo memModel(3,3);
			std::vector<double> factors;

			Core *core1 = nullptr;
			shared_ptr<Core> pCore1(core1);
			Core *core2 = nullptr;
			shared_ptr<Core> pCore2(core2);

			pCore1 = memModel.IteratorFirst();
			memModel.IteratorReset();
			double factor = 0;
			while(!memModel.IteratorComplete())
			{
				pCore2 = memModel.IteratorNext();
				factor = memModel.GetMemoryFactor(pCore1,pCore2);
				factors.push_back(factor);
			}

			Assert::IsTrue((factors[0] == 1)     && (factors[1] == 0.5)   && (factors[2] == 1.0/3)
				        && (factors[3] == 0.5)   && (factors[4] == 1.0/3) && (factors[5] == 0.25)
				        && (factors[6] == 1.0/3) && (factors[7] == 0.25)  && (factors[8] == 0.2));
		}

		TEST_METHOD(MemModelDemoGetMemoryFactor2)
		{
			MemModelDemo memModel(3,3);
			std::vector<double> factors;

			Core *core1 = nullptr;
			shared_ptr<Core> pCore1(core1);
			Core *core2 = nullptr;
			shared_ptr<Core> pCore2(core2);

			memModel.IteratorReset();
			memModel.IteratorNext();
			pCore1 = memModel.IteratorNext();

			memModel.IteratorReset();
			double factor = 0;
			while(!memModel.IteratorComplete())
			{
				pCore2 = memModel.IteratorNext();
				factor = memModel.GetMemoryFactor(pCore1,pCore2);
				factors.push_back(factor);
			}

			Assert::IsTrue((factors[0] == 0.5)   && (factors[1] == 1)     && (factors[2] == 0.5)
				        && (factors[3] == 1.0/3) && (factors[4] == 0.5)   && (factors[5] == 1.0/3)
				        && (factors[6] == 0.25)  && (factors[7] == 1.0/3) && (factors[8] == 0.25));
		}

		TEST_METHOD(MemModelDemoGetMemoryFactor3)
		{
			MemModelDemo memModel(3,3);
			std::vector<double> factors;

			Core *core1 = nullptr;
			shared_ptr<Core> pCore1(core1);
			Core *core2 = nullptr;
			shared_ptr<Core> pCore2(core2);

			memModel.IteratorReset();
			memModel.IteratorNext();
			memModel.IteratorNext();
			pCore1 = memModel.IteratorNext();

			memModel.IteratorReset();
			double factor = 0;
			while(!memModel.IteratorComplete())
			{
				pCore2 = memModel.IteratorNext();
				factor = memModel.GetMemoryFactor(pCore1,pCore2);
				factors.push_back(factor);
			}

			Assert::IsTrue((factors[0] == 1.0/3) && (factors[1] == 0.5)   && (factors[2] == 1)
				        && (factors[3] == 0.25)  && (factors[4] == 1.0/3) && (factors[5] == 0.5)
				        && (factors[6] == 0.2)   && (factors[7] == 0.25)  && (factors[8] == 1.0/3));
		}

		TEST_METHOD(MemModelDemoGetMemoryFactor4)
		{
			MemModelDemo memModel(3,3);
			std::vector<double> factors;

			Core *core1 = nullptr;
			shared_ptr<Core> pCore1(core1);
			Core *core2 = nullptr;
			shared_ptr<Core> pCore2(core2);

			memModel.IteratorReset();
			memModel.IteratorNext();
			memModel.IteratorNext();
			memModel.IteratorNext();
			pCore1 = memModel.IteratorNext();

			memModel.IteratorReset();
			double factor = 0;
			while(!memModel.IteratorComplete())
			{
				pCore2 = memModel.IteratorNext();
				factor = memModel.GetMemoryFactor(pCore1,pCore2);
				factors.push_back(factor);
			}

			Assert::IsTrue((factors[0] == 0.5) && (factors[1] == 1.0/3) && (factors[2] == 0.25)
				        && (factors[3] == 1)   && (factors[4] == 0.5)   && (factors[5] == 1.0/3)
				        && (factors[6] == 0.5) && (factors[7] == 1.0/3) && (factors[8] == 0.25));
		}

		TEST_METHOD(MemModelDemoGetMemoryFactor5)
		{
			MemModelDemo memModel(3,3);
			std::vector<double> factors;

			Core *core1 = nullptr;
			shared_ptr<Core> pCore1(core1);
			Core *core2 = nullptr;
			shared_ptr<Core> pCore2(core2);

			memModel.IteratorReset();
			memModel.IteratorNext();
			memModel.IteratorNext();
			memModel.IteratorNext();
			memModel.IteratorNext();
			pCore1 = memModel.IteratorNext();

			memModel.IteratorReset();
			double factor = 0;
			while(!memModel.IteratorComplete())
			{
				pCore2 = memModel.IteratorNext();
				factor = memModel.GetMemoryFactor(pCore1,pCore2);
				factors.push_back(factor);
			}

			Assert::IsTrue((factors[0] == 1.0/3) && (factors[1] == 0.5) && (factors[2] == 1.0/3)
				        && (factors[3] == 0.5)   && (factors[4] == 1)   && (factors[5] == 0.5)
				        && (factors[6] == 1.0/3) && (factors[7] == 0.5) && (factors[8] == 1.0/3));
		}

		TEST_METHOD(MemModelDemoGetMemoryFactor6)
		{
			MemModelDemo memModel(3,3);
			std::vector<double> factors;

			Core *core1 = nullptr;
			shared_ptr<Core> pCore1(core1);
			Core *core2 = nullptr;
			shared_ptr<Core> pCore2(core2);

			memModel.IteratorReset();
			memModel.IteratorNext();
			memModel.IteratorNext();
			memModel.IteratorNext();
			memModel.IteratorNext();
			memModel.IteratorNext();
			pCore1 = memModel.IteratorNext();

			memModel.IteratorReset();
			double factor = 0;
			while(!memModel.IteratorComplete())
			{
				pCore2 = memModel.IteratorNext();
				factor = memModel.GetMemoryFactor(pCore1,pCore2);
				factors.push_back(factor);
			}

			Assert::IsTrue((factors[0] == 0.25)  && (factors[1] == 1.0/3) && (factors[2] == 0.5)
				        && (factors[3] == 1.0/3) && (factors[4] == 0.5)   && (factors[5] == 1)
				        && (factors[6] == 0.25)  && (factors[7] == 1.0/3) && (factors[8] == 0.5));
		}

		TEST_METHOD(MemModelDemoGetMemoryFactor7)
		{
			MemModelDemo memModel(3,3);
			std::vector<double> factors;

			Core *core1 = nullptr;
			shared_ptr<Core> pCore1(core1);
			Core *core2 = nullptr;
			shared_ptr<Core> pCore2(core2);

			memModel.IteratorReset();
			memModel.IteratorNext();
			memModel.IteratorNext();
			memModel.IteratorNext();
			memModel.IteratorNext();
			memModel.IteratorNext();
			memModel.IteratorNext();
			pCore1 = memModel.IteratorNext();

			memModel.IteratorReset();
			double factor = 0;
			while(!memModel.IteratorComplete())
			{
				pCore2 = memModel.IteratorNext();
				factor = memModel.GetMemoryFactor(pCore1,pCore2);
				factors.push_back(factor);
			}

			Assert::IsTrue((factors[0] == 1.0/3) && (factors[1] == 0.25)  && (factors[2] == 0.2)
				        && (factors[3] == 0.5)   && (factors[4] == 1.0/3) && (factors[5] == 0.25)
				        && (factors[6] == 1)     && (factors[7] == 0.5)   && (factors[8] == 1.0/3));
		}

		TEST_METHOD(MemModelDemoGetMemoryFactor8)
		{
			MemModelDemo memModel(3,3);
			std::vector<double> factors;

			Core *core1 = nullptr;
			shared_ptr<Core> pCore1(core1);
			Core *core2 = nullptr;
			shared_ptr<Core> pCore2(core2);

			memModel.IteratorReset();
			memModel.IteratorNext();
			memModel.IteratorNext();
			memModel.IteratorNext();
			memModel.IteratorNext();
			memModel.IteratorNext();
			memModel.IteratorNext();
			memModel.IteratorNext();
			pCore1 = memModel.IteratorNext();

			memModel.IteratorReset();
			double factor = 0;
			while(!memModel.IteratorComplete())
			{
				pCore2 = memModel.IteratorNext();
				factor = memModel.GetMemoryFactor(pCore1,pCore2);
				factors.push_back(factor);
			}

			Assert::IsTrue((factors[0] == 0.25)  && (factors[1] == 1.0/3) && (factors[2] == 0.25)
				        && (factors[3] == 1.0/3) && (factors[4] == 0.5)   && (factors[5] == 1.0/3)
				        && (factors[6] == 0.5)   && (factors[7] == 1)     && (factors[8] == 0.5));
		}

		TEST_METHOD(MemModelDemoGetMemoryFactor9)
		{
			MemModelDemo memModel(3,3);
			std::vector<double> factors;

			Core *core1 = nullptr;
			shared_ptr<Core> pCore1(core1);
			Core *core2 = nullptr;
			shared_ptr<Core> pCore2(core2);

			memModel.IteratorReset();
			memModel.IteratorNext();
			memModel.IteratorNext();
			memModel.IteratorNext();
			memModel.IteratorNext();
			memModel.IteratorNext();
			memModel.IteratorNext();
			memModel.IteratorNext();
			memModel.IteratorNext();
			pCore1 = memModel.IteratorNext();

			memModel.IteratorReset();
			double factor = 0;
			while(!memModel.IteratorComplete())
			{
				pCore2 = memModel.IteratorNext();
				factor = memModel.GetMemoryFactor(pCore1,pCore2);
				factors.push_back(factor);
			}

			Assert::IsTrue((factors[0] == 0.2)   && (factors[1] == 0.25)  && (factors[2] == 1.0/3)
				        && (factors[3] == 0.25)  && (factors[4] == 1.0/3) && (factors[5] == 0.5)
				        && (factors[6] == 1.0/3) && (factors[7] == 0.5)   && (factors[8] == 1));
		}

		TEST_METHOD(MemModelDemoGetMemoryFactor10)
		{
			MemModelDemo memModel(3,4);
			std::vector<double> factors;

			Core *core1 = nullptr;
			shared_ptr<Core> pCore1(core1);
			Core *core2 = nullptr;
			shared_ptr<Core> pCore2(core2);

			pCore1 = memModel.IteratorFirst();
			memModel.IteratorReset();
			double factor = 0;
			while(!memModel.IteratorComplete())
			{
				pCore2 = memModel.IteratorNext();
				factor = memModel.GetMemoryFactor(pCore1,pCore2);
				factors.push_back(factor);
			}

			Assert::IsTrue((factors[0] == 1)     && (factors[1] == 0.5)   && (factors[2]  == 1.0/3) && (factors[3] == 0.25)
				        && (factors[4] == 0.5)   && (factors[5] == 1.0/3) && (factors[6]  == 0.25)  && (factors[7] == 0.2)
				        && (factors[8] == 1.0/3) && (factors[9] == 0.25)  && (factors[10] == 0.2)   && (factors[11] == 1.0/6));
		}

		TEST_METHOD(MemModelDemoFindNearestCores1)
		{
			MemModelDemo memModel(3,4);
			std::list<shared_ptr<Core> > cores;
			std::vector<std::vector<int> > coreNos;


			Core *core1 = nullptr;
			shared_ptr<Core> pCore1(core1);
			Core *core2 = nullptr;
			shared_ptr<Core> pCore2(core2);

			pCore1 = memModel.IteratorFirst();
			memModel.IteratorReset();
			double factor = 0;
			for(int i = 0; i < 7; i++)
			{
				memModel.FindNearestCores(cores,pCore1,i);
				std::vector<int> temp;
				for(std::list<shared_ptr<Core> >::iterator iter = cores.begin(); iter != cores.end(); ++iter)
				{
					temp.push_back((*iter)->GetCoreNo());
				}
				coreNos.push_back(temp);
			}

			Assert::IsTrue((coreNos[0].size() == 1) && (coreNos[0][0] == 1)
				        && (coreNos[1].size() == 2) && (coreNos[1][0] == 2) && (coreNos[1][1] == 5)
						&& (coreNos[2].size() == 3) && (coreNos[2][0] == 3) && (coreNos[2][1] == 6) && (coreNos[2][2] == 9)
						&& (coreNos[3].size() == 3) && (coreNos[3][0] == 4) && (coreNos[3][1] == 7) && (coreNos[3][2] == 10)
						&& (coreNos[4].size() == 2) && (coreNos[4][0] == 8) && (coreNos[4][1] == 11)
						&& (coreNos[5].size() == 1) && (coreNos[5][0] == 12)
						&& (coreNos[6].size() == 0));
		}
		
		TEST_METHOD(MemModelDemoFindNearestCores2)
		{
			MemModelDemo memModel(3,4);
			std::list<shared_ptr<Core> > cores;
			std::vector<std::vector<int> > coreNos;


			Core *core1 = nullptr;
			shared_ptr<Core> pCore1(core1);
			Core *core2 = nullptr;
			shared_ptr<Core> pCore2(core2);

			memModel.IteratorReset();
			memModel.IteratorNext();
			pCore1 = memModel.IteratorNext();
			memModel.IteratorReset();
			double factor = 0;
			for(int i = 0; i < 6; i++)
			{
				memModel.FindNearestCores(cores,pCore1,i);
				std::vector<int> temp;
				for(std::list<shared_ptr<Core> >::iterator iter = cores.begin(); iter != cores.end(); ++iter)
				{
					temp.push_back((*iter)->GetCoreNo());
				}
				coreNos.push_back(temp);
			}

			Assert::IsTrue((coreNos[0].size() == 1) && (coreNos[0][0] == 2)
				        && (coreNos[1].size() == 3) && (coreNos[1][0] == 1) && (coreNos[1][1] == 3) && (coreNos[1][2] == 6)
						&& (coreNos[2].size() == 4) && (coreNos[2][0] == 4) && (coreNos[2][1] == 5) && (coreNos[2][2] == 7) && (coreNos[2][3] == 10)
						&& (coreNos[3].size() == 3) && (coreNos[3][0] == 8) && (coreNos[3][1] == 9) && (coreNos[3][2] == 11)
						&& (coreNos[4].size() == 1) && (coreNos[4][0] == 12)
						&& (coreNos[5].size() == 0));
		}

		TEST_METHOD(MemModelDemoFindNearestCores3)
		{
			MemModelDemo memModel(3,4);
			std::list<shared_ptr<Core> > cores;
			std::vector<std::vector<int> > coreNos;

			Core *core1 = nullptr;
			shared_ptr<Core> pCore1(core1);
			Core *core2 = nullptr;
			shared_ptr<Core> pCore2(core2);

			memModel.IteratorReset();
			memModel.IteratorNext();
			memModel.IteratorNext();
			pCore1 = memModel.IteratorNext();
			memModel.IteratorReset();
			double factor = 0;
			for(int i = 0; i < 6; i++)
			{
				memModel.FindNearestCores(cores,pCore1,i);
				std::vector<int> temp;
				for(std::list<shared_ptr<Core> >::iterator iter = cores.begin(); iter != cores.end(); ++iter)
				{
					temp.push_back((*iter)->GetCoreNo());
				}
				coreNos.push_back(temp);
			}

			Assert::IsTrue((coreNos[0].size() == 1) && (coreNos[0][0] == 3)
				        && (coreNos[1].size() == 3) && (coreNos[1][0] == 2) && (coreNos[1][1] == 4)  && (coreNos[1][2] == 7)
						&& (coreNos[2].size() == 4) && (coreNos[2][0] == 1) && (coreNos[2][1] == 6)  && (coreNos[2][2] == 8) && (coreNos[2][3] == 11)
						&& (coreNos[3].size() == 3) && (coreNos[3][0] == 5) && (coreNos[3][1] == 10) && (coreNos[3][2] == 12)
						&& (coreNos[4].size() == 1) && (coreNos[4][0] == 9)
						&& (coreNos[5].size() == 0));
		}

		TEST_METHOD(MemModelDemoFindNearestCores4)
		{
			MemModelDemo memModel(3,4);
			std::list<shared_ptr<Core> > cores;
			std::vector<std::vector<int> > coreNos;

			Core *core1 = nullptr;
			shared_ptr<Core> pCore1(core1);
			Core *core2 = nullptr;
			shared_ptr<Core> pCore2(core2);

			memModel.IteratorReset();
			for(int i = 0; i < 4; i++)
			{
				pCore1 = memModel.IteratorNext();
			}
			memModel.IteratorReset();
			double factor = 0;
			for(int i = 0; i < 7; i++)
			{
				memModel.FindNearestCores(cores,pCore1,i);
				std::vector<int> temp;
				for(std::list<shared_ptr<Core> >::iterator iter = cores.begin(); iter != cores.end(); ++iter)
				{
					temp.push_back((*iter)->GetCoreNo());
				}
				coreNos.push_back(temp);
			}

			Assert::IsTrue((coreNos[0].size() == 1) && (coreNos[0][0] == 4)
				        && (coreNos[1].size() == 2) && (coreNos[1][0] == 3) && (coreNos[1][1] == 8)
						&& (coreNos[2].size() == 3) && (coreNos[2][0] == 2) && (coreNos[2][1] == 7) && (coreNos[2][2] == 12)
						&& (coreNos[3].size() == 3) && (coreNos[3][0] == 1) && (coreNos[3][1] == 6) && (coreNos[3][2] == 11)
						&& (coreNos[4].size() == 2) && (coreNos[4][0] == 5) && (coreNos[4][1] == 10)
						&& (coreNos[5].size() == 1) && (coreNos[5][0] == 9)
						&& (coreNos[6].size() == 0));
		}

		TEST_METHOD(MemModelDemoFindNearestCores5)
		{
			MemModelDemo memModel(3,4);
			std::list<shared_ptr<Core> > cores;
			std::vector<std::vector<int> > coreNos;

			Core *core1 = nullptr;
			shared_ptr<Core> pCore1(core1);
			Core *core2 = nullptr;
			shared_ptr<Core> pCore2(core2);

			memModel.IteratorReset();
			for(int i = 0; i < 5; i++)
			{
				pCore1 = memModel.IteratorNext();
			}
			memModel.IteratorReset();
			double factor = 0;
			for(int i = 0; i < 6; i++)
			{
				memModel.FindNearestCores(cores,pCore1,i);
				std::vector<int> temp;
				for(std::list<shared_ptr<Core> >::iterator iter = cores.begin(); iter != cores.end(); ++iter)
				{
					temp.push_back((*iter)->GetCoreNo());
				}
				coreNos.push_back(temp);
			}

			Assert::IsTrue((coreNos[0].size() == 1) && (coreNos[0][0] == 5)
				        && (coreNos[1].size() == 3) && (coreNos[1][0] == 1) && (coreNos[1][1] == 6) && (coreNos[1][2] == 9)
						&& (coreNos[2].size() == 3) && (coreNos[2][0] == 2) && (coreNos[2][1] == 7) && (coreNos[2][2] == 10)
						&& (coreNos[3].size() == 3) && (coreNos[3][0] == 3) && (coreNos[3][1] == 8) && (coreNos[3][2] == 11)
						&& (coreNos[4].size() == 2) && (coreNos[4][0] == 4) && (coreNos[4][1] == 12)
						&& (coreNos[5].size() == 0));
		}

		TEST_METHOD(MemModelDemoFindNearestCores6)
		{
			MemModelDemo memModel(3,4);
			std::list<shared_ptr<Core> > cores;
			std::vector<std::vector<int> > coreNos;

			Core *core1 = nullptr;
			shared_ptr<Core> pCore1(core1);
			Core *core2 = nullptr;
			shared_ptr<Core> pCore2(core2);

			memModel.IteratorReset();
			for(int i = 0; i < 6; i++)
			{
				pCore1 = memModel.IteratorNext();
			}
			memModel.IteratorReset();
			double factor = 0;
			for(int i = 0; i < 6; i++)
			{
				memModel.FindNearestCores(cores,pCore1,i);
				std::vector<int> temp;
				for(std::list<shared_ptr<Core> >::iterator iter = cores.begin(); iter != cores.end(); ++iter)
				{
					temp.push_back((*iter)->GetCoreNo());
				}
				coreNos.push_back(temp);
			}

			Assert::IsTrue((coreNos[0].size() == 1) && (coreNos[0][0] == 6)
				        && (coreNos[1].size() == 4) && (coreNos[1][0] == 2) && (coreNos[1][1] == 5) && (coreNos[1][2] == 7) && (coreNos[1][3] == 10)
						&& (coreNos[2].size() == 5) && (coreNos[2][0] == 1) && (coreNos[2][1] == 3) && (coreNos[2][2] == 8) && (coreNos[2][3] == 9) && (coreNos[2][4] == 11)
						&& (coreNos[3].size() == 2) && (coreNos[3][0] == 4) && (coreNos[3][1] == 12)
						&& (coreNos[4].size() == 0));
		}

		TEST_METHOD(MemModelDemoFindNearestCores7)
		{
			MemModelDemo memModel(3,4);
			std::list<shared_ptr<Core> > cores;
			std::vector<std::vector<int> > coreNos;

			Core *core1 = nullptr;
			shared_ptr<Core> pCore1(core1);
			Core *core2 = nullptr;
			shared_ptr<Core> pCore2(core2);

			memModel.IteratorReset();
			for(int i = 0; i < 7; i++)
			{
				pCore1 = memModel.IteratorNext();
			}
			memModel.IteratorReset();
			double factor = 0;
			for(int i = 0; i < 5; i++)
			{
				memModel.FindNearestCores(cores,pCore1,i);
				std::vector<int> temp;
				for(std::list<shared_ptr<Core> >::iterator iter = cores.begin(); iter != cores.end(); ++iter)
				{
					temp.push_back((*iter)->GetCoreNo());
				}
				coreNos.push_back(temp);
			}

			Assert::IsTrue((coreNos[0].size() == 1) && (coreNos[0][0] == 7)
				        && (coreNos[1].size() == 4) && (coreNos[1][0] == 3) && (coreNos[1][1] == 6) && (coreNos[1][2] == 8) && (coreNos[1][3] == 11)
						&& (coreNos[2].size() == 5) && (coreNos[2][0] == 2) && (coreNos[2][1] == 4) && (coreNos[2][2] == 5) && (coreNos[2][3] == 10) && (coreNos[2][4] == 12)
						&& (coreNos[3].size() == 2) && (coreNos[3][0] == 1) && (coreNos[3][1] == 9)
						&& (coreNos[4].size() == 0));
		}

		TEST_METHOD(MemModelDemoFindNearestCores8)
		{
			MemModelDemo memModel(3,4);
			std::list<shared_ptr<Core> > cores;
			std::vector<std::vector<int> > coreNos;

			Core *core1 = nullptr;
			shared_ptr<Core> pCore1(core1);
			Core *core2 = nullptr;
			shared_ptr<Core> pCore2(core2);

			memModel.IteratorReset();
			for(int i = 0; i < 8; i++)
			{
				pCore1 = memModel.IteratorNext();
			}
			memModel.IteratorReset();
			double factor = 0;
			for(int i = 0; i < 6; i++)
			{
				memModel.FindNearestCores(cores,pCore1,i);
				std::vector<int> temp;
				for(std::list<shared_ptr<Core> >::iterator iter = cores.begin(); iter != cores.end(); ++iter)
				{
					temp.push_back((*iter)->GetCoreNo());
				}
				coreNos.push_back(temp);
			}

			Assert::IsTrue((coreNos[0].size() == 1) && (coreNos[0][0] == 8)
				        && (coreNos[1].size() == 3) && (coreNos[1][0] == 4) && (coreNos[1][1] == 7) && (coreNos[1][2] == 12)
						&& (coreNos[2].size() == 3) && (coreNos[2][0] == 3) && (coreNos[2][1] == 6) && (coreNos[2][2] == 11)
						&& (coreNos[3].size() == 3) && (coreNos[3][0] == 2) && (coreNos[3][1] == 5) && (coreNos[3][2] == 10)
						&& (coreNos[4].size() == 2) && (coreNos[4][0] == 1) && (coreNos[4][1] == 9)
						&& (coreNos[5].size() == 0));
		}

		TEST_METHOD(MemModelDemoFindNearestCores9)
		{
			MemModelDemo memModel(3,4);
			std::list<shared_ptr<Core> > cores;
			std::vector<std::vector<int> > coreNos;

			Core *core1 = nullptr;
			shared_ptr<Core> pCore1(core1);
			Core *core2 = nullptr;
			shared_ptr<Core> pCore2(core2);

			memModel.IteratorReset();
			for(int i = 0; i < 9; i++)
			{
				pCore1 = memModel.IteratorNext();
			}
			memModel.IteratorReset();
			double factor = 0;
			for(int i = 0; i < 7; i++)
			{
				memModel.FindNearestCores(cores,pCore1,i);
				std::vector<int> temp;
				for(std::list<shared_ptr<Core> >::iterator iter = cores.begin(); iter != cores.end(); ++iter)
				{
					temp.push_back((*iter)->GetCoreNo());
				}
				coreNos.push_back(temp);
			}

			Assert::IsTrue((coreNos[0].size() == 1) && (coreNos[0][0] == 9)
				        && (coreNos[1].size() == 2) && (coreNos[1][0] == 5) && (coreNos[1][1] == 10)
						&& (coreNos[2].size() == 3) && (coreNos[2][0] == 1) && (coreNos[2][1] == 6) && (coreNos[2][2] == 11)
						&& (coreNos[3].size() == 3) && (coreNos[3][0] == 2) && (coreNos[3][1] == 7) && (coreNos[3][2] == 12)
						&& (coreNos[4].size() == 2) && (coreNos[4][0] == 3) && (coreNos[4][1] == 8)
						&& (coreNos[5].size() == 1) && (coreNos[5][0] == 4)
						&& (coreNos[6].size() == 0));
		}

		TEST_METHOD(MemModelDemoFindNearestCores10)
		{
			MemModelDemo memModel(3,4);
			std::list<shared_ptr<Core> > cores;
			std::vector<std::vector<int> > coreNos;

			Core *core1 = nullptr;
			shared_ptr<Core> pCore1(core1);
			Core *core2 = nullptr;
			shared_ptr<Core> pCore2(core2);

			memModel.IteratorReset();
			for(int i = 0; i < 10; i++)
			{
				pCore1 = memModel.IteratorNext();
			}
			memModel.IteratorReset();
			double factor = 0;
			for(int i = 0; i < 6; i++)
			{
				memModel.FindNearestCores(cores,pCore1,i);
				std::vector<int> temp;
				for(std::list<shared_ptr<Core> >::iterator iter = cores.begin(); iter != cores.end(); ++iter)
				{
					temp.push_back((*iter)->GetCoreNo());
				}
				coreNos.push_back(temp);
			}

			Assert::IsTrue((coreNos[0].size() == 1) && (coreNos[0][0] == 10)
				        && (coreNos[1].size() == 3) && (coreNos[1][0] == 6) && (coreNos[1][1] == 9) && (coreNos[1][2] == 11)
						&& (coreNos[2].size() == 4) && (coreNos[2][0] == 2) && (coreNos[2][1] == 5) && (coreNos[2][2] == 7) && (coreNos[2][3] == 12)
						&& (coreNos[3].size() == 3) && (coreNos[3][0] == 1) && (coreNos[3][1] == 3) && (coreNos[3][2] == 8)
						&& (coreNos[4].size() == 1) && (coreNos[4][0] == 4)
						&& (coreNos[5].size() == 0));
		}

		TEST_METHOD(MemModelDemoFindNearestCores11)
		{
			MemModelDemo memModel(3,4);
			std::list<shared_ptr<Core> > cores;
			std::vector<std::vector<int> > coreNos;

			Core *core1 = nullptr;
			shared_ptr<Core> pCore1(core1);
			Core *core2 = nullptr;
			shared_ptr<Core> pCore2(core2);

			memModel.IteratorReset();
			for(int i = 0; i < 11; i++)
			{
				pCore1 = memModel.IteratorNext();
			}
			memModel.IteratorReset();
			double factor = 0;
			for(int i = 0; i < 6; i++)
			{
				memModel.FindNearestCores(cores,pCore1,i);
				std::vector<int> temp;
				for(std::list<shared_ptr<Core> >::iterator iter = cores.begin(); iter != cores.end(); ++iter)
				{
					temp.push_back((*iter)->GetCoreNo());
				}
				coreNos.push_back(temp);
			}

			Assert::IsTrue((coreNos[0].size() == 1) && (coreNos[0][0] == 11)
				        && (coreNos[1].size() == 3) && (coreNos[1][0] == 7) && (coreNos[1][1] == 10) && (coreNos[1][2] == 12)
						&& (coreNos[2].size() == 4) && (coreNos[2][0] == 3) && (coreNos[2][1] == 6) && (coreNos[2][2] == 8) && (coreNos[2][3] == 9)
						&& (coreNos[3].size() == 3) && (coreNos[3][0] == 2) && (coreNos[3][1] == 4) && (coreNos[3][2] == 5)
						&& (coreNos[4].size() == 1) && (coreNos[4][0] == 1)
						&& (coreNos[5].size() == 0));
		}

		TEST_METHOD(MemModelDemoFindNearestCores12)
		{
			MemModelDemo memModel(3,4);
			std::list<shared_ptr<Core> > cores;
			std::vector<std::vector<int> > coreNos;

			Core *core1 = nullptr;
			shared_ptr<Core> pCore1(core1);
			Core *core2 = nullptr;
			shared_ptr<Core> pCore2(core2);

			memModel.IteratorReset();
			for(int i = 0; i < 12; i++)
			{
				pCore1 = memModel.IteratorNext();
			}
			memModel.IteratorReset();
			double factor = 0;
			for(int i = 0; i < 7; i++)
			{
				memModel.FindNearestCores(cores,pCore1,i);
				std::vector<int> temp;
				for(std::list<shared_ptr<Core> >::iterator iter = cores.begin(); iter != cores.end(); ++iter)
				{
					temp.push_back((*iter)->GetCoreNo());
				}
				coreNos.push_back(temp);
			}

			Assert::IsTrue((coreNos[0].size() == 1) && (coreNos[0][0] == 12)
				        && (coreNos[1].size() == 2) && (coreNos[1][0] == 8) && (coreNos[1][1] == 11)
						&& (coreNos[2].size() == 3) && (coreNos[2][0] == 4) && (coreNos[2][1] == 7) && (coreNos[2][2] == 10)
						&& (coreNos[3].size() == 3) && (coreNos[3][0] == 3) && (coreNos[3][1] == 6) && (coreNos[3][2] == 9)
						&& (coreNos[4].size() == 2) && (coreNos[4][0] == 2) && (coreNos[4][1] == 5)
						&& (coreNos[5].size() == 1) && (coreNos[5][0] == 1)
						&& (coreNos[6].size() == 0));
		}
	};
}