#pragma once
#include "Command.h"
#include "CommandAdd.h"
#include "CommandDelete.h"
#include "CommandDone.h"
#include "CommandClear.h"
#include "CommandEdit.h"
#include "CommandLoad.h"
#include "CommandRedo.h"
#include "CommandSearch.h"
#include "CommandUndo.h"
#include "Task.h"
#include "LogicParserCommandDetailsParser.h"
#include "LogicParserStringModifier.h"

//TODO
//Use patterns to detect more variations of the various commands.

const std::string COMMAND_DELETE = "/delete";
const std::string COMMAND_DONE = "/done";
const std::string COMMAND_CLEAR = "/clear";
const std::string COMMAND_EDIT = "/edit";
const std::string COMMAND_LOAD = "/load";
const std::string COMMAND_REDO = "/redo";
const std::string COMMAND_SEARCH = "/search";
const std::string COMMAND_UNDO = "/undo";

class LogicParserCommandCreator {
public:
	LogicParserCommandCreator(void);
	Command* createCommand(std::string userInput);

private:
	std::string _userInput;
	void setUserInput(std::string userInput);

	std::string getUserCommand(void);
	std::string getParameters(void);

	Command* createAddCommand(void);
	Command* createClearCommand(void);
	Command* createDeleteCommand(void);
	Command* createDoneCommand(void);
	Command* createEditCommand(void);
	Command* createLoadCommand(void);
	Command* createRedoCommand(void);
	Command* createSearchCommand(void);
	Command* createUndoCommand(void);

	bool isValidCommandWithStringParameters(void);
	bool isValidCommandWithIndexParameters(void);
	bool isValidCommandWithNoParameters(void);
};

