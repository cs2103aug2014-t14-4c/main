#ifndef LOGICDATA_H
#define LOGICDATA_H

#include <iostream>
#include <vector>
#include "State.h"
#include "StorageExecutor.h"
#include "Command.h"

//currentcommandhistoryindex --> Need to check where it should be initialised and how.

class LogicData{

	private:
		State _currentState;
		State _viewState;
		State _initialState;
		vector<Command> _commandHistory;
		int _currentCommandHistoryIndex;
	public:
		//Constructor
		LogicData();

		//setters
		void setCurrentState(State stateToSet);
		void setViewState(State stateToSet);

		//getters
		State getCurrentState();
		State getViewState();

		//operations
		vector<Command> getCommandHistory();
		void addCommandToHistory(Command commandToAdd);
		int getCurrentCommandHistoryIndex();
		void resetToInitialSettings();
		void loadInitialSettings();
};

#endif