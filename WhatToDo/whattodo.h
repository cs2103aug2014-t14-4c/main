//****************************************************************************
//@author A0110648L
//
// This is the main GUI logic / event handler class.
// 
// It is reponsible for (i) setting up the GUI with the help of other GUI
// classes; and (ii) and handling all subsequent events in the GUI and performing
// the respective simple logic actions to handle these events.
//
//****************************************************************************

#ifndef WHATTODO_H
#define WHATTODO_H

#include <QtWidgets/QMainWindow>
#include <QtWebKit/qwebelement.h>
#include <QWebFrame>
#include <QShortcut>
#include <QGraphicsObject>
#include <QTextCursor>
#include <QObject>
#include <QAction>
#include <sstream>
#include <string>
#include <vector>
#include <assert.h>
#include "boost/algorithm/string.hpp"
#include "boost/date_time.hpp"
#include "ui_whattodo.h"
#include "KeyPressEater.h"
#include "LogicExecutor.h"
#include "State.h"
#include "Task.h"

#include "calendarcanvas.h"

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

const string HTMLTAGS_BEGIN = 
	"<html><body style=\" font-family:'Calibri'; font-size:23pt; fon"
	"t-weight:400; font-style:normal;\">";
const string HTMLTAGS_END = "</ol></body></html>";
const string HTMLTAGS_TITLE_FLOATING = 
	"<p><b><u>Floating Tasks!</u></b></p><ol start=1 style=\"margin-"
	"top:-15px; margin-left:20px;\">";
const string HTMLTAGS_TITLE_DATE_PRE = "</ol><p><b><u>";
const string HTMLTAGS_TITLE_DATE_POST = "</u></b></p>";
const string HTMLTAGS_NUMBERING_PRE = "</ol><ol start=";
const string HTMLTAGS_NUMBERING_POST = 
	" style=\"margin-top:-15px; margin-left:20px;\">";
const string HTMLTAGS_TASK_PRE_UNCHANGED = 
	"<li style=\"margin-bottom:2px;\">";
const string HTMLTAGS_TASK_PRE_CHANGED = 
	"<li style=\"margin-bottom:2px;\" id=\"sptag\">";
const string HTMLTAGS_TASK_POST = "</li>";
const string HTMLTAGS_TASK_INDEX_SPECIAL_MARKER = 
	"<span style=\"\" id=\"sp\">[[SP]]</span>";
const string HTMLTAGS_TASK_NAMETAGS_POST = "]</span> ";
const string HTMLTAGS_TASK_NAMETAGS_PRE_DEADLINE_ALLDAY = 
	"<span style=\" font-weight:600; color:#ff0000;\">[DUE";
const string HTMLTAGS_TASK_NAMETAGS_POST_DEADLINE_TIMED = 
	"<span style=\" font-weight:600; color:#ff0000;\">[DUE - ";
const string HTMLTAGS_TASK_NAMETAGS_POST_FIXED_ALLDAY = 
	"<span style=\" font-weight:600; color:#0000ff;\">[All Day";
const string HTMLTAGS_TASK_NAMETAGS_POST_FIXED_START = 
	"<span style=\" font-weight:600; color:#0000ff;\">[";
const string HTMLTAGS_TASK_NAMETAGS_POST_FIXED_TIMED = 
	"<span style=\" font-weight:600; color:#0000ff;\">[";
const string HTMLTAGS_TASK_NAMETAGS_MID_FIXED_START = " - ";
const string HTMLTAGS_TASK_DONE_PRE = 
	"<font color=\"#007B21\"><b>[Done]";
const string HTMLTAGS_TASK_DONE_POST = "</font></b> ";
const string HTMLTAGS_TASK_TAGS_PRE = 
	"<span style=\" font-weight:600; color:#FF5D00;\"> ";
const string HTMLTAGS_TASK_TAGS_POST = "</span>";
const string HTMLTAGS_BACKGROUND_PAST_PRE = 
	"<span style=\"background-color: #D8D8D8;\">";
const string HTMLTAGS_BACKGROUND_PAST_POST = "</span>";
const string HTMLTAGS_BACKGROUND_CHANGED_TASK = 
	"background-color: #6DFF8F;";
const string HTMLTAGS_BACKGROUND_DELETED_TASK = 
	"background-color: #FF727E;";
const string HTMLTAGS_STYLE_PROPERTY = "style";
const string HTMLTAGS_STYLE_PROPERTY_HIDE = "display:none";
const string HTMLTAGS_CHANGED_TASK_TEXT = "[[sp]]";
const string HTMLTAGS_CHANGED_TASK_ID = "#sp";
const string HTMLTAGS_CHANGED_TASK_TEXT_ID = "#sptag";

