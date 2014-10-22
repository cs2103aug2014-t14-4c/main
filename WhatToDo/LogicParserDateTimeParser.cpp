#include "LogicParserDatetimeParser.h"

DatetimeParser::DatetimeParser(void) {
	_currentDate = boost::gregorian::day_clock::local_day();
	_startTime = boost::gregorian::not_a_date_time;
	_endTime = boost::gregorian::not_a_date_time;
	_deadlineTime = boost::gregorian::not_a_date_time;
}

DatetimeParser::~DatetimeParser(void) {
}

std::string DatetimeParser::addTaskDatetime(Command* command, Task* task, std::vector<std::string> parameters) {
	try{
		DatetimeParser::setParameters(parameters);
		DatetimeParser::addDeadlineDatetime();	
		DatetimeParser::addStartDatetime();
		if(DatetimeParser::hasStartDatetime()) {
			DatetimeParser::addEndDatetime();
		}
		DatetimeParser::setFoundDatetime(task);
		return DatetimeParser::convertParametersToString();
	}
	catch(const std::out_of_range&) {
		command->setParsedStatus(false);
		command->setUserMessage(USERMESSAGE_DATETIME_NOT_PARSED);
		return DatetimeParser::convertParametersToString();
	}
	catch(...) {
		command->setParsedStatus(false);
		command->setUserMessage("Wtf happened");
		return DatetimeParser::convertParametersToString();
	}
}

void DatetimeParser::setParameters(std::vector<std::string> parameters) {
	_parameters = parameters;
}

std::string DatetimeParser::convertParametersToString() {
	return DatetimeParser::detokenizeVector(_parameters);
}

void DatetimeParser::setFoundDatetime(Task* task) {
	task->setTaskStartTime(_startDatetime);
	task->setTaskEndTime(_endDatetime);
	task->setTaskDeadline(_deadlineDatetime);
}

bool DatetimeParser::hasStartDatetime(void) {
	return !_startDatetime.is_not_a_date_time();
}

bool DatetimeParser::hasEndDatetime(void) {
	return !_endDatetime.is_not_a_date_time();
}

bool DatetimeParser::hasDeadlineDatetime(void) {
	return !_deadlineDatetime.is_not_a_date_time();
}

void DatetimeParser::eraseWord(std::vector<std::string>::iterator& iter) {
	iter = _parameters.erase(iter);
	if(iter != _parameters.begin()) {
		--iter;
	}
}

std::vector<std::string>::iterator DatetimeParser::nextWord(std::vector<std::string>::iterator iter) {
	return ++iter;
}

bool DatetimeParser::isATime(std::vector<std::string>::iterator iter) {
	try {
		if(iter == _parameters.end()) {
			throw std::invalid_argument("Vector out of range");
		}
		return (DatetimeParser::isAmPmTime(*iter) 
			|| DatetimeParser::is24HourTime(*iter));
	}
	catch(const std::invalid_argument) {
		return false;
	}
}

bool DatetimeParser::isAmPmTime(std::string word) {
	word = DatetimeParser::removeTimeDelimiters(word);
	std::istringstream iss(word);
	int time = 0;
	std::string AMPM;
	iss >> time >> AMPM;
	return (DatetimeParser::is12HourTime(time) 
		&& (DatetimeParser::isAm(AMPM) || DatetimeParser::isPm(AMPM)));
}

bool DatetimeParser::is12HourTime(int time) {
	if(time < 100) {
		return (time > 0 && time < 13);
	} else if(time < 1300) {
		int hours = time / 100;
		int minutes = time % 100;
		return ((hours >= 1 && hours <= 12) && (minutes >= 0 && minutes <=59));
	} else {
		return false;
	}
}

bool DatetimeParser::isAm(std::string word) {
	return (word == IDENTIFIER_AM);
}

bool DatetimeParser::isPm(std::string word) {
	return (word == IDENTIFIER_PM);
}

