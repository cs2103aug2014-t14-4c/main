#include "CommandLoad.h"


CommandLoad::CommandLoad(void)
{
}

void CommandLoad::execute() {
	loadLogicDataSettings();
	return;
}

void CommandLoad::loadLogicDataSettings() {
	LogicData::loadInitialSettings();
}