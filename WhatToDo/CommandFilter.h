#pragma once

#include "Command.h"
#include "boost\date_time.hpp"

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

class CommandFilter: public Command {
	public:
		CommandFilter(void);
		void execute();

	protected:
		// CommandFilter Functions For Execution

		void performFilterOperation();

		// All Static Constants And Variables

		static string LOGGING_MSG_EXECUTE_COMMAND_FILTER;
};

