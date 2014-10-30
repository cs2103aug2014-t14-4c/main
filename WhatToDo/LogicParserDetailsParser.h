//****************************************************************************
//DetailsParser is concerned with the parsing of parameters for Command 
//subclasses which require them, specifically {CommandAdd, CommandDelete, 
//CommandDone, CommandEdit, CommandSearch}. It firstly checks the validity
//of the parameters supplied. In particular, it ensures that
//1) Only an integer parameter is given for {CommandDelete, CommandDone}.
//2) An integer followed by a string parameter is given for {CommandEdit}.
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
//	details.addNewTask((CommandAdd*) add);
//
//@Shu Chang A0110655N
//****************************************************************************

#pragma once
#include "LogicParserStringModifier.h"
#include "LogicParserDatetimeParser.h"

using namespace std;

const string IDENTIFIER_TAG = "#";

const string FILTER_DONE_BOTH = "nodone";
const string FILTER_DONE_DONE = "done";
const string FILTER_DONE_UNDONE = "undone";

const string FILTER_TYPE_ALL = "notype";
const string FILTER_TYPE_FIXED = "fixed";
const string FILTER_TYPE_DUE = "due";

const string FILTER_DATE_NONE = "nodate";

const string USERMESSAGE_NO_TASK_NAME =
	"You cannot add a task without a task name!";
const string USERMESSAGE_INVALID_DELETE = 
	"Type /delete <index> to delete the task at <index>.";
const string USERMESSAGE_INVALID_DONE = 
	"Type /done <index> to mark the task at <index> as done.";
const string USERMESSAGE_INVALID_EDIT_NO_INDEX = 
	"No index found. Type /edit <index> <edited task> to edit a task.";
const string USERMESSAGE_INVALID_EDIT_NO_TASK = 
	"No edited task found. Type /edit <index> <edited task> to edit a task.";

class DetailsParser : public StringModifier {
public:
	DetailsParser(string parameters);
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

	void filterExistingTasks(Command* command);

	//Command pointer will have its _searchKeyword set with parameters as
	//specified by the user input and formatted in accordance with the 
	//CommandSearch requirements.
	void searchForTask(Command* command);

private:
	string _parameters;
	vector<string> _tokens;

	void setTaskIndex(Command* command);
	void addTaskTags(Task* task);
	void addTaskName(Task* task);
	void parseDoneFilter(Command* command);
	void parseTypeFilter(Command* command);
	void parseDateFilter(Command* command);

	bool hasIndex(void);
	bool hasOnlyIndex(void);
	bool hasEditedTask(void);
	bool isTag(string word);

	bool foundDone(void);
	bool foundUndone(void);
	bool foundNoDone(void);

	bool foundFixed(void);
	bool foundDue(void);
	bool foundNoType(void);

	bool foundNoDate(void);

	void removeIndexForEdit(void);	
	void formatForSearch(void);
};