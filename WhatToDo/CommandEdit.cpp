#include "CommandEdit.h"


CommandEdit::CommandEdit(void)
{
}

void CommandEdit::execute() {
	retrieveExistingCurrentState();
	checkIsParsedCorrectly();
	checkIsCommandValid();
	
	if (_isParsedCorrectly && _isCommandValid) {
		deleteExistingTask();
		performAddOperation();
		addThisCommandToHistory(this);
		setNewCurrentState();
		setNewViewState();
	}

	addUserMessageToCurrentState();
	return;
}

void CommandEdit::deleteExistingTask() {
	_currentState->deleteTask(_commandTaskIndex);
	return;
}