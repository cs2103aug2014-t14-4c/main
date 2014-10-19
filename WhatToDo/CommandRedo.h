#pragma once

#include "CommandUndo.h"

using namespace std;

class CommandRedo: public CommandUndo {
	public:
		CommandRedo(void);
		void execute();

	protected:

		// CommandRedo Functions For Execution

		bool checkIsCommandValid();
		
		// All Static Constants And Variables

		static string LOGGING_MSG_EXECUTE_COMMAND_REDO;
		static string LOGGING_MSG_CHECK_IS_COMMAND_VALID;

		static string ERROR_MSG_CANNOT_REDO_ANYMORE;
};

