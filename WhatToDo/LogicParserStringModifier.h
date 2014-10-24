//****************************************************************************
//StringModifier is the class containing the common string manipulation and 
//modification methods used throughout the Parser component.
//
//Sample usage:
//	StringModifier stringMod;
//	string output = stringMod.transformToLowercase("One");
//  //output == "one"
//
//@Shu Chang A0110655N
//****************************************************************************

#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <assert.h>
#include <exception>
#include "Command.h"

using namespace std;

enum ConstInt {
	Zero, One, Two, Three
};

const string SPACE = " ";
const string EMPTY_STRING = "";
const string WHITESPACE_CHAR = " \f\n\r\t\v";

class StringModifier {
public:
	StringModifier(void);
	~StringModifier(void);

	bool isOneWord(string text);

	//Checks if the given string is wholly alphanumeric, excluding starting
	//and ending whitespace characters. Note that negative numbers denoted by
	//a - sign will fail this check.
	bool isNumber(string text);

	string getFirstWord(string text);

	//Gets the string given with the first word removed. Returns an empty
	//string if the given string consistly only of one word.
	string getExceptFirstWord(string text);

	//Trims the starting and ending whitespace characters around the given
	//string. Note that it does not modify whitespace characters between words.
	string trimWhiteSpace(string text);

	string transformToLowercase(string text);

	vector<string> tokenizeString(string text);

	//Sequentially concatenates a vector of strings into a single string,
	//with each token separated by a space.
	string detokenizeVector(vector<string> text);

private:
	string trimLeft(string text);
	string trimRight(string text);
};

