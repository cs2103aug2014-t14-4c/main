#include "CommandDelete.h"


CommandDelete::CommandDelete(void)
{
}

void CommandDelete::execute() {
	assert(_commandTaskIndex >= 0);
	log("\nCommand Delete Initiated:\n");
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
	log("Function called: performDeleteOperation(): _commandTaskIndex deleted: " + to_string(_commandTaskIndex) + "\n");
	return;
}