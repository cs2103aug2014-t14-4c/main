#pragma once
#include "Command.h"
using namespace std;

class CommandLoad: public Command {
	public:
		CommandLoad(void);
		void execute();

	private:
		void loadLogicDataSettings();
};

