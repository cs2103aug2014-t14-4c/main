//****************************************************************************
//@author A0110648L
//
// This is the Test Support Library created for WhatToDo's System Tests.
//
// It comprises of functions that allow the automation of WhatToDo's System 
// Tests to be carried out more efficiently.
//
//****************************************************************************

#pragma once
#include "stdafx.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

const string INPUT_COMMAND_FILE_EXT = "_in.txt";
const string EXPECTED_STATE_FILE_EXT = "_out.txt";
const string STORAGE_FILE_NAME = "Database.txt";
const string COMMAND_PARAM_LOAD = "/load";
const string NOT_A_DATE_TIME = "not-a-date-time";

class TestSupportLibrary
{
public:
	TestSupportLibrary(void);
	~TestSupportLibrary(void);

	// This function overwrites the database file for loading with the
	// specified input file to simulate loading for a subsequent system
	// test.

	static void writeInputDatabaseToDatabase(string inputFileName);

	// This function empties the database file for loading for a subsequent
	// system test.

	static void loadProgramFromEmptyFile();

	// This function executes all commands from a specified input file.

	static State executeCommandsFromInputFile(string inputFileName);

	// This function checks if a specified state (stateToTest) is equals 
	// to the expected state as specified in the expected output file 
	// (expectedStateFileName).

	static bool checkIsStateEqualsExpected(State stateToTest, 
										   string expectedStateFileName);

	// These following functions checks if a Task ad its attributes are
	// equal to the expected attributes as specified in the output file
	// written for the system test.

	static bool checkIsTaskEqualsExpected(Task taskToTest, 
										  ifstream& expectedInputFile);
	static bool checkIsTaskNameEqualsExpected(string taskNameToTest, 
											  ifstream& expectedInputFile);
	static bool checkIsDateTimeEqualsExpected(ptime dateTimeToTest, 
											  ifstream& expectedInputFile);
	static bool checkIsTaskTagsEqualsExpected(vector<string> taskTagsToTest, 
											  ifstream& expectedInputFile);
	static bool checkIsTaskIsDoneEqualsExpected(bool taskIsDoneStatus, 
											    ifstream& expectedInputFile);

};

