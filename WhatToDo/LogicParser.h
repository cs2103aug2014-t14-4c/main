#pragma once
#include "LogicParserCommandCreator.h"
#include "Command.h"

class LogicParser {
	public:
		//Constructor
		LogicParser(void);
		//Interface to the parser.
		Command* getCommandFromUserInput(std::string userInput);
};

