#include "CommandClear.h"


CommandClear::CommandClear(void)
{
}

void CommandClear::execute() {
	log("\nCommand Clear Initiated:\n");
	checkIsParsedCorrectly();
	
	if (_isParsedCorrectly) {
		retrieveExistingCurrentState();
		setNewViewState();
	}

	addUserMessageToCurrentState();
	return;
}
