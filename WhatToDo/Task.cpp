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

void Task::setTaskIsDone(bool doneStatusToSet){
	_isDone = doneStatusToSet; 
}

void Task::setTaskIsNotDone(){
	_isDone = false;
}

//Getters
int Task::getTaskType(){
	if ((_taskStartDateTime == not_a_date_time) && (_taskDeadline == not_a_date_time)) {
		return FLOATING;
	} else if (_taskDeadline != not_a_date_time) {
		if (_taskDeadline.time_of_day().seconds() == 1) {
			return DEADLINE_ALLDAY;
		} else {
			return DEADLINE_TIME;
		}
	} else if (_taskStartDateTime != not_a_date_time) {
		if (_taskEndDateTime != not_a_date_time) {
			return FIXED_TIME;
		} else if (_taskStartDateTime.time_of_day().seconds() == 1) {
			return FIXED_ALLDAY;
		} else {
			return FIXED_START;
		}
	}
	return FLOATING;
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

bool Task::hasStartTime() {
	return !(_taskStartDateTime == not_a_date_time);
}

bool Task::hasEndTime() {
	return !(_taskEndDateTime == not_a_date_time);
}

bool Task::hasDeadline() {
	return !(_taskDeadline == not_a_date_time);
}

bool Task::isTaskOverlapWith(Task myTask){
	bool isOverlap = false;

	assert(myTask.getTaskType() != FLOATING && this->getTaskType() != FLOATING);

	if (!((myTask.getTaskStartTime().time_of_day().seconds() == 0) 
		&& (myTask.getTaskEndTime().time_of_day().seconds() == 0)
		&& (_taskStartDateTime.time_of_day().seconds() == 0)
		&& (_taskEndDateTime.time_of_day().seconds() == 0))) {
			return isOverlap;
	}

	assert(myTask.getTaskType() == FIXED_TIME && this->getTaskType() == FIXED_TIME);
	if(_taskStartDateTime < myTask.getTaskStartTime() && _taskEndDateTime > myTask.getTaskStartTime()){
		isOverlap = true;
	}else if(_taskStartDateTime< myTask.getTaskEndTime() && _taskEndDateTime > myTask.getTaskEndTime()){
		isOverlap = true;
	}else if(_taskStartDateTime == myTask.getTaskStartTime() || _taskEndDateTime == myTask.getTaskEndTime()){
		isOverlap = true;
    }
	return isOverlap;
}

bool Task::isEarlierThan(Task myTask){
	bool isEarlier = false;
	assert(myTask.getTaskType() != FLOATING && this->getTaskType() != FLOATING);
	if(_taskStartDateTime < myTask.getTaskStartTime()){
		isEarlier = true;
	}
	return isEarlier;
}

bool Task::isTaskSortedBefore(Task firstTask, Task secondTask) {
	bool orderConfirmed = false;
	bool isEarlier;
	int functionToCall = COMPARE_FLOAT;
	try{
		while(!orderConfirmed && functionToCall <= NUM_OF_COMP_FUNCTIONS){
			isEarlier = compare(firstTask, secondTask, &orderConfirmed, functionToCall);
			functionToCall++;
		}
		return isEarlier;
	} catch(const invalid_argument& ia){
		cerr << ia.what();
	}
	return isEarlier;
}

bool Task::compare(Task firstTask, Task secondTask, bool *orderConfirmed, int functionToCall){
	switch(functionToCall){
		case COMPARE_FLOAT: return compareByFloat(firstTask,secondTask, orderConfirmed);
		case COMPARE_DATETIME: return compareByDateTime(firstTask,secondTask, orderConfirmed);
		case COMPARE_DEADLINEALLDAY: return compareByDeadlineAllDay(firstTask,secondTask, orderConfirmed);
		case COMPARE_DEADLINETIME: return compareByDeadlineTime(firstTask,secondTask, orderConfirmed);
		case COMPARE_FIXEDALLDAY: return compareByFixedAllDay(firstTask,secondTask, orderConfirmed);
		case COMPARE_FIXEDSTART: return compareByFixedStart(firstTask,secondTask, orderConfirmed);
		case COMPARE_FIXEDTIME: return compareByFixedTime(firstTask,secondTask, orderConfirmed);
		case COMPARE_FIXEDTIMEANDSTART: return compareByFixedTimeAndStart(firstTask,secondTask, orderConfirmed);
		default:;
			throw invalid_argument(MSG_ERR_INVALID_FUNCTION_CALL);
	}
}

bool Task::compareByFloat(Task firstTask, Task secondTask, bool *orderConfirmed){
	if ((firstTask.getTaskType() == FLOATING) && (secondTask.getTaskType() == FLOATING)) {
		*orderConfirmed = true;
		return firstTask.getTaskIndex() < secondTask.getTaskIndex();
	} else if (firstTask.getTaskType() == FLOATING) {
		*orderConfirmed = true;
		return true;
	} else if (secondTask.getTaskType() == FLOATING) {
		*orderConfirmed = true;
		return false;
	}
	return false;
}

bool Task::compareByDateTime(Task firstTask, Task secondTask, bool *orderConfirmed){
	ptime firstTaskTime;
	ptime secondTaskTime;
	
	if (firstTask.getTaskDeadline() != not_a_date_time) {
		firstTaskTime = firstTask.getTaskDeadline();
	} else {
		firstTaskTime = firstTask.getTaskStartTime();
	}

	if (secondTask.getTaskDeadline() != not_a_date_time) {
		secondTaskTime = secondTask.getTaskDeadline();
	} else {
		secondTaskTime = secondTask.getTaskStartTime();
	}

	if (firstTaskTime.date() < secondTaskTime.date()) {
		*orderConfirmed = true;
		return true;
	} else if (firstTaskTime.date() > secondTaskTime.date()) {
		*orderConfirmed = true;
		return false;
	}
    return false;
}

bool Task::compareByDeadlineAllDay(Task firstTask, Task secondTask, bool *orderConfirmed){
	if ((firstTask.getTaskType() == DEADLINE_ALLDAY) && (secondTask.getTaskType() == DEADLINE_ALLDAY)) {
		*orderConfirmed = true;
		return firstTask.getTaskIndex() < secondTask.getTaskIndex();
	} else if (firstTask.getTaskType() == DEADLINE_ALLDAY) {
		*orderConfirmed = true;
		return true;
	} else if (secondTask.getTaskType() == DEADLINE_ALLDAY) {
		*orderConfirmed = true;
		return false;
	}
	return false;
}

bool Task::compareByDeadlineTime(Task firstTask, Task secondTask, bool *orderConfirmed){
	if ((firstTask.getTaskType() == DEADLINE_TIME) && (secondTask.getTaskType() == DEADLINE_TIME)) {
		*orderConfirmed = true;
		return  firstTask.getTaskDeadline()< secondTask.getTaskDeadline();
	} else if (firstTask.getTaskType() == DEADLINE_TIME) {
		*orderConfirmed = true;
		return true;
	} else if (secondTask.getTaskType() == DEADLINE_TIME) {
		*orderConfirmed = true;
		return false;
	}
	return false;
}

bool Task::compareByFixedAllDay(Task firstTask, Task secondTask, bool *orderConfirmed){
	if ((firstTask.getTaskType() == FIXED_ALLDAY) && (secondTask.getTaskType() == FIXED_ALLDAY)) {
		*orderConfirmed = true;
		return firstTask.getTaskIndex() < secondTask.getTaskIndex();
	} else if (firstTask.getTaskType() == FIXED_ALLDAY) {
		*orderConfirmed = true;
		return true;
	} else if (secondTask.getTaskType() == FIXED_ALLDAY) {
		*orderConfirmed = true;
		return false;
	}
	return false;
}

bool Task::compareByFixedStart(Task firstTask, Task secondTask, bool *orderConfirmed){
	if ((firstTask.getTaskType() == FIXED_START) && (secondTask.getTaskType() == FIXED_START)) {
		*orderConfirmed = true;
		if (firstTask.getTaskStartTime() < secondTask.getTaskStartTime()) {
			return true;
		} else if (firstTask.getTaskStartTime() > secondTask.getTaskStartTime()) {
			return false;
		} else {
			return firstTask.getTaskIndex() < secondTask.getTaskIndex();
		}
	}
	return false;
}

bool Task::compareByFixedTime(Task firstTask, Task secondTask, bool *orderConfirmed){
	if ((firstTask.getTaskType() == FIXED_TIME) && (secondTask.getTaskType() == FIXED_TIME)) {
		*orderConfirmed = true;
		if (firstTask.getTaskStartTime() < secondTask.getTaskStartTime()) {
			return true;
		} else if (firstTask.getTaskStartTime() > secondTask.getTaskStartTime()) {
			return false;
		}
			
		if (firstTask.getTaskEndTime() == secondTask.getTaskEndTime()) {
			return firstTask.getTaskIndex() < secondTask.getTaskIndex();
		} else {
			return firstTask.getTaskEndTime() < secondTask.getTaskEndTime();
		}
	}
	return false;
}

bool Task::compareByFixedTimeAndStart(Task firstTask, Task secondTask, bool *orderConfirmed){
    ptime firstTaskTime;
	ptime secondTaskTime;
	
	if ((firstTask.getTaskType() == FIXED_TIME) && (secondTask.getTaskType() == FIXED_START)) {
		firstTaskTime = ptime(firstTask.getTaskStartTime().date(), hours(firstTask.getTaskStartTime().time_of_day().hours()) + minutes(firstTask.getTaskStartTime().time_of_day().minutes()));
		secondTaskTime = ptime(secondTask.getTaskStartTime().date(), hours(secondTask.getTaskStartTime().time_of_day().hours()) + minutes(secondTask.getTaskStartTime().time_of_day().minutes()));
		*orderConfirmed = true;

		if (firstTaskTime != secondTaskTime) {
			return firstTaskTime < secondTaskTime;
		} else {
			return false;
		}
	} else if ((firstTask.getTaskType() == FIXED_START) && (secondTask.getTaskType() == FIXED_TIME)) {
		firstTaskTime = ptime(firstTask.getTaskStartTime().date(), hours(firstTask.getTaskStartTime().time_of_day().hours()) + minutes(firstTask.getTaskStartTime().time_of_day().minutes()));
		secondTaskTime = ptime(secondTask.getTaskStartTime().date(), hours(secondTask.getTaskStartTime().time_of_day().hours()) + minutes(secondTask.getTaskStartTime().time_of_day().minutes()));
		*orderConfirmed = true;

		if (firstTaskTime != secondTaskTime) {
			return firstTaskTime < secondTaskTime;
		} else {
			return true;
		}
	}
	return false;
}
