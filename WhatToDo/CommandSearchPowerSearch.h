//****************************************************************************
//@author A0110648L
//
// This is powersearch class, which is reponsible for the more detailed logic 
// processing steps which are required for advanced search operations in the
// CommandSearch concrete command class.
//
// It allows for (i) fuzzy searches - not all text need to match in order for 
// a search term to match a task; (ii) shorthand searches - search keywords 
// comprised of the first characters of a task name will match; and (iii) acronym
// searches - search keywords which are fragments of a task name will match.
//
// Sample usage:
//     checkIsFound("i am coding cs2103", "2103");
//
//****************************************************************************

#pragma once

#include <string>
#include <vector>
#include <sstream>

using namespace std;

const int INITIAL_VALUE_PARTIAL_SHORT_HAND_INDEX = 1;
const int INITIAL_VALUE_FUZZYSEARCH_IDEAL_FOUND_INDEX = 0;
const int INITIAL_VALUE_FUZZYSEARCH_DEFAULT_ERROR = 1;
const double FUZZY_SEARCH_MATCH_REORD_TOLERANCE = 0.75;

class CommandSearchPowerSearch {
	public:
		CommandSearchPowerSearch(void);
		~CommandSearchPowerSearch(void);

		bool checkIsFound(string mainString, string searchString);

	private:

		// Attributes For Execution

		string _mainString;
		string _remainingString;
		string _newRemainingString;
		string _searchString;
		vector<string> _tokenizedSearchString;

		enum FoundType{
			FOUND = 1, NOTFOUND = 0
		};
		
		// Functions For Execution

		bool checkIsFoundByNormalSearch();
		bool checkIsFoundbyPowerSearch();

		// Performs a shorthand and acronym search on the mainstring
		// according to the substring to determine if the mainstring
		// matches the search criteria.

		bool powerSearchRemainingString(string remainingString);
		bool checkIsMatchesFuzzySearch(string mainToken, 
			string searchToken);
		bool checkIsFoundByFuzzySearch(string searchToken);
		bool checkIsFoundByShorthandSearch(string searchToken);
		bool checkIsFoundByAcronymSearch(string searchToken);
		
		// Breaks a given string delimited by spaces into individual
		// words stored in a vector of strings and returns the vector

		vector<string> tokenizeString(string stringToTokenize);

		// Recombines a given vector of strings (each containing a word)
		// back into a single string with spaces separating the words 
		// and returns the string

		string untokenizeString(vector<string> stringTokens);

		// Returns a string comprised of the first characters of each
		// word in a given tokenized string (in a vector of strings)

		string getFirstCharacters(vector<string>tokenizedMainString);

		bool isInRange(int lowerBound, int upperBound, 
			int toCheckRange);
		int toZeroIfNegative(int toConvert);

		// Determines if a match record containing information on whether
		// each letter in the mainstring has been successfully matched 
		// with the substring is acceptable according to predefined
		// tolerance limits

		bool detIfmatchRecordAcceptable(vector<int> matchRecord);
};

