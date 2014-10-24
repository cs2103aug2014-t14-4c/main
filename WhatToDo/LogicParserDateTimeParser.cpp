#include "LogicParserDatetimeParser.h"

DatetimeParser::DatetimeParser(void) {
	_currentDate = gr::day_clock::local_day();
	_startTime = gr::not_a_date_time;
	_endTime = gr::not_a_date_time;
	_deadlineTime = gr::not_a_date_time;
}

DatetimeParser::~DatetimeParser(void) {
}

void DatetimeParser::addTaskDatetime(Task* task, string& parameters) {
	try{
		DatetimeParser::setParameters(parameters);

		DatetimeParser::addDeadlineDatetime();	
		DatetimeParser::addStartDatetime();
		if(DatetimeParser::hasStartDatetime()) {
			DatetimeParser::addEndDatetime();
		}

		DatetimeParser::setFoundDatetime(task);
		parameters = DatetimeParser::getParameters();
	} catch(const exception&) {
		parameters = DatetimeParser::getParameters();
		throw;
	}
}

void DatetimeParser::setParameters(string parameters) {
	_parameters = StringModifier::tokenizeString(parameters);
}

string DatetimeParser::getParameters() {
	return StringModifier::detokenizeVector(_parameters);
}

void DatetimeParser::setFoundDatetime(Task* task) {
	task->setTaskStartTime(_startDatetime);
	task->setTaskEndTime(_endDatetime);
	task->setTaskDeadline(_deadlineDatetime);
}

void DatetimeParser::eraseWord(vector<string>::iterator& iter) {
	*iter = EMPTY_STRING;
}

//Start
void DatetimeParser::addStartDatetime(void) {
	try {
		DatetimeParser::addStartWithIdentifier(); 
		if(!DatetimeParser::hasStartDate() 
				|| !DatetimeParser::hasStartTime()) {
			DatetimeParser::addStartWithoutIdentifier();
		}
		DatetimeParser::combineStartDatetime();
	} catch(const exception&) {
		throw;
	}
}

bool DatetimeParser::hasStartDatetime(void) {
	return !_startDatetime.is_not_a_date_time();
}

bool DatetimeParser::hasStartDate(void) {
	return !_startDate.is_not_a_date();
}

bool DatetimeParser::hasStartTime(void) {
	return !_startTime.is_not_a_date_time();
}

void DatetimeParser::addStartWithIdentifier(void) {
	try {
		for(auto iter = _parameters.begin(); 
				iter != _parameters.end(); 
				++iter) {

			if(DatetimeParser::isStartIdentifier(*iter) 
					&& DatetimeParser::isATime(iter + One)) {
				DatetimeParser::addStartTime(iter + One);
				DatetimeParser::eraseWord(iter);

			} else if(DatetimeParser::isStartIdentifier(*iter)
					&& DatetimeParser::isADate(iter + One)) {
				DatetimeParser::addStartDate(iter + One);
				DatetimeParser::eraseWord(iter);
			}
		}
	} catch(const exception&) {
		throw;
	}
}

void DatetimeParser::addStartDate(vector<string>::iterator iter) {
	if(DatetimeParser::is3WordDate(iter)) {
		if(DatetimeParser::isATime(iter + Three)) {
			_startTime = DatetimeParser::parseTime(iter + Three);
		}
	} else if(DatetimeParser::is2WordDate(iter)) {
		if(DatetimeParser::isATime(iter + Two)) {
			_startTime = DatetimeParser::parseTime(iter + Two);
		}
	} else if(DatetimeParser::isATime(iter + One)) {
			_startTime = DatetimeParser::parseTime(iter + One);
	}
	_startDate = DatetimeParser::parseDate(iter);
}

void DatetimeParser::addStartTime(vector<string>::iterator iter) {
	if(DatetimeParser::isADate(iter + One)) {
		_startDate = DatetimeParser::parseDate(iter + One);
	}
	_startTime = DatetimeParser::parseTime(iter);
}

void DatetimeParser::addStartWithoutIdentifier(void) {
	try {
		for(auto iter = _parameters.begin(); 
				iter != _parameters.end(); 
				++iter) {

			if(!DatetimeParser::hasStartTime() 
					&& DatetimeParser::isATime(iter)) {
				_startTime = DatetimeParser::parseTime(iter);

			} else if(!DatetimeParser::hasStartDate()
					&& DatetimeParser::isADate(iter)) {
				_startDate = DatetimeParser::parseDate(iter);
			}
		}
	} catch(const exception&) {
		throw;
	}
}

