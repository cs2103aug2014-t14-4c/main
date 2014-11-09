//@author A0110655N
#include "LogicParserDatetimeParser.h"

DatetimeParser::DatetimeParser(void) {
	_currentDate = day_clock::local_day();
	_startTime = not_a_date_time;
	_endTime = not_a_date_time;
	_deadlineTime = not_a_date_time;
}

DatetimeParser::~DatetimeParser(void) {
}

void DatetimeParser::addTaskDatetime(Task* task, string& parameters) {
	try{
		setParameters(parameters);

		addDeadlineDatetime();
		addEndDatetime();
		addStartDatetime();

		combineDatetime();
		setFoundDatetime(task);
		parameters = getParameters();
	} catch(const out_of_range&) {
		throw;
	}
}

void DatetimeParser::addFilterDate(Command* command, string parameters) {
	try{
		setParameters(parameters);

		addEndWithIdentifier();
		addStartWithoutIdentifier();

		setFilterDatetime(command);
	} catch(const out_of_range&) {
		throw;
	}
}

void DatetimeParser::setParameters(string parameters) {
	_parameters = tokenizeString(parameters);
}

string DatetimeParser::getParameters() {
	return detokenizeVector(_parameters);
}

void DatetimeParser::combineDatetime(void) {
	combineDeadlineDatetime();
	combineStartDatetime();
	combineEndDatetime();
}

void DatetimeParser::setFoundDatetime(Task* task) {
	task->setTaskStartTime(_startDatetime);
	task->setTaskEndTime(_endDatetime);
	task->setTaskDeadline(_deadlineDatetime);
}

void DatetimeParser::setFilterDatetime(Command* command) {
	command->setStartDateFilter(_startDate);
	if(hasEndDate()) {
		command->setEndDateFilter(_endDate);
	} else {
		command->setEndDateFilter((date)pos_infin);
	}
}

void DatetimeParser::eraseWord(vector<string>::iterator& iter) {
	*iter = EMPTY_STRING;
}

void DatetimeParser::addDate(vector<string>::iterator iter, date& date, time_duration& time) {
	try {
		if(is3WordDate(iter)) {
			if(isATime(iter + THREE)) {
				time = parseTime(iter + THREE);
			}
		} else if(is2WordDate(iter)) {
			if(isATime(iter + TWO)) {
				time = parseTime(iter + TWO);
			}
		} else if(isATime(iter + ONE)) {
				time = parseTime(iter + ONE);
		}
		date = parseDate(iter);
	} catch(const out_of_range&) {
		throw;
	}
}

void DatetimeParser::addTime(vector<string>::iterator iter,  date& date, time_duration& time) {
	try {
		if(isADate(iter + ONE)) {
			date = parseDate(iter + ONE);
		}
		time = parseTime(iter);
	} catch(const out_of_range&) {
		throw;
	}
}

void DatetimeParser::addStartDatetime(void) {
	try {
		addStartWithIdentifier(); 
		if(!hasStartDate() || !hasStartTime()) {
			addStartWithoutIdentifier();
		}
	} catch(const out_of_range&) {
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
		for(auto iter = _parameters.begin(); iter != _parameters.end(); ++iter) {
			if(isStartIdentifier(*iter) && isATime(iter + ONE)) {
				addTime(iter + ONE, _startDate, _startTime);
				eraseWord(iter);
			} else if(isStartIdentifier(*iter) && isADate(iter + ONE)) {
				addDate(iter + ONE, _startDate, _startTime);
				eraseWord(iter);
			}
		}
	} catch(const out_of_range&) {
		throw;
	}
}

void DatetimeParser::addStartWithoutIdentifier(void) {
	try {
		for(auto iter = _parameters.begin(); iter != _parameters.end(); ++iter) {
			if(!hasStartTime() && isATime(iter)) {
				_startTime = parseTime(iter);
			} else if(!hasStartDate() && isADate(iter)) {
				_startDate = parseDate(iter);
			}
		}
	} catch(const out_of_range&) {
		throw;
	}
}

bool DatetimeParser::isStartIdentifier(string word) {
	for(auto iter = DATE_START.begin(); iter != DATE_START.end(); ++iter) {
		if(transformToLowercase(word) == *iter) {
			return true;
		}
	}
	return false;
}

void DatetimeParser::combineStartDatetime(void) {
	if(!hasStartTime()) {
		//Marker for allday tasks
		time_duration allDay = seconds(ONE);
		_startTime = allDay;
	} else if(!hasStartDate()) {
		_startDate = _currentDate;
	}
	ptime startDatetime(_startDate, _startTime);
	_startDatetime = startDatetime;
}

