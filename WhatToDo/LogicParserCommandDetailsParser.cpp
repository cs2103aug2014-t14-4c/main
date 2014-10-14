#include "LogicParserCommandDetailsParser.h"

LogicParserCommandDetailsParser::LogicParserCommandDetailsParser(void) {
}

LogicParserCommandDetailsParser::LogicParserCommandDetailsParser(std::string parameters) {
	_parameters = parameters;
}

void LogicParserCommandDetailsParser::setSearchKeyword(Command* command) {
	LogicParserCommandDetailsParser::transformParameterToLowercase();
	std::vector<std::string> searchTokens = LogicParserCommandDetailsParser::tokenizeString();
	std::string searchWords;
	std::string searchTags;

	LogicParserCommandDetailsParser::separateTagsForSearch(searchTokens, searchWords, searchTags);

	command->setSearchKeyword(searchWords + searchTags);
}

void LogicParserCommandDetailsParser::setTaskIndex(Command* command) {
	std::istringstream iss(_parameters);
	int taskIndex;
	iss >> taskIndex;

	command->setTaskIndex(taskIndex);
}

void LogicParserCommandDetailsParser::addNewTask(Command* command) {
	Task* task = new Task;
	LogicParserDateTimeParser dateTimeParser;

	LogicParserCommandDetailsParser::addTaskTags(task);
	dateTimeParser.addTaskDateTime(task, _parameters);
	LogicParserCommandDetailsParser::addTaskName(task);

	command->setCurrentTask(*task);
}

void LogicParserCommandDetailsParser::editExistingTask(Command* command) {
	if(LogicParserCommandDetailsParser::hasEditIndex() && LogicParserCommandDetailsParser::hasEditedTask()) {
		LogicParserCommandDetailsParser::setTaskIndex(command);
		LogicParserCommandDetailsParser::removeEditIndexFromParameter();
		LogicParserCommandDetailsParser::addNewTask(command);
	} else {
		command->setParsedStatus(false);
	}
}

bool LogicParserCommandDetailsParser::hasEditIndex() {
	std::istringstream iss(_parameters);
	int taskIndex = INVALID_INDEX;

	iss >> taskIndex;

	return (taskIndex != INVALID_INDEX);
}

void LogicParserCommandDetailsParser::removeEditIndexFromParameter() {
	LogicParserStringModifier stringMod;
	_parameters = stringMod.getStringExceptFirstWord(_parameters);
}

void LogicParserCommandDetailsParser::addTaskTags(Task* task) {
	std::vector<std::string> taskTags;
	std::istringstream iss(_parameters);
	std::string currentWord;
	_parameters.clear();

	while(iss >> currentWord) {
		if(LogicParserCommandDetailsParser::isTag(currentWord)) {
			taskTags.push_back(currentWord);
		} else {
			_parameters += currentWord + SPACE;
		}
	}

	task->setTaskTags(taskTags);
}

bool LogicParserCommandDetailsParser::isTag(std::string word) {
	return (word.find_first_of(IDENTIFIER_TAG) == 0);
}

void LogicParserCommandDetailsParser::addTaskName(Task* task) {
	LogicParserStringModifier stringMod;
	task->setTaskName(stringMod.trimWhiteSpace(_parameters));
}

std::vector<std::string> LogicParserCommandDetailsParser::tokenizeString() {
	std::istringstream iss(_parameters);
	std::string currentWord;
	std::vector<std::string> tokens;

	while(iss >> currentWord) {
		tokens.push_back(currentWord);
	}

	return tokens;
}

void LogicParserCommandDetailsParser::transformParameterToLowercase() {
	LogicParserStringModifier stringMod;
	_parameters = stringMod.transformToLowercase(_parameters);
}

void LogicParserCommandDetailsParser::separateTagsForSearch(std::vector<std::string>& searchTokens, std::string& searchWords, std::string& searchTags) {
	for(std::vector<std::string>::iterator iter = searchTokens.begin(); iter != searchTokens.end(); ++iter) {
		if(LogicParserCommandDetailsParser::isTag(*iter)) {
			searchTags += *iter;
		} else {
			searchWords += *iter + SPACE;
		}
	}

}