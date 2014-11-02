#ifndef LOGICDATA_H
#define LOGICDATA_H

#include <iostream>
#include <vector>
#include "State.h"
#include "StorageExecutor.h"

enum Done{
	DONE_NOT_SET = -1, DONE_BOTH, ONLY_DONE, ONLY_UNDONE
};

enum Type{
	TYPE_NOT_SET = -1, ALL_TYPES, ONLY_FIXED, ONLY_DUE
};

class Command;

class LogicData {

	private:
		static State _currentState;
		static State _viewState;
		static State _initialState;
		static vector<Command*> _commandHistory;
		static int _currentCommandHistoryIndex;
		static int _doneFilter;
		static int _typeFilter;
		static date _startDateFilter;
		static date _endDateFilter;

	public:
		//Constructor
		LogicData();

		//setters
		static void setCurrentState(State stateToSet);
		static void setViewState(State stateToSet);
		static void setDoneFilter(int doneFilter);
		static void setTypeFilter(int typeFilter);
		static void setDateFilter(date startDateFilter, date endDateFilter);

		//getters
		static State getCurrentState();
		static State getViewState();
		static int getDoneFilter();
		static int getTypeFilter();
		static date getStartDateFilter();
		static date getEndDateFilter();

		//operations
		static void resetCommandHistory();
		static vector<Command*> getCommandHistory();
		static void addCommandToHistory(Command* commandToAdd);
		static int getCurrentCommandHistoryIndex();
		static void resetToInitialSettings();
		static void loadInitialSettings();
		static void setCommandHistoryIndex(int indexToSet);
		static void fakeinitiate(State fakestate);
		static State filterTasks();
		static bool passDoneFilter(Task task);
		static bool passTypeFilter(Task task);
		static bool passDateFilter(Task task);
		static string getFilterStatus();
		static string changeMonthToMonthOfYear(int month);
		static string getDisplayDay(ptime myTime);

		static string ABBREV_MONTH_JAN;
		static string ABBREV_MONTH_FEB;
		static string ABBREV_MONTH_MAR;
		static string ABBREV_MONTH_APR;
		static string ABBREV_MONTH_MAY;
		static string ABBREV_MONTH_JUN;
		static string ABBREV_MONTH_JUL;
		static string ABBREV_MONTH_AUG;
		static string ABBREV_MONTH_SEP;
		static string ABBREV_MONTH_OCT;
		static string ABBREV_MONTH_NOV;
		static string ABBREV_MONTH_DEC;
		static string STRING_SPACE_CHAR;
		static string STRING_EMPTY;
};

#endif