#include "LogicData.h"

State LogicData::_currentState;
State LogicData::_viewState;
State LogicData::_initialState;
vector<Command*> LogicData::_commandHistory;
int LogicData::_currentCommandHistoryIndex;

LogicData::LogicData(){
	_currentCommandHistoryIndex = 0;
	_filters.done = Done::ALL;
	_filters.type = Type::ALL;
	_filters.startDate = boost::gregorian::date(neg_infin);
	_filters.endDate = boost::gregorian::date(pos_infin);
}

void LogicData::setCurrentState(State stateToSet){
	_currentState = stateToSet;
	StorageExecutor myStorageExecutor;
	myStorageExecutor.saveToStorage(_currentState);
}

void LogicData::setViewState(State stateToSet){
	_viewState = stateToSet;
}

void LogicData::setFilterDone(int doneness){
	_filters.done = doneness;
}

void LogicData::setFilterType(int type){
	_filters.type = type;
}

void LogicData::setFilterStartDate(date startDateToSet){
	_filters.startDate = startDateToSet;
}

void LogicData::setFilterEndDate(date endDateToSet){
	_filters.endDate = endDateToSet;
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

int LogicData::getFilterDone(){
	return _filters.done;
}

int LogicData::getFilterType(){
	return _filters.type;
}

date LogicData::getFilterStartDate(){
	return _filters.startDate;
}

date LogicData::getFilterEndDate(){
	return _filters.endDate;
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
	StorageExecutor myStorageExecutor;
	State initialState = myStorageExecutor.loadFromStorage();
	_initialState = initialState;
	_currentState = initialState;
	_viewState = initialState;
}

void LogicData::resetCommandHistory() {
	_commandHistory.clear();
	return;
}

void LogicData::setCommandHistoryIndex(int indexToSet) {
	_currentCommandHistoryIndex = indexToSet;
}

void LogicData::fakeinitiate(State fakestate) {
	_initialState = fakestate;
	_currentState = _initialState;
	_viewState = _initialState;

}