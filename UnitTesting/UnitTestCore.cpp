#include "stdafx.h"
#include "CppUnitTest.h"
//#include "Core.h"
//#include "Core.cpp"
#include "Thread.h"
#include "Thread.cpp"
//#include "OutputResults.h"
//#include "OutputResults.cpp"

using std::shared_ptr;


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		// Check core index is assigned and returned
		TEST_METHOD(CoreGetCoreNo)
		{
			int coreNoIn = 223;
			Core core(coreNoIn);
			int coreNoOut = core.GetCoreNo();

			Assert::AreEqual(coreNoIn,coreNoOut);
		}

		// Check newly created core has no threads
		TEST_METHOD(CoreGetNoOfThreads1)
		{
			Core core(10000);
			int addedThreads = core.GetNoOfThreads();

			Assert::AreEqual(addedThreads,0);
		}

		// Check count after adding 3 threads
		TEST_METHOD(CoreGetNoOfThreads2)
		{
			Core* core = new Core(223);
			shared_ptr<Core> pCore(core);
			Thread* thread1 = new Thread(17.3);
			shared_ptr<Thread> pTh1(thread1);
			Thread* thread2 = new Thread(77.4);
			shared_ptr<Thread> pTh2(thread2);
			Thread* thread3 = new Thread(89076.45);
			shared_ptr<Thread> pTh3(thread3);
			core->AddThread(pTh1,pCore);
			core->AddThread(pTh2,pCore);
			core->AddThread(pTh3,pCore);
			int addedThreads = core->GetNoOfThreads();

			Assert::AreEqual(addedThreads,3);
		}

		// Check count after add 2, remove 1, add 4, remove 2, add 1
		TEST_METHOD(CoreGetNoOfThreads3)
		{
			Core* core = new Core(5);
			shared_ptr<Core> pCore(core);
			Thread* thread1 = new Thread(17.3);
			shared_ptr<Thread> pTh1(thread1);
			Thread* thread2 = new Thread(77.4);
			shared_ptr<Thread> pTh2(thread2);
			Thread* thread3 = new Thread(89076.45);
			shared_ptr<Thread> pTh3(thread3);
			Thread* thread4 = new Thread(77.4);
			shared_ptr<Thread> pTh4(thread4);
			Thread* thread5 = new Thread(89076.45);
			shared_ptr<Thread> pTh5(thread5);
			Thread* thread6 = new Thread(77.4);
			shared_ptr<Thread> pTh6(thread6);
			Thread* thread7 = new Thread(89076.45);
			shared_ptr<Thread> pTh7(thread7);
			core->AddThread(pTh1,pCore);
			core->AddThread(pTh2,pCore);
			core->RemoveThread(pTh1);
			core->AddThread(pTh3,pCore);
			core->AddThread(pTh4,pCore);
			core->AddThread(pTh5,pCore);
			core->AddThread(pTh6,pCore);
			core->RemoveThread(pTh4);
			core->RemoveThread(pTh5);
			core->AddThread(pTh7,pCore);

			int addedThreads = core->GetNoOfThreads();

			Assert::AreEqual(addedThreads,4);
		}

		// Check activity level equals thread count
		TEST_METHOD(CoreGetActivityLevel)
		{
			Core* core = new Core(223);
			shared_ptr<Core> pCore(core);
			Thread* thread1 = new Thread(17.3);
			std::shared_ptr<Thread> pTh1(thread1);
			Thread* thread2 = new Thread(77.4);
			std::shared_ptr<Thread> pTh2(thread2);
			Thread* thread3 = new Thread(89076.45);
			std::shared_ptr<Thread> pTh3(thread3);
			Thread* thread4 = new Thread(77.4);
			std::shared_ptr<Thread> pTh4(thread4);
			core->AddThread(pTh1,pCore);
			core->AddThread(pTh2,pCore);
			core->AddThread(pTh3,pCore);
			core->AddThread(pTh4,pCore);
			core->RemoveThread(pTh4);

			double addedThreads = (double)core->GetNoOfThreads();
			double activityLevel = core->GetActivityLevel();

			Assert::AreEqual(addedThreads,activityLevel);
		}


		// Check a specified thread is added to the core
		TEST_METHOD(CoreAddThread)
		{
			Core* core765 = new Core(765);
			Core* core1 = new Core(1);
			Core* core33333 = new Core(33333);
			std::shared_ptr<Core> pcore765(core765);
			std::shared_ptr<Core> pcore1(core1);
			std::shared_ptr<Core> pcore33333(core33333);

			Thread* thread2763 = new Thread(276.3);
			std::shared_ptr<Thread> pTh2763(thread2763);
			Thread* thread3 = new Thread(3);
			std::shared_ptr<Thread> pTh3(thread3);
			Thread* thread0009 = new Thread(0.009);
			std::shared_ptr<Thread> pTh0009(thread0009);

			core765->AddThread(pTh2763,pcore765);
			core1->AddThread(pTh3,pcore1);
			core33333->AddThread(pTh0009,pcore33333);

			int core765No = (thread2763->GetCore())->GetCoreNo();
			int core1No = (thread3->GetCore())->GetCoreNo();
			int core33333No = (thread0009->GetCore())->GetCoreNo();

			Assert::IsTrue((core765No == 765) && (core1No == 1) && (core33333No == 33333));
		}


		// Check a specified thread is removed from the core
		TEST_METHOD(CoreRemoveThread)
		{
			Core* core = new Core(8000);
			std::shared_ptr<Core> pcore(core);

			Thread* thread888 = new Thread(888);
			std::shared_ptr<Thread> pTh888(thread888);
			Thread* thread78 = new Thread(78);
			std::shared_ptr<Thread> pTh78(thread78);
			Thread* thread6904 = new Thread(6.904);
			std::shared_ptr<Thread> pTh6904(thread6904);

			core->AddThread(pTh888,pcore);
			core->AddThread(pTh78,pcore);
			core->AddThread(pTh6904,pcore);
			core->RemoveThread(pTh78);

			int noOfThreads = core->GetNoOfThreads();

			int core888No = (thread888->GetCore())->GetCoreNo();
			int core6904No = (thread6904->GetCore())->GetCoreNo();

			Assert::IsTrue((noOfThreads == 2) && (core888No == 8000) && (core6904No == 8000));
		}

		// Check no exception thrown when updating a core with no threads
		TEST_METHOD(CoreUpdateCore1)
		{
			Core core(5674);
			int noOfThreads = core.GetNoOfThreads();
			core.UpdateCore(1.0);

			Assert::AreEqual(noOfThreads,0);
		}

		// Check thread updating with no threads finishing
		TEST_METHOD(CoreUpdateCore2)
		{
			Core* core = new Core(8000);
			std::shared_ptr<Core> pcore(core);

			Thread* thread1 = new Thread(72.5);
			thread1->SetMemoryFactor(1);
			std::shared_ptr<Thread> pTh1(thread1);
			Thread* thread2 = new Thread(100.25);
			thread2->SetMemoryFactor(1);
			std::shared_ptr<Thread> pTh2(thread2);
			Thread* thread3 = new Thread(7);
			thread3->SetMemoryFactor(1);
			std::shared_ptr<Thread> pTh3(thread3);
			Thread* thread4 = new Thread(4.75);
			thread4->SetMemoryFactor(1);
			std::shared_ptr<Thread> pTh4(thread4);

			core->AddThread(pTh1,pcore);
			core->AddThread(pTh2,pcore);
			core->AddThread(pTh3,pcore);
			core->AddThread(pTh4,pcore);

			core->UpdateCore(2.0);

			double rem1 = thread1->GetRemainingDuration();
			double run1 = thread1->GetRunTime();
			double rem2 = thread2->GetRemainingDuration();
			double run2 = thread2->GetRunTime();
			double rem3 = thread3->GetRemainingDuration();
			double run3 = thread3->GetRunTime();
			double rem4 = thread4->GetRemainingDuration();
			double run4 = thread4->GetRunTime();

			Assert::IsTrue((run1 == 2) && (run2 == 2) && (run3 == 2) && (run4 == 2) && (rem1 == 72) && (rem2 == 99.75) && (rem3 == 6.5) && (rem4 == 4.25));
		}

		// Check thread updating with 2 threads finishing in the same iteration
		TEST_METHOD(CoreUpdateCore3)
		{
			Core* core = new Core(8000);
			std::shared_ptr<Core> pcore(core);

			Thread* thread1 = new Thread(1.0);
			thread1->SetMemoryFactor(1);
			std::shared_ptr<Thread> pTh1(thread1);
			Thread* thread2 = new Thread(101.0);
			thread2->SetMemoryFactor(1);
			std::shared_ptr<Thread> pTh2(thread2);
			Thread* thread3 = new Thread(2.0);
			thread3->SetMemoryFactor(1);
			std::shared_ptr<Thread> pTh3(thread3);
			Thread* thread4 = new Thread(15.5);
			thread4->SetMemoryFactor(1);
			std::shared_ptr<Thread> pTh4(thread4);

			core->AddThread(pTh1,pcore);
			core->AddThread(pTh2,pcore);
			core->AddThread(pTh3,pcore);
			core->AddThread(pTh4,pcore);

			core->UpdateCore(16.0);

			double rem1 = thread1->GetRemainingDuration();
			double run1 = thread1->GetRunTime();
			double rem2 = thread2->GetRemainingDuration();
			double run2 = thread2->GetRunTime();
			double rem3 = thread3->GetRemainingDuration();
			double run3 = thread3->GetRunTime();
			double rem4 = thread4->GetRemainingDuration();
			double run4 = thread4->GetRunTime();

			Assert::IsTrue((run1 == 1) && (run2 == 16) && (run3 == 2.0) && (run4 == 16) && (rem1 == 0) && (rem2 == 94.5) && (rem3 == 0) && (rem4 == 9));
		}


		// Check thread updating with 2 threads finishing in different loops
		TEST_METHOD(CoreUpdateCore4)
		{
			Core* core = new Core(8000);
			std::shared_ptr<Core> pcore(core);

			Thread* thread1 = new Thread(50.0);
			thread1->SetMemoryFactor(1);
			std::shared_ptr<Thread> pTh1(thread1);
			Thread* thread2 = new Thread(4.5);
			thread2->SetMemoryFactor(1);
			std::shared_ptr<Thread> pTh2(thread2);
			Thread* thread3 = new Thread(1.0);
			thread3->SetMemoryFactor(1);
			std::shared_ptr<Thread> pTh3(thread3);
			Thread* thread4 = new Thread(36.5);
			thread4->SetMemoryFactor(1);
			std::shared_ptr<Thread> pTh4(thread4);

			core->AddThread(pTh1,pcore);
			core->AddThread(pTh2,pcore);
			core->AddThread(pTh3,pcore);
			core->AddThread(pTh4,pcore);

			core->UpdateCore(16.0);

			double rem1 = thread1->GetRemainingDuration();
			double run1 = thread1->GetRunTime();
			double rem2 = thread2->GetRemainingDuration();
			double run2 = thread2->GetRunTime();
			double rem3 = thread3->GetRemainingDuration();
			double run3 = thread3->GetRunTime();
			double rem4 = thread4->GetRemainingDuration();
			double run4 = thread4->GetRunTime();

			Assert::IsTrue((run1 == 16) && (run2== 4.5) && (run3 == 1.0) && (run4 == 16) && (rem1 == 44.75) && (rem2 == 0) && (rem3 == 0) && (rem4 == 31.25));
		}

	};
}