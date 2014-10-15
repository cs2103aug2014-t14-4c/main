#include "LogicParser.h"

LogicParser::LogicParser(void) {
}

Command* LogicParser::getCommandFromUserInput(std::string userInput) {
	try {
		if(userInput.empty())
			throw "User input is empty";

		LogicParserCommandCreator commandCreator;
	
		Command* command = commandCreator.createCommand(userInput);

		return command;
		}

	catch(std::string error) {
		std::cout << error << std::endl;
	}
}