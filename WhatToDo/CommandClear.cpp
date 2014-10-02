#include "CommandClear.h"


CommandClear::CommandClear(void)
{
}

void CommandClear::execute() {
	LogicData myLogicData;
	_currentState = myLogicData.getCurrentState();
	myLogicData.setViewState(_currentState);
	return;
}
