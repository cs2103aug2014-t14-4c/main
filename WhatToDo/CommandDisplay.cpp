#include "CommandDisplay.h"


CommandDisplay::CommandDisplay(void)
{
}

void CommandDisplay::execute() {
	return;
}

State CommandDisplay::getViewState() {
	LogicData myLogicData;
	_currentState = myLogicData.getViewState();
	return _currentState;
}