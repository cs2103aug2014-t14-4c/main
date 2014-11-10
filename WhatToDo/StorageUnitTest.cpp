//@author A0116278B

#include "stdafx.h"
#include "CppUnitTest.h"
#include "Task.cpp"
#include "StorageConverter.cpp"
#include "StorageDatabase.cpp"
#include "State.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace boost::posix_time;

namespace TestLibrary
{		
	TEST_CLASS(StorageConverterClassTest){
		private:
			string expectedString; 
			string testString; 
			vector<string> taskTags;
			Task taskObj;
			StorageConverter converterObj;
			
		public:
			TEST_METHOD(ptimeConversionFunctionTest){
				//normal Datetime
				ptime taskStartTime(date(2002,Jan,10), time_duration(1,2,3));
				string expectedDatetime = "20020110T010203";
				string startTimeTest = converterObj.convertTaskPtimeToString(taskStartTime);
				Assert::AreEqual(startTimeTest, expectedDatetime);
			}
			
			TEST_METHOD(ptimeConversionBoundaryTest){
				//boundary test case
				ptime testDatetime(not_a_date_time);
				string testDatetime2 = converterObj.convertTaskPtimeToString(testDatetime);
				string expectedDatetime = "not-a-date-time";
				Assert::AreEqual(testDatetime2, expectedDatetime);
			}
			TEST_METHOD(boolConvertionFunctionTest){
				expectedString = "1";
				testString = converterObj.convertTaskBoolToString(true); 
				Assert::AreEqual(testString, expectedString);
				
				expectedString = "0";
				testString = converterObj.convertTaskBoolToString(false);
				Assert::AreEqual(testString, expectedString); 	
			}

			//boundary case where NULL is entered 
			TEST_METHOD(boolConvertionBoundaryTest){
				expectedString = "0"; 
				testString = converterObj.convertTaskBoolToString(NULL);
				Assert::AreEqual(testString, expectedString); 
			}
			
			TEST_METHOD(taskTagConversionFunctionTest){
				//test convertion of task Tags
				taskTags.push_back("#cs1010");
				taskTags.push_back("#cs2103");
				expectedString = "#cs1010 #cs2103 ";
				testString = converterObj.convertTaskTagVectorToString(taskTags);
				Assert::AreEqual(testString, expectedString);
				taskTags.clear();
			}

			//test the case taskTag string is editted
			//that is user editted "#tag" to "tag"
			TEST_METHOD(taskTagConversionBoundaryTest){

				taskTags.push_back("cs1010");
				taskTags.push_back("cs2103");
				string expectedString = "cs1010 cs2103 ";
				testString = converterObj.convertTaskTagVectorToString(taskTags);
				Assert::AreEqual(expectedString, testString);
				taskTags.clear();
				taskTags = converterObj.convertTaskTagStringToVector(expectedString);
				vector<string> expectedTags; 
				expectedTags.push_back("#cs1010");
				expectedTags.push_back("#cs2103");
				Assert::AreEqual(expectedTags[0], taskTags[0]);
				Assert::AreEqual(expectedTags[1], taskTags[1]);
				taskTags.clear();
			}

			TEST_METHOD(convertStringToTaskIntegratedTest){
				vector<string> testInput;
				StorageConverter converterObj; 
				testInput.clear();

				testInput.push_back("Start Datetime: 20010101T010101");
				testInput.push_back("End Datetime: 20010102T010101");
				testInput.push_back("Task Deadline: 20010103T010101");
				testInput.push_back("Task Name: testName 2");
				testInput.push_back("Task Tags: #cs1010 #cs2103 ");
				testInput.push_back("Task isDone Status: 0");

				taskObj = converterObj.convertStringToTask(testInput);

				//checking if conversion is successful by validating individual attributes
				//startDatetime check
				ptime startDatetime = taskObj.getTaskStartTime();
				string startDatetimeString = converterObj.convertTaskPtimeToString(startDatetime);
				expectedString = "20010101T010101";
				Assert::AreEqual(expectedString, startDatetimeString);

				//endDatetime check
				ptime endDatetime = taskObj.getTaskEndTime();
				string endDatetimeString = converterObj.convertTaskPtimeToString(endDatetime);
				expectedString = "20010102T010101";
				Assert::AreEqual(expectedString, endDatetimeString);
				
				//deadLine check
				ptime deadLine = taskObj.getTaskDeadline();
				string deadLineString = converterObj.convertTaskPtimeToString(deadLine);
				expectedString = "20010103T010101";
				Assert::AreEqual(expectedString, deadLineString);
				
				//testName check
				string testName = taskObj.getTaskName();
				expectedString = "testName 2";
				Assert::AreEqual(expectedString, testName);

				//taskTags check
				vector<string> testTaskTags = taskObj.getTaskTags();
				string testTaskTagString = converterObj.convertTaskTagVectorToString(testTaskTags); 
				expectedString = "#cs1010 #cs2103 ";
				Assert::AreEqual(expectedString, testTaskTagString);

				//isDone check
				bool isDone = taskObj.getTaskIsDone();
				string isDoneString = converterObj.convertTaskBoolToString(isDone);
				expectedString = "0";
				Assert::AreEqual(expectedString, isDoneString);
			}
			
			TEST_METHOD(convertTaskToStringIntegratedTest){
				vector<string> testInput;
				testInput.clear();
				//contains all the boundary cases
				testInput.push_back("Start Datetime: not-a-date-time");
				testInput.push_back("End Datetime: 20010102T010101");
				testInput.push_back("Task Deadline: 20010102T010102");
				testInput.push_back("Task Name: testName 2");
				testInput.push_back("Task Tags: #cs1010 #cs2103 ");
				testInput.push_back("Task isDone Status: 1");

				Task taskObj2 = converterObj.convertStringToTask(testInput);
				ptime startDatetime = taskObj2.getTaskStartTime(); 
				string actualDatetime = converterObj.convertTaskPtimeToString(startDatetime);
				string expectedString = NOT_A_DATETIME; 
				Assert::AreEqual(actualDatetime, expectedString); 

				ptime endDatetime = taskObj2.getTaskEndTime();
				actualDatetime = converterObj.convertTaskPtimeToString(endDatetime); 
				expectedString = "20010102T010101"; 
				Assert::AreEqual(actualDatetime, expectedString);

				ptime deadLine = taskObj2.getTaskDeadline();
				actualDatetime = converterObj.convertTaskPtimeToString(deadLine);
				expectedString = "20010102T010102";
				Assert::AreEqual(actualDatetime, expectedString);

				vector<string> taskTags = taskObj2.getTaskTags(); 
				string actualTagString = converterObj.convertTaskTagVectorToString(taskTags);
				expectedString = "#cs1010 #cs2103 ";
				Assert::AreEqual(actualTagString, expectedString);

				string taskName = taskObj2.getTaskName(); 
				string actualName = converterObj.convertTaskNameToString(taskObj2);
				expectedString = "testName 2";
				Assert::AreEqual(actualName, expectedString); 

				bool isDoneStatus = taskObj2.getTaskIsDone(); 
				string actualIsDoneString = converterObj.convertTaskBoolToString(isDoneStatus);
				expectedString = "1";
				Assert::AreEqual(actualIsDoneString, expectedString); 
			}
	};

