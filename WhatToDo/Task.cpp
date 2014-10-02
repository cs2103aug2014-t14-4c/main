#include "Task.h"


Task::Task(void) {
}

bool Task::isOverlapWith(Task myTask) {
	return true;
}

bool Task::isEarlierThan(Task myTask) {
	return true;
}

int Task::getTaskType() {
	return 0;
}

		
int Task::getTaskIndex() {
	return 0;
}


ptime Task::getTaskStartDatetime() {
	return ptime();
}

ptime Task::getTaskEndDatetime() {
	return ptime();
}

ptime Task::getTaskDeadline() {
	return ptime();
}


int Task::getTaskDuration() {
	return 0;
}

string Task::getTaskName() {
	return "";
}

string Task::getTaskDetails() {
	return "";
}

vector<string> Task::getTaskTags() {
	vector<string> a;
	return a;
}

bool Task::getIsDone() {
	return true;
}

void Task::setTaskStartDatetime(ptime datetimeToSet) {
	return;
}

void Task::setTaskEndDatetime(ptime datetimeToSet) {
	return;
}

void Task::setTaskDeadline(ptime datetimeToSet) {
	return;
}


void Task::setTaskDuration(int durationToSet) {
	return;
}

void Task::setTaskName(string nameToSet) {
	return;
}

void Task::setTaskDetails(string detailsToSet) {
	return;
}

void Task::setTaskTags(vector<string> tagsToSet) {
	return;
}

void Task::setIsDone() {
	return;
}

void Task::setIsNotDone() {
	return;
}