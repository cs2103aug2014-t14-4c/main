#include "CommandFilter.h"

// These are the static variables that cannot be initialized in header file

string CommandFilter::LOGGING_MSG_EXECUTE_COMMAND_FILTER = "\nCommand Filter Initiated:\n";


CommandFilter::CommandFilter(void) {
}


void CommandFilter::execute() {
	sprintf_s(buffer, LOGGING_MSG_EXECUTE_COMMAND_FILTER.c_str());
	log(buffer);
	
	try {
		checkIsParsedCorrectly();
		retrieveExistingViewState();
		checkIsCommandValid();
		performFilterOperation();
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

void CommandFilter::performFilterOperation() {

	// Work on this!

	return;
}

bool CommandFilter::checkIsCommandValid() {

	// Implement this if you want to check if the filter command is valid
	// if you are not going to use this then please delete it at the end

	return true;
}