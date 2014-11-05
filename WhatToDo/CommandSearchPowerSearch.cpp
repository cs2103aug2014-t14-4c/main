#include "CommandSearchPowerSearch.h"

CommandSearchPowerSearch::CommandSearchPowerSearch(void) {
}

CommandSearchPowerSearch::~CommandSearchPowerSearch(void) {
}

bool CommandSearchPowerSearch::checkIsFound(string mainString, 
		string searchString) {
	bool isFound = false;
	_mainString = mainString;
	_remainingString = mainString;
	_searchString = searchString;
	_tokenizedSearchString = tokenizeString(searchString);

	if (checkIsFoundByNormalSearch()) {
		isFound = true;
	}
	else if (checkIsFoundbyPowerSearch()) {
		isFound = true;
	}

	return isFound;
}

bool CommandSearchPowerSearch::checkIsFoundByNormalSearch() {
	bool isFound = false;
	isFound = (_mainString.find(_searchString) != string::npos);
	return isFound;
}

bool CommandSearchPowerSearch::checkIsFoundbyPowerSearch() {
	bool isFound = true;
	bool isTokenFound;
	int i;

	if (checkIsFoundByFuzzySearch(_searchString)) {
		return true;
	}

	for (i=0; unsigned(i)<_tokenizedSearchString.size(); i++) {
		isTokenFound = 
			powerSearchRemainingString(_tokenizedSearchString[i]);

		if (!isTokenFound) {
			isFound = false;
			break;
		}
	}

	return isFound;
}

bool CommandSearchPowerSearch::powerSearchRemainingString(
		string searchToken) {
	bool isFound = false;

	if (checkIsFoundByShorthandSearch(searchToken)) {
		isFound = true;
	}
	else if (checkIsFoundByAcronymSearch(searchToken)) {
		isFound = true;
	}

	if (isFound) {
		_remainingString = _newRemainingString;
	}

	return isFound;
}

bool CommandSearchPowerSearch::checkIsFoundByFuzzySearch(
		string searchToken) {
	string mainString = _mainString;
	bool isFound = false;
	int mainStringSize = mainString.size();
	int i=0;
	
	for (i=0; unsigned(i)<mainStringSize; i++) {
		if (checkIsMatchesFuzzySearch(mainString, searchToken)) {
			isFound = true;
			break;
		}
		mainString.erase(mainString.begin());
	}
	return isFound;
}

bool CommandSearchPowerSearch::checkIsFoundByShorthandSearch(
		string searchToken) {
	vector<string> tokenizedMainString = 
		tokenizeString(_remainingString);
	bool isFound;
	int indexShorthandLastFound = 0;
	int i;
	int j;

	for (i=0; unsigned(i)<tokenizedMainString.size(); i++) {
		string currentMainToken = tokenizedMainString[i];
		int indexPartialShorthandLastFound = 
			INITIAL_VALUE_PARTIAL_SHORT_HAND_INDEX;
		isFound = true;
		
		for (j=0; unsigned(j)<searchToken.size(); j++) {
			bool isPartialSearchTokenFound = false;

			if ((j==0) && (searchToken[0] == currentMainToken[0])) {
				currentMainToken = 
					currentMainToken.substr(
					indexPartialShorthandLastFound);
				isPartialSearchTokenFound = true;
			}
			else if ((j!=0) 
					&& (currentMainToken.find(
					searchToken[j]) != string::npos)){
				indexPartialShorthandLastFound = 
					currentMainToken.find(searchToken[j]);
				currentMainToken = 
					currentMainToken.substr(
					indexPartialShorthandLastFound+1);
				isPartialSearchTokenFound = true;
			}

			if (!isPartialSearchTokenFound) {
				isFound = false;
				break;
			}
		}
		
		if (isFound) {
			int k;
			indexShorthandLastFound = i;
			for (k=0; unsigned(k)<=indexShorthandLastFound; k++) {
				tokenizedMainString.erase(
					tokenizedMainString.begin());
			}
			_newRemainingString =
				untokenizeString(tokenizedMainString);
			return true;
		}
		
	}

	return false;
}

