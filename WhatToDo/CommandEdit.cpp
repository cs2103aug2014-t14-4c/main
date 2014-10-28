#include "CommandEdit.h"

// These are the static variables that cannot be initialized in header file

string CommandEdit::LOGGING_MSG_EXECUTE_COMMAND_EDIT = "\nCommand Edit Initiated:\n";
string CommandEdit::LOGGING_MSG_DELETE_EXISTING_TASK = "Function called: deleteExistingTask(): _commandTaskIndex deleted: %s\n";


CommandEdit::CommandEdit(void) {
}

void CommandEdit::execute() {
	sprintf_s(buffer, LOGGING_MSG_EXECUTE_COMMAND_EDIT.c_str());
	log(buffer);
	
	try {
		checkIsParsedCorrectly();
		assert(_currentTask != NULL);
		assert(_commandTaskIndex >= 0);
		retrieveExistingCurrentState();
		checkIsCommandValid();
		deleteExistingTask();
		performAddOperation();
		addThisCommandToHistory(this);
		setNewCurrentState();
		setNewViewState();
	}
	catch (string errorMsg) {
		_userMessage = errorMsg;
		retrieveExistingViewState();
		addUserMessageToCurrentState();
		setNewViewState();
	}

	return;
}

void CommandEdit::deleteExistingTask() {
	_currentState->deleteTask(_commandTaskIndex);
	sprintf_s(buffer, LOGGING_MSG_DELETE_EXISTING_TASK.c_str(), to_string(_commandTaskIndex).c_str());
	log(buffer);
	return;
}