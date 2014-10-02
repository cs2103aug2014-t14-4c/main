#include "CommandEdit.h"


CommandEdit::CommandEdit(void)
{
}

void CommandEdit::execute() {
	LogicData myLogicData;
	_currentState = myLogicData.getCurrentState();
	_isCommandValid = checkIsCommandValid();
	if (_isCommandValid) {
		deleteExistingTask();
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

void CommandEdit::deleteExistingTask() {
	_currentState.deleteTask(_taskIndex);
	return;
}