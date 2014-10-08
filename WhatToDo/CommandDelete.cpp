#include "CommandDelete.h"


CommandDelete::CommandDelete(void)
{
}

void CommandDelete::execute() {
	if (!_parsedStatus) {
		return;
	}
	_currentState = LogicData::getCurrentState();
	performDeleteOperation();
	LogicData::addCommandToHistory(this);
	LogicData::setCurrentState(_currentState);
	LogicData::setViewState(_currentState);
	return;
}

void CommandDelete::performDeleteOperation() {
	_currentState.deleteTask(_taskIndex);
	return;
}