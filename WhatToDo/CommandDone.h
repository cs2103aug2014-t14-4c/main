#pragma once
#include "Command.h"
using namespace std;

class CommandDone: public Command {
	public:
		CommandDone(void);
		void execute();

	private:
		void performDoneOperation();
};

