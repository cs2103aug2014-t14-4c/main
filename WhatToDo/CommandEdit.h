//****************************************************************************
//@author A0110648L
//
// This is the concrete CommandEdit class, which is reponsible for executing 
// an "edit" command specified by the user.
//
// It works by (i) checking for the validity of the command; (ii) retrieving 
// the current state from LogicData; (iii) editing a particular task; (iv) 
// rewriting the current and view states in LogicData; and (v) adding 
// itself to LogicData's command history.
//
// If the command is invalid either due to (i) a false parsed status indicating
// it has been parsed incorrectly; or (ii) incorrect date orderings, an error 
// message will be added to the current state to be shown to the user eventually.
//
//****************************************************************************

#pragma once

#include "CommandAdd.h"

using namespace std;

const string MSG_LOGGING_EXECUTE_COMMAND_EDIT = 
	"\nCommand Edit Initiated:\n";
const string MSG_LOGGING_DELETE_EXISTING_TASK = 
	"Function called: deleteExistingTask(): _commandTaskIndex "
	"deleted: %s\n";
const string MSG_ACTION_EDIT = 
	"Task Edited!";

class CommandEdit: public CommandAdd {
	public:
		CommandEdit(void);
		
		/*
		// This API function executes the Edit Command when called.
		//
		// Pre-conditions:
		//     (i) There should be a proper task set as the current
		//     task in the command instance before execute is called.
		//     (ii) There should be a proper task index to edit set
		//     as the task index in the command instance before execute
		//     is called.
		//     (iii) The _isParsedCorrectly variable in the command 
		//     should be true.
		//
		// Post-Conditions:
		//     (i) The task with the specified task index will be deleted
		//     and replaced with the specified task unless there are logic
		//     errors with the task (such as if the specified task start 
		//     ime is after the end time)
		//
		// Sample usage:
		//     CommandEdit* anEditCommand = new CommandEdit;
		//     anEditCommand->setCurrentTask(taskToEdit);
		//     anEditCommand->setTaskIndex(taskIndexToEdit);
		//     anEditCommand->execute();
		*/
		
		void execute();

	protected:
		
		// Functions For Execution

		void deleteExistingTask();
		void performAddOperation();
};

