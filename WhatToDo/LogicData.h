//****************************************************************************
//LogicData is responsible for holding the current State, view State and
//initial State. It also keeps track of the commands that are executed from 
//the time that WhatToDo is executed. This allows for easy redoing and undoing
//from caller methods such as Command::Undo and Command::Redo. Also, LogicData
//supports Command::Filter as well, it is able to support filters such as:
//	1) Status
//		a) Done & Undone
//		b) Done only
//		c) Undone Only
//	2) Task type
//		a) All types
//		b) Fixed Timed
//		c) Deadline
//	3) Date
//
//Furthermore, LogicData support the logging of functions called and errors 
//from within. 
//
//@author A0110873L
//****************************************************************************

#ifndef LOGICDATA_H
#define LOGICDATA_H

#include <iostream>
#include <fstream>
#include <vector>
#include "State.h"
#include "StorageExecutor.h"

enum Status{
	STATUS_NOT_SET = -1, DONE_BOTH, ONLY_DONE, ONLY_UNDONE
};

enum Type{
	TYPE_NOT_SET = -1, ALL_TYPES, ONLY_FIXED, ONLY_DUE
};

class Command;

class LogicData {

	private:
		//Attributes for LogicData
		static State _currentState;
		static State _viewState;
		static State _initialState;
		static vector<Command*> _commandHistory;
		static int _currentCommandHistoryIndex;
		static int _doneFilter;
		static int _typeFilter;
		static date _startDateFilter;
		static date _endDateFilter;

		//Attributes for Logging
		static string _logFileName;
		static bool _loggingModeOn;
		static char buffer[255];

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

		//Logging
		static void log(string stringToLog);
		static bool isLoggingModeOn();
		static void setLoggingModeOff();
		static void setLoggingModeOn();

		//Constants
		static const string ABBREV_MONTH_JAN;
		static const string ABBREV_MONTH_FEB;
		static const string ABBREV_MONTH_MAR;
		static const string ABBREV_MONTH_APR;
		static const string ABBREV_MONTH_MAY;
		static const string ABBREV_MONTH_JUN;
		static const string ABBREV_MONTH_JUL;
		static const string ABBREV_MONTH_AUG;
		static const string ABBREV_MONTH_SEP;
		static const string ABBREV_MONTH_OCT;
		static const string ABBREV_MONTH_NOV;
		static const string ABBREV_MONTH_DEC;
		static const string STRING_SPACE_CHAR;
		static const string STRING_EMPTY;

		static const string INITIAL_VALUE_LOG_FILE_NAME;
		static const string LOG_MSG_CURRENT_STATE_SET;
		static const string LOG_MSG_VIEW_STATE_SET;
		static const string LOG_MSG_DONE_FILTER_SET;
		static const string LOG_MSG_TYPE_FILTER_SET;
		static const string LOG_MSG_DATE_FILTER_SET;
		static const string LOG_MSG_COMMAND_HISTORY_RESET;
		static const string LOG_MSG_COMMAND_HISTORY_ADDED;
		static const string LOG_MSG_RESET;
		static const string LOG_MSG_LOAD;
};

#endif