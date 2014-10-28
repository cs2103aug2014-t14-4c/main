#include "CommandAdd.h"

// These are the static variables that cannot be initialized in header file

string CommandAdd::LOGGING_MSG_EXECUTE_COMMAND_ADD = "\nCommand Add Initiated:\n";
string CommandAdd::LOGGING_MSG_IS_ORDER_DATETIMES_VALD = "Function called: checkIsCommandValid(): isOrderOfDateTimesValid: %s\n";
string CommandAdd::LOGGING_MSG_IS_INPUT_TIME_ALR_OCCUPIED = "Function called: checkIsCommandValid(): isInputTimeAlreadyOccupied: %s\n";
string CommandAdd::LOGGING_MSG_IS_COMMAND_VALID = "Function called: checkIsCommandValid(): _isCommandValid: %s\n";
string CommandAdd::LOGGING_MSG_PERFORM_ADD = "Function called: performAddOperation(): name of Task added: %s\n";

string CommandAdd::ERROR_MSG_DATETIME_INVALID = "Date entered was not valid!";
string CommandAdd::ERROR_MSG_DEADLINE_PASSED = "The deadline has already passed!";
string CommandAdd::ERROR_MSG_STARTTIME_PASSED = "The start time has already passed!";
string CommandAdd::ERROR_MSG_ENDTIME_BEFORE_STARTTIME = "The end time cannot be before the start time!";
string CommandAdd::ERROR_MSG_INPUT_TIME_OCCUPIED = "There is already a scheduled task at that slot!";


CommandAdd::CommandAdd(void)
{
}

void CommandAdd::execute() {
	sprintf_s(buffer, LOGGING_MSG_EXECUTE_COMMAND_ADD.c_str());
	log(buffer);
	
	try {
		checkIsParsedCorrectly();
		assert(_currentTask != NULL);
		retrieveExistingCurrentState();
		checkIsCommandValid();
		performAddOperation();
		addThisCommandToHistory(this);
		setNewCurrentState();
		setNewViewState();
	}
	catch (string errorMsg) {
		_userMessage = errorMsg;
		retrieveExistingViewState();
		addUserMessageToCurrentState();
		setNewViewState();
	}

	return;
}

bool CommandAdd::checkIsCommandValid() {
	bool isOrderOfDateTimesValid = checkIfOrderOfDateTimesValid();
	bool isInputTimeAlreadyOccupied = checkIsInputTimeNotOccupied();
	bool isCommandValid = isOrderOfDateTimesValid && isInputTimeAlreadyOccupied;
	_isCommandValid = isCommandValid;
	
	sprintf_s(buffer, LOGGING_MSG_IS_ORDER_DATETIMES_VALD.c_str(), to_string(isOrderOfDateTimesValid).c_str());
	log(buffer);
	sprintf_s(buffer, LOGGING_MSG_IS_INPUT_TIME_ALR_OCCUPIED.c_str(), to_string(isInputTimeAlreadyOccupied).c_str());
	log(buffer);
	sprintf_s(buffer, LOGGING_MSG_IS_COMMAND_VALID.c_str(), to_string(_isCommandValid).c_str());
	log(buffer);
	
	return isCommandValid;
}

bool CommandAdd::checkIfOrderOfDateTimesValid() {
	int currentTaskType = _currentTask->getTaskType();
	bool isOrderOfDateTimesValid = true;

	if (currentTaskType == Task::FIXEDTIME) {
		bool isStartAfterCurrentTime = checkIsStartAfterCurrentTime();
		bool isEndAfterStart = checkIsEndAfterStart();
		isOrderOfDateTimesValid = isStartAfterCurrentTime && isEndAfterStart;
	}
	else if (currentTaskType == Task::DEADLINE) {
		bool isDeadlineAfterCurrentTime = checkIsDeadlineAfterCurrentTime();
		isOrderOfDateTimesValid = isDeadlineAfterCurrentTime;
	}
	
	return isOrderOfDateTimesValid;
}

bool CommandAdd::checkIsDeadlineAfterCurrentTime() {
	bool isStartAfterCurrentTime = second_clock::local_time() <= _currentTask->getTaskDeadline();
	if (!isStartAfterCurrentTime) {
		throw ERROR_MSG_DEADLINE_PASSED;
	}
	return isStartAfterCurrentTime;
}

bool CommandAdd::checkIsStartAfterCurrentTime() {
	bool isStartAfterCurrentTime = second_clock::local_time() <= _currentTask->getTaskStartTime();
	if (!isStartAfterCurrentTime) {
		throw ERROR_MSG_STARTTIME_PASSED;
	}
	return isStartAfterCurrentTime;
}

bool CommandAdd::checkIsEndAfterStart() {
	bool isEndAfterStart = _currentTask->getTaskStartTime() <= _currentTask->getTaskEndTime();
	if (!isEndAfterStart) {
		throw ERROR_MSG_ENDTIME_BEFORE_STARTTIME;
	}
	return isEndAfterStart;
}

bool CommandAdd::checkIsInputTimeNotOccupied() {
	vector<Task> listOfTimedTasks = _currentState->getTimedTasks();
	int currentTaskType = _currentTask->getTaskType();
	bool isInputTimeNotOccupied = true;
	int i;

	if (currentTaskType != Task::FIXEDTIME) {
		return isInputTimeNotOccupied;
	}

	for (i=0; unsigned(i)<listOfTimedTasks.size(); i++) {
		if (_currentTask->isTaskOverlapWith(listOfTimedTasks[i])) {
			isInputTimeNotOccupied = false;
			throw ERROR_MSG_INPUT_TIME_OCCUPIED;
			break;
		}
	}

	return isInputTimeNotOccupied;
}

void CommandAdd::performAddOperation() {
	_currentState->addTask(*_currentTask);
	sprintf_s(buffer, LOGGING_MSG_PERFORM_ADD.c_str(), _currentTask->getTaskName().c_str());
	log(buffer);
	return;
}
