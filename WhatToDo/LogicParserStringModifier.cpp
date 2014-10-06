#include "LogicParserStringModifier.h"

LogicParserStringModifier::LogicParserStringModifier(void) {
}

std::string LogicParserStringModifier::getFirstWord(std::string text, std::string delimiters) {
	text = LogicParserStringModifier::trimWhiteSpace(text);
	return text.substr(0, text.find_first_of(delimiters));
}

std::string LogicParserStringModifier::getStringExceptFirstWord(std::string text, std::string delimiters) {
	text = LogicParserStringModifier::trimWhiteSpace(text);
	text = text.substr(text.find_first_of(delimiters));
	return LogicParserStringModifier::trimWhiteSpace(text);
}

std::string LogicParserStringModifier::transformToLowercase(std::string text) {
	std::transform(text.begin(), text.end(), text.begin(), tolower);
	return text;
}

bool LogicParserStringModifier::isOneWord(std::string text) {
	text = LogicParserStringModifier::trimWhiteSpace(text);
	return (std::all_of(text.begin(), text.end(), isalnum));
}

std::string LogicParserStringModifier::trimWhiteSpace(std::string text) {
	return LogicParserStringModifier::trimLeft(LogicParserStringModifier::trimRight(text));
}

std::string LogicParserStringModifier::trimLeft(std::string text, std::string delimiters) {
	return text.substr(text.find_first_not_of(delimiters));
}

std::string LogicParserStringModifier::trimRight(std::string text, std::string delimiters) {
	return text.substr(0, text.find_last_not_of(delimiters) + 1);
}