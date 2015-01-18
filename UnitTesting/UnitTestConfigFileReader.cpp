#include "stdafx.h"
#include "CppUnitTest.h"
#include "ConfigFileReader.h"
#include "ConfigFileReader.cpp"
//#include "FactoryMemModel.h"
//#include "FactoryMemModel.cpp"
#include "FactoryProbDist.h"
//#include "FactoryProbDist.cpp"
//#include "FactoryTPStrategy.cpp"
#include "ProbDistBernoulli.cpp"
#include "ProbdistNormal.cpp"
#include "ProbDistPoisson.cpp"
#include "MemModelDemo.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(UnitTestConfigFileReader)
	{
	public:
		
		TEST_METHOD(ConfigFileReaderStreamValid1)
		{
			ConfigFileReader conf("H:\\workspace\\FinalProject\\tpsim\\UnitTesting\\config.txt");
			bool fileFound = conf.StreamValid();

			Assert::IsTrue(fileFound);
		}

		TEST_METHOD(ConfigFileReaderStreamValid2)
		{
			ConfigFileReader conf("H:\\workspace\\FinalProject\\tpsim\\UnitTesting\\nonsuch.txt");
			bool fileFound = conf.StreamValid();

			Assert::IsFalse(fileFound);
		}

		TEST_METHOD(ConfigFileReaderExtractParameters1)
		{
			ConfigFileReader conf("H:\\workspace\\FinalProject\\tpsim\\UnitTesting\\config.txt");
			vector<string> output;
			bool found = conf.ExtractParameters("nonsuch", output);

			Assert::IsTrue(!found && (output[0].compare("TPSIM_ERROR: could not find identifier nonsuch in config file.\n") == 0));
		}

		TEST_METHOD(ConfigFileReaderExtractParameters2)
		{
			ConfigFileReader conf("H:\\workspace\\FinalProject\\tpsim\\UnitTesting\\config.txt");
			vector<string> output;
			bool found = conf.ExtractParameters("threadDurationDistribution", output);

			Assert::IsTrue(found && (output[0].compare("Normal") == 0) && (output[1].compare("20") == 0) && (output[2].compare("6") == 0) && (output[3].compare("3401862510") == 0));
		}

		TEST_METHOD(ConfigFileReaderAssignParameterInt1)
		{
			ConfigFileReader conf("H:\\workspace\\FinalProject\\tpsim\\UnitTesting\\config.txt");
			int output = -99;
			string TPSIM_ERROR;
			bool found = conf.AssignParameter("nonsuch", output, TPSIM_ERROR);

			Assert::IsTrue(!found && (output == 0) && (TPSIM_ERROR.compare("TPSIM_ERROR: could not find identifier nonsuch in config file.\n") == 0));
		}

		TEST_METHOD(ConfigFileReaderAssignParameterInt2)
		{
			ConfigFileReader conf("H:\\workspace\\FinalProject\\tpsim\\UnitTesting\\config.txt");
			int output = 9876;
			string TPSIM_ERROR;
			bool valid = conf.AssignParameter("TPStrategy", output, TPSIM_ERROR);

			Assert::IsTrue(!valid && (output == 0) && (TPSIM_ERROR.compare("TPSIM_ERROR: could not convert parameter associated with TPStrategy to an integer.\n") == 0));
		}

		TEST_METHOD(ConfigFileReaderAssignParameterInt3)
		{
			ConfigFileReader conf("H:\\workspace\\FinalProject\\tpsim\\UnitTesting\\config.txt");
			int output = 50000;
			string TPSIM_ERROR;
			bool valid = conf.AssignParameter("maxRuntime", output, TPSIM_ERROR);

			Assert::IsTrue(valid && (output == 100) && (TPSIM_ERROR.compare("") == 0));
		}

		TEST_METHOD(ConfigFileReaderAssignParameterDouble1)
		{
			ConfigFileReader conf("H:\\workspace\\FinalProject\\tpsim\\UnitTesting\\config.txt");
			double output = 8.7654;
			string TPSIM_ERROR;
			bool found = conf.AssignParameter("nonsuch", output, TPSIM_ERROR);

			Assert::IsTrue(!found && output == 0 && (TPSIM_ERROR.compare("TPSIM_ERROR: could not find identifier nonsuch in config file.\n") == 0));
		}

		TEST_METHOD(ConfigFileReaderAssignParameterDouble2)
		{
			ConfigFileReader conf("H:\\workspace\\FinalProject\\tpsim\\UnitTesting\\config.txt");
			double output = 20.765;
			string TPSIM_ERROR;
			bool valid = conf.AssignParameter("MemModel", output, TPSIM_ERROR);

			Assert::IsTrue(!valid && (output == 0) && (TPSIM_ERROR.compare("TPSIM_ERROR: could not convert parameter associated with MemModel to a double.\n") == 0));
		}

		TEST_METHOD(ConfigFileReaderAssignParameterDouble3)
		{
			ConfigFileReader conf("H:\\workspace\\FinalProject\\tpsim\\UnitTesting\\config.txt");
			double output = 7.10101;
			string TPSIM_ERROR;
			bool valid = conf.AssignParameter("stepSize", output, TPSIM_ERROR);

			Assert::IsTrue(valid && (output == 1.0) && (TPSIM_ERROR.compare("") == 0));
		}

		TEST_METHOD(ConfigFileReaderAssignParameterMemModel1)
		{
			ConfigFileReader conf("H:\\workspace\\FinalProject\\tpsim\\UnitTesting\\configMissingEntries.txt");
			shared_ptr<MemModel> pMemModel;
			string TPSIM_ERROR;
			bool found = conf.AssignParameter("MemModel", pMemModel, TPSIM_ERROR);

			Assert::IsTrue(!found && !pMemModel && (TPSIM_ERROR.compare("TPSIM_ERROR: could not find identifier MemModel in config file.\n") == 0));
		}

		TEST_METHOD(ConfigFileReaderAssignParameterMemModel2)
		{
			ConfigFileReader conf("H:\\workspace\\FinalProject\\tpsim\\UnitTesting\\configBadData.txt");
			shared_ptr<MemModel> pMemModel;
			string TPSIM_ERROR;
			bool valid = conf.AssignParameter("MemModel", pMemModel, TPSIM_ERROR);

			Assert::IsTrue(!valid && !pMemModel && (TPSIM_ERROR.compare("TPSIM_ERROR: MemModel has no associated parameters.\nTPSIM_ERROR: could not create MemModel.\n") == 0));
		}

		TEST_METHOD(ConfigFileReaderAssignParameterMemModel3)
		{
			ConfigFileReader conf("H:\\workspace\\FinalProject\\tpsim\\UnitTesting\\config.txt");
			shared_ptr<MemModel> pMemModel;
			string TPSIM_ERROR;
			bool valid = conf.AssignParameter("MemModel", pMemModel, TPSIM_ERROR);

			Assert::IsTrue(valid && pMemModel && (TPSIM_ERROR.compare("") == 0));
		}

		TEST_METHOD(ConfigFileReaderAssignParameterProbDist1)
		{
			ConfigFileReader conf("H:\\workspace\\FinalProject\\tpsim\\UnitTesting\\configMissingEntries.txt");
			shared_ptr<ProbDist> pProbDist;
			string TPSIM_ERROR;
			bool found = conf.AssignParameter("nonsuch", pProbDist, TPSIM_ERROR);

			Assert::IsTrue(!found && !pProbDist && (TPSIM_ERROR.compare("TPSIM_ERROR: could not find identifier nonsuch in config file.\n") == 0));
		}

		TEST_METHOD(ConfigFileReaderAssignParameterProbDist2)
		{
			ConfigFileReader conf("H:\\workspace\\FinalProject\\tpsim\\UnitTesting\\configBadData.txt");
			shared_ptr<ProbDist> pProbDist;
			string TPSIM_ERROR;
			bool valid = conf.AssignParameter("noOfProcessesDistribution", pProbDist, TPSIM_ERROR);

			Assert::IsTrue(!valid && !pProbDist && (TPSIM_ERROR.compare("TPSIM_ERROR: probability distribution has no associated parameters.\nTPSIM_ERROR: could not create Probability Distribution noOfProcessesDistribution.\n") == 0));
		}

		TEST_METHOD(ConfigFileReaderAssignParameterProbDist3)
		{
			ConfigFileReader conf("H:\\workspace\\FinalProject\\tpsim\\UnitTesting\\config.txt");
			shared_ptr<ProbDist> pProbDist;
			string TPSIM_ERROR;
			bool valid = conf.AssignParameter("threadDurationDistribution", pProbDist, TPSIM_ERROR);

			Assert::IsTrue(valid && pProbDist && (TPSIM_ERROR.compare("") == 0));
		}

		TEST_METHOD(ConfigFileReaderAssignParameterTPStrategy1)
		{
			ConfigFileReader conf("H:\\workspace\\FinalProject\\tpsim\\UnitTesting\\configMissingEntries.txt");
			MemModel* memModel = new MemModelDemo(10,10);
			shared_ptr<MemModel> pMemModel(memModel);
			shared_ptr<TPStrategy> pTPStrategy;
			string TPSIM_ERROR;
			bool found = conf.AssignParameter("TPStrategy", pTPStrategy, pMemModel, TPSIM_ERROR);

			Assert::IsTrue(!found && !pTPStrategy && (TPSIM_ERROR.compare("TPSIM_ERROR: could not find identifier TPStrategy in config file.\n") == 0));
		}

		TEST_METHOD(ConfigFileReaderAssignParameterTPStrategy2)
		{
			ConfigFileReader conf("H:\\workspace\\FinalProject\\tpsim\\UnitTesting\\configBadData.txt");
			MemModel* memModel = new MemModelDemo(10,10);
			shared_ptr<MemModel> pMemModel(memModel);
			shared_ptr<TPStrategy> pTPStrategy;
			string TPSIM_ERROR;
			bool valid = conf.AssignParameter("TPStrategy", pTPStrategy, pMemModel, TPSIM_ERROR);

			Assert::IsTrue(!valid && !pTPStrategy && (TPSIM_ERROR.compare("TPSIM_ERROR: TPStrategy has no associated parameters.\nTPSIM_ERROR: could not create Thread Placement Strategy.\n") == 0));
		}

		TEST_METHOD(ConfigFileReaderAssignParameterTPStrategy3)
		{
			ConfigFileReader conf("H:\\workspace\\FinalProject\\tpsim\\UnitTesting\\config.txt");
			MemModel* memModel = new MemModelDemo(10,10);
			shared_ptr<MemModel> pMemModel(memModel);
			shared_ptr<TPStrategy> pTPStrategy;
			string TPSIM_ERROR;
			bool valid = conf.AssignParameter("TPStrategy", pTPStrategy, pMemModel, TPSIM_ERROR);

			Assert::IsTrue(valid && pTPStrategy && (TPSIM_ERROR.compare("") == 0));
		}

		TEST_METHOD(ConfigFileReaderAssignParameterOutputResults1)
		{
			ConfigFileReader conf("H:\\workspace\\FinalProject\\tpsim\\UnitTesting\\configMissingEntries.txt");
			OutputResults output;
			string TPSIM_ERROR;
			bool valid = conf.AssignParameter(output, TPSIM_ERROR);

			Assert::IsTrue(!valid && (TPSIM_ERROR.compare("TPSIM_ERROR: could not find identifier outputCoreLoad in config file.\nTPSIM_ERROR: could not find identifier outputRunTimes in config file.\n") == 0));
		}

		TEST_METHOD(ConfigFileReaderAssignParameterOutputResults2)
		{
			ConfigFileReader conf("H:\\workspace\\FinalProject\\tpsim\\UnitTesting\\configMissingOutput1.txt");
			OutputResults output;
			string TPSIM_ERROR;
			bool valid = conf.AssignParameter(output, TPSIM_ERROR);

			Assert::IsTrue(!valid && (TPSIM_ERROR.compare("TPSIM_ERROR: could not find identifier outputRunTimes in config file.\n") == 0));
		}

		TEST_METHOD(ConfigFileReaderAssignParameterOutputResults3)
		{
			ConfigFileReader conf("H:\\workspace\\FinalProject\\tpsim\\UnitTesting\\configMissingOutput2.txt");
			OutputResults output;
			string TPSIM_ERROR;
			bool valid = conf.AssignParameter(output, TPSIM_ERROR);

			Assert::IsTrue(!valid && (TPSIM_ERROR.compare("TPSIM_ERROR: could not find identifier outputCoreLoad in config file.\n") == 0));
		}

		TEST_METHOD(ConfigFileReaderAssignParameterOutputResults4)
		{
			ConfigFileReader conf("H:\\workspace\\FinalProject\\tpsim\\UnitTesting\\configBadData.txt");
			OutputResults output;
			string TPSIM_ERROR;
			bool valid = conf.AssignParameter(output, TPSIM_ERROR);

			Assert::IsTrue(!valid && (TPSIM_ERROR.compare("TPSIM_ERROR: no options associated with outputCoreLoad\n") == 0));
		}

		TEST_METHOD(ConfigFileReaderAssignParameterOutputResults5)
		{
			ConfigFileReader conf("H:\\workspace\\FinalProject\\tpsim\\UnitTesting\\configBadData2.txt");
			OutputResults output;
			string TPSIM_ERROR;
			bool valid = conf.AssignParameter(output, TPSIM_ERROR);

			Assert::IsTrue(!valid && (TPSIM_ERROR.compare("TPSIM_ERROR: first option associated with outputCoreLoad should be 'on' or 'off'\n") == 0));
		}

		TEST_METHOD(ConfigFileReaderAssignParameterOutputResults6)
		{
			ConfigFileReader conf("H:\\workspace\\FinalProject\\tpsim\\UnitTesting\\configBadData3.txt");
			OutputResults output;
			string TPSIM_ERROR;
			bool valid = conf.AssignParameter(output, TPSIM_ERROR);

			Assert::IsTrue(!valid && (TPSIM_ERROR.compare("TPSIM_ERROR: Cannot parse input for outputCoreLoad. Expecting [string] [int] after on/off option.\n") == 0));
		}

		TEST_METHOD(ConfigFileReaderAssignParameterOutputResults7)
		{
			ConfigFileReader conf("H:\\workspace\\FinalProject\\tpsim\\UnitTesting\\configBadData4.txt");
			OutputResults output;
			string TPSIM_ERROR;
			bool valid = conf.AssignParameter(output, TPSIM_ERROR);

			Assert::IsTrue(!valid && (TPSIM_ERROR.compare("TPSIM_ERROR: Cannot parse input for outputRunTimes. Expecting [string] after on/off option.\n") == 0));
		}

		TEST_METHOD(ConfigFileReaderAssignParameterOutputResults8)
		{
			ConfigFileReader conf("H:\\workspace\\FinalProject\\tpsim\\UnitTesting\\configOnOff.txt");
			OutputResults output;
			string TPSIM_ERROR = "";
			bool valid = conf.AssignParameter(output, TPSIM_ERROR);
			bool coreOn = output.CoreInfoIsActive();
			bool threadOn = output.ThreadInfoIsActive();

			Assert::IsTrue(valid && coreOn && !threadOn && (TPSIM_ERROR.compare("") == 0));
		}

		TEST_METHOD(ConfigFileReaderAssignParameterOutputResults9)
		{
			ConfigFileReader conf("H:\\workspace\\FinalProject\\tpsim\\UnitTesting\\configOffOn.txt");
			OutputResults output;
			string TPSIM_ERROR = "";
			bool valid = conf.AssignParameter(output, TPSIM_ERROR);
			bool coreOn = output.CoreInfoIsActive();
			bool threadOn = output.ThreadInfoIsActive();

			Assert::IsTrue(valid && !coreOn && threadOn && (TPSIM_ERROR.compare("") == 0));
		}
	};
}