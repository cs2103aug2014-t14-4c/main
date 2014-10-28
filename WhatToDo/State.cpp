#include "State.h"

//Constructor
State::State(){
	maxIndex = 0;
}

//Operations
/*
   This function will need to create a unique index for task
**/
void State::addTask(Task taskToAdd){
	taskToAdd.setTaskIndex(maxIndex);
	maxIndex++;
	_entireListOfTasks.push_back(taskToAdd);
}

void State::deleteTask(int taskIndexToDelete){
	for(unsigned int i=0; i< _entireListOfTasks.size();i++){
		if(_entireListOfTasks[i].getTaskIndex() == taskIndexToDelete){
			_entireListOfTasks.erase(_entireListOfTasks.begin() + i);
		}
	}
}

void State::doneTask(int taskIndexToDo) {
	for(unsigned int i=0; i< _entireListOfTasks.size();i++){
		if(_entireListOfTasks[i].getTaskIndex() == taskIndexToDo){
			_entireListOfTasks[i].setTaskIsDone();
		}
	}
}

void State::clearAllTasks(){
	_entireListOfTasks.clear();
}

vector<Task> State::getAllTasks(){
	return _entireListOfTasks;
}

vector<Task> State::getTimedTasks(){
	vector<Task> timedTasks;

	for(unsigned int i=0; i<_entireListOfTasks.size();i++){
		if((_entireListOfTasks[i]).getTaskType() == Task::FIXEDTIME){
			timedTasks.push_back(_entireListOfTasks[i]);
		}
	}
	return timedTasks;
}

vector<Task> State::getDeadlineTasks(){
	vector<Task> deadlineTasks;

	for(unsigned int i=0; i<_entireListOfTasks.size();i++){
		if((_entireListOfTasks[i]).getTaskType() == Task::DEADLINE){
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

void State::setAllTasks(vector<Task> tasksToSet){
	_entireListOfTasks = tasksToSet;
}

void State::setUserMessage(string stringToSet){
	_userMessage = stringToSet;
}

string State::getUserMessage(){
	return _userMessage;
}