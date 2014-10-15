#include "CommandDelete.h"


CommandDelete::CommandDelete(void)
{
}

void CommandDelete::execute() {
	checkIsParsedCorrectly();
	
	if (_isParsedCorrectly) {
		retrieveExistingCurrentState();
		performDeleteOperation();
		addThisCommandToHistory(this);
		setNewCurrentState();
		setNewViewState();
	}

	addUserMessageToCurrentState();
	return;
}

void CommandDelete::performDeleteOperation() {
	_currentState->deleteTask(_commandTaskIndex);
	return;
}