bool DatetimeParser::is24HourTime(std::string word) {
	try {
		word = DatetimeParser::removeTimeDelimiters(word);
		if(!DatetimeParser::isNumber(word)) {
			throw std::invalid_argument("Not a number");
		} else if(word.length() != 4) {
			throw std::invalid_argument("Not a 24h time");
		}
		int time = std::stoi(word);
		int hours = time / 100;
		int minutes = time % 100;
		return ((hours >= 0 && hours <= 23) && (minutes >= 0 && minutes <=59));
	}
	catch(std::invalid_argument) {
		return false;
	}
}

std::string DatetimeParser::removeTimeDelimiters(std::string word) {
	word = DatetimeParser::transformToLowercase(word);
	for(auto iter = TIME_DELIMITERS.begin(); iter != TIME_DELIMITERS.end(); ++iter) {
		word.erase(std::remove(word.begin(), word.end(), *iter), word.end());
	}
	return word;
}

boost::posix_time::time_duration DatetimeParser::parseTime(std::vector<std::string>::iterator iter) {
	try {
		assert(iter != _parameters.end());
		assert(DatetimeParser::isATime(iter));

		std::istringstream iss(DatetimeParser::removeTimeDelimiters(*iter));
		int time;
		std::string AMPM;
		iss >> time >> AMPM;
		int hours = 0;
		int minutes = 0;

		if(DatetimeParser::isAmPmTime(*iter)) {
			if(time < 100) {
				hours = time;
			} else {
				hours = time / 100;
				minutes = time % 100;
			}
			if(DatetimeParser::isAm(AMPM) && hours == 12) {
				hours = 0;
			} else if(DatetimeParser::isPm(AMPM) && hours != 12) {
				hours += 12;
			}
		} else if(DatetimeParser::is24HourTime(*iter)) {
			hours = time / 100;
			minutes = time % 100;
		} else {
			throw std::invalid_argument("Unknown error");
		}

		DatetimeParser::eraseWord(iter);

		boost::posix_time::time_duration timeOfDay = boost::posix_time::hours(hours) + boost::posix_time::minutes(minutes);
		return timeOfDay;
	}
	catch(std::invalid_argument) {
		boost::posix_time::time_duration timeOfDay = boost::posix_time::not_a_date_time;
		return timeOfDay;
	}
}

bool DatetimeParser::isADate(std::vector<std::string>::iterator iter) {
	try {
		if(iter == _parameters.end()) {
			throw std::invalid_argument("Vector out of range");
		}
		return (DatetimeParser::is3ParameterDate(iter)
			|| DatetimeParser::is2ParameterDate(iter)
			|| DatetimeParser::is1ParameterDate(iter));
	}
	catch(const std::invalid_argument) {
		return false;
	}
}

bool DatetimeParser::is3ParameterDate(std::vector<std::string>::iterator iter) {
	try {
		if(iter == _parameters.end()
			|| DatetimeParser::nextWord(iter) == _parameters.end()
			|| DatetimeParser::nextWord(DatetimeParser::nextWord(iter)) == _parameters.end()) {
			throw std::invalid_argument("Vector out of range");
		} else if(!DatetimeParser::isNumber(*iter)) {
			throw std::invalid_argument("Not a numbered date");
		} else if(!DatetimeParser::isNumber(*(DatetimeParser::nextWord(DatetimeParser::nextWord(iter))))) {
			throw std::invalid_argument("Not a numbered year");
		}
		int date = std::stoi(*iter);
		std::string month = *(DatetimeParser::nextWord(iter));
		int year = std::stoi(*(DatetimeParser::nextWord(DatetimeParser::nextWord(iter))));

		return (DatetimeParser::isDate(date) 
			&& DatetimeParser::isMonth(month)
			&& DatetimeParser::isYear(year));
	}
	catch(const std::invalid_argument) {
		return false;
	}
}

