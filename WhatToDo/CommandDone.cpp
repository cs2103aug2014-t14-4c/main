#include "CommandDone.h"


CommandDone::CommandDone(void)
{
}

void CommandDone::execute() {
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
	_currentState.doneTask(_commandTaskIndex);
	return;
}