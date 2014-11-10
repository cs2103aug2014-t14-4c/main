//@author A0110873L
#include "State.h"

//Constructor
State::State(){
	maxIndex = 0;
	_loggingModeOn = false;
}

//Setters
void State::setAllTasks(vector<Task> tasksToSet) {
	_entireListOfTasks = tasksToSet;
}

void State::setUserMessage(string stringToSet) {
	_userMessage = stringToSet;
}

void State::setActionMessage(string stringToSet) {
	_actionMessage = stringToSet;
}

void State::setLastActionType(int actionTypeToSet) {
	_lastActionType = actionTypeToSet;
	return;
}

void State::setLastActionTaskIndex(int actionTaskIndexToSet) {
	_lastActionTaskIndex = actionTaskIndexToSet;
	return;
}

//Getters
string State::getUserMessage() {
	return _userMessage;
}

string State::getActionMessage() {
	return _actionMessage;
}

int State::getLastActionType() {
	return _lastActionType;
}

int State::getLastActionTaskIndex() {
	return _lastActionTaskIndex;
}

//Operations
void State::addTask(Task taskToAdd, bool isUserCommand, int specifiedIndex) {
	log(LOG_MSG_ADD_TASK);

	if (specifiedIndex == UNSPECIFIED_INDEX) {
		taskToAdd.setTaskIndex(maxIndex);
		if (isUserCommand) {
			_lastActionType = actionType::CHANGED;
			_lastActionTaskIndex = maxIndex;
		} else {
			_lastActionType = actionType::NONE;
		}
		maxIndex++;
		_entireListOfTasks.push_back(taskToAdd);
	} else {
		taskToAdd.setTaskIndex(specifiedIndex);
		if (isUserCommand) {
			_lastActionType = actionType::CHANGED;
			_lastActionTaskIndex = specifiedIndex;
		} else {
			_lastActionType = actionType::NONE;
		}
		_entireListOfTasks.push_back(taskToAdd);
	}
}

void State::deleteTask(int taskIndexToDelete, bool isUserCommand) {
	log(LOG_MSG_DELETE_TASK);

	for (unsigned int index = INITIAL_INDEX; 
		index < _entireListOfTasks.size(); index++) {
		if (_entireListOfTasks[index].getTaskIndex() == taskIndexToDelete) {
			if (isUserCommand) {
				_lastActionType = actionType::DELETED;
				_lastActionTaskIndex = taskIndexToDelete;
			} else {
				_lastActionType = actionType::NONE;
			}
			_entireListOfTasks.erase(_entireListOfTasks.begin() + index);
		}
	}
}

void State::doneTask(int taskIndexToDo, bool isUserCommand) {
	log(LOG_MSG_DONE_TASK);

	for(unsigned int index = INITIAL_INDEX; 
		index < _entireListOfTasks.size(); index++) {
		if(_entireListOfTasks[index].getTaskIndex() == taskIndexToDo) {
			_entireListOfTasks[index].setTaskIsDone(isUserCommand);
			_lastActionType = actionType::CHANGED;
			_lastActionTaskIndex = taskIndexToDo;
		}
	}
}

void State::clearAllTasks() {
	log(LOG_MSG_CLEAR_TASKS);
	_entireListOfTasks.clear();
}

void State::sortAllTasks() {
	log(LOG_MSG_SORT_TASKS);

	int primaryIndex, secondaryIndex;
	Task swapTask;

	//Selection Sort Algorithm
	for (primaryIndex = INITIAL_INDEX; 
		unsigned(primaryIndex) < _entireListOfTasks.size(); 
		primaryIndex++) {
			for (secondaryIndex = primaryIndex + TO_THE_RIGHT_BY_ONE; 
				unsigned(secondaryIndex) < _entireListOfTasks.size(); 
				secondaryIndex++) {
			if (!swapTask.isTaskSortedBefore(_entireListOfTasks[primaryIndex], 
				_entireListOfTasks[secondaryIndex])) {
				swapTask = _entireListOfTasks[secondaryIndex];
				_entireListOfTasks[secondaryIndex] = _entireListOfTasks[primaryIndex];
				_entireListOfTasks[primaryIndex] = swapTask;
			}
		}
	}
}

vector<Task> State::getAllTasks() {
	sortAllTasks();
	return _entireListOfTasks;
}

vector<Task> State::getTimedTasks() {
	vector<Task> timedTasks;
	sortAllTasks();

	for (unsigned int index = INITIAL_INDEX; 
		index < _entireListOfTasks.size(); index++) {
			if (isTimedTask(_entireListOfTasks[index])) {
			timedTasks.push_back(_entireListOfTasks[index]);
		}
	}
	return timedTasks;
}

vector<Task> State::getDeadlineTasks() {
	vector<Task> deadlineTasks;
	sortAllTasks();

	for (unsigned int index = INITIAL_INDEX; 
		index < _entireListOfTasks.size(); index++) {
			if (isDeadlineTask(_entireListOfTasks[index])) {
			deadlineTasks.push_back(_entireListOfTasks[index]);
		}
	}
	return deadlineTasks;
}

vector<Task> State::getFloatingTasks() {
	vector<Task> floatingTasks;
	sortAllTasks();

	for (unsigned int index = INITIAL_INDEX; 
		index < _entireListOfTasks.size(); index++) {
			if (isFloatingTask(_entireListOfTasks[index])) {
			floatingTasks.push_back(_entireListOfTasks[index]);
		}
	}
	return floatingTasks;
}

bool State::isTimedTask(Task taskToCheck) {
	return (taskToCheck.getTaskType() == Task::FIXED_ALLDAY) || 
			(taskToCheck.getTaskType() == Task::FIXED_START) || 
			(taskToCheck.getTaskType() == Task::FIXED_TIME_WITHIN_DAY) ||
			(taskToCheck.getTaskType() == Task::FIXED_TIME_ACROSS_DAY) ||
			(taskToCheck.getTaskType() == Task::FIXED_TIME_TO_DAY) ||
			(taskToCheck.getTaskType() == Task::FIXED_DAY_TO_TIME) ||
			(taskToCheck.getTaskType() == Task::FIXED_DAY_TO_DAY);
}

bool State::isDeadlineTask(Task taskToCheck) {
	return taskToCheck.getTaskType() == Task::DEADLINE_TIME || 
			taskToCheck.getTaskType() == Task::DEADLINE_ALLDAY;
}

bool State::isFloatingTask(Task taskToCheck) {
	return taskToCheck.getTaskType() == Task::FLOATING;
}

//Logging
void State::log(string stringToLog) {
	if (!isLoggingModeOn()) {
		return;
	}

	ofstream writeToLog;
	writeToLog.open(_logFileName, ios::app);
	writeToLog << stringToLog;
	writeToLog.close();

	return;
}

bool State::isLoggingModeOn() {
	return _loggingModeOn;
}

void State::setLoggingModeOff() {
	_loggingModeOn = false;
}

void State::setLoggingModeOn() {
	_loggingModeOn = true;
}