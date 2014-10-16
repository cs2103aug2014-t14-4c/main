#include "LogicParserCommandCreator.h"

LogicParserCommandCreator::LogicParserCommandCreator(void) {
}

Command* LogicParserCommandCreator::createCommand(std::string userInput) {
	LogicParserCommandCreator::setUserInput(userInput);
	Command* command = NULL;

	if(LogicParserCommandCreator::isClearCommand()) {
		command = LogicParserCommandCreator::createClearCommand();
	} else if(LogicParserCommandCreator::isDeleteCommand()) {
		command = LogicParserCommandCreator::createDeleteCommand();	
	} else if(LogicParserCommandCreator::isDoneCommand()) {
		command = LogicParserCommandCreator::createDoneCommand();
	} else if(LogicParserCommandCreator::isEditCommand()) {
		command = LogicParserCommandCreator::createEditCommand();
	} else if(LogicParserCommandCreator::isLoadCommand()) {
		command = LogicParserCommandCreator::createLoadCommand();
	} else if(LogicParserCommandCreator::isRedoCommand()) {
		command = LogicParserCommandCreator::createRedoCommand();
	} else if(LogicParserCommandCreator::isSearchCommand()) {
		command = LogicParserCommandCreator::createSearchCommand();
	} else if(LogicParserCommandCreator::isUndoCommand()) {
		command = LogicParserCommandCreator::createUndoCommand();
	} else {
		command = LogicParserCommandCreator::createAddCommand();
	}

	return command;
}


void LogicParserCommandCreator::setUserInput(std::string userInput) {
	_userInput = userInput;
}

std::string LogicParserCommandCreator::getUserCommand(void) {
	LogicParserStringModifier stringMod;
	return stringMod.transformToLowercase(stringMod.getFirstWord(_userInput));
}

std::string LogicParserCommandCreator::getParameters(void) {
	LogicParserStringModifier stringMod;
	return stringMod.getStringExceptFirstWord(_userInput);
}


bool LogicParserCommandCreator::isClearCommand(void) {
	std::string userCommand = LogicParserCommandCreator::getUserCommand();

	for(auto iter = COMMANDS_CLEAR.begin(); iter != COMMANDS_CLEAR.end() ; ++iter) {
		if(userCommand == *iter)
			return true;
	}

	return false;
}

bool LogicParserCommandCreator::isDeleteCommand(void) {
	std::string userCommand = LogicParserCommandCreator::getUserCommand();

	for(auto iter = COMMANDS_DELETE.begin(); iter != COMMANDS_DELETE.end() ; ++iter) {
		if(userCommand == *iter)
			return true;
	}

	return false;
}

bool LogicParserCommandCreator::isDoneCommand(void) {
	std::string userCommand = LogicParserCommandCreator::getUserCommand();

	for(auto iter = COMMANDS_DONE.begin(); iter != COMMANDS_DONE.end() ; ++iter) {
		if(userCommand == *iter)
			return true;
	}

	return false;
}

bool LogicParserCommandCreator::isEditCommand(void) {
	std::string userCommand = LogicParserCommandCreator::getUserCommand();

	for(auto iter = COMMANDS_EDIT.begin(); iter != COMMANDS_EDIT.end() ; ++iter) {
		if(userCommand == *iter)
			return true;
	}

	return false;
}

bool LogicParserCommandCreator::isLoadCommand(void) {
	std::string userCommand = LogicParserCommandCreator::getUserCommand();

	for(auto iter = COMMANDS_LOAD.begin(); iter != COMMANDS_LOAD.end() ; ++iter) {
		if(userCommand == *iter)
			return true;
	}

	return false;
}

bool LogicParserCommandCreator::isRedoCommand(void) {
	std::string userCommand = LogicParserCommandCreator::getUserCommand();

	for(auto iter = COMMANDS_REDO.begin(); iter != COMMANDS_REDO.end() ; ++iter) {
		if(userCommand == *iter)
			return true;
	}

	return false;
}

bool LogicParserCommandCreator::isSearchCommand(void) {
	std::string userCommand = LogicParserCommandCreator::getUserCommand();

	for(auto iter = COMMANDS_SEARCH.begin(); iter != COMMANDS_SEARCH.end() ; ++iter) {
		if(userCommand == *iter)
			return true;
	}

	return false;
}

