#include "LogicParserDateTimeParser.h"

LogicParserDateTimeParser::LogicParserDateTimeParser(void) {
}

void LogicParserDateTimeParser::addTaskDateTime(Task* task, std::string& parameters) {
	std::istringstream iss(parameters);
	parameters = "";
	std::string currentWord;
	boost::posix_time::ptime startDateTime;
	boost::posix_time::ptime endDateTime;
	boost::posix_time::ptime deadlineDateTime;


	while(iss >> currentWord) {
		switch (LogicParserDateTimeParser::determineDateTimeType(currentWord)) {
		case LogicParserDateTimeParser::DateTimeType::START:
			iss.imbue(std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d%m%Y %H:%M")));
			iss >> startDateTime;
			break;
		case LogicParserDateTimeParser::DateTimeType::END:
			iss.imbue(std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d%m%Y %H:%M")));
			iss >> endDateTime;
			break;
		case LogicParserDateTimeParser::DateTimeType::DEADLINE:
			iss.imbue(std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d%m%Y %H:%M")));
			iss >> deadlineDateTime;
			break;
		case LogicParserDateTimeParser::DateTimeType::INVALID:
			parameters += currentWord + " ";
		}
	}

	task->setTaskStartTime(startDateTime);
	task->setTaskEndTime(endDateTime);
	task->setTaskDeadline(deadlineDateTime);
}

LogicParserDateTimeParser::DateTimeType LogicParserDateTimeParser::determineDateTimeType(std::string word) {
	LogicParserStringModifier stringMod;
	word = stringMod.transformToLowercase(word);

	if (word == IDENTIFIER_DATETIME_AT || word == IDENTIFIER_DATETIME_FROM || word == IDENTIFIER_DATETIME_ON) {
		return LogicParserDateTimeParser::DateTimeType::START;
	} else if (word == IDENTIFIER_DATETIME_TO) {
		return LogicParserDateTimeParser::DateTimeType::END;
	} else if (word == IDENTIFIER_DATETIME_BY || word == IDENTIFIER_DATETIME_DUE) {
		return LogicParserDateTimeParser::DateTimeType::DEADLINE;
	} else {
		return LogicParserDateTimeParser::DateTimeType::INVALID;
	}
}

