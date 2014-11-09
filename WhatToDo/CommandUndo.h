//****************************************************************************
//@author A0110648L
// 
// This is the concrete CommandUndo class, which is reponsible for executing 
// a "undo" command specified by the user.
//
// It works by (i) checking for the validity of the command; (ii) resetting
// all LogicData's state settings; and (iii) running all the commands from the
// beginning all over again till the correct existing command to simulate an
// undo operation.
//
// If the command is invalid either due to (i) a false parsed status indicating
// it has been parsed incorrectly; or (ii) lack of past commands to undo, an error 
// message will be added to the current state to be shown to the user eventually.
//
//****************************************************************************

#pragma once

#include "Command.h"

using namespace std;

const string MSG_LOGGING_EXECUTE_COMMAND_UNDO = 
	"\nCommand Add Initiated:\n";
const string MSG_LOGGING_RUN_RELEVANT_COMMANDS_AGAIN = 
	"Function called: runAllRelevantCommandsAgain(): _currentCommand"
	"HistoryIndex: %s\n";
const string MSG_LOGGING_STORE_REMAINING_COMMANDS = 
	"Function called: storeRemainingCommandsInHistory(): size of _co"
	"mmandHistory: %s\nFunction called: storeRemainingCommandsInHist"
	"ory(): _currentCommandHistoryIndex: %s\n";
const string MSG_LOGGING_CHECK_IS_COMMAND_VALID = 
	"Function called: checkIsCommandValid(): updated _currentCommand"
	"HistoryIndex: %s\nFunction called: checkIsCommandValid(): isUnd"
	"o/RedoPossible: %s\n";
const string MSG_LOGGING_RETRIEVE_COMMAND_HISTORY = 
	"Function called: retrieveCommandHistory(): size of CommandHisto"
	"ry: %s\n";
const string MSG_LOGGING_RETRIEVE_COMMAND_HISTORY_INDEX = 
	"Function called: retrieveCommandHistoryIndex(): _currentCommand"
	"HistoryIndex: %s\n";

const string MSG_ERROR_CANNOT_UNDO_ANYMORE = 
	"Cannot undo anymore!";

class CommandUndo: public Command {
	public:
		CommandUndo(void);
		
		/*
		// This API function executes the Undo Command when called.
		//
		// Pre-conditions: 
		//     (i) LogicData's command history index must be between
		//     one and the size of the command history vector (LogicData
		//     must store a valid command history index.
		//     (ii) The _isParsedCorrectly variable in the command 
		//     should be true.
		//
		// Post-Conditions:
		//     (i) The latest done action in LogicData's command history 
		//     will be undone. If there is no such action, undo will 
		//     not be performed.
		//
		// Sample usage:
		//     CommandUndo* aUndoCommand = new CommandUndo;
		//     aUndoCommand->execute();
		*/
		
		void execute();

	protected:

		// Attributes For Execution

		int _currentCommandHistoryIndex;
		vector<Command*> _commandHistory;
		
		// Functions For Execution

		bool checkIsCommandValid();
		void runAllRelevantCommandsAgain();
		void storeRemainingCommandsInHistory();
		void retrieveCommandHistory();
		void retrieveCommandHistoryIndex();
};