bool DatetimeParser::isStartIdentifier(string word) {
	for(auto iter = DATE_START.begin(); 
			iter != DATE_START.end(); 
			++iter) {
		if(StringModifier::transformToLowercase(word) == *iter) {
			return true;
		}
	}
	return false;
}

void DatetimeParser::combineStartDatetime(void) {
	if(!DatetimeParser::hasStartTime()) {
		pt::time_duration allDay(pt::seconds(1));
		_startTime = allDay;
	} else if(!DatetimeParser::hasStartDate()) {
		_startDate = _currentDate;
	}
	pt::ptime startDatetime(_startDate, _startTime);
	_startDatetime = startDatetime;
}

//End
void DatetimeParser::addEndDatetime(void) {
	try {
		DatetimeParser::addEndWithIdentifier(); 
		DatetimeParser::combineEndDatetime();
	} catch(const exception&) {
		throw;
	}
}

bool DatetimeParser::hasEndDatetime(void) {
	return !_endDatetime.is_not_a_date_time();
}

bool DatetimeParser::hasEndDate(void) {
	return !_endDate.is_not_a_date();
}

bool DatetimeParser::hasEndTime(void) {
	return !_endTime.is_not_a_date_time();
}

void DatetimeParser::addEndWithIdentifier(void) {
	try {
		for(auto iter = _parameters.begin(); 
				iter != _parameters.end(); 
				++iter) {

			if(DatetimeParser::isEndIdentifier(*iter) 
					&& DatetimeParser::isATime(iter + One)) {
				DatetimeParser::addEndTime(iter + One);
				DatetimeParser::eraseWord(iter);

			} else if(DatetimeParser::isEndIdentifier(*iter)
					&& DatetimeParser::isADate(iter + One)) {
				DatetimeParser::addEndDate(iter + One);
				DatetimeParser::eraseWord(iter);
			}
		}
	} catch(const exception&) {
		throw;
	}
}

void DatetimeParser::addEndDate(vector<string>::iterator iter) {
	if(DatetimeParser::is3WordDate(iter)) {
		if(DatetimeParser::isATime(iter + Three)) {
			_endTime = DatetimeParser::parseTime(iter + Three);
		}
	} else if(DatetimeParser::is2WordDate(iter)) {
		if(DatetimeParser::isATime(iter + Two)) {
			_endTime = DatetimeParser::parseTime(iter + Two);
		}
	} else if(DatetimeParser::isATime(iter + One)) {
			_endTime = DatetimeParser::parseTime(iter + One);
	}
	_endDate = DatetimeParser::parseDate(iter);
}

void DatetimeParser::addEndTime(vector<string>::iterator iter) {
	if(DatetimeParser::isADate(iter + One)) {
		_endDate = DatetimeParser::parseDate(iter + One);
	}
	_endTime = DatetimeParser::parseTime(iter);

}

bool DatetimeParser::isEndIdentifier(string word) {
	for(auto iter = DATE_END.begin(); 
			iter != DATE_END.end(); 
			++iter) {
		if(StringModifier::transformToLowercase(word) == *iter) {
			return true;
		}
	}
	return false;
}

void DatetimeParser::combineEndDatetime(void) {
	if(!DatetimeParser::hasEndTime()) {
		pt::time_duration allDay(pt::seconds(1));
		_endTime = allDay;
	} else if(!DatetimeParser::hasEndDate()) {
		_endDate = _startDate;
	}
	pt::ptime endDatetime(_endDate, _endTime);
	_endDatetime = endDatetime;
}

//Deadline
void DatetimeParser::addDeadlineDatetime(void) {
	try {
		DatetimeParser::addDeadlineWithIdentifier(); 
		DatetimeParser::combineDeadlineDatetime();
	} catch(const exception&) {
		throw;
	}
}

bool DatetimeParser::hasDeadlineDatetime(void) {
	return !_deadlineDatetime.is_not_a_date_time();
}

bool DatetimeParser::hasDeadlineDate(void) {
	return !_deadlineDate.is_not_a_date();
}

