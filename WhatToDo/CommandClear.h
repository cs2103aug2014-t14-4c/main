#pragma once

#include "Command.h"

using namespace std;

class CommandClear: public Command {
	public:
		CommandClear(void);
		void execute();

	protected:

		// All Static Constants And Variables

		static string LOGGING_MSG_EXECUTE_COMMAND_CLEAR;
};

