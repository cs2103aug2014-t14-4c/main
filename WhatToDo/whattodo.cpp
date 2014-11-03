#include "whattodo.h"


string WhatToDo::HTMLTAGS_BEGIN = "<html><body style=\" font-family:'Calibri'; font-size:23pt; font-weight:400; font-style:normal;\">";
string WhatToDo::HTMLTAGS_END = "</ol></body></html>";
string WhatToDo::HTMLTAGS_TITLE_FLOATING = "<p><b><u>Floating Tasks!</u></b></p><ol start=1 style=\"margin-top:-15px; margin-left:20px;\">";
string WhatToDo::HTMLTAGS_TITLE_DATE_PRE = "</ol><p><b><u>";
string WhatToDo::HTMLTAGS_TITLE_DATE_POST = "</u></b></p>";
string WhatToDo::HTMLTAGS_NUMBERING_PRE = "</ol><ol start=";
string WhatToDo::HTMLTAGS_NUMBERING_POST = " style=\"margin-top:-15px; margin-left:20px;\">";
string WhatToDo::HTMLTAGS_TASK_PRE_UNCHANGED = "<li style=\"margin-bottom:2px;\">";
string WhatToDo::HTMLTAGS_TASK_PRE_CHANGED = "<li style=\"margin-bottom:2px;\" id=\"sptag\">";
string WhatToDo::HTMLTAGS_TASK_POST = "</li>";
string WhatToDo::HTMLTAGS_TASK_INDEX_SPECIAL_MARKER = "<span style=\"\" id=\"sp\">[[SP]]</span>";
string WhatToDo::HTMLTAGS_TASK_NAMETAGS_POST = "]</span> ";
string WhatToDo::HTMLTAGS_TASK_NAMETAGS_PRE_DEADLINE_ALLDAY = "<span style=\" font-weight:600; color:#ff0000;\">[DUE";
string WhatToDo::HTMLTAGS_TASK_NAMETAGS_POST_DEADLINE_TIMED = "<span style=\" font-weight:600; color:#ff0000;\">[DUE - ";
string WhatToDo::HTMLTAGS_TASK_NAMETAGS_POST_FIXED_ALLDAY = "<span style=\" font-weight:600; color:#0000ff;\">[All Day";
string WhatToDo::HTMLTAGS_TASK_NAMETAGS_POST_FIXED_START = "<span style=\" font-weight:600; color:#0000ff;\">[";
string WhatToDo::HTMLTAGS_TASK_NAMETAGS_POST_FIXED_TIMED = "<span style=\" font-weight:600; color:#0000ff;\">[";
string WhatToDo::HTMLTAGS_TASK_NAMETAGS_MID_FIXED_START = " - ";
string WhatToDo::HTMLTAGS_TASK_DONE_PRE = "<font color=\"#007B21\"><b>[Done]";
string WhatToDo::HTMLTAGS_TASK_DONE_POST = "</font></b> ";
string WhatToDo::HTMLTAGS_TASK_TAGS_PRE = "<span style=\" font-weight:600; color:#FF5D00;\"> ";
string WhatToDo::HTMLTAGS_TASK_TAGS_POST = "</span>";
string WhatToDo::HTMLTAGS_BACKGROUND_PAST_PRE = "<span style=\"background-color: #D8D8D8;\">";
string WhatToDo::HTMLTAGS_BACKGROUND_PAST_POST = "</span>";
string WhatToDo::HTMLTAGS_BACKGROUND_CHANGED_TASK = "background-color: #6DFF8F;";
string WhatToDo::HTMLTAGS_BACKGROUND_DELETED_TASK = "background-color: #FF727E;";
string WhatToDo::HTMLTAGS_STYLE_PROPERTY = "style";
string WhatToDo::HTMLTAGS_STYLE_PROPERTY_HIDE = "display:none";
string WhatToDo::HTMLTAGS_CHANGED_TASK_TEXT = "[[sp]]";
string WhatToDo::HTMLTAGS_CHANGED_TASK_ID = "#sp";
string WhatToDo::HTMLTAGS_CHANGED_TASK_TEXT_ID = "#sptag";

string WhatToDo::QTSTYLESHEET_TRANSPARENT_BACKGROUND = "background:transparent;";
int WhatToDo::GUI_PARAM_SIZE_WIDTH = 959;
int WhatToDo::GUI_PARAM_SIZE_HEIGHT = 692;
double WhatToDo::GUI_PARAM_TEXT_MULTIPLIER = 0.75;
string WhatToDo::GUI_PARAM_STATUS_TITLE = "Status: ";
string WhatToDo::GUI_PARAM_POPUP_PROPERTY_OPACITY = "imageOpacity";
string WhatToDo::GUI_PARAM_POPUP_PROPERTY_MESSAGE = "userMessage";
string WhatToDo::GUI_PARAM_POPUP_PROPERTY_ISANIMATE = "isStartAnimation";
string WhatToDo::GUI_PARAM_DISPLAY_DATE_TODAY = "Today";

string WhatToDo::COMMAND_PARAM_EDIT = "/edit";
string WhatToDo::COMMAND_PARAM_DELETE = "/delete";
string WhatToDo::COMMAND_PARAM_DONE = "/done";
string WhatToDo::COMMAND_PARAM_CLEAR = "/clear";
string WhatToDo::COMMAND_PARAM_HELP = "/help";
string WhatToDo::COMMAND_PARAM_UNDO = "/undo";
string WhatToDo::COMMAND_PARAM_REDO = "/redo";
string WhatToDo::COMMAND_PARAM_LOAD = "/load";
string WhatToDo::COMMAND_PARAM_FILTER = "/filter";
string WhatToDo::COMMAND_PARAM_SEARCH = "/search";
string WhatToDo::COMMAND_PARAM_HELP_EDIT = "edit";
string WhatToDo::COMMAND_PARAM_HELP_ADD = "add";
string WhatToDo::COMMAND_PARAM_HELP_DELETE = "delete";
string WhatToDo::COMMAND_PARAM_HELP_DONE = "done";
string WhatToDo::COMMAND_PARAM_HELP_CLEAR = "clear";
string WhatToDo::COMMAND_PARAM_HELP_UNDO = "undo";
string WhatToDo::COMMAND_PARAM_HELP_REDO = "redo";
string WhatToDo::COMMAND_PARAM_HELP_LOAD = "load";
string WhatToDo::COMMAND_PARAM_HELP_FILTER = "filter";
string WhatToDo::COMMAND_PARAM_HELP_SEARCH = "search";
string WhatToDo::COMMAND_PARAM_ADD_DATE_DEADLINE = "by ";
string WhatToDo::COMMAND_PARAM_ADD_DATE_TIMED_ALLDAY = "on ";
string WhatToDo::COMMAND_PARAM_ADD_DATE_TIMED_START = "from ";
string WhatToDo::COMMAND_PARAM_ADD_DATE_TIMED_END = "to ";

string WhatToDo::MESSAGE_USER_WRONG_INDEX = "No such display index!";
string WhatToDo::MESSAGE_USER_WRONG_PARAMS = "Command parameters wrong!";