bool CommandSearchPowerSearch::checkIsFoundByAcronymSearch(
		string searchToken) {
	vector<string> tokenizedMainString = 
		tokenizeString(_remainingString);
	string stringOfMainStringFirstChars = 
		getFirstCharacters(tokenizedMainString);
	string remainingMainStringFirstChars = 
		stringOfMainStringFirstChars;
	bool isFound = true;
	int indexAcronymLastFound = 0;
	int charIndex = 0;
	int i;

	for (i=0; unsigned(i)<searchToken.size(); i++) {
		if (remainingMainStringFirstChars.find(
				searchToken[i]) == string::npos) {
			isFound = false;
			break;
		}
		charIndex = 
			remainingMainStringFirstChars.find(searchToken[i]);
		remainingMainStringFirstChars = 
			remainingMainStringFirstChars.substr(charIndex+1);
	}

	indexAcronymLastFound = 
		stringOfMainStringFirstChars.size() - 
		remainingMainStringFirstChars.size();
	for (i=0; unsigned(i)<indexAcronymLastFound; i++) {
		tokenizedMainString.erase(tokenizedMainString.begin());
	}
	_newRemainingString = untokenizeString(tokenizedMainString);

	return isFound;
}



vector<string> CommandSearchPowerSearch::tokenizeString(
		string stringToTokenize) {
	istringstream inputString(stringToTokenize);
	string tokenString;
	vector<string> tokenizedString;

	while (inputString >> tokenString) {
		tokenizedString.push_back(tokenString);
	}

	return tokenizedString;
}

string CommandSearchPowerSearch::untokenizeString(
		vector<string> stringTokens) {
	ostringstream outputString;
	int i;
	
	if (stringTokens.size() > 0) {
		outputString << stringTokens[0];
	}

	for (i=1; unsigned(i)<stringTokens.size(); i++) {
		outputString << " " << stringTokens[i];
	}

	return outputString.str();
}

string CommandSearchPowerSearch::getFirstCharacters(
		vector<string> tokenizedMainString) {
	string listOfFirstCharacters;
	int i;

	for (i=0; unsigned(i)<tokenizedMainString.size(); i++) {
		if (tokenizedMainString[i].size() > 0) {
			listOfFirstCharacters.push_back(
				tokenizedMainString[i][0]);
		}
	}

	return listOfFirstCharacters;
}

bool CommandSearchPowerSearch::checkIsMatchesFuzzySearch(
		string mainToken, string searchToken) {
	vector<int> matchRecord;
	vector<int> errorRecord;
	int defaultError = INITIAL_VALUE_FUZZYSEARCH_DEFAULT_ERROR;
	int idealFoundIndex = 
		INITIAL_VALUE_FUZZYSEARCH_IDEAL_FOUND_INDEX;
	int actualFoundIndex;
	int lowerBound;
	int upperBound;
	int i;
	bool isFound;

	for(i=0; unsigned(i)<searchToken.size(); i++) {
		idealFoundIndex = i;
		lowerBound = idealFoundIndex - defaultError;
		upperBound = idealFoundIndex + defaultError;
		actualFoundIndex = mainToken.find(searchToken[i], 
			toZeroIfNegative(lowerBound));

		if (actualFoundIndex == string::npos) {
			matchRecord.push_back(NOTFOUND);
		}
		else {
			if (isInRange(lowerBound, upperBound, 
					actualFoundIndex)) {
				matchRecord.push_back(FOUND);
			}
			else {
				matchRecord.push_back(NOTFOUND);
			}
		}
	}

	isFound = detIfmatchRecordAcceptable(matchRecord);

	return isFound;
}



bool CommandSearchPowerSearch::isInRange(int lowerBound, 
		int upperBound, int toCheckRange) {

	if (toCheckRange < lowerBound) {
		return false;
	}
	else if (toCheckRange > upperBound) {
		return false;
	}
	return true;
}

int CommandSearchPowerSearch::toZeroIfNegative(int toConvert) {
	if (toConvert >= 0) {
		return toConvert;
	}
	return 0;
}

bool CommandSearchPowerSearch::detIfmatchRecordAcceptable(
		vector<int> matchRecord) {
	double percentageFit;
	double totalSum = 0;
	int i;

	for (i=0; unsigned(i)<matchRecord.size(); i++) {
		totalSum += matchRecord[i];
	}

	percentageFit = totalSum / matchRecord.size();

	if (percentageFit >= FUZZY_SEARCH_MATCH_REORD_TOLERANCE) {
		return true;
	}
	else {
		return false;
	}
}
