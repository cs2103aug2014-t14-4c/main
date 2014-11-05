//****************************************************************************
//@Poh Zhi Chao A0110648L
//
// This is the concrete CommandSearch class, which is reponsible for executing 
// an "search" command specified by the user.
//
// It works by (i) checking for the validity of the command; (ii) retrieving 
// the current state from LogicData; (iii) performing the search operation;
// and (iv) rewriting only the view state in LogicData.
//
// If the command is invalid due to a false parsed status indicating
// it has been parsed incorrectly, an error message will be added to the
// current state to be shown to the user eventually.
//
//****************************************************************************

#pragma once

#include <sstream>
#include "Command.h"
#include "CommandSearchPowerSearch.h"

using namespace std;

const string TAG_DELIMITER = "#";
const string MSG_LOGGING_EXECUTE_COMMAND_SEARCH = 
	"\nCommand Search Initiated:\n";

class CommandSearch: public Command {
	public:
		CommandSearch(void);
		void execute();

	private:
		
		// Attributes For Execution
		
		string _stringToSearchFor;
		vector<string> _tagsToSearchFor;
		vector<int> _listOfTaskIndexesToDelete;
		CommandSearchPowerSearch* _myPowerSearch;
		
		// Functions For Execution
		
		void performSearchOperation();

		// Divides the search string into the multiple tags that
		// may be present so as to search for tags in the program
		// database separately from the task names

		void getTagsToSearchFor();

		// Obtains the task name search string from the entire
		// search string provided in the command

		void getNameToSearchFor();

		// Determine which tasks are to be deleted subsequently
		// as they do not satisfy the search criteria

		void getListOfTaskIndexesNotMatchingSearch();

		// Deletes the tasks which have been marked for deleting
		// because they do not satisfy the search criteria

		void deleteListOfTaskIndexesNotMatchingSearch();

		bool checkIsFitsSearchCriteria(Task taskToCheck);
		bool checkIsFitsTagSearchCriteria(Task taskToCheck);
		bool checkIsFitsNameSearchCriteria(Task taskToCheck);

		string convertToLower(string toConvert);
};

