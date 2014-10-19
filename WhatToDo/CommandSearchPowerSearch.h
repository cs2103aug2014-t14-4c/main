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
		string _mainString;
		string _remainingString;
		string _newRemainingString;
		string _searchString;
		vector<string> _tokenizedSearchString;

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

		enum FoundType{
			FOUND = 1, NOTFOUND = 0
		};
};

