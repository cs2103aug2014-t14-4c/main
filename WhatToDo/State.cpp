#include "State.h"

//Constructor
State::State(){
	maxIndex = 0;
}

//Operations

/*
   This function will need to create a unique index for task
**/
void State::addTask(Task taskToAdd, bool isUserCommand, int specifiedIndex){
	if (specifiedIndex == -1) {
		taskToAdd.setTaskIndex(maxIndex);
		if (isUserCommand) {
			_lastActionType = CHANGED;
			_lastActionTaskIndex = maxIndex;
		}
		else {
			_lastActionType = NONE;
		}
		maxIndex++;
		_entireListOfTasks.push_back(taskToAdd);
	}
	else {
		taskToAdd.setTaskIndex(specifiedIndex);
		if (isUserCommand) {
			_lastActionType = CHANGED;
			_lastActionTaskIndex = specifiedIndex;
		}
		else {
			_lastActionType = NONE;
		}
		_entireListOfTasks.push_back(taskToAdd);
	}
}

//Need to consider if task to delete cannot be found --> Throw exception/error?
void State::deleteTask(int taskIndexToDelete, bool isUserCommand){
	for(unsigned int i=0; i< _entireListOfTasks.size();i++){
		if(_entireListOfTasks[i].getTaskIndex() == taskIndexToDelete){
			if (isUserCommand) {
				_lastActionType = DELETED;
				_lastActionTaskIndex = taskIndexToDelete;
			}
			else {
				_lastActionType = NONE;
			}
			_entireListOfTasks.erase(_entireListOfTasks.begin() + i);
		}
	}
}

void State::doneTask(int taskIndexToDo, bool isUserCommand) {
	for(unsigned int i=0; i< _entireListOfTasks.size();i++){
		if(_entireListOfTasks[i].getTaskIndex() == taskIndexToDo){
			_entireListOfTasks[i].setTaskIsDone(isUserCommand);
			_lastActionType = CHANGED;
			_lastActionTaskIndex = taskIndexToDo;
		}
	}
}

void State::clearAllTasks(){
	_entireListOfTasks.clear();
}

vector<Task> State::getAllTasks(){
	int i;
	int j;
	Task swapTask;

	for (i=0; unsigned(i)<_entireListOfTasks.size(); i++) {
		for (j=0; unsigned(j)<_entireListOfTasks.size(); j++) {
			if (swapTask.isTaskSortedBefore(_entireListOfTasks[i], _entireListOfTasks[j])) {
				swapTask = _entireListOfTasks[j];
				_entireListOfTasks[j] = _entireListOfTasks[i];
				_entireListOfTasks[i] = swapTask;
			}
		}
	}
	return _entireListOfTasks;
}

vector<Task> State::getTimedTasks(){
	vector<Task> timedTasks;

	for(unsigned int i=0; i<_entireListOfTasks.size();i++){
		if(((_entireListOfTasks[i]).getTaskType() == Task::FIXED_ALLDAY) || ((_entireListOfTasks[i]).getTaskType() == Task::FIXED_START) || ((_entireListOfTasks[i]).getTaskType() == Task::FIXED_TIME)) {
			timedTasks.push_back(_entireListOfTasks[i]);
		}
	}
	return timedTasks;
}

vector<Task> State::getDeadlineTasks(){
	vector<Task> deadlineTasks;

	for(unsigned int i=0; i<_entireListOfTasks.size();i++){
		if(((_entireListOfTasks[i]).getTaskType() == Task::DEADLINE_TIME) || ((_entireListOfTasks[i]).getTaskType() == Task::DEADLINE_ALLDAY)) {
			deadlineTasks.push_back(_entireListOfTasks[i]);
		}
	}
	return deadlineTasks;
}

vector<Task> State::getFloatingTasks(){
	vector<Task> floatingTasks;

	for(unsigned int i=0; i<_entireListOfTasks.size();i++){
		if((_entireListOfTasks[i]).getTaskType() == Task::FLOATING){
			floatingTasks.push_back(_entireListOfTasks[i]);
		}
	}
	return floatingTasks;
}

int State::getLastActionType() {
	return _lastActionType;
}

void State::setLastActionType(int actionTypeToSet) {
	_lastActionType = actionTypeToSet;
	return;
}

void State::setLastActionTaskIndex(int actionTaskIndexToSet) {
	_lastActionTaskIndex = actionTaskIndexToSet;
	return;
}

int State::getLastActionTaskIndex() {
	return _lastActionTaskIndex;
}


void State::setAllTasks(vector<Task> tasksToSet){
	_entireListOfTasks = tasksToSet;
}

void State::setUserMessage(string stringToSet){
	_userMessage = stringToSet;
}

void State::setActionMessage(string stringToSet){
	_actionMessage = stringToSet;
}

string State::getUserMessage(){
	return _userMessage;
}

string State::getActionMessage(){
	return _actionMessage;
}