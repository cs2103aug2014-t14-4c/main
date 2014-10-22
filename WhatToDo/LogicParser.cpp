#include "LogicParser.h"

LogicParser::LogicParser(void) {
}


LogicParser::~LogicParser(void) {
}

Command* LogicParser::getCommandFromUserInput(std::string userInput) {
	try {
		if(LogicParser::isEmptyInput(userInput)) {
			throw std::invalid_argument(USERMESSAGE_EMPTY_INPUT);
		}

		LogicParserCommandCreator commandCreator;
		Command* command = commandCreator.createCommand(userInput);

		return command;
	}
	catch(const std::invalid_argument& e) {
		Command* command = new CommandAdd;

		command->setParsedStatus(false);
		command->setUserMessage(e.what());

		return command;
	}
}

bool LogicParser::isEmptyInput(std::string userInput) {
	return (userInput.empty() || userInput.find_first_not_of(delimiters) == std::string::npos);
}
