//@author A0110655N
//****************************************************************************
//CommandCreator is the class responsible for the creation of pointers to each
//concrete Command subclass, based on the user input in comparison to the
//valid command inputs as listed below. 
//
//In the process of validating the command, CommandCreator checks the presence
//of the accomapanying parameters. In particular, it ensures that
//	1) No parameter is given for {CommandClear, CommandRedo, CommandUndo}.
//	2) Parameter(s) are given for {CommandAdd, CommandDelete, CommandDone,
//								   CommandEdit, CommandFilter, CommandSearch}.

//Note that the validity of the parameters are not checked by CommandCreator.
//
//If unnecessary or insufficient parameters are given, the Command
//pointer returned will have its isParsedCorrectly status set to false and
//userMessage set to an explanation of the command and its usage.
//
//CommandCreator inherits string modification functions from StringModifier.
//
//Sample usage:
//	CommandCreator commandCreator;
//	Command* command = commandCreator.createCommand(string);
//****************************************************************************

#pragma once
#include "CommandAdd.h"
#include "CommandDelete.h"
#include "CommandDone.h"
#include "CommandClear.h"
#include "CommandEdit.h"
#include "CommandFilter.h"
#include "CommandLoad.h"
#include "CommandRedo.h"
#include "CommandSearch.h"
#include "CommandUndo.h"
#include "LogicParserDetailsParser.h"

using namespace std;

const string COMMAND_CLEAR = "/clear";
const string COMMAND_DELETE = "/delete";
const string COMMAND_DONE = "/done";
const string COMMAND_EDIT = "/edit";
const string COMMAND_FILTER = "/filter";
const string COMMAND_LOAD = "/load";
const string COMMAND_REDO = "/redo";
const string COMMAND_SEARCH = "/search";
const string COMMAND_UNDO = "/undo";
const string COMMAND_UNDONE = "/undone";

const string USERMESSAGE_INVALID_COMMAND_CLEAR = 
	"Type /clear to clear the search results.";
const string USERMESSAGE_INVALID_COMMAND_DELETE =
	"Type /delete <index> to delete the task at <index>.";
const string USERMESSAGE_INVALID_COMMAND_DONE =
	"Type /done <index> to mark the task at <index> as done.";
const string USERMESSAGE_INVALID_COMMAND_EDIT =
	"Type /edit <index> <edited task> to edit the task at <index>.";
const string USERMESSAGE_INVALID_COMMAND_FILTER = 
	"Type /filter <option> to filter tasks by the option specified.";
const string USERMESSAGE_INVALID_COMMAND_LOAD = 
	"/load is a system command and should not be used.";
const string USERMESSAGE_INVALID_COMMAND_REDO =
	"Type /redo to redo the last undone action.";
const string USERMESSAGE_INVALID_COMMAND_SEARCH =
	"Type /search <keyword> to search for the keyword in your tasks.";
const string USERMESSAGE_INVALID_COMMAND_UNDO =
	"Type /undo to undo the last performed action.";
const string USERMESSAGE_INVALID_COMMAND_UNDONE =
	"Type /undone <index> to mark the task at <index> as not done.";

const string LOG_CREATE_ADD = 
	"CommandCreator - Creating an Add Command.\n";
const string LOG_CREATE_CLEAR = 
	"CommandCreator - Creating a Clear Command.\n";
const string LOG_CREATE_DELETE = 
	"CommandCreator - Creating an Delete Command.\n";
const string LOG_CREATE_DONE = 
	"CommandCreator - Creating a Done Command.\n";
const string LOG_CREATE_EDIT = 
	"CommandCreator - Creating an Edit Command.\n";
const string LOG_CREATE_FILTER = 
	"CommandCreator - Creating a Filter Command.\n";
const string LOG_CREATE_LOAD = 
	"CommandCreator - Creating a Load Command.\n";
const string LOG_CREATE_REDO = 
	"CommandCreator - Creating a Redo Command.\n";
const string LOG_CREATE_SEARCH = 
	"CommandCreator - Creating a Search Command.\n";
const string LOG_CREATE_UNDO = 
	"CommandCreator - Creating an Undo Command.\n";
const string LOG_CREATE_UNDONE = 
	"CommandCreator - Creating an Undone Command.\n";
const string LOG_ERROR_PARAMETER_NUMBER = 
	"CommandCreator - Error - Command not parsed correctly. Unexpected number"
	"of parameters supplied.\n";

class CommandCreator : public StringModifier {
public:
	CommandCreator(void);
	~CommandCreator(void);

	Command* createCommand(string userInput);

private:
	void setUserInput(string userInput);
	string getUserCommand(void);
	string getParameters(void);
	bool hasParameters(void);
	bool hasNoParameters(void);

	//Determines the type of concrete Command subclass according to the user
	//command, if any. This set of methods only check for the first word of
	//the user input, and is not concerned with the parameters, if any.
	bool isClearCommand(void);
	bool isDeleteCommand(void);
	bool isDoneCommand(void);
	bool isEditCommand(void);
	bool isFilterCommand(void);
	bool isLoadCommand(void);
	bool isRedoCommand(void);
	bool isSearchCommand(void);
	bool isUndoCommand(void);
	bool isUndoneCommand(void);

	//Creates the pointer to the respective Command subclasses, and populate
	//their internal fields with the variables required as specified in the
	//user input.
	Command* createAddCommand(void);
	Command* createClearCommand(void);
	Command* createDeleteCommand(void);
	Command* createDoneCommand(void);
	Command* createEditCommand(void);
	Command* createFilterCommand(void);
	Command* createLoadCommand(void);
	Command* createRedoCommand(void);
	Command* createSearchCommand(void);
	Command* createUndoCommand(void);
	Command* createUndoneCommand(void);

	string _userInput;
	string _userCommand;
};