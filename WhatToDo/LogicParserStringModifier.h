#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <assert.h>
#include <exception>
#include "Command.h"

const int ZERO = 0;
const int ONE = 1;
const std::string SPACE = " ";
const std::string EMPTY_STRING = "";
const std::string WHITESPACE_DELIMITERS = " \f\n\r\t\v";

class StringModifier {
public:
	StringModifier(void);
	~StringModifier(void);

	bool isOneWord(std::string text);
	bool isNumber(std::string text);

	std::string getFirstWord(std::string text);
	std::string getExceptFirstWord(std::string text);
	std::string trimWhiteSpace(std::string text);
	std::string transformToLowercase(std::string text);

	std::vector<std::string> tokenizeString(std::string text);
	std::string detokenizeVector(std::vector<std::string> text);

private:
	std::string trimLeft(std::string text);
	std::string trimRight(std::string text);
};

