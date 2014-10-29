#include "Task.h"

//Constructor
Task::Task(){
	_taskStartDateTime = not_a_date_time;
	_taskEndDateTime = not_a_date_time;
	_taskDeadline = not_a_date_time;
	_isDone = false;
}

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

void Task::setTaskIsDone(){
	_isDone = true; 
}

void setTaskIsNotDone(){
	_isDone = false;
}

//Getters
int Task::getTaskType(){
	if(!_taskStartDateTime.is_not_a_date_time()){
		return FIXEDTIME;
	} else if(!_taskDeadline.is_not_a_date_time()){
		return DEADLINE;
	} else {
		return FLOATING;
	}
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

//Assumes that taskEndDateTime and taskStartDateTime are initialized
time_duration Task::getTaskDuration(){
	time_duration taskDurationToReturn;
	taskDurationToReturn = _taskEndDateTime - _taskStartDateTime;
	return taskDurationToReturn;
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

bool Task::getTaskIsDone(){
	return _isDone;
}

bool Task::isTaskOverlapWith(Task myTask){
	bool isOverlap = false;

	if(_taskStartDateTime < myTask.getTaskStartTime() && _taskEndDateTime > myTask.getTaskStartTime()){
		isOverlap = true;
	}else if(_taskStartDateTime< myTask.getTaskEndTime() && _taskEndDateTime > myTask.getTaskEndTime()){
		isOverlap = true;
	}else if(_taskStartDateTime == myTask.getTaskStartTime() || _taskEndDateTime == myTask.getTaskEndTime()){
		isOverlap = true;
        }
	return isOverlap;
}

//Returns true if the Task calling this function is earlier than "myTask"
bool Task::isEarlierThan(Task myTask){
	bool isEarlier = false;

	if(_taskStartDateTime < myTask.getTaskStartTime()){
		isEarlier = true;
	}
	return isEarlier;
}