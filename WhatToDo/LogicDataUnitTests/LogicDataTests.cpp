#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace testLogicDataComponent {		
	TEST_CLASS(TestTask) {
		public:
		
			TEST_METHOD(testInitTask) {
				Task myTask;

				//Check if TaskStartTime is initialized as "NULL"
				Assert::AreEqual(true, myTask.getTaskStartTime().is_not_a_date_time());

				//Check if TaskEndTime is initialized as "NULL"
				Assert::AreEqual(true, myTask.getTaskEndTime().is_not_a_date_time());
			
				//Check if TaskDeadline is initialized as "NULL"
				Assert::AreEqual(true, myTask.getTaskDeadline().is_not_a_date_time());
			}

			TEST_METHOD(testTaskType) {
				//Checking for FLOATING tasks
				Task floatTask;
				Assert::AreEqual(int(Task::TaskType::FLOATING), floatTask.getTaskType());

				//Checking for DEADLINE_TIME tasks
				Task deadlineTimeTask;
				deadlineTimeTask.setTaskDeadline(ptime (date(2014,Dec,10), time_duration(14,30,0)));
				Assert::AreEqual(int(Task::TaskType::DEADLINE_TIME), deadlineTimeTask.getTaskType());

				//Checking for DEADLINE_ALLDAY tasks
				Task deadlineAllDayTask;
				deadlineAllDayTask.setTaskDeadline(ptime (date(2014,Dec,10), time_duration(0,0,1)));
				Assert::AreEqual(int(Task::TaskType::DEADLINE_ALLDAY), deadlineAllDayTask.getTaskType());

				//Checking for FIXED_ALLDAY tasks
				Task fixedAllDayTask;
				fixedAllDayTask.setTaskStartTime(ptime (date(2014,Dec,10), time_duration(0,0,1)));
				Assert::AreEqual(int(Task::TaskType::FIXED_ALLDAY), fixedAllDayTask.getTaskType());
			
				//Checking for FIXED_DAY_TO_DAY tasks
				Task fixedDayToDayTask;
				fixedDayToDayTask.setTaskStartTime(ptime (date(2014,Dec,10), time_duration(0,0,1)));
				fixedDayToDayTask.setTaskEndTime(ptime (date(2014,Dec,15), time_duration(0,0,1)));
				Assert::AreEqual(int(Task::TaskType::FIXED_DAY_TO_DAY), fixedDayToDayTask.getTaskType());

				//Checking for FIXED_DAY_TO_TIME tasks
				Task fixedDayToTimeTask;
				fixedDayToTimeTask.setTaskStartTime(ptime (date(2014,Dec,10), time_duration(0,0,1)));
				fixedDayToTimeTask.setTaskEndTime(ptime (date(2014,Dec,15), time_duration(10,30,0)));
				Assert::AreEqual(int(Task::TaskType::FIXED_DAY_TO_TIME), fixedDayToTimeTask.getTaskType());

				//Checking for FIXED_START tasks
				Task fixedStartTask;
				fixedStartTask.setTaskStartTime(ptime (date(2014,Dec,10), time_duration(14,30,1)));
				Assert::AreEqual(int(Task::TaskType::FIXED_START), fixedStartTask.getTaskType());

				//Checking for FIXED_TIME_WITHIN_DAY tasks
				Task fixedTimeWithinDayTask;
				fixedTimeWithinDayTask.setTaskStartTime(ptime (date(2014,Dec,10), time_duration(14,30,0)));
				fixedTimeWithinDayTask.setTaskEndTime(ptime (date(2014,Dec,10), time_duration(16,30,0)));
				Assert::AreEqual(int(Task::TaskType::FIXED_TIME_WITHIN_DAY), fixedTimeWithinDayTask.getTaskType());

				//Checking for FIXED_TIME_ACROSS_DAY tasks
				Task fixedTimeAcrossDayTask;
				fixedTimeAcrossDayTask.setTaskStartTime(ptime (date(2014,Dec,10), time_duration(14,30,0)));
				fixedTimeAcrossDayTask.setTaskEndTime(ptime (date(2014,Dec,12), time_duration(16,30,0)));
				Assert::AreEqual(int(Task::TaskType::FIXED_TIME_ACROSS_DAY), fixedTimeAcrossDayTask.getTaskType());
			
				//Checking for FIXED_TIME_TO_DAY tasks
				Task fixedTimeToDayTask;
				fixedTimeToDayTask.setTaskStartTime(ptime (date(2014,Dec,10), time_duration(14,30,0)));
				fixedTimeToDayTask.setTaskEndTime(ptime (date(2014,Dec,12), time_duration(0,0,1)));
				Assert::AreEqual(int(Task::TaskType::FIXED_TIME_TO_DAY), fixedTimeToDayTask.getTaskType());
			}

			TEST_METHOD(testTaskIsEarlier) {
				Task firstTask;
				Task secondTask;

           		//case where first task is earlier than second task (test for 'positive' value segment)
							//   first task          [   
							//   second task             [
				firstTask.setTaskStartTime(ptime (date(2002,Jan,10), time_duration(1,2,3)));
				secondTask.setTaskStartTime(ptime (date(2002,Jan,11), time_duration(1,2,3)));
				Assert::AreEqual(true, firstTask.isEarlierThan(secondTask));

				//case where first task is later than second task (test for 'negative' value segment)
							//   first task                 [
							//   second task         [
				firstTask.setTaskStartTime(ptime (date(2002,Jan,13), time_duration(1,2,3)));
				secondTask.setTaskStartTime(ptime (date(2002,Jan,11), time_duration(1,2,3)));
				Assert::AreEqual(false, firstTask.isEarlierThan(secondTask));

				//case where first task starts the same as second task (test for 'boundary' value segment)
							//   first task          [
							//   second task         [
				firstTask.setTaskStartTime(ptime (date(2002,Jan,11), time_duration(1,2,3)));
				secondTask.setTaskStartTime(ptime (date(2002,Jan,11), time_duration(1,2,3)));
				Assert::AreEqual(false, firstTask.isEarlierThan(secondTask));
			}

			TEST_METHOD(testTaskIsOverlap) {
				Task firstTask;
				Task secondTask;
       
				//case where start time of second task is between start and end times of first task
				//   first task          [     ] 
				//   second task            [     ]
				firstTask.setTaskStartTime(ptime (date(2002,Jan,10), time_duration(1,2,3)));
				firstTask.setTaskEndTime(ptime (date(2002, Jan, 12), time_duration(1,2,3)));
				secondTask.setTaskStartTime(ptime (date(2002,Jan,11), time_duration(1,2,3)));
				secondTask.setTaskEndTime(ptime (date(2002, Jan, 13), time_duration(1,2,3)));
				Assert::AreEqual(true, firstTask.isTaskOverlapWith(secondTask));

				//case where end time of second task is between start and end times of first task
				//   first task          [     ]
							//   second task      [     ]
 				firstTask.setTaskStartTime(ptime (date(2002,Jan,10), time_duration(1,2,3)));
				firstTask.setTaskEndTime(ptime (date(2002, Jan, 12), time_duration(1,2,3)));
				secondTask.setTaskStartTime(ptime (date(2002,Jan,9), time_duration(1,2,3)));
				secondTask.setTaskEndTime(ptime (date(2002, Jan, 11), time_duration(1,2,3)));
				Assert::AreEqual(true, firstTask.isTaskOverlapWith(secondTask));

				//case where start time of second task equals the end time of the first task
							//   first task          [     ]
							//   second task               [     ]
				firstTask.setTaskStartTime(ptime (date(2002,Jan,10), time_duration(1,2,3)));
				firstTask.setTaskEndTime(ptime (date(2002, Jan, 12), time_duration(1,2,3)));
				secondTask.setTaskStartTime(ptime (date(2002,Jan,12), time_duration(1,2,3)));
				secondTask.setTaskEndTime(ptime (date(2002, Jan, 14), time_duration(1,2,3)));
				Assert::AreEqual(false, firstTask.isTaskOverlapWith(secondTask));

				//case where end time of second task equals the start time of the first task
							//   first task          [     ]
							//   second task   [     ]
				firstTask.setTaskStartTime(ptime (date(2002,Jan,10), time_duration(1,2,3)));
				firstTask.setTaskEndTime(ptime (date(2002, Jan, 12), time_duration(1,2,3)));
				secondTask.setTaskStartTime(ptime (date(2002,Jan,8), time_duration(1,2,3)));
				secondTask.setTaskEndTime(ptime (date(2002, Jan, 10), time_duration(1,2,3)));
				Assert::AreEqual(false, firstTask.isTaskOverlapWith(secondTask));

				//case where end time of second task equals the end time of the first task
							//    first task         [     ]      
							//    second task           [  ]
				firstTask.setTaskStartTime(ptime (date(2002,Jan,10), time_duration(1,2,3)));
				firstTask.setTaskEndTime(ptime (date(2002, Jan, 12), time_duration(1,2,3)));
				secondTask.setTaskStartTime(ptime (date(2002,Jan,11), time_duration(1,2,3)));
				secondTask.setTaskEndTime(ptime (date(2002, Jan, 12), time_duration(1,2,3)));
				Assert::AreEqual(true, firstTask.isTaskOverlapWith(secondTask));

 				//case where start time of second task equals the start time of the first task
							//    first task         [     ]      
							//    second task        [  ]
				firstTask.setTaskStartTime(ptime (date(2002,Jan,10), time_duration(1,2,3)));
				firstTask.setTaskEndTime(ptime (date(2002, Jan, 12), time_duration(1,2,3)));
				secondTask.setTaskStartTime(ptime (date(2002,Jan,10), time_duration(1,2,3)));
				secondTask.setTaskEndTime(ptime (date(2002, Jan, 11), time_duration(1,2,3)));
				Assert::AreEqual(true, firstTask.isTaskOverlapWith(secondTask));
			}

			TEST_METHOD(testTaskIsSortedBefore) {
				//FlOATING VS DEADLINE_TIME
				Task floatTask;

				Task deadlineTimeTask;
				deadlineTimeTask.setTaskDeadline(ptime (date(2014,Dec,10), time_duration(14,29,0)));

				Assert::AreEqual(true, floatTask.isTaskSortedBefore(floatTask, deadlineTimeTask));

				//DEADLINE_TIME VS FIXED_START , deadline is earlier than start time of fixed task
				Task fixedStartTask;
				fixedStartTask.setTaskStartTime(ptime (date(2014,Dec,10), time_duration(14,30,1)));

				Assert::AreEqual(false, fixedStartTask.isTaskSortedBefore(fixedStartTask, deadlineTimeTask));

				//FIXED_START VS FIXED_START - 2nd time starts later
				Task fixedStartTaskTwo;
				fixedStartTaskTwo.setTaskStartTime(ptime (date(2014,Dec,10), time_duration(14,40,1)));

				Assert::AreEqual(true, fixedStartTask.isTaskSortedBefore(fixedStartTask, fixedStartTaskTwo));

				//FIXED_START VS FIXED_START - same start times
				Task fixedStartTaskThree;
				fixedStartTaskThree.setTaskStartTime(ptime (date(2014,Dec,10), time_duration(14,40,1)));
				fixedStartTaskTwo.setTaskIndex(1);
				fixedStartTaskThree.setTaskIndex(10);

				Assert::AreEqual(true, fixedStartTaskTwo.getTaskIndex() < fixedStartTaskThree.getTaskIndex());
				Assert::AreEqual(true, fixedStartTaskTwo.isTaskSortedBefore(fixedStartTaskTwo, fixedStartTaskThree));		

				//FIXED_START VS FIXED_TIME_WITHIN_DAY - same start times, one fixed time, other fixed start(Higher precedence)
				Task fixedTimeWithinDayTask;
				fixedTimeWithinDayTask.setTaskStartTime(ptime (date(2014,Dec,10), time_duration(14,40,0)));		
				fixedTimeWithinDayTask.setTaskEndTime(ptime (date(2014,Dec,10), time_duration(15,40,0)));	

				Assert::AreEqual(true, fixedStartTaskThree.isTaskSortedBefore(fixedStartTaskThree, fixedTimeWithinDayTask));
			}
	};

	TEST_CLASS(TestState) {
		public:

			TEST_METHOD(testStateAdd) {
				State myState;
				vector<Task> listOfTasks,listOfStateTasks;
				Task temp;

				temp.setTaskName("Go and Fish");
				myState.addTask(temp);
				listOfTasks.push_back(temp);
				temp.setTaskName("I will go and run");
				myState.addTask(temp);
				listOfTasks.push_back(temp);
				temp.setTaskName("Go and Laugh");
				myState.addTask(temp);
				listOfTasks.push_back(temp);
				temp.setTaskName("Go and LOL");
				myState.addTask(temp);
				listOfTasks.push_back(temp);

				listOfStateTasks = myState.getAllTasks();

				for(int i=0; i< int(listOfTasks.size()); i++) {
					Assert::AreEqual(listOfTasks[i].getTaskName(), listOfStateTasks[i].getTaskName());
				}
			}

			TEST_METHOD(testStateDelete) {
				State myState;
				vector<Task> listOfTasks,listOfStateTasks;
				Task temp;

				//Adding Tasks
				temp.setTaskName("Go and Fish");
				myState.addTask(temp);
				listOfTasks.push_back(temp);
				temp.setTaskName("I will go and run");
				myState.addTask(temp);
				listOfTasks.push_back(temp);
				temp.setTaskName("Go and Laugh");
				myState.addTask(temp);
				listOfTasks.push_back(temp);
				temp.setTaskName("Go and LOL");
				myState.addTask(temp);
				listOfTasks.push_back(temp);
			
				//Deleting
				myState.deleteTask(1);
				listOfTasks.erase(listOfTasks.begin() + 1);

				//Checking
				listOfStateTasks = myState.getAllTasks();
				for(int i=0; i<int(listOfTasks.size());i++){
					Assert::AreEqual(listOfTasks[i].getTaskName(),listOfStateTasks[i].getTaskName());
				}

			}

			TEST_METHOD(testStateClear) {
				State myState;
				vector<Task> listOfTasks,listOfStateTasks;
				Task temp;

				//Adding Tasks
				temp.setTaskName("Go and Fish");
				myState.addTask(temp);
				listOfTasks.push_back(temp);
				temp.setTaskName("I will go and run");
				myState.addTask(temp);
				listOfTasks.push_back(temp);
				temp.setTaskName("Go and Laugh");
				myState.addTask(temp);
				listOfTasks.push_back(temp);
				temp.setTaskName("Go and LOL");
				myState.addTask(temp);
				listOfTasks.push_back(temp);

				//Clear Tasks
				myState.clearAllTasks();
				listOfStateTasks = myState.getAllTasks();
            
				//Checking
				Assert::AreEqual(0, int(listOfStateTasks.size()));
			}
	};

	TEST_CLASS(TestLogicData) {
		public:

			TEST_METHOD(testInitialisation) {
				LogicData myLogicData;

				Assert::AreEqual(LogicData::INITIAL_COMMAND_HISTORY_INDEX,
					myLogicData.getCurrentCommandHistoryIndex());
				Assert::AreEqual(LogicData::Status::ONLY_UNDONE, 
					myLogicData.getDoneFilter());
				Assert::AreEqual(LogicData::Type::ALL_TYPES,
					myLogicData.getTypeFilter());
				Assert::AreEqual(boost::gregorian::date(neg_infin),
					myLogicData.getStartDateFilter());
				Assert::AreEqual(boost::gregorian::date(pos_infin),
					myLogicData.getEndDateFilter());
			}

			TEST_METHOD(testDoneFilter) {
				LogicData myLogicData;

				myLogicData.setDoneFilter(LogicData::Status::ONLY_DONE);

				State myState;
				Task temp;
				vector<Task> expectedTasks, actualTasks;

				temp.setTaskName("Go and Fish");
				temp.setTaskIsDone();
				myState.addTask(temp);
				expectedTasks.push_back(temp);
				
				temp.setTaskName("I will go and run");
				temp.setTaskIsNotDone();
				myState.addTask(temp);

				temp.setTaskName("Go and Laugh");
				myState.addTask(temp);

				temp.setTaskName("Go and LOL");
				temp.setTaskIsDone();
				myState.addTask(temp);
				expectedTasks.push_back(temp);

				myLogicData.setViewState(myState);
				State myfilteredState;
				myfilteredState = myLogicData.filterTasks();

				actualTasks = myfilteredState.getAllTasks();

				for(int i=0; i< int(expectedTasks.size()); i++) {
					Assert::AreEqual (expectedTasks[i].getTaskName(),
						actualTasks[i].getTaskName());
				}
			}

			TEST_METHOD(testUndoneFilter) {
				LogicData myLogicData;

				myLogicData.setDoneFilter(LogicData::Status::ONLY_UNDONE);

				State myState;
				Task temp;
				vector<Task> expectedTasks, actualTasks;

				temp.setTaskName("Go and Fish");
				temp.setTaskIsDone();
				myState.addTask(temp);
				
				temp.setTaskName("I will go and run");
				temp.setTaskIsNotDone();
				myState.addTask(temp);
				expectedTasks.push_back(temp);

				temp.setTaskName("Go and Laugh");
				myState.addTask(temp);
				expectedTasks.push_back(temp);

				temp.setTaskName("Go and LOL");
				temp.setTaskIsDone();
				myState.addTask(temp);

				myLogicData.setViewState(myState);
				State myfilteredState;
				myfilteredState = myLogicData.filterTasks();

				actualTasks = myfilteredState.getAllTasks();

				for(int i=0; i< int(expectedTasks.size()); i++) {
					Assert::AreEqual (expectedTasks[i].getTaskName(),
						actualTasks[i].getTaskName());
				}
			}

			TEST_METHOD(testDeadlineFilter) {
				LogicData myLogicData;

				myLogicData.setTypeFilter(LogicData::Type::ONLY_DUE);

				State myState;
				vector<Task> expectedTasks, actualTasks;
				
				Task deadlineTask;
				deadlineTask.setTaskName("Go and Fish");
				deadlineTask.setTaskDeadline(ptime (date(2014,Dec,10), time_duration(14,30,0)));
				myState.addTask(deadlineTask);
				expectedTasks.push_back(deadlineTask);

				deadlineTask.setTaskName("I will go and run");
				deadlineTask.setTaskDeadline(ptime (date(2014,Dec,10), time_duration(16,30,0)));
				myState.addTask(deadlineTask);
				expectedTasks.push_back(deadlineTask);

				Task fixedTask;
				fixedTask.setTaskName("Go and Laugh");
				fixedTask.setTaskStartTime(ptime (date(2014,Dec,10), time_duration(14,30,0)));
				fixedTask.setTaskEndTime(ptime (date(2014,Dec,12), time_duration(16,30,0)));
				myState.addTask(fixedTask);

				fixedTask.setTaskName("Go and LOL");
				fixedTask.setTaskStartTime(ptime (date(2014,Dec,11), time_duration(14,30,0)));
				fixedTask.setTaskEndTime(ptime (date(2014,Dec,12), time_duration(16,30,0)));
				myState.addTask(fixedTask);

				myLogicData.setViewState(myState);
				State myfilteredState;
				myfilteredState = myLogicData.filterTasks();
				actualTasks = myfilteredState.getAllTasks();

				for(int i=0; i< int(expectedTasks.size()); i++) {
					Assert::AreEqual (expectedTasks[i].getTaskName(),
						actualTasks[i].getTaskName());
				}
			}	

			TEST_METHOD(testFixedFilter) {
				LogicData myLogicData;

				myLogicData.setTypeFilter(LogicData::Type::ONLY_FIXED);

				State myState;
				vector<Task> expectedTasks, actualTasks;
				
				Task deadlineTask;
				deadlineTask.setTaskName("Go and Fish");
				deadlineTask.setTaskDeadline(ptime (date(2014,Dec,10), time_duration(14,30,0)));
				myState.addTask(deadlineTask);

				deadlineTask.setTaskName("I will go and run");
				deadlineTask.setTaskDeadline(ptime (date(2014,Dec,10), time_duration(16,30,0)));
				myState.addTask(deadlineTask);

				Task fixedTask;
				fixedTask.setTaskName("Go and Laugh");
				fixedTask.setTaskStartTime(ptime (date(2014,Dec,10), time_duration(14,30,0)));
				fixedTask.setTaskEndTime(ptime (date(2014,Dec,12), time_duration(16,30,0)));
				myState.addTask(fixedTask);
				expectedTasks.push_back(deadlineTask);

				fixedTask.setTaskName("Go and LOL");
				fixedTask.setTaskStartTime(ptime (date(2014,Dec,11), time_duration(14,30,0)));
				fixedTask.setTaskEndTime(ptime (date(2014,Dec,12), time_duration(16,30,0)));
				myState.addTask(fixedTask);
				expectedTasks.push_back(deadlineTask);

				myLogicData.setViewState(myState);
				State myfilteredState;
				myfilteredState = myLogicData.filterTasks();
				actualTasks = myfilteredState.getAllTasks();

				for(int i=0; i< int(expectedTasks.size()); i++) {
					Assert::AreEqual (expectedTasks[i].getTaskName(),
						actualTasks[i].getTaskName());
				}
			}	
	};
}