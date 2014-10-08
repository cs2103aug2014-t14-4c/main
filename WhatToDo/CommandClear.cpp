#include "CommandClear.h"


CommandClear::CommandClear(void)
{
}

void CommandClear::execute() {
	if (!_parsedStatus) {
		return;
	}
	_currentState = LogicData::getCurrentState();
	LogicData::setViewState(_currentState);
	return;
}
