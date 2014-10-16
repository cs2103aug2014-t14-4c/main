#include "CommandSearch.h"
#include <sstream>
using namespace std;

CommandSearch::CommandSearch(void)
{
}

void CommandSearch::execute() {
	log("\nCommand Search Initiated:\n");

	try {
		checkIsParsedCorrectly();
		retrieveExistingCurrentState();
		performSearchOperation();
		setNewViewState();
	}
	catch (string errorMsg) {
		retrieveExistingViewState();
		addUserMessageToCurrentState();
		setNewViewState();
	}
	
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
	vector<Task> listOfAllTasks = _currentState->getAllTasks();
	
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
		_currentState->deleteTask(_listOfTaskIndexesToDelete[i]);
	}
	return;
}

bool CommandSearch::checkIsFitsSearchCriteria(Task taskToCheck) {
	bool isFitsTagSearchCriteria = checkIsFitsTagSearchCriteria(taskToCheck);
	bool isFitsNameSearchCriteria = checkIsFitsNameSearchCriteria(taskToCheck);
	bool isFitsSearchCriteria = isFitsTagSearchCriteria && isFitsNameSearchCriteria;
	return isFitsSearchCriteria;
}

bool CommandSearch::checkIsFitsTagSearchCriteria(Task taskToCheck) {
	int i;
	int j;
	string taskTag;
	bool isFitsTagSearchCriteria = true;
	bool currentTagFound = false;
	vector<string> listOfTagsForTask = taskToCheck.getTaskTags();

	for (j=0; unsigned(j)<_tagsToSearchFor.size(); j++) {
		for (i=0; unsigned(i)<listOfTagsForTask.size(); i++) {
			taskTag = listOfTagsForTask[i];
			if (convertToLower(taskTag).find(_tagsToSearchFor[j]) != string::npos) {
				currentTagFound = true;
			}
		}
		if (!currentTagFound) {
			isFitsTagSearchCriteria = false;
			break;
		}
		else {
			currentTagFound = false;
		}
	}

	return isFitsTagSearchCriteria;
}

bool CommandSearch::checkIsFitsNameSearchCriteria(Task taskToCheck) {
	string taskName = taskToCheck.getTaskName();
	bool isFitsNameSearchCriteria = convertToLower(taskName).find(_stringToSearchFor) != string::npos;
	return isFitsNameSearchCriteria;
}

string CommandSearch::convertToLower(string toConvert) {
	int i;
	for (i=0; unsigned(i)<toConvert.size(); i++) {
		toConvert[i] = tolower(toConvert[i]);
	}
	return toConvert;
}