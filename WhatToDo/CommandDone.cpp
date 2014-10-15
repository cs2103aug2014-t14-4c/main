#include "CommandDone.h"


CommandDone::CommandDone(void)
{
}

void CommandDone::execute() {
	assert(_commandTaskIndex >= 0);
	log("\nCommand Done Initiated:\n");
	checkIsParsedCorrectly();
	
	if (_isParsedCorrectly) {
		retrieveExistingCurrentState();
		performDoneOperation();
		addThisCommandToHistory(this);
		setNewCurrentState();
		setNewViewState();
	}

	addUserMessageToCurrentState();
	return;
}

void CommandDone::performDoneOperation() {
	_currentState->doneTask(_commandTaskIndex);
	log("Function called: performDoneOperation(): _commandTaskIndex marked as done: " + to_string(_commandTaskIndex) + "\n");
	return;
}