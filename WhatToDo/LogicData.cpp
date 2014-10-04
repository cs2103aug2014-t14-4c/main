#include "LogicData.h"

LogicData::LogicData(){}

void LogicData::setCurrentState(State stateToSet){
	_currentState = stateToSet;
}

void LogicData::setViewState(State stateToSet){
	_viewState = stateToSet;
}

vector<Command> LogicData::getCommandHistory(){
	return _commandHistory;
}

void LogicData::addCommandToHistory(Command commandToAdd){
	_commandHistory.push_back(commandToAdd);
}

int LogicData::getCurrentCommandHistoryIndex(){
	return _currentCommandHistoryIndex;
}

//This function resets the view state and current state to initial state
void LogicData::resetToInitialSettings(){
	_currentState = _initialState;
	_viewState = _initialState;
	_commandHistory.clear();
}

void LogicData::loadInitialSettings(){

}