#include "CommandLoad.h"


CommandLoad::CommandLoad(void)
{
}

void CommandLoad::execute() {
	LogicData myLogicData;
	myLogicData.loadInitialSettings();
	return;
}
