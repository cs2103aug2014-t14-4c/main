#include "CommandDelete.h"


CommandDelete::CommandDelete(void)
{
}

void CommandDelete::execute() {
	LogicData myLogicData;
	_currentState = myLogicData.getCurrentState();
	performDeleteOperation();
	myLogicData.addCommandToHistory(*this);
	myLogicData.setCurrentState(_currentState);
	myLogicData.setViewState(_currentState);
	return;
}

void CommandDelete::performDeleteOperation() {
	_currentState.deleteTask(_taskIndex);
	return;
}