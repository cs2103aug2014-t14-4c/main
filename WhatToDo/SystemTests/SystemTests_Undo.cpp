//****************************************************************************
//@author A0110648L
//
// All system tests for an Undo user operation are performed here.

#include "stdafx.h"
#include "TestSupportLibrary.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SystemTests_Undo
{		
	TEST_CLASS(SystemTests_Undo)
	{
	public:
		
		// These tests are for the partition "Undo following different
		// task types"

		TEST_METHOD(SystemTests_Undo_One_01_Add)
		{
			string testPartition = "SystemTests_Undo_One_01_Add";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Undo_One_02_Delete)
		{
			string testPartition = "SystemTests_Undo_One_02_Delete";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Undo_One_03_Edit)
		{
			string testPartition = "SystemTests_Undo_One_03_Edit";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Undo_One_04_Done)
		{
			string testPartition = "SystemTests_Undo_One_04_Done";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Undo_One_05_Search)
		{
			string testPartition = "SystemTests_Undo_One_05_Search";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Undo_One_06_Clear)
		{
			string testPartition = "SystemTests_Undo_One_06_Clear";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Undo_Two_01_Add)
		{
			string testPartition = "SystemTests_Undo_Two_01_Add";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Undo_Two_02_Delete)
		{
			string testPartition = "SystemTests_Undo_Two_02_Delete";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Undo_Two_03_Edit)
		{
			string testPartition = "SystemTests_Undo_Two_03_Edit";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Undo_Two_04_Done)
		{
			string testPartition = "SystemTests_Undo_Two_04_Done";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}

		
	}; 
}