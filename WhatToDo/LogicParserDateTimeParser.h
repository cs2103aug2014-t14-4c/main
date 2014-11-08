//@author A0110655N
//****************************************************************************
//DatetimeParser is responsible for the parsing of date and/or time tokens in
//the user input, if any. It serves two main functions:
//	1) Parsing the datetimes for new tasks added/tasks that are to be edited
//	2) Parsing the date/date range required for filters.
//
//1) addTaskDatetime - Parsing datetimes for CommandAdd/CommandEdit
//addTaskDatetime takes in a Task pointer and a reference to a string, in order
//to set the Start/End/Deadline datetimes in the task to dates found in the
//string parameters given.
//
//It does so by breaking up the parameters given into individual tokens and 
//searching for instances of date and/or time tokens. If any of the datetimes]
//are found, the relevant tokens will be removed. Finally, the parameters
//string is reconstructed such that it can be used again by the calling 
//function (to be set as the task name). Note that in the process, the
//whitespace character(s) between tokens in the original paramters are all
//replaced by a single space.
//
//addTaskDatetime adds deadlines and end datetimes through the use of key
//identifier words as listed below. These identifiers are required for 
//deadline and end datetimes, but not for start datetimes. As such, a datetime
//token without a identifier will be automatically recognised as a start
//datetime.
//
//addTaskDatetime will throw an out_of_range exception if a "valid datetime",
//after parsing, is found to be non-existent (eg, 30 Feb 2014). It will NOT
//throw exceptions if invalid datetime tokens are encountered (eg, 32 Dec),
//but will instead retain them in the parameters string supplied.
//
//2) addFilterDate - Parsing date/date ranges for CommandFilter
//addFilterDate takes in a Command pointer and a string to parse the date
// or date range filtering options for the filter command.
//
//Similarly to addTaskDatetime, addFilterDate breaks the parameters string
//into tokens to look for instances of date tokens. However, as the parameters
//need not be updated for further use, it is not reconstructed or returned.
//
//addFilterDate requires identifiers to recognise end date filters, but will
//add start date filters regardless of identifiers.
//
//Exception handling procedures are identical the addTaskDatetime, as stated
//above.
//
//
//DatetimeParser currently supports the following formats for input:
//Date - 
//	1) Day Month Year - 15 Nov|November 14|2014
//	2) Day Month - 15 Nov|November (Sets the year as the current year)
//	3) This Weekday - this fri|friday (Sets the date as the friday this week,
//									   regardless of the day today.)
//	4) Next Weekday - next thur (Sets the date as the thursday this week, 
//								 regardless of the day today.)
//	5) DDMM - 0103 (Can be delimited by ".", "/", or "-", eg 01/03. Sets the
//				    year as the current year.)
//	6) DDMMYY - 010314 (As above, can be delimited by ".", "/", or "-".)
//	7) DDMMYYYY  -01032014 (As above, can be delimited by ".", "/", or "-".)
//	8) Weekday - fri|friday (Sets the date as the nearest friday, not counting
//							 today.)
//	9) Special - today|tomorrow
//
//Time - 
//	1) 12 Hours - 12pm, 1245AM (Can be delimited by "." or ":", eg 12:00a.m.)
//	2) 24 Hours - 0845, 2359 (Can be delimited by "." or ":", eg 23.59)
//
//All above input formats are case insensitive.
//
//DatetimeParser inherits string modification functions from StringModifier.
//
//Sample usage:
//	DatetimeParser datetime;
//	Task* task = new task;
//	string parameters = "parameters are inside here";
//	datetime.addTaskDatetime(task, parameters);
//****************************************************************************
#pragma once
#include "boost\date_time.hpp"
#include "LogicParserStringModifier.h"

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

const int NUMLEN_3 = 100;
const int NUMLEN_5 = 10000;
const int NUMLEN_7 = 1000000;

const int STRLEN_24H_TIME = 4;
const int STRLEN_DDMM = 4;
const int STRLEN_DDMMYY = 6;
const int STRLEN_DDMMYYYY = 8;

const int VALID_MIN_HOUR_12 = 1;
const int VALID_MAX_HOUR_12 = 12;
const int VALID_MIN_HOUR_24 = 0;
const int VALID_MAX_HOUR_24 = 23;
const int VALID_MIN_MINUTE = 0;
const int VALID_MAX_MINUTE = 59;

const int VALID_MIN_DAY = 1;
const int VALID_MAX_DAY = 31;
const int VALID_MIN_MONTH = 1;
const int VALID_MAX_MONTH = 12;
const int VALID_MIN_YEAR_YY = 0;
const int VALID_MAX_YEAR_YY = 99;
const int VALID_MIN_YEAR_YYYY = 1970;
const int VALID_MAX_YEAR_YYYY = 9999;
const int VALID_MAX_WEEKDAY = 7;
const int CURRENT_MILLENIUM = 2000;

const string TIME_DELIMITERS = ".:";
const string TIME_AM = "am";
const string TIME_PM = "pm";

const string DATE_DELIMITERS = "./-";
const string DATE_THIS = "this";
const string DATE_NEXT = "next";
const array<string, 2> DATE_TODAY = 
	{"today", "tdy"};
const array<string, 5> DATE_TOMORROW = 
	{"tomorrow", "tmr", "tml", "tmw", "tmrw"};
