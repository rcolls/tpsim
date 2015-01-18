#include "stdafx.h"
#include "CppUnitTest.h"
#include "OutputResults.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(UnitTestOutputResults)
	{
	public:
		
		TEST_METHOD(OutputResultsGetOutputOptions)
		{
			OutputResults output;
			vector<string> all = output.GetOutputOptions();

			Assert::IsTrue((all[0] == "outputCoreLoad") && (all[1] == "outputRunTimes"));
		}

		TEST_METHOD(OutputResultsActivateCoreInfoOptionAndCoreInfoIsActive)
		{
			OutputResults output;
			bool init = output.CoreInfoIsActive();
			output.ActivateCoreInfoOption("dummy.txt",5);
			bool final = output.CoreInfoIsActive();

			Assert::IsTrue(init == false && final == true);
		}

		TEST_METHOD(OutputResultsActivateCoreInfoOptionAndGetOutputCoreInterval)
		{
			OutputResults output;
			output.ActivateCoreInfoOption("somename.txt",17);
			int interval = output.GetCoreOutputInterval();

			Assert::AreEqual(interval,17);
		}

		TEST_METHOD(OutputResultsActivateThreadInfoOptionAndThreadInfoIsActive)
		{
			OutputResults output;
			bool init = output.ThreadInfoIsActive();
			output.ActivateThreadInfoOption("threadout.txt");
			bool final = output.ThreadInfoIsActive();

			Assert::IsTrue(init == false && final == true);
		}

		TEST_METHOD(OutputResultsClose1)
		{
			OutputResults output;
			output.ActivateCoreInfoOption("coreout.txt",4);
			output.ActivateThreadInfoOption("threadout.txt");
			bool init1 = output.CoreInfoIsActive();
			bool init2 = output.ThreadInfoIsActive();

			output.Close();

			bool final1 = output.CoreInfoIsActive();
			bool final2 = output.ThreadInfoIsActive();

			Assert::IsTrue((init1 == true) && (init2 == true) && (final1 == false) && (final2 == false)); 
		}

		TEST_METHOD(OutputResultsClose2)
		{
			OutputResults output;
			output.ActivateCoreInfoOption("coreout.txt",4);
			output.ActivateThreadInfoOption("threadout.txt");
			bool init1 = output.CoreInfoIsActive();
			bool init2 = output.ThreadInfoIsActive();

			output.Close();
			output.Close();

			bool final1 = output.CoreInfoIsActive();
			bool final2 = output.ThreadInfoIsActive();

			Assert::IsTrue((init1 == true) && (init2 == true) && (final1 == false) && (final2 == false)); 
		}

		TEST_METHOD(OutputResultsCloseCoreStream)
		{
			OutputResults output;
			output.ActivateCoreInfoOption("core.txt",4);
			output.ActivateThreadInfoOption("thread.txt");
			bool init1 = output.CoreInfoIsActive();
			bool init2 = output.ThreadInfoIsActive();
			output.CloseCoreStream();
			bool final1 = output.CoreInfoIsActive();
			bool final2 = output.ThreadInfoIsActive();

			Assert::IsTrue((init1 == true) && (init2 == true) && (final1 == false) && (final2 == true)); 
		}

		TEST_METHOD(OutputResultsCloseThreadStream)
		{
			OutputResults output;
			output.ActivateCoreInfoOption("core.txt",4);
			output.ActivateThreadInfoOption("thread.txt");
			bool init1 = output.CoreInfoIsActive();
			bool init2 = output.ThreadInfoIsActive();
			output.CloseThreadStream();
			bool final1 = output.CoreInfoIsActive();
			bool final2 = output.ThreadInfoIsActive();

			Assert::IsTrue((init1 == true) && (init2 == true) && (final1 == true) && (final2 == false)); 
		}

	};
}