void DatetimeParser::addEndDatetime(void) {
	try {
		addEndWithIdentifier(); 
	} catch(const out_of_range&) {
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
		for(auto iter = _parameters.begin(); iter != _parameters.end(); ++iter) {
			if(isEndIdentifier(*iter) && isATime(iter + ONE)) {
				addTime(iter + ONE, _endDate, _endTime);
				eraseWord(iter);
			} else if(isEndIdentifier(*iter) && isADate(iter + ONE)) {
				addDate(iter + ONE, _endDate, _endTime);
				eraseWord(iter);
			}
		}
	} catch(const out_of_range&) {
		throw;
	}
}

bool DatetimeParser::isEndIdentifier(string word) {
	for(auto iter = DATE_END.begin(); iter != DATE_END.end(); ++iter) {
		if(transformToLowercase(word) == *iter) {
			return true;
		}
	}
	return false;
}

void DatetimeParser::combineEndDatetime(void) {
	if(!hasEndTime()) {
		//Marker for allday tasks
		time_duration allDay = seconds(ONE);
		_endTime = allDay;
	} else if(!hasEndDate()) {
		_endDate = _startDate;
	}
	ptime endDatetime(_endDate, _endTime);
	_endDatetime = endDatetime;
}

void DatetimeParser::addDeadlineDatetime(void) {
	try {
		addDeadlineWithIdentifier(); 
	} catch(const out_of_range&) {
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
		for(auto iter = _parameters.begin(); iter != _parameters.end(); ++iter) {
			if(isDeadlineIdentifier(*iter) && isATime(iter + ONE)) {
				addTime(iter + ONE, _deadlineDate, _deadlineTime);
				eraseWord(iter);
			} else if(isDeadlineIdentifier(*iter) && isADate(iter + ONE)) {
				addDate(iter + ONE, _deadlineDate, _deadlineTime);
				eraseWord(iter);
			}
		}
	} catch(const out_of_range&) {
		throw;
	}
}

bool DatetimeParser::isDeadlineIdentifier(string word) {
	for(auto iter = DATE_DEADLINE.begin(); iter != DATE_DEADLINE.end(); ++iter) {
		if(transformToLowercase(word) == *iter) {
			return true;
		}
	}
	return false;
}

void DatetimeParser::combineDeadlineDatetime(void) {
	if(!hasDeadlineTime()) {
		//Marker for allday tasks
		time_duration allDay = seconds(ONE);
		_deadlineTime = allDay;
	} else if(!hasDeadlineDate()) {
		_deadlineDate = _currentDate;
	}
	ptime deadlineDatetime(_deadlineDate, _deadlineTime);
	_deadlineDatetime = deadlineDatetime;
}

//Time Parsing Functions													   
bool DatetimeParser::isATime(vector<string>::iterator iter) {
	if(iter == _parameters.end()) {
		return false;
	}
	return (isAmPmTime(*iter) || isMilitaryTime(*iter));
}

time_duration DatetimeParser::parseTime(vector<string>::iterator iter) {
	assert(iter != _parameters.end());
	assert(isATime(iter));

	int intHours = ZERO;
	int intMinutes = ZERO;

	if(isAmPmTime(*iter)) {
		parseAmPmTime(*iter, intHours, intMinutes);
	} else {
		parseMilitaryTime(*iter, intHours, intMinutes);
	}

	time_duration timeOfDay = hours(intHours) + minutes(intMinutes);
	eraseWord(iter);
	return timeOfDay;
}

bool DatetimeParser::isMilitaryTime(string word) {
	removeTimeDelimiters(word);

	if(!isNumber(word) || word.length() != STRLEN_24H_TIME) {
		return false;
	}
	return is24HourTime(stoi(word));
}

bool DatetimeParser::isAmPmTime(string word) {
	removeTimeDelimiters(word);

	istringstream iss(word);
	int time;
	string AMPM;

	iss >> time >> AMPM;
	return (is12HourTime(time) && (isAm(AMPM) || isPm(AMPM)));
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
	removeTimeDelimiters(word);

	int time = stoi(word);
	hours = time / NUMLEN_3;
	minutes = time % NUMLEN_3;
}

void DatetimeParser::parseAmPmTime(string word, int& hours, int& minutes) {
	removeTimeDelimiters(word);

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

	if(isAm(AMPM) && hours == VALID_MAX_HOUR_12) {
		hours = ZERO;
	} else if(isPm(AMPM) && hours != VALID_MAX_HOUR_12) {
		hours += VALID_MAX_HOUR_12;
	}
}

