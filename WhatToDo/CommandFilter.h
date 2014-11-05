//****************************************************************************
//@Poh Zhi Chao A0110648L
//
// This is the concrete CommandFilter class, which is reponsible for executing 
// an "filter" command specified by the user.
//
// It works by (i) checking for the validity of the command; (ii) altering the
// filter settings in LogicData so subsequent filters will be performed as 
// specified by the filter command parameters.
//
// If the command is invalid due to a false parsed status indicating
// it has been parsed incorrectly, an error message will be added to the
// current state to be shown to the user eventually.
//
//****************************************************************************

#pragma once

#include "Command.h"
#include "boost\date_time.hpp"

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

const string LOGGING_MSG_EXECUTE_COMMAND_FILTER = 
	"\nCommand Filter Initiated:\n";

class CommandFilter: public Command {
	public:
		CommandFilter(void);
		void execute();

	protected:
		// CommandFilter Functions For Execution

		void performFilterOperation();
};

