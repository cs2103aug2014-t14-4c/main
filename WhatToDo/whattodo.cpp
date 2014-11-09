//****************************************************************************
//@author A0110648L

#include "whattodo.h"


WhatToDo::WhatToDo(string exeDirectory, QWidget *parent)
	: QMainWindow(parent) {
	_exeDirectory = exeDirectory;
	_ui.setupUi(this);
	setupOtherUIConfigs();
	setupCalendar();
	setupKeyPressEater();
	defineAllHotkeys();
	connectAllOtherSignalAndSlots();
	loadSavedSettings();
}

WhatToDo::~WhatToDo() {
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

void WhatToDo::handleEntryFieldTab() {
	if (_ui.commandLine->hasFocus()) {
		_ui.commandSearch->setFocus();
	}
	else {
		_ui.commandLine->setFocus();
	}
	return;
}

void WhatToDo::handleEntryIntoSearchBar() {
	_ui.commandSearch->setFocus();
	_ui.commandSearch->selectAll();
	return;
}

void WhatToDo::handleSearchBarChange() {
	updateGUIFromSearchBar();
	return;
}


void WhatToDo::handleHotkeyMinimize() {
	this->showMinimized();
	return;
}

void WhatToDo::handleHotkeyEdit() {
	_ui.commandLine->setFocus();

	// Add the command parameter into the command entry field

	_ui.commandLine->setPlainText(
		QString::fromStdString(COMMAND_PARAM_EDIT + 
		STRING_SPACE_CHAR));
	
	// Move cursor to the end of the command entry field

	QTextCursor cursor = _ui.commandLine->textCursor();
	cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
	_ui.commandLine->setTextCursor(cursor);
	return;
}

void WhatToDo::handleHotkeyDelete() {
	_ui.commandLine->setFocus();

	// Add the command parameter into the command entry field

	_ui.commandLine->setPlainText(
		QString::fromStdString(COMMAND_PARAM_DELETE + 
		STRING_SPACE_CHAR));
	
	// Move cursor to the end of the command entry field

	QTextCursor cursor = _ui.commandLine->textCursor();
	cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
	_ui.commandLine->setTextCursor(cursor);
	return;
}

void WhatToDo::handleHotkeyDone() {
	_ui.commandLine->setFocus();
	
	// Add the command parameter into the command entry field

	_ui.commandLine->setPlainText(
		QString::fromStdString(COMMAND_PARAM_DONE + 
		STRING_SPACE_CHAR));
	
	// Move cursor to the end of the command entry field

	QTextCursor cursor = _ui.commandLine->textCursor();
	cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
	_ui.commandLine->setTextCursor(cursor);
	return;
}

void WhatToDo::handleHotkeyUndone() {
	_ui.commandLine->setFocus();
	
	// Add the command parameter into the command entry field

	_ui.commandLine->setPlainText(
		QString::fromStdString(COMMAND_PARAM_UNDONE + 
		STRING_SPACE_CHAR));
	
	// Move cursor to the end of the command entry field

	QTextCursor cursor = _ui.commandLine->textCursor();
	cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
	_ui.commandLine->setTextCursor(cursor);
	return;
}

void WhatToDo::handleHotkeyFilter() {
	_ui.commandLine->setFocus();
	
	// Add the command parameter into the command entry field

	_ui.commandLine->setPlainText(
		QString::fromStdString(COMMAND_PARAM_FILTER + 
		STRING_SPACE_CHAR));
	
	// Move cursor to the end of the command entry field

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
	updateCalendarView();
	
	// Move the calendar to a viewable position in the GUi
	
	_ui.calendarframe->move(20, 70);
	_ui.calendarbtn_next->move(290, 10);
	_ui.calendarbtn_prev->move(220, 10);

	// Bring the calendar to the front of all elements in the GUi
	// so it may be visible to the user

	_ui.calendarframe->raise();
	_ui.calendarbtn_next->raise();
	_ui.calendarbtn_prev->raise();
	return;
}

void WhatToDo::handleButtonCalendarPrev(){
	_SFMLView->prevPage();
}

void WhatToDo::handleButtonCalendarNext(){
	_SFMLView->nextPage();
}

void WhatToDo::handleButtonToggleAgenda() {
	updateAgendaView();
	
	// Move the calendar to an out-of-sight position in the GUi
	
	_ui.calendarframe->move(9999, 9999);
	_ui.calendarbtn_next->move(9999, 9999);
	_ui.calendarbtn_prev->move(9999, 9999);
}

void WhatToDo::handleCalendarCommands(string command) {
	updateGUIWithCommandString(command);
}



void WhatToDo::setupCalendar() {
	
	// Move the calendar frame to an out-of-sight position 
	// in the GUi initially
	
	_ui.calendarframe->move(9999, 9999);
	_ui.calendarbtn_next->move(9999, 9999);
	_ui.calendarbtn_prev->move(9999, 9999);
	_ui.calendarframe->setAttribute(Qt::WA_TransparentForMouseEvents);

	// Create the calendar view and show it to the user

	_SFMLView = new CalendarCanvas(this, _ui.calendarframe, 
		QPoint(0, 0), QSize(921, 501));
	_SFMLView->show();
	_b_calender_init_complete = true;
	return;
}

void WhatToDo::setupKeyPressEater() {
	_myKeyPressEater = new KeyPressEater();
	_ui.commandLine->installEventFilter(_myKeyPressEater);
	_ui.commandSearch->installEventFilter(_myKeyPressEater);
	return;
}

void WhatToDo::setupOtherUIConfigs() {
	setupInitialGUIFocusConfigs();
	setupInitialGUISizeConfigs();
	setupMessageBoxConfigs();
	setupTextSizeConfigs();
	return;
}

void WhatToDo::connectAllOtherSignalAndSlots() {
	QObject* decViewPointer;

	decViewPointer = _ui.buttonUndo->rootObject();
	connect(decViewPointer, SIGNAL(buttonClick()), 
		this, SLOT(handleButtonUndo()));
	decViewPointer = _ui.buttonRedo->rootObject();
	connect(decViewPointer, SIGNAL(buttonClick()), 
		this, SLOT(handleButtonRedo()));
	decViewPointer = _ui.buttonAgendaview->rootObject();
	connect(decViewPointer, SIGNAL(buttonClick()), 
		this, SLOT(handleButtonToggleAgenda()));
	decViewPointer = _ui.buttonCalendarview->rootObject();
	connect(decViewPointer, SIGNAL(buttonClick()), 
		this, SLOT(handleButtonToggleCalendar()));
	connect(_myKeyPressEater, SIGNAL(enterPressed(QObject*)), 
		this, SLOT(handleKeyPressEvents(QObject*)));
	connect(_myKeyPressEater, SIGNAL(tabPressed()), 
		this, SLOT(handleEntryFieldTab()));
	connect(_ui.commandSearch, SIGNAL(textChanged()), 
		this, SLOT(handleSearchBarChange()));
	connect(_ui.calendarbtn_prev, SIGNAL(released()),
		this, SLOT(handleButtonCalendarPrev()));
	connect(_ui.calendarbtn_next, SIGNAL(released()),
		this, SLOT(handleButtonCalendarNext()));

	return;
}

void WhatToDo::defineAllHotkeys() {
	
	// Define the QAction objects used to define hotkeys

	QAction *hotkeyUndo = new QAction(this);
	QAction *hotkeyRedo = new QAction(this);
	QAction *hotkeyFind = new QAction(this);
	QAction *hotkeyMinimize = new QAction(this);
	QAction *hotkeyDelete = new QAction(this);
	QAction *hotkeyEdit = new QAction(this);
	QAction *hotkeyDone = new QAction(this);
	QAction *hotkeyUndone = new QAction(this);
	QAction *hotkeyFilter = new QAction(this);
	QAction *hotkeyClear = new QAction(this);
	QAction *hotkeyHelp = new QAction(this);

	// Define the hotkeys available to the user

	hotkeyUndo->setShortcut(Qt::Key_S | Qt::CTRL | Qt::SHIFT);
	hotkeyRedo->setShortcut(Qt::Key_D | Qt::CTRL | Qt::SHIFT);
	hotkeyFind->setShortcut(Qt::Key_F | Qt::CTRL);
	hotkeyMinimize->setShortcut(Qt::Key_Space | Qt::CTRL);
	hotkeyDelete->setShortcut(Qt::Key_W | Qt::CTRL);
	hotkeyEdit->setShortcut(Qt::Key_E | Qt::CTRL);
	hotkeyDone->setShortcut(Qt::Key_D | Qt::CTRL);
	hotkeyUndone->setShortcut(Qt::Key_R | Qt::CTRL);
	hotkeyFilter->setShortcut(Qt::Key_Q | Qt::CTRL);
	hotkeyClear->setShortcut(Qt::Key_Escape);
	hotkeyHelp->setShortcut(Qt::Key_H | Qt::CTRL);

	// Connect the defined hotkeys to the relevant event handlers

	connect(hotkeyUndo, SIGNAL(triggered()), 
		this, SLOT(handleButtonUndo()));
	connect(hotkeyRedo, SIGNAL(triggered()), 
		this, SLOT(handleButtonRedo()));
	connect(hotkeyFind, SIGNAL(triggered()), 
		this, SLOT(handleEntryIntoSearchBar()));
	connect(hotkeyMinimize, SIGNAL(triggered()), 
		this, SLOT(handleHotkeyMinimize()));
	connect(hotkeyDelete, SIGNAL(triggered()), 
		this, SLOT(handleHotkeyDelete()));
	connect(hotkeyEdit, SIGNAL(triggered()), 
		this, SLOT(handleHotkeyEdit()));
	connect(hotkeyDone, SIGNAL(triggered()), 
		this, SLOT(handleHotkeyDone()));
	connect(hotkeyUndone, SIGNAL(triggered()), 
		this, SLOT(handleHotkeyUndone()));
	connect(hotkeyFilter, SIGNAL(triggered()), 
		this, SLOT(handleHotkeyFilter()));
	connect(hotkeyClear, SIGNAL(triggered()), 
		this, SLOT(handleHotkeyClear()));
	connect(hotkeyHelp, SIGNAL(triggered()), 
		this, SLOT(handleHotkeyHelp()));

	// Add these defined hotkeys to the GUI

	_ui.centralWidget->addAction(hotkeyUndo);
	_ui.centralWidget->addAction(hotkeyRedo);
	_ui.centralWidget->addAction(hotkeyFind);
	_ui.centralWidget->addAction(hotkeyMinimize);
	_ui.centralWidget->addAction(hotkeyDelete);
	_ui.centralWidget->addAction(hotkeyEdit);
	_ui.centralWidget->addAction(hotkeyDone);
	_ui.centralWidget->addAction(hotkeyUndone);
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


void WhatToDo::setupInitialGUIFocusConfigs() {
	_ui.commandLine->setFocus();
	return;
}

void WhatToDo::setupInitialGUISizeConfigs() {
	this->setFixedSize(GUI_PARAM_SIZE_WIDTH, GUI_PARAM_SIZE_HEIGHT);
	return;
}

void WhatToDo::setupMessageBoxConfigs() {

	// Set the message box view as transparent to the user and 
	// transparent to mouse events

	_ui.messageFeedback->setAttribute(Qt::WA_TranslucentBackground);
	_ui.messageFeedback->setStyleSheet(
		QString::fromStdString(QTSTYLESHEET_TRANSPARENT_BACKGROUND));
	_ui.messageFeedback->setAttribute(Qt::WA_TransparentForMouseEvents);
	return;
}

void WhatToDo::setupTextSizeConfigs() {
	_ui.displayAgendaviewFloat->setTextSizeMultiplier(
		GUI_PARAM_TEXT_MULTIPLIER);
	_ui.displayAgendaviewTimed->setTextSizeMultiplier(
		GUI_PARAM_TEXT_MULTIPLIER);
	return;
}



void WhatToDo::showLogicUserFeedback() {
	string userMessage = _currState.getUserMessage();
	string actionMessage = _currState.getActionMessage();

	// If there is a user-message to display, set the user message
	// in the popup and start the animation for the popup.
	//
	// Otherwise, if there is no user message to display, update the
	// statusbar with the correct user action message

	if (userMessage != STRING_EMPTY) {
		QObject* decViewPointer = _ui.messageFeedback->rootObject();
		decViewPointer->setProperty(
			GUI_PARAM_POPUP_PROPERTY_MESSAGE.c_str(), 
			QString::fromStdString(userMessage));
		decViewPointer->setProperty(
			GUI_PARAM_POPUP_PROPERTY_OPACITY.c_str(), 1.0);
		decViewPointer->setProperty(
			GUI_PARAM_POPUP_PROPERTY_ISANIMATE.c_str(), false);
		decViewPointer->setProperty(
			GUI_PARAM_POPUP_PROPERTY_ISANIMATE.c_str(), true);
		_currState.setUserMessage(STRING_EMPTY);
		_ui.statusBar->setPlainText(
			QString::fromStdString(GUI_PARAM_STATUS_TITLE + 
			userMessage));
	}
	else {
		_ui.statusBar->setPlainText(
			QString::fromStdString(GUI_PARAM_STATUS_TITLE + 
			actionMessage));
	}
	return;
}

void WhatToDo::showGUIUserFeedback(string guiUserFeedback) {
	
	// Set the user message in the popup and start the animation 
	// for the popup, taking the input parameter guiUserFeedback
	// as the user message to be displayed.

	QObject* decViewPointer = _ui.messageFeedback->rootObject();
	decViewPointer->setProperty(
		GUI_PARAM_POPUP_PROPERTY_MESSAGE.c_str(), 
		QString::fromStdString(guiUserFeedback));
	decViewPointer->setProperty(
		GUI_PARAM_POPUP_PROPERTY_OPACITY.c_str(), 1.0);
	decViewPointer->setProperty(
		GUI_PARAM_POPUP_PROPERTY_ISANIMATE.c_str(), false);
	decViewPointer->setProperty(
		GUI_PARAM_POPUP_PROPERTY_ISANIMATE.c_str(), true);
	_currState.setActionMessage(STRING_EMPTY);
	_ui.statusBar->setPlainText(
		QString::fromStdString(
		GUI_PARAM_STATUS_TITLE + guiUserFeedback));
	return;
}


void WhatToDo::updateGUIFromSearchBar() {
	string userSearchString;
	string logicComandString;

	userSearchString = 
		_ui.commandSearch->toPlainText().toStdString();
	userSearchString = removeUnwantedChars(userSearchString);
	
	// Only construct and process a search command for the user 
	// automatically when the search bar's contents are not empty.
	//
	// If the search bar's contents are empty, construct and process
	// a clear command for the user automatically.

	if (userSearchString == STRING_EMPTY) {
		logicComandString = COMMAND_PARAM_CLEAR;
	}
	else {
		logicComandString = COMMAND_PARAM_SEARCH + STRING_SPACE_CHAR + 
			userSearchString;
	}

	updateGUIWithCommandString(logicComandString);
	return;
}

void WhatToDo::updateGUIFromCommandLine() {
	bool isUserCommandValid;
	string usercommandString;
	string logicComandString;

	usercommandString = 
		_ui.commandLine->toPlainText().toStdString();
	usercommandString = 
		removeUnwantedChars(usercommandString);

	_ui.commandLine->setHtml(QString::fromStdString(STRING_EMPTY));
	
	// Only process the user's command when it is valid. Otherwise,
	// show any error message that was created because of invalid commands.

	try {
		checkIsUserCommandInputValid(usercommandString);
		updateGUIWithCommandString(usercommandString);
	}
	catch (string errMsg) {
		showGUIUserFeedback(errMsg);
	}

	return;
}

void WhatToDo::updateGUIWithCommandString(string commandString) {
	int commandType;

	try {
		commandType = determineCommandType(commandString);
	}
	catch (string errorMsg) {
		return;
	}

	switch (commandType) {
		case COMMAND_DONE_WITH_REAL_INDEX: {
			try {
				processCommandDone(commandString, true);
			}
			catch (string errorMsg) {
				showGUIUserFeedback(errorMsg);
			}
			break;
		}
		case COMMAND_UNDONE_WITH_REAL_INDEX: {
			try {
				processCommandUndone(commandString, true);
			}
			catch (string errorMsg) {
				showGUIUserFeedback(errorMsg);
			}
			break;
		}
		case COMMAND_DELETE_WITH_REAL_INDEX: {
			try {
				processCommandDelete(commandString, true);
			}
			catch (string errorMsg) {
				showGUIUserFeedback(errorMsg);
			}
			break;
		}
		case COMMAND_EDIT: {
			try {
				processCommandEdit(commandString);
			}
			catch (string errorMsg) {
				showGUIUserFeedback(errorMsg);
			}
			break;
		}
		case COMMAND_DONE: {
			try {
				processCommandDone(commandString, false);
			}
			catch (string errorMsg) {
				showGUIUserFeedback(errorMsg);
			}
			break;
		}
		case COMMAND_UNDONE: {
			try {
				processCommandUndone(commandString, false);
			}
			catch (string errorMsg) {
				showGUIUserFeedback(errorMsg);
			}
			break;
		}
		case COMMAND_DELETE: {
			try {
				processCommandDelete(commandString, false);
			}
			catch (string errorMsg) {
				showGUIUserFeedback(errorMsg);
			}
			break;
		}
		case COMMAND_UNDO: {
			try {
				processCommandOthers(commandString);
				processCommandOthers(COMMAND_PARAM_CLEAR);
			}
			catch (string errorMsg) {
				showGUIUserFeedback(errorMsg);
			}
			break;
		}
		case COMMAND_OTHERS: {
			try {
				processCommandOthers(commandString);
			}
			catch (string errorMsg) {
				return;
			}
			break;
		}
		case COMMAND_HELP: {
			string fullHelpDirectory = 
				_exeDirectory + RESOURCE_PATHS_HELP_CONTENT;
			_ui.displayAgendaviewTimed->load(
				QUrl::fromLocalFile(
				QString::fromStdString(fullHelpDirectory)));
			break;
		}
		case COMMAND_HELP_ADD: {
			string fullHelpDirectory = 
				_exeDirectory + RESOURCE_PATHS_HELP_ADD;
			_ui.displayAgendaviewTimed->load(
				QUrl::fromLocalFile(
				QString::fromStdString(fullHelpDirectory)));
			break;
		}
		case COMMAND_HELP_EDIT: {
			string fullHelpDirectory = 
				_exeDirectory + RESOURCE_PATHS_HELP_EDIT;
			_ui.displayAgendaviewTimed->load(
				QUrl::fromLocalFile(
				QString::fromStdString(fullHelpDirectory)));
			break;
		}
		case COMMAND_HELP_DONE: {
			string fullHelpDirectory = 
				_exeDirectory + RESOURCE_PATHS_HELP_DONE;
			_ui.displayAgendaviewTimed->load(
				QUrl::fromLocalFile(
				QString::fromStdString(fullHelpDirectory)));
			break;
		}
		case COMMAND_HELP_DELETE: {
			string fullHelpDirectory = 
				_exeDirectory + RESOURCE_PATHS_HELP_DELETE;
			_ui.displayAgendaviewTimed->load(
				QUrl::fromLocalFile(
				QString::fromStdString(fullHelpDirectory)));
			break;
		}
		case COMMAND_HELP_SEARCH: {
			string fullHelpDirectory = 
				_exeDirectory + RESOURCE_PATHS_HELP_SEARCH;
			_ui.displayAgendaviewTimed->load(
				QUrl::fromLocalFile(
				QString::fromStdString(fullHelpDirectory)));
			break;
		}
		case COMMAND_HELP_CLEAR: {
			string fullHelpDirectory = 
				_exeDirectory + RESOURCE_PATHS_HELP_CLEAR;
			_ui.displayAgendaviewTimed->load(
				QUrl::fromLocalFile(
				QString::fromStdString(fullHelpDirectory)));
			break;
		}
		case COMMAND_HELP_UNDO: {
			string fullHelpDirectory = 
				_exeDirectory + RESOURCE_PATHS_HELP_UNDO;
			_ui.displayAgendaviewTimed->load(
				QUrl::fromLocalFile(
				QString::fromStdString(fullHelpDirectory)));
			break;
		}
		case COMMAND_HELP_REDO: {
			string fullHelpDirectory = 
				_exeDirectory + RESOURCE_PATHS_HELP_REDO;
			_ui.displayAgendaviewTimed->load(
				QUrl::fromLocalFile(
				QString::fromStdString(fullHelpDirectory)));
			break;
		}
		case COMMAND_HELP_FILTER: {
			string fullHelpDirectory = 
				_exeDirectory + RESOURCE_PATHS_HELP_FILTER;
			_ui.displayAgendaviewTimed->load(
				QUrl::fromLocalFile(
				QString::fromStdString(fullHelpDirectory)));
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
	
	// Set the display as the help menu when there are no tasks
	// to display

	if (checkIsCurrentStateEmpty()) {
		updateGUIWithCommandString(COMMAND_PARAM_HELP);
		_ui.displayAgendaviewFloat->setHtml(
			QString::fromStdString(STRING_EMPTY));
		return;
	}

	// Get the new html strings for both agenda views according to the 
	// current state in this particular whattodo instance.

	newAgendaTimedViewHtml = getAgendaTimedViewHtml();
	newAgendaFloatViewHtml = getAgendaFloatViewHtml();
	
	// Get the initial scroll positions for both the agenda floating 
	// and agenda timed views

	timedViewScrollPos = 
		_ui.displayAgendaviewTimed->page()->mainFrame()->
		scrollBarValue(Qt::Vertical);
	floatViewScrollPos = 
		_ui.displayAgendaviewFloat->page()->mainFrame()->
		scrollBarValue(Qt::Vertical);
	
	_ui.displayAgendaviewTimed->setHtml(
		QString::fromStdString(newAgendaTimedViewHtml));
	_ui.displayAgendaviewFloat->setHtml(
		QString::fromStdString(newAgendaFloatViewHtml));
	
	markLastActionForUser(timedViewScrollPos, floatViewScrollPos);
	
	return;
}

void WhatToDo::updateCalendarView() {
	if (_b_calender_init_complete)
		_SFMLView->readFromState(_currState);
}

void WhatToDo::markLastActionForUser(int timedViewScrollPos, int floatViewScrollPos) {
	int newtimedViewScrollPos;
	int newfloatViewScrollPos;
	int lastActionTaskIndex = _currState.getLastActionTaskIndex();
	int lastActionType = _currState.getLastActionType();
	string lastActionElementID;
	QWebElement theChangedTaskElement;
	QWebElement tempTaskElement;
	QWebFrame* floatViewWebFrame = 
		_ui.displayAgendaviewFloat->page()->mainFrame();
	QWebFrame* timedViewWebFrame = 
		_ui.displayAgendaviewTimed->page()->mainFrame();
	
	// If there is was no last action to highlight, set the scroll 
	// bar to the original state it was in before updating the view

	if (lastActionType == State::NONE) {
		floatViewWebFrame->setScrollBarValue(
			Qt::Vertical, floatViewScrollPos);
		timedViewWebFrame->setScrollBarValue(
			Qt::Vertical, timedViewScrollPos);
		return;
	}

	// Otherwise, if there is a last action to highlight, 
	// continue to highlight the given task.

	else {
		
		// Get the scroll positions of the text to highlight so they can
		// be set later.

		_ui.displayAgendaviewFloat->findText(
			QString::fromStdString(HTMLTAGS_CHANGED_TASK_TEXT));
		_ui.displayAgendaviewTimed->findText(
			QString::fromStdString(HTMLTAGS_CHANGED_TASK_TEXT));
		newfloatViewScrollPos = 
			_ui.displayAgendaviewFloat->page()->mainFrame()->
			scrollBarValue(Qt::Vertical);
		newtimedViewScrollPos = 
			_ui.displayAgendaviewTimed->page()->mainFrame()->
			scrollBarValue(Qt::Vertical);
		floatViewWebFrame->setScrollBarValue(
			Qt::Vertical, newfloatViewScrollPos);
		timedViewWebFrame->setScrollBarValue(
			Qt::Vertical, newtimedViewScrollPos);
		
		// Find the new task which was changed

		tempTaskElement = 
			floatViewWebFrame->findFirstElement(
			QString::fromStdString(HTMLTAGS_CHANGED_TASK_ID));
		
		if (!tempTaskElement.isNull()) {
			theChangedTaskElement = tempTaskElement;
		}
		else {
			theChangedTaskElement = 
				timedViewWebFrame->findFirstElement(
				QString::fromStdString(HTMLTAGS_CHANGED_TASK_ID));
		}

		// For the new task which was changed, remove its visible tags
		// which were added previously for finding its scroll position

		theChangedTaskElement.setAttribute(
			QString::fromStdString(HTMLTAGS_STYLE_PROPERTY), 
			QString::fromStdString(HTMLTAGS_STYLE_PROPERTY_HIDE));
		
		// Find the new task html tag which was changed

		tempTaskElement = 
			floatViewWebFrame->findFirstElement(
			QString::fromStdString(HTMLTAGS_CHANGED_TASK_TEXT_ID));
		
		if (!tempTaskElement.isNull()) {
			theChangedTaskElement = tempTaskElement;
		}
		else {
			theChangedTaskElement = 
				timedViewWebFrame->findFirstElement(
				QString::fromStdString(
				HTMLTAGS_CHANGED_TASK_TEXT_ID));
		}

		// For the new task html tag which was changed, highlight
		// it according to the last action which was made.

		if (lastActionType == State::CHANGED) {
			theChangedTaskElement.setAttribute(
				QString::fromStdString(HTMLTAGS_STYLE_PROPERTY), 
				QString::fromStdString(
				HTMLTAGS_BACKGROUND_CHANGED_TASK));
		}
		else {
			theChangedTaskElement.setAttribute(
				QString::fromStdString(HTMLTAGS_STYLE_PROPERTY), 
				QString::fromStdString(
				HTMLTAGS_BACKGROUND_DELETED_TASK));
		}
	}

	return;
}

void WhatToDo::refreshCurrStateWithCommand(string commandString) {
	State incomingNewState = 
		LogicExecutor::getNewState(commandString);
	int lastActionType = 
		incomingNewState.getLastActionType();
	int lastActionTaskIndex = 
		incomingNewState.getLastActionTaskIndex();

	if ((lastActionType == State::CHANGED) 
			|| (lastActionType == State::NONE)){
		_currState = incomingNewState;
		_tempFutureState = incomingNewState;
	}
	else if (lastActionType == State::DELETED) {
		_currState = _tempFutureState;
		_currState.setLastActionTaskIndex(
			incomingNewState.getLastActionTaskIndex());
		_currState.setLastActionType(
			incomingNewState.getLastActionType());
		_currState.setActionMessage(
			incomingNewState.getActionMessage());
		_currState.setUserMessage(
			incomingNewState.getUserMessage());
		_tempFutureState = incomingNewState;
		
		/*
		incomingNewState = LogicExecutor::getNewState(COMMAND_PARAM_CLEAR);
		_currState = incomingNewState;
		_currState.setLastActionTaskIndex(
			incomingNewState.getLastActionTaskIndex());
		_currState.setLastActionType(
			incomingNewState.getLastActionType());
		_currState.setActionMessage(
			incomingNewState.getActionMessage());
		_currState.setUserMessage(
			incomingNewState.getUserMessage());
		_tempFutureState = incomingNewState;
		*/
	}	

	return;
}



bool WhatToDo::checkIsUserCommandInputValid(	string usercommandString) {
	bool isUserCommandValid = false;
	usercommandString = removeUnwantedChars(usercommandString);

	if (checkIsContainStrangeChars(usercommandString)) {
		throw MSG_ERR_UNACCEPTED_CHARS_ENTERED;
	}

	if (usercommandString != STRING_EMPTY) {
		isUserCommandValid = true;
	}
	return isUserCommandValid;
}

int WhatToDo::determineCommandType(string usercommandString) {
	istringstream inputString(usercommandString);
	string userCommand;
	string userCommandSpecs;

	assert(usercommandString != STRING_EMPTY);
	if (!(inputString >> userCommand)) {
		throw MSG_ERROR_INSUFFICIENT_INPUT;
	}
	if (userCommand == COMMAND_PARAM_DELETE_WITH_REAL_INDEX) {
		return COMMAND_DELETE_WITH_REAL_INDEX;
	}
	else if (userCommand == COMMAND_PARAM_DONE_WITH_REAL_INDEX) {
		return COMMAND_DONE_WITH_REAL_INDEX;
	}
	else if (userCommand == COMMAND_PARAM_UNDONE_WITH_REAL_INDEX) {
		return COMMAND_UNDONE_WITH_REAL_INDEX;
	}
	else if (userCommand == COMMAND_PARAM_EDIT) {
		return COMMAND_EDIT;
	}
	else if (userCommand == COMMAND_PARAM_DONE) {
		return COMMAND_DONE;
	}
	else if (userCommand == COMMAND_PARAM_UNDONE) {
		return COMMAND_UNDONE;
	}
	else if (userCommand == COMMAND_PARAM_DELETE) {
		return COMMAND_DELETE;
	}
	else if (userCommand == COMMAND_PARAM_UNDO) {
		return COMMAND_UNDO;
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

	assert(commandString != STRING_EMPTY);

	if (inputString >> userCommand >> displayIndexToEdit) {
		
		// Update the GUI with the edit command if the user
		// entered the details of the new task to replace the old one.

		if (getline(inputString, newEditContents)) {
			
			// If the user entered a valid display index to edit, 
			// replace the display index with the actual task index
			// and update the GUi with the edit command.
			
			if ((displayIndexToEdit >= 1) 
				&& (displayIndexToEdit <= allCurrentTasks.size())) {
				
				actualIndexToEdit = 
					allCurrentTasks[displayIndexToEdit-1].getTaskIndex();
				commandToPassLogic = 
					COMMAND_PARAM_EDIT + STRING_SPACE_CHAR + 
					to_string(actualIndexToEdit) + 
					STRING_SPACE_CHAR + newEditContents;

				refreshCurrStateWithCommand(commandToPassLogic);
				updateAgendaView();
				updateCalendarView();
				showLogicUserFeedback();
			}
			
			// If the display task index is invalid, throw an error.

			else {
				throw MSG_ERROR_USER_WRONG_INDEX;
			}
		}
		
		// If the user did not enter the details of the new task to replace
		// the old one, fill in the command entry field with details
		// of the current task.

		else {
			if ((displayIndexToEdit >= 1) 
				&& (displayIndexToEdit <= allCurrentTasks.size())) {

				newEditContents = 
					convertTaskToEditText(
					allCurrentTasks[displayIndexToEdit-1]);
				textToFillCommandLine = 
					COMMAND_PARAM_EDIT + STRING_SPACE_CHAR + 
					to_string(displayIndexToEdit) + 
					STRING_SPACE_CHAR + newEditContents;
				_ui.commandLine->setPlainText(
					QString::fromStdString(textToFillCommandLine));
				QTextCursor cursor = _ui.commandLine->textCursor();
				cursor.movePosition(QTextCursor::End, 
					QTextCursor::MoveAnchor);
				_ui.commandLine->setTextCursor(cursor);
			}
			
			// If the display task index is invalid, throw an error.

			else {
				throw MSG_ERROR_USER_WRONG_INDEX;
			}
		}
	}
	return;
}

void WhatToDo::processCommandDone(string commandString, bool b_usingRealIndex) {
	istringstream inputString(commandString);
	vector<Task> allCurrentTasks = _currState.getAllTasks();
	int displayIndexToDone;
	int actualIndexToDone;
	string userCommand;
	string commandToPassLogic;

	assert(commandString != STRING_EMPTY);

	if (inputString >> userCommand >> displayIndexToDone) {
		
		// if the done command has been crafted with the true
		// task index (meaning b_usingRealIndex is true), directly
		// update the GUi with the task index in the user command.
		
		if (b_usingRealIndex) {
			commandToPassLogic = COMMAND_PARAM_DONE + 
				STRING_SPACE_CHAR + to_string(displayIndexToDone);
			refreshCurrStateWithCommand(commandToPassLogic);
			updateAgendaView();
			updateCalendarView();
			showLogicUserFeedback();
		}

		// if the done command has not been crafted with the true
		// task index, replace the display task index with the true
		// task index before sending the command to Logic.

		else if ((displayIndexToDone >= 1) 
			&& (displayIndexToDone <= allCurrentTasks.size())) {
			
			actualIndexToDone = 
				allCurrentTasks[displayIndexToDone-1].getTaskIndex();
			commandToPassLogic = 
				COMMAND_PARAM_DONE + STRING_SPACE_CHAR + 
				to_string(actualIndexToDone);

			refreshCurrStateWithCommand(commandToPassLogic);
			updateAgendaView();
			updateCalendarView();
			showLogicUserFeedback();
		}
		
		// If the display task index is invalid, throw an error.

		else {
			throw MSG_ERROR_USER_WRONG_INDEX;
		}
	}
	else {
		throw MSG_ERROR_USER_WRONG_PARAMS;
	}
	return;
}

void WhatToDo::processCommandUndone(string commandString, bool b_usingRealIndex) {
	istringstream inputString(commandString);
	vector<Task> allCurrentTasks = _currState.getAllTasks();
	int displayIndexToUndone;
	int actualIndexToUndone;
	string userCommand;
	string commandToPassLogic;

	assert(commandString != STRING_EMPTY);

	if (inputString >> userCommand >> displayIndexToUndone) {
		
		// if the undone command has been crafted with the true
		// task index (meaning b_usingRealIndex is true), directly
		// update the GUi with the task index in the user command.
		
		if (b_usingRealIndex){
			commandToPassLogic = COMMAND_PARAM_UNDONE + STRING_SPACE_CHAR + to_string(displayIndexToUndone);
			refreshCurrStateWithCommand(commandToPassLogic);
			updateAgendaView();
			updateCalendarView();
			showLogicUserFeedback();
		}

		// if the undone command has not been crafted with the true
		// task index, replace the display task index with the true
		// task index before sending the command to Logic.

		else if ((displayIndexToUndone >= 1) 
			&& (displayIndexToUndone <= allCurrentTasks.size())) {
			
			actualIndexToUndone = 
				allCurrentTasks[displayIndexToUndone-1].getTaskIndex();
			commandToPassLogic = 
				COMMAND_PARAM_UNDONE + STRING_SPACE_CHAR + 
				to_string(actualIndexToUndone);

			refreshCurrStateWithCommand(commandToPassLogic);
			updateAgendaView();
			updateCalendarView();
			showLogicUserFeedback();
		}
		
		// If the display task index is invalid, throw an error.

		else {
			throw MSG_ERROR_USER_WRONG_INDEX;
		}
	}
	else {
		throw MSG_ERROR_USER_WRONG_PARAMS;
	}
	return;
}

void WhatToDo::processCommandDelete(string commandString, bool b_usingRealIndex) {
	istringstream inputString(commandString);
	vector<Task> allCurrentTasks = _currState.getAllTasks();
	int displayIndexToDelete;
	int actualIndexToDelete;
	string userCommand;
	string commandToPassLogic;

	assert(commandString != STRING_EMPTY);

	if (inputString >> userCommand >> displayIndexToDelete) {
		
		// if the delete command has been crafted with the true
		// task index (meaning b_usingRealIndex is true), directly
		// update the GUi with the task index in the user command.
		
		if (b_usingRealIndex){
			commandToPassLogic = COMMAND_PARAM_DELETE + STRING_SPACE_CHAR + to_string(displayIndexToDelete);
			refreshCurrStateWithCommand(commandToPassLogic);
			updateAgendaView();
			updateCalendarView();
			showLogicUserFeedback();
		}

		// if the delete command has not been crafted with the true
		// task index, replace the display task index with the true
		// task index before sending the command to Logic.

		else if ((displayIndexToDelete >= 1) 
			&& (displayIndexToDelete <= allCurrentTasks.size())) {
			
			actualIndexToDelete = 
				allCurrentTasks[displayIndexToDelete-1].getTaskIndex();
			commandToPassLogic = 
				COMMAND_PARAM_DELETE + STRING_SPACE_CHAR + 
				to_string(actualIndexToDelete);

			refreshCurrStateWithCommand(commandToPassLogic);
			updateAgendaView();
			updateCalendarView();
			showLogicUserFeedback();
		}
		
		// If the display task index is invalid, throw an error.

		else {
			throw MSG_ERROR_USER_WRONG_INDEX;
		}
	}
	else {
		throw MSG_ERROR_USER_WRONG_PARAMS;
	}

	return;
}

void WhatToDo::processCommandOthers(string commandString) {
	assert(commandString != STRING_EMPTY);
	refreshCurrStateWithCommand(commandString);
	updateAgendaView();
	updateCalendarView();
	showLogicUserFeedback();
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
		
		// Only get html for non-floating tasks to only display
		// non-floating tasks.
		
		if (!(listOfTasks[i].getTaskType() == Task::FLOATING)) {
			nextptime = getTaskOrderingDate(listOfTasks[i]);
			if (nextptime.date() != currentptime.date()) {
				newAgendaTimedViewHtml += 
					createDateTitleHtml(nextptime);
				newAgendaTimedViewHtml += 
					createPreNumberingHtml(i+1);
				currentptime = nextptime;
			}
			newAgendaTimedViewHtml += 
				createNonFloatingTaskHtml(listOfTasks[i]);
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
		
		// Only get html for floating tasks to only display
		// floating tasks.
		
		if (listOfTasks[i].getTaskType() == Task::FLOATING) {
			if (!isExistFloatingTasks) {
				newAgendaFloatViewHtml += HTMLTAGS_TITLE_FLOATING;
			}
			newAgendaFloatViewHtml += 
				createFloatingTaskHtml(listOfTasks[i]);
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
	string dayOfWeek = 
		changeDayToDayOfWeek(titleDate.date().day_of_week());
	string monthOfYear = 
		changeMonthToMonthOfYear(titleDate.date().month());

	// If the date is already past, display the title of the date with
	// a different background.

	if (titleDate.date() < second_clock::local_time().date()) {
		formattedDate += dayOfWeek;
		formattedDate += STRING_COMMA_CHAR + STRING_SPACE_CHAR + 
			to_string(titleDate.date().day()) + STRING_SPACE_CHAR + 
			monthOfYear + STRING_SPACE_CHAR + 
			to_string(titleDate.date().year());
		titleHtml = HTMLTAGS_TITLE_DATE_PRE + 
			HTMLTAGS_BACKGROUND_PAST_PRE + formattedDate + 
			HTMLTAGS_BACKGROUND_PAST_POST + HTMLTAGS_TITLE_DATE_POST;
	}

	// If the date is today, display the title of the date with 
	// an indication that its today's date.

	else if (titleDate.date() == second_clock::local_time().date()) {
		formattedDate += GUI_PARAM_DISPLAY_DATE_TODAY;
		formattedDate += STRING_COMMA_CHAR + STRING_SPACE_CHAR + 
			to_string(titleDate.date().day()) + STRING_SPACE_CHAR + 
			monthOfYear + STRING_SPACE_CHAR + 
			to_string(titleDate.date().year());
		titleHtml = HTMLTAGS_TITLE_DATE_PRE + formattedDate + 
			HTMLTAGS_TITLE_DATE_POST;
	}

	// If the date is in the future, display the day and date of the
	// date-title.

	else {
		formattedDate += dayOfWeek;
		formattedDate += STRING_COMMA_CHAR + STRING_SPACE_CHAR + 
			to_string(titleDate.date().day()) + STRING_SPACE_CHAR + 
			monthOfYear + STRING_SPACE_CHAR + 
			to_string(titleDate.date().year());
		titleHtml = HTMLTAGS_TITLE_DATE_PRE + formattedDate + 
			HTMLTAGS_TITLE_DATE_POST;
	}

	return titleHtml;
}

string WhatToDo::createPreNumberingHtml(int startNumber) {
	string preNumberingHtml;
	preNumberingHtml = HTMLTAGS_NUMBERING_PRE + 
		to_string(startNumber) + HTMLTAGS_NUMBERING_POST;
	return preNumberingHtml;
}

string WhatToDo::createFloatingTaskHtml(Task taskToProcess) {
	string fullTaskHtml;
	string taskNameTagsHtml = getTaskNameTagsHtml(taskToProcess);
	fullTaskHtml += getHtmlPreTaskTags(taskToProcess);
	fullTaskHtml += getLastActionTextIndexHtml(taskToProcess);
	
	// Add the done tag in front of done tasks to indicate that they
	// are done.

	if (taskToProcess.getTaskIsDone()) {
		fullTaskHtml += 
			HTMLTAGS_TASK_DONE_PRE + HTMLTAGS_TASK_DONE_POST + 
			taskNameTagsHtml;
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
	
	// Add the done tag in front of done tasks to indicate that they
	// are done.

	if (taskToProcess.getTaskIsDone()) {
		fullTaskHtml += 
			HTMLTAGS_TASK_DONE_PRE + HTMLTAGS_TASK_DONE_POST;
	}

	taskNameTagsHtml = getTaskNameTagsHtml(taskToProcess);

	// Different kinds of tasks will be displayed differently in the 
	// GUI with different tags.

	if (taskToProcess.getTaskType() == Task::DEADLINE_ALLDAY) {
		partialTaskHtml = 
			HTMLTAGS_TASK_NAMETAGS_PRE_DEADLINE_ALLDAY + 
			HTMLTAGS_TASK_NAMETAGS_POST + taskNameTagsHtml;
	}
	else if (taskToProcess.getTaskType() == Task::DEADLINE_TIME) {
		taskFirstDisplayTime = taskToProcess.getTaskDeadline();
		partialTaskHtml = 
			HTMLTAGS_TASK_NAMETAGS_POST_DEADLINE_TIMED + 
			getDisplayTime(taskFirstDisplayTime) + 
			HTMLTAGS_TASK_NAMETAGS_POST + taskNameTagsHtml;
	}
	else if (taskToProcess.getTaskType() == Task::FIXED_ALLDAY) {
		partialTaskHtml = HTMLTAGS_TASK_NAMETAGS_POST_FIXED_ALLDAY + 
			HTMLTAGS_TASK_NAMETAGS_POST + taskNameTagsHtml;
	}
	else if (taskToProcess.getTaskType() == Task::FIXED_START) {
		taskFirstDisplayTime = taskToProcess.getTaskStartTime();
		partialTaskHtml = HTMLTAGS_TASK_NAMETAGS_POST_FIXED_START + 
			getDisplayTime(taskFirstDisplayTime) + 
			HTMLTAGS_TASK_NAMETAGS_POST + taskNameTagsHtml;
	}
	else if (taskToProcess.isTaskHasStartAndEnd()) {
		taskFirstDisplayTime = taskToProcess.getTaskStartTime();
		taskSecondDisplayTime = taskToProcess.getTaskEndTime();
		if (taskToProcess.getTaskType() == Task::FIXED_TIME_WITHIN_DAY) {
			partialTaskHtml = 
				HTMLTAGS_TASK_NAMETAGS_POST_FIXED_TIMED + 
				getDisplayTime(taskFirstDisplayTime) + 
				HTMLTAGS_TASK_NAMETAGS_MID_FIXED_START + 
				getDisplayTime(taskSecondDisplayTime) + 
				HTMLTAGS_TASK_NAMETAGS_POST + taskNameTagsHtml;
		}
		else if (taskToProcess.getTaskType() == Task::FIXED_TIME_ACROSS_DAY) {
			partialTaskHtml = 
				HTMLTAGS_TASK_NAMETAGS_POST_FIXED_TIMED + 
				getDisplayTime(taskFirstDisplayTime) + 
				HTMLTAGS_TASK_NAMETAGS_MID_FIXED_START + 
				getDisplayDay(taskSecondDisplayTime) + 
				HTMLTAGS_TASK_NAMETAGS_POST + taskNameTagsHtml;
		}
		else if (taskToProcess.getTaskType() == Task::FIXED_DAY_TO_DAY) {
			partialTaskHtml = 
				HTMLTAGS_TASK_NAMETAGS_POST_FIXED_TIMED + 
				STRING_ALL_DAY + HTMLTAGS_TASK_NAMETAGS_MID_FIXED_START + 
				getDisplayDayWithoutTime(taskSecondDisplayTime) + 
				HTMLTAGS_TASK_NAMETAGS_POST + taskNameTagsHtml;
		}
		else if (taskToProcess.getTaskType() == Task::FIXED_TIME_TO_DAY) {
			partialTaskHtml = 
				HTMLTAGS_TASK_NAMETAGS_POST_FIXED_TIMED + 
				getDisplayTime(taskFirstDisplayTime) + 
				HTMLTAGS_TASK_NAMETAGS_MID_FIXED_START + 
				getDisplayDayWithoutTime(taskSecondDisplayTime) + 
				HTMLTAGS_TASK_NAMETAGS_POST + taskNameTagsHtml;
		}
		else if (taskToProcess.getTaskType() == Task::FIXED_DAY_TO_TIME) {
			partialTaskHtml = 
				HTMLTAGS_TASK_NAMETAGS_POST_FIXED_TIMED + 
				STRING_ALL_DAY + HTMLTAGS_TASK_NAMETAGS_MID_FIXED_START + 
				getDisplayDay(taskSecondDisplayTime) + 
				HTMLTAGS_TASK_NAMETAGS_POST + taskNameTagsHtml;
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
		taskNameTagsHtml += 
			myTask.getTaskTags()[i] + STRING_SPACE_CHAR;
	}

	taskNameTagsHtml += HTMLTAGS_TASK_TAGS_POST;

	return taskNameTagsHtml;
}

string WhatToDo::getLastActionTextIndexHtml(Task taskToProcess) {
	string lastActionTextIndexHtml = STRING_EMPTY;
	int lastActionType = _currState.getLastActionType();
	int lastActionTaskIndex = _currState.getLastActionTaskIndex();

	// Add a special text marker to the task if it was changed or
	// deleted in the previous action.

	if ((lastActionType == State::CHANGED) 
			|| (lastActionType == State::DELETED)) {
		if (lastActionTaskIndex == taskToProcess.getTaskIndex()) {
			lastActionTextIndexHtml += 
				HTMLTAGS_TASK_INDEX_SPECIAL_MARKER;
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
	else if (myTask.isTaskHasStartAndEnd()) {
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
		minutes = STRING_DOT_CHAR + STRING_ZERO_CHAR + 
			to_string(myTime.time_of_day().minutes());
	}
	else {
		minutes = STRING_DOT_CHAR + 
			to_string(myTime.time_of_day().minutes());
	}

	if (myTime.time_of_day().hours() == 0) {
		pmOrAm = STRING_AM;
		hours = to_string(12);
	}
	else if (myTime.time_of_day().hours() < 12) {
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
	displayDay += STRING_SPACE_CHAR + 
		changeMonthToMonthOfYear(myTime.date().month());
	displayDay += STRING_SPACE_CHAR + getDisplayTime(myTime);
	return displayDay;
}

string WhatToDo::getDisplayDayWithoutTime(ptime myTime) {
	string displayDayWithoutTime;
	displayDayWithoutTime += to_string(myTime.date().day());
	displayDayWithoutTime += STRING_SPACE_CHAR + 
		changeMonthToMonthOfYear(myTime.date().month());
	return displayDayWithoutTime;
}

string WhatToDo::removeUnwantedChars(string stringToProcess) {
	boost::replace_all(stringToProcess, 
		STRING_NEWLN_CHAR, STRING_EMPTY);
	boost::replace_all(stringToProcess, 
		STRING_RETURN_CHAR, STRING_EMPTY);
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
	taskEditText += STRING_SPACE_CHAR + 
		getTaskDateAsEditText(taskToConvert);
	for (i=0; unsigned(i)<taskTags.size();  i++) {
		if (i==0) {
			taskEditText += taskTags[i];
		}
		else {
			taskEditText += STRING_SPACE_CHAR + taskTags[i];
		}
	}
	return taskEditText;
}

string WhatToDo::getTaskDateAsEditText(Task taskToConvert) {
	string taskDateEditText;
	if (taskToConvert.getTaskType() == Task::FLOATING) {
		taskDateEditText = STRING_EMPTY;
	}
	else if (taskToConvert.getTaskType() == Task::DEADLINE_ALLDAY) {
		taskDateEditText = COMMAND_PARAM_ADD_DATE_DEADLINE + 
			convertDateToEditText(taskToConvert.getTaskDeadline());
	}
	else if (taskToConvert.getTaskType() == Task::DEADLINE_TIME) {
		taskDateEditText = COMMAND_PARAM_ADD_DATE_DEADLINE + 
			convertDateTimeToEditText(taskToConvert.getTaskDeadline());
	}
	else if (taskToConvert.getTaskType() == Task::FIXED_ALLDAY) {
		taskDateEditText = COMMAND_PARAM_ADD_DATE_TIMED_ALLDAY + 
			convertDateToEditText(taskToConvert.getTaskStartTime());
	}
	else if (taskToConvert.getTaskType() == Task::FIXED_START) {
		taskDateEditText = COMMAND_PARAM_ADD_DATE_TIMED_START + 
			convertDateTimeToEditText(taskToConvert.getTaskStartTime());
	}
	else if (taskToConvert.isTaskHasStartAndEnd()) {
		taskDateEditText += COMMAND_PARAM_ADD_DATE_TIMED_START + 
			convertDateTimeToEditText(taskToConvert.getTaskStartTime());
		taskDateEditText += COMMAND_PARAM_ADD_DATE_TIMED_END + 
			convertDateTimeToEditText(taskToConvert.getTaskEndTime());
	}

	return taskDateEditText;
}

string WhatToDo::convertDateTimeToEditText(ptime timeToConvert) {
	string dateTimeEditText;
	dateTimeEditText = to_string(timeToConvert.date().day()) + 
		STRING_SPACE_CHAR + 
		changeMonthToMonthOfYear(timeToConvert.date().month()) + 
		STRING_SPACE_CHAR + to_string(timeToConvert.date().year()) + 
		STRING_SPACE_CHAR + getDisplayTime(timeToConvert) + 
		STRING_SPACE_CHAR;
	return dateTimeEditText;
}

string WhatToDo::convertDateToEditText(ptime timeToConvert) {
	string dateEditText;
	dateEditText = to_string(timeToConvert.date().day()) + 
		STRING_SPACE_CHAR + 
		changeMonthToMonthOfYear(timeToConvert.date().month()) + 
		STRING_SPACE_CHAR + to_string(timeToConvert.date().year()) + 
		STRING_SPACE_CHAR;
	return dateEditText;
}

bool WhatToDo::checkIsContainStrangeChars(string stringToProcess) {
	bool isContainStrangeChars = false;
	int i;
	for (i=0; unsigned(i)<stringToProcess.size(); i++) {
		if ((stringToProcess[i]<GUI_MIN_CHAR) 
				|| (stringToProcess[i]>GUI_MAX_CHAR)) {
			isContainStrangeChars = true;
			break;
		}
	}
	return isContainStrangeChars;
}

bool WhatToDo::checkIsCurrentStateEmpty() {
	bool isCurrentStateEmpty = false;
	vector<Task> listOfTasksInState = _tempFutureState.getAllTasks();
	isCurrentStateEmpty = listOfTasksInState.empty();
	return isCurrentStateEmpty;
}
