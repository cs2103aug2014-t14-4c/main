#include "CommandSearch.h"


CommandSearch::CommandSearch(void)
{
}

void CommandSearch::execute() {
	LogicData myLogicData;
	_currentState = myLogicData.getCurrentState();
	performSearchOperation();
	myLogicData.setViewState(_currentState);
	return;
}

void CommandSearch::performSearchOperation() {
	getTagsToSearchFor();
	getNameToSearchFor();
	getListOfTaskIndexesNotMatchingSearch();
	deleteListOfTaskIndexesNotMatchingSearch();
	return;
}

void CommandSearch::getTagsToSearchFor() {
	int posOfNextTag = 0;
	int posOfCurrentTag = 0;
	int startPos;
	int endPos;
	string currentTag;

	while (_searchKeyword.find("#", posOfNextTag) != string::npos) {
		posOfCurrentTag = _searchKeyword.find("#", posOfNextTag);
		posOfNextTag = _searchKeyword.find("#", posOfCurrentTag+1);

		if (posOfNextTag != string::npos) {
			startPos = posOfCurrentTag + 1;
			endPos = posOfNextTag-posOfCurrentTag - 1;
			currentTag = _searchKeyword.substr(startPos, endPos);
			_tagsToSearchFor.push_back(currentTag);
		}

		else {
			startPos = posOfCurrentTag + 1;
			currentTag = _searchKeyword.substr(startPos);
			_tagsToSearchFor.push_back(currentTag);
			break;
		}
	}

	return;
}

void CommandSearch::getNameToSearchFor() {
	int firstTagPos = _searchKeyword.find("#");
	_stringToSearchFor = _searchKeyword.substr(0,firstTagPos);
	return;
}

void CommandSearch::getListOfTaskIndexesNotMatchingSearch() {
	int i;
	vector<Task> listOfAllTasks = _currentState.getAllTasks();
	
	for (i=0; unsigned(i)<listOfAllTasks.size(); i++) {
		if (!checkIsFitsSearchCriteria(listOfAllTasks[i])) {
			int taskIndexToDelete = listOfAllTasks[i].getTaskIndex();
			_listOfTaskIndexesToDelete.push_back(taskIndexToDelete);
		}
	}
	return;
}

void CommandSearch::deleteListOfTaskIndexesNotMatchingSearch() {
	int i;

	for (i=0; unsigned(i)<_listOfTaskIndexesToDelete.size(); i++) {
		_currentState.deleteTask(_listOfTaskIndexesToDelete[i]);
	}
	return;
}

bool CommandSearch::checkIsFitsSearchCriteria(Task taskToCheck) {
	bool isFitsTagSearchCriteria = checkIsFitsTagSearchCriteria();
	bool isFitsNameSearchCriteria = checkIsFitsNameSearchCriteria();
	bool isFitsSearchCriteria = isFitsTagSearchCriteria || isFitsNameSearchCriteria;
	return isFitsSearchCriteria;
}

bool CommandSearch::checkIsFitsTagSearchCriteria() {
	int i;
	int j;
	string taskTag;
	bool isFitsTagSearchCriteria = false;
	vector<string> listOfTagsForTask = _currentTask.getTaskTags();

	for (i=0; unsigned(i)<listOfTagsForTask.size(); i++) {
		for (j=0; unsigned(j)<_tagsToSearchFor.size(); j++) {
			taskTag = listOfTagsForTask[i];
			if (taskTag.find(_tagsToSearchFor[j]) != string::npos) {
				isFitsTagSearchCriteria = true;
			}
		}
	}

	return isFitsTagSearchCriteria;
}

bool CommandSearch::checkIsFitsNameSearchCriteria() {
	string taskName = _currentTask.getTaskName();
	bool isFitsNameSearchCriteria = taskName.find(_stringToSearchFor) != string::npos;
	return isFitsNameSearchCriteria;
}