#include "LogicParser.h"

LogicParser::LogicParser(void) {
}

LogicParser::~LogicParser(void) {
}

Command* LogicParser::getCommandFromUserInput(std::string userInput) {
	try {
		if(LogicParser::isEmptyInput(userInput)) {
			throw std::invalid_argument(EMPTY_STRING);
		}
		CommandCreator cmdCreator;
		Command* command = cmdCreator.createCommand(userInput);
		return command;
	} catch(...) {
		Command* command = new CommandAdd;

		command->setParsedStatus(false);
		return command;
	}
}

bool LogicParser::isEmptyInput(std::string userInput) {
	return (userInput.empty() 
		|| userInput.find_first_not_of(WHITESPACE_DELIMITERS) == std::string::npos);
}