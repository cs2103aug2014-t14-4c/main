#pragma once
#include "LogicParserStringModifier.h"
#include "boost\date_time.hpp"

const std::string USERMESSAGE_DATETIME_NOT_PARSED = 
	"Incorrect date/time input format. Please re-enter your task";
const std::string DATE_DELIMITERS = 
	"./-";
const std::string TIME_DELIMITERS = 
	".:";
const std::string TIME_AM = 
	"am";
const std::string TIME_PM = 
	"pm";
const std::array<std::string, 2> TODAY = 
	{"today", "tdy"};
const std::array<std::string, 5> TOMORROW = 
	{"tomorrow", "tmr", "tml", "tmw", "tmrw"};
const std::string IDENTIFIER_THIS =
	"this";
const std::string IDENTIFIER_NEXT =
	"next";
const std::array<std::string, 7> WEEKDAYS_SHORT = 
	{"mon", "tue", "wed", "thu", "fri", "sat", "sun"};
const std::array<std::string, 7> WEEKDAYS_LONG = 
	{"monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"};
const std::array<std::string, 3> IDENTIFIER_START = 
	{"at", "on", "from",};
const std::array<std::string, 1> IDENTIFIER_END = 
	{"to"};
const std::array<std::string, 3> IDENTIFIER_DEADLINE = 
	{"by", "due", "before"};
const std::array<std::string, 12> MONTHS_LONG = 
	{"january", "february", "march", "april", "may", "june",
	"july", "august", "september", "october", "november", "december"};
const std::array<std::string, 12> MONTHS_SHORT = 
	{"jan", "feb", "mar", "apr", "may", "jun",
	"jul", "aug", "sep", "oct", "nov", "dec"};


class LogicParserDatetimeParser :public StringModifier {
public:
	LogicParserDatetimeParser(void);
	~LogicParserDatetimeParser(void);
	std::string addTaskDatetime(Command* command, Task* task, std::vector<std::string> parameters);

//private:
	boost::gregorian::date _startDate;
	boost::gregorian::date _endDate;
	boost::gregorian::date _deadlineDate;
	boost::posix_time::time_duration _startTime;
	boost::posix_time::time_duration _endTime;
	boost::posix_time::time_duration _deadlineTime;
	boost::posix_time::ptime _startDatetime;
	boost::posix_time::ptime _endDatetime;
	boost::posix_time::ptime _deadlineDatetime;
	
	boost::gregorian::date _currentDate;
	std::vector<std::string> _parameters;

	void setParameters(std::vector<std::string> parameters);
	std::string convertParametersToString(void);
	void setFoundDatetime(Task* task);
	void eraseWord(std::vector<std::string>::iterator& iter);
	std::vector<std::string>::iterator nextWord(std::vector<std::string>::iterator iter);

	void addStartDatetime(void);
	bool hasStartDatetime(void);
	bool isStartIdentifier(std::string word);
	bool addStartWithIdentifier(std::vector<std::string>::iterator iter);
	void addStartWithoutIdentifier();
	void combineStartTimeDate();

	void addEndDatetime(void);
	bool hasEndDatetime(void);
	bool isEndIdentifier(std::string word);
	bool addEndWithIdentifier(std::vector<std::string>::iterator iter);
	void combineEndTimeDate();

	void addDeadlineDatetime(void);
	bool hasDeadlineDatetime(void);
	bool isDeadlineIdentifier(std::string word);
	bool addDeadlineWithIdentifier(std::vector<std::string>::iterator iter);
	void combineDeadlineTimeDate();

	bool isATime(std::vector<std::string>::iterator iter);
	bool isAmPmTime(std::string word);
	bool is12HourTime(int time);
	bool isAm(std::string word);
	bool isPm(std::string word);
	bool is24HourTime(std::string word);
	std::string removeTimeDelimiters(std::string word);

	bool isADate(std::vector<std::string>::iterator iter);
	bool is3ParameterDate(std::vector<std::string>::iterator iter);
	bool is2ParameterDate(std::vector<std::string>::iterator iter);
	bool isDateAndMonth(std::vector<std::string>::iterator iter);
	bool isThisNextWeek(std::vector<std::string>::iterator iter);
	bool is1ParameterDate(std::vector<std::string>::iterator iter);
	bool isToday(std::string date);
	bool isTomorrow(std::string date);
	bool isNumericalDate(std::string date);
	bool isDate(int date);
	bool isMonth(std::string month);
	bool isMonth(int month);
	bool isYear(int year);
	bool isThis(std::string word);
	bool isNext(std::string word);
	bool isWeekday(std::string word);
	std::string removeDateDelimiters(std::string word);

	boost::posix_time::time_duration parseTime(std::vector<std::string>::iterator iter);
	boost::gregorian::date parseDate(std::vector<std::string>::iterator iter);
	boost::gregorian::date parse3ParameterDate(std::vector<std::string>::iterator iter);
	boost::gregorian::date parse2ParameterDate(std::vector<std::string>::iterator iter);
	boost::gregorian::date parse1ParameterDate(std::vector<std::string>::iterator iter);
	int parseMonth(std::string month);
	boost::gregorian::date findThisWeekday(std::string day);
	boost::gregorian::date findNextWeekday(std::string day);
};

