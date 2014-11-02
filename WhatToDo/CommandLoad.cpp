#include "CommandLoad.h"

// These are the static variables that cannot be initialized in header file

string CommandLoad::LOGGING_MSG_EXECUTE_COMMAND_LOAD = "\nCommand Load Initiated:\n";
string CommandLoad::LOGGING_MSG_LOAD_LOGIC_DATA_SETTINGS = "Function called: loadLogicDataSettings()\n";


CommandLoad::CommandLoad(void)
{
}

void CommandLoad::execute() {
	sprintf_s(buffer, LOGGING_MSG_EXECUTE_COMMAND_LOAD.c_str());
	log(buffer);
	
	try {
		checkIsParsedCorrectly();
		loadLogicDataSettings();
		retrieveExistingCurrentState();
		_currentState->setLastActionType(State::NONE);
		setNewViewState();
	}
	catch (string errorMsg) {
		_userMessage = errorMsg;
		retrieveExistingViewState();
		addUserMessageToCurrentState();
		setNewViewState();
	}

	return;
}

void CommandLoad::loadLogicDataSettings() {
	LogicData::loadInitialSettings();
	sprintf_s(buffer, LOGGING_MSG_LOAD_LOGIC_DATA_SETTINGS.c_str());
	log(buffer);
	return;
}