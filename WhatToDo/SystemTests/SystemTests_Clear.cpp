//****************************************************************************
//@author A0110648L
//
// All system tests for an Clear user operation are performed here.

#include "stdafx.h"
#include "TestSupportLibrary.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SystemTests_Clear
{		
	TEST_CLASS(SystemTests_Clear)
	{
	public:
		
		// These tests are for the partition "Clear normal searches"

		TEST_METHOD(SystemTests_Clear_Search_01_Names)
		{
			string testPartition = "SystemTests_Clear_Search_01_Names";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Clear_Search_02_Tags)
		{
			string testPartition = "SystemTests_Clear_Search_02_Tags";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Clear_Search_03_NamesAndTags)
		{
			string testPartition = "SystemTests_Clear_Search_03_NamesAndTags";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Clear_Search_04_StrangeChars)
		{
			string testPartition = "SystemTests_Clear_Search_04_StrangeChars";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Clear_Search_05_MultipleTags)
		{
			string testPartition = "SystemTests_Clear_Search_05_MultipleTags";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Clear_Search_06_TooManyTags)
		{
			string testPartition = "SystemTests_Clear_Search_06_TooManyTags";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Clear_Search_07_TagsWithoutSpacing)
		{
			string testPartition = "SystemTests_Clear_Search_07_TagsWithoutSpacing";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Clear_Search_08_NamesAndTagsWithoutSpacing)
		{
			string testPartition = "SystemTests_Clear_Search_08_NamesAndTagsWithoutSpacing";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Clear_Search_09_InterspersedTags)
		{
			string testPartition = "SystemTests_Clear_Search_09_InterspersedTags";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Clear_Search_10_NamesWithSpace)
		{
			string testPartition = "SystemTests_Clear_Search_10_NamesWithSpace";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Clear_Search_11_IncorrectTags)
		{
			string testPartition = "SystemTests_Clear_Search_11_IncorrectTags";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		
		// These tests are for the partition "Clear fuzzy searches"

		TEST_METHOD(SystemTests_Clear_Search_Fuzzy_01)
		{
			string testPartition = "SystemTests_Clear_Search_Fuzzy_01";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Clear_Search_Fuzzy_02)
		{
			string testPartition = "SystemTests_Clear_Search_Fuzzy_02";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Clear_Search_Fuzzy_03)
		{
			string testPartition = "SystemTests_Clear_Search_Fuzzy_03";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		
		// These tests are for the partition "Clear acronym searches"

		TEST_METHOD(SystemTests_Clear_Search_Acronym_01)
		{
			string testPartition = "SystemTests_Clear_Search_Acronym_01";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Clear_Search_Acronym_02)
		{
			string testPartition = "SystemTests_Clear_Search_Acronym_02";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Clear_Search_Acronym_03)
		{
			string testPartition = "SystemTests_Clear_Search_Acronym_03";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		
		// These tests are for the partition "Clear shorthand searches"

		TEST_METHOD(SystemTests_Clear_Search_Shorthand_01)
		{
			string testPartition = "SystemTests_Clear_Search_Shorthand_01";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Clear_Search_Shorthand_02)
		{
			string testPartition = "SystemTests_Clear_Search_Shorthand_02";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Clear_Search_Shorthand_03)
		{
			string testPartition = "SystemTests_Clear_Search_Shorthand_03";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		
	}; 
}