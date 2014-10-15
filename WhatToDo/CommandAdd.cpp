#include "CommandAdd.h"


CommandAdd::CommandAdd(void)
{
}

void CommandAdd::execute() {
	assert(_currentTask != NULL);
	log("\nCommand Add Initiated:\n");
	retrieveExistingCurrentState();
	checkIsParsedCorrectly();
	checkIsCommandValid();
	
	if (_isParsedCorrectly && _isCommandValid) {
		performAddOperation();
		addThisCommandToHistory(this);
		setNewCurrentState();
		setNewViewState();
	}

	addUserMessageToCurrentState();
	return;
}

bool CommandAdd::checkIsCommandValid() {
	bool isEnteredDateTimesValid = checkIfEnteredDateTimesValid();
	bool isOrderOfDateTimesValid = checkIfOrderOfDateTimesValid();
	bool isInputTimeAlreadyOccupied = checkIsInputTimeNotOccupied();
	bool isCommandValid = isEnteredDateTimesValid && isOrderOfDateTimesValid && isInputTimeAlreadyOccupied;
	_isCommandValid = isCommandValid;
	log("Function called: checkIsCommandValid(): isEnteredDateTimesValid: " + to_string(isEnteredDateTimesValid) + "\n");
	log("Function called: checkIsCommandValid(): isOrderOfDateTimesValid: " + to_string(isOrderOfDateTimesValid) + "\n");
	log("Function called: checkIsCommandValid(): isInputTimeAlreadyOccupied: " + to_string(isInputTimeAlreadyOccupied) + "\n");
	log("Function called: checkIsCommandValid(): _isCommandValid: " + to_string(_isCommandValid) + "\n");
	return isCommandValid;
}

bool CommandAdd::checkIfEnteredDateTimesValid() {
	int currentTaskType = _currentTask->getTaskType();
	bool isStartDateTimeValid = true;
	bool isEndDateTimeValid = true;
	bool isDeadlineDateTimeValid = true;

	if (currentTaskType == Task::FIXEDTIME) {
		isStartDateTimeValid = checkIsDateTimeValid(_currentTask->getTaskStartTime());
		isEndDateTimeValid = checkIsDateTimeValid(_currentTask->getTaskEndTime());
	}
	else if (currentTaskType == Task::DEADLINE) {
		isDeadlineDateTimeValid = checkIsDateTimeValid(_currentTask->getTaskDeadline());
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
		_userMessage = "The deadline has already passed!";
	}
	return isStartAfterCurrentTime;
}


bool CommandAdd::checkIsStartAfterCurrentTime() {
	bool isStartAfterCurrentTime = second_clock::local_time() <= _currentTask->getTaskStartTime();
	if (!isStartAfterCurrentTime) {
		_userMessage = "The start time has already passed!";
	}
	return isStartAfterCurrentTime;
}

bool CommandAdd::checkIsEndAfterStart() {
	bool isEndAfterStart = _currentTask->getTaskStartTime() <= _currentTask->getTaskEndTime();
	if (!isEndAfterStart) {
		_userMessage = "The end time cannot be before the start time!";
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
			_userMessage = "There is already a scheduled task at that slot!";
			break;
		}
	}

	return isInputTimeNotOccupied;
}

void CommandAdd::performAddOperation() {
	_currentState->addTask(*_currentTask);
	log("Function called: performAddOperation(): name of Task added: " + _currentTask->getTaskName() + "\n");
	return;
}
