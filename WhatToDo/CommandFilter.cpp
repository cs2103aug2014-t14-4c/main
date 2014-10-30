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
	LogicData logicData;
	
	if(_doneFilter != Done::DONE_NOT_SET) {
		logicData.setDoneFilter(_doneFilter);
	}
	if(_typeFilter != Type::TYPE_NOT_SET) {
		logicData.setTypeFilter(_typeFilter);
	}
	if(!_startDateFilter.is_not_a_date() && !_endDateFilter.is_not_a_date()) {
		logicData.setDateFilter(_startDateFilter, _endDateFilter);
	}

	return;
}