string WhatToDo::RESOURCE_PATHS_HELP_ADD = "/UI Files/Help/Help_Add.html";
string WhatToDo::RESOURCE_PATHS_HELP_DELETE = "/UI Files/Help/Help_Delete.html";
string WhatToDo::RESOURCE_PATHS_HELP_EDIT = "/UI Files/Help/Help_Edit.html";
string WhatToDo::RESOURCE_PATHS_HELP_DONE = "/UI Files/Help/Help_Done.html";
string WhatToDo::RESOURCE_PATHS_HELP_CLEAR = "/UI Files/Help/Help_Clear.html";
string WhatToDo::RESOURCE_PATHS_HELP_SEARCH = "/UI Files/Help/Help_Search.html";
string WhatToDo::RESOURCE_PATHS_HELP_UNDO = "/UI Files/Help/Help_Undo.html";
string WhatToDo::RESOURCE_PATHS_HELP_REDO = "/UI Files/Help/Help_Redo.html";
string WhatToDo::RESOURCE_PATHS_HELP_FILTER = "/UI Files/Help/Help_Filter.html";
string WhatToDo::RESOURCE_PATHS_HELP_CONTENT = "/UI Files/Help/Help_Content.html";

string WhatToDo::ABBREV_MONTH_JAN = "Jan";
string WhatToDo::ABBREV_MONTH_FEB = "Feb";
string WhatToDo::ABBREV_MONTH_MAR = "Mar";
string WhatToDo::ABBREV_MONTH_APR = "Apr";
string WhatToDo::ABBREV_MONTH_MAY = "May";
string WhatToDo::ABBREV_MONTH_JUN = "Jun";
string WhatToDo::ABBREV_MONTH_JUL = "Jul";
string WhatToDo::ABBREV_MONTH_AUG = "Aug";
string WhatToDo::ABBREV_MONTH_SEP = "Sep";
string WhatToDo::ABBREV_MONTH_OCT = "Oct";
string WhatToDo::ABBREV_MONTH_NOV = "Nov";
string WhatToDo::ABBREV_MONTH_DEC = "Dec";

string WhatToDo::ABBREV_WEEK_MON = "Mon";
string WhatToDo::ABBREV_WEEK_TUE = "Tues";
string WhatToDo::ABBREV_WEEK_WED = "Wed";
string WhatToDo::ABBREV_WEEK_THU = "Thurs";
string WhatToDo::ABBREV_WEEK_FRI = "Fri";
string WhatToDo::ABBREV_WEEK_SAT = "Sat";
string WhatToDo::ABBREV_WEEK_SUN = "Sun";

string WhatToDo::STRING_EMPTY = "";
string WhatToDo::STRING_SPACE_CHAR = " ";
string WhatToDo::STRING_NEWLN_CHAR = "\n";
string WhatToDo::STRING_RETURN_CHAR = "\r";
string WhatToDo::STRING_DOT_CHAR = ".";
string WhatToDo::STRING_COMMA_CHAR = ",";
string WhatToDo::STRING_ZERO_CHAR = "0";
string WhatToDo::STRING_AM = "am";
string WhatToDo::STRING_PM = "pm";

WhatToDo::WhatToDo(string exeDirectory, QWidget *parent)
	: QMainWindow(parent)
{
	_ui.setupUi(this);
	_exeDirectory = exeDirectory;
	setupOtherUIConfigs();
	setupKeyPressEater();
	defineAllHotkeys();
	connectAllOtherSignalAndSlots();
	loadSavedSettings();
}

WhatToDo::~WhatToDo()
{

}



void WhatToDo::handleKeyPressEvents(QObject* obj) {
	if (obj == _ui.commandSearch) {
		updateGUIFromSearchBar();
	}
	else if (obj == _ui.commandLine) {
		updateGUIFromCommandLine();
	}
	return;
}

void WhatToDo::handleEntryIntoSearchBar() {
	_ui.commandSearch->setFocus();
	_ui.commandSearch->selectAll();
	return;
}

void WhatToDo::handleEntryFieldTab() {
	if (_ui.commandLine->hasFocus()) {
		_ui.commandSearch->setFocus();
	}
	else {
		_ui.commandLine->setFocus();
	}
	return;
}

void WhatToDo::handleToggleTab() {

	return;
}

void WhatToDo::handleMinimize() {
	this->showMinimized();
	return;
}

void WhatToDo::handleSearchBarChange() {
	updateGUIFromSearchBar();
	return;
}

void WhatToDo::handleHotkeyEdit() {
	_ui.commandLine->setFocus();
	_ui.commandLine->setPlainText(QString::fromStdString(COMMAND_PARAM_EDIT + STRING_SPACE_CHAR));
	QTextCursor cursor = _ui.commandLine->textCursor();
	cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
	_ui.commandLine->setTextCursor(cursor);
	return;
}

void WhatToDo::handleHotkeyDelete() {
	_ui.commandLine->setFocus();
	_ui.commandLine->setPlainText(QString::fromStdString(COMMAND_PARAM_DELETE + STRING_SPACE_CHAR));
	string commandContents = _ui.commandLine->toPlainText().toStdString();
	QTextCursor cursor = _ui.commandLine->textCursor();
	cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
	_ui.commandLine->setTextCursor(cursor);
	return;
}

void WhatToDo::handleHotkeyDone() {
	_ui.commandLine->setFocus();
	_ui.commandLine->setPlainText(QString::fromStdString(COMMAND_PARAM_DONE + STRING_SPACE_CHAR));
	string commandContents = _ui.commandLine->toPlainText().toStdString();
	QTextCursor cursor = _ui.commandLine->textCursor();
	cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
	_ui.commandLine->setTextCursor(cursor);
	return;
}

void WhatToDo::handleHotkeyFilter() {
	_ui.commandLine->setFocus();
	_ui.commandLine->setPlainText(QString::fromStdString(COMMAND_PARAM_FILTER + STRING_SPACE_CHAR));
	string commandContents = _ui.commandLine->toPlainText().toStdString();
	QTextCursor cursor = _ui.commandLine->textCursor();
	cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
	_ui.commandLine->setTextCursor(cursor);
	return;
}

void WhatToDo::handleHotkeyClear() {
	updateGUIWithCommandString(COMMAND_PARAM_CLEAR);
	return;
}

void WhatToDo::handleHotkeyHelp() {
	updateGUIWithCommandString(COMMAND_PARAM_HELP);
	return;
}

void WhatToDo::handleButtonUndo() {
	updateGUIWithCommandString(COMMAND_PARAM_UNDO);
	return;
}

void WhatToDo::handleButtonRedo() {
	updateGUIWithCommandString(COMMAND_PARAM_REDO);
	return;
}

void WhatToDo::handleButtonToggleCalendar() {

	return;
}

void WhatToDo::handleButtonToggleAgenda() {

	return;
}