bool LogicParserCommandCreator::isUndoCommand(void) {
	std::string userCommand = LogicParserCommandCreator::getUserCommand();

	for(auto iter = COMMANDS_UNDO.begin(); iter != COMMANDS_UNDO.end() ; ++iter) {
		if(userCommand == *iter)
			return true;
	}

	return false;
}


Command* LogicParserCommandCreator::createAddCommand(void) {
	Command* addCommand = new CommandAdd;
	LogicParserCommandDetailsParser detailsParser(_userInput);

	addCommand->setParsedStatus(true);
	detailsParser.addNewTask(addCommand);

	return addCommand;
}

Command* LogicParserCommandCreator::createClearCommand(void) {
	Command* clearCommand = new CommandClear;
	clearCommand->setParsedStatus(LogicParserCommandCreator::isCommandWithNoParameters());

	return clearCommand;
}

Command* LogicParserCommandCreator::createDeleteCommand(void) {
	Command* deleteCommand = new CommandDelete;
	deleteCommand->setParsedStatus(LogicParserCommandCreator::isCommandWithIndexParameters());

	if(deleteCommand->getParsedStatus()) {
		LogicParserCommandDetailsParser detailsParser(LogicParserCommandCreator::getParameters());
		detailsParser.setTaskIndex(deleteCommand);
	}

	return deleteCommand;
}

Command* LogicParserCommandCreator::createDoneCommand(void) {
	Command* doneCommand = new CommandDone;
	doneCommand->setParsedStatus(LogicParserCommandCreator::isCommandWithIndexParameters());

	if(doneCommand->getParsedStatus()) {
		LogicParserCommandDetailsParser detailsParser(LogicParserCommandCreator::getParameters());
		detailsParser.setTaskIndex(doneCommand);
	}

	return doneCommand;
}

Command* LogicParserCommandCreator::createEditCommand(void) {
	Command* editCommand = new CommandEdit;
	editCommand->setParsedStatus(LogicParserCommandCreator::isCommandWithParameters());

	if(editCommand->getParsedStatus()) {
		LogicParserCommandDetailsParser detailsParser(LogicParserCommandCreator::getParameters());
		detailsParser.editExistingTask(editCommand);
	}

	return editCommand;
}

Command* LogicParserCommandCreator::createLoadCommand(void) {
	Command* loadCommand = new CommandLoad;
	loadCommand->setParsedStatus(LogicParserCommandCreator::isCommandWithNoParameters());

	return loadCommand;
}

Command* LogicParserCommandCreator::createRedoCommand(void) {
	Command* redoCommand = new CommandRedo;
	redoCommand->setParsedStatus(LogicParserCommandCreator::isCommandWithNoParameters());

	return redoCommand;
}

Command* LogicParserCommandCreator::createSearchCommand(void) {
	Command* searchCommand = new CommandSearch;
	searchCommand->setParsedStatus(LogicParserCommandCreator::isCommandWithParameters());

	if(searchCommand->getParsedStatus()) {
		LogicParserCommandDetailsParser detailsParser(LogicParserCommandCreator::getParameters());
		detailsParser.setSearchKeyword(searchCommand);
	}

	return searchCommand;
}

Command* LogicParserCommandCreator::createUndoCommand(void) {
	Command* undoCommand = new CommandUndo;
	undoCommand->setParsedStatus(LogicParserCommandCreator::isCommandWithNoParameters());

	return undoCommand;
}


bool LogicParserCommandCreator::isCommandWithParameters(void) {
	LogicParserStringModifier stringMod;
	return !stringMod.isOneWord(_userInput);
}

bool LogicParserCommandCreator::isCommandWithNoParameters(void) {
	return !LogicParserCommandCreator::isCommandWithParameters();
}

bool LogicParserCommandCreator::isCommandWithIndexParameters(void) {
	LogicParserStringModifier stringMod;

	return (LogicParserCommandCreator::isCommandWithParameters() && 
			stringMod.isNumber(LogicParserCommandCreator::getParameters()));
}

