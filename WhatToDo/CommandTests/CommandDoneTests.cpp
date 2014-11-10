//****************************************************************************
//@author A0110648L
//
// All unit tests for CommmandDone are performed here.

#include "stdafx.h"
#include "CppUnitTest.h"
#include "TestSupportLibrary.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommandDoneTests
{		
	TEST_CLASS(CommandDoneTests)
	{
	public:

		// This is a test case falling under the "normal 
		// done process" partition

		TEST_METHOD(CommandDone_NormalDone)
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
			expectedViewState.addTask(anotherTask);
			expectedCurrentState.addTask(anotherTask);

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
			expectedViewState.addTask(anotherTask);
			expectedCurrentState.addTask(anotherTask);

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
			LogicData::setDoneFilter(0);
			
			// Creating a command and the expected states to test
			
			anotherTaskName = "Surf the web";
			anotherTaskStartTime = "not-a-date-time";
			anotherTaskEndTime = "not-a-date-time";
			anotherTaskDeadline = "20141120T110000";
			anotherTaskTags.clear();
			anotherTaskTags.push_back("#free");
			anotherTaskIsDone = true;
			anotherTask = TestSupportLibrary::createTask(
				anotherTaskName, anotherTaskStartTime, 
				anotherTaskEndTime, anotherTaskDeadline,
				anotherTaskTags, anotherTaskIsDone);
			expectedViewState.addTask(anotherTask);
			expectedCurrentState.addTask(anotherTask);

			Command* testCommandDone = new CommandDone;
			int index = 2;
			testCommandDone->setTaskIndex(index);
			testCommandDone->setIsDoneStatus(true);

			expectedViewState.setActionMessage(
				"Task marked as Done!  ||  Filtered by: all types");
			expectedCurrentState.setActionMessage("Task marked as Done!");

			// Obtaining the actual eventual states

			testCommandDone->execute();
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