void WhatToDo::connectAllOtherSignalAndSlots() {
	QObject* decViewPointer;

	decViewPointer = _ui.buttonUndo->rootObject();
	connect(decViewPointer, SIGNAL(buttonClick()), this, SLOT(handleButtonUndo()));
	decViewPointer = _ui.buttonRedo->rootObject();
	connect(decViewPointer, SIGNAL(buttonClick()), this, SLOT(handleButtonRedo()));
	decViewPointer = _ui.buttonAgendaview->rootObject();
	connect(decViewPointer, SIGNAL(buttonClick()), this, SLOT(handleButtonToggleCalendar()));
	decViewPointer = _ui.buttonCalendarview->rootObject();
	connect(decViewPointer, SIGNAL(buttonClick()), this, SLOT(handleButtonToggleAgenda()));
	connect(_myKeyPressEater, SIGNAL(enterPressed(QObject*)), this, SLOT(handleKeyPressEvents(QObject*)));
	connect(_myKeyPressEater, SIGNAL(tabPressed()), this, SLOT(handleEntryFieldTab()));
	connect(_ui.commandSearch, SIGNAL(textChanged()), this, SLOT(handleSearchBarChange()));

	return;
}

void WhatToDo::defineAllHotkeys() {
	
	QAction *hotkeyUndo = new QAction(this);
	QAction *hotkeyRedo = new QAction(this);
	QAction *hotkeyFind = new QAction(this);
	QAction *hotkeyTabView = new QAction(this);
	QAction *hotkeyMinimize = new QAction(this);
	QAction *hotkeyDelete = new QAction(this);
	QAction *hotkeyEdit = new QAction(this);
	QAction *hotkeyDone = new QAction(this);
	QAction *hotkeyFilter = new QAction(this);
	QAction *hotkeyClear = new QAction(this);
	QAction *hotkeyHelp = new QAction(this);

	hotkeyUndo->setShortcut(Qt::Key_S | Qt::CTRL | Qt::SHIFT);
	hotkeyRedo->setShortcut(Qt::Key_D | Qt::CTRL | Qt::SHIFT);
	hotkeyFind->setShortcut(Qt::Key_F | Qt::CTRL);
	hotkeyTabView->setShortcut(Qt::Key_Tab | Qt::CTRL);
	hotkeyMinimize->setShortcut(Qt::Key_Space | Qt::CTRL);
	hotkeyDelete->setShortcut(Qt::Key_W | Qt::CTRL);
	hotkeyEdit->setShortcut(Qt::Key_E | Qt::CTRL);
	hotkeyDone->setShortcut(Qt::Key_D | Qt::CTRL);
	hotkeyFilter->setShortcut(Qt::Key_Q | Qt::CTRL);
	hotkeyClear->setShortcut(Qt::Key_Escape);
	hotkeyHelp->setShortcut(Qt::Key_H | Qt::CTRL);

	connect(hotkeyUndo, SIGNAL(triggered()), this, SLOT(handleButtonUndo()));
	connect(hotkeyRedo, SIGNAL(triggered()), this, SLOT(handleButtonRedo()));
	connect(hotkeyFind, SIGNAL(triggered()), this, SLOT(handleEntryIntoSearchBar()));
	connect(hotkeyTabView, SIGNAL(triggered()), this, SLOT(handleToggleTab()));
	connect(hotkeyMinimize, SIGNAL(triggered()), this, SLOT(handleMinimize()));
	connect(hotkeyDelete, SIGNAL(triggered()), this, SLOT(handleHotkeyDelete()));
	connect(hotkeyEdit, SIGNAL(triggered()), this, SLOT(handleHotkeyEdit()));
	connect(hotkeyDone, SIGNAL(triggered()), this, SLOT(handleHotkeyDone()));
	connect(hotkeyFilter, SIGNAL(triggered()), this, SLOT(handleHotkeyFilter()));
	connect(hotkeyClear, SIGNAL(triggered()), this, SLOT(handleHotkeyClear()));
	connect(hotkeyHelp, SIGNAL(triggered()), this, SLOT(handleHotkeyHelp()));

	_ui.centralWidget->addAction(hotkeyUndo);
	_ui.centralWidget->addAction(hotkeyRedo);
	_ui.centralWidget->addAction(hotkeyFind);
	_ui.centralWidget->addAction(hotkeyTabView);
	_ui.centralWidget->addAction(hotkeyMinimize);
	_ui.centralWidget->addAction(hotkeyDelete);
	_ui.centralWidget->addAction(hotkeyEdit);
	_ui.centralWidget->addAction(hotkeyDone);
	_ui.centralWidget->addAction(hotkeyFilter);
	_ui.centralWidget->addAction(hotkeyClear);
	_ui.centralWidget->addAction(hotkeyHelp);

	return;
}

void WhatToDo::loadSavedSettings() {
	refreshCurrStateWithCommand(COMMAND_PARAM_LOAD);
	updateAgendaView();
	updateCalendarView();
	return;
}

void WhatToDo::setupOtherUIConfigs() {
	_ui.messageFeedback->setAttribute(Qt::WA_TranslucentBackground);
	_ui.messageFeedback->setStyleSheet(QString::fromStdString(QTSTYLESHEET_TRANSPARENT_BACKGROUND));
	_ui.messageFeedback->setAttribute(Qt::WA_TransparentForMouseEvents);

	this->setFixedSize(GUI_PARAM_SIZE_WIDTH, GUI_PARAM_SIZE_HEIGHT);
	_ui.displayAgendaviewFloat->setTextSizeMultiplier(GUI_PARAM_TEXT_MULTIPLIER);
	_ui.displayAgendaviewTimed->setTextSizeMultiplier(GUI_PARAM_TEXT_MULTIPLIER);

	return;
}

void WhatToDo::setupKeyPressEater() {
	_myKeyPressEater = new KeyPressEater();
	_ui.commandLine->installEventFilter(_myKeyPressEater);
	_ui.commandSearch->installEventFilter(_myKeyPressEater);
	return;
}

void WhatToDo::updateGUIFromSearchBar() {
	string userSearchString;
	string logicComandString;

	userSearchString = _ui.commandSearch->toPlainText().toStdString();
	userSearchString = removeUnwantedChars(userSearchString);
	
	if (userSearchString == STRING_EMPTY) {
		logicComandString = COMMAND_PARAM_CLEAR;
	}
	else {
		logicComandString = COMMAND_PARAM_SEARCH + STRING_SPACE_CHAR + userSearchString;
	}

	updateGUIWithCommandString(logicComandString);
	return;
}

void WhatToDo::updateGUIFromCommandLine() {
	bool isUserCommandValid;
	string usercommandString;
	string logicComandString;

	usercommandString = _ui.commandLine->toPlainText().toStdString();
	isUserCommandValid = checkIsUserCommandInputValid(usercommandString);
	usercommandString = removeUnwantedChars(usercommandString);

	_ui.commandLine->setHtml(QString::fromStdString(STRING_EMPTY));

	if (isUserCommandValid) {
		updateGUIWithCommandString(usercommandString);
	}
	return;
}

