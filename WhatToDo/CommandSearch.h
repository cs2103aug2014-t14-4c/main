#pragma once

#include <sstream>
#include "Command.h"
#include "CommandSearchPowerSearch.h"

using namespace std;

class CommandSearch: public Command {
	public:
		CommandSearch(void);
		void execute();

	private:
		
		// CommandSearch Attributes For Execution
		
		string _stringToSearchFor;
		vector<string> _tagsToSearchFor;
		vector<int> _listOfTaskIndexesToDelete;
		CommandSearchPowerSearch* _myPowerSearch;
		
		// CommandSearch Functions For Execution
		
		void performSearchOperation();
		void getTagsToSearchFor();
		void getNameToSearchFor();
		void getListOfTaskIndexesNotMatchingSearch();
		void deleteListOfTaskIndexesNotMatchingSearch();

		bool checkIsFitsSearchCriteria(Task taskToCheck);
		bool checkIsFitsTagSearchCriteria(Task taskToCheck);
		bool checkIsFitsNameSearchCriteria(Task taskToCheck);

		string convertToLower(string toConvert);

		// All Static Constants And Variables

		static string TAG_DELIMITER;

		static string LOGGING_MSG_EXECUTE_COMMAND_SEARCH;
};

