#pragma once
#include "CommandAdd.h"
#include "CommandDelete.h"
#include "CommandDone.h"
#include "CommandClear.h"
#include "CommandEdit.h"
#include "CommandLoad.h"
#include "CommandRedo.h"
#include "CommandSearch.h"
#include "CommandUndo.h"
#include "LogicParserDetailsParser.h"

const std::array<std::string, 2> COMMANDS_CLEAR = 
	{"/clear", "/c"};
const std::array<std::string, 3> COMMANDS_DELETE = 
	{"/delete", "/del", "/d"};
const std::array<std::string, 3> COMMANDS_DONE = 
	{"/done, /ok, /finished"};
const std::array<std::string, 2> COMMANDS_EDIT = 
	{"/edit", "/e"};
const std::array<std::string, 1> COMMANDS_LOAD = 
	{"/load"};
const std::array<std::string, 2> COMMANDS_REDO = 
	{"/redo", "/r"};
const std::array<std::string, 4> COMMANDS_SEARCH = 
	{"/search", "/s", "/find", "/f"};
const std::array<std::string, 2> COMMANDS_UNDO = 
	{"/undo", "/u"};

const std::string USERMESSAGE_INVALID_COMMAND_CLEAR = 
	"Type /clear to clear the search results";
const std::string USERMESSAGE_INVALID_COMMAND_DELETE =
	"Type /delete <index> to delete the task at <index>";
const std::string USERMESSAGE_INVALID_COMMAND_DONE =
	"Type /done <index> to mark the task at <index> as done";
const std::string USERMESSAGE_INVALID_COMMAND_EDIT =
	"Type /edit <index> to edit the task at <index>";
const std::string USERMESSAGE_INVALID_COMMAND_LOAD = 
	"/load is a system command and should not be used";
const std::string USERMESSAGE_INVALID_COMMAND_REDO =
	"Type /redo to redo the last undone action";
const std::string USERMESSAGE_INVALID_COMMAND_SEARCH =
	"Type /search <keyword> to search for the keyword in your tasks";
const std::string USERMESSAGE_INVALID_COMMAND_UNDO =
	"Type /undo to undo the last performed action";

class LogicParserCommandCreator :public LogicParserStringModifier {
public:
	LogicParserCommandCreator(void);
	~LogicParserCommandCreator(void);
	Command* createCommand(std::string userInput);

private:
	std::string _userInput;
	void setUserInput(std::string userInput);

	std::string getUserCommand(void);
	std::string getParameters(void);
	
	bool isClearCommand(void);
	bool isDeleteCommand(void);
	bool isDoneCommand(void);
	bool isEditCommand(void);
	bool isLoadCommand(void);
	bool isRedoCommand(void);
	bool isSearchCommand(void);
	bool isUndoCommand(void);

	Command* createAddCommand(void);
	Command* createClearCommand(void);
	Command* createDeleteCommand(void);
	Command* createDoneCommand(void);
	Command* createEditCommand(void);
	Command* createLoadCommand(void);
	Command* createRedoCommand(void);
	Command* createSearchCommand(void);
	Command* createUndoCommand(void);

	bool isCommandWithParameters(void);
	bool isCommandWithNoParameters(void);
};

