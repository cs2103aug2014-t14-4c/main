//****************************************************************************
//@author A0110648L

#include "CommandAdd.h"

CommandAdd::CommandAdd(void)
{
}

void CommandAdd::execute() {
	sprintf_s(buffer, MSG_LOGGING_EXECUTE_COMMAND_ADD.c_str());
	log(buffer);
	
	try {
		checkIsParsedCorrectly();
		assert(_currentTask != NULL);

		retrieveExistingCurrentState();

		checkIsCommandValid();
		checkIsInputTimeNotOccupied();
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
		_currentState->setActionMessage(STRING_EMPTY);
		setNewViewState();
	}

	return;
}

bool CommandAdd::checkIsCommandValid() {
	bool isOrderOfDateTimesValid = checkIfOrderOfDateTimesValid();
	bool isCommandValid = isOrderOfDateTimesValid;
	_isCommandValid = isCommandValid;
	return isCommandValid;
}

bool CommandAdd::checkIfOrderOfDateTimesValid() {
	bool isOrderOfDateTimesValid = true;

	if (_currentTask->isTaskHasStartAndEnd()) {
		bool isEndAfterStart = checkIsEndAfterStart();
		isOrderOfDateTimesValid = isEndAfterStart;
	}

	sprintf_s(buffer, MSG_LOGGING_IS_ORDER_DATETIMES_VALD.c_str(), 
		to_string(isOrderOfDateTimesValid).c_str());
	log(buffer);

	return isOrderOfDateTimesValid;
}

bool CommandAdd::checkIsEndAfterStart() {
	bool isEndAfterStart = 
		_currentTask->getTaskStartTime() <= 
		_currentTask->getTaskEndTime();

	if (!isEndAfterStart) {
		throw MSG_ERROR_ENDTIME_BEFORE_STARTTIME;
	}
	return isEndAfterStart;
}

bool CommandAdd::checkIsInputTimeNotOccupied() {
	vector<Task> listOfTimedTasks = _currentState->getTimedTasks();
	int currentTaskType = _currentTask->getTaskType();
	bool isInputTimeNotOccupied = true;
	int i;

	for (i=0; unsigned(i)<listOfTimedTasks.size(); i++) {
		if ((_currentTask->isTaskHasStartAndEnd()) 
			&& (listOfTimedTasks[i].isTaskHasStartAndEnd()) 
			&& (listOfTimedTasks[i].getTaskIsDone() == false)) {

			if (_currentTask->isTaskOverlapWith(listOfTimedTasks[i])) {
				isInputTimeNotOccupied = false;
				_userMessage = MSG_USER_INPUT_TIME_OCCUPIED;
				break;
			}
		}
	}
	
	sprintf_s(buffer, MSG_LOGGING_IS_INPUT_TIME_ALR_OCCUPIED.c_str(), 
		to_string(isInputTimeNotOccupied).c_str());
	log(buffer);

	return isInputTimeNotOccupied;
}

void CommandAdd::performAddOperation() {
	_currentState->addTask(*_currentTask, true);
	_actionMessage = MSG_ACTION_ADDED;

	sprintf_s(buffer, MSG_LOGGING_PERFORM_ADD.c_str());
	log(buffer);
	return;
}
