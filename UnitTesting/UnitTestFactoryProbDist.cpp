#include "stdafx.h"
#include "CppUnitTest.h"
#include "FactoryProbDist.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(UnitTestFactoryProbDist)
	{
	public:
		
		TEST_METHOD(FactoryProbDistGetSeed1)
		{
			string seedString = "rand";
			unsigned int seedVal1;
			string errMessage;

			bool valid1 = FactoryProbDist::GetSeed(seedString,seedVal1,errMessage);

			Assert::IsTrue(!valid1 && (seedVal1 == 0) && (errMessage.compare("TPSIM_ERROR: Cannot parse rand to a uint.\n") == 0));
		}


		TEST_METHOD(FactoryProbDistGetSeed2)
		{
			string seedString = "random";
			unsigned int seedVal1;
			unsigned int seedVal2;
			unsigned int seedVal3;
			string errMessage;

			bool valid1 = FactoryProbDist::GetSeed(seedString,seedVal1,errMessage);
			bool valid2 = FactoryProbDist::GetSeed(seedString,seedVal2,errMessage);
			bool valid3 = FactoryProbDist::GetSeed(seedString,seedVal3,errMessage);

			Assert::IsTrue(valid1 && valid2 && valid3 && (seedVal1 != seedVal2) && (seedVal1 != seedVal3) && (seedVal2 != seedVal3) && (errMessage.compare("") == 0));
		}

		TEST_METHOD(FactoryProbDistGetSeed3)
		{
			string seedString = "50265";
			unsigned int seedVal1;
			string errMessage;

			bool valid1 = FactoryProbDist::GetSeed(seedString,seedVal1,errMessage);

			Assert::IsTrue(valid1 && (seedVal1 == 50265) && (errMessage.compare("") == 0));
		}


		TEST_METHOD(FactoryProbDistCreateNew1)
		{
			vector<string> parameters;
			shared_ptr<ProbDist> pDistribution;
			string errMessage;

			bool valid = FactoryProbDist::CreateNew(parameters,pDistribution,errMessage);

			Assert::IsTrue(!valid && !pDistribution && (errMessage.compare("TPSIM_ERROR: probability distribution has no associated parameters.\n") == 0));
		}

		TEST_METHOD(FactoryProbDistCreateNew2)
		{
			vector<string> parameters;
			parameters.push_back("nonsuch");
			shared_ptr<ProbDist> pDistribution;
			string errMessage;

			bool valid = FactoryProbDist::CreateNew(parameters,pDistribution,errMessage);

			Assert::IsTrue(!valid && !pDistribution && (errMessage.compare("TPSIM_ERROR: FactoryProbDist does not recognize nonsuch.\n") == 0));
		}

		TEST_METHOD(FactoryProbDistCreateNew3)
		{
			vector<string> parameters;
			parameters.push_back("Poisson");
			shared_ptr<ProbDist> pDistribution;
			string errMessage;

			bool valid = FactoryProbDist::CreateNew(parameters,pDistribution,errMessage);

			Assert::IsTrue(!valid && !pDistribution && (errMessage.compare("TPSIM_ERROR: FactoryProbDist cannot construct Poisson. Expecting [double] ['random' or uint] after distribution name.\n") == 0));
		}

		TEST_METHOD(FactoryProbDistCreateNew4)
		{
			vector<string> parameters;
			parameters.push_back("Poisson");
			parameters.push_back("0");

			shared_ptr<ProbDist> pDistribution;
			string errMessage;

			bool valid = FactoryProbDist::CreateNew(parameters,pDistribution,errMessage);

			Assert::IsTrue(!valid && !pDistribution && (errMessage.compare("TPSIM_ERROR: FactoryProbDist cannot construct Poisson. Input parameter must be greater than zero.\n") == 0));
		}

		TEST_METHOD(FactoryProbDistCreateNew5)
		{
			vector<string> parameters;
			parameters.push_back("Poisson");
			parameters.push_back("1");

			shared_ptr<ProbDist> pDistribution;
			string errMessage;

			bool valid = FactoryProbDist::CreateNew(parameters,pDistribution,errMessage);

			Assert::IsTrue(!valid && !pDistribution && (errMessage.compare("TPSIM_ERROR: FactoryProbDist cannot construct Poisson. Expecting [double] ['random' or uint] after distribution name.\n") == 0));
		}

		TEST_METHOD(FactoryProbDistCreateNew6)
		{
			vector<string> parameters;
			parameters.push_back("Poisson");
			parameters.push_back("1");
			parameters.push_back("NAN");

			shared_ptr<ProbDist> pDistribution;
			string errMessage;

			bool valid = FactoryProbDist::CreateNew(parameters,pDistribution,errMessage);

			Assert::IsTrue(!valid && !pDistribution && (errMessage.compare("TPSIM_ERROR: Cannot parse NAN to a uint.\nTPSIM_ERROR: FactoryProbDist cannot construct Poisson. Possibly seed option is invalid.\n") == 0));
		}


		TEST_METHOD(FactoryProbDistCreateNew7)
		{
			vector<string> parameters;
			parameters.push_back("Poisson");
			parameters.push_back("0.1");
			parameters.push_back("random");

			shared_ptr<ProbDist> pDistribution;
			string errMessage;

			bool valid = FactoryProbDist::CreateNew(parameters,pDistribution,errMessage);

			int rand1 = pDistribution->GetNextInt();

			std::poisson_distribution<int> dist(0.1);
			std::default_random_engine generator;
			generator.seed(stoul(parameters[2]));
			int rand2 = dist(generator);

			Assert::IsTrue(valid && pDistribution && (rand1 == rand2) && (errMessage.compare("") == 0));
		}

		TEST_METHOD(FactoryProbDistCreateNew8)
		{
			vector<string> parameters;
			parameters.push_back("Poisson");
			parameters.push_back("6.2");
			parameters.push_back("3622201");

			shared_ptr<ProbDist> pDistribution;
			string errMessage;

			bool valid = FactoryProbDist::CreateNew(parameters,pDistribution,errMessage);

			int rand1 = pDistribution->GetNextInt();

			std::poisson_distribution<int> dist(6.2);
			std::default_random_engine generator;
			generator.seed(3622201);
			int rand2 = dist(generator);

			Assert::IsTrue(valid && pDistribution && (rand1 == rand2) && (errMessage.compare("") == 0));
		}

		TEST_METHOD(FactoryProbDistCreateNew9)
		{
			vector<string> parameters;
			parameters.push_back("Normal");
			shared_ptr<ProbDist> pDistribution;
			string errMessage;

			bool valid = FactoryProbDist::CreateNew(parameters,pDistribution,errMessage);

			Assert::IsTrue(!valid && !pDistribution && (errMessage.compare("TPSIM_ERROR: FactoryProbDist cannot construct Normal. Expecting [double] [double] ['random' or uint] after distribution name.\n") == 0));
		}

		TEST_METHOD(FactoryProbDistCreateNew10)
		{
			vector<string> parameters;
			parameters.push_back("Normal");
			parameters.push_back("-100");
			parameters.push_back("-0.1");

			shared_ptr<ProbDist> pDistribution;
			string errMessage;

			bool valid = FactoryProbDist::CreateNew(parameters,pDistribution,errMessage);

			Assert::IsTrue(!valid && !pDistribution && (errMessage.compare("TPSIM_ERROR: Normal distribution stDev must be greater than zero.\n") == 0));
		}

		TEST_METHOD(FactoryProbDistCreateNew11)
		{
			vector<string> parameters;
			parameters.push_back("Normal");
			parameters.push_back("-100");
			parameters.push_back("0.1");
			parameters.push_back("invalid");

			shared_ptr<ProbDist> pDistribution;
			string errMessage;

			bool valid = FactoryProbDist::CreateNew(parameters,pDistribution,errMessage);

			Assert::IsTrue(!valid && !pDistribution && (errMessage.compare("TPSIM_ERROR: Cannot parse invalid to a uint.\nTPSIM_ERROR: FactoryProbDist cannot construct Normal. Possibly seed option is invalid.\n") == 0));
		}

		TEST_METHOD(FactoryProbDistCreateNew12)
		{
			vector<string> parameters;
			parameters.push_back("Normal");
			parameters.push_back("500");
			parameters.push_back("20");
			parameters.push_back("random");

			shared_ptr<ProbDist> pDistribution;
			string errMessage;

			bool valid = FactoryProbDist::CreateNew(parameters,pDistribution,errMessage);

			double rand1 = pDistribution->GetNextDouble();

			std::normal_distribution<double> dist(500,20);
			std::default_random_engine generator;
			generator.seed(stoul(parameters[3]));
			double rand2 = dist(generator);

			Assert::IsTrue(valid && pDistribution && (rand1 == rand2) && (errMessage.compare("") == 0));
		}

		TEST_METHOD(FactoryProbDistCreateNew13)
		{
			vector<string> parameters;
			parameters.push_back("Normal");
			parameters.push_back("763");
			parameters.push_back("90");
			parameters.push_back("287");

			shared_ptr<ProbDist> pDistribution;
			string errMessage;

			bool valid = FactoryProbDist::CreateNew(parameters,pDistribution,errMessage);

			double rand1 = pDistribution->GetNextDouble();

			std::normal_distribution<double> dist(763,90);
			std::default_random_engine generator;
			generator.seed(287);
			double rand2 = dist(generator);

			Assert::IsTrue(valid && pDistribution && (rand1 == rand2) && (errMessage.compare("") == 0));
		}

		TEST_METHOD(FactoryProbDistCreateNew14)
		{
			vector<string> parameters;
			parameters.push_back("Bernoulli");
			shared_ptr<ProbDist> pDistribution;
			string errMessage;

			bool valid = FactoryProbDist::CreateNew(parameters,pDistribution,errMessage);

			Assert::IsTrue(!valid && !pDistribution && (errMessage.compare("TPSIM_ERROR: FactoryProbDist cannot construct Bernoulli. Expecting [double] ['random' or uint] after distribution name.\n") == 0));
		}

		TEST_METHOD(FactoryProbDistCreateNew15)
		{
			vector<string> parameters;
			parameters.push_back("Bernoulli");
			parameters.push_back("-0.1");

			shared_ptr<ProbDist> pDistribution;
			string errMessage;

			bool valid = FactoryProbDist::CreateNew(parameters,pDistribution,errMessage);

			Assert::IsTrue(!valid && !pDistribution && (errMessage.compare("TPSIM_ERROR: Bernoulli distribution parameter must be 0<=p<=1.\n") == 0));
		}

		TEST_METHOD(FactoryProbDistCreateNew16)
		{
			vector<string> parameters;
			parameters.push_back("Bernoulli");
			parameters.push_back("1.1");

			shared_ptr<ProbDist> pDistribution;
			string errMessage;

			bool valid = FactoryProbDist::CreateNew(parameters,pDistribution,errMessage);

			Assert::IsTrue(!valid && !pDistribution && (errMessage.compare("TPSIM_ERROR: Bernoulli distribution parameter must be 0<=p<=1.\n") == 0));
		}

		TEST_METHOD(FactoryProbDistCreateNew17)
		{
			vector<string> parameters;
			parameters.push_back("Bernoulli");
			parameters.push_back("0.567");
			parameters.push_back("typo");

			shared_ptr<ProbDist> pDistribution;
			string errMessage;

			bool valid = FactoryProbDist::CreateNew(parameters,pDistribution,errMessage);

			Assert::IsTrue(!valid && !pDistribution && (errMessage.compare("TPSIM_ERROR: Cannot parse typo to a uint.\nTPSIM_ERROR: FactoryProbDist cannot construct Bernoulli. Possibly seed option is invalid.\n") == 0));
		}

		TEST_METHOD(FactoryProbDistCreateNew18)
		{
			vector<string> parameters;
			parameters.push_back("Bernoulli");
			parameters.push_back("0.5");
			parameters.push_back("random");

			shared_ptr<ProbDist> pDistribution;
			string errMessage;

			bool valid = FactoryProbDist::CreateNew(parameters,pDistribution,errMessage);

			int rand1 = pDistribution->GetNextInt();

			std::bernoulli_distribution dist(0.5);
			std::default_random_engine generator;
			generator.seed(stoul(parameters[2]));
			int rand2 = dist(generator);

			Assert::IsTrue(valid && pDistribution && (rand1 == rand2) && (errMessage.compare("") == 0));
		}

		
		TEST_METHOD(FactoryProbDistCreateNew19)
		{
			vector<string> parameters;
			parameters.push_back("Bernoulli");
			parameters.push_back("0.4");
			parameters.push_back("11111101");

			shared_ptr<ProbDist> pDistribution;
			string errMessage;

			bool valid = FactoryProbDist::CreateNew(parameters,pDistribution,errMessage);

			int rand1 = pDistribution->GetNextInt();

			std::bernoulli_distribution dist(0.4);
			std::default_random_engine generator;
			generator.seed(11111101);
			int rand2 = dist(generator);

			Assert::IsTrue(valid && pDistribution && (rand1 == rand2) && (errMessage.compare("") == 0));
		}

		TEST_METHOD(FactoryProbDistCreateNew20)
		{
			vector<string> parameters;
			parameters.push_back("Constant");
			shared_ptr<ProbDist> pDistribution;
			string errMessage;

			bool valid = FactoryProbDist::CreateNew(parameters,pDistribution,errMessage);

			Assert::IsTrue(!valid && !pDistribution && (errMessage.compare("TPSIM_ERROR: FactoryProbDist cannot construct Constant. Expecting [double] after distribution name.\n") == 0));
		}

		TEST_METHOD(FactoryProbDistCreateNew21)
		{
			vector<string> parameters;
			parameters.push_back("Constant");
			parameters.push_back("9876.54");

			shared_ptr<ProbDist> pDistribution;
			string errMessage;

			bool valid = FactoryProbDist::CreateNew(parameters,pDistribution,errMessage);

			double rand1 = pDistribution->GetNextDouble();

			Assert::IsTrue(valid && pDistribution && (rand1 == 9876.54) && (errMessage.compare("") == 0));
		}

	};
}