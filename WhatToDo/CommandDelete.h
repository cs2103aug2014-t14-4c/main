#pragma once

#include "Command.h"

using namespace std;

class CommandDelete: public Command {
	public:
		CommandDelete(void);
		void execute();

	protected:
		
		// CommandDelete Functions For Execution

		void performDeleteOperation();

		// All Static Constants And Variables

		static string LOGGING_MSG_EXECUTE_COMMAND_DELETE;
		static string LOGGING_MSG_PERFORM_DELETE;
		static string ACTION_MSG_DELETED;
};

