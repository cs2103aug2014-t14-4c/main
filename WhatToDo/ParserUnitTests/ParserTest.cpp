//@author A0110655N
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

namespace ParserTest {		

	//Unit tests for the StringModifier class.
	TEST_CLASS(StringModifierTest) {
	public:
		StringModifier strMod;

		TEST_METHOD(StringModifier_isOneWOrd) {
			//One word with different characters
			Assert::AreEqual(true, strMod.isOneWord("one"));
			Assert::AreEqual(true, strMod.isOneWord(" onetwothreefour "));

			//More than one word
			Assert::AreEqual(false, strMod.isOneWord("two words"));
			Assert::AreEqual(false, strMod.isOneWord("  two     words"));

			//Empty string
			Assert::AreEqual(false, strMod.isOneWord(""));
		}

		TEST_METHOD(StringModifier_isNumber) {
			//Numbers
			Assert::AreEqual(true, strMod.isNumber("1"));
			Assert::AreEqual(true, strMod.isNumber(" 1  "));
			Assert::AreEqual(true, strMod.isNumber("1123432543363"));

			//Not numbers
			Assert::AreEqual(false, strMod.isNumber("-12"));
			Assert::AreEqual(false, strMod.isNumber("12ab"));
			Assert::AreEqual(false, strMod.isNumber("1 2 3 4 "));

			//Empty string
			Assert::AreEqual(false, strMod.isOneWord(""));
		}
		
		TEST_METHOD(StringModifier_getFirstWord) {
			string expected = "one";

			//Single word
			Assert::AreEqual(expected, strMod.getFirstWord("one"));

			//Multiple words
			Assert::AreEqual(expected, strMod.getFirstWord("one two three"));

			//Expected failing test
			Assert::AreNotEqual(expected, strMod.getFirstWord("two one"));
		}

		TEST_METHOD(StringModifier_getExceptFirstWord) {
			string expected = "two three";

			//Simple string
			Assert::AreEqual(expected, strMod.getExceptFirstWord("one two three"));
			
			//String with additional spaces
			Assert::AreEqual(expected, strMod.getExceptFirstWord(" onetwo  two three"));

			//Different substring
			Assert::AreNotEqual(expected, strMod.getExceptFirstWord("one two   three"));

			//Expected failing test
			Assert::AreNotEqual(expected, strMod.getExceptFirstWord("two three four"));
		}

		TEST_METHOD(StringModifier_trimWhitespace) {
			string expected1 = "one";
			string expected2 = "one two";

			//Single word, no whitespace
			Assert::AreEqual(expected1, strMod.trimWhiteSpace("one"));
			
			//Single word, with whitespace
			Assert::AreEqual(expected1, strMod.trimWhiteSpace("  one	"));

			//Multiple words, no whitespace
			Assert::AreEqual(expected2, strMod.trimWhiteSpace("one two"));

			//Multiple words, with whitespace
			Assert::AreEqual(expected2, strMod.trimWhiteSpace("	one two "));

			//Multiple words with whitespace in between
			Assert::AreNotEqual(expected2, strMod.trimWhiteSpace("one   two"));
		}

		TEST_METHOD(StringModifier_transformToLowercase) {
			string expected = "one two three";

			//Lowercase to lowercase
			Assert::AreEqual(expected, strMod.transformToLowercase("one two three"));

			//Uppercase to lowercase
			Assert::AreEqual(expected, strMod.transformToLowercase("ONE TwO thrEE"));
			
			//Different characters
			Assert::AreNotEqual(expected, strMod.transformToLowercase("one two thre3"));
		}

		TEST_METHOD(StringModifier_tokenizeString) {
			vector<string> actual = strMod.tokenizeString("	one  fine  day  ");
			size_t expectedSize = 3;
			string expected1 = "one";
			string expected2 = "fine";
			string expected3 = "day";
			Assert::AreEqual(expectedSize, actual.size());
			Assert::AreEqual(expected1, actual[0]);
			Assert::AreEqual(expected2, actual[1]);
			Assert::AreEqual(expected3, actual[2]);
		}
		
		TEST_METHOD(StringModifier_detokenizeVector) {
			vector<string> actual = strMod.tokenizeString("one fine day");
			string expected = "one fine day";
			Assert::AreEqual(expected, strMod.detokenizeVector(actual));
		}
	};