void WhatToDo::updateGUIWithCommandString(string commandString) {
	int commandType;
	commandType = determineCommandType(commandString);

	switch (commandType) {
		case COMMAND_EDIT: {
			processCommandEdit(commandString);
			break;
		}
		case COMMAND_DONE: {
			processCommandDone(commandString);
			break;
		}
		case COMMAND_DELETE: {
			processCommandDelete(commandString);
			break;
		}
		case COMMAND_OTHERS: {
			processCommandOthers(commandString);
			break;
		}
		case COMMAND_HELP: {
			string fullHelpDirectory = _exeDirectory + RESOURCE_PATHS_HELP_CONTENT;
			_ui.displayAgendaviewTimed->load(QUrl::fromLocalFile(QString::fromStdString(fullHelpDirectory)));
			break;
		}
		case COMMAND_HELP_ADD: {
			string fullHelpDirectory = _exeDirectory + RESOURCE_PATHS_HELP_ADD;
			_ui.displayAgendaviewTimed->load(QUrl::fromLocalFile(QString::fromStdString(RESOURCE_PATHS_HELP_ADD)));
			break;
		}
		case COMMAND_HELP_EDIT: {
			string fullHelpDirectory = _exeDirectory + RESOURCE_PATHS_HELP_EDIT;
			_ui.displayAgendaviewTimed->load(QUrl::fromLocalFile(QString::fromStdString(fullHelpDirectory)));
			break;
		}
		case COMMAND_HELP_DONE: {
			string fullHelpDirectory = _exeDirectory + RESOURCE_PATHS_HELP_DONE;
			_ui.displayAgendaviewTimed->load(QUrl::fromLocalFile(QString::fromStdString(fullHelpDirectory)));
			break;
		}
		case COMMAND_HELP_DELETE: {
			string fullHelpDirectory = _exeDirectory + RESOURCE_PATHS_HELP_DELETE;
			_ui.displayAgendaviewTimed->load(QUrl::fromLocalFile(QString::fromStdString(fullHelpDirectory)));
			break;
		}
		case COMMAND_HELP_SEARCH: {
			string fullHelpDirectory = _exeDirectory + RESOURCE_PATHS_HELP_SEARCH;
			_ui.displayAgendaviewTimed->load(QUrl::fromLocalFile(QString::fromStdString(fullHelpDirectory)));
			break;
		}
		case COMMAND_HELP_CLEAR: {
			string fullHelpDirectory = _exeDirectory + RESOURCE_PATHS_HELP_CLEAR;
			_ui.displayAgendaviewTimed->load(QUrl::fromLocalFile(QString::fromStdString(fullHelpDirectory)));
			break;
		}
		case COMMAND_HELP_UNDO: {
			string fullHelpDirectory = _exeDirectory + RESOURCE_PATHS_HELP_UNDO;
			_ui.displayAgendaviewTimed->load(QUrl::fromLocalFile(QString::fromStdString(fullHelpDirectory)));
			break;
		}
		case COMMAND_HELP_REDO: {
			string fullHelpDirectory = _exeDirectory + RESOURCE_PATHS_HELP_REDO;
			_ui.displayAgendaviewTimed->load(QUrl::fromLocalFile(QString::fromStdString(fullHelpDirectory)));
			break;
		}
		case COMMAND_HELP_FILTER: {
			string fullHelpDirectory = _exeDirectory + RESOURCE_PATHS_HELP_FILTER;
			_ui.displayAgendaviewTimed->load(QUrl::fromLocalFile(QString::fromStdString(fullHelpDirectory)));
			break;
		}
	}
	return;
}

void WhatToDo::updateAgendaView() {
	string newAgendaTimedViewHtml;
	string newAgendaFloatViewHtml;
	int timedViewScrollPos;
	int floatViewScrollPos;

	newAgendaTimedViewHtml = getAgendaTimedViewHtml();
	newAgendaFloatViewHtml = getAgendaFloatViewHtml();
	
	timedViewScrollPos = _ui.displayAgendaviewTimed->page()->mainFrame()->scrollBarValue(Qt::Vertical);
	floatViewScrollPos = _ui.displayAgendaviewFloat->page()->mainFrame()->scrollBarValue(Qt::Vertical);
	
	_ui.displayAgendaviewTimed->setHtml(QString::fromStdString(newAgendaTimedViewHtml));
	_ui.displayAgendaviewFloat->setHtml(QString::fromStdString(newAgendaFloatViewHtml));
	
	markLastActionForUser(timedViewScrollPos, floatViewScrollPos);

	return;
}

void WhatToDo::updateCalendarView() {

	return;
}



bool WhatToDo::checkIsUserCommandInputValid(string usercommandString) {
	bool isUserCommandValid = false;
	usercommandString = removeUnwantedChars(usercommandString);
	if (usercommandString != STRING_EMPTY) {
		isUserCommandValid = true;
	}
	return isUserCommandValid;
}

int WhatToDo::determineCommandType(string usercommandString) {
	istringstream inputString(usercommandString);
	string userCommand;
	string userCommandSpecs;
	inputString >> userCommand;

	if (userCommand == COMMAND_PARAM_EDIT) {
		return COMMAND_EDIT;
	}
	else if (userCommand == COMMAND_PARAM_DONE) {
		return COMMAND_DONE;
	}
	else if (userCommand == COMMAND_PARAM_DELETE) {
		return COMMAND_DELETE;
	}
	else if (userCommand == COMMAND_PARAM_HELP) {
		if (inputString >> userCommandSpecs) {
			if (userCommandSpecs == COMMAND_PARAM_HELP_ADD) {
				return COMMAND_HELP_ADD;
			}
			else if (userCommandSpecs == COMMAND_PARAM_HELP_EDIT) {
				return COMMAND_HELP_EDIT;
			}
			else if (userCommandSpecs == COMMAND_PARAM_HELP_DELETE) {
				return COMMAND_HELP_DELETE;
			}
			else if (userCommandSpecs == COMMAND_PARAM_HELP_DONE) {
				return COMMAND_HELP_DONE;
			}
			else if (userCommandSpecs == COMMAND_PARAM_HELP_SEARCH) {
				return COMMAND_HELP_SEARCH;
			}
			else if (userCommandSpecs == COMMAND_PARAM_HELP_UNDO) {
				return COMMAND_HELP_UNDO;
			}
			else if (userCommandSpecs == COMMAND_PARAM_HELP_REDO) {
				return COMMAND_HELP_REDO;
			}
			else if (userCommandSpecs == COMMAND_PARAM_HELP_CLEAR) {
				return COMMAND_HELP_CLEAR;
			}
			else {
				return COMMAND_HELP;
			}
		}
		else {
			return COMMAND_HELP;
		}
	}
	else {
		return COMMAND_OTHERS;
	}
	return COMMAND_OTHERS;
}

