//****************************************************************************
//@author A0110648L

#include "TestSupportLibrary.h"
#include "stdafx.h"

TestSupportLibrary::TestSupportLibrary(void) {
}


TestSupportLibrary::~TestSupportLibrary(void) {
}


void TestSupportLibrary::compareStates(State firstState, State secondState) {
	int i;
	vector<Task> firstStateTaskList = firstState.getAllTasks();
	vector<Task> secondStateTaskList = secondState.getAllTasks();

	// Number of tasks in both states should be  equal.

	Assert::AreEqual(firstStateTaskList.size(), secondStateTaskList.size());

	for (i=0; unsigned(i)<firstStateTaskList.size(); i++) {

		// Every task should be equal for both states.

		compareTasks(firstStateTaskList[i], secondStateTaskList[i]);
	}
	
	// Both the user messages and the action messages from both states
	// should be equal.

	Assert::AreEqual(firstState.getUserMessage(), 
		secondState.getUserMessage());
	Assert::AreEqual(firstState.getActionMessage(), 
		secondState.getActionMessage());
	return;
}

Task TestSupportLibrary::createTask(string taskName, 
									string taskStart, 
									string taskEnd, 
									string taskDeadline, 
									vector<string> taskTags, 
									bool isDone) {
	Task newTask;
	newTask.setTaskName(taskName);

	if (taskStart != "not-a-date-time") {
		newTask.setTaskStartTime(from_iso_string(taskStart));
	}
	else {
		newTask.setTaskStartTime(not_a_date_time);
	}

	if (taskEnd != "not-a-date-time") {
		newTask.setTaskEndTime(from_iso_string(taskEnd));
	}
	else {
		newTask.setTaskEndTime(not_a_date_time);
	}

	if (taskDeadline != "not-a-date-time") {
		newTask.setTaskDeadline(from_iso_string(taskDeadline));
	}
	else {
		newTask.setTaskDeadline(not_a_date_time);
	}
		
	newTask.setTaskTags(taskTags);

	if (isDone) {
		newTask.setTaskIsDone();
	}

	return newTask;
}


void TestSupportLibrary::compareTaskTags(vector<string> firstTaskTags,
										vector<string> secondTaskTags) {
	Assert::AreEqual(firstTaskTags.size(), secondTaskTags.size());
	int i;
	for (i=0; unsigned(i)<firstTaskTags.size(); i++) {
		Assert::AreEqual(firstTaskTags[i], secondTaskTags[i]);
	}
	return;
}
		
void TestSupportLibrary::compareTasks(Task firstTask, Task secondTask) {
	Assert::AreEqual(firstTask.getTaskName(), secondTask.getTaskName());
	Assert::AreEqual(firstTask.getTaskIsDone(), secondTask.getTaskIsDone());
	compareTaskTags(firstTask.getTaskTags(), secondTask.getTaskTags());
	Assert::AreEqual(to_simple_string(firstTask.getTaskStartTime()), 
		to_simple_string(secondTask.getTaskStartTime()));
	Assert::AreEqual(to_simple_string(firstTask.getTaskEndTime()), 
		to_simple_string(secondTask.getTaskEndTime()));
	Assert::AreEqual(to_simple_string(firstTask.getTaskDeadline()), 
		to_simple_string(secondTask.getTaskDeadline()));
	return;
}
