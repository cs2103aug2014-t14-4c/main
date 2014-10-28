#include "CommandUndo.h"

// These are the static variables that cannot be initialized in header file

string CommandUndo::LOGGING_MSG_EXECUTE_COMMAND_UNDO = "\nCommand Add Initiated:\n";
string CommandUndo::LOGGING_MSG_RUN_RELEVANT_COMMANDS_AGAIN = "Function called: runAllRelevantCommandsAgain(): _currentCommandHistoryIndex: %s\n";
string CommandUndo::LOGGING_MSG_STORE_REMAINING_COMMANDS = "Function called: storeRemainingCommandsInHistory(): size of _commandHistory: %s\nFunction called: storeRemainingCommandsInHistory(): _currentCommandHistoryIndex: %s\n";
string CommandUndo::LOGGING_MSG_CHECK_IS_COMMAND_VALID = "Function called: checkIsCommandValid(): updated _currentCommandHistoryIndex: %s\nFunction called: checkIsCommandValid(): isUndoPossible: %s\n";
string CommandUndo::LOGGING_MSG_RETRIEVE_COMMAND_HISTORY = "Function called: retrieveCommandHistory(): size of CommandHistory: %s\n";
string CommandUndo::LOGGING_MSG_RETRIEVE_COMMAND_HISTORY_INDEX = "Function called: retrieveCommandHistoryIndex(): _currentCommandHistoryIndex: %s\n";

string CommandUndo::ERROR_MSG_CANNOT_UNDO_ANYMORE = "Cannot undo anymore!";


CommandUndo::CommandUndo(void) {
}

void CommandUndo::execute() {
	sprintf_s(buffer, LOGGING_MSG_EXECUTE_COMMAND_UNDO.c_str());
	log(buffer);
	retrieveCommandHistory();
	retrieveCommandHistoryIndex();
	
	try {
		checkIsParsedCorrectly();
		assert(_currentCommandHistoryIndex >= 0);
		assert(_currentCommandHistoryIndex <= _commandHistory.size());
		checkIsCommandValid();
		resetLogicDataSettings();
		runAllRelevantCommandsAgain();
		storeRemainingCommandsInHistory();
	}
	catch (string errorMsg) {
		_userMessage = errorMsg;
		retrieveExistingViewState();
		addUserMessageToCurrentState();
		setNewViewState();
	}

	return;
}

void CommandUndo::runAllRelevantCommandsAgain() {
	int i;
	for (i=0; i<_currentCommandHistoryIndex; i++) {
		_commandHistory[i]->execute();
	}
	sprintf_s(buffer, LOGGING_MSG_RUN_RELEVANT_COMMANDS_AGAIN.c_str(), to_string(_currentCommandHistoryIndex).c_str());
	log(buffer);
	return;
}

void CommandUndo::storeRemainingCommandsInHistory() {
	int i;
	for (i=_currentCommandHistoryIndex; unsigned(i)<_commandHistory.size(); i++) {
		LogicData::addCommandToHistory(_commandHistory[i]);
	}
	LogicData::setCommandHistoryIndex(_currentCommandHistoryIndex);
	sprintf_s(buffer, LOGGING_MSG_STORE_REMAINING_COMMANDS.c_str(), to_string(_commandHistory.size()).c_str(), to_string(_currentCommandHistoryIndex).c_str());
	log(buffer);
	return;
}

bool CommandUndo::checkIsCommandValid() {
	bool isUndoPossible;
	if ((_currentCommandHistoryIndex <= 0) || (_currentCommandHistoryIndex > _commandHistory.size())) {
		throw ERROR_MSG_CANNOT_UNDO_ANYMORE;
		isUndoPossible = false;
	}
	else {
		isUndoPossible = true;
		_currentCommandHistoryIndex--;
	}

	sprintf_s(buffer, LOGGING_MSG_CHECK_IS_COMMAND_VALID.c_str(), to_string(_currentCommandHistoryIndex).c_str(), to_string(isUndoPossible).c_str());
	log(buffer);
	return isUndoPossible;
}

void CommandUndo::retrieveCommandHistory() {
	_commandHistory = LogicData::getCommandHistory();
	sprintf_s(buffer, LOGGING_MSG_RETRIEVE_COMMAND_HISTORY.c_str(), to_string(_commandHistory.size()).c_str());
	log(buffer);
	return;
}

void CommandUndo::retrieveCommandHistoryIndex() {
	_currentCommandHistoryIndex = LogicData::getCurrentCommandHistoryIndex();
	sprintf_s(buffer, LOGGING_MSG_RETRIEVE_COMMAND_HISTORY_INDEX.c_str(), to_string(_currentCommandHistoryIndex).c_str());
	log(buffer);
	return;
}
