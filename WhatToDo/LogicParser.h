#pragma once
#include "LogicParserCommandCreator.h"

class LogicParser {
public:
	LogicParser(void);
	~LogicParser(void);

	Command* getCommandFromUserInput(std::string userInput);

private:
	bool isEmptyInput(std::string userInput);
};

