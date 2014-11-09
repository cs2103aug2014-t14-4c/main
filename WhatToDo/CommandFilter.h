//****************************************************************************
//@author A0110648L
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
		
		/*
		// This API function executes the Filter Command when called.
		//
		// Pre-conditions:
		//     (i) The _isParsedCorrectly variable in the command 
		//     should be true.
		//
		// Post-Conditions:
		//     (i) The done, type, and date filters in LogicData will
		//     be changed according to the _doneFilter, _typeFilter, 
		//     _startDateFilter, and _endDateFilter values in the Command
		//     instance.
		//
		// Sample usage:
		//     CommandFilter* aFilterCommand = new CommandFilter;
		//     aFilterCommand->setDoneFilter(LogicData::DONE_BOTH);
		//     aFilterCommand->execute();
		*/
		
		void execute();

	protected:
		// Functions For Execution

		void performFilterOperation();
};

