//****************************************************************************
//@Poh Zhi Chao A0110648L
// 
//This is the interface class to the entire Logic component. When called with 
// the getNewState(string commandString) method, it is guaranteed to return an 
// updated view state which may be used to update the GUI (for example).
//
// This class works by (i) obtaining a command object from the LogicParser with  
// the commandString; (ii) executing the concrete command object; and (iii) 
// retrieving the updated viewState from LogicData which is returned in its
// function call.
//
// If an error has occurred during the processing of the commandString, the 
// concrete command objects will terminate execution midway and store details 
// of the failed execution in the returned state, which may be used for 
// subsequent update purposes.
//
// If a warning (not serious but worthy of note) occurs instead, the concrete
// command objects will continue execution as per normal but still store details
// of the warning in the returned state, which may also be used for subsequent 
// update purposes.
//
// Sample usage:
//    State newState = LogicExecutor::getNewState("/load");
//
//****************************************************************************

#pragma once

#include "State.h"
#include "Task.h"
#include "LogicParser.h"
#include "Command.h"

using namespace std;

class LogicExecutor {
	public:
		LogicExecutor(void);
		static State getNewState(string commandLineInput);


};

