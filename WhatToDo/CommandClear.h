#pragma once
#include "Command.h"
using namespace std;

class CommandClear: public Command {
	public:
		CommandClear(void);
		void execute();

	private:
};

