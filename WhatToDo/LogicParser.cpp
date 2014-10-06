#include "LogicParser.h"

LogicParser::LogicParser(void) {
}

Command* LogicParser::getCommandFromUserInput(std::string userInput) {
	LogicParserCommandCreator commandCreator;

	Command* command = commandCreator.createCommand(userInput);

	return command;
}