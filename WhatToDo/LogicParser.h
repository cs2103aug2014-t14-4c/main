#pragma once
#include "LogicParserCommandCreator.h"
#include "Command.h"

class LogicParser {
	public:
		//Constructor
		LogicParser(void);
		//This is the only thing you have to worry about.
		Command* getCommandFromUserInput(std::string userInput);
};

