#include "CommandEdit.h"


CommandEdit::CommandEdit(void)
{
}

void CommandEdit::execute() {
	log("\nCommand Edit Initiated:\n");
	assert(_currentTask != NULL);
	assert(_commandTaskIndex >= 0);
	
	try {
		checkIsParsedCorrectly();
		retrieveExistingCurrentState();
		checkIsCommandValid();
		deleteExistingTask();
		performAddOperation();
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

void CommandEdit::deleteExistingTask() {
	_currentState->deleteTask(_commandTaskIndex);
	log("Function called: deleteExistingTask(): _commandTaskIndex deleted: " + to_string(_commandTaskIndex) + "\n");
	return;
}