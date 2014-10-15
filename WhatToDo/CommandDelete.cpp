#include "CommandDelete.h"


CommandDelete::CommandDelete(void)
{
}

void CommandDelete::execute() {
	log("\nCommand Delete Initiated:\n");
	assert(_commandTaskIndex >= 0);
	
	try {
		checkIsParsedCorrectly();
		retrieveExistingCurrentState();
		performDeleteOperation();
		addThisCommandToHistory(this);
		setNewCurrentState();
		setNewViewState();
	}
	catch (string errorMsg) {
		retrieveExistingViewState();
		addUserMessageToCurrentState();
		setNewViewState();
	}
	
	return;
}

void CommandDelete::performDeleteOperation() {
	_currentState->deleteTask(_commandTaskIndex);
	log("Function called: performDeleteOperation(): _commandTaskIndex deleted: " + to_string(_commandTaskIndex) + "\n");
	return;
}