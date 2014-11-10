//****************************************************************************
//@author A0110648L

#include "TestSupportLibrary.h"


TestSupportLibrary::TestSupportLibrary(void) {
}

TestSupportLibrary::~TestSupportLibrary(void) {
}


void TestSupportLibrary::writeInputDatabaseToDatabase(string inputFileName) {
	ifstream inputFile;
	ofstream outputFile;
	string inputLine;

	inputFile.open(inputFileName);
	outputFile.open(STORAGE_FILE_NAME, ios::out);

	// Copy contents of input database to the database to be loaded during
	// the system test

	while (getline(inputFile, inputLine)) {
		outputFile << inputLine << endl;
	}

	inputFile.close();
	outputFile.close();
	return;
}

void TestSupportLibrary::loadProgramFromEmptyFile() {
	ofstream outputFile;

	// Remove contents of the database to be loaded during
	// the system test

	outputFile.open(STORAGE_FILE_NAME, ios::out);
	outputFile.close();
	LogicExecutor::getNewState(COMMAND_PARAM_LOAD);
	return;
}

State TestSupportLibrary::executeCommandsFromInputFile(string inputFileName) {
	ifstream inputFile;
	inputFile.open(inputFileName);
	string testUserCommand;
	State stateToReturn;

	loadProgramFromEmptyFile();

	// Execute all lines in the input file for the system test.

	while (getline(inputFile, testUserCommand)) {
		stateToReturn = LogicExecutor::getNewState(testUserCommand);
	}

	inputFile.close();
	return stateToReturn;
}

bool TestSupportLibrary::checkIsStateEqualsExpected(
		State stateToTest, 
		string expectedStateFileName) {

	bool isStateEqualsExpected = true;
	Task currentTask;
	ifstream expectedInput;
	string emptyLine;
	string expectedActionMessage;
	string expectedUserMessage;
	int expectedLastActionType;
	int expectedLastActionTaskIndex;
	vector<Task> listOfTasks = stateToTest.getAllTasks();
	int i;
	
	expectedInput.open(expectedStateFileName);

	for (i=0; unsigned(i)<listOfTasks.size(); i++) {
		
		// Check if each task in the stateToTest is equals to the
		// expected output specified in the output file.
		
		currentTask = listOfTasks[i];
		 checkIsTaskEqualsExpected(currentTask, expectedInput);
		 getline(expectedInput, emptyLine);
		 getline(expectedInput, emptyLine);
	}

	// Check if the action and user messages in the stateToTest 
	// are equal to the expected messages in the output file.

	getline(expectedInput, expectedActionMessage);
	getline(expectedInput, expectedUserMessage);
	Assert::AreEqual(expectedActionMessage, stateToTest.getActionMessage());
	Assert::AreEqual(expectedUserMessage, stateToTest.getUserMessage());
	
	// Check if the lastActionType and the lastActionTaskIndex in the 
	// stateToTest are equal to the expected messages in the output file.

	expectedInput >> expectedLastActionType;
	expectedInput >> expectedLastActionTaskIndex;
	if (expectedLastActionType == State::NONE) {
		Assert::AreEqual(expectedLastActionType, 
			stateToTest.getLastActionType());
	}
	else {
		Assert::AreEqual(expectedLastActionTaskIndex, 
			stateToTest.getLastActionTaskIndex());
	}

	expectedInput.close();
	return isStateEqualsExpected;
}

bool TestSupportLibrary::checkIsTaskEqualsExpected(
	Task taskToTest, 
	ifstream& expectedInputFile) {

	bool isTaskEqualsExpected = true;

	string expectedTaskName;
	getline(expectedInputFile, expectedTaskName);
	Assert::AreEqual(expectedTaskName, taskToTest.getTaskName());
	
	isTaskEqualsExpected = 
		checkIsDateTimeEqualsExpected(taskToTest.getTaskStartTime(), expectedInputFile)
		&& checkIsDateTimeEqualsExpected(taskToTest.getTaskEndTime(), expectedInputFile)
		&& checkIsDateTimeEqualsExpected(taskToTest.getTaskDeadline(), expectedInputFile)
		&& checkIsTaskTagsEqualsExpected(taskToTest.getTaskTags(), expectedInputFile)
		&& checkIsTaskIsDoneEqualsExpected(taskToTest.getTaskIsDone(), expectedInputFile);

	return isTaskEqualsExpected;
}

bool checkIsTaskNameEqualsExpected(
	string taskNameToTest, 
	ifstream& expectedInputFile) {

	bool isTaskNameEqualsExpected = true;
	string expectedTaskName;

	getline(expectedInputFile, expectedTaskName);
	Assert::AreEqual(expectedTaskName, taskNameToTest);

	return isTaskNameEqualsExpected;
}

bool TestSupportLibrary::checkIsDateTimeEqualsExpected(
	ptime dateTimeToTest, 
	ifstream& expectedInputFile) {

	bool isDateTimeEqualsExpected = true;
	string expectedDateTime;

	expectedInputFile >> expectedDateTime;
	if (expectedDateTime == NOT_A_DATE_TIME) {
		Assert::AreEqual(true, dateTimeToTest == not_a_date_time);
	}
	else {
		Assert::AreEqual(expectedDateTime, to_iso_string(dateTimeToTest));
	}

	return isDateTimeEqualsExpected;
}

bool TestSupportLibrary::checkIsTaskTagsEqualsExpected(
	vector<string> taskTagsToTest, 
	ifstream& expectedInputFile) {

	bool isTaskTagsEqualsExpected = true;
	string expectedTag;
	string emptyString;
	int expectedNoOfTags;
	int i;

	expectedInputFile >> expectedNoOfTags;
	getline(expectedInputFile, emptyString);

	Assert::AreEqual(unsigned(expectedNoOfTags), taskTagsToTest.size());

	for (i=0; i<expectedNoOfTags; i++) {
		getline(expectedInputFile, expectedTag);
		Assert::AreEqual(expectedTag, taskTagsToTest[i]);
	}

	return isTaskTagsEqualsExpected;
}

bool TestSupportLibrary::checkIsTaskIsDoneEqualsExpected(
	bool taskIsDoneStatus, 
	ifstream& expectedInputFile) {

	bool isTaskIsDoneEqualsExpected = true;
	bool expectedIsDoneStatus;
	
	expectedInputFile >> expectedIsDoneStatus;
	Assert::AreEqual(expectedIsDoneStatus, taskIsDoneStatus);

	return isTaskIsDoneEqualsExpected;
}