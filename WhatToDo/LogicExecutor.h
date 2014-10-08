#pragma once
#include "State.h"
#include "Task.h"
#include "LogicParser.h"
#include "Command.h"
using namespace std;

class LogicExecutor {
	public:
		LogicExecutor(void);
		static State getNewState(string commandLineInput);

	private:

};

