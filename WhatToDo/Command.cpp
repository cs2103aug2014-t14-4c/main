#include "Command.h"


Command::Command(void) {
	_searchKeyword = "";
	string _userMessage = "";
	bool _isCommandValid = true;
	bool _parsedStatus = true;
}

void Command::execute() {
	return;
}

void Command::setParsedStatus(bool parsedStatus) {
	_parsedStatus = parsedStatus;
	return;
}

bool Command::getParsedStatus() {
	return _parsedStatus;
}

string Command::getSearchKeyword() {
	return _searchKeyword;
}

Task Command::getCurrentTask() {
	return _currentTask;
}

int Command::getTaskIndex() {
	return _taskIndex;
}

void Command::setSearchKeyword(string searchKeywordToSet) {
	_searchKeyword = searchKeywordToSet;
	return;
}

void Command::setCurrentTask(Task currentTaskToSet) {
	_currentTask = currentTaskToSet;
	return;
}

void Command::setTaskIndex(int taskIndexToSet) {
	_taskIndex = taskIndexToSet;
	return;
}