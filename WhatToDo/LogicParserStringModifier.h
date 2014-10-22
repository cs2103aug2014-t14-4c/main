#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <exception>
#include "Command.h"

const std::string SPACE = " ";
const std::string EMPTY_STRING = "";
const std::string delimiters = " \f\n\r\t\v";

class LogicParserStringModifier {
public:
	LogicParserStringModifier(void);
	~LogicParserStringModifier(void);

	std::string getFirstWord(std::string text);
	std::string getStringExceptFirstWord(std::string text);

	std::string transformToLowercase(std::string text);
	std::vector<std::string> tokenizeString(std::string text);
	std::string convertTokenVectorToString(std::vector<std::string> text);

	bool isOneWord(std::string text);
	bool isNumber(std::string text);

	std::string trimWhiteSpace(std::string text);

private:
	std::string trimLeft(std::string text);
	std::string trimRight(std::string text);
};

