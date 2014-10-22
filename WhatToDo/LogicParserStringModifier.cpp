#include "LogicParserStringModifier.h"

StringModifier::StringModifier(void) {
}

StringModifier::~StringModifier(void) {
}

bool StringModifier::isOneWord(std::string text) {
	try {
		if(text.empty()) {
			throw std::invalid_argument(EMPTY_STRING);
		}
		text = StringModifier::trimWhiteSpace(text);
		return (text.find_first_of(WHITESPACE_DELIMITERS) == std::string::npos);
	} catch(...) {
		return false;
	}
}

bool StringModifier::isNumber(std::string text) {
	try {
		if(text.empty()) {
			throw std::invalid_argument(EMPTY_STRING);
		}
		text = StringModifier::trimWhiteSpace(text);
		return std::all_of(text.begin(), text.end(), isdigit);
	} catch(...) {
		return false;
	}
}

std::string StringModifier::getFirstWord(std::string text) {
	assert(!text.empty());
	text = StringModifier::trimWhiteSpace(text);
	return text.substr(ZERO, text.find_first_of(WHITESPACE_DELIMITERS));
}

std::string StringModifier::getExceptFirstWord(std::string text) {
	assert(!text.empty() && !isOneWord(text));
	text = StringModifier::trimWhiteSpace(text);
	text = text.substr(text.find_first_of(WHITESPACE_DELIMITERS));
	return StringModifier::trimWhiteSpace(text);
}

std::string StringModifier::trimWhiteSpace(std::string text) {
	try {
		if(text.empty()) {
			throw std::invalid_argument(EMPTY_STRING);
		}
		return StringModifier::trimLeft(StringModifier::trimRight(text));
	} catch(const std::invalid_argument& e) {
		return e.what();
	}
}

std::string StringModifier::transformToLowercase(std::string text) {
	assert(!text.empty());
	std::transform(text.begin(), text.end(), text.begin(), tolower);
	return text;
}

std::vector<std::string> StringModifier::tokenizeString(std::string text) {
	try {
		if(text.empty()) {
			throw std::invalid_argument(EMPTY_STRING);
		}
		std::istringstream iss(text);
		std::string currentWord;
		std::vector<std::string> tokens;

		while(iss >> currentWord) {
			tokens.push_back(currentWord);
		}

		return tokens;
	}
	catch(const std::invalid_argument) {
		std::vector<std::string> emptyVector;
		return emptyVector;
	}
}

std::string StringModifier::detokenizeVector(std::vector<std::string> text) {
	try {
		if(text.empty()) {
			throw std::invalid_argument(EMPTY_STRING);
		}
		std::string line;

		for(auto iter = text.begin(); iter != text.end(); ++iter) {
			line += *iter + SPACE;
		}

		return StringModifier::trimWhiteSpace(line);
	}
	catch(const std::invalid_argument& e) {
		return e.what();
	}
}

std::string StringModifier::trimLeft(std::string text) {
	assert(!text.empty());
	return text.substr(text.find_first_not_of(WHITESPACE_DELIMITERS));
}

std::string StringModifier::trimRight(std::string text) {
	assert(!text.empty());
	return text.substr(ZERO, text.find_last_not_of(WHITESPACE_DELIMITERS) + ONE);
}