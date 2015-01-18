#include "stdafx.h"
#include "CppUnitTest.h"
#include "ProbDistConstant.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(UnitTestProbDistConstant)
	{
	public:
		
		TEST_METHOD(ProbDistConstGetNextInt)
		{
			ProbDistConstant pDist(78.534);
			int next = pDist.GetNextInt();

			Assert::AreEqual(next,79);
		}

		TEST_METHOD(ProbDistConstGetNextDouble)
		{
			ProbDistConstant pDist(17.874);
			double next = pDist.GetNextDouble();

			Assert::AreEqual(next,17.874);
		}

		TEST_METHOD(ProbDistConstGetNextIntGEZero1)
		{
			ProbDistConstant pDist(0);
			int next = pDist.GetNextIntGEZero();

			Assert::AreEqual(next,0);
		}

		TEST_METHOD(ProbDistConstGetNextIntGEZero2)
		{
			ProbDistConstant pDist(-1);
			int next = pDist.GetNextIntGEZero();

			Assert::AreEqual(next,0);
		}

		TEST_METHOD(ProbDistConstGetNextDoubleGEZero1)
		{
			ProbDistConstant pDist(0);
			double next = pDist.GetNextDoubleGEZero();

			Assert::AreEqual(next,0.0);
		}

		TEST_METHOD(ProbDistConstGetNextDoubleGEZero2)
		{
			ProbDistConstant pDist(-0.0001);
			double next = pDist.GetNextDoubleGEZero();

			Assert::AreEqual(next,0.0);
		}

		TEST_METHOD(ProbDistConstGetNextIntGTZero1)
		{
			ProbDistConstant pDist(0);
			int next = pDist.GetNextIntGTZero();

			Assert::AreEqual(next,1);
		}

		TEST_METHOD(ProbDistConstGetNextIntGTZero2)
		{
			ProbDistConstant pDist(-1);
			int next = pDist.GetNextIntGTZero();

			Assert::AreEqual(next,1);
		}

		TEST_METHOD(ProbDistConstGetNextIntGTZero3)
		{
			ProbDistConstant pDist(2.654);
			int next = pDist.GetNextIntGTZero();

			Assert::AreEqual(next,3);
		}

		TEST_METHOD(ProbDistConstGetNextDoubleGTZero1)
		{
			ProbDistConstant pDist(0);
			double next = pDist.GetNextDoubleGTZero();

			Assert::AreEqual(next,std::numeric_limits<double>::epsilon());
		}

		TEST_METHOD(ProbDistConstGetNextDoubleGTZero2)
		{
			ProbDistConstant pDist(-0.0001);
			double next = pDist.GetNextDoubleGTZero();

			Assert::AreEqual(next,std::numeric_limits<double>::epsilon());
		}

		TEST_METHOD(ProbDistConstGetNextDoubleGTZero3)
		{
			ProbDistConstant pDist(1.0001);
			double next = pDist.GetNextDoubleGTZero();

			Assert::AreEqual(next,1.0001);
		}
	};
}