bool DatetimeParser::hasDeadlineTime(void) {
	return !_deadlineTime.is_not_a_date_time();
}

void DatetimeParser::addDeadlineWithIdentifier(void) {
	try {
		for(auto iter = _parameters.begin(); 
				iter != _parameters.end(); 
				++iter) {

			if(DatetimeParser::isDeadlineIdentifier(*iter) 
					&& DatetimeParser::isATime(iter + One)) {
				DatetimeParser::addDeadlineTime(iter + One);
				DatetimeParser::eraseWord(iter);

			} else if(DatetimeParser::isDeadlineIdentifier(*iter)
					&& DatetimeParser::isADate(iter + One)) {
				DatetimeParser::addDeadlineDate(iter + One);
				DatetimeParser::eraseWord(iter);
			}
		}
	} catch(const exception&) {
		throw;
	}
}

void DatetimeParser::addDeadlineDate(vector<string>::iterator iter) {
	if(DatetimeParser::is3WordDate(iter)) {
		if(DatetimeParser::isATime(iter + Three)) {
			_deadlineTime = DatetimeParser::parseTime(iter + Three);
		}
	} else if(DatetimeParser::is2WordDate(iter)) {
		if(DatetimeParser::isATime(iter + Two)) {
			_deadlineTime = DatetimeParser::parseTime(iter + Two);
		}
	} else if(DatetimeParser::isATime(iter + One)) {
			_deadlineTime = DatetimeParser::parseTime(iter + One);
	}
	_deadlineDate = DatetimeParser::parseDate(iter);
}

void DatetimeParser::addDeadlineTime(vector<string>::iterator iter) {
	if(DatetimeParser::isADate(iter + One)) {
		_deadlineDate = DatetimeParser::parseDate(iter + One);
	}
	_deadlineTime = DatetimeParser::parseTime(iter);
}

bool DatetimeParser::isDeadlineIdentifier(string word) {
	for(auto iter = DATE_DEADLINE.begin(); 
			iter != DATE_DEADLINE.end(); 
			++iter) {
		if(StringModifier::transformToLowercase(word) == *iter) {
			return true;
		}
	}
	return false;
}

void DatetimeParser::combineDeadlineDatetime(void) {
	if(!DatetimeParser::hasDeadlineTime()) {
		pt::time_duration allDay(pt::seconds(1));
		_deadlineTime = allDay;
	} else if(!DatetimeParser::hasDeadlineDate()) {
		_deadlineDate = _currentDate;
	}
	pt::ptime deadlineDatetime(_deadlineDate, _deadlineTime);
	_deadlineDatetime = deadlineDatetime;
}

//Time Parsing Functions													   
bool DatetimeParser::isATime(vector<string>::iterator iter) {
	if(iter == _parameters.end()) {
		return false;
	}
	return (DatetimeParser::isAmPmTime(*iter) 
		|| DatetimeParser::isMilitaryTime(*iter));
}

pt::time_duration DatetimeParser::parseTime(vector<string>::iterator iter) {
	try {
		assert(iter != _parameters.end());
		assert(DatetimeParser::isATime(iter));

		int hours = Zero;
		int minutes = Zero;

		if(DatetimeParser::isAmPmTime(*iter)) {
			DatetimeParser::parseAmPmTime(*iter, hours, minutes);
		} else {
			DatetimeParser::parseMilitaryTime(*iter, hours, minutes);
		}

		pt::time_duration timeOfDay = pt::hours(hours) + pt::minutes(minutes);
		DatetimeParser::eraseWord(iter);
		return timeOfDay;
	} catch(const exception&) {
		throw;
	}
}

bool DatetimeParser::isMilitaryTime(string word) {
	DatetimeParser::removeTimeDelimiters(word);
	if(!StringModifier::isNumber(word) || word.length() != STRLEN_24H_TIME) {
		return false;
	}
	return DatetimeParser::is24HourTime(stoi(word));
}

bool DatetimeParser::isAmPmTime(string word) {
	DatetimeParser::removeTimeDelimiters(word);

	istringstream iss(word);
	int time;
	string AMPM;

	iss >> time >> AMPM;
	return (DatetimeParser::is12HourTime(time) 
		&& (DatetimeParser::isAm(AMPM) || DatetimeParser::isPm(AMPM)));
}

