#include "LogicParserDetailsParser.h"

DetailsParser::DetailsParser(string parameters) {
	assert(!parameters.empty());
	_parameters = parameters;
	_tokens = tokenizeString(parameters);
}

DetailsParser::~DetailsParser(void) {
}

void DetailsParser::addNewTask(Command* command) {
	try {
		DatetimeParser datetime;
		Task* task = new Task;
	
		addTaskTags(task);
		datetime.addTaskDatetime(task, _parameters);
		addTaskName(task);

		command->setCurrentTask(*task);
		delete task;
	} catch(const invalid_argument& e) {
		command->setUserMessage(e.what());
		command->setParsedStatus(false);
	} catch(const out_of_range& e) {
		command->setUserMessage(e.what());
		command->setParsedStatus(false);
	}
}

void DetailsParser::deleteExistingTask(Command* command) {
	try {
		if(!hasOnlyIndex()) {
			throw invalid_argument(USERMESSAGE_INVALID_DELETE);
		}
		setTaskIndex(command);
		command->setIsDoneStatus(true);
	} catch(const invalid_argument& e) {
		command->setUserMessage(e.what());
		command->setParsedStatus(false);
	}
}

void DetailsParser::markTaskAsDone(Command* command) {
	try {
		if(!hasOnlyIndex()) {
			throw invalid_argument(USERMESSAGE_INVALID_DONE);
		}
		setTaskIndex(command);
		command->setIsDoneStatus(true);
	} catch(const invalid_argument& e) {
		command->setUserMessage(e.what());
		command->setParsedStatus(false);
	}
}

void DetailsParser::markTaskAsUndone(Command* command) {
	try {
		if(!hasOnlyIndex()) {
			throw invalid_argument(USERMESSAGE_INVALID_UNDONE);
		}
		setTaskIndex(command);
		command->setIsDoneStatus(false);
	} catch(const invalid_argument& e) {
		command->setUserMessage(e.what());
		command->setParsedStatus(false);
	}
}

void DetailsParser::editExistingTask(Command* command) {
	try {
		if(!hasIndex()) {
			throw invalid_argument(USERMESSAGE_INVALID_EDIT_NO_INDEX);
		} else if(!hasEditedTask()) {
			throw invalid_argument(USERMESSAGE_INVALID_EDIT_NO_TASK);
		}
		setTaskIndex(command);
		removeIndexForEdit();
		addNewTask(command);
	} catch(const invalid_argument& e) {
		command->setUserMessage(e.what());
		command->setParsedStatus(false);
	}
}

void DetailsParser::filterExistingTasks(Command* command) {
	try {
		_parameters = transformToLowercase(_parameters);
		_tokens = tokenizeString(_parameters);
		parseDoneFilter(command);
		parseTypeFilter(command);
		parseDateFilter(command);
	} catch(const invalid_argument& e) {
		command->setUserMessage(e.what());
		command->setParsedStatus(false);
	}
}

void DetailsParser::searchForTask(Command* command) {
	try {
		formatForSearch();
		command->setSearchKeyword(_parameters);
	} catch(const exception&) {
		command->setParsedStatus(false);
	}
}

void DetailsParser::setTaskIndex(Command* command) {
	assert(hasIndex());
	command->setTaskIndex(stoi(_tokens.front()));
}

