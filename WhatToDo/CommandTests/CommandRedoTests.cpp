//****************************************************************************
//@author A0110648L
//
// All unit tests for CommmandRedo are performed here.

#include "stdafx.h"
#include "CppUnitTest.h"
#include "TestSupportLibrary.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommandRedoTests
{		
	TEST_CLASS(CommandRedoTests)
	{
	public:
		
		// This is a test case falling under the "single viable redo"
		// partition

		TEST_METHOD(CommandRedo_OneRedo)
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

			LogicData::resetToInitialSettings();
			LogicData::fakeinitiate(initialState);

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
				anotherTaskEndTime, 	anotherTaskDeadline, 
				anotherTaskTags, anotherTaskIsDone);
			Command* testCommandAdd1 = new CommandAdd;
			testCommandAdd1->setCurrentTask(anotherTask);
			testCommandAdd1->execute();
			expectedCurrentState.addTask(anotherTask);
			expectedViewState.addTask(anotherTask);

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
			Command* testCommandAdd2 = new CommandAdd;
			testCommandAdd2->setCurrentTask(anotherTask);
			testCommandAdd2->execute();
			expectedCurrentState.addTask(anotherTask);
			expectedViewState.addTask(anotherTask);

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
			Command* testCommandAdd3 = new CommandAdd;
			testCommandAdd3->setCurrentTask(anotherTask);
			testCommandAdd3->execute();

			// Creating a command and the expected states to test

			Command* testCommandUndo = new CommandUndo;
			Command* testCommandRedo = new CommandRedo;
			expectedViewState.setActionMessage(
				"Task Added!  ||  Filtered by: all types / undone");
			expectedCurrentState.setActionMessage("Task Added!");

			// Obtaining the actual eventual states

			testCommandUndo->execute();
			testCommandUndo->execute();
			testCommandRedo->execute();
			actualViewState = LogicData::getViewState();
			actualCurrentState = LogicData::getCurrentState();

			// Perform the testing

			TestSupportLibrary::compareStates(
				expectedViewState,actualViewState);
			TestSupportLibrary::compareStates(
				expectedCurrentState,actualCurrentState);
	}

		// This is a test case falling under the "excessive redos
		// till redo is no longer possible" partition

		TEST_METHOD(CommandRedo_ExcessiveRedos)
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
			
			LogicData::resetToInitialSettings();
			LogicData::fakeinitiate(initialState);

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
			expectedCurrentState.addTask(anotherTask);
			expectedViewState.addTask(anotherTask);
			Command* testCommandAdd1 = new CommandAdd;
			testCommandAdd1->setCurrentTask(anotherTask);
			testCommandAdd1->execute();

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
			expectedCurrentState.addTask(anotherTask);
			expectedViewState.addTask(anotherTask);
			Command* testCommandAdd2 = new CommandAdd;
			testCommandAdd2->setCurrentTask(anotherTask);
			testCommandAdd2->execute();

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
			expectedCurrentState.addTask(anotherTask);
			expectedViewState.addTask(anotherTask);
			Command* testCommandAdd3 = new CommandAdd;
			testCommandAdd3->setCurrentTask(anotherTask);
			testCommandAdd3->execute();

			// Creating a command and the expected states to test

			Command* testCommandUndo = new CommandUndo;
			Command* testCommandRedo = new CommandRedo;
			expectedViewState.setUserMessage("Cannot redo anymore!");
			expectedViewState.setActionMessage(
				"  ||  Filtered by: all types / undone");
			expectedCurrentState.setActionMessage("Task Added!");

			// Obtaining the actual eventual states

			testCommandUndo->execute();
			testCommandRedo->execute();
			testCommandRedo->execute();
			testCommandRedo->execute();
			testCommandRedo->execute();

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