const string QTSTYLESHEET_TRANSPARENT_BACKGROUND = 
	"background:transparent;";
const int GUI_PARAM_SIZE_WIDTH = 959;
const int GUI_PARAM_SIZE_HEIGHT = 692;
const double GUI_PARAM_TEXT_MULTIPLIER = 0.75;
const string GUI_PARAM_STATUS_TITLE = "Status: ";
const string GUI_PARAM_POPUP_PROPERTY_OPACITY = "imageOpacity";
const string GUI_PARAM_POPUP_PROPERTY_MESSAGE = "userMessage";
const string GUI_PARAM_POPUP_PROPERTY_ISANIMATE = 
	"isStartAnimation";
const string GUI_PARAM_DISPLAY_DATE_TODAY = "Today";
const int GUI_MIN_CHAR = 0;
const int GUI_MAX_CHAR = 255;

const string COMMAND_PARAM_EDIT = "/edit";
const string COMMAND_PARAM_DELETE_WITH_REAL_INDEX = "/delete_r";
const string COMMAND_PARAM_DONE_WITH_REAL_INDEX = "/done_r";
const string COMMAND_PARAM_UNDONE_WITH_REAL_INDEX = "/undone_r";
const string COMMAND_PARAM_DELETE = "/delete";
const string COMMAND_PARAM_DONE = "/done";
const string COMMAND_PARAM_UNDONE = "/undone";
const string COMMAND_PARAM_CLEAR = "/clear";
const string COMMAND_PARAM_HELP = "/help";
const string COMMAND_PARAM_UNDO = "/undo";
const string COMMAND_PARAM_REDO = "/redo";
const string COMMAND_PARAM_LOAD = "/load";
const string COMMAND_PARAM_FILTER = "/filter";
const string COMMAND_PARAM_SEARCH = "/search";
const string COMMAND_PARAM_HELP_EDIT = "edit";
const string COMMAND_PARAM_HELP_ADD = "add";
const string COMMAND_PARAM_HELP_DELETE = "delete";
const string COMMAND_PARAM_HELP_DONE = "done";
const string COMMAND_PARAM_HELP_CLEAR = "clear";
const string COMMAND_PARAM_HELP_UNDO = "undo";
const string COMMAND_PARAM_HELP_REDO = "redo";
const string COMMAND_PARAM_HELP_LOAD = "load";
const string COMMAND_PARAM_HELP_FILTER = "filter";
const string COMMAND_PARAM_HELP_SEARCH = "search";
const string COMMAND_PARAM_ADD_DATE_DEADLINE = "by ";
const string COMMAND_PARAM_ADD_DATE_TIMED_ALLDAY = "on ";
const string COMMAND_PARAM_ADD_DATE_TIMED_START = "from ";
const string COMMAND_PARAM_ADD_DATE_TIMED_END = "to ";

const string MSG_ERROR_USER_WRONG_INDEX = "No such display index!";
const string MSG_ERROR_USER_WRONG_PARAMS = 
	"Command parameters wrong!";
const string MSG_ERROR_INSUFFICIENT_INPUT =
	"Insufficient input parameters!";
const string MSG_ERR_CHANGED_HTML_ELEMENT_MISSING =
	"Changed html element missing!";
const string MSG_ERR_UNACCEPTED_CHARS_ENTERED = 
	"Unaccepted characters entered!";

const string RESOURCE_PATHS_HELP_ADD = 
	"/UI Files/Help/Help_Add.html";
const string RESOURCE_PATHS_HELP_DELETE = 
	"/UI Files/Help/Help_Delete.html";
const string RESOURCE_PATHS_HELP_EDIT = 
	"/UI Files/Help/Help_Edit.html";
const string RESOURCE_PATHS_HELP_DONE = 
	"/UI Files/Help/Help_Done.html";
const string RESOURCE_PATHS_HELP_CLEAR = 
	"/UI Files/Help/Help_Clear.html";
const string RESOURCE_PATHS_HELP_SEARCH = 
	"/UI Files/Help/Help_Search.html";
const string RESOURCE_PATHS_HELP_UNDO = 
	"/UI Files/Help/Help_Undo.html";
const string RESOURCE_PATHS_HELP_REDO = 
	"/UI Files/Help/Help_Redo.html";
const string RESOURCE_PATHS_HELP_FILTER = 
	"/UI Files/Help/Help_Filter.html";
const string RESOURCE_PATHS_HELP_CONTENT = 
	"/UI Files/Help/Help_Content.html";

