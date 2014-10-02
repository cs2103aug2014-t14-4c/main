#pragma once
#include "Command.h"
#include "LogicData.h"
using namespace std;

class CommandClear: public Command {
	public:
		CommandClear(void);
		void execute();

	private:
};