void DetailsParser::addTaskTags(Task* task) {
	vector<string> taskTags;
	_parameters.clear();

	for(auto iter = _tokens.begin(); iter != _tokens.end(); ++iter) {
		if(isTag(*iter)) {
			taskTags.push_back(*iter);
		} else {
			_parameters += *iter + SPACE;
		}
	}
	_parameters = trimWhiteSpace(_parameters);
	_tokens = tokenizeString(_parameters);
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

void DetailsParser::parseDoneFilter(Command* command) {
	try {
		if(foundNoDone()) {
			command->setDoneFilter(Done::DONE_BOTH);
		} else if(foundDone()) {
			command->setDoneFilter(Done::ONLY_DONE);
		} else if(foundUndone()) {
			command->setDoneFilter(Done::ONLY_UNDONE);
		}
	} catch(const invalid_argument&) {
		throw;
	}
}

void DetailsParser::parseTypeFilter(Command* command) {
	try {
		if(foundNoType()) {
			command->setTypeFilter(Type::ALL_TYPES);
		} else if(foundDue()) {
			command->setTypeFilter(Type::ONLY_DUE);
		} else if(foundFixed()) {
			command->setTypeFilter(Type::ONLY_FIXED);
		}
	} catch(const invalid_argument&) {
		throw;
	}
}

void DetailsParser::parseDateFilter(Command* command) {
	try {
		if(foundNoDate()) {
			date positiveInfinity(pos_infin);
			date negativeInfinity(neg_infin);
			command->setStartDateFilter(negativeInfinity);
			command->setEndDateFilter(positiveInfinity);
		} else {
			DatetimeParser datetime;
			datetime.addFilterDate(command, _parameters);
		}
	} catch(const invalid_argument&) {
		throw;
	} catch(const out_of_range& e) {
		command->setUserMessage(e.what());
		command->setParsedStatus(false);
	}
}

bool DetailsParser::hasIndex() {
	return isNumber(_tokens.front());
}

bool DetailsParser::hasOnlyIndex() {
	return (isOneWord(_parameters) && hasIndex());
}

bool DetailsParser::hasEditedTask() {
	return !isOneWord(_parameters);
}

bool DetailsParser::isTag(string word) {
	return (word.find_first_of(IDENTIFIER_TAG) == Zero);
}

bool DetailsParser::foundDone(void) {
	for(auto iter = _tokens.begin(); iter != _tokens.end(); ++iter) {
		if(*iter == FILTER_DONE_DONE) {
			return true;
		}
	}
	return false;
}

bool DetailsParser::foundUndone(void) {
	for(auto iter = _tokens.begin(); iter != _tokens.end(); ++iter) {
		if(*iter == FILTER_DONE_UNDONE) {
			return true;
		}
	}
	return false;
}

bool DetailsParser::foundNoDone(void) {
	for(auto iter = _tokens.begin(); iter != _tokens.end(); ++iter) {
		if(*iter == FILTER_DONE_ALL) {
			return true;
		}
	}
	return false;
}

bool DetailsParser::foundFixed(void) {
	for(auto iter = _tokens.begin(); iter != _tokens.end(); ++iter) {
		if(*iter == FILTER_TYPE_FIXED) {
			return true;
		}
	}
	return false;
}

bool DetailsParser::foundDue(void) {
	for(auto iter = _tokens.begin(); iter != _tokens.end(); ++iter) {
		if(*iter == FILTER_TYPE_DUE) {
			return true;
		}
	}
	return false;
}

bool DetailsParser::foundNoType(void) {
	for(auto iter = _tokens.begin(); iter != _tokens.end(); ++iter) {
		if(*iter == FILTER_TYPE_ALL) {
			return true;
		}
	}
	return false;
}

bool DetailsParser::foundNoDate(void) {
	for(auto iter = _tokens.begin(); iter != _tokens.end(); ++iter) {
		if(*iter == FILTER_DATE_NONE) {
			return true;
		}
	}
	return false;
}

void DetailsParser::removeIndexForEdit() {
	_parameters = getExceptFirstWord(_parameters);
	_tokens.erase(_tokens.begin());
}

void DetailsParser::formatForSearch() {
	string searchWords;
	string searchTags;
	_parameters = transformToLowercase(_parameters);
	_tokens = tokenizeString(_parameters);
	
	for(auto iter = _tokens.begin(); iter != _tokens.end(); ++iter) {
		if(isTag(*iter)) {
			searchTags += *iter;
		} else {
			searchWords += *iter + SPACE;
		}
	}
	_parameters = trimWhiteSpace(searchWords) + searchTags;
}