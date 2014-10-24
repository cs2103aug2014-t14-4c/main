#include "LogicParser.h"

LogicParser::LogicParser(void) {
}

LogicParser::~LogicParser(void) {
}

Command* LogicParser::getCommandFromUserInput(string userInput) {
	try {
		if(LogicParser::isEmptyInput(userInput)) {
			throw invalid_argument(EMPTY_STRING);
		}
		CommandCreator cmdCreator;
		Command* command = cmdCreator.createCommand(userInput);

		return command;
	} catch(const exception&) {
		Command* command = new CommandAdd;
		command->setParsedStatus(false);
		return command;
	}
}

bool LogicParser::isEmptyInput(string userInput) {
	return (userInput.empty() 
		|| userInput.find_first_not_of(WHITESPACE_CHAR) == string::npos);
}