#pragma once
#include "Command.h"
#include "LogicData.h"
using namespace std;

class CommandDelete: public Command {
	public:
		CommandDelete(void);
		void execute();

	private:
		void performDeleteOperation();
};