	//Unit tests for the DetailsParser class.
	TEST_CLASS(DetailsParserTest) {
	public:
		TEST_METHOD(Details_search) {
			DetailsParser details("APPLE   #Fruit banana   #eat");
			Command* command = new Command;
			details.searchForTask(command);

			string expectedSearch = "apple banana#fruit#eat";

			Assert::AreEqual(expectedSearch, command->getSearchKeyword());
		}

		TEST_METHOD(Details_markAsDone) {
			DetailsParser details("123");
			Command* command = new Command;
			details.markTaskAsDone(command);

			int expectedIndex = 123;
			bool expectedDone = true;

			Assert::AreEqual(expectedIndex, command->getTaskIndex());
			Assert::AreEqual(expectedDone, command->getIsDoneStatus());
		}

		TEST_METHOD(Details_markAsDone_Fail) {
			DetailsParser details("abc");
			Command* command = new Command;
			details.markTaskAsDone(command);

			Assert::AreEqual(false, command->getParsedStatus());
		}

		TEST_METHOD(Details_markAsUndone) {
			DetailsParser details("123");
			Command* command = new Command;
			details.markTaskAsUndone(command);

			int expectedIndex = 123;
			bool expectedDone = false;

			Assert::AreEqual(expectedIndex, command->getTaskIndex());
			Assert::AreEqual(expectedDone, command->getIsDoneStatus());
		}

		TEST_METHOD(Details_deleteExistingTask) {
			DetailsParser details("3243523");
			Command* command = new Command;
			details.deleteExistingTask(command);

			int expectedIndex = 3243523;

			Assert::AreEqual(expectedIndex, command->getTaskIndex());
		}

		TEST_METHOD(Details_deleteExistingTask_Fail) {
			DetailsParser details("-1");
			Command* command = new Command;
			details.deleteExistingTask(command);

			Assert::AreEqual(false, command->getParsedStatus());
		}

		TEST_METHOD(Details_addNewTask_OnlyName) {
			DetailsParser details("watch cs2103 webcast");
			Command* command = new Command;
			details.addNewTask(command);
			Task task = command->getCurrentTask();

			string expectedName = "watch cs2103 webcast";

			Assert::AreEqual(expectedName, task.getTaskName());
		}

		TEST_METHOD(Details_addNewTask_OnlyTag_Fail) {
			DetailsParser details("#cs2103 #school");
			Command* command = new Command;
			details.addNewTask(command);

			Assert::AreEqual(false, command->getParsedStatus());
		}

		TEST_METHOD(Details_addNewTask_NameAndTags) {
			DetailsParser details("Prepare for exam #cs2103 #school");
			Command* command = new Command;
			details.addNewTask(command);
			Task task = command->getCurrentTask();

			string expectedName = "Prepare for exam";
			size_t expectedTagsSize = 2;
			string expectedTag1 = "#cs2103";
			string expectedTag2 = "#school";

			Assert::AreEqual(expectedName, task.getTaskName());
			Assert::AreEqual(expectedTagsSize, task.getTaskTags().size());
			Assert::AreEqual(expectedTag1, task.getTaskTags()[0]);
			Assert::AreEqual(expectedTag2, task.getTaskTags()[1]);
		}

		TEST_METHOD(Details_editExistingTask) {
			DetailsParser details("13 watch webcast #cs2103");
			Command* command = new Command;
			details.editExistingTask(command);
			Task task = command->getCurrentTask();

			int expectedIndex = 13;
			string expectedName = "watch webcast";
			size_t expectedTagsSize = 1;
			string expectedTag = "#cs2103";

			Assert::AreEqual(expectedIndex, command->getTaskIndex());
			Assert::AreEqual(expectedName, task.getTaskName());
			Assert::AreEqual(expectedTagsSize, task.getTaskTags().size());
			Assert::AreEqual(expectedTag, task.getTaskTags()[0]);
		}

		TEST_METHOD(Details_editExistingTask_Fail) {
			DetailsParser details("watch webcast #cs2103");
			Command* command = new Command;
			details.editExistingTask(command);

			Assert::AreEqual(false, command->getParsedStatus());
		}

		TEST_METHOD(Details_filterInvalid) {
			DetailsParser details("this doesn't contain any filters");
			Command* command = new Command;
			details.filterExistingTasks(command);

			int expectedDone = Status::STATUS_NOT_SET;
			int expectedType = Type::TYPE_NOT_SET;
			date start;
			date end((date)pos_infin);

			Assert::AreEqual(expectedDone, command->getDoneFilter());
			Assert::AreEqual(expectedType, command->getTypeFilter());

			string expectedStart = to_iso_string(start);
			string actualStart = to_iso_string(command->getStartDateFilter());
			Assert::AreEqual(expectedStart, actualStart);

			string expectedEnd = to_iso_string(end);
			string actualEnd = to_iso_string(command->getEndDateFilter());
			Assert::AreEqual(expectedEnd, actualEnd);
		}

		TEST_METHOD(Details_filterDone) {
			DetailsParser details("done but this is extra stuff");
			Command* command = new Command;
			details.filterExistingTasks(command);

			int expectedDone = Status::ONLY_DONE;
			int expectedType = Type::TYPE_NOT_SET;
			date start;
			date end((date)pos_infin);

			Assert::AreEqual(expectedDone, command->getDoneFilter());
			Assert::AreEqual(expectedType, command->getTypeFilter());

			string expectedStart = to_iso_string(start);
			string actualStart = to_iso_string(command->getStartDateFilter());
			Assert::AreEqual(expectedStart, actualStart);

			string expectedEnd = to_iso_string(end);
			string actualEnd = to_iso_string(command->getEndDateFilter());
			Assert::AreEqual(expectedEnd, actualEnd);
		}

		TEST_METHOD(Details_filterStartDate) {
			DetailsParser details("25 dec");
			Command* command = new Command;
			details.filterExistingTasks(command);

			int expectedDone = Status::STATUS_NOT_SET;
			int expectedType = Type::TYPE_NOT_SET;
			date start(2014, 12, 25);
			date end((date)pos_infin);

			Assert::AreEqual(expectedDone, command->getDoneFilter());
			Assert::AreEqual(expectedType, command->getTypeFilter());

			string expectedStart = to_iso_string(start);
			string actualStart = to_iso_string(command->getStartDateFilter());
			Assert::AreEqual(expectedStart, actualStart);

			string expectedEnd = to_iso_string(end);
			string actualEnd = to_iso_string(command->getEndDateFilter());
			Assert::AreEqual(expectedEnd, actualEnd);
		}

		TEST_METHOD(Details_filterStartEndDate) {
			DetailsParser details("25 dec to 31 dec");
			Command* command = new Command;
			details.filterExistingTasks(command);

			int expectedDone = Status::STATUS_NOT_SET;
			int expectedType = Type::TYPE_NOT_SET;
			date start(2014, 12, 25);
			date end(2014, 12, 31);

			Assert::AreEqual(expectedDone, command->getDoneFilter());
			Assert::AreEqual(expectedType, command->getTypeFilter());

			string expectedStart = to_iso_string(start);
			string actualStart = to_iso_string(command->getStartDateFilter());
			Assert::AreEqual(expectedStart, actualStart);

			string expectedEnd = to_iso_string(end);
			string actualEnd = to_iso_string(command->getEndDateFilter());
			Assert::AreEqual(expectedEnd, actualEnd);
		}

		TEST_METHOD(Details_filterDeadline) {
			DetailsParser details("due");
			Command* command = new Command;
			details.filterExistingTasks(command);

			int expectedDone = Status::STATUS_NOT_SET;
			int expectedType = Type::ONLY_DUE;
			date start;
			date end((date)pos_infin);

			Assert::AreEqual(expectedDone, command->getDoneFilter());
			Assert::AreEqual(expectedType, command->getTypeFilter());

			string expectedStart = to_iso_string(start);
			string actualStart = to_iso_string(command->getStartDateFilter());
			Assert::AreEqual(expectedStart, actualStart);

			string expectedEnd = to_iso_string(end);
			string actualEnd = to_iso_string(command->getEndDateFilter());
			Assert::AreEqual(expectedEnd, actualEnd);
		}

		TEST_METHOD(Details_filterMultiple) {
			DetailsParser details("due 25 Dec nodone");
			Command* command = new Command;
			details.filterExistingTasks(command);

			int expectedDone = Status::DONE_BOTH;
			int expectedType = Type::ONLY_DUE;
			date start(2014, 12, 25);
			date end((date)pos_infin);

			Assert::AreEqual(expectedDone, command->getDoneFilter());
			Assert::AreEqual(expectedType, command->getTypeFilter());

			string expectedStart = to_iso_string(start);
			string actualStart = to_iso_string(command->getStartDateFilter());
			Assert::AreEqual(expectedStart, actualStart);

			string expectedEnd = to_iso_string(end);
			string actualEnd = to_iso_string(command->getEndDateFilter());
			Assert::AreEqual(expectedEnd, actualEnd);
		}

		TEST_METHOD(Details_filterClear) {
			DetailsParser details("CLEAR");
			Command* command = new Command;
			details.filterExistingTasks(command);

			int expectedDone = Status::DONE_BOTH;
			int expectedType = Type::ALL_TYPES;
			date start((date)neg_infin);
			date end((date)pos_infin);

			Assert::AreEqual(expectedDone, command->getDoneFilter());
			Assert::AreEqual(expectedType, command->getTypeFilter());

			string expectedStart = to_iso_string(start);
			string actualStart = to_iso_string(command->getStartDateFilter());
			Assert::AreEqual(expectedStart, actualStart);

			string expectedEnd = to_iso_string(end);
			string actualEnd = to_iso_string(command->getEndDateFilter());
			Assert::AreEqual(expectedEnd, actualEnd);
		}
	};

