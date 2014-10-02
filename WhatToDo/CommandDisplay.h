#pragma once
#include "Command.h"
#include "LogicData.h"
using namespace std;

class CommandDisplay: public Command {
	public:
		CommandDisplay(void);
		void execute();
		State getViewState();

	private:

};

