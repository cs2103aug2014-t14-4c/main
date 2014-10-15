#include "CommandLoad.h"


CommandLoad::CommandLoad(void)
{
}

void CommandLoad::execute() {
	log("\nCommand Load initiated:\n");
	loadLogicDataSettings();
	return;
}

void CommandLoad::loadLogicDataSettings() {
	LogicData::loadInitialSettings();
	log("Function called: loadLogicDataSettings()\n");
}