	//Unit tests for the DatetimeParser class.
	TEST_CLASS(DatetimeParserTest) {
	public:
		DatetimeParser datetime;

		TEST_METHOD(Datetime_noDate) {
			Task* task = new Task;
			string parameters = "meeting with cs2103 group";
			datetime.addTaskDatetime(task, parameters);

			string expectedParameters = "meeting with cs2103 group";
			Assert::AreEqual(expectedParameters, parameters);
		}

		TEST_METHOD(Datetime_3Date_dateMonthYearNoIdentifier) {
			Task* task = new Task;
			string parameters = "meeting 25 oct 14";
			datetime.addTaskDatetime(task, parameters);

			string expectedParameters = "meeting";
			Assert::AreEqual(expectedParameters, parameters);

			date startDate(2014, 10, 25);
			time_duration startTime(0, 0, 1);
			ptime start(startDate, startTime);

			string expectedStart = to_iso_string(start);
			string actualStart = to_iso_string(task->getTaskStartTime());
			Assert::AreEqual(expectedStart, actualStart);
		}

		TEST_METHOD(Datetime_3Date_dateMonthFullYearNoIdentifier) {
			Task* task = new Task;
			string parameters = "meeting 25 oct 2015";
			datetime.addTaskDatetime(task, parameters);

			string expectedParameters = "meeting";
			Assert::AreEqual(expectedParameters, parameters);

			date startDate(2015, 10, 25);
			time_duration startTime(0, 0, 1);
			ptime start(startDate, startTime);

			string expectedStart = to_iso_string(start);
			string actualStart = to_iso_string(task->getTaskStartTime());
			Assert::AreEqual(expectedStart, actualStart);
		}

		TEST_METHOD(Datetime_2Date_dateMonthNoIdentifier) {
			Task* task = new Task;
			string parameters = "meeting 25 oct at utown";
			datetime.addTaskDatetime(task, parameters);

			string expectedParameters = "meeting at utown";
			Assert::AreEqual(expectedParameters, parameters);

			date startDate(2014, 10, 25);
			time_duration startTime(0, 0, 1);
			ptime start(startDate, startTime);

			string expectedStart = to_iso_string(start);
			string actualStart = to_iso_string(task->getTaskStartTime());
			Assert::AreEqual(expectedStart, actualStart);
		}

		//Must be adjusted according to current date
		TEST_METHOD(Datetime_2Date_thisWeekdayNoIdentifier) {
			Task* task = new Task;
			string parameters = "cs2103 meeting this fri";
			datetime.addTaskDatetime(task, parameters);

			string expectedParameters = "cs2103 meeting";
			Assert::AreEqual(expectedParameters, parameters);

			date startDate(2014, 11, 14);
			time_duration startTime(0, 0, 1);
			ptime start(startDate, startTime);

			string expectedStart = to_iso_string(start);
			string actualStart = to_iso_string(task->getTaskStartTime());
			Assert::AreEqual(expectedStart, actualStart);
		}

		//Must be adjusted according to current date
		TEST_METHOD(Datetime_2Date_nextWeekdayNoIdentifier) {
			Task* task = new Task;
			string parameters = "next mon meeting for cs";
			datetime.addTaskDatetime(task, parameters);

			string expectedParameters = "meeting for cs";
			Assert::AreEqual(expectedParameters, parameters);

			date startDate(2014, 11, 17);
			time_duration startTime(0, 0, 1);
			ptime start(startDate, startTime);

			string expectedStart = to_iso_string(start);
			string actualStart = to_iso_string(task->getTaskStartTime());
			Assert::AreEqual(expectedStart, actualStart);
		}

		TEST_METHOD(Datetime_1Date_DDMMNoIdentifier) {
			Task* task = new Task;
			string parameters = "meeting 13/11";
			datetime.addTaskDatetime(task, parameters);

			date startDate(2014, 11, 13);
			time_duration startTime(0, 0, 1);
			ptime start(startDate, startTime);

			string expectedStart = to_iso_string(start);
			string actualStart = to_iso_string(task->getTaskStartTime());
			Assert::AreEqual(expectedStart, actualStart);
		}

		TEST_METHOD(Datetime_1Date_DDMMYYNoIdentifier) {
			Task* task = new Task;
			string parameters = "meeting 13-11-14";
			datetime.addTaskDatetime(task, parameters);

			date startDate(2014, 11, 13);
			time_duration startTime(0, 0, 1);
			ptime start(startDate, startTime);

			string expectedStart = to_iso_string(start);
			string actualStart = to_iso_string(task->getTaskStartTime());
			Assert::AreEqual(expectedStart, actualStart);
		}

		TEST_METHOD(Datetime_1Date_DDMMYYYYNoIdentifier) {
			Task* task = new Task;
			string parameters = "meeting 13.11.2014";
			datetime.addTaskDatetime(task, parameters);

			date startDate(2014, 11, 13);
			time_duration startTime(0, 0, 1);
			ptime start(startDate, startTime);

			string expectedStart = to_iso_string(start);
			string actualStart = to_iso_string(task->getTaskStartTime());
			Assert::AreEqual(expectedStart, actualStart);
		}

		TEST_METHOD(Datetime_1Date_TodayNoIdentifier) {
			Task* task = new Task;
			string parameters = "meeting today";
			datetime.addTaskDatetime(task, parameters);

			date startDate(day_clock::local_day());
			time_duration startTime(0, 0, 1);
			ptime start(startDate, startTime);

			string expectedStart = to_iso_string(start);
			string actualStart = to_iso_string(task->getTaskStartTime());
			Assert::AreEqual(expectedStart, actualStart);
		}

		TEST_METHOD(Datetime_1Date_TomorrowNoIdentifier) {
			Task* task = new Task;
			string parameters = "meeting tmr";
			datetime.addTaskDatetime(task, parameters);

			date startDate(day_clock::local_day());
			time_duration startTime(24, 0, 1);
			ptime start(startDate, startTime);

			string expectedStart = to_iso_string(start);
			string actualStart = to_iso_string(task->getTaskStartTime());
			Assert::AreEqual(expectedStart, actualStart);
		}

		//Must be adjusted according to current date
		TEST_METHOD(Datetime_1Date_WeekdayNoIdentifier) {
			Task* task = new Task;
			string parameters = "wed meeting";
			datetime.addTaskDatetime(task, parameters);

			date startDate(2014, 11, 12);
			time_duration startTime(0, 0, 1);
			ptime start(startDate, startTime);

			string expectedStart = to_iso_string(start);
			string actualStart = to_iso_string(task->getTaskStartTime());
			Assert::AreEqual(expectedStart, actualStart);
		}

		TEST_METHOD(Datetime_12HTime_NoIdentifier) {
			Task* task = new Task;
			string parameters = "meeting 10.00a.m. 04/01/2015";
			datetime.addTaskDatetime(task, parameters);

			date startDate(2015, 1, 4);
			time_duration startTime(10, 0, 0);
			ptime start(startDate, startTime);

			string expectedStart = to_iso_string(start);
			string actualStart = to_iso_string(task->getTaskStartTime());
			Assert::AreEqual(expectedStart, actualStart);
		}

		TEST_METHOD(Datetime_24HTime_NoIdentifier) {
			Task* task = new Task;
			string parameters = "meeting 23:59 25 dec";
			datetime.addTaskDatetime(task, parameters);

			date startDate(2014, 12, 25);
			time_duration startTime(23, 59, 0);
			ptime start(startDate, startTime);

			string expectedStart = to_iso_string(start);
			string actualStart = to_iso_string(task->getTaskStartTime());
			Assert::AreEqual(expectedStart, actualStart);
		}

		TEST_METHOD(Datetime_StartIdentifier) {
			Task* task = new Task;
			string parameters = "meeting on 23 dec at 12:30pm";
			datetime.addTaskDatetime(task, parameters);

			date startDate(2014, 12, 23);
			time_duration startTime(12, 30, 0);
			ptime start(startDate, startTime);
			ptime end;
			ptime deadline;

			string expectedStart = to_iso_string(start);
			string actualStart = to_iso_string(task->getTaskStartTime());
			Assert::AreEqual(expectedStart, actualStart);

			string expectedEnd = to_iso_string(end);
			string actualEnd = to_iso_string(task->getTaskEndTime());
			Assert::AreEqual(expectedEnd, actualEnd);

			string expectedDeadline = to_iso_string(deadline);
			string actualDeadline = to_iso_string(task->getTaskDeadline());
			Assert::AreEqual(expectedDeadline, actualDeadline);
		}

		TEST_METHOD(Datetime_EndIdentifier) {
			Task* task = new Task;
			string parameters = "meeting on 23 dec from 12:30pm - 1:30pm";
			datetime.addTaskDatetime(task, parameters);

			date startDate(2014, 12, 23);
			time_duration startTime(12, 30, 0);
			ptime start(startDate, startTime);

			date endDate(2014, 12, 23);
			time_duration endTime(13, 30, 0);
			ptime end(endDate, endTime);

			ptime deadline;

			string expectedStart = to_iso_string(start);
			string actualStart = to_iso_string(task->getTaskStartTime());
			Assert::AreEqual(expectedStart, actualStart);

			string expectedEnd = to_iso_string(end);
			string actualEnd = to_iso_string(task->getTaskEndTime());
			Assert::AreEqual(expectedEnd, actualEnd);

			string expectedDeadline = to_iso_string(deadline);
			string actualDeadline = to_iso_string(task->getTaskDeadline());
			Assert::AreEqual(expectedDeadline, actualDeadline);
		}

		TEST_METHOD(Datetime_DeadlineIdentifier) {
			Task* task = new Task;
			string parameters = "meeting by 25 dec 2014 3pm";
			datetime.addTaskDatetime(task, parameters);

			ptime start;
			ptime end;
			date deadlineDate(2014, 12, 25);
			time_duration deadlineTime(15, 0, 0);
			ptime deadline(deadlineDate, deadlineTime);

			string expectedStart = to_iso_string(start);
			string actualStart = to_iso_string(task->getTaskStartTime());
			Assert::AreEqual(expectedStart, actualStart);

			string expectedEnd = to_iso_string(end);
			string actualEnd = to_iso_string(task->getTaskEndTime());
			Assert::AreEqual(expectedEnd, actualEnd);

			string expectedDeadline = to_iso_string(deadline);
			string actualDeadline = to_iso_string(task->getTaskDeadline());
			Assert::AreEqual(expectedDeadline, actualDeadline);
		}

		TEST_METHOD(Datetime_StartEndIdentifier) {
			Task* task = new Task;
			string parameters = "meeting from 31 oct 2014 3pm to 31 oct 2014 4pm";
			datetime.addTaskDatetime(task, parameters);

			date startDate(2014, 10, 31);
			time_duration startTime(15, 0, 0);
			ptime start(startDate, startTime);
			date endDate(2014, 10, 31);
			time_duration endTime(16, 0, 0);
			ptime end(endDate, endTime);
			ptime deadline;

			string expectedStart = to_iso_string(start);
			string actualStart = to_iso_string(task->getTaskStartTime());
			Assert::AreEqual(expectedStart, actualStart);

			string expectedEnd = to_iso_string(end);
			string actualEnd = to_iso_string(task->getTaskEndTime());
			Assert::AreEqual(expectedEnd, actualEnd);

			string expectedDeadline = to_iso_string(deadline);
			string actualDeadline = to_iso_string(task->getTaskDeadline());
			Assert::AreEqual(expectedDeadline, actualDeadline);
		}
	};
	
