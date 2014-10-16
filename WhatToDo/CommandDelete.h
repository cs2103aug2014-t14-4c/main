#pragma once
#include "Command.h"
using namespace std;

class CommandDelete: public Command {
	public:
		CommandDelete(void);
		void execute();

	private:
		void performDeleteOperation();
};

