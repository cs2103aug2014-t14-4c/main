#include "LogicParserCommandCreator.h"

CommandCreator::CommandCreator(void) {
}

CommandCreator::~CommandCreator(void) {
}

Command* CommandCreator::createCommand(string userInput) {
	assert(!userInput.empty());

	setUserInput(userInput);
	Command* command = NULL;

	if(isClearCommand()) {
		command = createClearCommand();
	} else if(isDeleteCommand()) {
		command = createDeleteCommand();	
	} else if(isDoneCommand()) {
		command = createDoneCommand();
	} else if(isEditCommand()) {
		command = createEditCommand();
	} else if(isFilterCommand()) {
		command = createFilterCommand();
	} else if(isLoadCommand()) {
		command = createLoadCommand();
	} else if(isRedoCommand()) {
		command = createRedoCommand();
	} else if(isSearchCommand()) {
		command = createSearchCommand();
	} else if(isUndoCommand()) {
		command = createUndoCommand();
	} else {
		command = createAddCommand();
	}
	return command;
}

void CommandCreator::setUserInput(string userInput) {
	_userInput = userInput;
	_userCommand = getUserCommand();
}

string CommandCreator::getUserCommand(void) {
	return transformToLowercase(getFirstWord(_userInput));
}

string CommandCreator::getParameters(void) {
	return getExceptFirstWord(_userInput);
}

bool CommandCreator::hasParameters(void) {
	return !isOneWord(_userInput);
}

bool CommandCreator::hasNoParameters(void) {
	return isOneWord(_userInput);
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

bool CommandCreator::isFilterCommand(void) {
	for(auto iter = COMMANDS_FILTER.begin();
			iter != COMMANDS_FILTER.end();
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
	clearCommand->setParsedStatus(hasNoParameters());

	if(!clearCommand->getParsedStatus()) {
		clearCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_CLEAR);
	}
	return clearCommand;
}

Command* CommandCreator::createDeleteCommand(void) {
	Command* deleteCommand = new CommandDelete;
	deleteCommand->setParsedStatus(hasParameters());

	if(deleteCommand->getParsedStatus()) {
		DetailsParser details(getParameters());
		details.deleteExistingTask(deleteCommand);
	} else {
		deleteCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_DELETE);
	}
	return deleteCommand;
}

Command* CommandCreator::createDoneCommand(void) {
	Command* doneCommand = new CommandDone;
	doneCommand->setParsedStatus(hasParameters());

	if(doneCommand->getParsedStatus()) {
		DetailsParser details(getParameters());
		details.markTaskAsDone(doneCommand);
	} else {
		doneCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_DONE);
	}
	return doneCommand;
}

Command* CommandCreator::createEditCommand(void) {
	Command* editCommand = new CommandEdit;
	editCommand->setParsedStatus(hasParameters());

	if(editCommand->getParsedStatus()) {
		DetailsParser details(getParameters());
		details.editExistingTask(editCommand);
	} else {
		editCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_EDIT);
	}
	return editCommand;
}

Command* CommandCreator::createFilterCommand(void) {
	Command* filterCommand = new CommandFilter;
	filterCommand->setParsedStatus(hasParameters());

	if(filterCommand->getParsedStatus()) {
		DetailsParser details(getParameters());
		details.filterExistingTasks(filterCommand);
	} else {
		filterCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_FILTER);
	}
	return filterCommand;
}

Command* CommandCreator::createLoadCommand(void) {
	Command* loadCommand = new CommandLoad;
	loadCommand->setParsedStatus(hasNoParameters());

	if(!loadCommand->getParsedStatus()) {
		loadCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_LOAD);
	}
	return loadCommand;
}

Command* CommandCreator::createRedoCommand(void) {
	Command* redoCommand = new CommandRedo;
	redoCommand->setParsedStatus(hasNoParameters());
	
	if(!redoCommand->getParsedStatus()) {
		redoCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_CLEAR);
	}
	return redoCommand;
}

Command* CommandCreator::createSearchCommand(void) {
	Command* searchCommand = new CommandSearch;
	searchCommand->setParsedStatus(hasParameters());

	if(searchCommand->getParsedStatus()) {
		DetailsParser details(getParameters());
		details.searchForTask(searchCommand);
	} else {
		searchCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_SEARCH);
	}
	return searchCommand;
}

Command* CommandCreator::createUndoCommand(void) {
	Command* undoCommand = new CommandUndo;
	undoCommand->setParsedStatus(hasNoParameters());
		
	if(!undoCommand->getParsedStatus()) {
		undoCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_CLEAR);
	}
	return undoCommand;
}