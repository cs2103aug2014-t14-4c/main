#pragma once
#include <string>
#include "Command.h"
using namespace std;

class LogicParserExecutor {
	public:
		LogicParserExecutor(void);
		Command getCommandFromUserInput(string commandLineInput);

	private:

};

