#pragma once

#include "Command.h"
#include "LogicParserCommandCreator.h"

class LogicParser {
	public:
		//Constructor
		LogicParser(void);
		//Gets the command with the parameters given by the user input.
		Command* getCommandFromUserInput(std::string userInput);
};
