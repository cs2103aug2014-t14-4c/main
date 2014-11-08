//@author A0110655N
//****************************************************************************
//DetailsParser is concerned with the parsing of parameters for Command 
//subclasses which require them, specifically {CommandAdd, CommandDelete, 
//CommandDone, CommandEdit, CommandFilter, CommandSearch}. It firstly checks 
//the validity of the parameters supplied. In particular, it ensures that
//	1) Only an integer parameter is given for {CommandDelete, CommandDone}.
//	2) An integer followed by a string parameter is given for {CommandEdit}.
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
//****************************************************************************

#pragma once
#include "LogicParserStringModifier.h"
#include "LogicParserDatetimeParser.h"

using namespace std;

const string IDENTIFIER_TAG = "#";

const string FILTER_CLEAR = "clear";
const string FILTER_DONE_ALL = "nodone";
const string FILTER_DONE_DONE = "done";
const string FILTER_DONE_UNDONE = "undone";
const string FILTER_TYPE_ALL = "notype";
const string FILTER_TYPE_FIXED = "fixed";
const string FILTER_TYPE_DUE = "due";
const string FILTER_DATE_NONE = "nodate";

const string USERMESSAGE_NO_TASK_NAME =
	"You cannot add a task without a task name!";
const string USERMESSAGE_INVALID_DELETE = 
	"You must specify an index to delete a task!";
const string USERMESSAGE_INVALID_DONE = 
	"You must specify an index to mark a task as done!";
const string USERMESSAGE_INVALID_UNDONE = 
	"You must specify an index to mark a task as not done!";
const string USERMESSAGE_INVALID_EDIT_NO_INDEX = 
	"You must specify an index to edit a task!";
const string USERMESSAGE_INVALID_EDIT_NO_TASK = 
	"You must add changed task details to edit a task!";

const string LOG_ADD_TASK = 
	"DetailsParser - Adding new task.\n";
const string LOG_DELETE_TASK = 
	"DetailsParser - Deleteing task.\n";
const string LOG_MARK_DONE = 
	"DetailsParser - Marking task as done.\n";
const string LOG_MARK_UNDONE = 
	"DetailsParser - Marking task as undone.\n";
const string LOG_EDIT_TASK = 
	"DetailsParser - Editing task.\n";
const string LOG_FILTER_TASKS = 
	"DetailsParser - Filtering tasks.\n";
const string LOG_SEARCH_TASKS = 
	"DetailsParser - Searching tasks.\n";

const string LOG_ERROR_NO_INDEX = 
	"DetailsParser - Error - No index supplied.\n";
const string LOG_ERROR_NO_TASK = 
	"DetailsParser - Error - No task supplied.\n";
const string LOG_ERROR_NO_NAME = 
	"DetailsParser - Error - No task name supplied.\n";

class DetailsParser : public StringModifier {
public:
	DetailsParser(string parameters);
	~DetailsParser(void);

	void addNewTask(Command* command);
	void deleteExistingTask(Command* command);
	void markTaskAsDone(Command* command);
	void markTaskAsUndone(Command* command);
	void editExistingTask(Command* command);
	void filterExistingTasks(Command* command);
	void searchForTask(Command* command);

private:
	void setTaskIndex(Command* command);
	void addTaskTags(Task* task);
	void addTaskName(Task* task);

	void clearFilters(Command* command);
	void parseDoneFilter(Command* command);
	void parseTypeFilter(Command* command);
	void parseDateFilter(Command* command);

	bool hasIndex(void);
	bool hasOnlyIndex(void);
	bool hasEditedTask(void);
	bool isTag(string word);

	bool foundClear(void);
	bool foundDone(void);
	bool foundUndone(void);
	bool foundNoDone(void);
	bool foundFixed(void);
	bool foundDue(void);
	bool foundNoType(void);
	bool foundNoDate(void);

	void removeIndexForEdit(void);	
	void formatForSearch(void);

	string _parameters;
	vector<string> _tokens;
};