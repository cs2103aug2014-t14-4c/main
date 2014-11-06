//****************************************************************************
//@author A0110655N
//This is the interface class to the entire Parser component. When called with 
//the getCommandFromUserInput(string) method, it is guaranteed to return a 
//pointer to a concrete Command object (such as CommandAdd, CommandEdit, etc).
//
//If an error has occurred during the parsing of the string, the boolean field
//isParsedCorrectly of the Command pointer will be set to false. In the case
//of incorrect input, an appropriate message to the user will be set in the 
//userMessage field of the Command pointer.
//
//Sample usage:
//	LogicParser parser;
//	Command* command = parser.getCommandFromUserInput(string);
//	(...)command.execute();
//	delete command;
//****************************************************************************

#pragma once
#include "LogicParserCommandCreator.h"

using namespace std;

class LogicParser {
public:
	LogicParser(void);
	~LogicParser(void);

	Command* getCommandFromUserInput(string userInput);

private:
	bool isEmptyInput(string userInput);
};