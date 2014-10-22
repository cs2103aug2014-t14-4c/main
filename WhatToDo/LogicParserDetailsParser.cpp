#include "LogicParserDetailsParser.h"

LogicParserDetailsParser::LogicParserDetailsParser(void) {
}

LogicParserDetailsParser::LogicParserDetailsParser(std::string parameters) {
	assert(!parameters.empty());

	_parameters = parameters;
	_parameterTokens = LogicParserDetailsParser::tokenizeString(parameters);
}

LogicParserDetailsParser::~LogicParserDetailsParser(void) {
}

std::string LogicParserDetailsParser::getStoredString(void) {
	return _parameters;
}

std::vector<std::string> LogicParserDetailsParser::getStoredVector(void) {
	return _parameterTokens;
}

void LogicParserDetailsParser::addNewTask(Command* command) {
	Task* task = new Task;
	LogicParserDatetimeParser datetimeParser;

	LogicParserDetailsParser::addTaskTags(task);
	_parameters = datetimeParser.addTaskDatetime(command, task, _parameterTokens);
	LogicParserDetailsParser::addTaskName(task);

	command->setCurrentTask(*task);
}

void LogicParserDetailsParser::deleteExistingTask(Command* command) {
	try {
		if(!LogicParserDetailsParser::hasOnlyIndex()) {
			throw std::invalid_argument(USERMESSAGE_INVALID_DELETE);
		}
		LogicParserDetailsParser::setTaskIndex(command);
	}
	catch(const std::invalid_argument& e) {
		command->setParsedStatus(false);
		command->setUserMessage(e.what());
	}
}

void LogicParserDetailsParser::markTaskAsDone(Command* command) {
	try {
		if(!LogicParserDetailsParser::hasOnlyIndex()) {
			throw std::invalid_argument(USERMESSAGE_INVALID_DONE);
		}
		LogicParserDetailsParser::setTaskIndex(command);
	}
	catch(const std::invalid_argument& e) {
		command->setParsedStatus(false);
		command->setUserMessage(e.what());
	}
}

void LogicParserDetailsParser::editExistingTask(Command* command) {
	try {
		if(!LogicParserDetailsParser::hasIndex()) {
			throw std::invalid_argument(USERMESSAGE_INVALID_EDIT_NO_INDEX);
		} else if(!LogicParserDetailsParser::hasEditedTask()) {
			throw std::invalid_argument(USERMESSAGE_INVALID_EDIT_NO_TASK);
		}
		LogicParserDetailsParser::setTaskIndex(command);
		LogicParserDetailsParser::removeIndex();
		LogicParserDetailsParser::addNewTask(command);
	}
	catch(const std::invalid_argument& e) {
		command->setParsedStatus(false);
		command->setUserMessage(e.what());
	}
}	

void LogicParserDetailsParser::searchForTask(Command* command) {
	LogicParserDetailsParser::setSearchKeyword(command);
}

void LogicParserDetailsParser::setTaskIndex(Command* command) {
	assert(LogicParserDetailsParser::hasIndex());
	command->setTaskIndex(std::stoi(_parameterTokens.front()));
}

void LogicParserDetailsParser::setSearchKeyword(Command* command) {
	LogicParserDetailsParser::transformParametersToLowercase();
	LogicParserDetailsParser::separateTagsForSearch();

	assert(!_parameters.empty());
	command->setSearchKeyword(_parameters);
}

void LogicParserDetailsParser::addTaskTags(Task* task) {
	std::vector<std::string> taskTags;
	_parameters.clear();

	for(std::vector<std::string>::const_iterator iter = _parameterTokens.begin(); iter != _parameterTokens.end(); ++iter) {
		if(LogicParserDetailsParser::isTag(*iter)) {
			taskTags.push_back(*iter);
		} else {
			_parameters += *iter + SPACE;
		}
	}

	_parameters = LogicParserDetailsParser::trimWhiteSpace(_parameters);
	_parameterTokens = LogicParserDetailsParser::tokenizeString(_parameters);
	task->setTaskTags(taskTags);
}

void LogicParserDetailsParser::addTaskName(Task* task) {
	task->setTaskName(_parameters);
}

bool LogicParserDetailsParser::hasOnlyIndex() {
	return (LogicParserDetailsParser::isOneWord(_parameters) && 
		LogicParserDetailsParser::hasIndex());
}

bool LogicParserDetailsParser::hasIndex() {
	return (LogicParserDetailsParser::isNumber(_parameterTokens.front()));
}

bool LogicParserDetailsParser::hasEditedTask() {
	return !LogicParserDetailsParser::isOneWord(_parameters);
}

void LogicParserDetailsParser::removeIndex() {
	_parameters = LogicParserDetailsParser::getExceptFirstWord(_parameters);
	_parameterTokens.erase(_parameterTokens.begin());
}

void LogicParserDetailsParser::separateTagsForSearch() {
	std::string searchTags;
	std::string searchWords;

	for(auto iter = _parameterTokens.begin(); iter != _parameterTokens.end(); ++iter) {
		if(LogicParserDetailsParser::isTag(*iter)) {
			searchTags += *iter;
		} else {
			searchWords += *iter + SPACE;
		}
	}

	_parameters = LogicParserDetailsParser::trimWhiteSpace(searchWords) + searchTags;
}

bool LogicParserDetailsParser::isTag(std::string word) {
	return (word.find_first_of(IDENTIFIER_TAG) == FIRST_INDEX);
}


void LogicParserDetailsParser::transformParametersToLowercase() {
	_parameters = LogicParserDetailsParser::transformToLowercase(_parameters);

	for(auto iter = _parameterTokens.begin(); iter != _parameterTokens.end(); ++iter) {
		*iter = LogicParserDetailsParser::transformToLowercase(*iter);
	}
}