void WhatToDo::processCommandEdit(string commandString) {
	istringstream inputString(commandString);
	vector<Task> allCurrentTasks = _currState.getAllTasks();
	int displayIndexToEdit;
	int actualIndexToEdit;
	string userCommand;
	string newEditContents;
	string commandToPassLogic;
	string textToFillCommandLine;

	if (inputString >> userCommand >> displayIndexToEdit) {
		if (getline(inputString, newEditContents)) {
			if ((displayIndexToEdit >= 1) && (displayIndexToEdit <= allCurrentTasks.size())) {
				actualIndexToEdit = allCurrentTasks[displayIndexToEdit-1].getTaskIndex();
				commandToPassLogic = COMMAND_PARAM_EDIT + STRING_SPACE_CHAR + to_string(actualIndexToEdit) + STRING_SPACE_CHAR + newEditContents;

				refreshCurrStateWithCommand(commandToPassLogic);
				updateAgendaView();
				updateCalendarView();
				showLogicUserFeedback();
			}
			else {
				showGUIUserFeedback(MESSAGE_USER_WRONG_INDEX);
			}
		}
		else {
			if ((displayIndexToEdit >= 1) && (displayIndexToEdit <= allCurrentTasks.size())) {
				newEditContents = convertTaskToEditText(allCurrentTasks[displayIndexToEdit-1]);
				textToFillCommandLine = COMMAND_PARAM_EDIT + STRING_SPACE_CHAR + to_string(displayIndexToEdit) + STRING_SPACE_CHAR + newEditContents;
				_ui.commandLine->setPlainText(QString::fromStdString(textToFillCommandLine));
				QTextCursor cursor = _ui.commandLine->textCursor();
				cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
				_ui.commandLine->setTextCursor(cursor);
			}
			else {
				showGUIUserFeedback(MESSAGE_USER_WRONG_INDEX);
			}
		}
	}
	return;
}

void WhatToDo::processCommandDone(string commandString) {
	istringstream inputString(commandString);
	vector<Task> allCurrentTasks = _currState.getAllTasks();
	int displayIndexToDone;
	int actualIndexToDone;
	string userCommand;
	string commandToPassLogic;

	if (inputString >> userCommand >> displayIndexToDone) {
		if ((displayIndexToDone >= 1) && (displayIndexToDone <= allCurrentTasks.size())) {
			actualIndexToDone = allCurrentTasks[displayIndexToDone-1].getTaskIndex();
			commandToPassLogic = COMMAND_PARAM_DONE + STRING_SPACE_CHAR + to_string(actualIndexToDone);

			refreshCurrStateWithCommand(commandToPassLogic);
			updateAgendaView();
			updateCalendarView();
			showLogicUserFeedback();
		}
		else {
			showGUIUserFeedback(MESSAGE_USER_WRONG_INDEX);
		}
	}
	else {
		showGUIUserFeedback(MESSAGE_USER_WRONG_PARAMS);
	}
	return;
}

void WhatToDo::processCommandDelete(string commandString) {
	istringstream inputString(commandString);
	vector<Task> allCurrentTasks = _currState.getAllTasks();
	int displayIndexToDelete;
	int actualIndexToDelete;
	string userCommand;
	string commandToPassLogic;

	if (inputString >> userCommand >> displayIndexToDelete) {
		if ((displayIndexToDelete >= 1) && (displayIndexToDelete <= allCurrentTasks.size())) {
			actualIndexToDelete = allCurrentTasks[displayIndexToDelete-1].getTaskIndex();
			commandToPassLogic = COMMAND_PARAM_DELETE + STRING_SPACE_CHAR + to_string(actualIndexToDelete);

			refreshCurrStateWithCommand(commandToPassLogic);
			updateAgendaView();
			updateCalendarView();
			showLogicUserFeedback();
		}
		else {
			showGUIUserFeedback(MESSAGE_USER_WRONG_INDEX);
		}
	}
	else {
		showGUIUserFeedback(MESSAGE_USER_WRONG_PARAMS);
	}

	return;
}

void WhatToDo::processCommandOthers(string commandString) {
	refreshCurrStateWithCommand(commandString);
	updateAgendaView();
	updateCalendarView();
	showLogicUserFeedback();
	return;
}

void WhatToDo::showLogicUserFeedback() {
	string userMessage = _currState.getUserMessage();
	string actionMessage = _currState.getActionMessage();

	if (userMessage != STRING_EMPTY) {
		QObject* decViewPointer = _ui.messageFeedback->rootObject();
		decViewPointer->setProperty(GUI_PARAM_POPUP_PROPERTY_MESSAGE.c_str(), QString::fromStdString(userMessage));
		decViewPointer->setProperty(GUI_PARAM_POPUP_PROPERTY_OPACITY.c_str(), 1.0);
		decViewPointer->setProperty(GUI_PARAM_POPUP_PROPERTY_ISANIMATE.c_str(), false);
		decViewPointer->setProperty(GUI_PARAM_POPUP_PROPERTY_ISANIMATE.c_str(), true);
		_currState.setUserMessage(STRING_EMPTY);
		_ui.statusBar->setPlainText(QString::fromStdString(GUI_PARAM_STATUS_TITLE + userMessage));
	}
	else {
		_ui.statusBar->setPlainText(QString::fromStdString(GUI_PARAM_STATUS_TITLE + actionMessage));
	}
	return;
}

void WhatToDo::showGUIUserFeedback(string guiUserFeedback) {
	QObject* decViewPointer = _ui.messageFeedback->rootObject();
	decViewPointer->setProperty(GUI_PARAM_POPUP_PROPERTY_MESSAGE.c_str(), QString::fromStdString(guiUserFeedback));
	decViewPointer->setProperty(GUI_PARAM_POPUP_PROPERTY_OPACITY.c_str(), 1.0);
	decViewPointer->setProperty(GUI_PARAM_POPUP_PROPERTY_ISANIMATE.c_str(), false);
	decViewPointer->setProperty(GUI_PARAM_POPUP_PROPERTY_ISANIMATE.c_str(), true);
	_currState.setActionMessage(STRING_EMPTY);
	_ui.statusBar->setPlainText(QString::fromStdString(GUI_PARAM_STATUS_TITLE + guiUserFeedback));
	return;
}

void WhatToDo::refreshCurrStateWithCommand(string commandString) {
	State incomingNewState = LogicExecutor::getNewState(commandString);
	int lastActionType = incomingNewState.getLastActionType();
	int lastActionTaskIndex = incomingNewState.getLastActionTaskIndex();

	if ((lastActionType == State::CHANGED) || (lastActionType == State::NONE)){
		_currState = incomingNewState;
		_tempFutureState = incomingNewState;
	}
	else {
		_currState = _tempFutureState;
		_currState.setLastActionTaskIndex(incomingNewState.getLastActionTaskIndex());
		_currState.setLastActionType(incomingNewState.getLastActionType());
		_currState.setActionMessage(incomingNewState.getActionMessage());
		_tempFutureState = incomingNewState;
	}	

	return;
}

