#include "CommandEdit.h"


CommandEdit::CommandEdit(void)
{
}

void CommandEdit::execute() {
	_currentState = LogicData::getCurrentState();
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