bool DatetimeParser::is2ParameterDate(std::vector<std::string>::iterator iter) {
	try {
		if(iter == _parameters.end()
			|| DatetimeParser::nextWord(iter) == _parameters.end()) {
			throw std::invalid_argument("Vector out of range");
		}
		return (DatetimeParser::isDateAndMonth(iter) 
			|| DatetimeParser::isThisNextWeek(iter));
	}
	catch(const std::invalid_argument) {
		return false;
	}
}

bool DatetimeParser::isDateAndMonth(std::vector<std::string>::iterator iter) {
try {
		if(!DatetimeParser::isNumber(*iter)) {
			throw std::invalid_argument("Not a numbered date");
		} 
		int date = std::stoi(*iter);
		std::string month = *(DatetimeParser::nextWord(iter));

		return (DatetimeParser::isDate(date) 
			&& DatetimeParser::isMonth(month));
	}
	catch(const std::invalid_argument) {
		return false;
	}
}

bool DatetimeParser::isThisNextWeek(std::vector<std::string>::iterator iter) {
	return ((DatetimeParser::isThis(*iter) || DatetimeParser::isNext(*iter))
		&& DatetimeParser::isWeekday(*(DatetimeParser::nextWord(iter))));
}

bool DatetimeParser::is1ParameterDate(std::vector<std::string>::iterator iter) {
	try {
		if(iter == _parameters.end()) {
			throw std::invalid_argument("Vector out of range");
		}
		std::string date = DatetimeParser::removeDateDelimiters(*iter);
		return (DatetimeParser::isToday(date)
			|| DatetimeParser::isTomorrow(date)
			|| DatetimeParser::isNumericalDate(date));
	}
	catch(const std::invalid_argument) {
		return false;
	}
}

bool DatetimeParser::isToday(std::string date) {
	for(auto iter = IDENTIFIER_TODAY.begin(); iter != IDENTIFIER_TODAY.end(); ++iter) {
		if(date == *iter) {
			return true;
		}
	}
	return false;
}

bool DatetimeParser::isTomorrow(std::string date) {
	for(auto iter = IDENTIFIER_TOMORROW.begin(); iter != IDENTIFIER_TOMORROW.end(); ++iter) {
		if(date == *iter) {
			return true;
		}
	}
	return false;
}

bool DatetimeParser::isNumericalDate(std::string date) {
	try {
		if(!DatetimeParser::isNumber(date)) {
			throw std::invalid_argument("Not a number");
		}
		int numericalDate = std::stoi(date);
		int day = 0;
		int month = 0;
		int year = 0;
		if(date.length() == 4) {
			day = numericalDate / 100;
			month = numericalDate % 100;
		} else if(date.length() == 6) {
			day = numericalDate / 10000;
			month = (numericalDate / 100) % 100;
			year = 2000 + numericalDate % 100;
		} else if(date.length() == 8) {
			day = numericalDate / 1000000;
			month = (numericalDate / 10000) % 100;
			year = numericalDate % 100;
		} else {
			throw std::invalid_argument("Not accepted length of input");
		}
		return (DatetimeParser::isDate(day)
			&& DatetimeParser::isMonth(month)
			&& DatetimeParser::isYear(year));
	}
	catch(const std::invalid_argument) {
		return false;
	}
}

bool DatetimeParser::isDate(int date) {
	return (date >= 1 && date <= 31);
}

bool DatetimeParser::isMonth(std::string month) {
	month = DatetimeParser::transformToLowercase(month);
	for(int index = 0; index < 12; ++index) {
		if(month == MONTHS_LONG[index] || month == MONTHS_SHORT[index]) {
			return true;
		}
	}
	return false;
}

bool DatetimeParser::isMonth(int month) {
	return (month >= 1 && month <= 12);
}

bool DatetimeParser::isYear(int year) {
	return (year >= 0 && (year <= 99 || year >= 2000));
}

bool DatetimeParser::isThis(std::string word) {
	return (DatetimeParser::transformToLowercase(word) == IDENTIFIER_THIS);
}

