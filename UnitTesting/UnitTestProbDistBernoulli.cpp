#include "stdafx.h"
#include "CppUnitTest.h"
#include "ProbDistBernoulli.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(UnitTestProbDistBernoulli)
	{
	public:
		
		TEST_METHOD(ProbDistBernoulliGetNextInt)
		{
			std::random_device rd;
		    unsigned int seedVal = rd();
			ProbDistBernoulli pDist(0.6,seedVal);
			int nextInt = pDist.GetNextInt();

			std::bernoulli_distribution dist(0.6);
			std::default_random_engine generator;
			generator.seed(seedVal);
			int rand = dist(generator);

			Assert::AreEqual(nextInt,rand);
		}

		TEST_METHOD(ProbDistBernoulliGetNextDouble)
		{
			std::random_device rd;
		    unsigned int seedVal = rd();
			ProbDistBernoulli pDist(0.3,seedVal);
			double nextDouble = pDist.GetNextDouble();

			std::bernoulli_distribution dist(0.3);
			std::default_random_engine generator;
			generator.seed(seedVal);
			double rand = (double)dist(generator);

			Assert::AreEqual(nextDouble,rand);
		}

		TEST_METHOD(ProbDistBernoulliGetIntGEZero)
		{
			std::random_device rd;
		    unsigned int seedVal = rd();
			ProbDistBernoulli pDist(0.1,seedVal);
			int nextInt = pDist.GetNextIntGEZero();

			std::bernoulli_distribution dist(0.1);
			std::default_random_engine generator;
			generator.seed(seedVal);
			int rand = dist(generator);

			Assert::IsTrue((nextInt == rand) && (nextInt >= 0));
		}

		TEST_METHOD(ProbDistBernoulliGetDoubleGEZero)
		{
			std::random_device rd;
		    unsigned int seedVal = rd();
			ProbDistBernoulli pDist(0.01,seedVal);
			double next = pDist.GetNextDoubleGEZero();

			std::bernoulli_distribution dist(0.01);
			std::default_random_engine generator;
			generator.seed(seedVal);
			double rand = (double)dist(generator);

			Assert::IsTrue((next == rand) && (next >= 0));
		}

		TEST_METHOD(ProbDistBernoulliGetIntGTZero)
		{
			std::random_device rd;
		    unsigned int seedVal = rd();
			ProbDistBernoulli pDist(0.00001,seedVal);
			int nextInt = 0;
			int minInt = 1;
			for(int i = 0; i < 1000; i++)
			{
				nextInt = pDist.GetNextIntGTZero();
				if(nextInt < minInt)
				{
					minInt = nextInt;
				}
			}

			Assert::AreEqual(minInt,1);
		}

		TEST_METHOD(ProbDistBernoulliGetDoubleGTZero)
		{
			std::random_device rd;
		    unsigned int seedVal = rd();
			ProbDistBernoulli pDist(0.007,seedVal);
			double nextInt = 0;
			double minInt = 1;
			for(int i = 0; i < 1000; i++)
			{
				nextInt = (double)pDist.GetNextDoubleGTZero();
				if(nextInt < minInt)
				{
					minInt = nextInt;
				}
			}

			Assert::AreEqual(minInt,1.0);
		}

	};
}