//****************************************************************************
//@author A0110648L
//
// All system tests for an Add user operation are performed here.

#include "stdafx.h"
#include "TestSupportLibrary.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SystemTests_Add
{		
	TEST_CLASS(SystemTests_Add)
	{
	public:

		// These tests are for the partition "Add floating tasks"

		TEST_METHOD(SystemTests_Add_Floating_01_Multiple)
		{
			string testPartition = "SystemTests_Add_Floating_01_Multiple";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_Floating_02_LongTaskNames)
		{
			string testPartition = "SystemTests_Add_Floating_02_LongTaskNames";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_Floating_03_StrangeChars)
		{
			string testPartition = "SystemTests_Add_Floating_03_StrangeChars";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_Floating_04_NormalTags)
		{
			string testPartition = "SystemTests_Add_Floating_04_NormalTags";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_Floating_05_MultipleTags)
		{
			string testPartition = "SystemTests_Add_Floating_05_MultipleTags";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_Floating_06_MultipleTagsInterspersed)
		{
			string testPartition = "SystemTests_Add_Floating_06_MultipleTagsInterspersed";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		
		// These tests are for the partition "Add due all day tasks"

		TEST_METHOD(SystemTests_Add_DueAllDay_01_Multiple)
		{
			string testPartition = "SystemTests_Add_DueAllDay_01_Multiple";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_DueAllDay_02_MultipleTags)
		{
			string testPartition = "SystemTests_Add_DueAllDay_02_MultipleTags";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_DueAllDay_03_SameDay)
		{
			string testPartition = "SystemTests_Add_DueAllDay_03_SameDay";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}

		// These tests are for the partition "Add due timed tasks"

		TEST_METHOD(SystemTests_Add_DueTimed_01_Multiple)
		{
			string testPartition = "SystemTests_Add_DueTimed_01_Multiple";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_DueTimed_02_MultipleTags)
		{
			string testPartition = "SystemTests_Add_DueTimed_02_MultipleTags";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_DueTimed_03_SameDay)
		{
			string testPartition = "SystemTests_Add_DueTimed_03_SameDay";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_DueTimed_04_SameTime)
		{
			string testPartition = "SystemTests_Add_DueTimed_04_SameTime";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		
		// These tests are for the partition "Add fixed all day tasks"

		TEST_METHOD(SystemTests_Add_FixedAllDay_01_Multiple)
		{
			string testPartition = "SystemTests_Add_FixedAllDay_01_Multiple";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_FixedAllDay_02_MultipleTags)
		{
			string testPartition = "SystemTests_Add_FixedAllDay_02_MultipleTags";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_FixedAllDay_03_SameDay)
		{
			string testPartition = "SystemTests_Add_FixedAllDay_03_SameDay";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		
		// These tests are for the partition "Add fixed start tasks"

		TEST_METHOD(SystemTests_Add_FixedStart_01_Multiple)
		{
			string testPartition = "SystemTests_Add_FixedStart_01_Multiple";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_FixedStart_02_MultipleTags)
		{
			string testPartition = "SystemTests_Add_FixedStart_02_MultipleTags";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_FixedStart_03_SameDay)
		{
			string testPartition = "SystemTests_Add_FixedStart_03_SameDay";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_FixedStart_04_SameTime)
		{
			string testPartition = "SystemTests_Add_FixedStart_04_SameTime";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		
		// These tests are for the partition "Add fixed timed tasks"

		TEST_METHOD(SystemTests_Add_FixedTime_01_TimetoTime)
		{
			string testPartition = "SystemTests_Add_FixedTime_01_TimetoTime";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_FixedTime_02_TimetoTimeOverlap)
		{
			string testPartition = "SystemTests_Add_FixedTime_02_TimetoTimeOverlap";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_FixedTime_03_TimetoDay)
		{
			string testPartition = "SystemTests_Add_FixedTime_03_TimetoDay";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_FixedTime_04_TimetoDayOverlap)
		{
			string testPartition = "SystemTests_Add_FixedTime_04_TimetoDayOverlap";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_FixedTime_05_DaytoTime)
		{
			string testPartition = "SystemTests_Add_FixedTime_05_DaytoTime";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_FixedTime_06_DaytoTimeOverlap)
		{
			string testPartition = "SystemTests_Add_FixedTime_06_DaytoTimeOverlap";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_FixedTime_07_DaytoDay)
		{
			string testPartition = "SystemTests_Add_FixedTime_07_DaytoDay";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_FixedTime_08_DaytoDayOverlap)
		{
			string testPartition = "SystemTests_Add_FixedTime_08_DaytoDayOverlap";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_FixedTime_09_StartAfterEnd)
		{
			string testPartition = "SystemTests_Add_FixedTime_09_StartAfterEnd";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		
		// These tests are for the partition "Add tasks with different time formats"

		TEST_METHOD(SystemTests_Add_TimeFormats_01_HhmmFormat)
		{
			string testPartition = "SystemTests_Add_TimeFormats_01_HhmmFormat";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_TimeFormats_02_AmpmFormat)
		{
			string testPartition = "SystemTests_Add_TimeFormats_02_AmpmFormat";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_TimeFormats_03_AmpmAndHhmmFormat)
		{
			string testPartition = "SystemTests_Add_TimeFormats_03_AmpmAndHhmmFormat";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_TimeFormats_04_WayInThePast)
		{
			string testPartition = "SystemTests_Add_TimeFormats_04_WayInThePast";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_TimeFormats_05_WayInTheFuture)
		{
			string testPartition = "SystemTests_Add_TimeFormats_05_WayInTheFuture";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_TimeFormats_06_WayInPastToWayInFuture)
		{
			string testPartition = "SystemTests_Add_TimeFormats_06_WayInPastToWayInFuture";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		
		// These tests are for the partition "Add tasks of different types"

		TEST_METHOD(SystemTests_Add_MixedTypes_01)
		{
			string testPartition = "SystemTests_Add_MixedTypes_01";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_MixedTypes_02)
		{
			string testPartition = "SystemTests_Add_MixedTypes_02";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_MixedTypes_03)
		{
			string testPartition = "SystemTests_Add_MixedTypes_03";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_MixedTypes_04)
		{
			string testPartition = "SystemTests_Add_MixedTypes_04";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_MixedTypes_05)
		{
			string testPartition = "SystemTests_Add_MixedTypes_05";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_MixedTypes_06)
		{
			string testPartition = "SystemTests_Add_MixedTypes_06";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_MixedTypes_07)
		{
			string testPartition = "SystemTests_Add_MixedTypes_07";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_MixedTypes_08)
		{
			string testPartition = "SystemTests_Add_MixedTypes_08";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_MixedTypes_09)
		{
			string testPartition = "SystemTests_Add_MixedTypes_09";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		TEST_METHOD(SystemTests_Add_MixedTypes_10)
		{
			string testPartition = "SystemTests_Add_MixedTypes_10";
			State actualState = TestSupportLibrary::executeCommandsFromInputFile(
				testPartition + INPUT_COMMAND_FILE_EXT);
			
			TestSupportLibrary::checkIsStateEqualsExpected(actualState, 
				testPartition + EXPECTED_STATE_FILE_EXT);
		}
		
	}; 
}