bool DatetimeParser::isNext(std::string word) {
	return (DatetimeParser::transformToLowercase(word) == IDENTIFIER_NEXT);
}

bool DatetimeParser::isWeekday(std::string word) {
	word = DatetimeParser::transformToLowercase(word);
	for(int index = 0; index < 12; ++index) {
		if(word == WEEKDAYS_LONG[index] || word == WEEKDAYS_SHORT[index]) {
			return true;
		}
	}
	return false;
}

std::string DatetimeParser::removeDateDelimiters(std::string word) {
	word = DatetimeParser::transformToLowercase(word);
	for(auto iter = DATE_DELIMITERS.begin(); iter != DATE_DELIMITERS.end(); ++iter) {
		word.erase(std::remove(word.begin(), word.end(), *iter), word.end());
	}
	return word;
}

boost::gregorian::date DatetimeParser::parseDate(std::vector<std::string>::iterator iter) {
	try {
		assert(iter != _parameters.end());
		assert(DatetimeParser::isADate(iter));
		if(DatetimeParser::is3ParameterDate(iter)) {
			return DatetimeParser::parse3ParameterDate(iter);
		} else if(DatetimeParser::is2ParameterDate(iter)) {
			return DatetimeParser::parse2ParameterDate(iter);
		} else if(DatetimeParser::is1ParameterDate(iter)) {
			return DatetimeParser::parse1ParameterDate(iter);
		} else {
			throw std::invalid_argument("What happened here");
		}
	}
	catch(const std::out_of_range& e) {
		throw e;
	}
	catch(...) {
		boost::gregorian::date date;
		return date;
	}
}

boost::gregorian::date DatetimeParser::parse3ParameterDate(std::vector<std::string>::iterator iter) {
	try {
		int day;
		int month;
		int year;
		day = std::stoi(*iter);
		month = DatetimeParser::parseMonth(*(DatetimeParser::nextWord(iter)));
		year = std::stoi(*DatetimeParser::nextWord(DatetimeParser::nextWord(iter)));
		if(year < 100) {
			year += 2000;
		}
		boost::gregorian::date dateFound(year, month, day);
		DatetimeParser::eraseWord(DatetimeParser::nextWord(DatetimeParser::nextWord(iter)));
		DatetimeParser::eraseWord(DatetimeParser::nextWord(iter));
		DatetimeParser::eraseWord(iter);
		return dateFound;
	}
	catch(...) {
		throw;
	}
}

boost::gregorian::date DatetimeParser::parse2ParameterDate(std::vector<std::string>::iterator iter) {
	try {
		if(DatetimeParser::isDateAndMonth(iter)){
			int day = std::stoi(*iter);
			int month = DatetimeParser::parseMonth(*(DatetimeParser::nextWord(iter)));;
			int year = _currentDate.year();

			boost::gregorian::date dateFound(year, month, day);
			DatetimeParser::eraseWord(iter);
			DatetimeParser::eraseWord(DatetimeParser::nextWord(iter));
			return dateFound;
		} else if(DatetimeParser::isThisNextWeek(iter)) {
			boost::gregorian::date dateFound;
			if(DatetimeParser::isThis(*iter)) {
				dateFound = DatetimeParser::findThisWeekday(*(DatetimeParser::nextWord(iter)));
			} else {
				dateFound = DatetimeParser::findNextWeekday(*(DatetimeParser::nextWord(iter)));
			}
			DatetimeParser::eraseWord(iter);
			DatetimeParser::eraseWord(DatetimeParser::nextWord(iter));
			return dateFound;
		} else {
			throw std::invalid_argument("WTF");
		}
	}
	catch(...) {
		throw;
	}
}

