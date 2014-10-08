#include "CommandEdit.h"


CommandEdit::CommandEdit(void)
{
}

void CommandEdit::execute() {
	if (!_parsedStatus) {
		return;
	}
	_currentState = LogicData::getCurrentState();
	if (!_parsedStatus) {
		return;
	}
	_isCommandValid = checkIsCommandValid();
	if (_isCommandValid) {
		deleteExistingTask();
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

void CommandEdit::deleteExistingTask() {
	_currentState.deleteTask(_taskIndex);
	return;
}