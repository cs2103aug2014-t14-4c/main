#pragma once
#include "CommandUndo.h"
using namespace std;

class CommandRedo: public CommandUndo {
	public:
		CommandRedo(void);
		void execute();

	private:
		bool checkIsCommandValid();

};

