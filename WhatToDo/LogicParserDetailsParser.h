//****************************************************************************
//DetailsParser is concerned with the parsing of parameters for Command 
//subclasses which require them, specifically {CommandAdd, CommandDelete, 
//CommandDone, CommandEdit, CommandSearch}. It firstly checks the validity
//of the parameters supplied. In particular, it ensures that
//1) Only an index parameter is given for {CommandDelete, CommandDone}.
//2) An index followed by a string parameter is given for {CommandEdit}.
//
//DetailsParser further ensures that all details are formatted and placed
//in their respective fields. Tasks created for {CommandAdd, CommandEdit} are
//also given its individual attributes, such as TaskName and TaskTags. If 
//parsing is unsuccessful, isParsedCorrectly status will be set to false.
//
//DetailsParser inherits string modification functions from StringModifier.
//
//Sample usage: Initialize with parameters, call relevant function with
//				Command pointer.
//	DetailsParser details(parameters);
//
//	details.addNewTask((CommandAdd*) add);
//	|| details.deleteExistingTask((CommandDelete*) delete);
//	|| details.markTaskAsDone((CommandDone*) done);
//	|| details.editExistingTask((CommandEdit*) edit);
//	|| details.searchForTask((CommandSearch*) search);
//
//@Shu Chang A0110655N
//****************************************************************************

#pragma once
#include "LogicParserStringModifier.h"
#include "LogicParserDatetimeParser.h"

const std::string IDENTIFIER_TAG = "#";

const std::string USERMESSAGE_INVALID_DELETE = 
	"Type /delete <index> to delete the task at <index>.";
const std::string USERMESSAGE_INVALID_DONE = 
	"Type /done <index> to mark the task at <index> as done.";
const std::string USERMESSAGE_INVALID_EDIT_NO_INDEX = 
	"No index found. Type /edit <index> <edited task> to edit a task.";
const std::string USERMESSAGE_INVALID_EDIT_NO_TASK = 
	"No edited task found. Type /edit <index> <edited task> to edit a task.";

class DetailsParser : public StringModifier {
public:
	DetailsParser(std::string parameters);
	~DetailsParser(void);

	//Command pointer will have its _currentTask set with parameters as
	//specified by the user input.
	void addNewTask(Command* command);
	//Command pointer will have its _commandTaskIndex set to the index given.
	void deleteExistingTask(Command* command);
	//Command pointer will have its _commandTaskIndex set to the index given.
	void markTaskAsDone(Command* command);
	//Command pointer will have its _commandTaskIndex set to the index given  
	//and _currentTask set with parameters as specified by the user input.
	void editExistingTask(Command* command);
	//Command pointer will have its _searchKeyword set with parameters as
	//specified by the user input and formatted in accordance with the 
	//CommandSearch documentation.
	void searchForTask(Command* command);

private:
	std::string _parameters;
	std::vector<std::string> _tokens;

	void setTaskIndex(Command* command);
	void addTaskTags(Task* task);
	void addTaskName(Task* task);

	bool hasIndex(void);
	bool hasOnlyIndex(void);
	bool hasEditedTask(void);
	bool isTag(std::string word);

	void removeIndexForEdit(void);	
	void formatForSearch(void);
};