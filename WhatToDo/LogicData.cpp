#include "LogicData.h"

State LogicData::_currentState;
State LogicData::_viewState;
State LogicData::_initialState;
vector<Command*> LogicData::_commandHistory;
int LogicData::_currentCommandHistoryIndex;
int LogicData::_doneFilter;
int LogicData::_typeFilter;
date LogicData::_startDateFilter;
date LogicData::_endDateFilter;

LogicData::LogicData(){
	_currentCommandHistoryIndex = 0;
	_doneFilter = Done::ONLY_UNDONE;
	_typeFilter = Type::ALL_TYPES;
	_startDateFilter = boost::gregorian::date(neg_infin);
	_endDateFilter = boost::gregorian::date(pos_infin);
}

void LogicData::setCurrentState(State stateToSet){
	_currentState = stateToSet;
	StorageExecutor myStorageExecutor;
	myStorageExecutor.saveToStorage(_currentState);
}

void LogicData::setViewState(State stateToSet){
	_viewState = stateToSet;
}

void LogicData::setDoneFilter(int doneFilter){
	_doneFilter = doneFilter;
}

void LogicData::setTypeFilter(int typeFilter){
	_typeFilter = typeFilter;
}

void LogicData::setDateFilter(date startDateFilter, date endDateFilter){
	_startDateFilter = startDateFilter;
	_endDateFilter = endDateFilter;
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

int LogicData::getDoneFilter(){
	return _doneFilter;
}

int LogicData::getTypeFilter(){
	return _typeFilter;
}

date LogicData::getStartDateFilter(){
	return _startDateFilter;
}

date LogicData::getEndDateFilter(){
	return _endDateFilter;
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

State LogicData::filterTasks() {
	State filteredViewState = _viewState;
	vector<Task> unfilteredTasks = _viewState.getAllTasks();
	vector<Task> filteredTasks;
	for(auto iter = unfilteredTasks.begin(); iter != unfilteredTasks.end(); ++iter) {
		if(passDoneFilter(*iter) && passTypeFilter(*iter) && passDateFilter(*iter)) {
			filteredTasks.push_back(*iter);
		}
	}	
	filteredViewState.setAllTasks(filteredTasks);
	return filteredViewState;
}

bool LogicData::passDoneFilter(Task task) {
	switch(_doneFilter) {
		case(Done::DONE_BOTH) :
			return true;
		case(Done::ONLY_DONE) :
			return task.getTaskIsDone();
		case(Done::ONLY_UNDONE) :
			return !task.getTaskIsDone();
	}
}

bool LogicData::passTypeFilter(Task task) {
	switch(_typeFilter) {
		case(Type::ALL_TYPES) :
			return true;
		case(Type::ONLY_FIXED) :
			return !task.hasDeadline();
		case(Type::ONLY_DUE) :
			return task.hasDeadline() || !task.hasStartTime();
	}
}

bool LogicData::passDateFilter(Task task) {
	if(!task.hasStartTime() && !task.hasDeadline()) {
		return true;
	} else if(task.hasDeadline()) {
		return (task.getTaskDeadline().date() >= _startDateFilter);
	} else if(task.hasStartTime() && task.hasEndTime()) {
		return ((task.getTaskStartTime().date() >= _startDateFilter)
			&& (task.getTaskEndTime().date() <= _endDateFilter));
	} else if(task.hasStartTime() && !task.hasEndTime()) {
		return (task.getTaskStartTime().date() >= _startDateFilter);
	}
	return false;
}