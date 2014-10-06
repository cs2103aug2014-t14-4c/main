#pragma once
#include <string>
#include <sstream>
#include "Task.h"
#include "LogicParserStringModifier.h"
#include "boost\date_time.hpp"

const std::string IDENTIFIER_DATETIME_AT = "-at";
const std::string IDENTIFIER_DATETIME_ON = "-on";
const std::string IDENTIFIER_DATETIME_DUE = "-due";
const std::string IDENTIFIER_DATETIME_BY = "-by";
const std::string IDENTIFIER_DATETIME_FROM = "-from";
const std::string IDENTIFIER_DATETIME_TO = "-to";

//Unusable for now.
/*
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
*/

class LogicParserDateTimeParser {
public:
	LogicParserDateTimeParser(void);
	void addTaskDateTime(Task* task, std::string& parameters);

private:
	enum DateTimeType {
		START, END, DEADLINE, INVALID
	};

	DateTimeType determineDateTimeType(std::string word);
};

