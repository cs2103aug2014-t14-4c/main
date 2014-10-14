#pragma once
#include <string>
#include <algorithm>

class LogicParserStringModifier {
public:
	LogicParserStringModifier(void);

	//Returns the first word in a string
	std::string getFirstWord(std::string text, const std::string delimiters = " \f\n\r\t\v");
	//Returns the string with the first word omitted
	std::string getStringExceptFirstWord(std::string text, const std::string delimiters = " \f\n\r\t\v");
	//Converts a string to lowercase
	std::string transformToLowercase(std::string text);
	//Checks if a given string consists of only one word
	bool isOneWord(std::string text, const std::string delimiters = " \f\n\r\t\v");
	//Trims the whitespace around a given string
	std::string trimWhiteSpace(std::string text);
	//Trims the whitespace on the left of a given string
	std::string trimLeft(std::string text, const std::string delimiters = " \f\n\r\t\v");
	//Trims the whitespace on the right of a given string
	std::string trimRight(std::string text, const std::string delimiters = " \f\n\r\t\v");
};

