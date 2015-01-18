#include "stdafx.h"
#include "CppUnitTest.h"
#include "Thread.h"
#include "Core.h"
#include "OutputResults.h"

using std::shared_ptr;


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(UnitTestThread)
	{
	public:
		
		TEST_METHOD(ThreadGetMinimumDuration)
		{
			Thread thread = Thread(77.65);
			double minDur = thread.GetMinimumDuration();
			Assert::AreEqual(minDur,77.65);
		}

		TEST_METHOD(ThreadGetRemainingDuration)
		{
			Thread thread = Thread(33.624);
			double remDur = thread.GetRemainingDuration();
			Assert::AreEqual(remDur,33.624);
		}


		TEST_METHOD(ThreadGetRemainingDuration2)
		{
			Thread *thread = new Thread(100.25);
			thread->SetMemoryFactor(1);
			shared_ptr<Thread> pThread(thread);

			Core* core = new Core(33);
			shared_ptr<Core> pCore(core);

			core->AddThread(pThread,pCore);

			thread->UpdateThread(1,0,1);
			double remDur = thread->GetRemainingDuration();
			Assert::AreEqual(remDur,99.25);
		}


		TEST_METHOD(ThreadGetRunTime)
		{
			Thread thread = Thread(77);
			double runtime = thread.GetRunTime();
			Assert::AreEqual(runtime,0.0);
		}


		TEST_METHOD(ThreadGetRunTime2)
		{
			Thread *thread = new Thread(7.009);
			thread->SetMemoryFactor(1);
			shared_ptr<Thread> pThread(thread);

			Core* core = new Core(1001);
			shared_ptr<Core> pCore(core);

			core->AddThread(pThread,pCore);

			thread->UpdateThread(1,0,93.666);
			thread->UpdateThread(1,0,1.2);
			double runtime = thread->GetRunTime();
			Assert::AreEqual(runtime,94.866);
		}

		TEST_METHOD(ThreadUpdateThread)
		{
			Thread *thread = new Thread(26.84);
			shared_ptr<Thread> pThread(thread);

			Core* core = new Core(345);
			shared_ptr<Core> pCore(core);

			thread->SetCore(pCore);
			shared_ptr<Core> pCoreReturned = thread->GetCore();

			thread->SetMemoryFactor(0.25);
			thread->UpdateThread(10,0,35.48);
			thread->SetMemoryFactor(0.2);
			double leftover = thread->UpdateThread(25,0,15.67);
			double remTime = thread->GetRemainingDuration();
			double runTime = thread->GetRunTime();
			Assert::IsTrue((leftover == 0) && (runTime == 51.15) && (remTime == 19.34));
		}


		TEST_METHOD(ThreadUpdateThread2)
		{
			Thread *thread = new Thread(77.83);
			shared_ptr<Thread> pThread(thread);

			Core* core = new Core(12);
			shared_ptr<Core> pCore(core);

			thread->SetCore(pCore);
			shared_ptr<Core> pCoreReturned = thread->GetCore();

			thread->SetMemoryFactor(0.8);
			thread->UpdateThread(5,0,17);
			thread->SetMemoryFactor(0.25);
			double leftover = thread->UpdateThread(1,0,35.45);
			leftover = thread->UpdateThread(8,1,35.45);
			double remTime = thread->GetRemainingDuration();
			double runTime = thread->GetRunTime();
			Assert::IsTrue((leftover == 0) && (runTime == 52.45) && (remTime == 71.83));
		}


		TEST_METHOD(ThreadUpdateThread3)
		{
			Thread *thread = new Thread(1.5);
			shared_ptr<Thread> pThread(thread);

			Core* core = new Core(12);
			shared_ptr<Core> pCore(core);

			thread->SetCore(pCore);
			shared_ptr<Core> pCoreReturned = thread->GetCore();

			thread->SetMemoryFactor(1);
			double leftover = thread->UpdateThread(1,0,33);
			thread->SetMemoryFactor(0.8);
			leftover = thread->UpdateThread(1,0,66.09);
			double remTime = thread->GetRemainingDuration();
			double runTime = thread->GetRunTime();
			Assert::IsTrue((leftover == 0.375) && (runTime == 33.625) && (remTime == 0));
		}

		TEST_METHOD(ThreadIsComplete1)
		{
			Thread thread = Thread(4.356);
			bool complete = thread.IsComplete();
			Assert::IsFalse(complete);
		}

		TEST_METHOD(ThreadIsComplete2)
		{
			Thread thread = Thread(0);
			bool complete = thread.IsComplete();
			Assert::IsTrue(complete);
		}


		TEST_METHOD(ThreadGetAndSetCore)
		{
			Thread *thread = new Thread(34.908);
			shared_ptr<Thread> pThread(thread);

			Core* core = new Core(55555);
			shared_ptr<Core> pCore(core);

			thread->SetCore(pCore);
			shared_ptr<Core> pCoreReturned = thread->GetCore();

			Assert::AreEqual(pCore->GetCoreNo(),pCoreReturned->GetCoreNo());
		}

		TEST_METHOD(ThreadSetMemoryFactor)
		{
			Thread *thread = new Thread(17.6);
			thread->SetMemoryFactor(0.25);
			shared_ptr<Thread> pThread(thread);

			Core* core = new Core(5);
			shared_ptr<Core> pCore(core);

			core->AddThread(pThread,pCore);

			thread->UpdateThread(4,0,50);
			double remDur = thread->GetRemainingDuration();
			Assert::AreEqual(remDur,16.6);
		}

		
		TEST_METHOD(ThreadGetMemoryFactor)
		{
			Thread *thread = new Thread(47.1);
			thread->SetMemoryFactor(66.609);
			double memoryFactor = thread->GetMemoryFactor();
			Assert::AreEqual(memoryFactor,66.609);
		}

	};
}