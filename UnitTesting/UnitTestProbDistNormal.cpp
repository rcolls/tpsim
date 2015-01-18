#include "stdafx.h"
#include "CppUnitTest.h"
#include "ProbDistNormal.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(UnitTestProbDistNormal)
	{
	public:
		
		TEST_METHOD(ProbDistNormalGetNextInt)
		{
			std::random_device rd;
		    unsigned int seedVal = rd();
			ProbDistNormal pDist(55.876,7.34,seedVal);
			int nextInt = pDist.GetNextInt();

			std::normal_distribution<double> dist(55.876,7.34);
			std::default_random_engine generator;
			generator.seed(seedVal);
			double f = dist(generator);
			int tmp = static_cast<int> (f);
			tmp += (f-tmp >= 0.5) - (f-tmp <= -0.5);

			Assert::AreEqual(nextInt,tmp);
		}

		TEST_METHOD(ProbDistNormalGetNextDouble)
		{
			std::random_device rd;
		    unsigned int seedVal = rd();
			ProbDistNormal pDist(100.9,500,seedVal);
			double next = pDist.GetNextDouble();

			std::normal_distribution<double> dist(100.9,500);
			std::default_random_engine generator;
			generator.seed(seedVal);
			double rand = dist(generator);

			Assert::AreEqual(next,rand);
		}

		TEST_METHOD(ProbDistNormalGetNextIntGEZero)
		{
			std::random_device rd;
		    unsigned int seedVal = rd();
			ProbDistNormal pDist(-5,2,seedVal);
			int nextInt = pDist.GetNextIntGEZero();

			std::normal_distribution<double> dist(-5,2);
			std::default_random_engine generator;
			generator.seed(seedVal);
			double f = dist(generator);
			int tmp = static_cast<int> (f);
			tmp += (f-tmp >= 0.5) - (f-tmp <= -0.5);
			while(f < 0.0)
			{
				f = dist(generator);
				tmp = static_cast<int> (f);
				tmp += (f-tmp >= 0.5) - (f-tmp <= -0.5);
			}
			 
			Assert::IsTrue((nextInt == tmp) && (nextInt >= 0));
		}
		   
		TEST_METHOD(ProbDistNormalGetNextDoubleGEZero)
		{
			std::random_device rd;
		    unsigned int seedVal = rd();
			ProbDistNormal pDist(-8.654,5,seedVal);
			double next = pDist.GetNextDoubleGEZero();

			std::normal_distribution<double> dist(-8.654,5);
			std::default_random_engine generator;
			generator.seed(seedVal);
			double rand = dist(generator);
			while(rand < 0.0)
			{
				rand = dist(generator);
			}

			Assert::IsTrue((next == rand) && (next >= 0));
		}
		        
		TEST_METHOD(ProbDistNormalGetNextIntGTZero)
		{
			std::random_device rd;
		    unsigned int seedVal = rd();
			ProbDistNormal pDist(-10.1,4,seedVal);
			int nextInt = pDist.GetNextIntGTZero();

			std::normal_distribution<double> dist(-10.1,4);
			std::default_random_engine generator;
			generator.seed(seedVal);
			double f = dist(generator);
			int tmp = static_cast<int> (f);
			tmp += (f-tmp >= 0.5) - (f-tmp <= -0.5);
			while(tmp <= 0)
			{
				f = dist(generator);
				tmp = static_cast<int> (f);
				tmp += (f-tmp >= 0.5) - (f-tmp <= -0.5);
			}

			Assert::IsTrue((nextInt == tmp) && (nextInt > 0));
		}

		TEST_METHOD(ProbDistNormalGetNextDoubleGTZero)
		{
			std::random_device rd;
		    unsigned int seedVal = rd();
			ProbDistNormal pDist(-2,1,seedVal);
			double next = pDist.GetNextDoubleGTZero();

			std::normal_distribution<double> dist(-2,1);
			std::default_random_engine generator;
			generator.seed(seedVal);
			double rand = dist(generator);
			while(rand <= 0.0)
			{
				rand = dist(generator);
			}

			Assert::IsTrue((next == rand) && (next > 0));
		}

	};
}