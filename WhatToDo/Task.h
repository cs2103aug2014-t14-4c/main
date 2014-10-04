#ifndef TASK_H
#define TASK_H

// TODO 1) Add Boost
// 2) State
// 3) Figure out how to check overlap.

#include <iostream>
#include <vector>
#include <string>
#include <boost/date_time/gregorian_calendar.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace std;
using namespace boost::posix_time;

class Task{
	private:
		ptime _taskStartDateTime;
		ptime _taskEndDateTime;
		ptime _taskDeadline;
		time_duration _taskDuration;
		string _taskName;
		string _taskDetails; //Not used for now
		vector<string> _taskTags;
		int _taskIndex;
		int _taskType;

	public:
		//Constructor
		Task();
		

		//Setters
		void setTaskStartDatetime(ptime dateTimeToSet);
		void setTaskEndDatetime(ptime dateTimeToSet);
		void setTaskDeadline(ptime dateTimeToSet);
		void setTaskDuration(time_duration durationToSet);
		void setTaskName(string nameToSet);
		void setTaskDetails(string detailsToSet); // Not used for now
		void setTaskTags(vector<string> tagsToSet);
		void setTaskIndex(int indexToSet);
		
		//Getters
		int getTaskType();
		int getTaskIndex();
		ptime getTaskStartDatetime();
		ptime getTaskEndDatetime();
		ptime getTaskDeadline();
		time_duration getTaskDuration();
		string getTaskName();
		string getTaskDetails();//Not used for now
		vector<string> getTaskTags();

		//Operations
		bool isTaskOverlapWith(Task myTask);
		bool isEarlierThan(Task myTask);
};

#endif