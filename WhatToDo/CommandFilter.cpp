#include "CommandFilter.h"

// These are the static variables that cannot be initialized in header file

string CommandFilter::LOGGING_MSG_EXECUTE_COMMAND_FILTER = "\nCommand Filter Initiated:\n";


CommandFilter::CommandFilter(void) {
	done = Done::NOT_SET;
	type = Type::NOT_SET;
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

void CommandFilter::setDone(int doneFilter) {
	done = doneFilter;
}

void CommandFilter::setType(int typeFilter) {
	type = typeFilter;
}

void CommandFilter::setStartDate(date startDateFilter) {
	start = startDateFilter;
}

void CommandFilter::setEndDate(date endDateFilter) {
	end = endDateFilter;
}

void CommandFilter::performFilterOperation() {
	LogicData logicData;

	if(done != Done::NOT_SET) {
		logicData.setFilterDone(done);
	}

	if(type != Done::NOT_SET) {
		logicData.setFilterType(type);
	}

	if(!start.is_not_a_date()) {
		logicData.setFilterStartDate(start);
	}

	if(!end.is_not_a_date()) {
		logicData.setFilterEndDate(end);
	}

	return;
}