#pragma once

#include "Command.h"
#include "boost\date_time.hpp"

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

class CommandAdd: public Command {
	public:
		CommandAdd(void);
		void execute();

	protected:

		// CommandAdd Functions For Execution

		bool checkIsCommandValid();
		void performAddOperation();

		bool checkIfEnteredDateTimesValid();
		bool checkIfOrderOfDateTimesValid();
		bool checkIsInputTimeNotOccupied();

		bool checkIsDateTimeValid(ptime dateTimeToCheck);
		bool checkIsDeadlineAfterCurrentTime();
		bool checkIsStartAfterCurrentTime();
		bool checkIsEndAfterStart();

		// All Static Constants And Variables

		static string LOGGING_MSG_EXECUTE_COMMAND_ADD;
		static string LOGGING_MSG_IS_ENTERED_DATETIMES_VALID;
		static string LOGGING_MSG_IS_ORDER_DATETIMES_VALD;
		static string LOGGING_MSG_IS_INPUT_TIME_ALR_OCCUPIED;
		static string LOGGING_MSG_IS_COMMAND_VALID;
		static string LOGGING_MSG_PERFORM_ADD;

		static string ERROR_MSG_DATETIME_INVALID;
		static string ERROR_MSG_DEADLINE_PASSED;
		static string ERROR_MSG_STARTTIME_PASSED;
		static string ERROR_MSG_ENDTIME_BEFORE_STARTTIME;
		static string ERROR_MSG_INPUT_TIME_OCCUPIED;


};

