#include "CommandUndo.h"

CommandUndo::CommandUndo(void) {
}

void CommandUndo::execute() {
	sprintf_s(buffer, MSG_LOGGING_EXECUTE_COMMAND_UNDO.c_str());
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
		_currentState->setActionMessage(STRING_EMPTY);
		setNewViewState();
	}

	return;
}

void CommandUndo::runAllRelevantCommandsAgain() {
	int i;
	for (i=0; i<_currentCommandHistoryIndex; i++) {
		_commandHistory[i]->execute();
	}

	sprintf_s(buffer, 
		MSG_LOGGING_RUN_RELEVANT_COMMANDS_AGAIN.c_str(), 
		to_string(_currentCommandHistoryIndex).c_str());
	log(buffer);
	return;
}

void CommandUndo::storeRemainingCommandsInHistory() {
	int i;
	for (i=_currentCommandHistoryIndex; 
			unsigned(i)<_commandHistory.size(); i++) {
		LogicData::addCommandToHistory(_commandHistory[i]);
	}
	LogicData::setCommandHistoryIndex(_currentCommandHistoryIndex);

	sprintf_s(buffer, MSG_LOGGING_STORE_REMAINING_COMMANDS.c_str(), 
		to_string(_commandHistory.size()).c_str(), 
		to_string(_currentCommandHistoryIndex).c_str());
	log(buffer);
	return;
}

bool CommandUndo::checkIsCommandValid() {
	bool isUndoPossible;
	if ((_currentCommandHistoryIndex <= 0) 
			|| (_currentCommandHistoryIndex > _commandHistory.size())) {
		throw MSG_ERROR_CANNOT_UNDO_ANYMORE;
		isUndoPossible = false;
	}
	else {
		isUndoPossible = true;
		_currentCommandHistoryIndex--;
	}

	sprintf_s(buffer, MSG_LOGGING_CHECK_IS_COMMAND_VALID.c_str(), 
		to_string(_currentCommandHistoryIndex).c_str(), 
		to_string(isUndoPossible).c_str());
	log(buffer);
	return isUndoPossible;
}

void CommandUndo::retrieveCommandHistory() {
	_commandHistory = LogicData::getCommandHistory();

	sprintf_s(buffer, MSG_LOGGING_RETRIEVE_COMMAND_HISTORY.c_str(), 
		to_string(_commandHistory.size()).c_str());
	log(buffer);
	return;
}

void CommandUndo::retrieveCommandHistoryIndex() {
	_currentCommandHistoryIndex = 
		LogicData::getCurrentCommandHistoryIndex();

	sprintf_s(buffer, 
		MSG_LOGGING_RETRIEVE_COMMAND_HISTORY_INDEX.c_str(), 
		to_string(_currentCommandHistoryIndex).c_str());
	log(buffer);
	return;
}
