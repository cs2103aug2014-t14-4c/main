#ifndef TASK_H
#define TASK_H

//1) isDone;
//2) LogicData;

#include <iostream>
#include <vector>
#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian_calendar.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class Task{
	private:
		ptime _taskStartDateTime;
		ptime _taskEndDateTime;
		ptime _taskDeadline;
		string _taskName;
		string _taskDetails; //Not used for now
		vector<string> _taskTags;
		int _taskIndex;
		int _taskType;
		bool _isDone;

	public:
		//Constructor
		Task();

		//Setters
		void setTaskStartTime(ptime dateTimeToSet);
		void setTaskEndTime(ptime dateTimeToSet);
		void setTaskDeadline(ptime dateTimeToSet);
		void setTaskName(string nameToSet);
		void setTaskDetails(string detailsToSet); // Not used for now
		void setTaskTags(vector<string> tagsToSet);
		void setTaskIndex(int indexToSet);
		void setTaskIsDone(bool doneStatusToSet = true);
		void setTaskIsNotDone();

		//Getters
		int getTaskType();
		int getTaskIndex();
		ptime getTaskStartTime();
		ptime getTaskEndTime();
		ptime getTaskDeadline();
		time_duration getTaskDuration();
		string getTaskName();
		string getTaskDetails();//Not used for now
		vector<string> getTaskTags();
		bool getTaskIsDone();
		


		//Operations
		bool hasStartTime();
		bool hasEndTime();
		bool hasDeadline();
		bool isTaskOverlapWith(Task myTask);
		bool isEarlierThan(Task myTask);
		bool isTaskSortedBefore(Task firstTask, Task secondTask);

		//Enumeration
		enum TaskType{
			 FLOATING = 1, DEADLINE_TIME, DEADLINE_ALLDAY, FIXED_TIME, FIXED_START, FIXED_ALLDAY
		};
};

#endif