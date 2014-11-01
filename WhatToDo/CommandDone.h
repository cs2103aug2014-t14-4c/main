#pragma once

#include "Command.h"

using namespace std;

class CommandDone: public Command {
	public:
		CommandDone(void);
		void execute();

	private:

		// CommandDone Functions For Execution

		void performDoneOperation();

		// All Static Constants And Variables

		static string LOGGING_MSG_EXECUTE_COMMAND_DONE;
		static string LOGGING_MSG_PERFORM_DONE;
		static string ACTION_MSG_DONE;
};

