//****************************************************************************
//@Poh Zhi Chao A0110648L
//
// This is the concrete CommandDone class, which is reponsible for executing 
// an "done" command specified by the user.
//
// It works by (i) checking for the validity of the command; (ii) retrieving 
// the current state from LogicData; (iii) marking a task as done; (iv) 
// rewriting the current and view states in LogicData; and (v) adding 
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

const string LOGGING_MSG_EXECUTE_COMMAND_DONE = 
	"\nCommand Done Initiated:\n";
const string LOGGING_MSG_PERFORM_DONE = 
	"Function called: performDoneOperation(): _commandTaskIndex mark"
	"ed as done: %s\n";
const string ACTION_MSG_DONE = 
	"Task marked as Done!";
const string ACTION_MSG_UNDONE = 
	"Task marked as Undone!";

class CommandDone: public Command {
	public:
		CommandDone(void);
		void execute();

	protected:

		// Functions For Execution

		void performDoneOperation();
};

