#include "Command.h"

Command::Command(void) {
	_commandTaskIndex = 0;
	_isCommandValid = true;
	_isParsedCorrectly = true;
	_searchKeyword = "";
	_userMessage = "";
	_currentTask = NULL;
	_currentState = NULL;
}

void Command::execute() {
	return;
}

int Command::getTaskIndex() {
	return _commandTaskIndex;
}

bool Command::getParsedStatus() {
	return _isParsedCorrectly;
}

string Command::getSearchKeyword() {
	return _searchKeyword;
}

Task Command::getCurrentTask() {
	return *_currentTask;
}

void Command::setTaskIndex(int commandTaskIndexToSet) {
	_commandTaskIndex = commandTaskIndexToSet;
	return;
}

void Command::setParsedStatus(bool parsedStatus) {
	_isParsedCorrectly = parsedStatus;
	return;
}

void Command::setSearchKeyword(string searchKeywordToSet) {
	_searchKeyword = searchKeywordToSet;
	return;
}

void Command::setCurrentTask(Task currentTaskToSet) {
	_currentTask = new Task;
	*_currentTask = currentTaskToSet;
	return;
}

bool Command::checkIsParsedCorrectly() {
	if (!_isParsedCorrectly) {
		_userMessage = "Please enter correct input format!";
	}
	return _isParsedCorrectly;
}

void Command::retrieveExistingViewState() {
	_currentState = new State;
	*_currentState = LogicData::getViewState();
	return;
}

void Command::retrieveExistingCurrentState() {
	_currentState = new State;
	*_currentState = LogicData::getCurrentState();
	return;
}

void Command::setNewCurrentState() {
	LogicData::setCurrentState(*_currentState);
	return;
}

void Command::setNewViewState() {
	LogicData::setViewState(*_currentState);
	return;
}

void Command::addThisCommandToHistory(Command* commandToAdd) {
	LogicData::addCommandToHistory(commandToAdd);
	return;
}

void Command::addUserMessageToCurrentState() {
	_currentState->setUserMessage(_userMessage);
	return;
}

void Command::resetLogicDataSettings() {
	LogicData::resetToInitialSettings();
	return;
}