void DatetimeParser::removeTimeDelimiters(string& word) {
	word = transformToLowercase(word);
	for(auto iter = TIME_DELIMITERS.begin(); iter != TIME_DELIMITERS.end(); ++iter) {
		word.erase(remove(word.begin(), word.end(), *iter), word.end());
	}
}

//Date Parsing Functions
bool DatetimeParser::isADate(vector<string>::iterator iter) {
	if(iter == _parameters.end()) {
		return false;
	}
	return (is3WordDate(iter) || is2WordDate(iter) || is1WordDate(iter));
}

date DatetimeParser::parseDate(vector<string>::iterator iter) {
	try{
		assert(iter != _parameters.end());
		assert(isADate(iter));
		if(is3WordDate(iter)) {
			return parse3WordDate(iter);
		} else if(is2WordDate(iter)) {
			return parse2WordDate(iter);
		} else {
			return parse1WordDate(iter);
		}
	} catch(const out_of_range&) {
		throw;
	}
}

bool DatetimeParser::is3WordDate(vector<string>::iterator iter) {
	assert(iter != _parameters.end());
	if((iter + ONE) == _parameters.end() || (iter + TWO) == _parameters.end()) {
		return false;
	}
	return DatetimeParser::isDayMonthYear(iter);
}

bool DatetimeParser::is2WordDate(vector<string>::iterator iter) {
	assert(iter != _parameters.end());
	if((iter + ONE) == _parameters.end()) {
		return false;
	}
	return (isDayMonth(iter) || isThisNextWeekday(iter));
}

bool DatetimeParser::is1WordDate(vector<string>::iterator iter) {
	assert(iter != _parameters.end());
	return (isToday(*iter)
		 || isTomorrow(*iter)
	 	 || isWeekday(*iter)
		 || isNumericalDate(*iter));
}

bool DatetimeParser::isDayMonthYear(vector<string>::iterator iter) {
	assert(iter != _parameters.end());
	assert((iter + ONE) != _parameters.end());
	assert((iter + TWO) != _parameters.end());
	if(!isNumber(*iter)) {
		return false;
	} else if(!isNumber(*(iter + TWO))) {
		return false;
	}
	int day = stoi(*iter);
	string month = *(iter + ONE);
	int year = stoi(*(iter + TWO));
	return (isDay(day) && isMonth(month) && isYear(year));
}

bool DatetimeParser::isDayMonth(vector<string>::iterator iter) {
	assert(iter != _parameters.end());
	assert((iter + ONE) != _parameters.end());
	if(!isNumber(*iter)) {
		return false;
	}
	int day = stoi(*iter);
	string month = *(iter + ONE);
	return (isDay(day) && isMonth(month));
}

bool DatetimeParser::isThisNextWeekday(vector<string>::iterator iter) {
	assert(iter != _parameters.end());
	assert((iter + ONE) != _parameters.end());
	string thisNext = *iter;
	string weekday = *(iter + ONE);
	return (isWeekday(weekday) 
		&& (isThis(thisNext) || isNext(thisNext)));
}

bool DatetimeParser::isToday(string date) {
	date = transformToLowercase(date);
	for(auto iter = DATE_TODAY.begin(); iter != DATE_TODAY.end(); ++iter) {
		if(date == *iter) {
			return true;
		}
	}
	return false;
}

bool DatetimeParser::isTomorrow(string date) {
	date = transformToLowercase(date);
	for(auto iter = DATE_TOMORROW.begin(); iter != DATE_TOMORROW.end(); ++iter) {
		if(date == *iter) {
			return true;
		}
	}
	return false;
}

bool DatetimeParser::isWeekday(string date) {
	date = transformToLowercase(date);
	for(int index = ZERO; index < VALID_MAX_WEEKDAY; ++index) {
		if(date == WEEKDAYS_LONG[index] || date == WEEKDAYS_SHORT[index]) {
			return true;
		}
	}
	return false;
}

bool DatetimeParser::isNumericalDate(string date) {
	removeDateDelimiters(date);

	if(!isNumber(date)) {
		return false;
	}
	return (isDDMM(date) 
		 || isDDMMYY(date) 
		 || isDDMMYYYY(date));
}

bool DatetimeParser::isDDMM(string date) {
	if(date.length() != STRLEN_DDMM) {
		return false;
	}
	int numDate = stoi(date);
	int day = numDate / NUMLEN_3;
	int month = numDate % NUMLEN_3;
	return (isDay(day) && isMonth(month));
}

