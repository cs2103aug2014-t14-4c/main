#include "LogicData.h"


State LogicData::_currentState;
State LogicData::_viewState;
State LogicData::_initialState;
vector<Command*> LogicData::_commandHistory;
int LogicData::_currentCommandHistoryIndex;

LogicData::LogicData(){
	_currentCommandHistoryIndex = 0;
}

void LogicData::setCurrentState(State stateToSet){
	_currentState = stateToSet;
}

void LogicData::setViewState(State stateToSet){
	_viewState = stateToSet;
}

State LogicData::getCurrentState() {
	return _currentState;
}

State LogicData::getViewState() {
	return _viewState;
}

vector<Command*> LogicData::getCommandHistory(){
	return _commandHistory;
}

void LogicData::addCommandToHistory(Command* commandToAdd){
	_commandHistory.push_back(commandToAdd);
	_currentCommandHistoryIndex++;
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

void LogicData::setCommandHistoryIndex(int indexToSet) {
	_currentCommandHistoryIndex = indexToSet;
}

void LogicData::fakeinitiate(State fakestate) {
	_initialState = fakestate;
	_currentState = _initialState;
	_viewState = _initialState;

}
