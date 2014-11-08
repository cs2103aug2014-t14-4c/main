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
	if ((!hasStartDateTime()) && (!hasDeadline())) {
		return FLOATING;
	} else if (hasDeadline()) {
		if (isFullDay(_taskDeadline)) {
			return DEADLINE_ALLDAY;
		} else {
			return DEADLINE_TIME;
		}
	} else if (hasStartDateTime()) {
		if (hasEndDateTime()) {
			if(isStartDateEqualEndDate()) {
				return FIXED_TIME_WITHIN_DAY;
			} else if (isFullDay(_taskStartDateTime)) {
				if(isFullDay(_taskEndDateTime)) {
					return FIXED_DAY_TO_DAY;
				} else {
					return FIXED_DAY_TO_TIME;
				}
			} else if(isFullDay(_taskEndDateTime)) {
				return FIXED_TIME_TO_DAY;
			} else {
				return FIXED_TIME_ACROSS_DAY;
			}
		} else if (isFullDay(_taskStartDateTime)) {
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

bool Task::hasStartDateTime() {
	return !(_taskStartDateTime == not_a_date_time);
}

bool Task::hasEndDateTime() {
	return !(_taskEndDateTime == not_a_date_time);
}

bool Task::hasDeadline() {
	return !(_taskDeadline == not_a_date_time);
}

bool Task::isFullDay(ptime dateTimeToCheck){
	return dateTimeToCheck.time_of_day().seconds() == MARKED_AS_FULL_DAY;
}

bool Task::isStartDateEqualEndDate(){
	return _taskStartDateTime.date() == _taskEndDateTime.date();
}

bool Task::isTaskTypeFixedDay(Task myTask){
	int myTaskType = myTask.getTaskType();
	return myTaskType == FIXED_ALLDAY || myTaskType == FIXED_DAY_TO_DAY || 
		myTaskType == FIXED_DAY_TO_TIME;
}

bool Task::isTaskTypeFixedTime(Task myTask){
	int myTaskType = myTask.getTaskType();
	return myTaskType == FIXED_TIME_WITHIN_DAY || myTaskType == FIXED_TIME_ACROSS_DAY ||
		myTaskType == FIXED_TIME_TO_DAY;
}

bool Task::isTaskOverlapWith(Task myTask){
	bool isOverlap = false;
	assert(myTask.getTaskType() != FLOATING && this->getTaskType() != FLOATING);

	if(isFullDay(myTask.getTaskStartTime())
	   || isFullDay(myTask.getTaskEndTime())
	   || isFullDay(_taskStartDateTime)
	   || isFullDay(_taskEndDateTime)){
		   return isOverlap;
	}

	assert(myTask.getTaskType() == FIXED_TIME_WITHIN_DAY && this->getTaskType() == FIXED_TIME_WITHIN_DAY);
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
		case COMPARE_FLOAT: return compareByFloat(firstTask, secondTask, orderConfirmed);
		case COMPARE_DATE: return compareByDate(firstTask, secondTask, orderConfirmed);
		case COMPARE_DEADLINE_ALLDAY: return compareByDeadlineAllDay(firstTask, secondTask, orderConfirmed);
		case COMPARE_DEADLINE_TIME: return compareByDeadlineTime(firstTask, secondTask, orderConfirmed);
		case COMPARE_FIXED_DAY: return compareByFixedDay(firstTask, secondTask, orderConfirmed);
		case COMPARE_FIXED_START: return compareByFixedStart(firstTask, secondTask, orderConfirmed);
		case COMPARE_FIXED_TIME: return compareByFixedTime(firstTask, secondTask, orderConfirmed);
		case COMPARE_FIXED_TIME_START: return compareByFixedTimeAndStart(firstTask, secondTask, orderConfirmed);
		default: throw invalid_argument(MSG_ERR_INVALID_FUNCTION_CALL);
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

bool Task::compareByDate(Task firstTask, Task secondTask, bool *orderConfirmed){
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
	ptime firstTaskTime;
	ptime secondTaskTime;
	
	if ((firstTask.getTaskType() == DEADLINE_TIME) && (secondTask.getTaskType() == DEADLINE_TIME)) {
		*orderConfirmed = true;
		if(firstTask.getTaskDeadline() < secondTask.getTaskDeadline()) {
			return true;
		} else if (firstTask.getTaskDeadline() > secondTask.getTaskDeadline()) {
			return false;
		} else {
			return firstTask.getTaskIndex() < secondTask.getTaskIndex();
		}
	} else if (firstTask.getTaskType() == DEADLINE_TIME) {
		*orderConfirmed = true;
		return true;
	} else if (secondTask.getTaskType() == DEADLINE_TIME) {
		*orderConfirmed = true;
		return false;
	}
	return false;
}

bool Task::compareByFixedDay(Task firstTask, Task secondTask, bool *orderConfirmed){
	if (isTaskTypeFixedDay(firstTask) && isTaskTypeFixedDay(secondTask)) {
		*orderConfirmed = true;

		if (firstTask.getTaskType() == FIXED_ALLDAY) {
			if (secondTask.getTaskType() == FIXED_ALLDAY) {
				return firstTask.getTaskIndex() < secondTask.getTaskIndex();
			} else {
				return true;
			}
		} else if (secondTask.getTaskType() == FIXED_ALLDAY) {
			return false;
		} else if (firstTask.getTaskType() == FIXED_DAY_TO_DAY) {
			if(secondTask.getTaskType() == FIXED_DAY_TO_DAY) {
				if(firstTask.getTaskEndTime().date() < secondTask.getTaskEndTime().date()){
					return true;
				} else if(firstTask.getTaskEndTime().date() > secondTask.getTaskEndTime().date()) {
					return false;
				} else {
					return firstTask.getTaskIndex() < secondTask.getTaskIndex();
			    }
			} else {
				assert(secondTask.getTaskType() == FIXED_DAY_TO_TIME);
				return true;
			}
		} else {
			assert(firstTask.getTaskType() == FIXED_DAY_TO_TIME);
			if(secondTask.getTaskType() != FIXED_DAY_TO_TIME) {
				return false;
			} else {
				assert(secondTask.getTaskType() == FIXED_DAY_TO_TIME);
				if(firstTask.getTaskEndTime() < secondTask.getTaskEndTime()) {
					return true;
				} else if (firstTask.getTaskEndTime() > secondTask.getTaskEndTime()) {
					return false;
				} else {
					return firstTask.getTaskIndex() < secondTask.getTaskIndex();
				}
			}
		}
	} else if (isTaskTypeFixedDay(firstTask)) {
		*orderConfirmed = true;
		return true;
	} else if (isTaskTypeFixedDay(secondTask)) {
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
	if (isTaskTypeFixedTime(firstTask) && isTaskTypeFixedTime(secondTask)) {
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
	
	if ((isTaskTypeFixedTime(firstTask)) && (secondTask.getTaskType() == FIXED_START)) {
		firstTaskTime = ptime(firstTask.getTaskStartTime().date(), 
			hours(firstTask.getTaskStartTime().time_of_day().hours()) + 
			minutes(firstTask.getTaskStartTime().time_of_day().minutes()));

		secondTaskTime = ptime(secondTask.getTaskStartTime().date(), 
			hours(secondTask.getTaskStartTime().time_of_day().hours()) + 
			minutes(secondTask.getTaskStartTime().time_of_day().minutes()));
		*orderConfirmed = true;

		if (firstTaskTime != secondTaskTime) {
			return firstTaskTime < secondTaskTime;
		} else {
			return false;
		}
	} else if ((firstTask.getTaskType() == FIXED_START) && (isTaskTypeFixedTime(secondTask))) {
		firstTaskTime = ptime(firstTask.getTaskStartTime().date(), 
			hours(firstTask.getTaskStartTime().time_of_day().hours()) + 
			minutes(firstTask.getTaskStartTime().time_of_day().minutes()));
		secondTaskTime = ptime(secondTask.getTaskStartTime().date(), 
			hours(secondTask.getTaskStartTime().time_of_day().hours()) + 
			minutes(secondTask.getTaskStartTime().time_of_day().minutes()));
		*orderConfirmed = true;

		if (firstTaskTime != secondTaskTime) {
			return firstTaskTime < secondTaskTime;
		} else {
			return true;
		}
	}
	return false;
}