bool DatetimeParser::isDDMMYY(string date) {
	if(date.length() != STRLEN_DDMMYY) {
		return false;
	}
	int numDate = stoi(date);
	int day = numDate / NUMLEN_5;
	int month = (numDate / NUMLEN_3) % NUMLEN_3;
	int year = (numDate % NUMLEN_3) + CURRENT_MILLENIUM;
	return (isDay(day) && isMonth(month) && isYear(year));
}

bool DatetimeParser::isDDMMYYYY(string date) {
	if(date.length() != STRLEN_DDMMYYYY) {
		return false;
	}
	int numDate = stoi(date);
	int day = numDate / NUMLEN_7;
	int month = (numDate / NUMLEN_5) % NUMLEN_3;
	int year = numDate % NUMLEN_5;
	return (isDay(day) && isMonth(month) && isYear(year));
}

bool DatetimeParser::isThis(string word) {
	return transformToLowercase(word) == DATE_THIS;
}

bool DatetimeParser::isNext(string word) {
	return transformToLowercase(word) == DATE_NEXT;
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
	month = transformToLowercase(month);
	for(int index = ZERO; index < VALID_MAX_MONTH; ++index) {
		if(month == MONTHS_LONG[index] || month == MONTHS_SHORT[index]) {
			return true;
		}
	}
	return false;
}

date DatetimeParser::parse3WordDate(vector<string>::iterator iter) {
	try {
		assert(iter != _parameters.end());
		assert((iter + ONE) != _parameters.end());
		assert((iter + TWO) != _parameters.end());

		date dateFound = parseDayMonthYear(iter);

		eraseWord(iter);
		eraseWord(iter + ONE);
		eraseWord(iter + TWO);
		return dateFound;
	} catch(const out_of_range&) {
		throw;
	}
}

date DatetimeParser::parse2WordDate(vector<string>::iterator iter) {
	try {
		assert(iter != _parameters.end());
		assert((iter + ONE) != _parameters.end());

		date dateFound;
		if(isDayMonth(iter)) {
			dateFound = parseDayMonth(iter);
		} else if(isThis(*iter)) {
			dateFound = parseThisWeekday(*(iter + ONE));
		} else {
			dateFound = parseNextWeekday(*(iter + ONE));
		}

		eraseWord(iter);
		eraseWord(iter + ONE);
		return dateFound;
	} catch(const out_of_range&) {
		throw;
	}
}

date DatetimeParser::parse1WordDate(vector<string>::iterator iter) {
	try {
		assert(iter != _parameters.end());

		date dateFound;
		if(isToday(*iter)) {
			dateFound = parseToday();
		} else if(isTomorrow(*iter)) {
			dateFound = parseTomorrow();
		} else if(isWeekday(*iter)) {
			dateFound = parseComingWeekday(*iter);
		} else {
			dateFound = parseNumericalDate(*iter);
		}

		eraseWord(iter);
		return dateFound;
	} catch(const out_of_range&) {
		throw;
	}
}

date DatetimeParser::parseDayMonthYear(vector<string>::iterator iter) {
	try {
		int day = parseDay(*iter);
		int month = parseMonth(*(iter + ONE));
		int year = parseYear(*(iter + TWO));
		date dateFound(year, month, day);
		return dateFound;
	} catch(const out_of_range&) {
		throw out_of_range(USERMESSAGE_DATETIME_NOT_PARSED);
	}
}

date DatetimeParser::parseDayMonth(vector<string>::iterator iter) {
	try {
		int day = parseDay(*iter);
		int month = parseMonth(*(iter + ONE));
		int year = _currentDate.year();
		date dateFound(year, month, day);
		return dateFound;
	} catch(const out_of_range&) {
		throw out_of_range(USERMESSAGE_DATETIME_NOT_PARSED);
	}
}

date DatetimeParser::parseThisWeekday(string weekday) {
	weekday = transformToLowercase(weekday);
	int _currentWeekday = (int)_currentDate.day_of_week();
		
	for(int index = ZERO; index < VALID_MAX_WEEKDAY; ++index) {
		if(weekday == WEEKDAYS_LONG[index] || weekday == WEEKDAYS_SHORT[index]) {
			if(index >= _currentWeekday) {
				return next_weekday(_currentDate, (greg_weekday)index);
			} else {
				date thisWeekday = next_weekday(_currentDate, (greg_weekday)index);
				date dateFound = thisWeekday - (date_duration)VALID_MAX_WEEKDAY;
				return dateFound;
			}
		}
	}
	date notFound;
	return notFound;
}

