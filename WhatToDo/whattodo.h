#ifndef WHATTODO_H
#define WHATTODO_H

#include <QtWidgets/QMainWindow>
#include <QWebElement>
#include <QWebFrame>
#include <QShortcut>
#include <QGraphicsObject>
#include <QTextCursor>
#include <QObject>
#include <QAction>
#include <boost/algorithm/string.hpp>
#include <boost\date_time.hpp>
#include <sstream>
#include <string>
#include <vector>
#include "ui_whattodo.h"
#include "KeyPressEater.h"
#include "LogicExecutor.h"
#include "State.h"
#include "Task.h"
#include "calendarcanvas.h"

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class WhatToDo : public QMainWindow
{
	Q_OBJECT

	public:
		WhatToDo(QWidget *parent = 0);
		~WhatToDo();
		void updateCalendarScrollBar(int x, int y);
		void removeDeletedTask(); // to be called by calendar

	public slots:
		void handleKeyPressEvents(QObject* obj);
		void handleEntryIntoSearchBar();
		void handleEntryFieldTab();
		void handleToggleTab();
		void handleMinimize();
		void handleSearchBarChange();
		void handleHotkeyEdit();
		void handleHotkeyDelete();
		void handleHotkeyDone();
		void handleHotkeyFilter();
		void handleButtonEnter();
		void handleHotkeyClear();
		void handleHotkeyHelp();
		void handleButtonUndo();
		void handleButtonRedo();
		//Calendar
		void handleButtonToggleCalendar();
		void handleButtonCalendarPrev();
		void handleButtonCalendarNext();
		void handleButtonVertScroll(int);
		void handleButtonHoriScroll(int);

		void handleButtonToggleAgenda();

	private:
		Ui::WhatToDoClass _ui;
		KeyPressEater* _myKeyPressEater;
		State _currState;
		State _tempFutureState;
		CalendarCanvas *SFMLView;
		bool b_calendar_active, b_calender_init_complete;

		void connectAllOtherSignalAndSlots();
		void defineAllHotkeys();
		void loadSavedSettings();
		void setupOtherUIConfigs();
		void setupKeyPressEater();
		void updateGUIFromSearchBar();
		void updateGUIFromCommandLine();
		void updateGUIWithCommandString(string commandString);
		void updateAgendaView();
		void updateCalendarView();
		void showLogicUserFeedback();
		void showGUIUserFeedback(string guiUserFeedback);
		void refreshCurrStateWithCommand(string commandString);
		void markLastActionForUser(int timedViewScrollPos, int floatViewScrollPos);

		bool checkIsUserCommandInputValid(string usercommandString);
		int determineCommandType(string usercommandString);
		void processCommandEdit(string commandString);
		void processCommandDone(string commandString);
		void processCommandDelete(string commandString);
		void processCommandOthers(string commandString);

		string getAgendaTimedViewHtml();
		string getAgendaFloatViewHtml();
		string createDateTitleHtml(ptime titleDate);
		string createPreNumberingHtml(int startNumber);
		string createFloatingTaskHtml(Task taskToProcess);
		string createNonFloatingTaskHtml(Task taskToProcess);
		string getTaskNameTagsHtml(Task myTask);
		string getLastActionTextIndexHtml(Task taskToProcess);
		string getHtmlPreTaskTags(Task taskToProcess);

		ptime getTaskOrderingDate(Task myTask);
		string getDisplayTime(ptime myTime);
		string getDisplayDay(ptime myTime);
		string removeUnwantedChars(string stringToProcess);
		string changeDayToDayOfWeek(int day);
		string changeMonthToMonthOfYear(int year);
		string convertTaskToEditText(Task taskToConvert);
		string getTaskDateAsEditText(Task taskToConvert);
		string convertDateTimeToEditText(ptime timeToConvert);
		string convertDateToEditText(ptime timeToConvert);

		enum userCommandType { COMMAND_OTHERS = 1, COMMAND_EDIT, COMMAND_DONE, COMMAND_DELETE, COMMAND_HELP, COMMAND_HELP_ADD, COMMAND_HELP_EDIT, COMMAND_HELP_DELETE, COMMAND_HELP_DONE, COMMAND_HELP_SEARCH, COMMAND_HELP_CLEAR, COMMAND_HELP_UNDO, COMMAND_HELP_REDO, COMMAND_HELP_FILTER };

		static string HTMLTAGS_BEGIN;
		static string HTMLTAGS_END;
		static string HTMLTAGS_TITLE_FLOATING;
		static string HTMLTAGS_TITLE_DATE_PRE;
		static string HTMLTAGS_TITLE_DATE_POST;
		static string HTMLTAGS_NUMBERING_PRE;
		static string HTMLTAGS_NUMBERING_POST;
		static string HTMLTAGS_TASK_PRE_UNCHANGED;
		static string HTMLTAGS_TASK_PRE_CHANGED;
		static string HTMLTAGS_TASK_POST;
		static string HTMLTAGS_TASK_INDEX_SPECIAL_MARKER;
		static string HTMLTAGS_TASK_NAMETAGS_POST;
		static string HTMLTAGS_TASK_NAMETAGS_PRE_DEADLINE_ALLDAY;
		static string HTMLTAGS_TASK_NAMETAGS_POST_DEADLINE_TIMED;
		static string HTMLTAGS_TASK_NAMETAGS_POST_FIXED_ALLDAY;
		static string HTMLTAGS_TASK_NAMETAGS_POST_FIXED_START;
		static string HTMLTAGS_TASK_NAMETAGS_POST_FIXED_TIMED;
		static string HTMLTAGS_TASK_NAMETAGS_MID_FIXED_START;
		static string HTMLTAGS_TASK_DONE_PRE;
		static string HTMLTAGS_TASK_DONE_POST;
		static string HTMLTAGS_TASK_TAGS_PRE;
		static string HTMLTAGS_TASK_TAGS_POST;
		static string HTMLTAGS_BACKGROUND_PAST_PRE;
		static string HTMLTAGS_BACKGROUND_PAST_POST;
		static string HTMLTAGS_BACKGROUND_CHANGED_TASK;
		static string HTMLTAGS_BACKGROUND_DELETED_TASK;
		static string HTMLTAGS_STYLE_PROPERTY;
		static string HTMLTAGS_STYLE_PROPERTY_HIDE;
		static string HTMLTAGS_CHANGED_TASK_TEXT;
		static string HTMLTAGS_CHANGED_TASK_ID;
		static string HTMLTAGS_CHANGED_TASK_TEXT_ID;

		static string QTSTYLESHEET_TRANSPARENT_BACKGROUND;
		static int GUI_PARAM_SIZE_WIDTH;
		static int GUI_PARAM_SIZE_HEIGHT;
		static double GUI_PARAM_TEXT_MULTIPLIER;
		static string GUI_PARAM_STATUS_TITLE;
		static string GUI_PARAM_POPUP_PROPERTY_OPACITY;
		static string GUI_PARAM_POPUP_PROPERTY_MESSAGE;
		static string GUI_PARAM_POPUP_PROPERTY_ISANIMATE;
		static string GUI_PARAM_DISPLAY_DATE_TODAY;

		static string COMMAND_PARAM_EDIT;
		static string COMMAND_PARAM_DELETE;
		static string COMMAND_PARAM_DONE;
		static string COMMAND_PARAM_CLEAR;
		static string COMMAND_PARAM_HELP;
		static string COMMAND_PARAM_UNDO;
		static string COMMAND_PARAM_REDO;
		static string COMMAND_PARAM_LOAD;
		static string COMMAND_PARAM_FILTER;
		static string COMMAND_PARAM_SEARCH;
		static string COMMAND_PARAM_HELP_EDIT;
		static string COMMAND_PARAM_HELP_DELETE;
		static string COMMAND_PARAM_HELP_DONE;
		static string COMMAND_PARAM_HELP_ADD;
		static string COMMAND_PARAM_HELP_CLEAR;
		static string COMMAND_PARAM_HELP_UNDO;
		static string COMMAND_PARAM_HELP_REDO;
		static string COMMAND_PARAM_HELP_LOAD;
		static string COMMAND_PARAM_HELP_FILTER;
		static string COMMAND_PARAM_HELP_SEARCH;
		static string COMMAND_PARAM_ADD_DATE_DEADLINE;
		static string COMMAND_PARAM_ADD_DATE_TIMED_ALLDAY;
		static string COMMAND_PARAM_ADD_DATE_TIMED_START;
		static string COMMAND_PARAM_ADD_DATE_TIMED_END;

		static string MESSAGE_USER_WRONG_INDEX;
		static string MESSAGE_USER_WRONG_PARAMS;

		static string RESOURCE_PATHS_HELP_ADD;
		static string RESOURCE_PATHS_HELP_DELETE;
		static string RESOURCE_PATHS_HELP_EDIT;
		static string RESOURCE_PATHS_HELP_DONE;
		static string RESOURCE_PATHS_HELP_CLEAR;
		static string RESOURCE_PATHS_HELP_SEARCH;
		static string RESOURCE_PATHS_HELP_UNDO;
		static string RESOURCE_PATHS_HELP_REDO;
		static string RESOURCE_PATHS_HELP_FILTER;
		static string RESOURCE_PATHS_HELP_CONTENT;

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

		static string ABBREV_WEEK_MON;
		static string ABBREV_WEEK_TUE;
		static string ABBREV_WEEK_WED;
		static string ABBREV_WEEK_THU;
		static string ABBREV_WEEK_FRI;
		static string ABBREV_WEEK_SAT;
		static string ABBREV_WEEK_SUN;

		static string STRING_EMPTY;
		static string STRING_SPACE_CHAR;
		static string STRING_NEWLN_CHAR;
		static string STRING_RETURN_CHAR;
		static string STRING_DOT_CHAR;
		static string STRING_COMMA_CHAR;
		static string STRING_ZERO_CHAR;
		static string STRING_AM;
		static string STRING_PM;

};

#endif // WHATTODO_H