bool DatetimeParser::is24HourTime(int number) {
	int hours = number / NUMLEN_3;
	int minutes = number % NUMLEN_3;
	return ((hours >= VALID_MIN_HOUR_24 && hours <= VALID_MAX_HOUR_24) 
		&& (minutes >= VALID_MIN_MINUTE && minutes <= VALID_MAX_MINUTE));
}

bool DatetimeParser::is12HourTime(int number) {
	if(number < NUMLEN_3) {
		return (number >= VALID_MIN_HOUR_12 && number <= VALID_MAX_HOUR_12);
	} else {
		int hours = number / NUMLEN_3;
		int minutes = number % NUMLEN_3;
		return ((hours >= VALID_MIN_HOUR_12 && hours <= VALID_MAX_HOUR_12) 
			&& (minutes >= VALID_MIN_MINUTE && minutes <= VALID_MAX_MINUTE));
	}
}

bool DatetimeParser::isAm(string word) {
	return (word == TIME_AM);
}

bool DatetimeParser::isPm(string word) {
	return (word == TIME_PM);
}

void DatetimeParser::parseMilitaryTime(string word, int& hours, int& minutes) {
		int time = stoi(word);
		hours = time / NUMLEN_3;
		minutes = time % NUMLEN_3;
}

void DatetimeParser::parseAmPmTime(string word, int& hours, int& minutes) {
		istringstream iss(word);
		int time;
		string AMPM;

		iss >> time >> AMPM;
		if(time < NUMLEN_3) {
			hours = time;
		} else {
			hours = time / NUMLEN_3;
			minutes = time % NUMLEN_3;
		}

		if(DatetimeParser::isAm(AMPM) && hours == VALID_MAX_HOUR_12) {
			hours = Zero;
		} else if(DatetimeParser::isPm(AMPM) && hours != VALID_MAX_HOUR_12) {
			hours += VALID_MAX_HOUR_12;
		}
}

void DatetimeParser::removeTimeDelimiters(string& word) {
	word = StringModifier::transformToLowercase(word);
	for(auto iter = TIME_DELIMITERS.begin();
			iter != TIME_DELIMITERS.end();
			++iter) {
		word.erase(remove(word.begin(), word.end(), *iter), word.end());
	}
}

//Date Parsing Functions
bool DatetimeParser::isADate(vector<string>::iterator iter) {
	if(iter == _parameters.end()) {
		return false;
	}
	return (DatetimeParser::is3WordDate(iter) 
		|| DatetimeParser::is2WordDate(iter)
		|| DatetimeParser::is1WordDate(iter));
}

gr::date DatetimeParser::parseDate(vector<string>::iterator iter) {
	try{
		assert(iter != _parameters.end());
		assert(DatetimeParser::isADate(iter));
		if(DatetimeParser::is3WordDate(iter)) {
			return parse3WordDate(iter);
		} else if(DatetimeParser::is2WordDate(iter)) {
			return parse2WordDate(iter);
		} else {
			return parse1WordDate(iter);
		}
	} catch(const exception&) {
		throw;
	}
}

bool DatetimeParser::is3WordDate(vector<string>::iterator iter) {
	assert(iter != _parameters.end());
	if((iter + One) == _parameters.end() 
			|| (iter + Two) == _parameters.end()) {
		return false;
	}
	return DatetimeParser::isDayMonthYear(iter);
}

bool DatetimeParser::is2WordDate(vector<string>::iterator iter) {
	assert(iter != _parameters.end());
	if((iter + One) == _parameters.end()) {
		return false;
	}
	return (DatetimeParser::isDayMonth(iter) 
		|| DatetimeParser::isThisNextWeekday(iter));
}

bool DatetimeParser::is1WordDate(vector<string>::iterator iter) {
	assert(iter != _parameters.end());
	return (DatetimeParser::isToday(*iter)
		|| DatetimeParser::isTomorrow(*iter)
		|| DatetimeParser::isWeekday(*iter)
		|| DatetimeParser::isNumericalDate(*iter));
}

bool DatetimeParser::isDayMonthYear(vector<string>::iterator iter) {
	assert(iter != _parameters.end());
	assert((iter + One) != _parameters.end());
	assert((iter + Two) != _parameters.end());
	if(!StringModifier::isNumber(*iter)) {
		return false;
	} else if(!StringModifier::isNumber(*(iter + Two))) {
		return false;
	}
	int day = stoi(*iter);
	string month = *(iter + One);
	int year = stoi(*(iter + Two));
	return (DatetimeParser::isDay(day) 
		&& DatetimeParser::isMonth(month)
		&& DatetimeParser::isYear(year));
}

