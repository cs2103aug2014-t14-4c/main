#include "Command.h"
 
 
Command::Command(void)
{
}

void Command::execute() {
	return;
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