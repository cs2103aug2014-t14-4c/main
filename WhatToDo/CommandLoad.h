//****************************************************************************
//@author A0110648L
//
// This is the concrete CommandLoad class, which is reponsible for executing 
// an "load" command.
//
// It works by calling LogicData to load all its internal data states and
// specifications from the existing external storage.
//
// If the command is invalid either due to a false parsed status indicating
// it has been parsed incorrectly, an error message will be added to the
// current state to be shown to the user eventually.
//
//****************************************************************************

#pragma once

#include "Command.h"

using namespace std;

const string MSG_LOGGING_EXECUTE_COMMAND_LOAD = 
	"\nCommand Load Initiated:\n";
const string MSG_LOGGING_LOAD_LOGIC_DATA_SETTINGS = 
	"Function called: loadLogicDataSettings()\n";

class CommandLoad: public Command {
	public:
		CommandLoad(void);
		
		/*
		// This API function executes the Load Command when called.
		//
		// Pre-conditions: 
		//     (i) The _isParsedCorrectly variable in the command 
		//     should be true.
		//
		// Post-Conditions:
		//     (i) The loadInitialSettings() function in LogicData will 
		//     be called
		//
		// Sample usage:
		//     CommandLoad* aLoadCommand = new CommandLoad;
		//     aLoadCommand->execute();
		*/
		
		void execute();

	protected:
		
		// Functions For Execution

		void loadLogicDataSettings();
		void resetLastActionType();
};