void WhatToDo::markLastActionForUser(int timedViewScrollPos, int floatViewScrollPos) {
	int newtimedViewScrollPos;
	int newfloatViewScrollPos;
	int lastActionTaskIndex = _currState.getLastActionTaskIndex();
	int lastActionType = _currState.getLastActionType();
	string lastActionElementID;
	QWebElement theChangedTaskElement;
	QWebElement tempTaskElement;
	QWebFrame* floatViewWebFrame = _ui.displayAgendaviewFloat->page()->mainFrame();
	QWebFrame* timedViewWebFrame = _ui.displayAgendaviewTimed->page()->mainFrame();
	
	if (lastActionType == State::NONE) {
		floatViewWebFrame->setScrollBarValue(Qt::Vertical, floatViewScrollPos);
		timedViewWebFrame->setScrollBarValue(Qt::Vertical, timedViewScrollPos);
		return;
	}
	else {
		_ui.displayAgendaviewFloat->findText(QString::fromStdString(HTMLTAGS_CHANGED_TASK_TEXT));
		_ui.displayAgendaviewTimed->findText(QString::fromStdString(HTMLTAGS_CHANGED_TASK_TEXT));
		newfloatViewScrollPos = _ui.displayAgendaviewFloat->page()->mainFrame()->scrollBarValue(Qt::Vertical);
		newtimedViewScrollPos = _ui.displayAgendaviewTimed->page()->mainFrame()->scrollBarValue(Qt::Vertical);
		floatViewWebFrame->setScrollBarValue(Qt::Vertical, newfloatViewScrollPos);
		timedViewWebFrame->setScrollBarValue(Qt::Vertical, newtimedViewScrollPos);
		
		tempTaskElement = floatViewWebFrame->findFirstElement(QString::fromStdString(HTMLTAGS_CHANGED_TASK_ID));
		if (!tempTaskElement.isNull()) {
			theChangedTaskElement = tempTaskElement;
		}
		else {
			theChangedTaskElement = timedViewWebFrame->findFirstElement(QString::fromStdString(HTMLTAGS_CHANGED_TASK_ID));
		}
		theChangedTaskElement.setAttribute(QString::fromStdString(HTMLTAGS_STYLE_PROPERTY), QString::fromStdString(HTMLTAGS_STYLE_PROPERTY_HIDE));

		tempTaskElement = floatViewWebFrame->findFirstElement(QString::fromStdString(HTMLTAGS_CHANGED_TASK_TEXT_ID));
		if (!tempTaskElement.isNull()) {
			theChangedTaskElement = tempTaskElement;
		}
		else {
			theChangedTaskElement = timedViewWebFrame->findFirstElement(QString::fromStdString(HTMLTAGS_CHANGED_TASK_TEXT_ID));
		}

		if (lastActionType == State::CHANGED) {
			theChangedTaskElement.setAttribute(QString::fromStdString(HTMLTAGS_STYLE_PROPERTY), QString::fromStdString(HTMLTAGS_BACKGROUND_CHANGED_TASK));
		}
		else {
			theChangedTaskElement.setAttribute(QString::fromStdString(HTMLTAGS_STYLE_PROPERTY), QString::fromStdString(HTMLTAGS_BACKGROUND_DELETED_TASK));
		}
	}

	return;
}



string WhatToDo::getAgendaTimedViewHtml() {
	string newAgendaTimedViewHtml;
	vector<Task> listOfTasks = _currState.getAllTasks();
	ptime currentptime = not_a_date_time;
	ptime nextptime = not_a_date_time;
	int i;

	newAgendaTimedViewHtml += HTMLTAGS_BEGIN;

	for (i=0; unsigned(i)<listOfTasks.size(); i++) {
		if (!(listOfTasks[i].getTaskType() == Task::FLOATING)) {
			nextptime = getTaskOrderingDate(listOfTasks[i]);
			if (nextptime.date() != currentptime.date()) {
				newAgendaTimedViewHtml += createDateTitleHtml(nextptime);
				newAgendaTimedViewHtml += createPreNumberingHtml(i+1);
				currentptime = nextptime;
			}
			newAgendaTimedViewHtml += createNonFloatingTaskHtml(listOfTasks[i]);
		}
	}

	newAgendaTimedViewHtml += HTMLTAGS_END;
	return newAgendaTimedViewHtml;
}

string WhatToDo::getAgendaFloatViewHtml() {
	string newAgendaFloatViewHtml;
	vector<Task> listOfTasks = _currState.getAllTasks();
	ptime currentptime = not_a_date_time;
	ptime nextptime = not_a_date_time;
	bool isExistFloatingTasks = false;
	int i;

	newAgendaFloatViewHtml += HTMLTAGS_BEGIN;

	for (i=0; unsigned(i)<listOfTasks.size(); i++) {
		if (listOfTasks[i].getTaskType() == Task::FLOATING) {
			if (!isExistFloatingTasks) {
				newAgendaFloatViewHtml += HTMLTAGS_TITLE_FLOATING;
			}
			newAgendaFloatViewHtml += createFloatingTaskHtml(listOfTasks[i]);
			isExistFloatingTasks = true;
		}
		else {
			break;
		}
	}

	newAgendaFloatViewHtml += HTMLTAGS_END;
	return newAgendaFloatViewHtml;
}

string WhatToDo::createDateTitleHtml(ptime titleDate){
	string titleHtml;
	string formattedDate;
	string dayOfWeek = changeDayToDayOfWeek(titleDate.date().day_of_week());
	string monthOfYear = changeMonthToMonthOfYear(titleDate.date().month());

	if (titleDate.date() < second_clock::local_time().date()) {
		formattedDate += dayOfWeek;
		formattedDate += STRING_COMMA_CHAR + STRING_SPACE_CHAR + to_string(titleDate.date().day()) + STRING_SPACE_CHAR + monthOfYear + STRING_SPACE_CHAR + to_string(titleDate.date().year());
		titleHtml = HTMLTAGS_TITLE_DATE_PRE + HTMLTAGS_BACKGROUND_PAST_PRE + formattedDate + HTMLTAGS_BACKGROUND_PAST_POST + HTMLTAGS_TITLE_DATE_POST;
	}
	else if (titleDate.date() == second_clock::local_time().date()) {
		formattedDate += GUI_PARAM_DISPLAY_DATE_TODAY;
		formattedDate += STRING_COMMA_CHAR + STRING_SPACE_CHAR + to_string(titleDate.date().day()) + STRING_SPACE_CHAR + monthOfYear + STRING_SPACE_CHAR + to_string(titleDate.date().year());
		titleHtml = HTMLTAGS_TITLE_DATE_PRE + formattedDate + HTMLTAGS_TITLE_DATE_POST;
	}
	else {
		formattedDate += dayOfWeek;
		formattedDate += STRING_COMMA_CHAR + STRING_SPACE_CHAR + to_string(titleDate.date().day()) + STRING_SPACE_CHAR + monthOfYear + STRING_SPACE_CHAR + to_string(titleDate.date().year());
		titleHtml = HTMLTAGS_TITLE_DATE_PRE + formattedDate + HTMLTAGS_TITLE_DATE_POST;
	}

	return titleHtml;
}

