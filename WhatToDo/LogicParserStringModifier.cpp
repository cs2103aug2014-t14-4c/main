#include "LogicParserStringModifier.h"

LogicParserStringModifier::LogicParserStringModifier(void) {
}

LogicParserStringModifier::~LogicParserStringModifier(void) {
}

std::string LogicParserStringModifier::getFirstWord(std::string text) {
	assert(!text.empty());
	text = LogicParserStringModifier::trimWhiteSpace(text);
	return text.substr(0, text.find_first_of(delimiters));
}

std::string LogicParserStringModifier::getStringExceptFirstWord(std::string	 text) {
	assert(!text.empty() && !isOneWord(text));
	text = LogicParserStringModifier::trimWhiteSpace(text);
	text = text.substr(text.find_first_of(delimiters));
	return LogicParserStringModifier::trimWhiteSpace(text);
}

std::string LogicParserStringModifier::transformToLowercase(std::string text) {
	assert(!text.empty());
	std::transform(text.begin(), text.end(), text.begin(), tolower);
	return text;
}

std::vector<std::string> LogicParserStringModifier::tokenizeString(std::string text) {
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

std::string LogicParserStringModifier::convertTokenVectorToString(std::vector<std::string> text) {
	try {
		if(text.empty()) {
			throw std::invalid_argument(EMPTY_STRING);
		}
		std::string line;
		for(auto iter = text.begin(); iter != text.end(); ++iter) {
			line += *iter + SPACE;
		}

		return LogicParserStringModifier::trimWhiteSpace(line);
	}
	catch(const std::invalid_argument& e) {
		return e.what();
	}
}

bool LogicParserStringModifier::isOneWord(std::string text) {
	try {
		if(text.empty()) {
			throw std::invalid_argument(EMPTY_STRING);
		}
	text = LogicParserStringModifier::trimWhiteSpace(text);
	return (text.find_first_of(delimiters) == std::string::npos);
	}
	catch(const std::invalid_argument) {
		return false;
	}
}

bool LogicParserStringModifier::isNumber(std::string text) {
	try {
		if(text.empty()) {
			throw std::invalid_argument(EMPTY_STRING);
		}
		text = LogicParserStringModifier::trimWhiteSpace(text);
		return std::all_of(text.begin(), text.end(), isdigit);
	}
	catch(const std::invalid_argument) {
		return false;
	}
}

std::string LogicParserStringModifier::trimWhiteSpace(std::string text) {
	try {
		if(text.empty()) {
			throw std::invalid_argument(EMPTY_STRING);
		}
		return LogicParserStringModifier::trimLeft(LogicParserStringModifier::trimRight(text));
	}
	catch(const std::invalid_argument& e) {
		return e.what();
	}
}

std::string LogicParserStringModifier::trimLeft(std::string text) {
	assert(!text.empty());
	return text.substr(text.find_first_not_of(delimiters));
}

std::string LogicParserStringModifier::trimRight(std::string text) {
	assert(!text.empty());
	return text.substr(0, text.find_last_not_of(delimiters) + 1);
}