date DatetimeParser::parseNextWeekday(string weekday) {
	weekday = transformToLowercase(weekday);
	int _currentWeekday = (int)_currentDate.day_of_week();

	for(int index = ZERO; index < VALID_MAX_WEEKDAY; ++index) {
		if(weekday == WEEKDAYS_LONG[index] || weekday == WEEKDAYS_SHORT[index]) {
			if(index >= _currentWeekday) {
				date nextWeekday = next_weekday(_currentDate, (greg_weekday)index);
				date dateFound = nextWeekday + (date_duration)VALID_MAX_WEEKDAY;
				return dateFound;
			} else {
				return next_weekday(_currentDate, (greg_weekday)index);
			}
		}
	}
	date notFound;
	return notFound;
}

date DatetimeParser::parseToday(void) {
	return _currentDate;
}

date DatetimeParser::parseTomorrow(void) {
	return _currentDate + (date_duration)ONE;
}

date DatetimeParser::parseComingWeekday(string weekday) {
	weekday = transformToLowercase(weekday);
	int _currentWeekday = (int)_currentDate.day_of_week();

	for(int index = ZERO; index < VALID_MAX_WEEKDAY; ++index) {
		if(weekday == WEEKDAYS_LONG[index] || weekday == WEEKDAYS_SHORT[index]) {
			if(index == _currentWeekday) {
				return _currentDate + (date_duration)VALID_MAX_WEEKDAY;
			} else {
				return next_weekday(_currentDate, (greg_weekday)index);
			}
		}
	}
	date notFound;
	return notFound;
}

date DatetimeParser::parseNumericalDate(string date) {
	try {
		removeDateDelimiters(date);

		assert(isNumber(date));
		if(isDDMM(date)) {
			return parseDDMM(stoi(date));
		} else if(isDDMMYY(date)) {
			return parseDDMMYY(stoi(date));
		} else {
			return parseDDMMYYYY(stoi(date));
		}
	} catch(const out_of_range&) {
		throw;
	}
}

date DatetimeParser::parseDDMM(int intDate) {
	try {
		int day = intDate / NUMLEN_3;
		int month = intDate % NUMLEN_3;
		int year = _currentDate.year();
		date dateFound(year, month, day);
		return dateFound;
	} catch(const out_of_range&) {
		throw out_of_range(USERMESSAGE_DATETIME_NOT_PARSED);
	}
}

date DatetimeParser::parseDDMMYY(int intDate) {
	try {
		int day = intDate / NUMLEN_5;
		int month = (intDate / NUMLEN_3) % NUMLEN_3;
		int year = intDate % NUMLEN_3;
		if(year <= VALID_MAX_YEAR_YY) {
			year += CURRENT_MILLENIUM;
		}
		date dateFound(year, month, day);
		return dateFound;
	} catch(const out_of_range&) {
		throw out_of_range(USERMESSAGE_DATETIME_NOT_PARSED);
	}
}

date DatetimeParser::parseDDMMYYYY(int intDate) {
	try {
		int day = intDate / NUMLEN_7;
		int month = (intDate / NUMLEN_5) % NUMLEN_3;
		int year = intDate % NUMLEN_5;
		date dateFound(year, month, day);
		return dateFound;
	} catch(const out_of_range&) {
		throw out_of_range(USERMESSAGE_DATETIME_NOT_PARSED);
	}
}

int DatetimeParser::parseDay(string day) {
	assert(isNumber(day));
	return stoi(day);
}

int DatetimeParser::parseMonth(string month) {
	if(isNumber(month)) {
		return stoi(month);
	} else {
		month = transformToLowercase(month);
		for(int index = ZERO; index < VALID_MAX_MONTH; ++index) {
			if(month == MONTHS_LONG[index] || month == MONTHS_SHORT[index]) {
				return ++index;
			}
		}
	}
	return ZERO;
}

int DatetimeParser::parseYear(string year) {
	assert(isNumber(year));
	int numYear = stoi(year);
	if(numYear <= VALID_MAX_YEAR_YY) {
		numYear += CURRENT_MILLENIUM;
	}
	return numYear;
}

void DatetimeParser::removeDateDelimiters(string& word) {
	word = transformToLowercase(word);
	for(auto iter = DATE_DELIMITERS.begin(); iter != DATE_DELIMITERS.end(); ++iter) {
		word.erase(remove(word.begin(), word.end(), *iter), word.end());
	}
}