string WhatToDo::createPreNumberingHtml(int startNumber) {
	string preNumberingHtml;
	preNumberingHtml = HTMLTAGS_NUMBERING_PRE + to_string(startNumber) + HTMLTAGS_NUMBERING_POST;
	return preNumberingHtml;
}

string WhatToDo::createFloatingTaskHtml(Task taskToProcess) {
	string fullTaskHtml;
	string taskNameTagsHtml = getTaskNameTagsHtml(taskToProcess);
	fullTaskHtml += getHtmlPreTaskTags(taskToProcess);
	fullTaskHtml += getLastActionTextIndexHtml(taskToProcess);
	
	if (taskToProcess.getTaskIsDone()) {
		fullTaskHtml += HTMLTAGS_TASK_DONE_PRE + HTMLTAGS_TASK_DONE_POST + taskNameTagsHtml;
	}
	else {
		fullTaskHtml += taskNameTagsHtml + HTMLTAGS_TASK_POST;
	}
	return fullTaskHtml;
}

string WhatToDo::createNonFloatingTaskHtml(Task taskToProcess) {
	string fullTaskHtml;
	string partialTaskHtml;
	string taskNameTagsHtml;
	ptime taskFirstDisplayTime;
	ptime taskSecondDisplayTime;

	fullTaskHtml += getHtmlPreTaskTags(taskToProcess);
	fullTaskHtml += getLastActionTextIndexHtml(taskToProcess);

	if (taskToProcess.getTaskIsDone()) {
		fullTaskHtml += HTMLTAGS_TASK_DONE_PRE + HTMLTAGS_TASK_DONE_POST;
	}

	taskNameTagsHtml = getTaskNameTagsHtml(taskToProcess);

	if (taskToProcess.getTaskType() == Task::DEADLINE_ALLDAY) {
		partialTaskHtml = HTMLTAGS_TASK_NAMETAGS_PRE_DEADLINE_ALLDAY + HTMLTAGS_TASK_NAMETAGS_POST + taskNameTagsHtml;
	}
	else if (taskToProcess.getTaskType() == Task::DEADLINE_TIME) {
		taskFirstDisplayTime = taskToProcess.getTaskDeadline();
		partialTaskHtml = HTMLTAGS_TASK_NAMETAGS_POST_DEADLINE_TIMED + getDisplayTime(taskFirstDisplayTime) + HTMLTAGS_TASK_NAMETAGS_POST + taskNameTagsHtml;
	}
	else if (taskToProcess.getTaskType() == Task::FIXED_ALLDAY) {
		partialTaskHtml = HTMLTAGS_TASK_NAMETAGS_POST_FIXED_ALLDAY + HTMLTAGS_TASK_NAMETAGS_POST + taskNameTagsHtml;
	}
	else if (taskToProcess.getTaskType() == Task::FIXED_START) {
		taskFirstDisplayTime = taskToProcess.getTaskStartTime();
		partialTaskHtml = HTMLTAGS_TASK_NAMETAGS_POST_FIXED_START + getDisplayTime(taskFirstDisplayTime) + HTMLTAGS_TASK_NAMETAGS_POST + taskNameTagsHtml;
	}
	else if (taskToProcess.getTaskType() == Task::FIXED_TIME) {
		taskFirstDisplayTime = taskToProcess.getTaskStartTime();
		taskSecondDisplayTime = taskToProcess.getTaskEndTime();
		if (taskFirstDisplayTime.date() == taskSecondDisplayTime.date()) {
			partialTaskHtml = HTMLTAGS_TASK_NAMETAGS_POST_FIXED_TIMED + getDisplayTime(taskFirstDisplayTime) + HTMLTAGS_TASK_NAMETAGS_MID_FIXED_START + getDisplayTime(taskSecondDisplayTime) + HTMLTAGS_TASK_NAMETAGS_POST + taskNameTagsHtml;
		}
		else {
			partialTaskHtml = HTMLTAGS_TASK_NAMETAGS_POST_FIXED_TIMED + getDisplayTime(taskFirstDisplayTime) + HTMLTAGS_TASK_NAMETAGS_MID_FIXED_START + getDisplayDay(taskSecondDisplayTime) + HTMLTAGS_TASK_NAMETAGS_POST + taskNameTagsHtml;
		}
	}

	fullTaskHtml += partialTaskHtml + HTMLTAGS_TASK_POST;
	return fullTaskHtml;
}

string WhatToDo::getTaskNameTagsHtml(Task myTask) {
	string taskNameTagsHtml;
	int i;

	taskNameTagsHtml += myTask.getTaskName();
	taskNameTagsHtml += HTMLTAGS_TASK_TAGS_PRE;

	for (i=0; unsigned(i)<myTask.getTaskTags().size(); i++) {
		taskNameTagsHtml += myTask.getTaskTags()[i] + STRING_SPACE_CHAR;
	}

	taskNameTagsHtml += HTMLTAGS_TASK_TAGS_POST;

	return taskNameTagsHtml;
}

string WhatToDo::getLastActionTextIndexHtml(Task taskToProcess) {
	string lastActionTextIndexHtml = STRING_EMPTY;
	int lastActionType = _currState.getLastActionType();
	int lastActionTaskIndex = _currState.getLastActionTaskIndex();

	if ((lastActionType == State::CHANGED) || (lastActionType == State::DELETED)) {
		if (lastActionTaskIndex == taskToProcess.getTaskIndex()) {
			lastActionTextIndexHtml += HTMLTAGS_TASK_INDEX_SPECIAL_MARKER;
		}
	}

	return lastActionTextIndexHtml;
}

string WhatToDo::getHtmlPreTaskTags(Task taskToProcess) {
	string htmlPreTaskTags = STRING_EMPTY;
	int lastActionTaskIndex = _currState.getLastActionTaskIndex();
	int lastActionType = _currState.getLastActionType();
	
	if (lastActionType != State::NONE) {
		if (taskToProcess.getTaskIndex() == lastActionTaskIndex) {
			htmlPreTaskTags = HTMLTAGS_TASK_PRE_CHANGED;
		}
		else {
			htmlPreTaskTags = HTMLTAGS_TASK_PRE_UNCHANGED;
		}
	}
	else {
		htmlPreTaskTags = HTMLTAGS_TASK_PRE_UNCHANGED;
	}

	return htmlPreTaskTags;
}




ptime WhatToDo::getTaskOrderingDate(Task myTask) {
	if (myTask.getTaskType() == Task::FLOATING) {
		return not_a_date_time;
	}
	else if (myTask.getTaskType() == Task::DEADLINE_ALLDAY) {
		return myTask.getTaskDeadline();
	}
	else if (myTask.getTaskType() == Task::DEADLINE_TIME) {
		return myTask.getTaskDeadline();
	}
	else if (myTask.getTaskType() == Task::FIXED_ALLDAY) {
		return myTask.getTaskStartTime();
	}
	else if (myTask.getTaskType() == Task::FIXED_START) {
		return myTask.getTaskStartTime();
	}
	else if (myTask.getTaskType() == Task::FIXED_TIME) {
		return myTask.getTaskStartTime();
	}
	return not_a_date_time;
}