	//Unit tests for the entire LogicParser component.
	TEST_CLASS(ParserTest) {
	public:
		LogicParser parser;
		Command* command;

		TEST_METHOD(Parser_addInvalidInput) {
			command = parser.getCommandFromUserInput("    ");
			Assert::AreEqual(command->getParsedStatus(), false);
			command = parser.getCommandFromUserInput("");
			Assert::AreEqual(command->getParsedStatus(), false);
		}

		TEST_METHOD(Parser_addValidInput) {
			command = parser.getCommandFromUserInput("meeting for cs2103 #cs2103");
			Task task = command->getCurrentTask();

			string expected = "meeting for cs2103";
			size_t expectedSize = 1;
			string expectedTag = "#cs2103";

			Assert::AreEqual(true, command->getParsedStatus());
			Assert::AreEqual(expected, task.getTaskName());
			Assert::AreEqual(expectedSize, task.getTaskTags().size());
			Assert::AreEqual(expectedTag, task.getTaskTags()[0]);
		}

		TEST_METHOD(Parser_addFixedTime) {
			command = parser.getCommandFromUserInput("meeting 9 dec 6am to 815pm #cs2103");
			Task task = command->getCurrentTask();

			string expectedName = "meeting";
			size_t expectedTagSize = 1;
			string expectedTag = "#cs2103";

			date startDate(2014, 12, 9);
			time_duration startTime(6, 0, 0);
			ptime start(startDate, startTime);

			date endDate(2014, 12, 9);
			time_duration endTime(20, 15, 0);
			ptime end(endDate, endTime);

			Assert::AreEqual(true, command->getParsedStatus());
			Assert::AreEqual(expectedName, task.getTaskName());
			Assert::AreEqual(expectedTagSize, task.getTaskTags().size());
			Assert::AreEqual(expectedTag, task.getTaskTags()[0]);


			string expectedStart = to_iso_string(start);
			string actualStart = to_iso_string(task.getTaskStartTime());
			Assert::AreEqual(expectedStart, actualStart);

			string expectedEnd = to_iso_string(end);
			string actualEnd = to_iso_string(task.getTaskEndTime());
			Assert::AreEqual(expectedEnd, actualEnd);
		}

		TEST_METHOD(Parser_addDeadline) {
			command = parser.getCommandFromUserInput("finish report by 11 dec "
													 "#cs2103 #important and "
													 "message group");
			Task task = command->getCurrentTask();

			string expectedName = "finish report and message group";
			size_t expectedTagSize = 2;
			string expectedTag1 = "#cs2103";
			string expectedTag2 = "#important";

			date deadlineDate(2014, 12, 11);
			time_duration deadlineTime(0, 0, 1);
			ptime deadline(deadlineDate, deadlineTime);

			Assert::AreEqual(true, command->getParsedStatus());
			Assert::AreEqual(expectedName, task.getTaskName());
			Assert::AreEqual(expectedTagSize, task.getTaskTags().size());
			Assert::AreEqual(expectedTag1, task.getTaskTags()[0]);
			Assert::AreEqual(expectedTag2, task.getTaskTags()[1]);

			string expectedDeadline = to_iso_string(deadline);
			string actualDeadline = to_iso_string(task.getTaskDeadline());
			Assert::AreEqual(expectedDeadline, actualDeadline);
		}

		TEST_METHOD(Parser_addlongInput) {
			string input = "This is a super"
				" duper long task name that I added just to test parser’s "
				"behaviour and it continues on and on and on and on and "
				"on and on and on and on and on and on and on and on and "
				"on and on and on and on and on and on and on and on and "
				"on and on and on and on and on and on and on and on and "
				"on and on and on and on and on and on and on and on and "
				"on and on and on and on and on and on and on and on and "
				"on and on and on and on and on and on and on and on and "
				"on and on and on and on and on and on and on and on and "
				"on and on and on and on and on and on and on and on and "
				"on and on and on and on and on and on and on and on and "
				"on and on and on and on and on and on and on and on and "
				"on and on and on and on and on and on and on and on and "
				"on and on and on and on and on and on and on and on and "
				"on and on and on and on and on and on and on and on";

			command = parser.getCommandFromUserInput(input);
			Task task = command->getCurrentTask();

			Assert::AreEqual(true, command->getParsedStatus());
			Assert::AreEqual(input, task.getTaskName());
		}

		TEST_METHOD(Parser_addNonexistentValidDate_Fail) {
			command = parser.getCommandFromUserInput("group meeting #ie2101 30 feb 2015");

			Assert::AreEqual(false, command->getParsedStatus());
		}

		TEST_METHOD(Parser_addNonexistentInvalidDate) {
			command = parser.getCommandFromUserInput("group meeting #ie2101 32 feb 2015");
			Task task = command->getCurrentTask();

			//2015 is recognised as a 24hour time
			string expected = "group meeting 32 feb";

			Assert::AreEqual(true, command->getParsedStatus());
			Assert::AreEqual(expected, task.getTaskName());
		}

		TEST_METHOD(Parser_addOnlyTag_Fail) {
			command = parser.getCommandFromUserInput("#ie2101");

			Assert::AreEqual(false, command->getParsedStatus());
		}
	
		TEST_METHOD(Parser_addOnlyDate_Fail) {
			command = parser.getCommandFromUserInput("25 feb 2014");

			Assert::AreEqual(false, command->getParsedStatus());
		}

		TEST_METHOD(Parser_done) {
			command = parser.getCommandFromUserInput("/done 1");

			int expectedIndex = 1;

			Assert::AreEqual(true, command->getParsedStatus());
			Assert::AreEqual(expectedIndex, command->getTaskIndex());
		}

		TEST_METHOD(Parser_undone) {
			command = parser.getCommandFromUserInput("/undone 146");

			int expectedIndex = 146;

			Assert::AreEqual(true, command->getParsedStatus());
			Assert::AreEqual(expectedIndex, command->getTaskIndex());
		}

		TEST_METHOD(Parser_undone_Fail) {
			command = parser.getCommandFromUserInput("/undone 1 123");

			Assert::AreEqual(false, command->getParsedStatus());
		}

		TEST_METHOD(Parser_delete) {
			command = parser.getCommandFromUserInput("/delete 213");

			int expectedIndex = 213;

			Assert::AreEqual(true, command->getParsedStatus());
			Assert::AreEqual(expectedIndex, command->getTaskIndex());
		}

		TEST_METHOD(Parser_delete_Fail) {
			command = parser.getCommandFromUserInput("/done abc");

			Assert::AreEqual(false, command->getParsedStatus());
		}

		TEST_METHOD(Parser_filter) {
			command = parser.getCommandFromUserInput("/filter clear");

			int expectedDone = Status::DONE_BOTH;
			int expectedType = Type::ALL_TYPES;
			date start(neg_infin);
			date end(pos_infin);

			Assert::AreEqual(true, command->getParsedStatus());
			Assert::AreEqual(expectedDone, command->getDoneFilter());
			Assert::AreEqual(expectedType, command->getTypeFilter());

			string expectedStart = to_iso_string(start);
			string actualStart = to_iso_string(command->getStartDateFilter());
			Assert::AreEqual(expectedStart, actualStart);

			string expectedEnd = to_iso_string(end);
			string actualEnd = to_iso_string(command->getEndDateFilter());
			Assert::AreEqual(expectedEnd, actualEnd);
		}

		TEST_METHOD(Parser_filterNoValidFilterApplied) {
			command = parser.getCommandFromUserInput("/filter all stuff");

			int expectedDone = Status::STATUS_NOT_SET;
			int expectedType = Type::TYPE_NOT_SET;
			date start;
			date end(pos_infin);

			Assert::AreEqual(true, command->getParsedStatus());
			Assert::AreEqual(expectedDone, command->getDoneFilter());
			Assert::AreEqual(expectedType, command->getTypeFilter());

			string expectedStart = to_iso_string(start);
			string actualStart = to_iso_string(command->getStartDateFilter());
			Assert::AreEqual(expectedStart, actualStart);

			string expectedEnd = to_iso_string(end);
			string actualEnd = to_iso_string(command->getEndDateFilter());
			Assert::AreEqual(expectedEnd, actualEnd);
		}

		TEST_METHOD(Parser_edit) {
			command = parser.getCommandFromUserInput("/edit 4 meeting 9 dec 615pm");
			Task task = command->getCurrentTask();

			string expectedName = "meeting";
			int expectedIndex = 4;
			string expectedTag = "#cs2103";

			date startDate(2014, 12, 9);
			time_duration startTime(18, 15, 0);
			ptime start(startDate, startTime);

			Assert::AreEqual(true, command->getParsedStatus());
			Assert::AreEqual(expectedName, task.getTaskName());
			Assert::AreEqual(expectedIndex, command->getTaskIndex());

			string expectedStart = to_iso_string(start);
			string actualStart = to_iso_string(task.getTaskStartTime());
			Assert::AreEqual(expectedStart, actualStart);
		}

		TEST_METHOD(Parser_editNoIndex_Fail) {
			command = parser.getCommandFromUserInput("/edit meeting 9 dec 615pm");

			Assert::AreEqual(false, command->getParsedStatus());
		}

		TEST_METHOD(Parser_editNoTask_Fail) {
			command = parser.getCommandFromUserInput("/edit 9");

			Assert::AreEqual(false, command->getParsedStatus());
		}

		TEST_METHOD(Parser_undo) {
			command = parser.getCommandFromUserInput("/undo");

			Assert::AreEqual(true, command->getParsedStatus());
		}

		TEST_METHOD(Parser_undo_Fail) {
			command = parser.getCommandFromUserInput("/undo something");

			Assert::AreEqual(false, command->getParsedStatus());
		}

		TEST_METHOD(Parser_redo) {
			command = parser.getCommandFromUserInput("/redo");

			Assert::AreEqual(true, command->getParsedStatus());
		}

		TEST_METHOD(Parser_redo_Fail) {
			command = parser.getCommandFromUserInput("/redo blah");

			Assert::AreEqual(false, command->getParsedStatus());
		}

		TEST_METHOD(Parser_search) {
			command = parser.getCommandFromUserInput("/search meeting");

			string expected = "meeting";

			Assert::AreEqual(true, command->getParsedStatus());
			Assert::AreEqual(expected, command->getSearchKeyword());
		}
	};
}