bool DatetimeParser::isDayMonth(vector<string>::iterator iter) {
	assert(iter != _parameters.end());
	assert((iter + One) != _parameters.end());
	if(!StringModifier::isNumber(*iter)) {
		return false;
	}
	int day = stoi(*iter);
	string month = *(iter + One);
	return (DatetimeParser::isDay(day) 
		&& DatetimeParser::isMonth(month));
}

bool DatetimeParser::isThisNextWeekday(vector<string>::iterator iter) {
	assert(iter != _parameters.end());
	assert((iter + One) != _parameters.end());
	string thisNext = *iter;
	string weekday = *(iter + One);
	return (DatetimeParser::isWeekday(weekday)
		&& (DatetimeParser::isThis(thisNext) 
		|| DatetimeParser::isNext(thisNext)));
}

bool DatetimeParser::isToday(string date) {
	date = StringModifier::transformToLowercase(date);
	for(auto iter = DATE_TODAY.begin();
			iter != DATE_TODAY.end(); 
			++iter) {
		if(date == *iter) {
			return true;
		}
	}
	return false;
}

bool DatetimeParser::isTomorrow(string date) {
	date = StringModifier::transformToLowercase(date);
	for(auto iter = DATE_TOMORROW.begin();
			iter != DATE_TOMORROW.end(); 
			++iter) {
		if(date == *iter) {
			return true;
		}
	}
	return false;
}

bool DatetimeParser::isWeekday(string date) {
	date = StringModifier::transformToLowercase(date);
	for(int index = Zero; index < VALID_MAX_WEEKDAY; ++index) {
		if(date == WEEKDAYS_LONG[index] || date == WEEKDAYS_SHORT[index]) {
			return true;
		}
	}
	return false;
}

bool DatetimeParser::isNumericalDate(string date) {
	DatetimeParser::removeDateDelimiters(date);
	if(!StringModifier::isNumber(date)) {
		return false;
	}
	return (DatetimeParser::isDDMM(date)
		|| DatetimeParser::isDDMMYY(date)
		|| DatetimeParser::isDDMMYYYY(date));
}

bool DatetimeParser::isDDMM(string date) {
	if(date.length() != STRLEN_DDMM) {
		return false;
	}
	int numDate = stoi(date);
	int day = numDate / NUMLEN_3;
	int month = numDate % NUMLEN_3;
	return (DatetimeParser::isDay(day) 
		&& DatetimeParser::isMonth(month));
}

bool DatetimeParser::isDDMMYY(string date) {
	if(date.length() != STRLEN_DDMMYY) {
		return false;
	}
	int numDate = stoi(date);
	int day = numDate / NUMLEN_5;
	int month = (numDate / NUMLEN_3) % NUMLEN_3;
	int year = (numDate % NUMLEN_3) + CURRENT_MILLENIUM;
	return (DatetimeParser::isDay(day) 
		&& DatetimeParser::isMonth(month)
		&& DatetimeParser::isYear(year));
}

bool DatetimeParser::isDDMMYYYY(string date) {
	if(date.length() != STRLEN_DDMMYYYY) {
		return false;
	}
	int numDate = stoi(date);
	int day = numDate / NUMLEN_7;
	int month = (numDate / NUMLEN_5) % NUMLEN_3;
	int year = numDate % NUMLEN_5;
	return (DatetimeParser::isDay(day) 
		&& DatetimeParser::isMonth(month)
		&& DatetimeParser::isYear(year));
}

bool DatetimeParser::isThis(string word) {
	return StringModifier::transformToLowercase(word) == DATE_THIS;
}

bool DatetimeParser::isNext(string word) {
	return StringModifier::transformToLowercase(word) == DATE_NEXT;
}

bool DatetimeParser::isDay(int day) {
	return (day >= VALID_MIN_DAY && day <= VALID_MAX_DAY);
}

bool DatetimeParser::isMonth(int month) {
	return (month >= VALID_MIN_MONTH && month <= VALID_MAX_MONTH);
}

