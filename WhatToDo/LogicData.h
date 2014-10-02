#pragma once
#include <vector>
#include "State.h"
#include "Command.h"
using namespace std;

class LogicData {
	public:
		LogicData(void);
		State getCurrentState();
		State getViewState();
		vector<Command> getCommandHistory();
		void setCurrentState(State stateToSet);
		void setViewState(State stateToSet);
		void addCommandToHistory(Command commandToAdd);
		int getCurrentCommandHistoryIndex();
		void resetToInitialSettings();
		void loadInitialSettings();

	private:
		State currentState;
		State viewState;
		State initialState;
		vector<Command> commandHistory;
		int currentCommandHistoryIndex;

};

