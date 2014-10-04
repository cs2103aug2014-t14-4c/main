#include "LogicParser.h"

LogicParser::LogicParser(void) {
}

Command* LogicParser::getCommandFromUserInput(std::string userInput) {
	LogicParser::setUserInput(userInput);

	Command* command = LogicParser::createCommand();

	return command;
}

void LogicParser::setUserInput(std::string userInput) {
	_userInput = userInput;
}

Command* LogicParser::createCommand() {
	string userCommand = LogicParser::getUserCommand();
	Command* command = NULL;

	if(userCommand == COMMAND_CLEAR) {
		command = LogicParser::createClearCommand();
	} else if(userCommand == COMMAND_DELETE) {
		command = LogicParser::createDeleteCommand();	
	} else if(userCommand == COMMAND_DONE) {
		command = LogicParser::createDoneCommand();
	} else if(userCommand == COMMAND_EDIT) {
		command = LogicParser::createEditCommand();
	} else if(userCommand == COMMAND_LOAD) {
		command = LogicParser::createLoadCommand();
	} else if(userCommand == COMMAND_REDO) {
		command = LogicParser::createRedoCommand();
	} else if(userCommand == COMMAND_SEARCH) {
		command = LogicParser::createSearchCommand();
	} else if(userCommand == COMMAND_UNDO) {
		command = LogicParser::createUndoCommand();
	} else {
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
		LogicParser::addTaskDetails(addCommand);
	}

	return addCommand;
}

Command* LogicParser::createEditCommand() {
	Command* editCommand = new CommandEdit;
	editCommand->setParsedStatus(LogicParser::isValidCommandWithStringParameters());

	if(editCommand->getParsedStatus()) {
		LogicParser::addTaskIndex(editCommand);
		LogicParser::removeEditIndex();
		LogicParser::addTaskDetails(editCommand);
	}

	return editCommand;
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

void LogicParser::addTaskIndex(Command* command) {
	int taskIndex = 0;
	std::istringstream iss(_userInput);

	iss >> taskIndex;
	command->setTaskIndex(taskIndex);
}

void LogicParser::removeEditIndex() {
	_userInput = LogicParser::removeFirstWord(_userInput);
}

void LogicParser::addTaskDetails(Command* command) {
	std::string taskParameters = LogicParser::getParameters(_userInput);
	Task* task = new Task;

	LogicParser::addTaskTags(task, taskParameters);
	LogicParser::addTaskDateTime(task, taskParameters);
	LogicParser::addTaskName(task, taskParameters);
}

void LogicParser::addTaskTags(Task* task, std::string& taskParameters) {
	std::vector<std::string> taskTags;
	std::istringstream iss(taskParameters);
	std::string currentWord;
	taskParameters = "";

	while(iss >> currentWord) {
		if(LogicParser::isTag(currentWord)) {
			taskTags.push_back(currentWord);
		} else {
			taskParameters += currentWord + " ";
		}
	}

	task->setTaskTags(taskTags);
}

bool LogicParser::isTag(std::string word) {
	return (word.find_first_of(IDENTIFIER_TAG) == 0);
}

void LogicParser::addTaskDateTime(Task* task, std::string& taskParameters) {
	std::istringstream iss(taskParameters);
	std::string currentWord;
	boost::posix_time::ptime currentTime(second_clock::local_time());
	boost::posix_time::ptime startDateTime;
	boost::posix_time::ptime endDateTime;
	boost::posix_time::ptime deadline;


	taskParameters = "";

	while(iss >> currentWord) {
		if(LogicParser::isDateTimeIdentifier(currentWord)) {
			switch (LogicParser::determineDateTimeType(currentWord)) {
			case AT:
			case FROM:
			case ON:
				for(size_t i = 0; i < formats_n; i++) {
					iss.imbue(formats[i]);
					iss >> startDateTime;
					if(startDateTime != boost::posix_time::ptime()) {
						break;
				    }
				}
			case TO:
				for(size_t i = 0; i < formats_n; i++) {
					iss.imbue(formats[i]);
					iss >> endDateTime;
					if(endDateTime != boost::posix_time::ptime()) {
						break;
				    }
				}
			case BY:
				for(size_t i = 0; i < formats_n; i++) {
					iss.imbue(formats[i]);
					iss >> deadline;
					if(deadline != boost::posix_time::ptime()) {
						break;
				    }
				}
			case INVALID:
				taskParameters += currentWord + " ";
			}
		} else {
			taskParameters += currentWord + " ";
		}
	}

}

bool LogicParser::isDateTimeIdentifier(std::string word) {
	return (word.find_first_of(IDENTIFIER_DATETIME) == 0);

}

LogicParser::DateTimeType LogicParser::determineDateTimeType(std::string word) {
	word = LogicParser::transformToLowercase(word);

	if (word == IDENTIFIER_DATETIME_AT) {
		return LogicParser::DateTimeType::AT;
	} else if (word == IDENTIFIER_DATETIME_BY) {
		return LogicParser::DateTimeType::BY;
	} else if (word == IDENTIFIER_DATETIME_ON) {
		return LogicParser::DateTimeType::ON;
	} else if (word == IDENTIFIER_DATETIME_FROM) {
		return LogicParser::DateTimeType::FROM;
	} else if (word == IDENTIFIER_DATETIME_TO) {
		return LogicParser::DateTimeType::TO;
	} else {
		return LogicParser::DateTimeType::INVALID;
	}
}

void LogicParser::addTaskName(Task* task, std::string taskParameters) {
	task->setTaskName(LogicParser::trimWhiteSpace(taskParameters));
}

Command* LogicParser::createDeleteCommand() {
	Command* deleteCommand = new CommandDelete;
	deleteCommand->setParsedStatus(LogicParser::isValidCommandWithIndexParameters());

	if(deleteCommand->getParsedStatus()) {
		LogicParser::addTaskIndex(deleteCommand);
	}

	return deleteCommand;
}

Command* LogicParser::createDoneCommand() {
	Command* doneCommand = new CommandDone;
	doneCommand->setParsedStatus(LogicParser::isValidCommandWithIndexParameters());

	if(doneCommand->getParsedStatus()) {
		LogicParser::addTaskIndex(doneCommand);
	}

	return doneCommand;
}

Command* LogicParser::createClearCommand() {
	Command* clearCommand = new CommandClear;
	clearCommand->setParsedStatus(LogicParser::isValidCommandWithNoParameters());

	return clearCommand;
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
	} else {
		std::string parameters = LogicParser::getParameters(_userInput);
		return std::all_of(parameters.begin(), parameters.end(), isdigit);
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
	std::transform(text.begin(), text.end(), text.begin(), tolower);
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

std::vector<std::string> LogicParser::splitWordsIntoVector(std::string text) {
	std::vector<std::string> taskParameters;
	std::istringstream iss(text);
	std::string currentWord;
	
	while(iss >> currentWord) {
			taskParameters.push_back(currentWord);
	}

	return taskParameters;
}