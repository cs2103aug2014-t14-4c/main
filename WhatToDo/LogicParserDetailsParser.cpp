#include "LogicParserDetailsParser.h"

DetailsParser::DetailsParser(string parameters) {
	assert(!parameters.empty());
	_parameters = parameters;
	_tokens = StringModifier::tokenizeString(parameters);
}

DetailsParser::~DetailsParser(void) {
}

void DetailsParser::addNewTask(Command* command) {
	try {
		DatetimeParser datetime;
		Task* task = new Task;
	
		DetailsParser::addTaskTags(task);
		datetime.addTaskDatetime(task, _parameters);
		DetailsParser::addTaskName(task);

		command->setCurrentTask(*task);
		delete task;
	} catch(const exception& e) {
		command->setUserMessage(e.what());
		command->setParsedStatus(false);
	}
}

void DetailsParser::deleteExistingTask(Command* command) {
	try {
		if(!DetailsParser::hasOnlyIndex()) {
			throw invalid_argument(USERMESSAGE_INVALID_DELETE);
		}
		DetailsParser::setTaskIndex(command);
	} catch(const invalid_argument& e) {
		command->setUserMessage(e.what());
		command->setParsedStatus(false);
	}
}

void DetailsParser::markTaskAsDone(Command* command) {
	try {
		if(!DetailsParser::hasOnlyIndex()) {
			throw invalid_argument(USERMESSAGE_INVALID_DONE);
		}
		DetailsParser::setTaskIndex(command);
	} catch(const invalid_argument& e) {
		command->setUserMessage(e.what());
		command->setParsedStatus(false);
	}
}

void DetailsParser::editExistingTask(Command* command) {
	try {
		if(!DetailsParser::hasIndex()) {
			throw invalid_argument(USERMESSAGE_INVALID_EDIT_NO_INDEX);
		} else if(!DetailsParser::hasEditedTask()) {
			throw invalid_argument(USERMESSAGE_INVALID_EDIT_NO_TASK);
		}
		DetailsParser::setTaskIndex(command);
		DetailsParser::removeIndexForEdit();
		DetailsParser::addNewTask(command);
	} catch(const invalid_argument& e) {
		command->setUserMessage(e.what());
		command->setParsedStatus(false);
	}
}	

void DetailsParser::searchForTask(Command* command) {
	try {
		DetailsParser::formatForSearch();
		command->setSearchKeyword(_parameters);
	} catch(const exception&) {
		command->setParsedStatus(false);
	}
}

void DetailsParser::setTaskIndex(Command* command) {
	command->setTaskIndex(stoi(_tokens.front()));
}

void DetailsParser::addTaskTags(Task* task) {
	vector<string> taskTags;
	_parameters.clear();

	for(auto iter = _tokens.begin(); iter != _tokens.end(); ++iter) {
		if(DetailsParser::isTag(*iter)) {
			taskTags.push_back(*iter);
		} else {
			_parameters += *iter + SPACE;
		}
	}
	_parameters = StringModifier::trimWhiteSpace(_parameters);
	_tokens = StringModifier::tokenizeString(_parameters);
	task->setTaskTags(taskTags);
}

void DetailsParser::addTaskName(Task* task) {
	try {
		if(_parameters.empty()) {
			throw invalid_argument(USERMESSAGE_NO_TASK_NAME);
		}
		task->setTaskName(_parameters);
	} catch(const invalid_argument&) {
		throw;
	}
}

bool DetailsParser::hasIndex() {
	return StringModifier::isNumber(_tokens.front());
}

bool DetailsParser::hasOnlyIndex() {
	return (StringModifier::isOneWord(_parameters) 
		&& DetailsParser::hasIndex());
}

bool DetailsParser::hasEditedTask() {
	return !StringModifier::isOneWord(_parameters);
}

bool DetailsParser::isTag(string word) {
	return (word.find_first_of(IDENTIFIER_TAG) == Zero);
}

void DetailsParser::removeIndexForEdit() {
	_parameters = StringModifier::getExceptFirstWord(_parameters);
	_tokens.erase(_tokens.begin());
}

void DetailsParser::formatForSearch() {
	string searchWords;
	string searchTags;
	_parameters = StringModifier::transformToLowercase(_parameters);
	_tokens = StringModifier::tokenizeString(_parameters);
	
	for(auto iter = _tokens.begin(); iter != _tokens.end(); ++iter) {
		if(DetailsParser::isTag(*iter)) {
			searchTags += *iter;
		} else {
			searchWords += *iter + SPACE;
		}
	}
	_parameters = StringModifier::trimWhiteSpace(searchWords) + searchTags;
}