#include "LogicParserCommandCreator.h"

CommandCreator::CommandCreator(void) {
}

CommandCreator::~CommandCreator(void) {
}

Command* CommandCreator::createCommand(std::string userInput) {
	assert(!userInput.empty());

	CommandCreator::setUserInput(userInput);
	Command* command = NULL;

	if(CommandCreator::isClearCommand()) {
		command = CommandCreator::createClearCommand();
	} else if(CommandCreator::isDeleteCommand()) {
		command = CommandCreator::createDeleteCommand();	
	} else if(CommandCreator::isDoneCommand()) {
		command = CommandCreator::createDoneCommand();
	} else if(CommandCreator::isEditCommand()) {
		command = CommandCreator::createEditCommand();
	} else if(CommandCreator::isLoadCommand()) {
		command = CommandCreator::createLoadCommand();
	} else if(CommandCreator::isRedoCommand()) {
		command = CommandCreator::createRedoCommand();
	} else if(CommandCreator::isSearchCommand()) {
		command = CommandCreator::createSearchCommand();
	} else if(CommandCreator::isUndoCommand()) {
		command = CommandCreator::createUndoCommand();
	} else {
		command = CommandCreator::createAddCommand();
	}
	return command;
}

void CommandCreator::setUserInput(std::string userInput) {
	_userInput = userInput;
	_userCommand = CommandCreator::getUserCommand();
}

std::string CommandCreator::getUserCommand(void) {
	return CommandCreator::transformToLowercase(
		CommandCreator::getFirstWord(_userInput));
}

std::string CommandCreator::getParameters(void) {
	return CommandCreator::getExceptFirstWord(_userInput);
}

bool CommandCreator::hasParameters(void) {
	return !CommandCreator::isOneWord(_userInput);
}

bool CommandCreator::hasNoParameters(void) {
	return CommandCreator::isOneWord(_userInput);
}

bool CommandCreator::isClearCommand(void) {
	for(auto iter = COMMANDS_CLEAR.begin(); 
			iter != COMMANDS_CLEAR.end(); 
			++iter) {
		if(_userCommand == *iter) {
			return true;
		}
	}
	return false;
}

bool CommandCreator::isDeleteCommand(void) {
	for(auto iter = COMMANDS_DELETE.begin(); 
			iter != COMMANDS_DELETE.end(); 
			++iter) {
		if(_userCommand == *iter) {
			return true;
		}
	}
	return false;
}

bool CommandCreator::isDoneCommand(void) {
	for(auto iter = COMMANDS_DONE.begin(); 
			iter != COMMANDS_DONE.end(); 
			++iter) {
		if(_userCommand == *iter) {
			return true;
		}
	}
	return false;
}

bool CommandCreator::isEditCommand(void) {
	for(auto iter = COMMANDS_EDIT.begin(); 
			iter != COMMANDS_EDIT.end(); 
			++iter) {
		if(_userCommand == *iter) {
			return true;
		}
	}
	return false;
}

bool CommandCreator::isLoadCommand(void) {
	for(auto iter = COMMANDS_LOAD.begin(); 
			iter != COMMANDS_LOAD.end(); 
			++iter) {
		if(_userCommand == *iter) {
			return true;
		}
	}
	return false;
}

bool CommandCreator::isRedoCommand(void) {
	for(auto iter = COMMANDS_REDO.begin(); 
			iter != COMMANDS_REDO.end(); 
			++iter) {
		if(_userCommand == *iter) {
			return true;
		}
	}
	return false;
}

bool CommandCreator::isSearchCommand(void) {
	for(auto iter = COMMANDS_SEARCH.begin(); 
			iter != COMMANDS_SEARCH.end(); 
			++iter) {
		if(_userCommand == *iter) {
			return true;
		}
	}
	return false;
}

bool CommandCreator::isUndoCommand(void) {
	for(auto iter = COMMANDS_UNDO.begin(); 
			iter != COMMANDS_UNDO.end(); 
			++iter) {
		if(_userCommand == *iter) {
			return true;
		}
	}
	return false;
}

Command* CommandCreator::createAddCommand(void) {
	Command* addCommand = new CommandAdd;
	addCommand->setParsedStatus(true);

	DetailsParser details(_userInput);
	details.addNewTask(addCommand);
	return addCommand;
}

Command* CommandCreator::createClearCommand(void) {
	Command* clearCommand = new CommandClear;
	clearCommand->setParsedStatus(CommandCreator::hasNoParameters());

	if(!clearCommand->getParsedStatus()) {
		clearCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_CLEAR);
	}
	return clearCommand;
}

Command* CommandCreator::createDeleteCommand(void) {
	Command* deleteCommand = new CommandDelete;
	deleteCommand->setParsedStatus(CommandCreator::hasParameters());

	if(deleteCommand->getParsedStatus()) {
		DetailsParser details(CommandCreator::getParameters());
		details.deleteExistingTask(deleteCommand);
	} else {
		deleteCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_DELETE);
	}
	return deleteCommand;
}

Command* CommandCreator::createDoneCommand(void) {
	Command* doneCommand = new CommandDone;
	doneCommand->setParsedStatus(CommandCreator::hasParameters());

	if(doneCommand->getParsedStatus()) {
		DetailsParser details(CommandCreator::getParameters());
		details.markTaskAsDone(doneCommand);
	} else {
		doneCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_DONE);
	}
	return doneCommand;
}

Command* CommandCreator::createEditCommand(void) {
	Command* editCommand = new CommandEdit;
	editCommand->setParsedStatus(CommandCreator::hasParameters());

	if(editCommand->getParsedStatus()) {
		DetailsParser details(CommandCreator::getParameters());
		details.editExistingTask(editCommand);
	} else {
		editCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_EDIT);
	}
	return editCommand;
}

Command* CommandCreator::createLoadCommand(void) {
	Command* loadCommand = new CommandLoad;
	loadCommand->setParsedStatus(CommandCreator::hasNoParameters());

	if(!loadCommand->getParsedStatus()) {
		loadCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_LOAD);
	}
	return loadCommand;
}

Command* CommandCreator::createRedoCommand(void) {
	Command* redoCommand = new CommandRedo;
	redoCommand->setParsedStatus(CommandCreator::hasNoParameters());
	
	if(!redoCommand->getParsedStatus()) {
		redoCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_CLEAR);
	}
	return redoCommand;
}

Command* CommandCreator::createSearchCommand(void) {
	Command* searchCommand = new CommandSearch;
	searchCommand->setParsedStatus(CommandCreator::hasParameters());

	if(searchCommand->getParsedStatus()) {
		DetailsParser details(CommandCreator::getParameters());
		details.searchForTask(searchCommand);
	} else {
		searchCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_SEARCH);
	}
	return searchCommand;
}

Command* CommandCreator::createUndoCommand(void) {
	Command* undoCommand = new CommandUndo;
	undoCommand->setParsedStatus(CommandCreator::hasNoParameters());
		
	if(!undoCommand->getParsedStatus()) {
		undoCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_CLEAR);
	}
	return undoCommand;
}