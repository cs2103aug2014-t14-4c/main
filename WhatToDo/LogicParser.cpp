#include "LogicParser.h"

LogicParser::LogicParser(void) {
}

void LogicParser::setUserInput(std::string userInput) {
	_userInput = userInput;
}

std::string LogicParser::getUserInput(void) {
	return _userInput;
}

Command* LogicParser::getCommandFromUserInput(std::string userInput) {
	LogicParser::setUserInput(userInput);

	Command* command = LogicParser::createCommand();

	return command;
}

Command* LogicParser::createCommand() {
	string userCommand = LogicParser::getUserCommand();
	Command* command = NULL;

	if(userCommand == "/delete") {
		command = LogicParser::createDeleteCommand();	
	}
	else if(userCommand == "/display") {
		command = LogicParser::createDisplayCommand();
	}
	else if(userCommand == "/edit") {
		command = LogicParser::createEditCommand();
	}
	else if(userCommand == "/load") {
		command = LogicParser::createLoadCommand();
	}
	else if(userCommand == "/redo") {
		command = LogicParser::createRedoCommand();
	}
	else if(userCommand == "/search") {
		command = LogicParser::createSearchCommand();
	}
	else if(userCommand == "/undo") {
		command = LogicParser::createUndoCommand();
	}
	else {
		command = LogicParser::createAddCommand();
	}

	return command;
}

std::string LogicParser::getUserCommand(void) {
	return LogicParser::transformToLowercase(LogicParser::getFirstWord(_userInput));
}

Command* LogicParser::createAddCommand() {
	Command* addCommand = new CommandAdd;
	addCommand->setParsedStatus(LogicParser::isValidCommandWithStringParameters());

	if(addCommand->getParsedStatus()) {
		LogicParser::createAddCommandDetails(addCommand);
	}

	return addCommand;
}

void LogicParser::createAddCommandDetails(Command* addCommand) {
	std::string taskParameters = LogicParser::getParameters(_userInput);
	Task* task = new Task;

	LogicParser::addTaskTags(task, taskParameters);
	LogicParser::addTaskDateTime(task, taskParameters);
	LogicParser::addTaskName(task, taskParameters);
}

void LogicParser::addTaskTags(Task* task, std::string taskParameters) {
	std::vector<std::string> taskTags;
	std::istringstream iss(taskParameters);
	std::string currentToken;

	while(iss >> currentToken) {
		if(LogicParser::isTag(currentToken)) {
			taskTags.push_back(currentToken);
		}
	}

	task->setTaskTags(taskTags);
}

bool LogicParser::isTag(std::string word) {
	return (word.find_first_of("@#") == 0);
}

void LogicParser::addTaskDateTime(Task* task, std::string taskParameters) {
}
void LogicParser::addTaskName(Task* task, std::string taskParameters) {
}

Command* LogicParser::createDeleteCommand() {
	Command* deleteCommand = new CommandDelete;
	deleteCommand->setParsedStatus(LogicParser::isValidCommandWithIndexParameters());

	if(deleteCommand->getParsedStatus()) {
		int index = std::stoi(LogicParser::getParameters(_userInput));
		deleteCommand->setTaskIndex(index);
	}

	return deleteCommand;
}

Command* LogicParser::createDisplayCommand() {
	Command* displayCommand = new CommandDisplay;
	displayCommand->setParsedStatus(LogicParser::isValidCommandWithNoParameters());

	return displayCommand;
}

Command* LogicParser::createEditCommand() {
	Command* editCommand = new CommandEdit;
	editCommand->setParsedStatus(LogicParser::isValidCommandWithIndexParameters());

	if(editCommand->getParsedStatus()) {
		int index = std::stoi(LogicParser::getParameters(_userInput));
		editCommand->setTaskIndex(index);
	}

	return editCommand;
}

Command* LogicParser::createLoadCommand() {
	Command* loadCommand = new CommandLoad;
	loadCommand->setParsedStatus(LogicParser::isValidCommandWithNoParameters());

	return loadCommand;
}

Command* LogicParser::createRedoCommand() {
	Command* redoCommand = new CommandRedo;
	redoCommand->setParsedStatus(LogicParser::isValidCommandWithNoParameters());

	return redoCommand;
}

Command* LogicParser::createSearchCommand() {
	Command* searchCommand = new CommandSearch;
	searchCommand->setParsedStatus(LogicParser::isValidCommandWithStringParameters());

	if(searchCommand->getParsedStatus()) {
		std::string searchString = LogicParser::getParameters(_userInput);
		searchCommand->setSearchKeyword(searchString);
	}

	return searchCommand;
}

Command* LogicParser::createUndoCommand() {
	Command* undoCommand = new CommandUndo;
	undoCommand->setParsedStatus(LogicParser::isValidCommandWithNoParameters());

	return undoCommand;
}

bool LogicParser::isValidCommandWithStringParameters() {
	return !LogicParser::isOneWord(_userInput);
}

bool LogicParser::isValidCommandWithIndexParameters() {
	if(LogicParser::isOneWord(_userInput)) {
		return false;
	}
	else {
		std::string parameters = LogicParser::getParameters(_userInput);
		return std::all_of(parameters.begin(), parameters.end(), ::isdigit);
	}
}

bool LogicParser::isValidCommandWithNoParameters() {
	return LogicParser::isOneWord(_userInput);
}

std::string LogicParser::getFirstWord(std::string text, const std::string& delimiters) {
	text = LogicParser::trimWhiteSpace(text);
	return text.substr(0, text.find_first_of(delimiters));
}

std::string LogicParser::getParameters(std::string text, const std::string& delimiters) {
	text = LogicParser::trimWhiteSpace(LogicParser::removeFirstWord(text));
	return text.substr(text.find_first_not_of(delimiters));
}

std::string LogicParser::removeFirstWord(std::string text, const std::string& delimiters) {
	text = LogicParser::trimWhiteSpace(text);
	return text.substr(text.find_first_of(delimiters), text.find_last_not_of(delimiters) + 1);
}

std::string LogicParser::transformToLowercase(std::string text) {
	std::transform(text.begin(), text.end(), text.begin(), ::tolower);
	return text;
}

bool LogicParser::isOneWord(std::string text) {
	text = LogicParser::trimWhiteSpace(text);
	return (std::all_of(text.begin(), text.end(), isalnum));
}

std::string LogicParser::trimWhiteSpace(const std::string& text) {
	return LogicParser::trimLeft(LogicParser::trimRight(text));
}

std::string LogicParser::trimLeft(const std::string& text, const std::string& delimiters) {
	return text.substr(text.find_first_not_of(delimiters));
}

std::string LogicParser::trimRight(const std::string& text, const std::string& delimiters) {
	return text.substr(0, text.find_last_not_of(delimiters) + 1);
}
