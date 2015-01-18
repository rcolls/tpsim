#include "stdafx.h"
#include "CppUnitTest.h"
#include "ProbDistPoisson.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(UnitTestProbDistPoisson)
	{
	public:
		
		TEST_METHOD(ProbDistPoissonGetNextInt)
		{
			std::random_device rd;
		    unsigned int seedVal = rd();
			ProbDistPoisson pDist(3.419,seedVal);
			int next = pDist.GetNextInt();

			std::poisson_distribution<int> dist(3.419);
			std::default_random_engine generator;
			generator.seed(seedVal);
			int rand = dist(generator);

			Assert::AreEqual(next,rand);
		}

		TEST_METHOD(ProbDistPoissonGetNextDouble)
		{
			std::random_device rd;
		    unsigned int seedVal = rd();
			ProbDistPoisson pDist(7.912,seedVal);
			double next = pDist.GetNextDouble();

			std::poisson_distribution<int> dist(7.912);
			std::default_random_engine generator;
			generator.seed(seedVal);
			double rand = (double)dist(generator);

			Assert::AreEqual(next,rand);
		}
		
		TEST_METHOD(ProbDistPoissonGetNextIntGEZero)
		{
			std::random_device rd;
		    unsigned int seedVal = rd();
			ProbDistPoisson pDist(0.3,seedVal);
			int next = pDist.GetNextIntGEZero();

			std::poisson_distribution<int> dist(0.3);
			std::default_random_engine generator;
			generator.seed(seedVal);
			int rand = dist(generator);
			while(rand < 0)
			{
				rand = dist(generator);
			}

			Assert::IsTrue((next == rand) && (next >=0));
		}

		TEST_METHOD(ProbDistPoissonGetNextDoubleGEZero)
		{
			std::random_device rd;
		    unsigned int seedVal = rd();
			ProbDistPoisson pDist(0.55,seedVal);
			double next = pDist.GetNextDoubleGEZero();

			std::poisson_distribution<int> dist(0.55);
			std::default_random_engine generator;
			generator.seed(seedVal);
			double rand = (double)dist(generator);
			while(rand < 0)
			{
				rand = dist(generator);
			}

			Assert::IsTrue((next == rand) && (next >=0));
		}

		TEST_METHOD(ProbDistPoissonGetNextIntGTZero)
		{
			std::random_device rd;
		    unsigned int seedVal = rd();
			ProbDistPoisson pDist(0.002,seedVal);
			int next = pDist.GetNextIntGTZero();

			std::poisson_distribution<int> dist(0.002);
			std::default_random_engine generator;
			generator.seed(seedVal);
			int rand = dist(generator);
			while(rand <= 0)
			{
				rand = dist(generator);
			}

			Assert::IsTrue((next == rand) && (next > 0));
		}

		TEST_METHOD(ProbDistPoissonGetNextDoubleGTZero)
		{
			std::random_device rd;
		    unsigned int seedVal = rd();
			ProbDistPoisson pDist(0.001,seedVal);
			double next = pDist.GetNextDoubleGTZero();

			std::poisson_distribution<int> dist(0.001);
			std::default_random_engine generator;
			generator.seed(seedVal);
			double rand = (double)dist(generator);
			while(rand <= 0.0)
			{
				rand = dist(generator);
			}

			Assert::IsTrue((next == rand) && (next > 0));
		}
	};
}