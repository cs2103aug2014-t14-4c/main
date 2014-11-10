//****************************************************************************
//@author A0110648L
//
// All system tests for a Load GUI operation are performed here.

#include "stdafx.h"
#include "TestSupportLibrary.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SystemTests_Load
{		
	TEST_CLASS(SystemTests_Load)
	{
	public:

		// This test is for the partition "a normal load"
		TEST_METHOD(SystemTests_Load_01_AllTaskTypes)
		{
			string testPartition = "SystemTests_Load_01_AllTaskTypes";
			TestSupportLibrary::writeInputDatabaseToDatabase(
				testPartition + INPUT_COMMAND_FILE_EXT);
			State actualState = LogicExecutor::getNewState(COMMAND_PARAM_LOAD);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		
	}; 
}