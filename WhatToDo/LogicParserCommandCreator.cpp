#include "LogicParserCommandCreator.h"

LogicParserCommandCreator::LogicParserCommandCreator(void) {
}

void LogicParserCommandCreator::setUserInput(std::string userInput) {
	_userInput = userInput;
}

Command* LogicParserCommandCreator::createCommand(std::string userInput) {
	LogicParserCommandCreator::setUserInput(userInput);
	string userCommand = LogicParserCommandCreator::getUserCommand();
	Command* command = NULL;

	if(userCommand == COMMAND_CLEAR) {
		command = LogicParserCommandCreator::createClearCommand();
	} else if(userCommand == COMMAND_DELETE) {
		command = LogicParserCommandCreator::createDeleteCommand();	
	} else if(userCommand == COMMAND_DONE) {
		command = LogicParserCommandCreator::createDoneCommand();
	} else if(userCommand == COMMAND_EDIT) {
		command = LogicParserCommandCreator::createEditCommand();
	} else if(userCommand == COMMAND_LOAD) {
		command = LogicParserCommandCreator::createLoadCommand();
	} else if(userCommand == COMMAND_REDO) {
		command = LogicParserCommandCreator::createRedoCommand();
	} else if(userCommand == COMMAND_SEARCH) {
		command = LogicParserCommandCreator::createSearchCommand();
	} else if(userCommand == COMMAND_UNDO) {
		command = LogicParserCommandCreator::createUndoCommand();
	} else {
		command = LogicParserCommandCreator::createAddCommand();
	}

	return command;
}

std::string LogicParserCommandCreator::getUserCommand(void) {
	LogicParserStringModifier stringMod;
	return stringMod.transformToLowercase(stringMod.getFirstWord(_userInput));
}

std::string LogicParserCommandCreator::getParameters(void) {
	LogicParserStringModifier stringMod;
	return stringMod.getStringExceptFirstWord(_userInput);
}

Command* LogicParserCommandCreator::createAddCommand(void) {
	Command* addCommand = new CommandAdd;
	addCommand->setParsedStatus(true);

	if(addCommand->getParsedStatus()) {
		LogicParserCommandDetailsParser detailsParser(_userInput);
		detailsParser.addNewTask(addCommand);
	}

	return addCommand;
}

Command* LogicParserCommandCreator::createClearCommand(void) {
	Command* clearCommand = new CommandClear;
	clearCommand->setParsedStatus(LogicParserCommandCreator::isValidCommandWithNoParameters());

	return clearCommand;
}

Command* LogicParserCommandCreator::createDeleteCommand(void) {
	Command* deleteCommand = new CommandDelete;
	deleteCommand->setParsedStatus(LogicParserCommandCreator::isValidCommandWithIndexParameters());

	if(deleteCommand->getParsedStatus()) {
		LogicParserCommandDetailsParser detailsParser(LogicParserCommandCreator::getParameters());
		detailsParser.setTaskIndex(deleteCommand);
	}

	return deleteCommand;
}

Command* LogicParserCommandCreator::createDoneCommand(void) {
	Command* doneCommand = new CommandDone;
	doneCommand->setParsedStatus(LogicParserCommandCreator::isValidCommandWithIndexParameters());

	if(doneCommand->getParsedStatus()) {
		LogicParserCommandDetailsParser detailsParser(LogicParserCommandCreator::getParameters());
		detailsParser.setTaskIndex(doneCommand);
	}

	return doneCommand;
}

Command* LogicParserCommandCreator::createEditCommand(void) {
	Command* editCommand = new CommandEdit;
	editCommand->setParsedStatus(LogicParserCommandCreator::isValidCommandWithStringParameters());

	if(editCommand->getParsedStatus()) {
		LogicParserCommandDetailsParser detailsParser(LogicParserCommandCreator::getParameters());
		detailsParser.editExistingTask(editCommand);
	}

	return editCommand;
}

Command* LogicParserCommandCreator::createLoadCommand(void) {
	Command* loadCommand = new CommandLoad;
	loadCommand->setParsedStatus(LogicParserCommandCreator::isValidCommandWithNoParameters());

	return loadCommand;
}

Command* LogicParserCommandCreator::createRedoCommand(void) {
	Command* redoCommand = new CommandRedo;
	redoCommand->setParsedStatus(LogicParserCommandCreator::isValidCommandWithNoParameters());

	return redoCommand;
}

Command* LogicParserCommandCreator::createSearchCommand(void) {
	Command* searchCommand = new CommandSearch;
	searchCommand->setParsedStatus(LogicParserCommandCreator::isValidCommandWithStringParameters());

	if(searchCommand->getParsedStatus()) {
		LogicParserCommandDetailsParser detailsParser(LogicParserCommandCreator::getParameters());
		detailsParser.setSearchKeyword(searchCommand);
	}

	return searchCommand;
}

Command* LogicParserCommandCreator::createUndoCommand(void) {
	Command* undoCommand = new CommandUndo;
	undoCommand->setParsedStatus(LogicParserCommandCreator::isValidCommandWithNoParameters());

	return undoCommand;
}

bool LogicParserCommandCreator::isValidCommandWithStringParameters(void) {
	LogicParserStringModifier stringMod;
	return !stringMod.isOneWord(_userInput);
}

bool LogicParserCommandCreator::isValidCommandWithIndexParameters(void) {
	LogicParserStringModifier stringMod;
	if(stringMod.isOneWord(_userInput)) {
		return false;
	} else {
		std::string parameters = LogicParserCommandCreator::getParameters();
		return std::all_of(parameters.begin(), parameters.end(), isdigit);
	}
}

bool LogicParserCommandCreator::isValidCommandWithNoParameters(void) {
	LogicParserStringModifier stringMod;
	return stringMod.isOneWord(_userInput);
}