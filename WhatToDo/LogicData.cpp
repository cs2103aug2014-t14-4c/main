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

const string LogicData::ABBREV_MONTH_JAN = "Jan";
const string LogicData::ABBREV_MONTH_FEB = "Feb";
const string LogicData::ABBREV_MONTH_MAR = "Mar";
const string LogicData::ABBREV_MONTH_APR = "Apr";
const string LogicData::ABBREV_MONTH_MAY = "May";
const string LogicData::ABBREV_MONTH_JUN = "Jun";
const string LogicData::ABBREV_MONTH_JUL = "Jul";
const string LogicData::ABBREV_MONTH_AUG = "Aug";
const string LogicData::ABBREV_MONTH_SEP = "Sep";
const string LogicData::ABBREV_MONTH_OCT = "Oct";
const string LogicData::ABBREV_MONTH_NOV = "Nov";
const string LogicData::ABBREV_MONTH_DEC = "Dec";
const string LogicData::STRING_SPACE_CHAR = " ";
const string LogicData::STRING_EMPTY = "";

const string LogicData::INITIAL_VALUE_LOG_FILE_NAME = "LogicDataLog.txt";

LogicData::LogicData(){
	_currentCommandHistoryIndex = 0;
	_doneFilter = Done::ONLY_UNDONE;
	_typeFilter = Type::ALL_TYPES;
	_startDateFilter = boost::gregorian::date(neg_infin);
	_endDateFilter = boost::gregorian::date(pos_infin);
	_logFileName = INITIAL_VALUE_LOG_FILE_NAME;
	_loggingModeOn = false;
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
	return filterTasks();
	//return _viewState;
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
	LogicData();
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
	try{
		for(auto iter = unfilteredTasks.begin(); iter != unfilteredTasks.end(); ++iter) {
			if(passDoneFilter(*iter) && passTypeFilter(*iter) && passDateFilter(*iter)) {
				filteredTasks.push_back(*iter);
			}
		}
	} catch (const invalid_argument& ia){
		if(!isLoggingModeOn())
			setLoggingModeOn;
	    log(ia.what());
	}
	filteredViewState.setAllTasks(filteredTasks);
	filteredViewState.setActionMessage(filteredViewState.getActionMessage() + "  ||  " + getFilterStatus());
	return filteredViewState;
}

bool LogicData::passDoneFilter(Task task) {
	try{
		switch(_doneFilter) {
			case(Done::DONE_BOTH) :
				return true;
			case(Done::ONLY_DONE) :
				return task.getTaskIsDone();
			case(Done::ONLY_UNDONE) :
				return !task.getTaskIsDone();
			default:;
				throw invalid_argument("INVALID_ARGUMENT: Filter Type not known\n");
		}
	} catch (const invalid_argument&){
		throw;
	}
}

bool LogicData::passTypeFilter(Task task) {
	try{
		switch(_typeFilter) {
			case(Type::ALL_TYPES) :
				return true;
			case(Type::ONLY_FIXED) : 
				return !task.hasDeadline();
			case(Type::ONLY_DUE) :
				return task.hasDeadline() || !task.hasStartTime();
			default:;
				throw invalid_argument("INVALID_ARGUMENT: Filter Type not known\n");
		}
	} catch (const invalid_argument&){
		throw;
	}
}

bool LogicData::passDateFilter(Task task) {
	if(!task.hasStartTime() && !task.hasDeadline()) {
		return true;
	} else if(task.hasDeadline()) {
		return ((task.getTaskDeadline().date() >= _startDateFilter) && (task.getTaskDeadline().date() <= _endDateFilter));
	} else if(task.hasStartTime() && task.hasEndTime()) {
		return ((task.getTaskStartTime().date() >= _startDateFilter) && (task.getTaskStartTime().date() <= _endDateFilter)
			&& (task.getTaskEndTime().date() <= _endDateFilter) && (task.getTaskStartTime().date() >= _startDateFilter));
	} else if(task.hasStartTime() && !task.hasEndTime()) {
		return ((task.getTaskStartTime().date() >= _startDateFilter) && (task.getTaskStartTime().date() <= _endDateFilter));
	}
	return false;
}

string LogicData::getFilterStatus() {
	string filterStatus;
	string doneFilterStatus;
	string typeFilterStatus;
	string dateFilterStatus;
	
	switch(_doneFilter) {
		case(Done::DONE_BOTH) :
			doneFilterStatus = "nodone";
			break;
		case(Done::ONLY_DONE) :
			doneFilterStatus = "done";
			break;
		case(Done::ONLY_UNDONE) :
			doneFilterStatus = "undone";
			break;
	}

	switch(_typeFilter) {
		case(Type::ALL_TYPES) :
			typeFilterStatus = "all types";
			break;
		case(Type::ONLY_FIXED) :
			typeFilterStatus = "only fixed";
			break;
		case(Type::ONLY_DUE) :
			typeFilterStatus = "only due";
			break;
	}

	if (_startDateFilter != boost::gregorian::date(neg_infin)) {
		dateFilterStatus += " / from " + getDisplayDay(ptime(_startDateFilter));
	}
	if (_endDateFilter != boost::gregorian::date(pos_infin)) {
		dateFilterStatus += " to " + getDisplayDay(ptime(_endDateFilter));
	}

	filterStatus = "Filtered by: " + doneFilterStatus + " / " + typeFilterStatus + dateFilterStatus;
	return filterStatus;
}

string LogicData::getDisplayDay(ptime myTime) {
	string displayDay;
	displayDay += to_string(myTime.date().day());
	displayDay += STRING_SPACE_CHAR + changeMonthToMonthOfYear(myTime.date().month());
	displayDay += STRING_SPACE_CHAR + to_string(myTime.date().year());
	return displayDay;
}

string LogicData::changeMonthToMonthOfYear(int month) {
	if (month == 1) {
		return ABBREV_MONTH_JAN;
	} else if (month == 2) {
		return ABBREV_MONTH_FEB;
	} else if (month == 3) {
		return ABBREV_MONTH_MAR;
	} else if (month == 4) {
		return ABBREV_MONTH_APR;
	} else if (month == 5) {
		return ABBREV_MONTH_MAY;
	} else if (month == 6) {
		return ABBREV_MONTH_JUN;
	} else if (month == 7) {
		return ABBREV_MONTH_JUL;
	} else if (month == 8) {
		return ABBREV_MONTH_AUG;
	} else if (month == 9) {
		return ABBREV_MONTH_SEP;
	} else if (month == 10) {
		return ABBREV_MONTH_OCT;
	} else if (month == 11) {
		return ABBREV_MONTH_NOV;
	} else if (month == 12) {
		return ABBREV_MONTH_DEC;
	}

	return STRING_EMPTY;
}

void LogicData::log(string stringToLog){
	if (!isLoggingModeOn()) {
		return;
	}

	ofstream writeToLog;
	writeToLog.open(_logFileName, ios::app);
	writeToLog << stringToLog;
	writeToLog.close();

	return;
}

bool LogicData::isLoggingModeOn(){
	return _loggingModeOn;
}

void LogicData::setLoggingModeOff(){
	_loggingModeOn = false;
}

void LogicData::setLoggingModeOn(){
	_loggingModeOn = true;
}
