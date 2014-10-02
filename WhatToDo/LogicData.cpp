#include "LogicData.h"


LogicData::LogicData(void) {
}

State LogicData::getCurrentState() {
	State a;
	return a;
}

State LogicData::getViewState() {
	State a;
	return a;
}

vector<Command> LogicData::getCommandHistory() {
	vector<Command> a;
	return a;
}

void LogicData::setCurrentState(State stateToSet) {
	return;
}
;
void LogicData::setViewState(State stateToSet) {
	return;
}

void LogicData::addCommandToHistory(Command commandToAdd) {
	return;
}

int LogicData::getCurrentCommandHistoryIndex() {
	return 0;
}

void LogicData::resetToInitialSettings() {
	return;
}

void LogicData::loadInitialSettings() {
	return;
}
