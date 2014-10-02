#pragma once
#include "CommandAdd.h"
using namespace std;

class CommandEdit: public CommandAdd {
	public:
		CommandEdit(void);
		void execute();

	private:
		void deleteExistingTask();
};

