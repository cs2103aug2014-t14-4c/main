#include "CommandDone.h"


CommandDone::CommandDone(void)
{
}

void CommandDone::execute() {
	if (!_parsedStatus) {
		return;
	}
	_currentState = LogicData::getCurrentState();
	performDoneOperation();
	LogicData::addCommandToHistory(this);
	LogicData::setCurrentState(_currentState);
	LogicData::setViewState(_currentState);
	return;
}

void CommandDone::performDoneOperation() {
	_currentState.doneTask(_taskIndex);
	return;
}