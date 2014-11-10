//@author A0110873L
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
//****************************************************************************

#ifndef LOGICDATA_H
#define LOGICDATA_H

#include <iostream>
#include <fstream>
#include <vector>
#include "State.h"
#include "StorageExecutor.h"

enum Status {
	STATUS_NOT_SET = -1, DONE_BOTH, ONLY_DONE, ONLY_UNDONE
};

enum Type {
	TYPE_NOT_SET = -1, ALL_TYPES, ONLY_FIXED, ONLY_DUE
};

enum Month {
	JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT,
	NOV, DEC
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

		static char buffer[255];

	public:
		//Constructor
		LogicData();

		//Setters
		static void setCurrentState(State stateToSet);
		static void setViewState(State stateToSet);
		static void setDoneFilter(int doneFilter);
		static void setTypeFilter(int typeFilter);
		static void setDateFilter(date startDateFilter, date endDateFilter);
		static void setCommandHistoryIndex(int indexToSet);

		//Getters
		static State getCurrentState();
		static State getViewState();
		static vector<Command*> getCommandHistory();
		static int getCurrentCommandHistoryIndex();
		static int getDoneFilter();
		static int getTypeFilter();
		static date getStartDateFilter();
		static date getEndDateFilter();

		//Operations
		static void resetCommandHistory();
		static void addCommandToHistory(Command* commandToAdd);
		static void resetToInitialSettings();
		static void loadInitialSettings();
		static void fakeinitiate(State fakestate);
		static State filterTasks();
		static bool passDoneFilter(Task task);
		static bool passTypeFilter(Task task);
		static bool passDateFilter(Task task);
		static string getFilterStatus();
		static string changeMonthToMonthOfYear(int month);
		static string getDisplayDay(ptime myTime);
		static string compileNewActionMessage(State filteredViewState);
		static string compileStartDateFilterStatus(string dateFilterStatus, 
			date startDateFilter);
		static string compileEndDateFilterStatus(string dateFilterStatus, 
			date endDateFilter);
		static string compileFilterStatus(string doneFilterStatus,
			string typeFilterStatus, string dateFilterStatus);
		static string compileNewActionMessage(State filteredViewState);
		static bool doesDeadlinePassDateFilter(Task task);
		static bool doesStartDatePassDateFilter(Task task);
		static bool doesEndDatePassDateFilter(Task task);

		//Constants
		static const int INITIAL_COMMAND_HISTORY_INDEX;

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
		static const string STRING_FRONTSLASH_CHAR;
		static const string STRING_FROM;
		static const string STRING_TO;
		static const string STRING_FILTERED_BY;
		static const string STRING_COLON;
		static const string STRING_VERTICAL_BAR_CHAR;
		static const string STRING_EMPTY;
		static const string STRING_NO_DONE;
		static const string STRING_DONE;
		static const string STRING_UNDONE;
		static const string STRING_ALL_TYPES;
		static const string STRING_ONLY_FIXED;
		static const string STRING_ONLY_DUE;

		static const string ERR_MSG_INVALID_TASK_TYPE;
		static const string ERR_MSG_INVALID_STATUS_TYPE;
};

#endif