#ifndef LOGICDATA_H
#define LOGICDATA_H

#include <iostream>
#include <vector>
#include "State.h"
#include "StorageExecutor.h"

class Command;

enum Done{
	ALL, DONE, UNDONE
};

enum Type{
	ALL, TODO, AGENDA, FIXED, DUE
};

class LogicData{

	private:
		static State _currentState;
		static State _viewState;
		static State _initialState;
		static vector<Command*> _commandHistory;
		static int _currentCommandHistoryIndex;
		struct FILTERS{
			int done;
			int type;
			date startDate;
			date endDate;
		};
		static FILTERS _filters;

	public:
		//Constructor
		LogicData();

		//setters
		static void setCurrentState(State stateToSet);
		static void setViewState(State stateToSet);
		static void setFilterDone(int doneness);
		static void setFilterType(int type);
		static void setFilterStartDate(date startDateToSet);
		static void setFilterEndDate(date endDateToSet);

		//getters
		static State getCurrentState();
		static State getViewState();
		static int getFilterDone();
		static int getFilterType();
		static date getFilterStartDate();
		static date getFilterEndDate();

		//operations
		static void resetCommandHistory();
		static vector<Command*> getCommandHistory();
		static void addCommandToHistory(Command* commandToAdd);
		static int getCurrentCommandHistoryIndex();
		static void resetToInitialSettings();
		static void loadInitialSettings();
		static void setCommandHistoryIndex(int indexToSet);
		static void fakeinitiate(State fakestate);
};

#endif