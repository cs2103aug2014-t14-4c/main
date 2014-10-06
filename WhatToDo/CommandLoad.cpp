#include "CommandLoad.h"


CommandLoad::CommandLoad(void)
{
}

void CommandLoad::execute() {
	LogicData::loadInitialSettings();
	return;
}