boost::gregorian::date DatetimeParser::parse1ParameterDate(std::vector<std::string>::iterator iter) {
	try{
		std::string date = DatetimeParser::removeDateDelimiters(*iter);
		DatetimeParser::eraseWord(iter);

		if(DatetimeParser::isToday(date)) {
			return _currentDate;
		} else if(DatetimeParser::isTomorrow(date)) {
			boost::gregorian::date_duration oneDay(1);
			return _currentDate + oneDay;
		} else {
			int numericalDate = std::stoi(date);
			int day = 0;
			int month = 0;
			int year = 0;
			if(date.length() == 4) {
				day = numericalDate / 100;
				month = numericalDate % 100;
				year = _currentDate.year();
			} else if(date.length() == 6) {
				day = numericalDate / 10000;
				month = (numericalDate / 100) % 100;
				year = 2000 + numericalDate % 100;
			} else if(date.length() == 8) {
				day = numericalDate / 1000000;
				month = (numericalDate / 10000) % 100;
				year = numericalDate % 10000;
			}
			boost::gregorian::date dateFound(year, month, day);
			return dateFound;
		}
	}
	catch(...) {
		throw;
	}
}

int DatetimeParser::parseMonth(std::string month) {
	if(DatetimeParser::isNumber(month)) {
		return std::stoi(month);
	} else {
		for(int i = 0; i < 12; ++i) {
			if(DatetimeParser::transformToLowercase(month) == MONTHS_LONG[i]
			|| DatetimeParser::transformToLowercase(month) == MONTHS_SHORT[i]) {
				return i+1;
			}
		}
	}
	return -1;
}

boost::gregorian::date DatetimeParser::findThisWeekday(std::string day) {
	day = DatetimeParser::transformToLowercase(day);
	int _currentWeekday = (int)_currentDate.day_of_week();
	boost::gregorian::date_duration oneWeek(7);
	for(int index = 0; index < 7; ++index) {
		if(day == WEEKDAYS_LONG[index] || day == WEEKDAYS_SHORT[index]) {
			if(index >= _currentWeekday) {
				return boost::gregorian::next_weekday(_currentDate, (boost::gregorian::greg_weekday)index);
			} else {
				boost::gregorian::date thisWeekday = 
					boost::gregorian::next_weekday(_currentDate, (boost::gregorian::greg_weekday)index);
				boost::gregorian::date dateFound = thisWeekday - oneWeek;
				return dateFound;
			}
		}
	}
	boost::gregorian::date notFound;
	return notFound;
}

boost::gregorian::date DatetimeParser::findNextWeekday(std::string day) {
	day = DatetimeParser::transformToLowercase(day);
	int _currentWeekday = (int)_currentDate.day_of_week();
	boost::gregorian::date_duration oneWeek(7);
	for(int index = 0; index < 7; ++index) {
		if(day == WEEKDAYS_LONG[index] || day == WEEKDAYS_SHORT[index]) {
			if(index >= _currentWeekday) {
				boost::gregorian::date nextWeekday = 
					boost::gregorian::next_weekday(_currentDate, (boost::gregorian::greg_weekday)index);
				boost::gregorian::date dateFound = nextWeekday + oneWeek;
				return dateFound;
			} else {
				return boost::gregorian::next_weekday(_currentDate, (boost::gregorian::greg_weekday)index);
			}
		}
	}
	boost::gregorian::date notFound;
	return notFound;
}

void DatetimeParser::addStartDatetime(void) {
	try {
		for(auto iter = _parameters.begin(); iter != _parameters.end(); ++iter) {
			if(DatetimeParser::isStartIdentifier(*iter)) {
				if(DatetimeParser::addStartWithIdentifier(DatetimeParser::nextWord(iter))) {
					DatetimeParser::eraseWord(iter);
				}
			}
		} 
		if(_startDate.is_not_a_date() || _startTime.is_not_a_date_time()) {
			DatetimeParser::addStartWithoutIdentifier();
		}
		DatetimeParser::combineStartTimeDate();
	}
	catch(const std::out_of_range& e) {
		throw e;
	}
}

