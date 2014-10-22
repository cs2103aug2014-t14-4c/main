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
		LogicParserCommandCreator commandCreator;

		Command* command = commandCreator.createCommand(userInput);
		return command;
	} catch(const std::invalid_argument& e) {
		Command* command = new CommandAdd;

		command->setParsedStatus(false);
		command->setUserMessage(e.what());
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
