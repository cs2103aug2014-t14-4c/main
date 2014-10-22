#include "LogicParserDetailsParser.h"

DetailsParser::DetailsParser(std::string parameters) {
	assert(!parameters.empty());

	_parameters = parameters;
	_tokens = DetailsParser::tokenizeString(parameters);
}

DetailsParser::~DetailsParser(void) {
}

void DetailsParser::addNewTask(Command* command) {
	Task* task = new Task;
	DatetimeParser datetimeParser;

	DetailsParser::addTaskTags(task);
	_parameters = datetimeParser.addTaskDatetime(command, task, _tokens);
	DetailsParser::addTaskName(task);

	command->setCurrentTask(*task);
	delete task;
}

void DetailsParser::deleteExistingTask(Command* command) {
	try {
		if(!DetailsParser::hasOnlyIndex()) {
			throw std::invalid_argument(USERMESSAGE_INVALID_DELETE);
		}
		DetailsParser::setTaskIndex(command);
	} catch(const std::invalid_argument& e) {
		command->setParsedStatus(false);
		command->setUserMessage(e.what());
	}
}

void DetailsParser::markTaskAsDone(Command* command) {
	try {
		if(!DetailsParser::hasOnlyIndex()) {
			throw std::invalid_argument(USERMESSAGE_INVALID_DONE);
		}
		DetailsParser::setTaskIndex(command);
	} catch(const std::invalid_argument& e) {
		command->setParsedStatus(false);
		command->setUserMessage(e.what());
	}
}

void DetailsParser::editExistingTask(Command* command) {
	try {
		if(!DetailsParser::hasIndex()) {
			throw std::invalid_argument(USERMESSAGE_INVALID_EDIT_NO_INDEX);
		} else if(!DetailsParser::hasEditedTask()) {
			throw std::invalid_argument(USERMESSAGE_INVALID_EDIT_NO_TASK);
		}
		DetailsParser::setTaskIndex(command);
		DetailsParser::removeIndexForEdit();
		DetailsParser::addNewTask(command);
	} catch(const std::invalid_argument& e) {
		command->setParsedStatus(false);
		command->setUserMessage(e.what());
	}
}	

void DetailsParser::searchForTask(Command* command) {
	DetailsParser::formatForSearch();
	assert(!_parameters.empty());
	command->setSearchKeyword(_parameters);
}

void DetailsParser::setTaskIndex(Command* command) {
	assert(DetailsParser::hasIndex());
	command->setTaskIndex(std::stoi(_tokens.front()));
}

void DetailsParser::addTaskTags(Task* task) {
	std::vector<std::string> taskTags;
	_parameters.clear();

	for(auto iter = _tokens.begin(); iter != _tokens.end(); ++iter) {
		if(DetailsParser::isTag(*iter)) {
			taskTags.push_back(*iter);
		} else {
			_parameters += *iter + SPACE;
		}
	}
	_parameters = DetailsParser::trimWhiteSpace(_parameters);
	_tokens = DetailsParser::tokenizeString(_parameters);
	task->setTaskTags(taskTags);
}

void DetailsParser::addTaskName(Task* task) {
	task->setTaskName(_parameters);
}

bool DetailsParser::hasIndex() {
	return (DetailsParser::isNumber(_tokens.front()));
}

bool DetailsParser::hasOnlyIndex() {
	return (DetailsParser::isOneWord(_parameters) 
		&& DetailsParser::hasIndex());
}

bool DetailsParser::hasEditedTask() {
	return (!DetailsParser::isOneWord(_parameters));
}

bool DetailsParser::isTag(std::string word) {
	return (word.find_first_of(IDENTIFIER_TAG) == ZERO);
}

void DetailsParser::removeIndexForEdit() {
	_parameters = DetailsParser::getExceptFirstWord(_parameters);
	_tokens.erase(_tokens.begin());
}

void DetailsParser::formatForSearch() {
	std::string searchWords;
	std::string searchTags;
	_parameters = DetailsParser::transformToLowercase(_parameters);
	_tokens = DetailsParser::tokenizeString(_parameters);
	
	for(auto iter = _tokens.begin(); iter != _tokens.end(); ++iter) {
		if(DetailsParser::isTag(*iter)) {
			searchTags += *iter;
		} else {
			searchWords += *iter + SPACE;
		}
	}
	_parameters = DetailsParser::trimWhiteSpace(searchWords) + searchTags;
}