bool DatetimeParser::isYear(int year) {
	return ((year >= VALID_MIN_YEAR_YY && year <= VALID_MAX_YEAR_YY)
		|| year >= VALID_MIN_YEAR_YYYY && year <= VALID_MAX_YEAR_YYYY);
}

bool DatetimeParser::isMonth(string month) {
	month = StringModifier::transformToLowercase(month);
	for(int index = Zero; index < VALID_MAX_MONTH; ++index) {
		if(month == MONTHS_LONG[index] || month == MONTHS_SHORT[index]) {
			return true;
		}
	}
	return false;
}

gr::date DatetimeParser::parse3WordDate(vector<string>::iterator iter) {
	try {
		assert(iter != _parameters.end());
		assert((iter + One) != _parameters.end());
		assert((iter + Two) != _parameters.end());

		gr::date dateFound = parseDayMonthYear(iter);

		DatetimeParser::eraseWord(iter);
		DatetimeParser::eraseWord(iter + One);
		DatetimeParser::eraseWord(iter + Two);
		return dateFound;
	} catch(const exception&) {
		throw;
	}
}

gr::date DatetimeParser::parse2WordDate(vector<string>::iterator iter) {
	try {
		assert(iter != _parameters.end());
		assert((iter + One) != _parameters.end());
		gr::date dateFound;

		if(DatetimeParser::isDayMonth(iter)) {
			dateFound = DatetimeParser::parseDayMonth(iter);
		} else if(DatetimeParser::isThis(*iter)) {
			dateFound = DatetimeParser::parseThisWeekday(*(iter + One));
		} else {
			dateFound = DatetimeParser::parseNextWeekday(*(iter + One));
		}

		DatetimeParser::eraseWord(iter);
		DatetimeParser::eraseWord(iter + One);
		return dateFound;
	} catch(const exception&) {
		throw;
	}
}

gr::date DatetimeParser::parse1WordDate(vector<string>::iterator iter) {
	try {
		assert(iter != _parameters.end());
		gr::date dateFound;

		if(DatetimeParser::isToday(*iter)) {
			dateFound = DatetimeParser::parseToday();
		} else if(DatetimeParser::isTomorrow(*iter)) {
			dateFound = DatetimeParser::parseTomorrow();
		} else if(DatetimeParser::isWeekday(*iter)) {
			dateFound = DatetimeParser::parseComingWeekday(*iter);
		} else {
			dateFound = DatetimeParser::parseNumericalDate(*iter);
		}

		DatetimeParser::eraseWord(iter);
		return dateFound;
	} catch(const exception&) {
		throw;
	}
}

gr::date DatetimeParser::parseDayMonthYear(vector<string>::iterator iter) {
	try {
		int day = DatetimeParser::parseDay(*iter);
		int month = DatetimeParser::parseMonth(*(iter + One));
		int year = DatetimeParser::parseYear(*(iter + Two));
		gr::date dateFound(year, month, day);
		return dateFound;
	} catch(const exception&) {
		throw;
	}
}

gr::date DatetimeParser::parseDayMonth(vector<string>::iterator iter) {
	try {
		int day = DatetimeParser::parseDay(*iter);
		int month = DatetimeParser::parseMonth(*(iter + One));
		int year = _currentDate.year();
		gr::date dateFound(year, month, day);
		return dateFound;
	} catch(const exception&) {
		throw;
	}
}

gr::date DatetimeParser::parseThisWeekday(string weekday) {
	weekday = StringModifier::transformToLowercase(weekday);
	int _currentWeekday = (int)_currentDate.day_of_week();
		
	for(int index = Zero; index < VALID_MAX_WEEKDAY; ++index) {
		if(weekday == WEEKDAYS_LONG[index] 
				|| weekday == WEEKDAYS_SHORT[index]) {
			if(index >= _currentWeekday) {
				return gr::next_weekday(_currentDate, (gr::greg_weekday)index);
			} else {
				gr::date_duration oneWeek(7);
				gr::date thisWeekday = 
					gr::next_weekday(_currentDate, (gr::greg_weekday)index);
				gr::date dateFound = thisWeekday - oneWeek;
				return dateFound;
			}
		}
	}
	gr::date notFound;
	return notFound;
}

