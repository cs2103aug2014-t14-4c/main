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
	sprintf_s(logBuffer, LOG_CREATE_ADD.c_str());
	log(logBuffer);

	Command* addCommand = new CommandAdd;
	addCommand->setParsedStatus(true);

	DetailsParser details(_userInput);
	details.addNewTask(addCommand);
	return addCommand;
}

Command* CommandCreator::createClearCommand(void) {
	sprintf_s(logBuffer, LOG_CREATE_CLEAR.c_str());
	log(logBuffer);

	Command* clearCommand = new CommandClear;
	clearCommand->setParsedStatus(hasNoParameters());

	if(!clearCommand->getParsedStatus()) {
		clearCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_CLEAR);
		sprintf_s(logBuffer, LOG_ERROR_PARAMETER_NUMBER.c_str());
		log(logBuffer);
	}
	return clearCommand;
}

Command* CommandCreator::createDeleteCommand(void) {
	sprintf_s(logBuffer, LOG_CREATE_DELETE.c_str());
	log(logBuffer);

	Command* deleteCommand = new CommandDelete;
	deleteCommand->setParsedStatus(hasParameters());

	if(deleteCommand->getParsedStatus()) {
		DetailsParser details(getParameters());
		details.deleteExistingTask(deleteCommand);
	} else {
		deleteCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_DELETE);
		sprintf_s(logBuffer, LOG_ERROR_PARAMETER_NUMBER.c_str());
		log(logBuffer);
	}
	return deleteCommand;
}

Command* CommandCreator::createDoneCommand(void) {
	sprintf_s(logBuffer, LOG_CREATE_DONE.c_str());
	log(logBuffer);

	Command* doneCommand = new CommandDone;
	doneCommand->setParsedStatus(hasParameters());

	if(doneCommand->getParsedStatus()) {
		DetailsParser details(getParameters());
		details.markTaskAsDone(doneCommand);
	} else {
		doneCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_DONE);
		sprintf_s(logBuffer, LOG_ERROR_PARAMETER_NUMBER.c_str());
		log(logBuffer);
	}
	return doneCommand;
}

Command* CommandCreator::createEditCommand(void) {
	sprintf_s(logBuffer, LOG_CREATE_EDIT.c_str());
	log(logBuffer);

	Command* editCommand = new CommandEdit;
	editCommand->setParsedStatus(hasParameters());

	if(editCommand->getParsedStatus()) {
		DetailsParser details(getParameters());
		details.editExistingTask(editCommand);
	} else {
		editCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_EDIT);
		sprintf_s(logBuffer, LOG_ERROR_PARAMETER_NUMBER.c_str());
		log(logBuffer);
	}
	return editCommand;
}

Command* CommandCreator::createFilterCommand(void) {
	sprintf_s(logBuffer, LOG_CREATE_FILTER.c_str());
	log(logBuffer);

	Command* filterCommand = new CommandFilter;
	filterCommand->setParsedStatus(hasParameters());

	if(filterCommand->getParsedStatus()) {
		DetailsParser details(getParameters());
		details.filterExistingTasks(filterCommand);
	} else {
		filterCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_FILTER);
		sprintf_s(logBuffer, LOG_ERROR_PARAMETER_NUMBER.c_str());
		log(logBuffer);
	}
	return filterCommand;
}

Command* CommandCreator::createLoadCommand(void) {
	sprintf_s(logBuffer, LOG_CREATE_LOAD.c_str());
	log(logBuffer);

	Command* loadCommand = new CommandLoad;
	loadCommand->setParsedStatus(hasNoParameters());

	if(!loadCommand->getParsedStatus()) {
		loadCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_LOAD);
		sprintf_s(logBuffer, LOG_ERROR_PARAMETER_NUMBER.c_str());
		log(logBuffer);
	}
	return loadCommand;
}

Command* CommandCreator::createRedoCommand(void) {
	sprintf_s(logBuffer, LOG_CREATE_REDO.c_str());
	log(logBuffer);
	
	Command* redoCommand = new CommandRedo;
	redoCommand->setParsedStatus(hasNoParameters());
	
	if(!redoCommand->getParsedStatus()) {
		redoCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_REDO);
		sprintf_s(logBuffer, LOG_ERROR_PARAMETER_NUMBER.c_str());
		log(logBuffer);
	}
	return redoCommand;
}

Command* CommandCreator::createSearchCommand(void) {
	sprintf_s(logBuffer, LOG_CREATE_SEARCH.c_str());
	log(logBuffer);

	Command* searchCommand = new CommandSearch;
	searchCommand->setParsedStatus(hasParameters());

	if(searchCommand->getParsedStatus()) {
		DetailsParser details(getParameters());
		details.searchForTask(searchCommand);
	} else {
		searchCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_SEARCH);
		sprintf_s(logBuffer, LOG_ERROR_PARAMETER_NUMBER.c_str());
		log(logBuffer);
	}
	return searchCommand;
}

Command* CommandCreator::createUndoCommand(void) {
	sprintf_s(logBuffer, LOG_CREATE_UNDO.c_str());
	log(logBuffer);

	Command* undoCommand = new CommandUndo;
	undoCommand->setParsedStatus(hasNoParameters());
		
	if(!undoCommand->getParsedStatus()) {
		undoCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_UNDO);
		sprintf_s(logBuffer, LOG_ERROR_PARAMETER_NUMBER.c_str());
		log(logBuffer);
	}
	return undoCommand;
}

Command* CommandCreator::createUndoneCommand(void) {
	sprintf_s(logBuffer, LOG_CREATE_UNDONE.c_str());
	log(logBuffer);
	
	Command* undoneCommand = new CommandDone;
	undoneCommand->setParsedStatus(hasParameters());

	if(undoneCommand->getParsedStatus()) {
		DetailsParser details(getParameters());
		details.markTaskAsUndone(undoneCommand);
	} else {
		undoneCommand->setUserMessage(USERMESSAGE_INVALID_COMMAND_UNDONE);
		sprintf_s(logBuffer, LOG_ERROR_PARAMETER_NUMBER.c_str());
		log(logBuffer);
	}
	return undoneCommand;
}