const string ABBREV_MONTH_JAN = "Jan";
const string ABBREV_MONTH_FEB = "Feb";
const string ABBREV_MONTH_MAR = "Mar";
const string ABBREV_MONTH_APR = "Apr";
const string ABBREV_MONTH_MAY = "May";
const string ABBREV_MONTH_JUN = "Jun";
const string ABBREV_MONTH_JUL = "Jul";
const string ABBREV_MONTH_AUG = "Aug";
const string ABBREV_MONTH_SEP = "Sep";
const string ABBREV_MONTH_OCT = "Oct";
const string ABBREV_MONTH_NOV = "Nov";
const string ABBREV_MONTH_DEC = "Dec";

const string ABBREV_WEEK_MON = "Mon";
const string ABBREV_WEEK_TUE = "Tues";
const string ABBREV_WEEK_WED = "Wed";
const string ABBREV_WEEK_THU = "Thurs";
const string ABBREV_WEEK_FRI = "Fri";
const string ABBREV_WEEK_SAT = "Sat";
const string ABBREV_WEEK_SUN = "Sun";

const string STRING_SPACE_CHAR = " ";
const string STRING_NEWLN_CHAR = "\n";
const string STRING_RETURN_CHAR = "\r";
const string STRING_DOT_CHAR = ".";
const string STRING_COMMA_CHAR = ",";
const string STRING_ZERO_CHAR = "0";
const string STRING_AM = "am";
const string STRING_PM = "pm";
const string STRING_ALL_DAY = "All Day";

class WhatToDo : public QMainWindow
{
	Q_OBJECT

	public:
		WhatToDo(string exeDirectory, QWidget *parent = 0);
		~WhatToDo();

		// This event handler handles commands which are given by the
		// user through the calendar.

		void handleCalendarCommands(string command);
		void updateCalendarView();

	public slots:
		
		/*
		// All public event handlers are triggered when various events
		// occur within the GUI according to the user's interactions
		// with the program, and changes to the GUI have to be made via
		// these event handlers.
		*/

		// This event handler is called when the "Return" key is 
		// pressed for a widget with the KeyPressEater installed. In the
		// case where the "Return" key is pressed for the command entry 
		// field, this event handler will update the GUI accordingly 
		// depending on the user's command.

		void handleKeyPressEvents(QObject* obj);

		// This event handler is called when the "Tab" key is 
		// pressed for a widget with the KeyPressEater installed. This
		// event handler will alternate between the search bar and the command 
		// entry field when the "Tab" key is pressed.

		void handleEntryFieldTab();

		// This event handler is called when the search bar is entered through 
		// a hotkey event. This event handler will highlight all the text in the
		// search bar.

		void handleEntryIntoSearchBar();

		// This event handler is called when the user changes the contents of the
		// search bar, and it will update the GUI according to the user's 
		// desired search contents.

		void handleSearchBarChange();

		// These event handlers are called when hotkeys are pressed by the user.
		// The event handler titles should be self-explanatory.

		void handleHotkeyMinimize();
		void handleHotkeyEdit();
		void handleHotkeyDelete();
		void handleHotkeyDone();
		void handleHotkeyUndone();
		void handleHotkeyFilter();
		void handleHotkeyClear();
		void handleHotkeyHelp();

		// These event handlers are called when buttons are pressed by 
		// the user. The event handler titles should be self-explanatory.

		void handleButtonUndo();
		void handleButtonRedo();
		void handleButtonToggleCalendar();
		void handleButtonToggleAgenda();
		void handleButtonCalendarPrev();
		void handleButtonCalendarNext();

	private:
		
		// Attributes For Execution
		
		Ui::WhatToDoClass _ui;
		KeyPressEater* _myKeyPressEater;
		State _currState;
		State _tempFutureState;
		string _exeDirectory;
		CalendarCanvas* _SFMLView;
		bool _b_calender_init_complete;

		enum userCommandType { 
			COMMAND_OTHERS = 1, COMMAND_EDIT, 
			COMMAND_DONE_WITH_REAL_INDEX, 
			COMMAND_UNDONE_WITH_REAL_INDEX, 
			COMMAND_DELETE_WITH_REAL_INDEX,
			COMMAND_DONE, COMMAND_UNDONE, 
			COMMAND_DELETE, COMMAND_UNDO, COMMAND_HELP, 
			COMMAND_HELP_ADD, COMMAND_HELP_EDIT, 
			COMMAND_HELP_DELETE, COMMAND_HELP_DONE, 
			COMMAND_HELP_SEARCH, COMMAND_HELP_CLEAR, 
			COMMAND_HELP_UNDO, COMMAND_HELP_REDO, 
			COMMAND_HELP_FILTER
		};

		/*
		// These functions set up the GUI at startup by loading the
		// relevant graphic and information configurations to get it up
		// and running at startup. The function names should be self-
		// explanatory.
		*/

