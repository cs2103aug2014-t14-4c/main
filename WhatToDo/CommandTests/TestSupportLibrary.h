//****************************************************************************
//@author A0110648L
//
// This is the Test Support Library created for Command Unit Tests.
//
// It comprises of functions that allow the automation of Command Unit Tests
// to be carried out more efficiently.
//
//****************************************************************************

#pragma once
#include "stdafx.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

class TestSupportLibrary {
public:
	TestSupportLibrary(void);
	~TestSupportLibrary(void);
	
	// This function allows for a task to be created with all its 
	// attributes initialized according to specified parameters all at 
	// once, as opposed to setting each attribute individually after
	// creating the task.

	static Task createTask(string taskName, string taskStart, 
		string taskEnd, string taskDeadline, vector<string> taskTags, 
		bool isDone);

	// This function allows for two states to be compared. All data
	// attributes for all tasks and state from the first state will be
	// asserted to be equals to to the second state.

	static void compareStates(State firstState, State secondState);

	static void compareTasks(Task firstTask, Task secondTask);
	static void compareTaskTags(vector<string> firstTaskTags, 
		vector<string> secondTaskTags);
	
};

