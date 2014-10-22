#include "CommandSuggest.h"

// These are the static variables that cannot be initialized in header file

string CommandSuggest::LOGGING_MSG_EXECUTE_COMMAND_SUGGEST = "\nCommand Suggest Initiated:\n";


CommandSuggest::CommandSuggest(void) {
}

vector<string> CommandSuggest::getSuggestions() {
	sprintf_s(buffer, LOGGING_MSG_EXECUTE_COMMAND_SUGGEST.c_str());
	log(buffer);
	
	vector<string> newSuggestions;

	// Work on this part!!
	// The suggest string is in the _suggestString variable

	return newSuggestions;
}

void CommandSuggest::setSuggestString(string suggestStringToSet) {
	_suggestString = suggestStringToSet;
	return;
}