	TEST_CLASS(StorageDatabaseTest){
	private:
	public:

		TEST_METHOD(saveFileTest){
			
			vector<string> taskString; 
			StorageDatabase databaseObj; 
			databaseObj.setFileName("saveFileTest.txt");
			ofstream readFile2;
			readFile2.open("saveFileTest2.txt");
			readFile2 << "haha" << endl;
			vector<string> expectedString;
			expectedString.push_back("Start Datetime: 20010101T010101");
			expectedString.push_back("End Datetime: 20010102T010101");
			expectedString.push_back("Task Deadline: 20010103T010101");
			expectedString.push_back("Task Name: testName 2");
			expectedString.push_back("Task Tags: #cs1010 #cs2103 ");
			expectedString.push_back("Start Datetime: 20010101T010101");

			vector<vector<string>> actualContents;
			actualContents.push_back(expectedString);

			string myText; 
			int index;
			databaseObj.writeToDatabase(actualContents); 
			ifstream readFile("saveFileTest.txt"); 
			while(readFile.peek()!=EOF){
				for(index = START; index < NO_OF_ATTRIBUTES; index++){
					getline(readFile, myText);
				}
			}
			
		}

		TEST_METHOD(readFileTest){
			int index = 0; 

			string fileName = "testInput.txt"; 
			StorageDatabase databaseObj;
			databaseObj.setFileName(fileName); 
			vector<vector<string>> actualContents = databaseObj.readFromDatabase();
			vector<vector<string>> expectedContents;
			vector<string> taskString;
			taskString.push_back("Start Datetime: 20010101T010101");
			taskString.push_back("End Datetime: 20010102T010101");
			taskString.push_back("Task Deadline: 20010103T010101");
			taskString.push_back("Task Name: testName 2");
			taskString.push_back("Task Tags: #cs1010 #cs2103 ");
			taskString.push_back("Start Datetime: 20010101T010101");
			expectedContents.push_back(taskString);
			vector<vector<string>>::iterator vIte = actualContents.begin();
			vector<vector<string>>::iterator vIte2 = expectedContents.begin(); 
			while(vIte != actualContents.end() && vIte2!=expectedContents.end()){
				for(index = START, index < NO_OF_ATTRIBUTES; index++;){
					Assert::AreEqual((*vIte)[index], (*vIte2)[index]); 
				}
				vIte++;
				vIte2++;
			}
		}

	};
}