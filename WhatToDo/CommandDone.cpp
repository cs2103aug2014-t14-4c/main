#include "CommandDone.h"


CommandDone::CommandDone(void)
{
}

void CommandDone::execute() {
	LogicData myLogicData;
	_currentState = myLogicData.getCurrentState();
	performDoneOperation();
	myLogicData.addCommandToHistory(*this);
	myLogicData.setCurrentState(_currentState);
	myLogicData.setViewState(_currentState);
	return;
}

void CommandDone::performDoneOperation() {
	_currentState.doneTask(_taskIndex);
	return;
}