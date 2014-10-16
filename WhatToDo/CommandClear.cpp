#include "CommandClear.h"


CommandClear::CommandClear(void)
{
}

void CommandClear::execute() {
	log("\nCommand Clear Initiated:\n");
	
	try {
		checkIsParsedCorrectly();
		retrieveExistingCurrentState();
		setNewViewState();
	}
	catch (string errorMsg) {
		retrieveExistingViewState();
		addUserMessageToCurrentState();
		setNewViewState();
	}

	return;
}
