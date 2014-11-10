//****************************************************************************
//@author A0110648L
//
// All system tests for a Filter user operation are performed here.

#include "stdafx.h"
#include "TestSupportLibrary.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SystemTests_Filter
{		
	TEST_CLASS(SystemTests_Filter)
	{
	public:
		
		// These tests are for the partition "Filter by task type"

		TEST_METHOD(SystemTests_Filter_Type_01_AllTypes)
		{
			string testPartition = "SystemTests_Filter_Type_01_AllTypes";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Filter_Type_02_Due)
		{
			string testPartition = "SystemTests_Filter_Type_02_Due";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Filter_Type_03_Fixed)
		{
			string testPartition = "SystemTests_Filter_Type_03_Fixed";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		
		// These tests are for the partition "Filter by done type"

		TEST_METHOD(SystemTests_Filter_Done_01_NoDone)
		{
			string testPartition = "SystemTests_Filter_Done_01_NoDone";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Filter_Done_02_Done)
		{
			string testPartition = "SystemTests_Filter_Done_02_Done";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Filter_Done_03_Undone)
		{
			string testPartition = "SystemTests_Filter_Done_03_Undone";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
	
		// These tests are for the partition "Filter by date"

		TEST_METHOD(SystemTests_Filter_Date_01_PastStartDate)
		{
			string testPartition = "SystemTests_Filter_Date_01_PastStartDate";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Filter_Date_02_FutureStartDate)
		{
			string testPartition = "SystemTests_Filter_Date_02_FutureStartDate";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Filter_Date_03_StartAndEnd)
		{
			string testPartition = "SystemTests_Filter_Date_03_StartAndEnd";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		
		// These tests are for the partition "Filter multiple combinations"

		TEST_METHOD(SystemTests_Filter_Strange_01_NoParam)
		{
			string testPartition = "SystemTests_Filter_Strange_01_NoParam";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Filter_Strange_02_WrongParams)
		{
			string testPartition = "SystemTests_Filter_Strange_02_WrongParams";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Filter_Strange_03_SpaceBtwParams)
		{
			string testPartition = "SystemTests_Filter_Strange_03_SpaceBtwParams";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		
		// These tests are for the partition "Add floating tasks"

		TEST_METHOD(SystemTests_Filter_Mixed_01_AllTypes_NoDone_StartDate)
		{
			string testPartition = "SystemTests_Filter_Mixed_01_AllTypes_NoDone_StartDate";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Filter_Mixed_02_AllTypes_NoDone_StartAndEndDate)
		{
			string testPartition = "SystemTests_Filter_Mixed_02_AllTypes_NoDone_StartAndEndDate";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Filter_Mixed_03_AllTypes_Done_StartDate)
		{
			string testPartition = "SystemTests_Filter_Mixed_03_AllTypes_Done_StartDate";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Filter_Mixed_04_AllTypes_Done_StartAndEndDate)
		{
			string testPartition = "SystemTests_Filter_Mixed_04_AllTypes_Done_StartAndEndDate";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Filter_Mixed_05_AllTypes_Undone_StartDate)
		{
			string testPartition = "SystemTests_Filter_Mixed_05_AllTypes_Undone_StartDate";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Filter_Mixed_06_AllTypes_Undone_StartAndEndDate)
		{
			string testPartition = "SystemTests_Filter_Mixed_06_AllTypes_Undone_StartAndEndDate";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Filter_Mixed_07_Fixed_NoDone_StartDate)
		{
			string testPartition = "SystemTests_Filter_Mixed_07_Fixed_NoDone_StartDate";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Filter_Mixed_08_Fixed_NoDone_StartAndEndDate)
		{
			string testPartition = "SystemTests_Filter_Mixed_08_Fixed_NoDone_StartAndEndDate";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Filter_Mixed_09_Fixed_Done_StartDate)
		{
			string testPartition = "SystemTests_Filter_Mixed_09_Fixed_Done_StartDate";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Filter_Mixed_10_Fixed_Done_StartAndEndDate)
		{
			string testPartition = "SystemTests_Filter_Mixed_10_Fixed_Done_StartAndEndDate";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Filter_Mixed_11_Fixed_Undone_StartDate)
		{
			string testPartition = "SystemTests_Filter_Mixed_11_Fixed_Undone_StartDate";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Filter_Mixed_12_Fixed_Undone_StartAndEndDate)
		{
			string testPartition = "SystemTests_Filter_Mixed_12_Fixed_Undone_StartAndEndDate";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Filter_Mixed_13_Due_NoDone_StartDate)
		{
			string testPartition = "SystemTests_Filter_Mixed_13_Due_NoDone_StartDate";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Filter_Mixed_14_Due_NoDone_StartAndEndDate)
		{
			string testPartition = "SystemTests_Filter_Mixed_14_Due_NoDone_StartAndEndDate";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Filter_Mixed_15_Due_Done_StartDate)
		{
			string testPartition = "SystemTests_Filter_Mixed_15_Due_Done_StartDate";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Filter_Mixed_16_Due_Done_StartAndEndDate)
		{
			string testPartition = "SystemTests_Filter_Mixed_16_Due_Done_StartAndEndDate";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Filter_Mixed_17_Due_Undone_StartDate)
		{
			string testPartition = "SystemTests_Filter_Mixed_17_Due_Undone_StartDate";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Filter_Mixed_18_Due_Undone_StartAndEndDate)
		{
			string testPartition = "SystemTests_Filter_Mixed_18_Due_Undone_StartAndEndDate";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}

	}; 
}