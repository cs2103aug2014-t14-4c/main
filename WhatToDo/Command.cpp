#include "Command.h"

Command::Command(void) {
	_commandTaskIndex = 0;
	_isCommandValid = true;
	_isParsedCorrectly = true;
	_searchKeyword = "";
	_userMessage = "";
	_currentTask = NULL;
	_currentState = NULL;
	_logFileName = "commandLog.txt";
	_loggingModeOn = false;
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
		throw string("Cannot perform command");
		_isParsedCorrectly = false;
	}
	log("Function called: checkIsParsedCorrectly(): _userMessage set as:" + _userMessage + "\n");
	return _isParsedCorrectly;
}

void Command::retrieveExistingViewState() {
	_currentState = new State;
	*_currentState = LogicData::getViewState();
	log("Function called: retrieveExistingViewState()\n");
	return;
}

void Command::retrieveExistingCurrentState() {
	_currentState = new State;
	*_currentState = LogicData::getCurrentState();
	log("Function called: retrieveExistingCurrentState()\n");
	return;
}

void Command::setNewCurrentState() {
	LogicData::setCurrentState(*_currentState);
	log("Function called: setNewCurrentState()\n");
	return;
}

void Command::setNewViewState() {
	LogicData::setViewState(*_currentState);
	log("Function called: setNewViewState()\n");
	return;
}

void Command::addThisCommandToHistory(Command* commandToAdd) {
	LogicData::addCommandToHistory(commandToAdd);
	log("Function called: addThisCommandToHistory()\n");
	return;
}

void Command::addUserMessageToCurrentState() {
	_currentState->setUserMessage(_userMessage);
	log("Function called: addUserMessageToCurrentState(): _userMessage written: " + _userMessage + "\n");
	return;
}

void Command::resetLogicDataSettings() {
	LogicData::resetToInitialSettings();
	log("Function called: resetLogicDataSettings()\n");
	return;
}

void Command::log(string stringToLog) {
	if (!_loggingModeOn) {
		return;
	}
	ofstream writeToLog;
	writeToLog.open(_logFileName, ios::app);
	writeToLog << stringToLog;
	writeToLog.close();
	return;
}