		void setupCalendar();
		void setupKeyPressEater();
		void setupOtherUIConfigs();
		void connectAllOtherSignalAndSlots();
		void defineAllHotkeys();
		void loadSavedSettings();

		void setupInitialGUIFocusConfigs();
		void setupInitialGUISizeConfigs();
		void setupMessageBoxConfigs();
		void setupTextSizeConfigs();

		/*
		// These functions handle the updating of GUI elements when there
		// are changes such as (i) user messages to display; or (ii) new view
		// states to display because the user made an action.
		*/

		// These functions update the GUI when there are new popup messages or
		// status bar messages to display to the user
		
		void showLogicUserFeedback();
		void showGUIUserFeedback(string guiUserFeedback);
		
		// These function updates the entire GUI according to the current 
		// contents in the search bar.

		void updateGUIFromSearchBar();

		// These function updates the entire GUI according to the current 
		// contents in the command entry field.

		void updateGUIFromCommandLine();

		// These function updates the GUI according to a command string
		// 
		// Pre-condition: 
		//     (i) the parameter commandString passed in must be 
		//     a valid command according to the checkIsUserCommandInputValid()
		//     function.

		void updateGUIWithCommandString(string commandString);

		// These functions update the agenda view in the GUI according to
		// the current state within this particular whattodo instance.

		void updateAgendaView();
		void markLastActionForUser(int timedViewScrollPos, int floatViewScrollPos);

		// This function refreshes the current state and temporary future states
		// within this particular whattodo instance according to the given
		// commandString.
		//
		// Pre-conditions: 
		//     (i) the parameter commandString passed in must be 
		//     a valid command according to the checkIsUserCommandInputValid()
		//     function.
		//     (ii) if the command implied by the parameter commandString is
		//     contains a task index, it should be the actual task index instead
		//     of the display index in the GUI
		//

		void refreshCurrStateWithCommand(string commandString);

		// This function checks if a given command string is considered 
		// valid user input 
		//
		// Pre-conditions: none
		// Post-conditions: 
		//     (i) returns true if the user input does not contain unwanted
		//     characters and is non-empty (not counting newline characters).

		bool checkIsUserCommandInputValid(string usercommandString);

		// This function determines and returns the user's command type given
		// a command string.

		int determineCommandType(string usercommandString);

		// The following functions execute the user's command string accordingly.
		//
		// Pre-conditions: 
		//     (i) the parameter commandString passed in should be a valid command
		//     according to the checkIsUserCommandInputValid() function.
		//     (ii) the parameter commandString passed in should be a command
		//     corresponding to the function name. For instance, the processCommandEdit()
		//     function should only be called to handle a commandString for an 
		//     edit command.

		void processCommandEdit(string commandString);
		void processCommandDone(string commandString, bool b_usingRealIndex);
		void processCommandUndone(string commandString, bool b_usingRealIndex);
		void processCommandDelete(string commandString, bool b_usingRealIndex);
		void processCommandOthers(string commandString);

		/*
		// These are functions that facilitate the construction of html tags
		// for display of the current state in the agenda view which is
		// to be shown to the user.
		*/

		string getAgendaTimedViewHtml();
		string getAgendaFloatViewHtml();
		string createDateTitleHtml(ptime titleDate);
		string createPreNumberingHtml(int startNumber);
		string createFloatingTaskHtml(Task taskToProcess);
		string createNonFloatingTaskHtml(Task taskToProcess);
		string getTaskNameTagsHtml(Task myTask);
		string getLastActionTextIndexHtml(Task taskToProcess);
		string getHtmlPreTaskTags(Task taskToProcess);

		/*
		// Other low-level functions which generally deal with formatting
		// issues and text conversions.
		*/

		ptime getTaskOrderingDate(Task myTask);
		string getDisplayTime(ptime myTime);
		string getDisplayDay(ptime myTime);
		string getDisplayDayWithoutTime(ptime myTime);
		string removeUnwantedChars(string stringToProcess);
		string changeDayToDayOfWeek(int day);
		string changeMonthToMonthOfYear(int year);

		// This function converts a task into text that the user can
		// readily edit.

		string convertTaskToEditText(Task taskToConvert);

		// This function converts a task's date into text that the user 
		// can readily edit.

		string getTaskDateAsEditText(Task taskToConvert);

		// This function converts a ptime's date into text that the
		// user can readily edit.

		string convertDateTimeToEditText(ptime timeToConvert);

		// This function converts a ptime's date and time into text that 
		// the user can readily edit.

		string convertDateToEditText(ptime timeToConvert);
		bool checkIsContainStrangeChars(string stringToProcess);
		bool checkIsCurrentStateEmpty();
};

#endif // WHATTODO_H
