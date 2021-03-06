//****************************************************************************
//@author A0110648L
//
// All unit tests for CommmandEdit are performed here.

#include "stdafx.h"
#include "CppUnitTest.h"
#include "TestSupportLibrary.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommandEditTests
{		
	TEST_CLASS(CommandEditTests)
	{
	public:

		// This is a test case falling under the "normal 
		// edit process" partition

		TEST_METHOD(CommandEdit_NormalSuccessfulEdit)
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
			
			// Creating a command and the expected states to test

			anotherTaskName = "Surf the web along along";
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
			expectedViewState.addTask(anotherTask);
			expectedCurrentState.addTask(anotherTask);

			Command* testCommandEdit = new CommandEdit;
			int index = 2;
			testCommandEdit->setTaskIndex(index);
			testCommandEdit->setCurrentTask(anotherTask);

			expectedViewState.setActionMessage(
				"Task Edited!  ||  Filtered by: all types / undone");
			expectedCurrentState.setActionMessage("Task Edited!");

			// Obtaining the actual eventual states

			testCommandEdit->execute();
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