#pragma once
#include "Command.h"
#include "LogicData.h"
using namespace std;

class CommandSearch: public Command {
	public:
		CommandSearch(void);
		void execute();

	private:
		void performSearchOperation();
		void getTagsToSearchFor();
		void getNameToSearchFor();
		void getListOfTaskIndexesNotMatchingSearch();
		void deleteListOfTaskIndexesNotMatchingSearch();
		bool checkIsFitsSearchCriteria(Task taskToCheck);
		bool checkIsFitsTagSearchCriteria(Task taskToCheck);
		bool checkIsFitsNameSearchCriteria(Task taskToCheck);
		vector<string> _tagsToSearchFor;
		string _stringToSearchFor;
		vector<int> _listOfTaskIndexesToDelete;
		string convertToLower(string toConvert);

};

