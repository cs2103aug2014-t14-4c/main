#include "LogicParserDatetimeParser.h"

LogicParserDatetimeParser::LogicParserDatetimeParser(void) {
	_currentDate = boost::gregorian::day_clock::local_day();
	_startTime = boost::gregorian::not_a_date_time;
	_endTime = boost::gregorian::not_a_date_time;
	_deadlineTime = boost::gregorian::not_a_date_time;
}

LogicParserDatetimeParser::~LogicParserDatetimeParser(void) {
}

std::string LogicParserDatetimeParser::addTaskDatetime(Command* command, Task* task, std::vector<std::string> parameters) {
	try{
		LogicParserDatetimeParser::setParameters(parameters);
		//LogicParserDatetimeParser::addDeadlineDatetime();	
		LogicParserDatetimeParser::addStartDatetime();
		if(LogicParserDatetimeParser::hasStartDatetime()) {
			LogicParserDatetimeParser::addEndDatetime();
		}
		LogicParserDatetimeParser::setFoundDatetime(task);
		return LogicParserDatetimeParser::convertParametersToString();
	}
	catch(const std::out_of_range&) {
		command->setParsedStatus(false);
		command->setUserMessage(USERMESSAGE_DATETIME_NOT_PARSED);
		return LogicParserDatetimeParser::convertParametersToString();
	}
	catch(...) {
		command->setParsedStatus(false);
		command->setUserMessage("Wtf happened");
		return LogicParserDatetimeParser::convertParametersToString();
	}
}

void LogicParserDatetimeParser::setParameters(std::vector<std::string> parameters) {
	_parameters = parameters;
}

std::string LogicParserDatetimeParser::convertParametersToString() {
	return LogicParserDatetimeParser::convertTokenVectorToString(_parameters);
}

void LogicParserDatetimeParser::setFoundDatetime(Task* task) {
	task->setTaskStartTime(_startDatetime);
	task->setTaskEndTime(_endDatetime);
	task->setTaskDeadline(_deadlineDatetime);
}

bool LogicParserDatetimeParser::hasStartDatetime(void) {
	return !_startDatetime.is_not_a_date_time();
}

bool LogicParserDatetimeParser::hasEndDatetime(void) {
	return !_endDatetime.is_not_a_date_time();
}

bool LogicParserDatetimeParser::hasDeadlineDatetime(void) {
	return !_deadlineDatetime.is_not_a_date_time();
}

void LogicParserDatetimeParser::eraseWord(std::vector<std::string>::iterator& iter) {
	iter = _parameters.erase(iter);
	if(iter != _parameters.begin()) {
		--iter;
	}
}

std::vector<std::string>::iterator LogicParserDatetimeParser::nextWord(std::vector<std::string>::iterator iter) {
	return ++iter;
}

bool LogicParserDatetimeParser::isATime(std::vector<std::string>::iterator iter) {
	try {
		if(iter == _parameters.end()) {
			throw std::invalid_argument("Vector out of range");
		}
		return (LogicParserDatetimeParser::isAmPmTime(*iter) 
			|| LogicParserDatetimeParser::is24HourTime(*iter));
	}
	catch(const std::invalid_argument) {
		return false;
	}
}

bool LogicParserDatetimeParser::isAmPmTime(std::string word) {
	word = LogicParserDatetimeParser::removeTimeDelimiters(word);
	std::istringstream iss(word);
	int time = 0;
	std::string AMPM;
	iss >> time >> AMPM;
	return (LogicParserDatetimeParser::is12HourTime(time) 
		&& (LogicParserDatetimeParser::isAm(AMPM) || LogicParserDatetimeParser::isPm(AMPM)));
}

