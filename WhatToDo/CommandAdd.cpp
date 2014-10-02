#include "CommandAdd.h"


CommandAdd::CommandAdd(void)
{
}

void CommandAdd::execute() {
	LogicData myLogicData;
	_currentState = myLogicData.getCurrentState();
	_isCommandValid = checkIsCommandValid();
	if (_isCommandValid) {
		performAddOperation();
		myLogicData.addCommandToHistory(*this);
	}
	else {
		addUserMessageToCurrentState();
	}
	myLogicData.setCurrentState(_currentState);
	myLogicData.setViewState(_currentState);
	return;
}

bool CommandAdd::checkIsCommandValid() {
	bool isEnteredDatetimesValid = checkIfEnteredDatetimesValid();
	bool isOrderOfDatetimesValid = checkIfOrderOfDatetimesValid();
	bool isInputTimeAlreadyOccupied = checkIsInputTimeNotOccupied();
	bool isCommandValid = isEnteredDatetimesValid && isOrderOfDatetimesValid && isInputTimeAlreadyOccupied;
	return isCommandValid;
}

bool CommandAdd::checkIfEnteredDatetimesValid() {
	bool isStartDatetimeValid = checkIsDatetimeValid(_currentTask.getTaskStartDatetime());
	bool isEndDatetimeValid = checkIsDatetimeValid(_currentTask.getTaskEndDatetime());
	bool isDeadlineDatetimeValid = checkIsDatetimeValid(_currentTask.getTaskDeadline());
	bool isEnteredDatetimesValid = isStartDatetimeValid && isEndDatetimeValid && isDeadlineDatetimeValid;
	return isEnteredDatetimesValid;
}

bool CommandAdd::checkIsDatetimeValid(ptime datetimeToCheck) {
	bool isDatetimeValid = (ptime(date(0,0,0),hours(0)) != datetimeToCheck);
	if (!isDatetimeValid) {
		_userMessage = "Date entered was not valid!";
	}
	return isDatetimeValid;
}
	
bool CommandAdd::checkIfOrderOfDatetimesValid() {
	int currentTaskType = _currentTask.getTaskType();
	bool isOrderOfDatetimesValid = true;

	if (currentTaskType == 1) {
		bool isStartAfterCurrentTime = checkIsStartAfterCurrentTime();
		bool isEndAfterStart = checkIsEndAfterStart();
		bool isDeadlineAfterEnd = checkIsDeadlineAfterEnd();
		isOrderOfDatetimesValid = isStartAfterCurrentTime && isEndAfterStart && isDeadlineAfterEnd;
	}
	else if (currentTaskType == 2) {
		bool isDeadlineAfterCurrentTime = checkIsDeadlineAfterCurrentTime();
		isOrderOfDatetimesValid = isDeadlineAfterCurrentTime;
	}
	
	return isOrderOfDatetimesValid;
}

bool CommandAdd::checkIsDeadlineAfterCurrentTime() {
	bool isStartAfterCurrentTime = second_clock::local_time() <= _currentTask.getTaskDeadline();
	if (!isStartAfterCurrentTime) {
		_userMessage = "The deadline has already passed!";
	}
	return isStartAfterCurrentTime;
}


bool CommandAdd::checkIsStartAfterCurrentTime() {
	bool isStartAfterCurrentTime = second_clock::local_time() <= _currentTask.getTaskStartDatetime();
	if (!isStartAfterCurrentTime) {
		_userMessage = "The start time has already passed!";
	}
	return isStartAfterCurrentTime;
}

bool CommandAdd::checkIsEndAfterStart() {
	bool isEndAfterStart = _currentTask.getTaskStartDatetime() <= _currentTask.getTaskEndDatetime();
	if (!isEndAfterStart) {
		_userMessage = "The end time cannot be before the start time!";
	}
	return isEndAfterStart;
}

bool CommandAdd::checkIsDeadlineAfterEnd() {
	bool isDeadlineAfterEnd = _currentTask.getTaskEndDatetime() <= _currentTask.getTaskDeadline();
	if (!isDeadlineAfterEnd) {
		_userMessage = "The deadline cannot be before the end time!";
	}
	return isDeadlineAfterEnd;
}

bool CommandAdd::checkIsInputTimeNotOccupied() {
	vector<Task> listOfTimedTasks = _currentState.getTimedTasks();
	int currentTaskType = _currentTask.getTaskType();
	bool isInputTimeNotOccupied = true;
	int i;

	if (currentTaskType != 1) {
		return isInputTimeNotOccupied;
	}

	for (i=0; unsigned(i)<listOfTimedTasks.size(); i++) {
		if (_currentTask.isOverlapWith(listOfTimedTasks[i])) {
			isInputTimeNotOccupied = false;
			break;
		}
	}

	return isInputTimeNotOccupied;
}

void CommandAdd::performAddOperation() {
	_currentState.addTask(_currentTask);
	return;
}

void CommandAdd::addUserMessageToCurrentState() {
	_currentState.setUserMessage(_userMessage);
	return;
}