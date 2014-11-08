#include "State.h"

//Constructor
State::State(){
	maxIndex = 0;
}

//Setters
void State::setAllTasks(vector<Task> tasksToSet){
	_entireListOfTasks = tasksToSet;
}

void State::setUserMessage(string stringToSet){
	_userMessage = stringToSet;
}

void State::setActionMessage(string stringToSet){
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
string State::getUserMessage(){
	return _userMessage;
}

string State::getActionMessage(){
	return _actionMessage;
}

int State::getLastActionType() {
	return _lastActionType;
}

int State::getLastActionTaskIndex() {
	return _lastActionTaskIndex;
}

//Operations
void State::addTask(Task taskToAdd, bool isUserCommand, int specifiedIndex){
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

void State::deleteTask(int taskIndexToDelete, bool isUserCommand){
	for(unsigned int i=0; i< _entireListOfTasks.size();i++){
		if(_entireListOfTasks[i].getTaskIndex() == taskIndexToDelete){
			if (isUserCommand) {
				_lastActionType = actionType::DELETED;
				_lastActionTaskIndex = taskIndexToDelete;
			} else {
				_lastActionType = actionType::NONE;
			}
			_entireListOfTasks.erase(_entireListOfTasks.begin() + i);
		}
	}
}

void State::doneTask(int taskIndexToDo, bool isUserCommand) {
	for(unsigned int i=0; i< _entireListOfTasks.size();i++){
		if(_entireListOfTasks[i].getTaskIndex() == taskIndexToDo){
			_entireListOfTasks[i].setTaskIsDone(isUserCommand);
			_lastActionType = actionType::CHANGED;
			_lastActionTaskIndex = taskIndexToDo;
		}
	}
}

void State::clearAllTasks(){
	_entireListOfTasks.clear();
}

void State::sortAllTasks(){
	int i,j;
	Task swapTask;

	for (i=0; unsigned(i)<_entireListOfTasks.size(); i++) {
		for (j=i+1; unsigned(j)<_entireListOfTasks.size(); j++) {
			if (swapTask.isTaskSortedBefore(_entireListOfTasks[i], _entireListOfTasks[j])) {
				swapTask = _entireListOfTasks[j];
				_entireListOfTasks[j] = _entireListOfTasks[i];
				_entireListOfTasks[i] = swapTask;
			}
		}
	}
}

vector<Task> State::getAllTasks(){
	sortAllTasks();
	return _entireListOfTasks;
}

vector<Task> State::getTimedTasks(){
	vector<Task> timedTasks;
	sortAllTasks();

	for(unsigned int i=0; i<_entireListOfTasks.size();i++){
		if(((_entireListOfTasks[i]).getTaskType() == Task::FIXED_ALLDAY) || 
			((_entireListOfTasks[i]).getTaskType() == Task::FIXED_START) || 
			((_entireListOfTasks[i]).getTaskType() == Task::FIXED_TIME_WITHIN_DAY) ||
			((_entireListOfTasks[i]).getTaskType() == Task::FIXED_TIME_ACROSS_DAY) ||
			((_entireListOfTasks[i]).getTaskType() == Task::FIXED_TIME_TO_DAY) ||
			((_entireListOfTasks[i]).getTaskType() == Task::FIXED_DAY_TO_TIME) ||
			((_entireListOfTasks[i]).getTaskType() == Task::FIXED_DAY_TO_DAY)) {
			timedTasks.push_back(_entireListOfTasks[i]);
		}
	}
	return timedTasks;
}

vector<Task> State::getDeadlineTasks(){
	vector<Task> deadlineTasks;
	sortAllTasks();

	for(unsigned int i=0; i<_entireListOfTasks.size();i++){
		if(((_entireListOfTasks[i]).getTaskType() == Task::DEADLINE_TIME) || 
			((_entireListOfTasks[i]).getTaskType() == Task::DEADLINE_ALLDAY)) {
			deadlineTasks.push_back(_entireListOfTasks[i]);
		}
	}
	return deadlineTasks;
}

vector<Task> State::getFloatingTasks(){
	vector<Task> floatingTasks;
	sortAllTasks();

	for(unsigned int i=0; i<_entireListOfTasks.size();i++){
		if((_entireListOfTasks[i]).getTaskType() == Task::FLOATING){
			floatingTasks.push_back(_entireListOfTasks[i]);
		}
	}
	return floatingTasks;
}

