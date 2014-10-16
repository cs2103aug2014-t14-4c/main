#pragma once
#include <vector>
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

const std::array<std::string, 2> COMMANDS_CLEAR = {"/clear", "/c"};
const std::array<std::string, 3> COMMANDS_DELETE = {"/delete", "/del", "/d"};
const std::array<std::string, 3> COMMANDS_DONE = {"/done, /ok, /finished"};
const std::array<std::string, 2> COMMANDS_EDIT = {"/edit", "/e"};
const std::array<std::string, 1> COMMANDS_LOAD = {"/load"};
const std::array<std::string, 2> COMMANDS_REDO = {"/redo", "/r"};
const std::array<std::string, 4> COMMANDS_SEARCH = {"/search", "/s", "/find", "/f"};
const std::array<std::string, 2> COMMANDS_UNDO = {"/undo", "/u"};

class LogicParserCommandCreator {
public:
	LogicParserCommandCreator(void);
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
	bool isCommandWithIndexParameters(void);
};