bool DatetimeParser::isStartIdentifier(std::string word) {
	for(auto iter = IDENTIFIER_START.begin(); iter != IDENTIFIER_START.end(); ++iter) {
		if(DatetimeParser::transformToLowercase(word) == *iter) {
			return true;
		}
	}
	return false;
}

bool DatetimeParser::addStartWithIdentifier(std::vector<std::string>::iterator iter) {
	try {
		if(iter == _parameters.end()) {
			throw std::invalid_argument("Vector out of range");
		} 
		if(DatetimeParser::isATime(iter)) {
			if(DatetimeParser::isADate(DatetimeParser::nextWord(iter))) {
				_startDate = DatetimeParser::parseDate(DatetimeParser::nextWord(iter));
			}
			_startTime = DatetimeParser::parseTime(iter);
			return true;
		} else if(DatetimeParser::isADate(iter)) {
			if(DatetimeParser::isATime(DatetimeParser::nextWord(iter))) {
				_startTime = DatetimeParser::parseTime(DatetimeParser::nextWord(iter));
			}
			_startDate = DatetimeParser::parseDate(iter);
			return true;
		}
		return false;
	}
	catch(const std::invalid_argument) {
		return false;
	}
	catch(const std::out_of_range& e) {
		throw e;
	}
}

void DatetimeParser::addStartWithoutIdentifier() {
	try {
		for(auto iter = _parameters.begin(); iter != _parameters.end(); ++iter) {
			if(_startTime.is_not_a_date_time() && DatetimeParser::isATime(iter)) {
				_startTime = DatetimeParser::parseTime(iter);
				iter = _parameters.begin();
			} else if(_startDate.is_not_a_date() && DatetimeParser::isADate(iter)) {
				_startDate = DatetimeParser::parseDate(iter);
				iter = _parameters.begin();
			}
		}
	}
	catch(const std::out_of_range& e) {
		throw e;
	}
}

void DatetimeParser::combineStartTimeDate() {
	if(!_startDate.is_not_a_date() && !_startTime.is_not_a_date_time()) {
		boost::posix_time::ptime tempDatetime(_startDate, _startTime);
		_startDatetime = tempDatetime;
	} else if(_startTime.is_not_a_date_time()) {
		boost::posix_time::time_duration oneSecond(boost::posix_time::seconds(1));
		boost::posix_time::ptime tempDatetime(_startDate, oneSecond);
		_startDatetime = tempDatetime;
	} else if(_startDate.is_not_a_date()) {
		boost::posix_time::ptime tempDatetime(_currentDate, _startTime);
		_startDatetime = tempDatetime;
	}
}

void DatetimeParser::addEndDatetime(void) {
	try {
		for(auto iter = _parameters.begin(); iter != _parameters.end(); ++iter) {
			if(DatetimeParser::isEndIdentifier(*iter)) {
				if(DatetimeParser::addEndWithIdentifier(DatetimeParser::nextWord(iter))) {
					DatetimeParser::eraseWord(iter);
				}
			}
		} 
		DatetimeParser::combineEndTimeDate();
	}
	catch(const std::out_of_range& e) {
		throw e;
	}
}

bool DatetimeParser::isEndIdentifier(std::string word) {
	for(auto iter = IDENTIFIER_END.begin(); iter != IDENTIFIER_END.end(); ++iter) {
		if(DatetimeParser::transformToLowercase(word) == *iter) {
			return true;
		}
	}
	return false;
}

