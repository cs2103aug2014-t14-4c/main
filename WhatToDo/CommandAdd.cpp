#include "CommandAdd.h"


CommandAdd::CommandAdd(void)
{
}

void CommandAdd::execute() {
	_currentState = LogicData::getCurrentState();
	if (!_parsedStatus) {
		return;
	}
	_isCommandValid = checkIsCommandValid();
	if (_isCommandValid) {
		performAddOperation();
		LogicData::addCommandToHistory(this);
	}
	else {
		addUserMessageToCurrentState();
	}
	LogicData::setCurrentState(_currentState);
	LogicData::setViewState(_currentState);
	return;
}

bool CommandAdd::checkIsCommandValid() {
	bool isEnteredDateTimesValid = checkIfEnteredDateTimesValid();
	bool isOrderOfDateTimesValid = checkIfOrderOfDateTimesValid();
	bool isInputTimeAlreadyOccupied = checkIsInputTimeNotOccupied();
	bool isCommandValid = isEnteredDateTimesValid && isOrderOfDateTimesValid && isInputTimeAlreadyOccupied;
	return isCommandValid;
}

bool CommandAdd::checkIfEnteredDateTimesValid() {
	int currentTaskType = _currentTask.getTaskType();
	bool isStartDateTimeValid = true;
	bool isEndDateTimeValid = true;
	bool isDeadlineDateTimeValid = true;

	if (currentTaskType == 1) {
		bool isStartDateTimeValid = checkIsDateTimeValid(_currentTask.getTaskStartTime());
		bool isEndDateTimeValid = checkIsDateTimeValid(_currentTask.getTaskEndTime());
	}
	else if (currentTaskType == 2) {
		bool isDeadlineDateTimeValid = checkIsDateTimeValid(_currentTask.getTaskDeadline());
	}

	bool isEnteredDateTimesValid = isStartDateTimeValid && isEndDateTimeValid && isDeadlineDateTimeValid;
	return isEnteredDateTimesValid;
}

bool CommandAdd::checkIsDateTimeValid(ptime dateTimeToCheck) {
	bool isDateTimeValid =(dateTimeToCheck != not_a_date_time);
	if (!isDateTimeValid) {
		_userMessage = "Date entered was not valid!";
	}	
	return isDateTimeValid;
}
	
bool CommandAdd::checkIfOrderOfDateTimesValid() {
	int currentTaskType = _currentTask.getTaskType();
	bool isOrderOfDateTimesValid = true;

	if (currentTaskType == 1) {
		bool isStartAfterCurrentTime = checkIsStartAfterCurrentTime();
		bool isEndAfterStart = checkIsEndAfterStart();
		isOrderOfDateTimesValid = isStartAfterCurrentTime && isEndAfterStart;
	}
	else if (currentTaskType == 2) {
		bool isDeadlineAfterCurrentTime = checkIsDeadlineAfterCurrentTime();
		isOrderOfDateTimesValid = isDeadlineAfterCurrentTime;
	}
	
	return isOrderOfDateTimesValid;
}

bool CommandAdd::checkIsDeadlineAfterCurrentTime() {
	bool isStartAfterCurrentTime = second_clock::local_time() <= _currentTask.getTaskDeadline();
	if (!isStartAfterCurrentTime) {
		_userMessage = "The deadline has already passed!";
	}
	return isStartAfterCurrentTime;
}


bool CommandAdd::checkIsStartAfterCurrentTime() {
	bool isStartAfterCurrentTime = second_clock::local_time() <= _currentTask.getTaskStartTime();
	if (!isStartAfterCurrentTime) {
		_userMessage = "The start time has already passed!";
	}
	return isStartAfterCurrentTime;
}

bool CommandAdd::checkIsEndAfterStart() {
	bool isEndAfterStart = _currentTask.getTaskStartTime() <= _currentTask.getTaskEndTime();
	if (!isEndAfterStart) {
		_userMessage = "The end time cannot be before the start time!";
	}
	return isEndAfterStart;
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
		if (_currentTask.isTaskOverlapWith(listOfTimedTasks[i])) {
			isInputTimeNotOccupied = false;
			_userMessage = "There is already a scheduled task at that slot!";
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