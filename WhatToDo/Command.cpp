#include "Command.h"

// These are the static variables that cannot be initialized in header file

char Command::buffer[255];

int Command::INITIAL_VALUE_COMMAND_TASK_INDEX = 0;
bool Command::INITIAL_VALUE_IS_PARSED_CORRECTLY = true;
bool Command::INITIAL_VALUE_IS_COMMAND_VALID = true;
bool Command::INITIAL_VALUE_LOGGING_MODE_ON = false;
string Command::INITIAL_VALUE_SEARCH_KEYWORD = "";
string Command::INITIAL_VALUE_USER_MESSAGE = "";
string Command::INITIAL_VALUE_ACTION_MESSAGE = "";
string Command::INITIAL_VALUE_LOG_FILE_NAME = "CommandLog.txt";
Task* Command::INITIAL_VALUE_CURRENT_TASK = NULL;
State* Command::INITIAL_VALUE_CURRENT_STATE = NULL;

string Command::LOGGING_MSG_CHECK_IS_PARSED_CORRECTLY = "Function called: checkIsParsedCorrectly(): _userMessage set as: %s\n";
string Command::LOGGING_MSG_RETRIEVE_EXISTING_VIEW_STATE = "Function called: retrieveExistingViewState()\n";
string Command::LOGGING_MSG_RETRIEVE_EXISTING_CURRENT_STATE = "Function called: retrieveExistingCurrentState()\n";
string Command::LOGGING_MSG_SET_NEW_CURRENT_STATE = "Function called: setNewCurrentState()\n";
string Command::LOGGING_MSG_SET_NEW_VIEW_STATE = "Function called: setNewViewState()\n";
string Command::LOGGING_MSG_ADD_THIS_COMMAND_TO_HISTORY = "Function called: addThisCommandToHistory()\n";
string Command::LOGGING_MSG_ADD_USER_MESSAGE_TO_CURRENT_STATE = "Function called: addUserMessageToCurrentState(): _userMessage written: %s\n";
string Command::LOGGING_MSG_RESET_LOGIC_DATA_SETTINGS = "Function called: resetLogicDataSettings()\n";

string Command::ERROR_MSG_NOT_PARSED_CORRECTLY = "Cannot perform command";


Command::Command(void) {
	_commandTaskIndex = INITIAL_VALUE_COMMAND_TASK_INDEX;
	_isCommandValid = INITIAL_VALUE_IS_COMMAND_VALID;
	_isParsedCorrectly = INITIAL_VALUE_IS_PARSED_CORRECTLY;
	_searchKeyword = INITIAL_VALUE_SEARCH_KEYWORD;
	_userMessage = INITIAL_VALUE_USER_MESSAGE;
	_actionMessage = INITIAL_VALUE_ACTION_MESSAGE;
	_currentTask = INITIAL_VALUE_CURRENT_TASK;
	_currentState = INITIAL_VALUE_CURRENT_STATE;
	_logFileName = INITIAL_VALUE_LOG_FILE_NAME;
	_loggingModeOn = INITIAL_VALUE_LOGGING_MODE_ON;
	_doneFilter = Done::DONE_NOT_SET;
	_typeFilter = Type::TYPE_NOT_SET;
}

void Command::execute() {
	return;
}

int Command::getTaskIndex() {
	return _commandTaskIndex;
}

bool Command::getParsedStatus() {
	return _isParsedCorrectly;
}

string Command::getSearchKeyword() {
	return _searchKeyword;
}

Task Command::getCurrentTask() {
	return *_currentTask;
}

string Command::getUserMessage() {
	return _userMessage;
}

int Command::getDoneFilter(void) {
	return _doneFilter;
}

int Command::getTypeFilter(void) {
	return _typeFilter;
}

date Command::getStartDateFilter(void) {
	return _startDateFilter;
}

date Command::getEndDateFilter(void) {
	return _endDateFilter;
}

void Command::setTaskIndex(int commandTaskIndexToSet) {
	_commandTaskIndex = commandTaskIndexToSet;
	return;
}

void Command::setParsedStatus(bool parsedStatus) {
	_isParsedCorrectly = parsedStatus;
	return;
}

void Command::setSearchKeyword(string searchKeywordToSet) {
	_searchKeyword = searchKeywordToSet;
	return;
}

void Command::setCurrentTask(Task currentTaskToSet) {
	_currentTask = new Task;
	*_currentTask = currentTaskToSet;
	return;
}

void Command::setUserMessage(string userMessageToSet) {
	_userMessage = userMessageToSet;
	return;
}

void Command::setDoneFilter(int doneFilter) {
	_doneFilter = doneFilter;
}

void Command::setTypeFilter(int typeFilter) {
	_typeFilter = typeFilter;
}

void Command::setStartDateFilter(date startDateFilter) {
	_startDateFilter = startDateFilter;
}

void Command::setEndDateFilter(date endDateFilter) {
	_endDateFilter = endDateFilter;
}

bool Command::checkIsParsedCorrectly() {
	if (!_isParsedCorrectly) {
		throw _userMessage;
		_isParsedCorrectly = false;
	}
	sprintf_s(buffer, LOGGING_MSG_CHECK_IS_PARSED_CORRECTLY.c_str(), _userMessage.c_str());
	log(buffer);
	return _isParsedCorrectly;
}

void Command::retrieveExistingViewState() {
	_currentState = new State;
	*_currentState = LogicData::getViewState();
	sprintf_s(buffer, LOGGING_MSG_RETRIEVE_EXISTING_VIEW_STATE.c_str());
	log(buffer);
	return;
}

void Command::retrieveExistingCurrentState() {
	_currentState = new State;
	*_currentState = LogicData::getCurrentState();
	sprintf_s(buffer, LOGGING_MSG_RETRIEVE_EXISTING_CURRENT_STATE.c_str());
	log(buffer);
	return;
}

void Command::setNewCurrentState() {
	LogicData::setCurrentState(*_currentState);
	sprintf_s(buffer, LOGGING_MSG_SET_NEW_CURRENT_STATE.c_str());
	log(buffer);
	return;
}

void Command::setNewViewState() {
	LogicData::setViewState(*_currentState);
	sprintf_s(buffer, LOGGING_MSG_SET_NEW_VIEW_STATE.c_str());
	log(buffer);
	return;
}

void Command::addThisCommandToHistory(Command* commandToAdd) {
	LogicData::addCommandToHistory(commandToAdd);
	sprintf_s(buffer, LOGGING_MSG_ADD_THIS_COMMAND_TO_HISTORY.c_str());
	log(buffer);
	return;
}

void Command::addUserMessageToCurrentState() {
	_currentState->setUserMessage(_userMessage);
	sprintf_s(buffer, LOGGING_MSG_ADD_USER_MESSAGE_TO_CURRENT_STATE.c_str(), _userMessage.c_str());
	log(buffer);
	return;
}

void Command::addActionMessageToCurrentState() {
	_currentState->setActionMessage(_actionMessage);
	return;
}

void Command::resetLogicDataSettings() {
	LogicData::resetToInitialSettings();
	sprintf_s(buffer, LOGGING_MSG_RESET_LOGIC_DATA_SETTINGS.c_str());
	log(buffer);
	return;
}

void Command::log(string stringToLog) {
	if (!_loggingModeOn) {
		return;
	}
	ofstream writeToLog;
	writeToLog.open(_logFileName, ios::app);
	writeToLog << stringToLog;
	writeToLog.close();
	return;
}