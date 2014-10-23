#ifndef LOGICDATA_H
#define LOGICDATA_H

#include <iostream>
#include <vector>
#include "State.h"
#include "StorageExecutor.h"

class Command;

class LogicData{

	private:
		static State _currentState;
		static State _viewState;
		static State _initialState;
		static vector<Command*> _commandHistory;
		static int _currentCommandHistoryIndex;

	public:
		//Constructor
		LogicData();

		//setters
		static void setCurrentState(State stateToSet);
		static void setViewState(State stateToSet);

		//getters
		static State getCurrentState();
		static State getViewState();

		//operations
		static vector<Command*> getCommandHistory();
		static void addCommandToHistory(Command* commandToAdd);
		static int getCurrentCommandHistoryIndex();
		static void resetToInitialSettings();
		static void loadInitialSettings();
		static void setCommandHistoryIndex(int indexToSet);
		static void fakeinitiate(State fakestate);
};

#endif