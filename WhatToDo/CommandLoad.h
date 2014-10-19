#pragma once

#include "Command.h"

using namespace std;

class CommandLoad: public Command {
	public:
		CommandLoad(void);
		void execute();

	private:
		
		// CommandLoad Functions For Execution

		void loadLogicDataSettings();

		// All Static Constants And Variables

		static string LOGGING_MSG_EXECUTE_COMMAND_LOAD;
		static string LOGGING_MSG_LOAD_LOGIC_DATA_SETTINGS;
};

