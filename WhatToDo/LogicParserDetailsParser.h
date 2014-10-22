#pragma once
#include "LogicParserStringModifier.h"
#include "LogicParserDatetimeParser.h"

const std::string IDENTIFIER_TAG = "#";
const int FIRST_INDEX = 0;

const std::string USERMESSAGE_INVALID_DELETE = 
	"Type /delete <index> to delete the task at <index>";
const std::string USERMESSAGE_INVALID_DONE = 
	"Type /done <index> to mark the task at <index> as done";
const std::string USERMESSAGE_INVALID_EDIT_NO_INDEX = 
	"No index found. Please type /edit <index> <edited task>";
const std::string USERMESSAGE_INVALID_EDIT_NO_TASK = 
	"No edited task found. Please type /edit <index> <edited task>";

class LogicParserDetailsParser :public LogicParserStringModifier {
public:
	LogicParserDetailsParser(void);
	LogicParserDetailsParser(std::string parameters);
	~LogicParserDetailsParser(void);

	void addNewTask(Command* command);
	void deleteExistingTask(Command* command);
	void markTaskAsDone(Command* command);
	void editExistingTask(Command* command);
	void searchForTask(Command* command);

	std::string getStoredString(void);
	std::vector<std::string> getStoredVector(void);

private:
	std::string _parameters;
	std::vector<std::string> _parameterTokens;

	void setTaskIndex(Command* command);
	void setSearchKeyword(Command* command);
	void addTaskTags(Task* task);
	void addTaskName(Task* task);

	bool hasIndex(void);
	bool hasOnlyIndex(void);
	bool hasEditedTask(void);
	void removeIndex(void);

	void separateTagsForSearch(void);
	bool isTag(std::string word);

	void transformParametersToLowercase(void);
};