#include "CommandLoad.h"


CommandLoad::CommandLoad(void)
{
}

void CommandLoad::execute() {
	log("\nCommand Load initiated:\n");

	try {
		checkIsParsedCorrectly();
		loadLogicDataSettings();
	}
	catch (string errorMsg) {
		retrieveExistingViewState();
		addUserMessageToCurrentState();
		setNewViewState();
	}

	return;
}

void CommandLoad::loadLogicDataSettings() {
	LogicData::loadInitialSettings();
	log("Function called: loadLogicDataSettings()\n");
}