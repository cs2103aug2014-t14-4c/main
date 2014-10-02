#include "State.h"


State::State(void) {
}

void State::addTask(Task taskToAdd) {
	return;
}

void State::deleteTask(int taskIndexToDelete) {
	return;
}

void State::doneTask(int taskIndexToDo) {
	return;
}

void State::clearAllTasks() {
	return;
}

vector<Task> State::getAllTasks() {
	vector<Task> a;
	return a;
}

vector<Task> State::getTimedTasks() {
	vector<Task> a;
	return a;
}

vector<Task> State::getDeadlineTasks() {
	vector<Task> a;
	return a;
}

vector<Task> State::getFloatingTasks() {
	vector<Task> a;
	return a;
}

void State::setAllTasks(vector<Task> tasksToAdd) {
	return;
}

void State::setUserMessage(string stringToSet) {
	return;
}

string State::getUserMessage() {
	return "";
}
