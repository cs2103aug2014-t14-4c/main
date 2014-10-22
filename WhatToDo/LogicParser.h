#pragma once
#include "LogicParserCommandCreator.h"

const std::string USERMESSAGE_EMPTY_INPUT = "User input is empty";

class LogicParser {
public:
	LogicParser(void);
	~LogicParser(void);

	Command* getCommandFromUserInput(std::string userInput);
private:
	bool isEmptyInput(std::string userInput);
};

