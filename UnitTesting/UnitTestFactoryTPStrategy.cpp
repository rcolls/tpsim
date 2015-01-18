#include "stdafx.h"
#include "CppUnitTest.h"
#include "FactoryTPStrategy.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(UnitTestFactoryTPStrategy)
	{
	public:
		
		TEST_METHOD(TPStrategyCreateTPStrategy1)
		{
			vector<string> parameters;
			shared_ptr<TPStrategy> pTPStrategy;
			shared_ptr<MemModel> pMemModel;
			string errMessage;

			bool valid = FactoryTPStrategy::CreateTPStrategy(parameters,pTPStrategy,pMemModel,errMessage);

			Assert::IsTrue(!valid && !pTPStrategy && (errMessage.compare("TPSIM_ERROR: TPStrategy has no associated parameters.\n") == 0));
		}

		TEST_METHOD(FactoryTPStrategyCreateTPStrategy2)
		{
			vector<string> parameters;
			parameters.push_back("nonsuch");
			shared_ptr<TPStrategy> pTPStrategy;
			shared_ptr<MemModel> pMemModel;
			string errMessage;

			bool valid = FactoryTPStrategy::CreateTPStrategy(parameters,pTPStrategy,pMemModel,errMessage);

			Assert::IsTrue(!valid && !pTPStrategy && (errMessage.compare("TPSIM_ERROR: FactoryMemModel does not recognize nonsuch.\n") == 0));
		}

		TEST_METHOD(FactoryTPStrategyCreateTPStrategy3)
		{
			vector<string> parameters;
			parameters.push_back("TPStrategyDemo");
			shared_ptr<TPStrategy> pTPStrategy;
			shared_ptr<MemModel> pMemModel;
			string errMessage;

			bool valid = FactoryTPStrategy::CreateTPStrategy(parameters,pTPStrategy,pMemModel,errMessage);

			Assert::IsTrue(!valid && !pTPStrategy && (errMessage.compare("TPSIM_ERROR: FactoryTPStrategy cannot construct TPStrategyDemo. Expecting [string] after model name\n") == 0));
		}

		TEST_METHOD(FactoryTPStrategyCreateTPStrategy4)
		{
			vector<string> parameters;
			parameters.push_back("TPStrategyDemo");
			parameters.push_back("migOn");
			shared_ptr<TPStrategy> pTPStrategy;
			shared_ptr<MemModel> pMemModel;
			string errMessage;

			bool valid = FactoryTPStrategy::CreateTPStrategy(parameters,pTPStrategy,pMemModel,errMessage);

			Assert::IsTrue(valid && pTPStrategy && (errMessage.compare("") == 0));
		}

	};
}