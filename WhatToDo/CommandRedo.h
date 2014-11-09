//****************************************************************************
//@author A0110648L
//
// This is the concrete CommandRedo class, which is reponsible for executing 
// a "redo" command specified by the user.
//
// It works by (i) checking for the validity of the command; (ii) resetting
// all LogicData's state settings; and (iii) running all the commands from the
// beginning all over again till the correct existing command to simulate a
// redo operation.
//
// If the command is invalid either due to (i) a false parsed status indicating
// it has been parsed incorrectly; or (ii) lack of commands to redo, an error 
// message will be added to the current state to be shown to the user eventually.
//
//****************************************************************************

#pragma once

#include "CommandUndo.h"

using namespace std;

const string MSG_LOGGING_EXECUTE_COMMAND_REDO = 
	"\nCommand Redo Initiated:\n";
const string MSG_ERROR_CANNOT_REDO_ANYMORE = 
	"Cannot redo anymore!";

class CommandRedo: public CommandUndo {
	public:
		CommandRedo(void);
		
		/*
		// This API function executes the Redo Command when called.
		//
		// Pre-conditions: 
		//     (i) LogicData's command history index must be between
		//     one and the size of the command history vector (LogicData
		//     must store a valid command history index.
		//     (ii) The _isParsedCorrectly variable in the command 
		//     should be true.
		//
		// Post-Conditions:
		//     (i) The latest undone action in LogicData's command history 
		//     will be redone. If there is no such action, redo will 
		//     not be performed.
		//
		// Sample usage:
		//     CommandRedo* aRedoCommand = new CommandRedo;
		//     aRedoCommand->execute();
		*/
		
		void execute();

	protected:

		// Functions For Execution

		bool checkIsCommandValid();
};

