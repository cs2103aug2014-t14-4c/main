#include "Task.h"

//Constructor
Task::Task(){}

//Setters
void Task::setTaskStartTime(ptime dateTimeToSet){
	_taskStartDateTime = dateTimeToSet;
}

void Task::setTaskEndTime(ptime dateTimeToSet){
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

ptime Task::getTaskStartTime(){
	return _taskStartDateTime;
}

ptime Task::getTaskEndTime(){
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

	if(_taskStartDateTime< myTask.getTaskStartTime() && _taskEndDateTime > myTask.getTaskStartTime())
		isOverlap = true;
	else {
		if(_taskStartDateTime< myTask.getTaskEndTime() && _taskEndDateTime > myTask.getTaskEndTime())
			isOverlap = true;
	}
	return isOverlap;
}

//Returns true if myTask is earlier than this task
bool Task::isEarlierThan(Task myTask){
	bool isEarlier = false;

	if(myTask.getTaskStartTime() < _taskStartDateTime){
		isEarlier = true;
	}
	return isEarlier;
}