const array<string, 3> DATE_START = 
	{"at", "on", "from"};
const array<string, 5> DATE_END = 
	{"to", "till", "til", "until", "-"};
const array<string, 3> DATE_DEADLINE = 
	{"by", "due", "before"};

const array<string, 7> WEEKDAYS_SHORT = 
	{"sun", "mon", "tue", "wed", "thu", "fri", "sat",};
const array<string, 7> WEEKDAYS_LONG = 
	{"sunday", "monday", "tuesday", "wednesday",
	"thursday", "friday", "saturday"};
const array<string, 12> MONTHS_SHORT = 
	{"jan", "feb", "mar", "apr", "may", "jun",
	"jul", "aug", "sep", "oct", "nov", "dec"};
const array<string, 12> MONTHS_LONG = 
	{"january", "february", "march", "april", "may", "june",
	"july", "august", "september", "october", "november", "december"};

const string USERMESSAGE_DATETIME_NOT_PARSED = 
	"You've entered a non-existent date!";

class DatetimeParser : public StringModifier {
public:
	DatetimeParser(void);
	~DatetimeParser(void);

	void addTaskDatetime(Task* task, string& parameters);
	void addFilterDate(Command* command, string parameters);

private:
	vector<string> _parameters;
	date _currentDate;
	date _startDate;
	date _endDate;
	date _deadlineDate;
	time_duration _startTime;
	time_duration _endTime;
	time_duration _deadlineTime;
	ptime _startDatetime;
	ptime _endDatetime;
	ptime _deadlineDatetime;
	
	void setParameters(string parameters);
	string getParameters(void);
	void combineDatetime(void);
	void setFoundDatetime(Task* task);
	void setFilterDatetime(Command* command);
	void eraseWord(vector<string>::iterator& iter);
	void addDate(vector<string>::iterator iter, date& date, time_duration& time);
	void addTime(vector<string>::iterator iter, date& date, time_duration& time);

	//Functions to parse the start datetime of the task
	void addStartDatetime(void);
	bool hasStartDatetime(void);
	bool hasStartDate(void);
	bool hasStartTime(void);
	void addStartWithIdentifier(void);
	void addStartWithoutIdentifier(void);
	bool isStartIdentifier(string word);
	void combineStartDatetime(void);

	//Functions to parse the end datetime of the task
	void addEndDatetime(void);
	bool hasEndDatetime(void);
	bool hasEndDate(void);
	bool hasEndTime(void);
	void addEndWithIdentifier(void);
	bool isEndIdentifier(string word);
	void combineEndDatetime(void);

	//Functions to parse the deadline datetime of the task
	void addDeadlineDatetime(void);
	bool hasDeadlineDatetime(void);
	bool hasDeadlineDate(void);
	bool hasDeadlineTime(void);
	void addDeadlineWithIdentifier(void);
	bool isDeadlineIdentifier(string word);
	void combineDeadlineDatetime(void);

	//Time Parsing Functions
	bool isATime(vector<string>::iterator iter);
	time_duration parseTime(vector<string>::iterator iter);

	bool isMilitaryTime(string word);
	bool isAmPmTime(string word);

	bool is24HourTime(int number);
	bool is12HourTime(int number);
	bool isAm(string word);
	bool isPm(string word);

	//Handles the parsing for military (or 24 hour) time.
	void parseMilitaryTime(string word, int& hours, int& minutes);
	//Handles the parsing for AM/PM (or 12 hour) time.
	void parseAmPmTime(string word, int& hours, int& minutes);

	void removeTimeDelimiters(string& word);

	//Date Parsing Functions
	bool isADate(vector<string>::iterator iter);
	date parseDate(vector<string>::iterator iter);

	bool is3WordDate(vector<string>::iterator iter);
	bool is2WordDate(vector<string>::iterator iter);
	bool is1WordDate(vector<string>::iterator iter);

	bool isDayMonthYear(vector<string>::iterator iter);
	bool isDayMonth(vector<string>::iterator iter);
	bool isThisNextWeekday(vector<string>::iterator iter);
	bool isToday(string date);
	bool isTomorrow(string date);
	bool isWeekday(string date);
	bool isNumericalDate(string date);

	bool isDDMM(string date);
	bool isDDMMYY(string date);
	bool isDDMMYYYY(string date);
	bool isThis(string word);
	bool isNext(string word);
	bool isDay(int day);
	bool isMonth(string month);
	bool isMonth(int month);
	bool isYear(int year);

	date parse3WordDate(vector<string>::iterator iter);
	date parse2WordDate(vector<string>::iterator iter);
	date parse1WordDate(vector<string>::iterator iter);

	date parseDayMonthYear(vector<string>::iterator iter);
	date parseDayMonth(vector<string>::iterator iter);
	date parseThisWeekday(string weekday);
	date parseNextWeekday(string weekday);
	date parseToday(void);
	date parseTomorrow(void);
	date parseComingWeekday(string weekday);
	date parseNumericalDate(string date);
	date parseDDMM(int intDate);
	date parseDDMMYY(int intDate);
	date parseDDMMYYYY(int intDate);
	
	int parseDay(string day);
	int parseMonth(string month);
	int parseYear(string year);

	void removeDateDelimiters(string& word);
};