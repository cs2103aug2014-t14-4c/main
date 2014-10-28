#pragma once

#include "Command.h"
//1) Identify keywords like 'hour', 'day' , 'month', 'year', 'tomorrow'
//2) Break string into 2 strings.
//3) First suggestion original string
//4) Second suggestion 


using namespace std;

class CommandSuggest: public Command {
	public:
		CommandSuggest(void);
		vector<string> getSuggestions();
		void setSuggestString(string suggestStringToSet);

	protected:
		
		// Command Attributes For Getting Suggestions

		string _suggestString;

		// Implement any functions you need here



		// All Static Constants And Variables

		static string LOGGING_MSG_EXECUTE_COMMAND_SUGGEST;

};

