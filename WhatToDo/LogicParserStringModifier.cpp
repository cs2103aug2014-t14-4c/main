#include "LogicParserStringModifier.h"

StringModifier::StringModifier(void) {
}

StringModifier::~StringModifier(void) {
}

bool StringModifier::isOneWord(string text) {
	if(text.empty()) {
		return false;
	}
	text = StringModifier::trimWhiteSpace(text);
	return (text.find_first_of(WHITESPACE_CHAR) == string::npos);
}

bool StringModifier::isNumber(string text) {
	if(text.empty()) {
		return false;
	}
	text = StringModifier::trimWhiteSpace(text);
	return all_of(text.begin(), text.end(), isdigit);
}

string StringModifier::getFirstWord(string text) {
	assert(!text.empty());
	text = StringModifier::trimWhiteSpace(text);
	return text.substr(Zero, text.find_first_of(WHITESPACE_CHAR));
}

string StringModifier::getExceptFirstWord(string text) {
	assert(!text.empty());
	if(StringModifier::isOneWord(text)) {
		return EMPTY_STRING;
	}
	text = StringModifier::trimWhiteSpace(text);
	text = text.substr(text.find_first_of(WHITESPACE_CHAR));
	return StringModifier::trimWhiteSpace(text);
}

string StringModifier::trimWhiteSpace(string text) {
	if(text.empty()) {
		return EMPTY_STRING;
	}
	return StringModifier::trimLeft(StringModifier::trimRight(text));
}

string StringModifier::transformToLowercase(string text) {
	if(text.empty()) {
		return EMPTY_STRING;
	}
	transform(text.begin(), text.end(), text.begin(), tolower);
	return text;
}

vector<string> StringModifier::tokenizeString(string text) {
	try {
		if(text.empty()) {
			throw invalid_argument(EMPTY_STRING);
		}
		istringstream iss(text);
		string currentWord;
		vector<string> tokens;

		while(iss >> currentWord) {
			tokens.push_back(currentWord);
		}
		return tokens;
	}
	catch(const invalid_argument) {
		vector<string> emptyVector;
		return emptyVector;
	}
}

string StringModifier::detokenizeVector(vector<string> text) {
	if(text.empty()) {
		return EMPTY_STRING;
	}
	string line;
	for(auto iter = text.begin(); iter != text.end(); ++iter) {
		if(!(*iter).empty()) {
			line += *iter + SPACE;
		}
	}
	return StringModifier::trimWhiteSpace(line);
}

string StringModifier::trimLeft(string text) {
	assert(!text.empty());
	return text.substr(text.find_first_not_of(WHITESPACE_CHAR));
}

string StringModifier::trimRight(string text) {
	assert(!text.empty());
	return text.substr(Zero, text.find_last_not_of(WHITESPACE_CHAR) + One);
}