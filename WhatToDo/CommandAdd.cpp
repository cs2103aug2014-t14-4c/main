#include "CommandAdd.h"

// These are the static variables that cannot be initialized in header file

string CommandAdd::LOGGING_MSG_EXECUTE_COMMAND_ADD = "\nCommand Add Initiated:\n";
string CommandAdd::LOGGING_MSG_IS_ORDER_DATETIMES_VALD = "Function called: checkIsCommandValid(): isOrderOfDateTimesValid: %s\n";
string CommandAdd::LOGGING_MSG_IS_INPUT_TIME_ALR_OCCUPIED = "Function called: checkIsCommandValid(): isInputTimeAlreadyOccupied: %s\n";
string CommandAdd::LOGGING_MSG_IS_COMMAND_VALID = "Function called: checkIsCommandValid(): _isCommandValid: %s\n";
string CommandAdd::LOGGING_MSG_PERFORM_ADD = "Function called: performAddOperation()\n";

string CommandAdd::ERROR_MSG_ENDTIME_BEFORE_STARTTIME = "The end time cannot be before the start time!";
string CommandAdd::USER_MSG_INPUT_TIME_OCCUPIED = "Task Added! Note: Beware task overlap!";
string CommandAdd::ACTION_MSG_ADDED = "Task Added!";

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
		addUserMessageToCurrentState();
		addActionMessageToCurrentState();
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

	if (currentTaskType == Task::FIXED_TIME) {
		bool isEndAfterStart = checkIsEndAfterStart();
		isOrderOfDateTimesValid = isEndAfterStart;
	}
	return isOrderOfDateTimesValid;
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

	for (i=0; unsigned(i)<listOfTimedTasks.size(); i++) {
		if ((_currentTask->getTaskType() == Task::FIXED_TIME) && (listOfTimedTasks[i].getTaskType() == Task::FIXED_TIME) && (listOfTimedTasks[i].getTaskIsDone() == false)) {
			if (_currentTask->isTaskOverlapWith(listOfTimedTasks[i])) {
				isInputTimeNotOccupied = false;
				_userMessage = USER_MSG_INPUT_TIME_OCCUPIED;
				break;
			}
		}
	}

	return isInputTimeNotOccupied;
}

void CommandAdd::performAddOperation() {
	_currentState->addTask(*_currentTask, true);
	_actionMessage = ACTION_MSG_ADDED;
	sprintf_s(buffer, LOGGING_MSG_PERFORM_ADD.c_str());
	log(buffer);
	return;
}
