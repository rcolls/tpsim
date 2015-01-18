#include "stdafx.h"
#include "CppUnitTest.h"
#include "FactoryMemModel.h"
#include "FactoryMemModel.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(UnitTestFactoryMemModel)
	{
	public:
		
		TEST_METHOD(FactorymemModelCreateModel1)
		{
			vector<string> parameters;
			shared_ptr<MemModel> pMemModel;
			string errMessage;
			bool valid = FactoryMemModel::CreateMemModel(parameters,pMemModel,errMessage);

			Assert::IsTrue(!valid && !pMemModel && (errMessage.compare("TPSIM_ERROR: MemModel has no associated parameters.\n") == 0));
		}

		TEST_METHOD(FactorymemModelCreateModel2)
		{
			vector<string> parameters;
			parameters.push_back("nonsuch");
			shared_ptr<MemModel> pMemModel;
			string errMessage;
			bool valid = FactoryMemModel::CreateMemModel(parameters,pMemModel,errMessage);

			Assert::IsTrue(!valid && !pMemModel && (errMessage.compare("TPSIM_ERROR: FactoryMemModel does not recognize nonsuch.\n") == 0));
		}

		TEST_METHOD(FactorymemModelCreateModel3)
		{
			vector<string> parameters;
			parameters.push_back("MemModelDemo");
			parameters.push_back("NAN");
			shared_ptr<MemModel> pMemModel;
			string errMessage;
			bool valid = FactoryMemModel::CreateMemModel(parameters,pMemModel,errMessage);

			Assert::IsTrue(!valid && !pMemModel && (errMessage.compare("TPSIM_ERROR: FactoryMemModel cannot construct MemModelDemo. Expecting [int] [int] after model name.\n") == 0));
		}

		TEST_METHOD(FactorymemModelCreateModel4)
		{
			vector<string> parameters;
			parameters.push_back("MemModelDemo");
			parameters.push_back("17");
			parameters.push_back("786");
			shared_ptr<MemModel> pMemModel;
			string errMessage;
			bool valid = FactoryMemModel::CreateMemModel(parameters,pMemModel,errMessage);

			int rows = 0;
			int cols = 0;
			pMemModel->GetSize(rows,cols);

			Assert::IsTrue(valid && pMemModel && (rows == 17) && (cols == 786) && (errMessage.compare("") == 0));
		}

	};
}