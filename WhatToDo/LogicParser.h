#pragma once
#include <string>
#include <sstream>
#include <algorithm>
#include "Command.h"
#include "CommandAdd.h"
#include "CommandDelete.h"
#include "CommandEdit.h"
#include "CommandLoad.h"
#include "CommandRedo.h"
#include "CommandSearch.h"
#include "CommandUndo.h"
#include "Task.h"
#include "boost\date_time.hpp"

class LogicParser {
	public:
		//Constructor
		LogicParser(void);
		//Test Functions for internal members. Please ignore.
		void setUserInput(std::string userInput);
		std::string getUserInput(void);
		//This is the only thing you have to worry about.
		Command* getCommandFromUserInput(std::string userInput);

	private:
		std::string _userInput;
		
		Command* LogicParser::createCommand();
		std::string getUserCommand(void);

		Command* createAddCommand();
		void createAddCommandDetails(Command* addCommand);
		void addTaskTags(Task* task, std::string taskParameters);
		bool LogicParser::isTag(std::string word);
		void addTaskDateTime(Task* task, std::string taskParameters);
		void addTaskName(Task* task, std::string taskParameters);

		Command* createDeleteCommand();
		Command* createEditCommand();
		Command* createLoadCommand();
		Command* createRedoCommand();
		Command* createSearchCommand();
		Command* createUndoCommand();

		bool isValidCommandWithStringParameters();
		bool isValidCommandWithIndexParameters();
		bool isValidCommandWithNoParameters();

		std::string getFirstWord(std::string text, const std::string& delimiters = " \f\n\r\t\v");
		std::string getParameters(std::string text, const std::string& delimiters = " \f\n\r\t\v");
		std::string removeFirstWord(std::string text, const std::string& delimiters = " \f\n\r\t\v");
		std::string transformToLowercase(std::string text);
		bool isOneWord(std::string text);
		std::string trimWhiteSpace(const std::string& text);
		std::string trimLeft(const std::string& text, const std::string& delimiters = " \f\n\r\t\v");
		std::string trimRight(const std::string& text, const std::string& delimiters = " \f\n\r\t\v");
};

