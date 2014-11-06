//****************************************************************************
//@Poh Zhi Chao A0110648L
//
// This is the concrete CommandClear class, which is reponsible for executing 
// an "clear" command specified by the user.
//
// It works by (i) checking for the validity of the command; (ii) retrieving 
// the current state from LogicData; and (iii) rewriting the view state in 
// LogicData.
//
// If the command is invalid due to a false parsed status indicating
// it has been parsed incorrectly an error message will be added to the current\
// state to be shown to the user eventually.
//
//****************************************************************************

#pragma once

#include "Command.h"

using namespace std;

const string MSG_LOGGING_EXECUTE_COMMAND_CLEAR = 
	"\nCommand Clear Initiated:\n";

class CommandClear: public Command {
	public:
		CommandClear(void);
		void execute();
};

