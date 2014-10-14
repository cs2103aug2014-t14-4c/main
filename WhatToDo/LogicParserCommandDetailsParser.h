#pragma once

#include <sstream>
#include <vector>
#include "Command.h"
#include "Task.h"
#include "LogicParserDateTimeParser.h"
#include "LogicParserStringModifier.h"

const std::string IDENTIFIER_TAG = "#@";
const std::string SPACE = " ";
const int INVALID_INDEX = -1;

class LogicParserCommandDetailsParser {
public:
	LogicParserCommandDetailsParser(void);
	LogicParserCommandDetailsParser(std::string parameters);

	void addNewTask(Command* command);
	void editExistingTask(Command* command);

	void setTaskIndex(Command* command);
	void setSearchKeyword(Command* command);

	bool hasEditIndex();
	bool hasEditedTask();

	void addTaskTags(Task* task);
	bool isTag(std::string word);
	void addTaskName(Task* task);
	void removeEditIndexFromParameter();
	std::vector<std::string> tokenizeString();
	void transformParameterToLowercase();
	void separateTagsForSearch(std::vector<std::string>& searchTokens, std::string& searchWords, std::string& searchTags);

private:
	std::string _parameters;
};

