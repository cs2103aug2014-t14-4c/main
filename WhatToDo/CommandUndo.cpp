#include "CommandUndo.h"


CommandUndo::CommandUndo(void)
{
}

void CommandUndo::execute() {
	log("\nCommand Undo Initiated:\n");
	retrieveCommandHistory();
	retrieveCommandHistoryIndex();
	assert(_currentCommandHistoryIndex >= 0);
	assert(_currentCommandHistoryIndex <= _commandHistory.size());
	
	try {
		checkIsParsedCorrectly();
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
	log("Function called: runAllRelevantCommandsAgain(): _currentCommandHistoryIndex: " + to_string(_currentCommandHistoryIndex) + "\n");
	return;
}

void CommandUndo::storeRemainingCommandsInHistory() {
	int i;
	for (i=_currentCommandHistoryIndex; unsigned(i)<_commandHistory.size(); i++) {
		LogicData::addCommandToHistory(_commandHistory[i]);
	}
	LogicData::setCommandHistoryIndex(_currentCommandHistoryIndex);
	log("Function called: storeRemainingCommandsInHistory(): size of _commandHistory: " + to_string(_commandHistory.size()) + "\n");
	log("Function called: storeRemainingCommandsInHistory(): _currentCommandHistoryIndex: " + to_string(_currentCommandHistoryIndex) + "\n");
	return;
}

bool CommandUndo::checkIsCommandValid() {
	bool isUndoPossible;
	if ((_currentCommandHistoryIndex <= 0) || (_currentCommandHistoryIndex > _commandHistory.size())) {
		throw string("Cannot undo anymore!");
		isUndoPossible = false;
	}
	else {
		isUndoPossible = true;
		_currentCommandHistoryIndex--;
	}

	log("Function called: checkIsCommandValid(): updated _currentCommandHistoryIndex: " + to_string(_currentCommandHistoryIndex) + "\n");
	log("Function called: checkIsCommandValid(): isUndoPossible: " + to_string(isUndoPossible) + "\n");
	return isUndoPossible;
}

void CommandUndo::retrieveCommandHistory() {
	_commandHistory = LogicData::getCommandHistory();
	log("Function called: retrieveCommandHistory(): size of CommandHistory: " + to_string(_commandHistory.size()) + "\n");
	return;
}

void CommandUndo::retrieveCommandHistoryIndex() {
	_currentCommandHistoryIndex = LogicData::getCurrentCommandHistoryIndex();
	log("Function called: retrieveCommandHistoryIndex(): _currentCommandHistoryIndex: " + to_string(_currentCommandHistoryIndex) + "\n");
	return;
}
