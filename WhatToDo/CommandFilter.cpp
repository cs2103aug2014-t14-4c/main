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
		performFilterOperation();
	}
	catch (string errorMsg) {
		_userMessage = errorMsg;
		addUserMessageToCurrentState();
	}

	return;
}

void CommandFilter::performFilterOperation() {
	
	if(_doneFilter != Done::DONE_NOT_SET) {
		LogicData::setDoneFilter(_doneFilter);
	}
	if(_typeFilter != Type::TYPE_NOT_SET) {
		LogicData::setTypeFilter(_typeFilter);
	}
	if(!_startDateFilter.is_not_a_date() && !_endDateFilter.is_not_a_date()) {
		LogicData::setDateFilter(_startDateFilter, _endDateFilter);
	}

	retrieveExistingCurrentState();
	_currentState->setLastActionType(State::NONE);
	setNewViewState();
	return;
}