#include "Task.h"

//Constructor
Task::Task(){}

//Setters
void Task::setTaskStartDatetime(ptime dateTimeToSet){
	_taskStartDateTime = dateTimeToSet;
}

void Task::setTaskEndDatetime(ptime dateTimeToSet){
	_taskEndDateTime = dateTimeToSet;
}

void Task::setTaskDeadline(ptime dateTimeToSet){
	_taskDeadline = dateTimeToSet;
}

void Task::setTaskDuration(time_duration durationToSet){
	_taskDuration = durationToSet;
}

void Task::setTaskName(string nameToSet){
	_taskName = nameToSet;
}

void Task::setTaskDetails(string detailsToSet){
	_taskDetails = detailsToSet;
}

void Task::setTaskTags(vector<string> tagsToSet){
	_taskTags = tagsToSet;
}

void Task::setTaskIndex(int indexToSet){
	_taskIndex = indexToSet;
}

//Getters
int Task::getTaskType(){
	return _taskType;
}

int Task::getTaskIndex(){
	return _taskIndex;
}

ptime Task::getTaskStartDatetime(){
	return _taskStartDateTime;
}

ptime Task::getTaskEndDatetime(){
	return _taskEndDateTime;
}

ptime Task::getTaskDeadline(){
	return _taskDeadline;
}

time_duration Task::getTaskDuration(){
	return _taskDuration;
}

string Task::getTaskName(){
	return _taskName;
}

string Task::getTaskDetails(){
	return _taskDetails;
}

vector<string> Task::getTaskTags(){
	return _taskTags;
}

bool Task::isTaskOverlapWith(Task myTask){
	bool isOverlap = false;

	if(_taskStartDateTime< myTask.getTaskStartDatetime() && _taskEndDateTime > myTask.getTaskStartDatetime())
		isOverlap = true;
	else {
		if(_taskStartDateTime< myTask.getTaskEndDatetime() && _taskEndDateTime > myTask.getTaskEndDatetime())
			isOverlap = true;
	}
	return isOverlap;
}

//Returns true if myTask is earlier than this task
bool Task::isEarlierThan(Task myTask){
	bool isEarlier = false;

	if(myTask.getTaskStartDatetime() < _taskStartDateTime){
		isEarlier = true;
	}
	return isEarlier;
}

