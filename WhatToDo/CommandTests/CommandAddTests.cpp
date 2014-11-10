//****************************************************************************
//@author A0110648L
//
// All unit tests for CommmandAdd are performed here.

#include "stdafx.h"
#include "CppUnitTest.h"
#include "TestSupportLibrary.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommandAddTests
{		
	TEST_CLASS(CommandAddTests)
	{
	public:

		// This is a test case falling under the "normal 
		// adding process" partition

		TEST_METHOD(CommandAdd_NormalSuccessfulAdd)
		{
			// Initiating the LogicData with an initial state
			
			State initialState;
			State expectedCurrentState;
			State expectedViewState;
			State actualCurrentState;
			State actualViewState;

			Task anotherTask;
			string anotherTaskName;
			string anotherTaskStartTime;
			string anotherTaskEndTime;
			string anotherTaskDeadline;
			vector<string> anotherTaskTags;
			bool anotherTaskIsDone;
			
			anotherTaskName = "Finish Tutorial 1";
			anotherTaskStartTime = "20141120T100000";
			anotherTaskEndTime = "20141120T110000";
			anotherTaskDeadline = "not-a-date-time";
			anotherTaskTags.clear();
			anotherTaskTags.push_back("#cs2103");
			anotherTaskTags.push_back("#homework");
			anotherTaskIsDone = false;
			anotherTask = TestSupportLibrary::createTask(
				anotherTaskName, anotherTaskStartTime, 
				anotherTaskEndTime, anotherTaskDeadline, 
				anotherTaskTags, anotherTaskIsDone);
			initialState.addTask(anotherTask);
			
			anotherTaskName = "Practice Moonlight Sonata";
			anotherTaskStartTime = "not-a-date-time";
			anotherTaskEndTime = "not-a-date-time";
			anotherTaskDeadline = "not-a-date-time";
			anotherTaskTags.clear();
			anotherTaskTags.push_back("#homework");
			anotherTaskTags.push_back("#tutorial");
			anotherTaskIsDone = false;
			anotherTask = TestSupportLibrary::createTask(
				anotherTaskName, anotherTaskStartTime,
				anotherTaskEndTime, anotherTaskDeadline, 
				anotherTaskTags, anotherTaskIsDone);
			initialState.addTask(anotherTask);

			anotherTaskName = "Surf the web";
			anotherTaskStartTime = "not-a-date-time";
			anotherTaskEndTime = "not-a-date-time";
			anotherTaskDeadline = "20141120T110000";
			anotherTaskTags.clear();
			anotherTaskTags.push_back("#free");
			anotherTaskIsDone = false;
			anotherTask = TestSupportLibrary::createTask(
				anotherTaskName, anotherTaskStartTime, 
				anotherTaskEndTime, anotherTaskDeadline,
				anotherTaskTags, anotherTaskIsDone);
			initialState.addTask(anotherTask);
			
			LogicData::fakeinitiate(initialState);
			
			// Creating a command and the expected states to test

			Command* testCommand = new CommandAdd;
			
			anotherTaskName = "Watch some TV";
			anotherTaskStartTime = "not-a-date-time";
			anotherTaskEndTime = "not-a-date-time";
			anotherTaskDeadline = "not-a-date-time";
			anotherTaskTags.clear();
			anotherTaskTags.push_back("#free");
			anotherTaskIsDone = false;
			anotherTask = TestSupportLibrary::createTask(
				anotherTaskName, anotherTaskStartTime, 
				anotherTaskEndTime, anotherTaskDeadline, 
				anotherTaskTags, anotherTaskIsDone);
			initialState.addTask(anotherTask);
			testCommand->setCurrentTask(anotherTask);

			expectedCurrentState = initialState;
			expectedViewState = expectedCurrentState;
			expectedViewState.setActionMessage(
				"Task Added!  ||  Filtered by: all types / undone");
			expectedCurrentState.setActionMessage("Task Added!");

			// Obtaining the actual eventual states

			testCommand->execute();
			actualViewState = LogicData::getViewState();
			actualCurrentState = LogicData::getCurrentState();

			// Perform the testing

			TestSupportLibrary::compareStates(
				expectedViewState,actualViewState);
			TestSupportLibrary::compareStates(
				expectedCurrentState,actualCurrentState);
		}

		// This is a test case falling under the "failed add
		// due to timing overlap" partition

		TEST_METHOD(CommandAdd_TimingOverlap)
		{
			// Initiating the LogicData with an initial state
			
			State initialState;
			State expectedCurrentState;
			State expectedViewState;
			State actualCurrentState;
			State actualViewState;

			Task anotherTask;
			string anotherTaskName;
			string anotherTaskStartTime;
			string anotherTaskEndTime;
			string anotherTaskDeadline;
			vector<string> anotherTaskTags;
			bool anotherTaskIsDone;
			
			anotherTaskName = "Finish Tutorial 1";
			anotherTaskStartTime = "20141120T100000";
			anotherTaskEndTime = "20141120T110000";
			anotherTaskDeadline = "not-a-date-time";
			anotherTaskTags.clear();
			anotherTaskTags.push_back("#cs2103");
			anotherTaskTags.push_back("#homework");
			anotherTaskIsDone = false;
			anotherTask = TestSupportLibrary::createTask(
				anotherTaskName, anotherTaskStartTime, 
				anotherTaskEndTime, anotherTaskDeadline, 
				anotherTaskTags, anotherTaskIsDone);
			initialState.addTask(anotherTask);
			
			anotherTaskName = "Practice Moonlight Sonata";
			anotherTaskStartTime = "not-a-date-time";
			anotherTaskEndTime = "not-a-date-time";
			anotherTaskDeadline = "not-a-date-time";
			anotherTaskTags.clear();
			anotherTaskTags.push_back("#homework");
			anotherTaskTags.push_back("#tutorial");
			anotherTaskIsDone = false;
			anotherTask = TestSupportLibrary::createTask(
				anotherTaskName, anotherTaskStartTime,
				anotherTaskEndTime, anotherTaskDeadline, 
				anotherTaskTags, anotherTaskIsDone);
			initialState.addTask(anotherTask);

			anotherTaskName = "Surf the web";
			anotherTaskStartTime = "not-a-date-time";
			anotherTaskEndTime = "not-a-date-time";
			anotherTaskDeadline = "20141120T110000";
			anotherTaskTags.clear();
			anotherTaskTags.push_back("#free");
			anotherTaskIsDone = false;
			anotherTask = TestSupportLibrary::createTask(
				anotherTaskName, anotherTaskStartTime,
				anotherTaskEndTime, anotherTaskDeadline, 
				anotherTaskTags, anotherTaskIsDone);
			initialState.addTask(anotherTask);

			LogicData::fakeinitiate(initialState);
			
			// Creating a command and the expected states to test

			Command* testCommand = new CommandAdd;
			
			anotherTaskName = "Watch some TV";
			anotherTaskStartTime = "20141120T090000";
			anotherTaskEndTime = "20141120T101500";
			anotherTaskDeadline = "not-a-date-time";
			anotherTaskTags.clear();
			anotherTaskTags.push_back("#free");
			anotherTaskIsDone = false;
			anotherTask = TestSupportLibrary::createTask(
				anotherTaskName, anotherTaskStartTime, 
				anotherTaskEndTime, anotherTaskDeadline, 
				anotherTaskTags, anotherTaskIsDone);
			testCommand->setCurrentTask(anotherTask);
			initialState.addTask(anotherTask);

			expectedCurrentState = initialState;
			expectedViewState = expectedCurrentState;
			expectedViewState.setUserMessage(
				"Task Added! Note: Beware task overlap!");
			expectedViewState.setActionMessage(
				"Task Added!  ||  Filtered by: all types / undone");
			expectedCurrentState.setUserMessage(
				"Task Added! Note: Beware task overlap!");
			expectedCurrentState.setActionMessage(
				"Task Added!");

			// Obtaining the actual eventual states

			testCommand->execute();
			actualViewState = LogicData::getViewState();
			actualCurrentState = LogicData::getCurrentState();

			// Perform the testing

			TestSupportLibrary::compareStates(
				expectedViewState,actualViewState);
			TestSupportLibrary::compareStates(
				expectedCurrentState,actualCurrentState);
		}

		// This is a test case falling under the "failed add
		// due to incorrect time ordering" partition

		TEST_METHOD(CommandAdd_EndTimeBeforeStartTime)
		{
			// Initiating the LogicData with an initial state
			
			State initialState;
			State expectedCurrentState;
			State expectedViewState;
			State actualCurrentState;
			State actualViewState;

			Task anotherTask;
			string anotherTaskName;
			string anotherTaskStartTime;
			string anotherTaskEndTime;
			string anotherTaskDeadline;
			vector<string> anotherTaskTags;
			bool anotherTaskIsDone;
			
			anotherTaskName = "Finish Tutorial 1";
			anotherTaskStartTime = "20141120T100000";
			anotherTaskEndTime = "20141120T110000";
			anotherTaskDeadline = "not-a-date-time";
			anotherTaskTags.clear();
			anotherTaskTags.push_back("#cs2103");
			anotherTaskTags.push_back("#homework");
			anotherTaskIsDone = false;
			anotherTask = TestSupportLibrary::createTask(
				anotherTaskName, anotherTaskStartTime, 
				anotherTaskEndTime, anotherTaskDeadline, 
				anotherTaskTags, anotherTaskIsDone);
			initialState.addTask(anotherTask);
			
			anotherTaskName = "Practice Moonlight Sonata";
			anotherTaskStartTime = "not-a-date-time";
			anotherTaskEndTime = "not-a-date-time";
			anotherTaskDeadline = "not-a-date-time";
			anotherTaskTags.clear();
			anotherTaskTags.push_back("#homework");
			anotherTaskTags.push_back("#tutorial");
			anotherTaskIsDone = false;
			anotherTask = TestSupportLibrary::createTask(
				anotherTaskName, anotherTaskStartTime,
				anotherTaskEndTime, anotherTaskDeadline, 
				anotherTaskTags, anotherTaskIsDone);
			initialState.addTask(anotherTask);

			anotherTaskName = "Surf the web";
			anotherTaskStartTime = "not-a-date-time";
			anotherTaskEndTime = "not-a-date-time";
			anotherTaskDeadline = "20141120T110000";
			anotherTaskTags.clear();
			anotherTaskTags.push_back("#free");
			anotherTaskIsDone = false;
			anotherTask = TestSupportLibrary::createTask(
				anotherTaskName, anotherTaskStartTime,
				anotherTaskEndTime, anotherTaskDeadline,
				anotherTaskTags, anotherTaskIsDone);
			initialState.addTask(anotherTask);

			LogicData::fakeinitiate(initialState);
			
			// Creating a command and the expected states to test

			Command* testCommand = new CommandAdd;
			
			anotherTaskName = "Watch some TV";
			anotherTaskStartTime = "20141120T130000";
			anotherTaskEndTime = "20141120T120000";
			anotherTaskDeadline = "not-a-date-time";
			anotherTaskTags.clear();
			anotherTaskTags.push_back("#free");
			anotherTaskIsDone = false;
			anotherTask = TestSupportLibrary::createTask(
				anotherTaskName, anotherTaskStartTime,
				anotherTaskEndTime, anotherTaskDeadline,
				anotherTaskTags, anotherTaskIsDone);
			testCommand->setCurrentTask(anotherTask);

			expectedCurrentState = initialState;
			expectedViewState = expectedCurrentState;
			expectedViewState.setUserMessage(
				"The end time cannot be before the start time!");
			expectedViewState.setActionMessage(
				"  ||  Filtered by: all types / undone");
			expectedCurrentState.setActionMessage("");

			// Obtaining the actual eventual states

			testCommand->execute();
			actualViewState = LogicData::getViewState();
			actualCurrentState = LogicData::getCurrentState();

			// Perform the testing

			TestSupportLibrary::compareStates(
				expectedViewState,actualViewState);
			TestSupportLibrary::compareStates(
				expectedCurrentState,actualCurrentState);
		}

		// This is a test case falling under the "failed add due
		// to incorrectincorrect user input parsed wrongly" partition

		TEST_METHOD(CommandAdd_ParsedStatusFalse)
		{
			// Initiating the LogicData with an initial state
			
			State initialState;
			State expectedCurrentState;
			State expectedViewState;
			State actualCurrentState;
			State actualViewState;

			Task anotherTask;
			string anotherTaskName;
			string anotherTaskStartTime;
			string anotherTaskEndTime;
			string anotherTaskDeadline;
			vector<string> anotherTaskTags;
			bool anotherTaskIsDone;
			
			anotherTaskName = "Finish Tutorial 1";
			anotherTaskStartTime = "20141120T100000";
			anotherTaskEndTime = "20141120T110000";
			anotherTaskDeadline = "not-a-date-time";
			anotherTaskTags.clear();
			anotherTaskTags.push_back("#cs2103");
			anotherTaskTags.push_back("#homework");
			anotherTaskIsDone = false;
			anotherTask = TestSupportLibrary::createTask(
				anotherTaskName, anotherTaskStartTime,
				anotherTaskEndTime, anotherTaskDeadline,
				anotherTaskTags, anotherTaskIsDone);
			initialState.addTask(anotherTask);
			
			anotherTaskName = "Practice Moonlight Sonata";
			anotherTaskStartTime = "not-a-date-time";
			anotherTaskEndTime = "not-a-date-time";
			anotherTaskDeadline = "not-a-date-time";
			anotherTaskTags.clear();
			anotherTaskTags.push_back("#homework");
			anotherTaskTags.push_back("#tutorial");
			anotherTaskIsDone = false;
			anotherTask = TestSupportLibrary::createTask
				(anotherTaskName, anotherTaskStartTime, 
				anotherTaskEndTime, anotherTaskDeadline, 
				anotherTaskTags, anotherTaskIsDone);
			initialState.addTask(anotherTask);

			anotherTaskName = "Surf the web";
			anotherTaskStartTime = "not-a-date-time";
			anotherTaskEndTime = "not-a-date-time";
			anotherTaskDeadline = "20141120T110000";
			anotherTaskTags.clear();
			anotherTaskTags.push_back("#free");
			anotherTaskIsDone = false;
			anotherTask = TestSupportLibrary::createTask(
				anotherTaskName, anotherTaskStartTime, 
				anotherTaskEndTime, anotherTaskDeadline,
				anotherTaskTags, anotherTaskIsDone);
			initialState.addTask(anotherTask);

			LogicData::fakeinitiate(initialState);
			
			// Creating a command and the expected states to test

			Command* testCommand = new CommandAdd;
			
			anotherTaskName = "Watch some TV";
			anotherTaskStartTime = "not-a-date-time";
			anotherTaskEndTime = "not-a-date-time";
			anotherTaskDeadline = "not-a-date-time";
			anotherTaskTags.clear();
			anotherTaskTags.push_back("#free");
			anotherTaskIsDone = true;
			anotherTask = TestSupportLibrary::createTask(
				anotherTaskName, anotherTaskStartTime, 
				anotherTaskEndTime, anotherTaskDeadline,
				anotherTaskTags, anotherTaskIsDone);
			testCommand->setCurrentTask(anotherTask);
			testCommand->setParsedStatus(false);

			expectedCurrentState = initialState;
			expectedViewState = expectedCurrentState;
			expectedViewState.setUserMessage("");
			expectedViewState.setActionMessage(
				"  ||  Filtered by: all types / undone");
			expectedCurrentState.setActionMessage("");

			// Obtaining the actual eventual states

			testCommand->execute();
			actualViewState = LogicData::getViewState();
			actualCurrentState = LogicData::getCurrentState();

			// Perform the testing

			TestSupportLibrary::compareStates(
				expectedViewState,actualViewState);
			TestSupportLibrary::compareStates(
				expectedCurrentState,actualCurrentState);
		}
	};
}