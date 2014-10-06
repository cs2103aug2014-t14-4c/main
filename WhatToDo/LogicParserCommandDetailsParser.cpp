#include "LogicParserCommandDetailsParser.h"

LogicParserCommandDetailsParser::LogicParserCommandDetailsParser(void) {
}

LogicParserCommandDetailsParser::LogicParserCommandDetailsParser(std::string parameters) {
	_parameters = parameters;
}

void LogicParserCommandDetailsParser::setSearchKeyword(Command* command) {
	command->setSearchKeyword(_parameters);
}

void LogicParserCommandDetailsParser::setTaskIndex(Command* command) {
	int taskIndex = -1;
	std::istringstream iss(_parameters);
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
	LogicParserCommandDetailsParser::setTaskIndex(command);
	LogicParserCommandDetailsParser::removeEditIndexFromParameter();
	LogicParserCommandDetailsParser::addNewTask(command);
}

void LogicParserCommandDetailsParser::removeEditIndexFromParameter() {
	LogicParserStringModifier stringMod;
	_parameters = stringMod.getStringExceptFirstWord(_parameters);
}

void LogicParserCommandDetailsParser::addTaskTags(Task* task) {
	std::vector<std::string> taskTags;
	std::istringstream iss(_parameters);
	std::string currentWord;
	_parameters = "";

	while(iss >> currentWord) {
		if(LogicParserCommandDetailsParser::isTag(currentWord)) {
			taskTags.push_back(currentWord);
		} else {
			_parameters += currentWord + " ";
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