bool DatetimeParser::addEndWithIdentifier(std::vector<std::string>::iterator iter) {
	try {
		if(iter == _parameters.end()) {
			throw std::invalid_argument("Vector out of range");
		} 
		if(DatetimeParser::isATime(iter)) {
			if(DatetimeParser::isADate(DatetimeParser::nextWord(iter))) {
				_endDate = DatetimeParser::parseDate(DatetimeParser::nextWord(iter));
			}
			_endTime = DatetimeParser::parseTime(iter);
			return true;
		} else if(DatetimeParser::isADate(iter)) {
			if(DatetimeParser::isATime(DatetimeParser::nextWord(iter))) {
				_endTime = DatetimeParser::parseTime(DatetimeParser::nextWord(iter));
			}
			_endDate = DatetimeParser::parseDate(iter);
			return true;
		}
		return false;
	}
	catch(const std::invalid_argument) {
		return false;
	}
	catch(const std::out_of_range& e) {
		throw e;
	}
}

void DatetimeParser::combineEndTimeDate() {
	if(!_endDate.is_not_a_date() && !_endTime.is_not_a_date_time()) {
		boost::posix_time::ptime tempDatetime(_endDate, _endTime);
		_endDatetime = tempDatetime;
	} else if(_endTime.is_not_a_date_time()) {
		boost::posix_time::time_duration oneSecond(boost::posix_time::seconds(1));
		boost::posix_time::ptime tempDatetime(_endDate, oneSecond);
		_endDatetime = tempDatetime;
	} else if(_endDate.is_not_a_date()) {
		boost::posix_time::ptime tempDatetime(_startDate, _endTime);
		_endDatetime = tempDatetime;
	}
}

void DatetimeParser::addDeadlineDatetime(void) {
	try {
		for(auto iter = _parameters.begin(); iter != _parameters.end(); ++iter) {
			if(DatetimeParser::isDeadlineIdentifier(*iter)) {
				if(DatetimeParser::addDeadlineWithIdentifier(DatetimeParser::nextWord(iter))) {
					DatetimeParser::eraseWord(iter);
				}
			}
		} 
		DatetimeParser::combineDeadlineTimeDate();
	}
	catch(const std::out_of_range& e) {
		throw e;
	}
}


bool DatetimeParser::isDeadlineIdentifier(std::string word) {
	for(auto iter = IDENTIFIER_DEADLINE.begin(); iter != IDENTIFIER_DEADLINE.end(); ++iter) {
		if(DatetimeParser::transformToLowercase(word) == *iter) {
			return true;
		}
	}
	return false;
}

bool DatetimeParser::addDeadlineWithIdentifier(std::vector<std::string>::iterator iter) {
	try {
		if(iter == _parameters.end()) {
			throw std::invalid_argument("Vector out of range");
		} 
		if(DatetimeParser::isATime(iter)) {
			if(DatetimeParser::isADate(DatetimeParser::nextWord(iter))) {
				_deadlineDate = DatetimeParser::parseDate(DatetimeParser::nextWord(iter));
			}
			_deadlineTime = DatetimeParser::parseTime(iter);
			return true;
		} else if(DatetimeParser::isADate(iter)) {
			if(DatetimeParser::isATime(DatetimeParser::nextWord(iter))) {
				_deadlineTime = DatetimeParser::parseTime(DatetimeParser::nextWord(iter));
			}
			_deadlineDate = DatetimeParser::parseDate(iter);
			return true;
		}
		return false;
	}
	catch(const std::invalid_argument) {
		return false;
	}
	catch(const std::out_of_range& e) {
		throw e;
	}
}

void DatetimeParser::combineDeadlineTimeDate() {
	if(!_deadlineDate.is_not_a_date() && !_deadlineTime.is_not_a_date_time()) {
		boost::posix_time::ptime tempDatetime(_deadlineDate, _deadlineTime);
		_deadlineDatetime = tempDatetime;
	} else if(_deadlineTime.is_not_a_date_time()) {
		boost::posix_time::time_duration oneSecond(boost::posix_time::seconds(1));
		boost::posix_time::ptime tempDatetime(_deadlineDate, oneSecond);
		_deadlineDatetime = tempDatetime;
	} else if(_deadlineDate.is_not_a_date()) {
		boost::posix_time::ptime tempDatetime(_currentDate, _deadlineTime);
		_deadlineDatetime = tempDatetime;
	}
}