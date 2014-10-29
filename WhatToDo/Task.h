#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <vector>
#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian_calendar.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

//FixedTime start-end
//FixedTime onlystarttime
//FixedTime onlystartday
//Deadline floating
//Deadline withTime

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
		void setTaskIsDone();
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
		bool isTaskOverlapWith(Task myTask);
		bool isEarlierThan(Task myTask);


		//Enumeration
		enum TaskType{
			FIXEDTIME = 1, DEADLINE, FLOATING 
		};
};

#endif