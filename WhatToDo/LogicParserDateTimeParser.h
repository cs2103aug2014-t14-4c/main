#pragma once
#include "boost\date_time.hpp"
#include "LogicParserStringModifier.h"

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;
using namespace std;

const int NUMLEN_3 = 100;
const int NUMLEN_5 = 10000;
const int NUMLEN_7 = 1000000;

const int STRLEN_24H_TIME = 4;
const int STRLEN_DDMM = 4;
const int STRLEN_DDMMYY = 6;
const int STRLEN_DDMMYYYY = 8;
const int CURRENT_MILLENIUM = 2000;

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
const int VALID_MAX_YEAR_YYYY = 2100;
const int VALID_MAX_WEEKDAY = 7;

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
	"Incorrect date/time input format."
	" Please use DDMMYYYY and HHMM for the best results.";
const string EXCEPTION_VECTOR_OOR = 
	"Vector out of range";

class DatetimeParser : public StringModifier {
public:
	DatetimeParser(void);
	~DatetimeParser(void);

	void addTaskDatetime(Task* task, string& parameters);

private:
	vector<string> _parameters;
	gr::date _currentDate;
	gr::date _startDate;
	gr::date _endDate;
	gr::date _deadlineDate;
	pt::time_duration _startTime;
	pt::time_duration _endTime;
	pt::time_duration _deadlineTime;
	pt::ptime _startDatetime;
	pt::ptime _endDatetime;
	pt::ptime _deadlineDatetime;
	
	void setParameters(string parameters);
	string getParameters(void);
	void setFoundDatetime(Task* task);
	void eraseWord(vector<string>::iterator& iter);

	//StartDatetime
	void addStartDatetime(void);
	bool hasStartDatetime(void);
	bool hasStartDate(void);
	bool hasStartTime(void);
	void addStartWithIdentifier(void);
	void addStartDate(vector<string>::iterator iter);
	void addStartTime(vector<string>::iterator iter);
	void addStartWithoutIdentifier(void);
	bool isStartIdentifier(string word);
	void combineStartDatetime(void);

	//EndDatetime
	void addEndDatetime(void);
	bool hasEndDatetime(void);
	bool hasEndDate(void);
	bool hasEndTime(void);
	void addEndWithIdentifier(void);
	void addEndDate(vector<string>::iterator iter);
	void addEndTime(vector<string>::iterator iter);
	bool isEndIdentifier(string word);
	void combineEndDatetime(void);

	//DeadlineDatetime
	void addDeadlineDatetime(void);
	bool hasDeadlineDatetime(void);
	bool hasDeadlineDate(void);
	bool hasDeadlineTime(void);
	void addDeadlineWithIdentifier(void);
	void addDeadlineDate(vector<string>::iterator iter);
	void addDeadlineTime(vector<string>::iterator iter);
	bool isDeadlineIdentifier(string word);
	void combineDeadlineDatetime(void);

	//Time Parsing Functions
	bool isATime(vector<string>::iterator iter);
	pt::time_duration parseTime(vector<string>::iterator iter);

	bool isMilitaryTime(string word);
	bool isAmPmTime(string word);

	bool is24HourTime(int number);
	bool is12HourTime(int number);
	bool isAm(string word);
	bool isPm(string word);

	void parseMilitaryTime(string word, int& hours, int& minutes);
	void parseAmPmTime(string word, int& hours, int& minutes);

	void removeTimeDelimiters(string& word);

	//Date Parsing Functions
	bool isADate(vector<string>::iterator iter);
	gr::date parseDate(vector<string>::iterator iter);

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

	gr::date parse3WordDate(vector<string>::iterator iter);
	gr::date parse2WordDate(vector<string>::iterator iter);
	gr::date parse1WordDate(vector<string>::iterator iter);

	gr::date parseDayMonthYear(vector<string>::iterator iter);
	gr::date parseDayMonth(vector<string>::iterator iter);
	gr::date parseThisWeekday(string weekday);
	gr::date parseNextWeekday(string weekday);
	gr::date parseToday(void);
	gr::date parseTomorrow(void);
	gr::date parseComingWeekday(string weekday);
	gr::date parseNumericalDate(string date);
	gr::date parseDDMM(int date);
	gr::date parseDDMMYY(int date);
	gr::date parseDDMMYYYY(int date);
	
	int parseDay(string day);
	int parseMonth(string month);
	int parseYear(string year);

	void removeDateDelimiters(string& word);
};