string WhatToDo::getDisplayTime(ptime myTime) {
	string hours = STRING_EMPTY;
	string minutes = STRING_EMPTY;
	string displayTime = STRING_EMPTY;
	string pmOrAm = STRING_EMPTY;

	if (myTime.time_of_day().minutes() == 0) {
		minutes = STRING_EMPTY;
	}
	else if (myTime.time_of_day().minutes() < 10) {
		minutes = STRING_DOT_CHAR + STRING_ZERO_CHAR + to_string(myTime.time_of_day().minutes());
	}
	else {
		minutes = STRING_DOT_CHAR + to_string(myTime.time_of_day().minutes());
	}

	if (myTime.time_of_day().hours() < 12) {
		pmOrAm = STRING_AM;
		hours = to_string(myTime.time_of_day().hours());
	}
	else if (myTime.time_of_day().hours() == 12) {
		pmOrAm = STRING_PM;
		hours = to_string(12);
	}
	else if (myTime.time_of_day().hours() >= 12) {
		pmOrAm = STRING_PM;
		hours = to_string(myTime.time_of_day().hours()-12);
	}

	displayTime = hours + minutes + pmOrAm;

	return displayTime;
}

string WhatToDo::getDisplayDay(ptime myTime) {
	string displayDay;
	displayDay += to_string(myTime.date().day());
	displayDay += STRING_SPACE_CHAR + changeMonthToMonthOfYear(myTime.date().month());
	displayDay += STRING_SPACE_CHAR + getDisplayTime(myTime);
	return displayDay;
}

string WhatToDo::removeUnwantedChars(string stringToProcess) {
	boost::replace_all(stringToProcess, STRING_NEWLN_CHAR, STRING_EMPTY);
	boost::replace_all(stringToProcess, STRING_RETURN_CHAR, STRING_EMPTY);
	return stringToProcess;
}

string WhatToDo::changeDayToDayOfWeek(int day) {
	if (day == 1) {
		return ABBREV_WEEK_MON;
	}
	else if (day == 2) {
		return ABBREV_WEEK_TUE;
	}
	else if (day == 3) {
		return ABBREV_WEEK_WED;
	}
	else if (day == 4) {
		return ABBREV_WEEK_THU;
	}
	else if (day == 5) {
		return ABBREV_WEEK_FRI;
	}
	else if (day == 6) {
		return ABBREV_WEEK_SAT;
	}
	else if (day == 0) {
		return ABBREV_WEEK_SUN;
	}
	
	return STRING_EMPTY;
}

string WhatToDo::changeMonthToMonthOfYear(int month) {
	if (month == 1) {
		return ABBREV_MONTH_JAN;
	}
	else if (month == 2) {
		return ABBREV_MONTH_FEB;
	}
	else if (month == 3) {
		return ABBREV_MONTH_MAR;
	}
	else if (month == 4) {
		return ABBREV_MONTH_APR;
	}
	else if (month == 5) {
		return ABBREV_MONTH_MAY;
	}
	else if (month == 6) {
		return ABBREV_MONTH_JUN;
	}
	else if (month == 7) {
		return ABBREV_MONTH_JUL;
	}
	else if (month == 8) {
		return ABBREV_MONTH_AUG;
	}
	else if (month == 9) {
		return ABBREV_MONTH_SEP;
	}
	else if (month == 10) {
		return ABBREV_MONTH_OCT;
	}
	else if (month == 11) {
		return ABBREV_MONTH_NOV;
	}
	else if (month == 12) {
		return ABBREV_MONTH_DEC;
	}

	return STRING_EMPTY;
}

string WhatToDo::convertTaskToEditText(Task taskToConvert) {
	string taskEditText;
	vector<string> taskTags = taskToConvert.getTaskTags();
	int i;
	
	taskEditText += taskToConvert.getTaskName();
	taskEditText += STRING_SPACE_CHAR + getTaskDateAsEditText(taskToConvert);
	for (i=0; unsigned(i)<taskTags.size();  i++) {
		taskEditText += STRING_SPACE_CHAR + taskTags[i];
	}
	return taskEditText;
}

string WhatToDo::getTaskDateAsEditText(Task taskToConvert) {
	string taskDateEditText;
	if (taskToConvert.getTaskType() == Task::FLOATING) {
		taskDateEditText = STRING_EMPTY;
	}
	else if (taskToConvert.getTaskType() == Task::DEADLINE_ALLDAY) {
		taskDateEditText = COMMAND_PARAM_ADD_DATE_DEADLINE + STRING_SPACE_CHAR + convertDateToEditText(taskToConvert.getTaskDeadline());
	}
	else if (taskToConvert.getTaskType() == Task::DEADLINE_TIME) {
		taskDateEditText = COMMAND_PARAM_ADD_DATE_DEADLINE + STRING_SPACE_CHAR + convertDateTimeToEditText(taskToConvert.getTaskDeadline());
	}
	else if (taskToConvert.getTaskType() == Task::FIXED_ALLDAY) {
		taskDateEditText = COMMAND_PARAM_ADD_DATE_TIMED_ALLDAY + STRING_SPACE_CHAR + convertDateToEditText(taskToConvert.getTaskStartTime());
	}
	else if (taskToConvert.getTaskType() == Task::FIXED_START) {
		taskDateEditText = COMMAND_PARAM_ADD_DATE_TIMED_START + STRING_SPACE_CHAR + convertDateTimeToEditText(taskToConvert.getTaskStartTime());
	}
	else if (taskToConvert.getTaskType() == Task::FIXED_TIME) {
		taskDateEditText += COMMAND_PARAM_ADD_DATE_TIMED_START + STRING_SPACE_CHAR + convertDateTimeToEditText(taskToConvert.getTaskStartTime());
		taskDateEditText += COMMAND_PARAM_ADD_DATE_TIMED_END + STRING_SPACE_CHAR + convertDateTimeToEditText(taskToConvert.getTaskEndTime());
	}

	return taskDateEditText;
}

string WhatToDo::convertDateTimeToEditText(ptime timeToConvert) {
	string dateTimeEditText;
	dateTimeEditText = to_string(timeToConvert.date().day()) + STRING_SPACE_CHAR + changeMonthToMonthOfYear(timeToConvert.date().month()) + STRING_SPACE_CHAR + to_string(timeToConvert.date().year()) + STRING_SPACE_CHAR + getDisplayTime(timeToConvert) + STRING_SPACE_CHAR;
	return dateTimeEditText;
}

string WhatToDo::convertDateToEditText(ptime timeToConvert) {
	string dateEditText;
	dateEditText = to_string(timeToConvert.date().day()) + STRING_SPACE_CHAR + changeMonthToMonthOfYear(timeToConvert.date().month()) + STRING_SPACE_CHAR + to_string(timeToConvert.date().year()) + STRING_SPACE_CHAR;
	return dateEditText;
}




