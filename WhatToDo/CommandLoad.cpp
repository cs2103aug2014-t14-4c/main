//****************************************************************************
//@author A0110648L

#include "CommandLoad.h"

CommandLoad::CommandLoad(void) {
}

void CommandLoad::execute() {
	sprintf_s(buffer, MSG_LOGGING_EXECUTE_COMMAND_LOAD.c_str());
	log(buffer);
	
	try {
		checkIsParsedCorrectly();
		loadLogicDataSettings();
		retrieveExistingCurrentState();
		resetLastActionType();
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
	sprintf_s(buffer, MSG_LOGGING_LOAD_LOGIC_DATA_SETTINGS.c_str());
	log(buffer);
	return;
}

void CommandLoad::resetLastActionType() {
	_currentState->setLastActionType(State::NONE);
	return;
}