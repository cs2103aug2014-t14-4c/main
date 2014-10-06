#pragma once
#include "Command.h"
#include "LogicData.h"
#include "boost\date_time.hpp"
using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

class CommandAdd: public Command {
	public:
		CommandAdd(void);
		void execute();

	protected:
		bool checkIsCommandValid();
		void performAddOperation();
		void addUserMessageToCurrentState();
		bool checkIfEnteredDateTimesValid();
		bool checkIfOrderOfDateTimesValid();
		bool checkIsInputTimeNotOccupied();
		bool checkIsDateTimeValid(ptime dateTimeToCheck);
		bool checkIsDeadlineAfterCurrentTime();
		bool checkIsStartAfterCurrentTime();
		bool checkIsEndAfterStart();
};

