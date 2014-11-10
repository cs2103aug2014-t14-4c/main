//****************************************************************************
//@author A0110648L
//
// All system tests for a Delete user operation are performed here.

#include "stdafx.h"
#include "TestSupportLibrary.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SystemTests_Delete
{		
	TEST_CLASS(SystemTests_Delete)
	{
	public:
		
		// These tests are for the partition "Delete one tasks"

		TEST_METHOD(SystemTests_Delete_One_01_Floating)
		{
			string testPartition = "SystemTests_Delete_One_01_Floating";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Delete_One_02_DueAllDay)
		{
			string testPartition = "SystemTests_Delete_One_02_DueAllDay";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Delete_One_03_DueTimed)
		{
			string testPartition = "SystemTests_Delete_One_03_DueTimed";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Delete_One_04_FixedAllDay)
		{
			string testPartition = "SystemTests_Delete_One_04_FixedAllDay";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Delete_One_05_FixedStart)
		{
			string testPartition = "SystemTests_Delete_One_05_FixedStart";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Delete_One_06_FixedTime_DayToDay)
		{
			string testPartition = "SystemTests_Delete_One_06_FixedTime_DayToDay";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Delete_One_07_FixedTime_DayToTime)
		{
			string testPartition = "SystemTests_Delete_One_07_FixedTime_DayToTime";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Delete_One_08_FixedTime_TimeToDay)
		{
			string testPartition = "SystemTests_Delete_One_08_FixedTime_TimeToDay";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Delete_One_09_FixedTime_TimeToTime)
		{
			string testPartition = "SystemTests_Delete_One_09_FixedTime_TimeToTime";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		
		// These tests are for the partition "Delete multiple tasks"

		TEST_METHOD(SystemTests_Delete_Multiple_01_Floating)
		{
			string testPartition = "SystemTests_Delete_Multiple_01_Floating";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Delete_Multiple_02_DueAllDay)
		{
			string testPartition = "SystemTests_Delete_Multiple_02_DueAllDay";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Delete_Multiple_03_DueTimed)
		{
			string testPartition = "SystemTests_Delete_Multiple_03_DueTimed";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Delete_Multiple_04_FixedAllDay)
		{
			string testPartition = "SystemTests_Delete_Multiple_04_FixedAllDay";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Delete_Multiple_05_FixedStart)
		{
			string testPartition = "SystemTests_Delete_Multiple_05_FixedStart";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Delete_Multiple_06_FixedTime_DayToDay)
		{
			string testPartition = "SystemTests_Delete_Multiple_06_FixedTime_DayToDay";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Delete_Multiple_07_FixedTime_DayToTime)
		{
			string testPartition = "SystemTests_Delete_Multiple_07_FixedTime_DayToTime";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Delete_Multiple_08_FixedTime_TimeToDay)
		{
			string testPartition = "SystemTests_Delete_Multiple_08_FixedTime_TimeToDay";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Delete_Multiple_09_FixedTime_TimeToTime)
		{
			string testPartition = "SystemTests_Delete_Multiple_09_FixedTime_TimeToTime";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		
		// These tests are for the partition "Strange delete commands"

		TEST_METHOD(SystemTests_Delete_Strange_01_LargeIndex)
		{
			string testPartition = "SystemTests_Delete_Strange_01_LargeIndex";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Delete_Strange_02_VeryLargeIndex)
		{
			string testPartition = "SystemTests_Delete_Strange_02_VeryLargeIndex";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Delete_Strange_03_NegativeIndex)
		{
			string testPartition = "SystemTests_Delete_Strange_03_NegativeIndex";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Delete_Strange_04_VeryNegativeIndex)
		{
			string testPartition = "SystemTests_Delete_Strange_04_VeryNegativeIndex";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Delete_Strange_05_NonNumberIndex)
		{
			string testPartition = "SystemTests_Delete_Strange_05_NonNumberIndex";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Delete_Strange_06_StringIndex)
		{
			string testPartition = "SystemTests_Delete_Strange_06_StringIndex";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Delete_Strange_07_NoIndex)
		{
			string testPartition = "SystemTests_Delete_Strange_07_NoIndex";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Delete_Strange_08_BlankIndex)
		{
			string testPartition = "SystemTests_Delete_Strange_08_BlankIndex";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Delete_Strange_09_MultipleIndex)
		{
			string testPartition = "SystemTests_Delete_Strange_09_MultipleIndex";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Delete_Strange_10_WrongCommand)
		{
			string testPartition = "SystemTests_Delete_Strange_10_WrongCommand";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Delete_Strange_11_SpacesBtwCommandAndIndex)
		{
			string testPartition = "SystemTests_Delete_Strange_11_SpacesBtwCommandAndIndex";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Delete_Strange_12_NoSpaceBtwCommandAndIndex)
		{
			string testPartition = "SystemTests_Delete_Strange_12_NoSpaceBtwCommandAndIndex";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}

	}; 
}