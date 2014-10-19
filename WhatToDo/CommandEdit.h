#pragma once

#include "CommandAdd.h"

using namespace std;

class CommandEdit: public CommandAdd {
	public:
		CommandEdit(void);
		void execute();

	protected:
		
		// CommandEdit Functions For Execution

		void deleteExistingTask();

		// All Static Constants And Variables

		static string LOGGING_MSG_EXECUTE_COMMAND_EDIT;
		static string LOGGING_MSG_DELETE_EXISTING_TASK;
};

