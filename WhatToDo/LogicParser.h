#pragma once
#include <string>
#include <sstream>
#include <algorithm>
#include "Command.h"
#include "CommandAdd.h"
#include "CommandDelete.h"
#include "CommandDone.h"
#include "CommandClear.h"
#include "CommandEdit.h"
#include "CommandLoad.h"
#include "CommandRedo.h"
#include "CommandSearch.h"
#include "CommandUndo.h"
#include "Task.h"
#include "boost\date_time.hpp"

const std::string COMMAND_DELETE = "/delete";
const std::string COMMAND_DONE = "/done";
const std::string COMMAND_CLEAR = "/clear";
const std::string COMMAND_EDIT = "/edit";
const std::string COMMAND_LOAD = "/load";
const std::string COMMAND_REDO = "/redo";
const std::string COMMAND_SEARCH = "/search";
const std::string COMMAND_UNDO = "/undo";
const std::string IDENTIFIER_TAG = "#";
const std::string IDENTIFIER_DATETIME = "-";
const std::string IDENTIFIER_DATETIME_AT = "-at";
const std::string IDENTIFIER_DATETIME_BY = "-by";
const std::string IDENTIFIER_DATETIME_ON = "-on";
const std::string IDENTIFIER_DATETIME_FROM = "-from";
const std::string IDENTIFIER_DATETIME_TO = "-to";

const std::locale formats[] = {
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d%m%Y %H:%M")), //25042014
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d%m%y %H:%M")), //250414
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d%m %H:%M")), //2504

	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d-%m-%Y %H:%M")), //25-04-2014
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d-%m-%y %H:%M")), //25-04-14
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d-%m %H:%M")), //25-04

	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d/%m/%Y %H:%M")), //25/04/2014
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d/%m/%y %H:%M")), //25/04/14
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d/%m %H:%M")), //25/04

	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d %B %Y %H:%M")), //25 April 2014
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d %B %y %H:%M")), //25 April 14
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d %B %H:%M")), //25 April

	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d %b %Y %H:%M")), //25 Apr 2014
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d %b %y %H:%M")), //25 Apr 14
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d %b %H:%M")), //25 Apr


	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d%m%Y %H%M")), //25042014
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d%m%y %H%M")), //250414
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d%m %H%M")), //2504

	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d-%m-%Y %H%M")), //25-04-2014
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d-%m-%y %H%M")), //25-04-14
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d-%m %H%M")), //25-04

	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d/%m/%Y %H%M")), //25/04/2014
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d/%m/%y %H%M")), //25/04/14
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d/%m %H%M")), //25/04

	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d %B %Y %H%M")), //25 April 2014
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d %B %y %H%M")), //25 April 14
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d %B %H%M")), //25 April

	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d %b %Y %H%M")), //25 Apr 2014
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d %b %y %H%M")), //25 Apr 14
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d %b %H%M")), //25 Apr


	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d%m%Y")), //25042014
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d%m%y")), //250414
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d%m")), //2504

	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d-%m-%Y")), //25-04-2014
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d-%m-%y")), //25-04-14
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d-%m")), //25-04

	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d/%m/%Y")), //25/04/2014
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d/%m/%y")), //25/04/14
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d/%m")), //25/04

	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d %B %Y")), //25 April 2014
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d %B %y")), //25 April 14
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d %B")), //25 April

	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d %b %Y")), //25 Apr 2014
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d %b %y")), //25 Apr 14
	std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d %b")), //25 Apr
};
const size_t formats_n = sizeof(formats)/sizeof(formats[0]);

class LogicParser {
	public:
		//Constructor
		LogicParser(void);
		//Gets the command with the parameters given by the user input
		Command* getCommandFromUserInput(std::string userInput);

	private:
		enum DateTimeType {
			AT, BY, ON, FROM, TO, INVALID
		};

		std::string _userInput;
		void setUserInput(std::string userInput);

		Command* LogicParser::createCommand();
		std::string getUserCommand(void);

		Command* createAddCommand();
		Command* createEditCommand();
		Command* createSearchCommand();

		void addTaskIndex(Command* command);
		void removeEditIndex();
		void addTaskDetails(Command* command);
		void addTaskTags(Task* task, std::string& taskParameters);
		bool isTag(std::string word);
		void addTaskDateTime(Task* task, std::string& taskParameters);
		bool isDateTimeIdentifier(std::string word);
		DateTimeType determineDateTimeType(std::string word);
		void addTaskName(Task* task, std::string taskParameters);

		Command* createDeleteCommand();
		Command* createDoneCommand();

		Command* createClearCommand();
		Command* createLoadCommand();
		Command* createRedoCommand();
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
		std::vector<std::string> splitWordsIntoVector(std::string text);
};

