//****************************************************************************
//@author A0110648L
//
// This is the concrete CommandAdd class, which is reponsible for executing 
// an "add" command specified by the user.
//
// It works by (i) checking for the validity of the command; (ii) retrieving 
// the current state from LogicData; (iii) performing the add operation;
// (iv) rewriting the current and view states in LogicData; and (v) adding 
// itself to LogicData's command history.
//
// If the command is invalid either due to (i) a false parsed status indicating
// it has been parsed incorrectly; or (ii) incorrect date orderings, an error 
// message will be added to the current state to be shown to the user eventually.
//
//****************************************************************************

#pragma once

#include "Command.h"
#include "boost\date_time.hpp"

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

const string MSG_LOGGING_EXECUTE_COMMAND_ADD = 
	"\nCommand Add Initiated:\n";
const string MSG_LOGGING_IS_ORDER_DATETIMES_VALD = 
	"Function called: checkIsCommandValid(): isOrderOfDateTimesValid"
	": %s\n";
const string MSG_LOGGING_IS_INPUT_TIME_ALR_OCCUPIED = 
	"Function called: checkIsCommandValid(): isInputTimeAlreadyOccup"
	"ied: %s\n";
const string MSG_LOGGING_IS_COMMAND_VALID = 
	"Function called: checkIsCommandValid(): _isCommandValid: %s\n";
const string MSG_LOGGING_PERFORM_ADD = 
	"Function called: performAddOperation()\n";

const string MSG_ERROR_ENDTIME_BEFORE_STARTTIME = 
	"The end time cannot be before the start time!";
const string MSG_USER_INPUT_TIME_OCCUPIED = 
	"Task Added! Note: Beware task overlap!";
const string MSG_ACTION_ADDED = "Task Added!";

class CommandAdd: public Command {
	public:
		CommandAdd(void);

		/*
		// This API function executes the Add Command when called.
		//
		// Pre-conditions:
		//     (i) There should be a proper task set as the current
		//     task in the command instance before execute is called.
		//     (ii) The _isParsedCorrectly variable in the command 
		//     should be true.
		//
		// Post-Conditions:
		//     (i) The specified task will be added to LogicData unless
		//     there are logic errors with the task (such as if the
		//     specified task start time is after the end time)
		//
		// Sample usage:
		//     CommandAdd* anAddCommand = new CommandAdd;
		//     anAddCommand->setCurrentTask(taskToAdd);
		//     anAddCommand->execute();
		*/

		void execute();

	protected:

		// Functions For Execution

		bool checkIsCommandValid();
		void performAddOperation();

		// These functions check for the validity of the add 
		// operation. If there are serious logic errors with the
		// specified command, the add operation will not be completed
		// and errors will be written into the state. If there are 
		// warnings then the add operation will be completed but these
		// warnings will still be written into the state (to be shown
		// to the user eventually.

		bool checkIfOrderOfDateTimesValid();
		bool checkIsInputTimeNotOccupied();
		bool checkIsEndAfterStart();

};

