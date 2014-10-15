#include "CommandClear.h"


CommandClear::CommandClear(void)
{
}

void CommandClear::execute() {
	checkIsParsedCorrectly();
	
	if (_isParsedCorrectly) {
		retrieveExistingCurrentState();
		setNewViewState();
	}

	addUserMessageToCurrentState();
	return;
}