gr::date DatetimeParser::parseNextWeekday(string weekday) {
	weekday = StringModifier::transformToLowercase(weekday);
	int _currentWeekday = (int)_currentDate.day_of_week();

	for(int index = Zero; index < VALID_MAX_WEEKDAY; ++index) {
		if(weekday == WEEKDAYS_LONG[index] 
				|| weekday == WEEKDAYS_SHORT[index]) {
			if(index >= _currentWeekday) {
				gr::date_duration oneWeek(7);
				gr::date nextWeekday = 
					gr::next_weekday(_currentDate, (gr::greg_weekday)index);
				gr::date dateFound = nextWeekday + oneWeek;
				return dateFound;
			} else {
				return gr::next_weekday(_currentDate, (gr::greg_weekday)index);
			}
		}
	}
	gr::date notFound;
	return notFound;
}

gr::date DatetimeParser::parseToday(void) {
	return _currentDate;
}

gr::date DatetimeParser::parseTomorrow(void) {
	gr::date_duration oneDay(1);
	return _currentDate + oneDay;
}

gr::date DatetimeParser::parseComingWeekday(string weekday) {
	weekday = StringModifier::transformToLowercase(weekday);
	int _currentWeekday = (int)_currentDate.day_of_week();

	for(int index = Zero; index < VALID_MAX_WEEKDAY; ++index) {
		if(weekday == WEEKDAYS_LONG[index] 
				|| weekday == WEEKDAYS_SHORT[index]) {
			if(index == _currentWeekday) {
				gr::date_duration oneWeek(7);
				return (_currentDate + oneWeek);
			} else {
				return gr::next_weekday(_currentDate, (gr::greg_weekday)index);
			}
		}
	}
	gr::date notFound;
	return notFound;
}

gr::date DatetimeParser::parseNumericalDate(string date) {
	try {
		DatetimeParser::removeDateDelimiters(date);
		assert(StringModifier::isNumber(date));
		if(DatetimeParser::isDDMM(date)) {
			return parseDDMM(stoi(date));
		} else if(DatetimeParser::isDDMMYY(date)) {
			return parseDDMMYY(stoi(date));
		} else {
			return parseDDMMYYYY(stoi(date));
		}
	} catch(const exception&) {
		throw;
	}
}

gr::date DatetimeParser::parseDDMM(int date) {
	try {
		int day = date / NUMLEN_3;
		int month = date % NUMLEN_3;
		int year = _currentDate.year();
		gr::date dateFound(year, month, day);
		return dateFound;
	} catch(const exception&) {
		throw;
	}
}

gr::date DatetimeParser::parseDDMMYY(int date) {
	try {
		int day = date / NUMLEN_5;
		int month = (date / NUMLEN_3) % NUMLEN_3;
		int year = date % NUMLEN_3;
		gr::date dateFound(year, month, day);
		return dateFound;
	} catch(const exception&) {
		throw;
	}
}

gr::date DatetimeParser::parseDDMMYYYY(int date) {
	try {
		int day = date / NUMLEN_7;
		int month = (date / NUMLEN_5) % NUMLEN_3;
		int year = date % NUMLEN_5;
		gr::date dateFound(year, month, day);
		return dateFound;
	} catch(const exception&) {
		throw;
	}
}

int DatetimeParser::parseDay(string day) {
	assert(StringModifier::isNumber(day));
	return stoi(day);
}

int DatetimeParser::parseMonth(string month) {
	if(StringModifier::isNumber(month)) {
		return stoi(month);
	} else {
		month = StringModifier::transformToLowercase(month);
		for(int index = Zero; index < VALID_MAX_MONTH; ++index) {
			if(month == MONTHS_LONG[index] || month == MONTHS_SHORT[index]) {
				return ++index;
			}
		}
	}
	return Zero;
}

int DatetimeParser::parseYear(string year) {
	assert(StringModifier::isNumber(year));
	int numYear = stoi(year);
	if(numYear <= VALID_MAX_YEAR_YY) {
		numYear += CURRENT_MILLENIUM;
	}
	return numYear;
}

void DatetimeParser::removeDateDelimiters(string& word) {
	word = StringModifier::transformToLowercase(word);
	for(auto iter = DATE_DELIMITERS.begin();
			iter != DATE_DELIMITERS.end();
			++iter) {
		word.erase(remove(word.begin(), word.end(), *iter), word.end());
	}
}