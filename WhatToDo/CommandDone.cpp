#include "CommandDone.h"


CommandDone::CommandDone(void)
{
}

void CommandDone::execute() {
	log("\nCommand Done Initiated:\n");
	assert(_commandTaskIndex >= 0);
	
	try {
		checkIsParsedCorrectly();
		retrieveExistingCurrentState();
		performDoneOperation();
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

void CommandDone::performDoneOperation() {
	_currentState->doneTask(_commandTaskIndex);
	log("Function called: performDoneOperation(): _commandTaskIndex marked as done: " + to_string(_commandTaskIndex) + "\n");
	return;
}