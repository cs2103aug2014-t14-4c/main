#pragma once

#include <sstream>
#include "Command.h"
#include "Task.h"
#include "LogicParserDateTimeParser.h"
#include "LogicParserStringModifier.h"

const std::string IDENTIFIER_TAG = "#";

class LogicParserCommandDetailsParser {
public:
	LogicParserCommandDetailsParser(void);
	LogicParserCommandDetailsParser(std::string parameters);

	void addNewTask(Command* command);
	void editExistingTask(Command* command);

	void setTaskIndex(Command* command);
	void setSearchKeyword(Command* command);

	void addTaskTags(Task* task);
	bool isTag(std::string word);
	void addTaskName(Task* task);
	void removeEditIndexFromParameter();

private:
	std::string _parameters;
};

