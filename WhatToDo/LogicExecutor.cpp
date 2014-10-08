#include "LogicExecutor.h"


LogicExecutor::LogicExecutor(void)
{
}

State LogicExecutor::getNewState(string commandLineInput) {
	LogicParser parser;
	Command* currentCommand = parser.getCommandFromUserInput(commandLineInput);
	currentCommand->execute();
	State stateToReturn = LogicData::getViewState();
	return stateToReturn;
}