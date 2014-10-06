#include "CommandClear.h"


CommandClear::CommandClear(void)
{
}

void CommandClear::execute() {
	_currentState = LogicData::getCurrentState();
	LogicData::setViewState(_currentState);
	return;
}
