//@author A0110655N
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
	} else if(isUndoneCommand()) {
		command = createUndoneCommand();
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
	if(_userCommand == COMMAND_CLEAR) {
			return true;
	}
	return false;
}

bool CommandCreator::isDeleteCommand(void) {
	if(_userCommand == COMMAND_DELETE) {
			return true;
	}
	return false;
}

bool CommandCreator::isDoneCommand(void) {
	if(_userCommand == COMMAND_DONE) {
			return true;
	}
	return false;
}

bool CommandCreator::isEditCommand(void) {
	if(_userCommand == COMMAND_EDIT) {
			return true;
	}
	return false;
}

bool CommandCreator::isFilterCommand(void) {
	if(_userCommand == COMMAND_FILTER) {
			return true;
	}
	return false;
}

bool CommandCreator::isLoadCommand(void) {
	if(_userCommand == COMMAND_LOAD) {
			return true;
	}
	return false;
}

bool CommandCreator::isRedoCommand(void) {
	if(_userCommand == COMMAND_REDO) {
			return true;
	}
	return false;
}

bool CommandCreator::isSearchCommand(void) {
	if(_userCommand == COMMAND_SEARCH) {
			return true;
	}
	return false;
}

bool CommandCreator::isUndoCommand(void) {
	if(_userCommand == COMMAND_UNDO) {
			return true;
	}
	return false;
}

bool CommandCreator::isUndoneCommand(void) {
	if(_userCommand == COMMAND_UNDONE) {
			return true;
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

Command* CommandCreator::createUndoneCommand(void) {
	Command* undoneCommand = new CommandDone;
	undoneCommand->setParsedStatus(hasParameters());

	if(undoneCommand->getParsedStatus()) {
		DetailsParser details(getParameters());
		details.markTaskAsUndone(undoneCommand);
	} else {
		undoneCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_UNDONE);
	}
	return undoneCommand;
}