bool LogicParserDatetimeParser::is12HourTime(int time) {
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

bool LogicParserDatetimeParser::isAm(std::string word) {
	return (word == TIME_AM);
}

bool LogicParserDatetimeParser::isPm(std::string word) {
	return (word == TIME_PM);
}

bool LogicParserDatetimeParser::is24HourTime(std::string word) {
	try {
		word = LogicParserDatetimeParser::removeTimeDelimiters(word);
		if(!LogicParserDatetimeParser::isNumber(word)) {
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

std::string LogicParserDatetimeParser::removeTimeDelimiters(std::string word) {
	word = LogicParserDatetimeParser::transformToLowercase(word);
	for(auto iter = TIME_DELIMITERS.begin(); iter != TIME_DELIMITERS.end(); ++iter) {
		word.erase(std::remove(word.begin(), word.end(), *iter), word.end());
	}
	return word;
}

boost::posix_time::time_duration LogicParserDatetimeParser::parseTime(std::vector<std::string>::iterator iter) {
	try {
		assert(iter != _parameters.end());
		assert(LogicParserDatetimeParser::isATime(iter));

		std::istringstream iss(LogicParserDatetimeParser::removeTimeDelimiters(*iter));
		int time;
		std::string AMPM;
		iss >> time >> AMPM;
		int hours = 0;
		int minutes = 0;

		if(LogicParserDatetimeParser::isAmPmTime(*iter)) {
			if(time < 100) {
				hours = time;
			} else {
				hours = time / 100;
				minutes = time % 100;
			}
			if(LogicParserDatetimeParser::isAm(AMPM) && hours == 12) {
				hours = 0;
			} else if(LogicParserDatetimeParser::isPm(AMPM) && hours != 12) {
				hours += 12;
			}
		} else if(LogicParserDatetimeParser::is24HourTime(*iter)) {
			hours = time / 100;
			minutes = time % 100;
		} else {
			throw std::invalid_argument("Unknown error");
		}

		LogicParserDatetimeParser::eraseWord(iter);

		boost::posix_time::time_duration timeOfDay = boost::posix_time::hours(hours) + boost::posix_time::minutes(minutes);
		return timeOfDay;
	}
	catch(std::invalid_argument) {
		boost::posix_time::time_duration timeOfDay = boost::posix_time::not_a_date_time;
		return timeOfDay;
	}
}

bool LogicParserDatetimeParser::isADate(std::vector<std::string>::iterator iter) {
	try {
		if(iter == _parameters.end()) {
			throw std::invalid_argument("Vector out of range");
		}
		return (LogicParserDatetimeParser::is3ParameterDate(iter)
			|| LogicParserDatetimeParser::is2ParameterDate(iter)
			|| LogicParserDatetimeParser::is1ParameterDate(iter));
	}
	catch(const std::invalid_argument) {
		return false;
	}
}

bool LogicParserDatetimeParser::is3ParameterDate(std::vector<std::string>::iterator iter) {
	try {
		if(iter == _parameters.end()
			|| LogicParserDatetimeParser::nextWord(iter) == _parameters.end()
			|| LogicParserDatetimeParser::nextWord(LogicParserDatetimeParser::nextWord(iter)) == _parameters.end()) {
			throw std::invalid_argument("Vector out of range");
		} else if(!LogicParserDatetimeParser::isNumber(*iter)) {
			throw std::invalid_argument("Not a numbered date");
		} else if(!LogicParserDatetimeParser::isNumber(*(LogicParserDatetimeParser::nextWord(LogicParserDatetimeParser::nextWord(iter))))) {
			throw std::invalid_argument("Not a numbered year");
		}
		int date = std::stoi(*iter);
		std::string month = *(LogicParserDatetimeParser::nextWord(iter));
		int year = std::stoi(*(LogicParserDatetimeParser::nextWord(LogicParserDatetimeParser::nextWord(iter))));

		return (LogicParserDatetimeParser::isDate(date) 
			&& LogicParserDatetimeParser::isMonth(month)
			&& LogicParserDatetimeParser::isYear(year));
	}
	catch(const std::invalid_argument) {
		return false;
	}
}

bool LogicParserDatetimeParser::is2ParameterDate(std::vector<std::string>::iterator iter) {
	try {
		if(iter == _parameters.end()
			|| LogicParserDatetimeParser::nextWord(iter) == _parameters.end()) {
			throw std::invalid_argument("Vector out of range");
		}
		return (LogicParserDatetimeParser::isDateAndMonth(iter) 
			|| LogicParserDatetimeParser::isThisNextWeek(iter));
	}
	catch(const std::invalid_argument) {
		return false;
	}
}

bool LogicParserDatetimeParser::isDateAndMonth(std::vector<std::string>::iterator iter) {
try {
		if(!LogicParserDatetimeParser::isNumber(*iter)) {
			throw std::invalid_argument("Not a numbered date");
		} 
		int date = std::stoi(*iter);
		std::string month = *(LogicParserDatetimeParser::nextWord(iter));

		return (LogicParserDatetimeParser::isDate(date) 
			&& LogicParserDatetimeParser::isMonth(month));
	}
	catch(const std::invalid_argument) {
		return false;
	}
}

bool LogicParserDatetimeParser::isThisNextWeek(std::vector<std::string>::iterator iter) {
	return ((LogicParserDatetimeParser::isThis(*iter) || LogicParserDatetimeParser::isNext(*iter))
		&& LogicParserDatetimeParser::isWeekday(*(LogicParserDatetimeParser::nextWord(iter))));
}

bool LogicParserDatetimeParser::is1ParameterDate(std::vector<std::string>::iterator iter) {
	try {
		if(iter == _parameters.end()) {
			throw std::invalid_argument("Vector out of range");
		}
		std::string date = LogicParserDatetimeParser::removeDateDelimiters(*iter);
		return (LogicParserDatetimeParser::isToday(date)
			|| LogicParserDatetimeParser::isTomorrow(date)
			|| LogicParserDatetimeParser::isNumericalDate(date));
	}
	catch(const std::invalid_argument) {
		return false;
	}
}

bool LogicParserDatetimeParser::isToday(std::string date) {
	for(auto iter = TODAY.begin(); iter != TODAY.end(); ++iter) {
		if(date == *iter) {
			return true;
		}
	}
	return false;
}

bool LogicParserDatetimeParser::isTomorrow(std::string date) {
	for(auto iter = TOMORROW.begin(); iter != TOMORROW.end(); ++iter) {
		if(date == *iter) {
			return true;
		}
	}
	return false;
}

bool LogicParserDatetimeParser::isNumericalDate(std::string date) {
	try {
		if(!LogicParserDatetimeParser::isNumber(date)) {
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
		return (LogicParserDatetimeParser::isDate(day)
			&& LogicParserDatetimeParser::isMonth(month)
			&& LogicParserDatetimeParser::isYear(year));
	}
	catch(const std::invalid_argument) {
		return false;
	}
}

bool LogicParserDatetimeParser::isDate(int date) {
	return (date >= 1 && date <= 31);
}

bool LogicParserDatetimeParser::isMonth(std::string month) {
	month = LogicParserDatetimeParser::transformToLowercase(month);
	for(int index = 0; index < 12; ++index) {
		if(month == MONTHS_LONG[index] || month == MONTHS_SHORT[index]) {
			return true;
		}
	}
	return false;
}

bool LogicParserDatetimeParser::isMonth(int month) {
	return (month >= 1 && month <= 12);
}

bool LogicParserDatetimeParser::isYear(int year) {
	return (year >= 0 && (year <= 99 || year >= 2000));
}

bool LogicParserDatetimeParser::isThis(std::string word) {
	return (LogicParserDatetimeParser::transformToLowercase(word) == IDENTIFIER_THIS);
}

bool LogicParserDatetimeParser::isNext(std::string word) {
	return (LogicParserDatetimeParser::transformToLowercase(word) == IDENTIFIER_NEXT);
}

bool LogicParserDatetimeParser::isWeekday(std::string word) {
	word = LogicParserDatetimeParser::transformToLowercase(word);
	for(int index = 0; index < 12; ++index) {
		if(word == WEEKDAYS_LONG[index] || word == WEEKDAYS_SHORT[index]) {
			return true;
		}
	}
	return false;
}

std::string LogicParserDatetimeParser::removeDateDelimiters(std::string word) {
	word = LogicParserDatetimeParser::transformToLowercase(word);
	for(auto iter = DATE_DELIMITERS.begin(); iter != DATE_DELIMITERS.end(); ++iter) {
		word.erase(std::remove(word.begin(), word.end(), *iter), word.end());
	}
	return word;
}

boost::gregorian::date LogicParserDatetimeParser::parseDate(std::vector<std::string>::iterator iter) {
	try {
		assert(iter != _parameters.end());
		assert(LogicParserDatetimeParser::isADate(iter));
		if(LogicParserDatetimeParser::is3ParameterDate(iter)) {
			return LogicParserDatetimeParser::parse3ParameterDate(iter);
		} else if(LogicParserDatetimeParser::is2ParameterDate(iter)) {
			return LogicParserDatetimeParser::parse2ParameterDate(iter);
		} else if(LogicParserDatetimeParser::is1ParameterDate(iter)) {
			return LogicParserDatetimeParser::parse1ParameterDate(iter);
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

boost::gregorian::date LogicParserDatetimeParser::parse3ParameterDate(std::vector<std::string>::iterator iter) {
	try {
		int day;
		int month;
		int year;
		day = std::stoi(*iter);
		month = LogicParserDatetimeParser::parseMonth(*(LogicParserDatetimeParser::nextWord(iter)));
		year = std::stoi(*LogicParserDatetimeParser::nextWord(LogicParserDatetimeParser::nextWord(iter)));
		if(year < 100) {
			year += 2000;
		}
		boost::gregorian::date dateFound(year, month, day);
		LogicParserDatetimeParser::eraseWord(LogicParserDatetimeParser::nextWord(LogicParserDatetimeParser::nextWord(iter)));
		LogicParserDatetimeParser::eraseWord(LogicParserDatetimeParser::nextWord(iter));
		LogicParserDatetimeParser::eraseWord(iter);
		return dateFound;
	}
	catch(...) {
		throw;
	}
}

boost::gregorian::date LogicParserDatetimeParser::parse2ParameterDate(std::vector<std::string>::iterator iter) {
	try {
		if(LogicParserDatetimeParser::isDateAndMonth(iter)){
			int day = std::stoi(*iter);
			int month = LogicParserDatetimeParser::parseMonth(*(LogicParserDatetimeParser::nextWord(iter)));;
			int year = _currentDate.year();

			boost::gregorian::date dateFound(year, month, day);
			LogicParserDatetimeParser::eraseWord(iter);
			LogicParserDatetimeParser::eraseWord(LogicParserDatetimeParser::nextWord(iter));
			return dateFound;
		} else if(LogicParserDatetimeParser::isThisNextWeek(iter)) {
			boost::gregorian::date dateFound;
			if(LogicParserDatetimeParser::isThis(*iter)) {
				dateFound = LogicParserDatetimeParser::findThisWeekday(*(LogicParserDatetimeParser::nextWord(iter)));
			} else {
				dateFound = LogicParserDatetimeParser::findNextWeekday(*(LogicParserDatetimeParser::nextWord(iter)));
			}
			LogicParserDatetimeParser::eraseWord(iter);
			LogicParserDatetimeParser::eraseWord(LogicParserDatetimeParser::nextWord(iter));
			return dateFound;
		} else {
			throw std::invalid_argument("WTF");
		}
	}
	catch(...) {
		throw;
	}
}

boost::gregorian::date LogicParserDatetimeParser::parse1ParameterDate(std::vector<std::string>::iterator iter) {
	try{
		std::string date = LogicParserDatetimeParser::removeDateDelimiters(*iter);
		LogicParserDatetimeParser::eraseWord(iter);

		if(LogicParserDatetimeParser::isToday(date)) {
			return _currentDate;
		} else if(LogicParserDatetimeParser::isTomorrow(date)) {
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

int LogicParserDatetimeParser::parseMonth(std::string month) {
	if(LogicParserDatetimeParser::isNumber(month)) {
		return std::stoi(month);
	} else {
		for(int i = 0; i < 12; ++i) {
			if(LogicParserDatetimeParser::transformToLowercase(month) == MONTHS_LONG[i]
			|| LogicParserDatetimeParser::transformToLowercase(month) == MONTHS_SHORT[i]) {
				return i+1;
			}
		}
	}
	return -1;
}

boost::gregorian::date LogicParserDatetimeParser::findThisWeekday(std::string day) {
	day = LogicParserDatetimeParser::transformToLowercase(day);
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

boost::gregorian::date LogicParserDatetimeParser::findNextWeekday(std::string day) {
	day = LogicParserDatetimeParser::transformToLowercase(day);
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

void LogicParserDatetimeParser::addStartDatetime(void) {
	try {
		for(auto iter = _parameters.begin(); iter != _parameters.end(); ++iter) {
			if(LogicParserDatetimeParser::isStartIdentifier(*iter)) {
				if(LogicParserDatetimeParser::addStartWithIdentifier(LogicParserDatetimeParser::nextWord(iter))) {
					LogicParserDatetimeParser::eraseWord(iter);
				}
			}
		} 
		if(_startDate.is_not_a_date() || _startTime.is_not_a_date_time()) {
			LogicParserDatetimeParser::addStartWithoutIdentifier();
		}
		LogicParserDatetimeParser::combineStartTimeDate();
	}
	catch(const std::out_of_range& e) {
		throw e;
	}
}

bool LogicParserDatetimeParser::isStartIdentifier(std::string word) {
	for(auto iter = IDENTIFIER_START.begin(); iter != IDENTIFIER_START.end(); ++iter) {
		if(LogicParserDatetimeParser::transformToLowercase(word) == *iter) {
			return true;
		}
	}
	return false;
}

bool LogicParserDatetimeParser::addStartWithIdentifier(std::vector<std::string>::iterator iter) {
	try {
		if(iter == _parameters.end()) {
			throw std::invalid_argument("Vector out of range");
		} 
		if(LogicParserDatetimeParser::isATime(iter)) {
			if(LogicParserDatetimeParser::isADate(LogicParserDatetimeParser::nextWord(iter))) {
				_startDate = LogicParserDatetimeParser::parseDate(LogicParserDatetimeParser::nextWord(iter));
			}
			_startTime = LogicParserDatetimeParser::parseTime(iter);
			return true;
		} else if(LogicParserDatetimeParser::isADate(iter)) {
			if(LogicParserDatetimeParser::isATime(LogicParserDatetimeParser::nextWord(iter))) {
				_startTime = LogicParserDatetimeParser::parseTime(LogicParserDatetimeParser::nextWord(iter));
			}
			_startDate = LogicParserDatetimeParser::parseDate(iter);
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

void LogicParserDatetimeParser::addStartWithoutIdentifier() {
	try {
		for(auto iter = _parameters.begin(); iter != _parameters.end(); ++iter) {
			if(_startTime.is_not_a_date_time() && LogicParserDatetimeParser::isATime(iter)) {
				_startTime = LogicParserDatetimeParser::parseTime(iter);
				iter = _parameters.begin();
			} else if(_startDate.is_not_a_date() && LogicParserDatetimeParser::isADate(iter)) {
				_startDate = LogicParserDatetimeParser::parseDate(iter);
				iter = _parameters.begin();
			}
		}
	}
	catch(const std::out_of_range& e) {
		throw e;
	}
}

void LogicParserDatetimeParser::combineStartTimeDate() {
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

void LogicParserDatetimeParser::addEndDatetime(void) {
	try {
		for(auto iter = _parameters.begin(); iter != _parameters.end(); ++iter) {
			if(LogicParserDatetimeParser::isEndIdentifier(*iter)) {
				if(LogicParserDatetimeParser::addEndWithIdentifier(LogicParserDatetimeParser::nextWord(iter))) {
					LogicParserDatetimeParser::eraseWord(iter);
				}
			}
		} 
		LogicParserDatetimeParser::combineEndTimeDate();
	}
	catch(const std::out_of_range& e) {
		throw e;
	}
}

bool LogicParserDatetimeParser::isEndIdentifier(std::string word) {
	for(auto iter = IDENTIFIER_END.begin(); iter != IDENTIFIER_END.end(); ++iter) {
		if(LogicParserDatetimeParser::transformToLowercase(word) == *iter) {
			return true;
		}
	}
	return false;
}

bool LogicParserDatetimeParser::addEndWithIdentifier(std::vector<std::string>::iterator iter) {
	try {
		if(iter == _parameters.end()) {
			throw std::invalid_argument("Vector out of range");
		} 
		if(LogicParserDatetimeParser::isATime(iter)) {
			if(LogicParserDatetimeParser::isADate(LogicParserDatetimeParser::nextWord(iter))) {
				_endDate = LogicParserDatetimeParser::parseDate(LogicParserDatetimeParser::nextWord(iter));
			}
			_endTime = LogicParserDatetimeParser::parseTime(iter);
			return true;
		} else if(LogicParserDatetimeParser::isADate(iter)) {
			if(LogicParserDatetimeParser::isATime(LogicParserDatetimeParser::nextWord(iter))) {
				_endTime = LogicParserDatetimeParser::parseTime(LogicParserDatetimeParser::nextWord(iter));
			}
			_endDate = LogicParserDatetimeParser::parseDate(iter);
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

void LogicParserDatetimeParser::combineEndTimeDate() {
	if(!_endDate.is_not_a_date() && !_endTime.is_not_a_date_time()) {
		boost::posix_time::ptime tempDatetime(_endDate, _endTime);
		_endDatetime = tempDatetime;
	} else if(_startTime.is_not_a_date_time()) {
		boost::posix_time::time_duration oneSecond(boost::posix_time::seconds(1));
		boost::posix_time::ptime tempDatetime(_endDate, oneSecond);
		_endDatetime = tempDatetime;
	} else if(_startDate.is_not_a_date()) {
		boost::posix_time::ptime tempDatetime(_startDate, _endTime);
		_endDatetime = tempDatetime;
	}
}