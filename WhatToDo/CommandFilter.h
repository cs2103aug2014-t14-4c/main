#pragma once

#include "Command.h"
#include "boost\date_time.hpp"

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

enum Done{
	NOT_SET = -1, ALL, DONE, UNDONE
};

enum Type{
	NOT_SET = -1, ALL, TODO, AGENDA, FIXED, DUE
};

class CommandFilter: public Command {
	public:
		CommandFilter(void);
		void execute();
		void setDone(int doneFilter);
		void setType(int typeFilter);
		void setStartDate(date startDateFilter);
		void setEndDate(date endDateFilter);

	protected:
		int done;
		int type;
		date start;
		date end;
		// CommandAdd Functions For Execution

		void performFilterOperation();

		// All Static Constants And Variables

		static string LOGGING_MSG_EXECUTE_COMMAND_FILTER;
};

