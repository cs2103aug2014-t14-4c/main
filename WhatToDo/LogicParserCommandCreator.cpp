#include "LogicParserCommandCreator.h"

LogicParserCommandCreator::LogicParserCommandCreator(void) {
}

LogicParserCommandCreator::~LogicParserCommandCreator(void) {
}

Command* LogicParserCommandCreator::createCommand(std::string userInput) {
	assert(!userInput.empty());

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
	return LogicParserCommandCreator::transformToLowercase(LogicParserCommandCreator::getFirstWord(_userInput));
}

std::string LogicParserCommandCreator::getParameters(void) {
	return LogicParserCommandCreator::getExceptFirstWord(_userInput);
}

bool LogicParserCommandCreator::isClearCommand(void) {
	std::string userCommand = LogicParserCommandCreator::getUserCommand();

	for(auto iter = COMMANDS_CLEAR.begin(); iter != COMMANDS_CLEAR.end() ; ++iter) {
		if(userCommand == *iter) {
			return true;
		}
	}

	return false;
}

bool LogicParserCommandCreator::isDeleteCommand(void) {
	std::string userCommand = LogicParserCommandCreator::getUserCommand();

	for(auto iter = COMMANDS_DELETE.begin(); iter != COMMANDS_DELETE.end() ; ++iter) {
		if(userCommand == *iter) {
			return true;
		}
	}

	return false;
}

bool LogicParserCommandCreator::isDoneCommand(void) {
	std::string userCommand = LogicParserCommandCreator::getUserCommand();

	for(auto iter = COMMANDS_DONE.begin(); iter != COMMANDS_DONE.end() ; ++iter) {
		if(userCommand == *iter) {
			return true;
		}
	}

	return false;
}

bool LogicParserCommandCreator::isEditCommand(void) {
	std::string userCommand = LogicParserCommandCreator::getUserCommand();

	for(auto iter = COMMANDS_EDIT.begin(); iter != COMMANDS_EDIT.end() ; ++iter) {
		if(userCommand == *iter) {
			return true;
		}
	}

	return false;
}

bool LogicParserCommandCreator::isLoadCommand(void) {
	std::string userCommand = LogicParserCommandCreator::getUserCommand();

	for(auto iter = COMMANDS_LOAD.begin(); iter != COMMANDS_LOAD.end() ; ++iter) {
		if(userCommand == *iter) {
			return true;
		}
	}

	return false;
}

bool LogicParserCommandCreator::isRedoCommand(void) {
	std::string userCommand = LogicParserCommandCreator::getUserCommand();

	for(auto iter = COMMANDS_REDO.begin(); iter != COMMANDS_REDO.end() ; ++iter) {
		if(userCommand == *iter) {
			return true;
		}
	}

	return false;
}

bool LogicParserCommandCreator::isSearchCommand(void) {
	std::string userCommand = LogicParserCommandCreator::getUserCommand();

	for(auto iter = COMMANDS_SEARCH.begin(); iter != COMMANDS_SEARCH.end() ; ++iter) {
		if(userCommand == *iter) {
			return true;
		}
	}

	return false;
}

bool LogicParserCommandCreator::isUndoCommand(void) {
	std::string userCommand = LogicParserCommandCreator::getUserCommand();

	for(auto iter = COMMANDS_UNDO.begin(); iter != COMMANDS_UNDO.end() ; ++iter) {
		if(userCommand == *iter) {
			return true;
		}
	}

	return false;
}

Command* LogicParserCommandCreator::createAddCommand(void) {
	Command* addCommand = new CommandAdd;
	LogicParserDetailsParser detailsParser(_userInput);

	addCommand->setParsedStatus(true);
	detailsParser.addNewTask(addCommand);

	return addCommand;
}

Command* LogicParserCommandCreator::createClearCommand(void) {
	Command* clearCommand = new CommandClear;
	clearCommand->setParsedStatus(LogicParserCommandCreator::isCommandWithNoParameters());

	if(!clearCommand->getParsedStatus()) {
		clearCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_CLEAR);
	}

	return clearCommand;
}

Command* LogicParserCommandCreator::createDeleteCommand(void) {
	Command* deleteCommand = new CommandDelete;
	deleteCommand->setParsedStatus(LogicParserCommandCreator::isCommandWithParameters());

	if(deleteCommand->getParsedStatus()) {
		LogicParserDetailsParser detailsParser(LogicParserCommandCreator::getParameters());
		detailsParser.deleteExistingTask(deleteCommand);
	} else {
		deleteCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_DELETE);
	}

	return deleteCommand;
}

Command* LogicParserCommandCreator::createDoneCommand(void) {
	Command* doneCommand = new CommandDone;
	doneCommand->setParsedStatus(LogicParserCommandCreator::isCommandWithParameters());

	if(doneCommand->getParsedStatus()) {
		LogicParserDetailsParser detailsParser(LogicParserCommandCreator::getParameters());
		detailsParser.markTaskAsDone(doneCommand);
	} else {
		doneCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_DONE);
	}

	return doneCommand;
}

Command* LogicParserCommandCreator::createEditCommand(void) {
	Command* editCommand = new CommandEdit;
	editCommand->setParsedStatus(LogicParserCommandCreator::isCommandWithParameters());

	if(editCommand->getParsedStatus()) {
		LogicParserDetailsParser detailsParser(LogicParserCommandCreator::getParameters());
		detailsParser.editExistingTask(editCommand);
	} else {
		editCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_EDIT);
	}

	return editCommand;
}

Command* LogicParserCommandCreator::createLoadCommand(void) {
	Command* loadCommand = new CommandLoad;
	loadCommand->setParsedStatus(LogicParserCommandCreator::isCommandWithNoParameters());

	if(!loadCommand->getParsedStatus()) {
		loadCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_LOAD);
	}

	return loadCommand;
}

Command* LogicParserCommandCreator::createRedoCommand(void) {
	Command* redoCommand = new CommandRedo;
	redoCommand->setParsedStatus(LogicParserCommandCreator::isCommandWithNoParameters());
	
	if(!redoCommand->getParsedStatus()) {
		redoCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_CLEAR);
	}

	return redoCommand;
}

Command* LogicParserCommandCreator::createSearchCommand(void) {
	Command* searchCommand = new CommandSearch;
	searchCommand->setParsedStatus(LogicParserCommandCreator::isCommandWithParameters());

	if(searchCommand->getParsedStatus()) {
		LogicParserDetailsParser detailsParser(LogicParserCommandCreator::getParameters());
		detailsParser.searchForTask(searchCommand);
	} else {
		searchCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_SEARCH);
	}

	return searchCommand;
}

Command* LogicParserCommandCreator::createUndoCommand(void) {
	Command* undoCommand = new CommandUndo;
	undoCommand->setParsedStatus(LogicParserCommandCreator::isCommandWithNoParameters());
		
	if(!undoCommand->getParsedStatus()) {
		undoCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_CLEAR);
	}

	return undoCommand;
}

bool LogicParserCommandCreator::isCommandWithParameters(void) {
	return !LogicParserCommandCreator::isOneWord(_userInput);
}

bool LogicParserCommandCreator::isCommandWithNoParameters(void) {
	return !LogicParserCommandCreator::isCommandWithParameters();
}