//****************************************************************************
//@author A0110648L
//
// This is the concrete CommandDelete class, which is reponsible for executing 
// a "delete" command specified by the user.
//
// It works by (i) checking for the validity of the command; (ii) retrieving 
// the current state from LogicData; (iii) performing the delete operation;
// (iv) rewriting the current and view states in LogicData; and (v) adding 
// itself to LogicData's command history.
//
// If the command is invalid due to a false parsed status indicating
// it has been parsed incorrectly, an error message will be added to the 
// current state to be shown to the user eventually.
//
//****************************************************************************

#pragma once

#include "Command.h"

using namespace std;

const string LOGGING_MSG_EXECUTE_COMMAND_DELETE = 
	"\nCommand Delete Initiated:\n";
const string LOGGING_MSG_PERFORM_DELETE = 
	"Function called: performDeleteOperation(): _commandTaskIndex de"
	"leted: %s\n";
const string ACTION_MSG_DELETED = 
	"Task Deleted!";

class CommandDelete: public Command {
	public:
		CommandDelete(void);
		
		/*
		// This API function executes the Delete Command when called.
		//
		// Pre-conditions:
		//     (i) There should be a proper task index (and not just a display
		//     task index set as the current task index in the command instance
		//     before execute is called.
		//     (ii) The _isParsedCorrectly variable in the command 
		//     should be true.
		//
		// Post-Conditions:
		//     (i) The specified task will be deleted to LogicData
		//
		// Sample usage:
		//     CommandDelete* aDeleteCommand = new CommandDelete;
		//     aDeleteCommand->setTaskIndex(taskIndexToDelete);
		//     aDeleteCommand->execute();
		*/

		void execute();

	protected:
		
		// Functions For Execution

		void performDeleteOperation();
};

