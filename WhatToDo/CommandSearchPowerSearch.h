#pragma once

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class CommandSearchPowerSearch {
	public:
		CommandSearchPowerSearch(void);
		~CommandSearchPowerSearch(void);

		bool checkIsFound(string mainString, string searchString);

	private:

		// Power Search Attributes For Execution

		string _mainString;
		string _remainingString;
		string _newRemainingString;
		string _searchString;
		vector<string> _tokenizedSearchString;

		enum FoundType{
			FOUND = 1, NOTFOUND = 0
		};
		
		// Power Search Functions For Execution

		bool checkIsFoundByNormalSearch();
		bool checkIsFoundbyPowerSearch();
		bool powerSearchRemainingString(string remainingString);
		bool checkIsMatchesFuzzySearch(string mainToken, string searchToken);
		bool checkIsFoundByFuzzySearch(string searchToken);
		bool checkIsFoundByShorthandSearch(string searchToken);
		bool checkIsFoundByAcronymSearch(string searchToken);
		
		vector<string> tokenizeString(string stringToTokenize);
		string untokenizeString(vector<string> stringTokens);
		string getFirstCharacters(vector<string>tokenizedMainString);

		bool isInRange(int lowerBound, int upperBound, int toCheckRange);
		int toZeroIfNegative(int toConvert);
		bool detIfmatchRecordAcceptable(vector<int> matchRecord);
		
		// All Static Constants And Variables

		static int INITIAL_VALUE_PARTIAL_SHORT_HAND_INDEX;
		static int INITIAL_VALUE_FUZZYSEARCH_IDEAL_FOUND_INDEX;
		static int INITIAL_VALUE_FUZZYSEARCH_DEFAULT_ERROR;
		static double FUZZY_SEARCH_MATCH_REORD_TOLERANCE;
};

